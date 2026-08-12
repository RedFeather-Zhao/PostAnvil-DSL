# 原生项目构建与发布

[文档中心](../README.md) · [项目首页](../../README.md)

## 本页目录

- [工程结构](#工程结构)
- [选择构建方式](#选择构建方式)
- [Windows 与 Visual Studio](#windows-与-visual-studio)
- [Linux、macOS 与 Ninja](#linuxmacos-与-ninja)
- [重新生成语法代码](#重新生成语法代码)
- [构建产物](#构建产物)
- [发布原生包](#发布原生包)

## 工程结构

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
├─ tests/                   62 项跨平台测试与预编译头
├─ bindings/python/         pybind11 扩展
├─ bindings/android/        Android JNI 适配层
├─ packaging/               本地原生包构建脚本
└─ .github/workflows/       跨平台构建与 wheel 工作流
```

ANTLR 只存在于库的内部实现。普通 C++ 使用者只需包含 `PostAnvil.h`，不会再配置
ANTLR 头目录、宏或外部 `antlr4-runtime.lib`。

DSL 语法、规则、类型、内置属性与宿主 API 的完整说明见
[DSL 快速开始](../dsl/README.md)。

## 选择构建方式

PostAnvil 同时提供 C++ 库、Python 包和 Android JNI 绑定。它们面向的使用场景不同，
构建产物也不能互相替代：

| 目标 | 推荐入口 | 主要产物 | 适用场景 |
| --- | --- | --- | --- |
| 开发和测试 C++ 核心 | `cmake --workflow --preset ninja-debug-check` | 调试库、测试程序 | 修改 C++、语法或运行时实现 |
| 构建 C++ Release 库 | `cmake --preset ninja-release` 后执行构建 | `.lib` / `.a` / `.dll` / `.so` / `.dylib` | 在本机项目中链接 |
| 安装 C++ 开发文件 | `cmake --build --preset ninja-release-install` | 头文件、库、CMake 包配置 | 供其他 CMake 工程使用 `find_package` |
| 分发 C++ 开发包 | `cmake --workflow --preset ninja-release-package` | ZIP（也可用脚本生成 ZIP/TGZ） | 给不参与源码构建的 C++ 使用者 |
| 分发或测试 Python 包 | `python -m build --wheel` | `.whl` | 安装到指定 Python/Conda 环境 |
| 构建 Android 绑定 | Android NDK + CMake | `libpostanvil_jni.so` | Android Java/Kotlin 应用 |

这里的“安装”有两种含义：`cmake --install` 安装的是 **C++ 开发文件**；
`python -m pip install` 安装的是 **Python 包**。如果目标是让 Python 能执行
`import postanvil`，应当构建并安装 wheel，而不是只复制 C++ 动态库或单独复制 `.pyd`。

开始前的通用要求：CMake 3.25 或更高版本、支持 C++20 的编译器。Ninja 预设还要求
系统或当前环境中能够找到 `ninja`。Python wheel 的额外要求见后文。

## Windows 与 Visual Studio

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

## Linux、macOS 与 Ninja

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

### 不使用预设：直接配置 CMake

预设只是保存了一组常用参数，并不是构建所必需的。需要自定义目录、生成器或库类型时，
可以直接传入以下开关：

```bash
cmake -S . -B out/build/custom -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DPOSTANVIL_BUILD_STATIC=ON \
  -DPOSTANVIL_BUILD_SHARED=ON \
  -DPOSTANVIL_BUILD_TESTS=OFF \
  -DPOSTANVIL_BUILD_PYTHON=OFF \
  -DPOSTANVIL_BUILD_ANDROID_JNI=OFF
cmake --build out/build/custom --parallel
```

各开关的含义：

- `POSTANVIL_BUILD_STATIC`：构建静态 C++ 库；Python 和 Android 绑定依赖此项。
- `POSTANVIL_BUILD_SHARED`：构建供 C++ 程序动态链接的库。
- `POSTANVIL_BUILD_TESTS`：构建并注册 C++ 测试。
- `POSTANVIL_BUILD_PYTHON`：构建 pybind11 扩展；通常由 `python -m build` 自动开启。
- `POSTANVIL_BUILD_ANDROID_JNI`：构建 Android JNI 共享库，只能配合 Android 工具链使用。

除非正在调试底层绑定构建过程，否则 Python 开发者不需要手工设置这些 CMake 参数；
`pyproject.toml` 已经为 wheel 选择了正确的组合。

## 重新生成语法代码

日常构建不依赖 Java。修改 `grammar/PostAnvil.g4` 后显式运行：

```bash
cmake --build out/build/ninja-debug --target postanvil_generate_parser
```

该目标固定使用 `tools/antlr/antlr-4.13.2-complete.jar`，与内嵌 Runtime 版本一致。

## 构建产物

- Windows Debug：`postanvil_static_d.lib`、`postanvil_d.dll/.lib`
- Windows Release：`postanvil_static.lib`、`postanvil.dll/.lib`
- Linux：`libpostanvil_static.a`、`libpostanvil.so`
- macOS：`libpostanvil_static.a`、`libpostanvil.dylib`
- Android：`libpostanvil_static.a`、可选 `libpostanvil_jni.so`

`cmake --build <build-dir> --target package` 可生成 ZIP/TGZ 原生开发包；安装树包含
头文件、库和 `PostAnvilConfig.cmake`。

仓库还提供了命令行打包脚本，适合不想记忆完整 CMake 参数的开发者：

```powershell
.\packaging\build-native.ps1 -Configuration Release
.\packaging\build-native.ps1 -Configuration Release -StaticOnly
```

```bash
./packaging/build-native.sh Release
```

脚本会依次配置、编译、安装并执行 CPack。安装树位于 `out/install/release`，打包文件位于
`out/build/package-release`。这些脚本生成的是 **C++ 原生开发包**，不会生成或安装
Python wheel；Python 包请使用前文的 `python -m build --wheel`。

## 发布原生包

原生包和 Python wheel 共用 `CMakeLists.txt` 中的项目版本。更新版本号并通过对应平台
测试后，可按以下方式生成面向 C++ 用户的安装包。

Windows Visual Studio 多配置构建：

```powershell
cmake --preset vs2026-x64
cmake --build --preset vs2026-release
ctest --test-dir out/build/vs2026-x64 -C Release --output-on-failure
cmake --build --preset vs2026-release-package-build
```

Linux、macOS 或 Windows Ninja 构建：

```bash
cmake --workflow --preset ninja-release-package
```

生成的 ZIP/TGZ 位于相应构建目录。最终用户解压后，可通过包内的
`PostAnvilConfig.cmake` 使用：

```cmake
find_package(PostAnvil CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE PostAnvil::static) # 或 PostAnvil::shared
```

---

[文档中心](../README.md) · 下一篇：[Python 包构建与发布](python-package.md)
