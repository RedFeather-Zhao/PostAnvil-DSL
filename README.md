# PostAnvil CMake 工程

这是 PostAnvil 0.7 的跨平台工程根目录，可独立完成构建、测试、安装、打包以及
Python、Android 绑定构建。0.6 及更早版本的 Visual Studio 工程仍可从 Git 历史获取。

## 当前迁移结构

```text
PostAnvil/
├─ include/                 对外 C++ API（不暴露 ANTLR）
├─ src/                     公共 API 的 PImpl 实现
├─ grammar/                 PostAnvil.g4
├─ generated/antlr/         ANTLR 4.13.2 生成的解析器
├─ third_party/
│  ├─ antlr4-runtime/src/   直接参与构建的 Runtime 4.13.2 源码
│  └─ licenses/             第三方许可证
├─ tools/antlr/             ANTLR JAR 与 Runtime 原始源码 ZIP
├─ tests/                   49 项跨平台测试与预编译头
├─ bindings/python/         pybind11 扩展
├─ bindings/android/        Android JNI 适配层
├─ packaging/               本地原生包构建脚本
└─ .github/workflows/       跨平台构建与 wheel 工作流
```

ANTLR 只存在于库的内部实现。普通 C++ 使用者只需包含 `PostAnvil.h`，不会再配置
ANTLR 头目录、宏或外部 `antlr4-runtime.lib`。

## Windows：生成 Visual Studio 解决方案

在本目录打开 PowerShell：

```powershell
cmake --preset vs2026-x64
cmake --build --preset vs2026-debug
ctest --preset vs2026-debug
```

生成的解决方案位于：

```text
out/build/vs2026-x64/PostAnvil.sln
```

Release 构建：

```powershell
cmake --build --preset vs2026-release
ctest --test-dir out/build/vs2026-x64 -C Release --output-on-failure
```

若使用 VS 2022，可直接配置：

```powershell
cmake -S . -B out/build/vs2022-x64 -G "Visual Studio 17 2022" -A x64
```

### Visual Studio 图形界面操作

使用“文件 → 打开 → 文件夹”打开本目录后，在 Visual Studio 顶部选择需要的配置预设：

- `Ninja Debug`：日常开发，编译测试，产物位于 `out/build/ninja-debug`。
- `Ninja Release`：发布构建，不编译测试，产物位于 `out/build/ninja-release`。
- `Visual Studio 2026 x64`：生成多配置解决方案，可继续选择 Debug 或 Release。

在“解决方案资源管理器”中切换到“CMake 目标视图”，可以右键普通编译目标执行：

- `postanvil_static`：只编译静态库。
- `postanvil_shared`：只编译动态库。
- `postanvil_tests`：编译测试程序；仅 Debug 预设提供测试。

Visual Studio 的 CMake 目标视图可能隐藏 `install` 和 `package` 等全局目标。本项目已经将
这些操作封装成顶部配置下拉框中的构建预设：

- `Ninja Debug - 编译并安装`
- `Ninja Release - 编译并安装`
- `Ninja Release - 编译并打包`
- `VS Debug - 编译并安装`
- `VS Release - 编译并安装`
- `VS Release - 编译并打包`

选择相应预设后，使用“生成 → 全部生成”即可执行，无需在目标视图中寻找全局目标。

安装目录已经由预设固定，无需在图形界面中手工填写：

```text
out/install/debug       Ninja Debug 安装结果
out/install/release     Ninja Release 安装结果
out/install/vs2026-x64  Visual Studio 多配置安装结果
```

如果修改预设后目标或目录没有刷新，使用“项目 → 删除缓存并重新配置”，然后重新选择预设。

## Linux / macOS / Ninja

```bash
cmake --preset ninja-debug
cmake --build --preset ninja-debug
ctest --preset ninja-debug
```

只构建发布用静态库，不编译测试和动态库：

```bash
cmake -S . -B out/build/static-release -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DPOSTANVIL_BUILD_STATIC=ON \
  -DPOSTANVIL_BUILD_SHARED=OFF \
  -DPOSTANVIL_BUILD_TESTS=OFF
cmake --build out/build/static-release
```

## C++ 使用方式

源码树内直接链接：

```cmake
add_subdirectory(path/to/PostAnvil)
target_link_libraries(my_app PRIVATE PostAnvil::static)
```

使用发布预设编译并安装：

```bash
cmake --preset ninja-release
cmake --build --preset ninja-release-install
```

其中 `ninja-release-install` 会自动安装到 `out/install/release`。图形界面中选择
`Ninja Release - 编译并安装`，然后执行“生成 → 全部生成”具有相同效果。

```cmake
find_package(PostAnvil CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE PostAnvil::static) # 或 PostAnvil::shared
```

最小 C++ 代码：

```cpp
#include <PostAnvil.h>

postanvil::Compiler compiler;
auto program = compiler.compile(source);
postanvil::Scene result = program.evaluate(input_scene);
```

## 重新生成语法代码

日常构建不依赖 Java。修改 `grammar/PostAnvil.g4` 后显式运行：

```bash
cmake --build out/build/ninja-debug --target postanvil_generate_parser
```

该目标固定使用 `tools/antlr/antlr-4.13.2-complete.jar`，与内嵌 Runtime 版本一致。

## Python wheel

```bash
python -m pip install build
python -m build --wheel .
```

`scikit-build-core` 会调用同一份 CMake，`pybind11` 模块静态链接 PostAnvil 与
ANTLR Runtime，因此 wheel 使用者不需要额外安装本机动态库。

```python
from postanvil import Compiler, Image, Instance, Scene

program = Compiler().compile(source)
scene = Scene(Image(640, 640), [
	Instance("person", 10, 20, 100, 200, 0.9),
])
result = program.evaluate(scene)
```

## Android JNI

Gradle `externalNativeBuild` 的 CMake 路径指向本目录的 `CMakeLists.txt`，并传入：

```text
-DPOSTANVIL_BUILD_STATIC=ON
-DPOSTANVIL_BUILD_SHARED=OFF
-DPOSTANVIL_BUILD_TESTS=OFF
-DPOSTANVIL_BUILD_ANDROID_JNI=ON
```

生成 `libpostanvil_jni.so`。Java 示例位于
`bindings/android/java/org/postanvil/NativeBridge.java`。`Program` 会缓存编译结果，
应在页面或模型生命周期内复用，并在结束时调用 `close()`。

## 构建产物

- Windows Debug：`postanvil_static_d.lib`、`postanvil_d.dll/.lib`
- Windows Release：`postanvil_static.lib`、`postanvil.dll/.lib`
- Linux：`libpostanvil_static.a`、`libpostanvil.so`
- macOS：`libpostanvil_static.a`、`libpostanvil.dylib`
- Android：`libpostanvil_static.a`、可选 `libpostanvil_jni.so`

`cmake --build <build-dir> --target package` 可生成 ZIP/TGZ 原生开发包；安装树包含
头文件、库和 `PostAnvilConfig.cmake`。
