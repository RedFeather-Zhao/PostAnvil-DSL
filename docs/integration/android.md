# Android 接入

[文档中心](../README.md) · [原生项目构建](../development/building.md)

## 本页目录

- [平台与构建配置](#平台与构建配置)
- [一次构建两个 ABI](#一次构建两个-abi)
- [单独使用 CMake 预设](#单独使用-cmake-预设)
- [在 C++ Android 工程中使用静态库](#在-c-android-工程中使用静态库)
- [使用预编译 JNI 库](#使用预编译-jni-库)
- [Gradle 直接构建](#gradle-直接构建)
- [真机验证](#真机验证)
- [Java 调用方式](#java-调用方式)

## 平台与构建配置

当前 Android 预设面向 **API 32 及以上**，支持 `arm64-v8a` 和 `armeabi-v7a`，
使用 Android NDK、CMake 和 Ninja 交叉编译。项目不会把开发者本机的 NDK
绝对路径写入公共预设。构建时可通过 `POSTANVIL_ANDROID_NDK` 指定 NDK，或将
`ANDROID_NDK_HOME` 指向 NDK 根目录。项目的 Android toolchain 入口同时兼容
真正的 NDK 根目录，以及其下只有一个 NDK 版本子目录的外层目录。

## 一次构建两个 ABI

Android 的 ABI 是 CMake 配置期参数，不能在同一个 CMake 缓存中同时设置两个值。
项目因此为每个 ABI 使用独立的构建目录，并由脚本依次完成配置、编译和安装：

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass `
    -File ./packaging/build-android.ps1 `
    -NdkPath 'D:\Android\Sdk\ndk\29.0.14206865'
```

`ExecutionPolicy Bypass` 只作用于本次子进程，不修改系统或用户的 PowerShell
执行策略。请在 Visual Studio Developer PowerShell 中运行，或先确保当前终端可以
找到 `cmake` 和 `ninja`。

默认同时构建 `arm64-v8a` 和 `armeabi-v7a`。也可只构建指定 ABI：

```powershell
powershell.exe -NoProfile -ExecutionPolicy Bypass `
    -File ./packaging/build-android.ps1 `
    -NdkPath 'D:\Android\Sdk\ndk\29.0.14206865' `
    -Abis arm64-v8a
```

双 ABI SDK 安装目录如下，可直接按 `${ANDROID_ABI}` 选取：

```text
out/install/android-release/
├── arm64-v8a/
│   ├── include/
│   └── lib/
└── armeabi-v7a/
    ├── include/
    └── lib/
```

每个 ABI 目录都包含 `lib/libpostanvil_static.a`、公开头文件、
`share/PostAnvil/android/postanvil-java.jar` 和
`lib/cmake/PostAnvil`；启用 Android JNI 构建时还包含
`lib/libpostanvil_jni.so`。

## 单独使用 CMake 预设

下列示例使用 `arm64-v8a`。`POSTANVIL_ANDROID_NDK` 可以指向真正的 NDK 根目录，
也可以指向仅包含一个版本子目录的外层目录：

```powershell
cmake --fresh --preset android-arm64-release `
    -DPOSTANVIL_ANDROID_NDK='D:/Android/Sdk/ndk/29.0.14206865'
cmake --build --preset android-arm64-release-install --parallel 4
```

构建 `armeabi-v7a` 时，将两个预设名替换为：

```powershell
cmake --fresh --preset android-armv7-release `
    -DPOSTANVIL_ANDROID_NDK='D:/Android/Sdk/ndk/29.0.14206865'
cmake --build --preset android-armv7-release-install --parallel 4
```

也可以先为当前终端设置环境变量，此后省略命令行中的 NDK 参数：

```powershell
$env:ANDROID_NDK_HOME = 'D:\Android\Sdk\ndk\29.0.14206865'

cmake --preset android-arm64-release
cmake --build --preset android-arm64-release-install
```

在 Visual Studio 中选择 Android 预设前，应确保启动 Visual Studio 的进程环境中
存在 `ANDROID_NDK_HOME`；环境变量在 Visual Studio 启动后才设置时，需要重启
Visual Studio。旧配置已经出现 `CMAKE_CXX_COMPILER not set` 时，应使用 `--fresh`
重新配置，或在 Visual Studio 中删除对应预设的缓存后重新生成。项目 toolchain 会将
解析后的 NDK 路径传给 CMake 的编译器探测子配置，避免编译器探测阶段丢失 NDK。

Release 预设固定为 `ANDROID_PLATFORM=android-32` 和 `ANDROID_STL=c++_static`，
各 ABI 预设分别设置 `ANDROID_ABI`。`c++_static` 使 JNI 库不需要额外随 APK 分发
`libc++_shared.so`。若应用的其他原生库已统一使用 `c++_shared`，应在所有
原生库之间保持一致，而不是在同一进程中混用两套 C++ 运行时。

`arm64-v8a` 可部署产物位于：

```text
out/install/android-release/arm64-v8a/lib/libpostanvil_jni.so
```

未剥离符号的构建产物位于
`out/build/android-arm64-release/bindings/android/libpostanvil_jni.so`，用于本地符号化和
原生崩溃排查。日常 JNI 调试可改用：

```powershell
cmake --preset android-arm64-debug
cmake --build --preset android-arm64-debug
```

## 在 C++ Android 工程中使用静态库

如果宿主只使用 C++，不从 Java 或 Kotlin 调用 PostAnvil，就不需要 JNI bridge。
将对应 ABI 的安装目录复制到应用工程后，可以直接消费随 SDK 导出的 CMake 包：

```cmake
set(PostAnvil_DIR
    "${CMAKE_SOURCE_DIR}/postanvil-android-release/${ANDROID_ABI}/lib/cmake/PostAnvil")
find_package(PostAnvil CONFIG REQUIRED)

target_link_libraries(yolo11_jni PRIVATE PostAnvil::static)
```

`PostAnvil::static` 会同时提供头文件搜索路径和静态库链接信息，不需要手工
`add_library(... IMPORTED)`。最终生成 `.so` 的页面对齐仍由宿主工程负责；`.a`
本身不决定 APK 中动态库的页面大小。

## 使用预编译 JNI 库

将 Release 产物放入应用的 ABI 目录：

```text
app/src/main/jniLibs/arm64-v8a/libpostanvil_jni.so
```

将 `bindings/android/java/org/postanvil/NativeBridge.java` 复制到应用的
`app/src/main/java/org/postanvil/NativeBridge.java`。不要更改其包名，因为当前 JNI 导出
符号与 `org.postanvil.NativeBridge` 类名绑定。Android 模块至少需要：

```kotlin
android {
    compileSdk = 32 // 或更高

    defaultConfig {
        minSdk = 32
        ndk {
            abiFilters += listOf("arm64-v8a", "armeabi-v7a")
        }
    }
}
```

如果 Release 构建启用 R8/ProGuard，在应用的保留规则中加入：

```proguard
-keep class org.postanvil.NativeBridge { *; }
-keep class org.postanvil.NativeBridge$* { *; }
```

否则混淆后的类名可能与 JNI 导出符号不一致。

## Gradle 直接构建

如果应用希望在 Gradle 构建期直接编译本仓库，`externalNativeBuild` 的 CMake
路径指向项目根目录的 `CMakeLists.txt`，并传入：

```text
-DANDROID_PLATFORM=android-32
-DANDROID_STL=c++_static
-DPOSTANVIL_BUILD_STATIC=ON
-DPOSTANVIL_BUILD_SHARED=OFF
-DPOSTANVIL_BUILD_TESTS=OFF
-DPOSTANVIL_BUILD_PYTHON=OFF
-DPOSTANVIL_BUILD_ANDROID_JNI=ON
```

Gradle 中同样应显式声明需要的 ABI，并使用 NDK 29.0.14206865 或后续已验证版本。

## 真机验证

Java 示例位于 `bindings/android/java/org/postanvil/NativeBridge.java`。先在真机上
验证动态库加载和基本执行：

```java
if (!"0.8.0".equals(NativeBridge.version())) {
    throw new AssertionError("Unexpected PostAnvil native version");
}

try (NativeBridge.Program program = new NativeBridge.Program(
        "RULE FILTER \"person\" {\n    self.conf >= 0.5\n}")) {
    NativeBridge.SceneResult result = program.evaluate(
        640,
        480,
        new String[] {"person", "person"},
        new double[] {
            10, 20, 100, 200, 0.90,
            30, 40, 80, 120, 0.20
        });
    if (result.count("PERSON") != 1) {
        throw new AssertionError("Unexpected filtered instance count");
    }
    if (result.allInstanceCount() != 2
        || result.count(NativeBridge.ALL_INST) != 2) {
        throw new AssertionError("Unexpected ALL_INST membership");
    }
}
```

`Program` 会缓存编译结果，应在页面或模型生命周期内复用，并在结束时
调用 `close()`。真机出现 `UnsatisfiedLinkError` 时，先解压 APK 确认
`lib/arm64-v8a/libpostanvil_jni.so` 存在，再确认类包名和 R8 保留规则。
安装 Android SDK Platform-Tools 后，可在连接设备时先确认系统版本和 ABI：

```bash
adb shell getprop ro.build.version.sdk
adb shell getprop ro.product.cpu.abilist
```

第一条命令应返回 `32` 或更高，第二条应包含 `arm64-v8a`。

## Java 调用方式

Android 绑定接收扁平化的检测输入：`classes[i]` 是第 `i` 个框的类别，
`boxes` 每 5 个数表示一个 `[x, y, width, height, confidence]`。两个数组必须
满足 `boxes.length == classes.length * 5`。

```java
String source = "RULE FILTER \"person\" {\n    self.conf >= 0.5\n}";
String[] classes = {"person", "person"};
double[] boxes = {
    10, 20, 100, 200, 0.90,
    30, 40, 80, 120, 0.20
};

try (NativeBridge.Program program = new NativeBridge.Program(source)) {
    NativeBridge.SceneResult result = program.evaluate(640, 480, classes, boxes);
    long kept = result.count("PERSON");
    long allKept = result.count(NativeBridge.ALL_INST);
    long[] allIds = result.allInstanceIds();
    for (int i = 0; i < result.size(); ++i) {
        String clsName = result.className(i);
        long instanceId = result.instanceId(i);
        double[] box = result.box(i);
    }
}
```

`SceneResult` 是执行后 Scene 的不可变类别成员快照，每行包含类别名、稳定实例 ID
和 5 个框数值。如果一个实例同时属于多个类别，结果中会出现多行，但这些行使用
同一个 `instanceId`；这表示多个类别成员关系，不表示实例被复制。`classNames()`、
`instanceIds()` 和 `boxes()` 返回防御性副本。

内置类别不混入普通类别行。`allInstanceCount()`、`allInstanceId()`、
`allInstanceBox()`、`allInstanceIds()` 和 `allInstanceBoxes()` 单独暴露 `ALL_INST`
当前的类别视图；`count(NativeBridge.ALL_INST)` 也返回该数量。输入 `classes`
不得使用保留名 `ALL_INST`，Java 和 JNI 两层都会拒绝冲突。

只需类别数量时可使用 `evaluateCounts(..., outputClasses)`。应显式传入要查询的
`outputClasses`，这样才能读取 `GROUP` 或 `APPEND` 新建类别的数量。不带
`outputClasses` 的重载仅查询输入 `classes` 中出现过的类别。

DSL 编译失败在 Java 层映射为 `IllegalArgumentException`；输入数组无效也使用
`IllegalArgumentException`；DSL 执行错误映射为 `IllegalStateException`；其他原生异常映射为
`RuntimeException`。当前 Android 轻量绑定专注检测框输入和类别成员输出，尚未暴露
`IMPORT` / `EXPORT`、动态属性和类别属性；需要这些能力时应使用 C++ 或 Python API。

---

上一篇：[Python 接入](python.md) · [返回文档中心](../README.md)
