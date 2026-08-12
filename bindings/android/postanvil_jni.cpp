#include <PostAnvil.h>

#include <jni.h>

#include <algorithm>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using postanvil::Compiler;
using postanvil::Program;

namespace {

std::string to_utf8(JNIEnv* env, jstring text)
{
    if (text == nullptr) return {};

    const char* chars = env->GetStringUTFChars(text, nullptr);
    if (chars == nullptr) return {};

    std::string result(chars);
    env->ReleaseStringUTFChars(text, chars);
    return result;
}

void throw_java(JNIEnv* env, const char* class_name, const std::string& message)
{
    if (env->ExceptionCheck()) return;
    if (const jclass type = env->FindClass(class_name); type != nullptr) {
        env->ThrowNew(type, message.c_str());
        env->DeleteLocalRef(type);
    }
}

Program* program_from_handle(jlong handle)
{
    return reinterpret_cast<Program*>(handle);
}

jobject make_scene_result(JNIEnv* env, const postanvil::Scene& scene)
{
    std::vector<std::string> cls_names;
    cls_names.reserve(scene.class_index().size());
    for (const auto& [cls_name, _] : scene.class_index()) {
        cls_names.emplace_back(cls_name);
    }
    std::ranges::sort(cls_names);

    std::size_t row_count = 0;
    for (const auto& cls_name : cls_names) {
        row_count += scene.get_inst_count(cls_name);
    }
    constexpr auto BOX_VALUE_COUNT = std::size_t{ 5 };
    const auto max_array_size = static_cast<std::size_t>(std::numeric_limits<jsize>::max());
    if (row_count > max_array_size / BOX_VALUE_COUNT) {
        throw std::overflow_error("Scene result contains too many class memberships");
    }

    const auto output_count = static_cast<jsize>(row_count);
    const auto output_box_count = static_cast<jsize>(row_count * BOX_VALUE_COUNT);
    const jclass string_class = env->FindClass("java/lang/String");
    if (string_class == nullptr) return nullptr;

    const jobjectArray output_classes = env->NewObjectArray(output_count, string_class, nullptr);
    const jlongArray output_ids = env->NewLongArray(output_count);
    const jdoubleArray output_boxes = env->NewDoubleArray(output_box_count);
    env->DeleteLocalRef(string_class);
    if (output_classes == nullptr || output_ids == nullptr || output_boxes == nullptr) return nullptr;

    std::vector<jlong> ids(row_count);
    std::vector<jdouble> boxes(row_count * 5);
    jsize row = 0;
    for (const auto& cls_name : cls_names) {
        for (const auto id : scene.get_inst_ids(cls_name)) {
            const jstring output_cls_name = env->NewStringUTF(cls_name.c_str());
            if (output_cls_name == nullptr) return nullptr;
            env->SetObjectArrayElement(output_classes, row, output_cls_name);
            env->DeleteLocalRef(output_cls_name);
            if (env->ExceptionCheck()) return nullptr;

            const auto& instance = scene.inst(id);
            ids[static_cast<std::size_t>(row)] = static_cast<jlong>(id);
            const auto offset = static_cast<std::size_t>(row) * 5;
            boxes[offset] = instance.x1();
            boxes[offset + 1] = instance.y1();
            boxes[offset + 2] = instance.w();
            boxes[offset + 3] = instance.h();
            boxes[offset + 4] = instance.conf();
            ++row;
        }
    }

    env->SetLongArrayRegion(output_ids, 0, output_count, ids.data());
    env->SetDoubleArrayRegion(output_boxes, 0, output_box_count, boxes.data());
    if (env->ExceptionCheck()) return nullptr;

    const jclass result_class = env->FindClass("org/postanvil/NativeBridge$SceneResult");
    if (result_class == nullptr) return nullptr;
    const jmethodID constructor = env->GetMethodID(
        result_class, "<init>", "([Ljava/lang/String;[J[D)V");
    if (constructor == nullptr) {
        env->DeleteLocalRef(result_class);
        return nullptr;
    }

    const jobject result = env->NewObject(
        result_class, constructor, output_classes, output_ids, output_boxes);
    env->DeleteLocalRef(result_class);
    env->DeleteLocalRef(output_classes);
    env->DeleteLocalRef(output_ids);
    env->DeleteLocalRef(output_boxes);
    return result;
}

} // namespace

