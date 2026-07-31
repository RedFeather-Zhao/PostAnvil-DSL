#include <PostAnvil.h>

#include <jni.h>

#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>

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
    if (const jclass type = env->FindClass(class_name); type != nullptr) {
        env->ThrowNew(type, message.c_str());
    }
}

Program* program_from_handle(jlong handle)
{
    return reinterpret_cast<Program*>(handle);
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
        auto program = std::make_unique<Program>(Compiler{}.compile(to_utf8(env, source)));
        return reinterpret_cast<jlong>(program.release());
    }
    catch (const std::exception& error) {
        throw_java(env, "java/lang/IllegalArgumentException", error.what());
        return 0;
    }
}

extern "C" JNIEXPORT void JNICALL
Java_org_postanvil_NativeBridge_destroyProgram(JNIEnv*, jclass, jlong handle)
{
    delete program_from_handle(handle);
}

extern "C" JNIEXPORT jlongArray JNICALL
Java_org_postanvil_NativeBridge_evaluateCounts(
    JNIEnv* env,
    jclass,
    jlong handle,
    jdouble image_width,
    jdouble image_height,
    jobjectArray classes,
    jdoubleArray boxes)
{
    try {
        Program* program = program_from_handle(handle);
        if (program == nullptr) throw std::invalid_argument("Program handle is null");

        const jsize count = env->GetArrayLength(classes);
        if (env->GetArrayLength(boxes) != count * 5) {
            throw std::invalid_argument("boxes must contain [x,y,w,h,confidence] per class entry");
        }

        jboolean is_copy = JNI_FALSE;
        jdouble* values = env->GetDoubleArrayElements(boxes, &is_copy);
        if (values == nullptr) throw std::runtime_error("Cannot access boxes array");

        postanvil::Scene scene(postanvil::Image{ image_width, image_height });
        for (jsize i = 0; i < count; ++i) {
            auto label = static_cast<jstring>(env->GetObjectArrayElement(classes, i));
            scene.add(postanvil::Instance(to_utf8(env, label), values[i * 5],
                values[i * 5 + 1], values[i * 5 + 2], values[i * 5 + 3],
                values[i * 5 + 4]));
            env->DeleteLocalRef(label);
        }
        env->ReleaseDoubleArrayElements(boxes, values, JNI_ABORT);

        const auto result = program->evaluate(scene);
        auto output = env->NewLongArray(count);
        if (output == nullptr) return nullptr;
        std::unique_ptr<jlong[]> counts(new jlong[static_cast<std::size_t>(count)]{});
        for (jsize i = 0; i < count; ++i) {
            auto label = static_cast<jstring>(env->GetObjectArrayElement(classes, i));
            auto name = to_utf8(env, label);
            for (auto& ch : name) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
            const auto it = result.objects.find(name);
            counts[static_cast<std::size_t>(i)] =
                it == result.objects.end() ? 0 : static_cast<jlong>(it->second.size());
            env->DeleteLocalRef(label);
        }
        env->SetLongArrayRegion(output, 0, count, counts.get());
        return output;
    }
    catch (const std::exception& error) {
        throw_java(env, "java/lang/RuntimeException", error.what());
        return nullptr;
    }
}