extern "C" JNIEXPORT jstring JNICALL
Java_org_postanvil_NativeBridge_version(JNIEnv* env, jclass)
{
    return env->NewStringUTF(postanvil::version());
}

extern "C" JNIEXPORT jlong JNICALL
Java_org_postanvil_NativeBridge_compile(JNIEnv* env, jclass, jstring source)
{
    try {
        if (source == nullptr) throw std::invalid_argument("source must not be null");
        auto program = std::make_unique<Program>(Compiler{}.compile(to_utf8(env, source)));
        if (env->ExceptionCheck()) return 0;
        return reinterpret_cast<jlong>(program.release());
    }
    catch (const postanvil::PACompileError& error) {
        throw_java(env, "java/lang/IllegalArgumentException", error.what());
        return 0;
    }
    catch (const std::exception& error) {
        throw_java(env, "java/lang/RuntimeException", error.what());
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_postanvil_NativeBridge_destroyProgram(JNIEnv*, jclass, jlong handle)
{
    delete program_from_handle(handle);
}

extern "C" JNIEXPORT jobject JNICALL
Java_org_postanvil_NativeBridge_evaluate(
    JNIEnv* env,
    jclass,
    jlong handle,
    jdouble image_width,
    jdouble image_height,
    jobjectArray classes,
    jdoubleArray boxes)
{
    try {
        Program* const program = program_from_handle(handle);
        if (program == nullptr) throw std::invalid_argument("Program handle is null");
        if (classes == nullptr) throw std::invalid_argument("classes must not be null");
        if (boxes == nullptr) throw std::invalid_argument("boxes must not be null");

        const jsize count = env->GetArrayLength(classes);
        const jsize value_count = env->GetArrayLength(boxes);
        if (count > std::numeric_limits<jsize>::max() / 5) {
            throw std::overflow_error("classes contains too many entries");
        }
        if (value_count != count * 5) {
            throw std::invalid_argument(
                "boxes must contain [x,y,w,h,confidence] per class entry");
        }

        std::vector<jdouble> values(static_cast<std::size_t>(value_count));
        env->GetDoubleArrayRegion(boxes, 0, value_count, values.data());
        if (env->ExceptionCheck()) return nullptr;

        postanvil::Scene scene(postanvil::Image{ image_width, image_height });
        for (jsize i = 0; i < count; ++i) {
            const auto label = static_cast<jstring>(env->GetObjectArrayElement(classes, i));
            if (env->ExceptionCheck()) return nullptr;
            if (label == nullptr) {
                throw std::invalid_argument("classes must not contain null entries");
            }

            const auto cls_name = to_utf8(env, label);
            env->DeleteLocalRef(label);
            if (env->ExceptionCheck()) return nullptr;

            const auto offset = static_cast<std::size_t>(i) * 5;
            scene.add(cls_name, postanvil::Instance(
                values[offset],
                values[offset + 1],
                values[offset + 2],
                values[offset + 3],
                values[offset + 4]));
        }

        return make_scene_result(env, program->evaluate(scene));
    }
    catch (const std::invalid_argument& error) {
        throw_java(env, "java/lang/IllegalArgumentException", error.what());
        return nullptr;
    }
    catch (const postanvil::PARuntimeError& error) {
        throw_java(env, "java/lang/IllegalStateException", error.what());
        return nullptr;
    }
    catch (const std::exception& error) {
        throw_java(env, "java/lang/RuntimeException", error.what());
        return nullptr;
    }
}
