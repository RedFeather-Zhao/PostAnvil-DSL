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

DSL 语法、规则、类型、内置属性与宿主 API 的完整说明见
[PostAnvil DSL 用户手册](docs/PostAnvil%20DSL%20用户手册.md)。

## 先选择需要的构建方式

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

## Python 包：获取、构建、安装和验证

Python wheel 使用 `scikit-build-core` 调用同一份 CMake 工程。`pybind11` 扩展会静态
链接 PostAnvil 和 ANTLR Runtime，因此安装 wheel 的最终用户不需要另外安装 CMake、
ANTLR 或本机动态库。

### 将包安装到哪个 Python 环境

所有安装命令都使用 `python -m pip`，这样 wheel 会安装到该 `python` 对应的环境中。
执行前先确认解释器位置和版本：

```bash
python -c "import sys; print(sys.executable); print(sys.version)"
python -m pip --version
```

使用 Conda 时，推荐先激活目标环境：

```bash
conda activate postanvil-test
python -c "import sys; print(sys.executable)"
```

不想激活环境时，也可以明确指定环境执行安装，例如：

```bash
conda run -n postanvil-test python -m pip install path/to/postanvil.whl
```

不要使用来源不明的裸 `pip` 命令，因为它可能属于系统 Python 或另一个虚拟环境。

### 方式一：安装 PyPI 上发布的版本

如果 wheel 已发布到 PyPI，最终用户直接安装：

```bash
python -m pip install postanvil
```

需要 Ultralytics YOLO 适配功能时安装可选依赖：

```bash
python -m pip install "postanvil[ultralytics]"
```

### 方式二：安装下载或他人提供的 wheel

如果拿到的是本地 wheel 文件，在 **目标 Python 环境** 中执行：

```bash
python -m pip install /path/to/postanvil-0.7.0-cp314-cp314-linux_x86_64.whl
```

Windows PowerShell 示例：

```powershell
python -m pip install .\downloads\postanvil-0.7.0-cp314-cp314-win_amd64.whl
```

wheel 文件名中的 Python ABI 和平台必须与用户环境匹配。例如，`cp314-cp314-win_amd64`
表示 CPython 3.14、CPython 3.14 ABI、Windows x64；其他 Python 版本、操作系统和 CPU
架构通常需要各自的 wheel。pip 报告 `not a supported wheel on this platform` 时，应更换
匹配的文件，而不是修改文件名。

### 创建隔离的构建与测试环境

推荐使用独立 Conda 环境，避免修改系统 Python 或项目目录：

```bash
conda create -n postanvil-build python=3.14 pip -y
conda activate postanvil-build
python -m pip install -U build scikit-build-core pybind11 cmake ninja
```

Windows 还需要安装带“使用 C++ 的桌面开发”组件的 Visual Studio 2022 或更高版本，
并在对应的 **x64 Native Tools Command Prompt/Developer PowerShell** 中运行构建命令。
Linux 和 macOS 需要可用的 C++20 编译器及 Ninja。

### 方式三：从源码构建 wheel

在工程根目录执行标准隔离构建：

```bash
python -m build --wheel
```

如果当前 Conda 环境已经安装了 `pyproject.toml` 中声明的全部构建依赖，可以避免创建
一次性隔离环境：

```bash
python -m build --wheel --no-isolation
```

产物位于 `dist/`，例如：

```text
dist/postanvil-0.7.0-cp314-cp314-win_amd64.whl
```

`python -m build` 只负责生成发布文件，不会自动把它安装到当前环境。构建结束后仍需执行
下一节的 `python -m pip install`。

### 安装并测试刚构建的 wheel

将下面的文件名替换为 `dist/` 中的实际产物：

```bash
python -m pip install --force-reinstall --no-deps \
  dist/postanvil-0.7.0-cp314-cp314-win_amd64.whl
python -m pip check
python -c "import postanvil; print(postanvil.__version__); print(postanvil.__file__)"
```

Windows PowerShell 可以写成一行：

```powershell
python -m pip install --force-reinstall --no-deps .\dist\postanvil-0.7.0-cp314-cp314-win_amd64.whl
```

从工程根目录运行仓库自带的冒烟测试：

```bash
python -c "p='bindings/python/smoke_test.py'; exec(compile(open(p, encoding='utf-8').read(), p, 'exec'))"
python -I bindings/python/compile_error_smoke_test.py
```

不要直接运行 `python bindings/python/smoke_test.py`。直接运行时，脚本目录中的源码包
可能优先于环境中安装的 wheel，导致测试对象不是刚安装的产物。
第二条命令使用 Python 隔离模式验证编译错误的源码行、插入符和提示文本。

也可以手工验证主要功能：

```python
import postanvil

source = '''
RULE FILTER "global":
	self.conf >= 0.5
RULEEND
'''

scene = postanvil.Scene(postanvil.Image(640, 640), [
	postanvil.Instance("person", 10, 20, 100, 200, 0.9),
	postanvil.Instance("person", 30, 40, 80, 120, 0.2),
])
result = postanvil.compile(source).evaluate(scene)
assert result.count("PERSON") == 1
```

### 从 GitHub Actions 下载多平台 wheel

仓库的 `.github/workflows/wheels.yml` 会在推送 `v*` 标签时运行，也可以在 GitHub 的
**Actions → python-wheels → Run workflow** 中手工触发。工作流会分别在 Windows、Linux
和 macOS 上构建，并上传 `wheels-Windows`、`wheels-Linux`、`wheels-macOS` artifact。

开发者可以在对应的工作流运行页面下载 artifact，解压后选择与 Python 版本、操作系统
和 CPU 架构匹配的 `.whl`，再按“方式二”安装。已安装 GitHub CLI 时也可以执行：

```bash
gh run list --workflow wheels.yml
gh run download RUN_ID --name wheels-Windows --dir downloads/wheels-Windows
```

将 `RUN_ID` 替换为第一条命令显示的运行编号。
Linux 或 macOS 将 artifact 名称替换为 `wheels-Linux` 或 `wheels-macOS`。GitHub 下载的是
一个 artifact 压缩包或解压目录，不是 Python 安装源；最终仍需运行：

```powershell
$wheel = Get-ChildItem .\downloads\wheels-Windows\*.whl | Select-Object -First 1
python -m pip install $wheel.FullName
```

### 仅调试 Python 扩展：直接使用 CMake

绑定开发者可以绕过 wheel 前端，直接生成 `_postanvil` 扩展模块：

```bash
cmake -S . -B out/build/python-dev -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DPOSTANVIL_BUILD_PYTHON=ON \
  -DPOSTANVIL_BUILD_STATIC=ON \
  -DPOSTANVIL_BUILD_SHARED=OFF \
  -DPOSTANVIL_BUILD_TESTS=OFF \
  -DPython_EXECUTABLE=/path/to/python \
  -Dpybind11_DIR="$(python -m pybind11 --cmakedir)"
cmake --build out/build/python-dev --parallel
```

直接构建前也要在当前 Python 中安装 `pybind11`。Windows PowerShell 可先执行
`$pybind11Dir = python -m pybind11 --cmakedir`，然后将最后两个参数写为
`"-DPython_EXECUTABLE=$env:CONDA_PREFIX\python.exe"` 和 `"-Dpybind11_DIR=$pybind11Dir"`。
这种方式适合排查 C++/pybind11 编译问题，但生成的 `_postanvil.pyd` 或
`_postanvil.so` 不是完整 Python 包：它不包含 `postanvil/__init__.py`、适配器和包元数据，
也不应作为公开分发方式。需要安装和交付时，仍应生成 wheel。

### Python 构建常见问题

- **`python` 或 `pip` 指向错误环境**：重新检查 `sys.executable` 和
  `python -m pip --version`，不要仅凭终端提示符判断。
- **找不到 C++ 编译器**：Windows 应从 Visual Studio Developer PowerShell 构建；
  Linux/macOS 应先确认 C++20 编译器和 Ninja 可用。
- **wheel 与环境不兼容**：核对文件名中的 Python ABI、操作系统和 CPU 架构；不能靠
  重命名 wheel 解决兼容性问题。
- **安装后仍导入旧版本**：使用 `--force-reinstall`，再打印 `postanvil.__file__` 确认
  实际加载位置。不要从 `bindings/python` 目录直接启动验证脚本。
- **CMake 仍使用旧配置**：对单独的构建目录执行
  `cmake --fresh -S . -B out/build/<所用目录> ...` 重新配置；不要删除或覆盖源码目录。
- **只得到了 `.pyd` / `.so`**：这是扩展模块而不是完整包。公开测试、交付和安装都应
  使用 wheel。

### Ultralytics YOLO 可选集成

普通 PostAnvil 安装不依赖 Ultralytics、PyTorch。需要直接处理 Ultralytics YOLO
轴对齐目标检测结果时，安装可选依赖：

```bash
python -m pip install "postanvil[ultralytics]"
```

对本地 wheel 安装可选依赖：

```bash
python -m pip install "./dist/postanvil-0.7.0-<python>-<abi>-<platform>.whl[ultralytics]"
```

编译一次规则，然后复用于每个 `Results`：

```python
from ultralytics import YOLO
import postanvil

model = YOLO("model.pt")
program = postanvil.compile('''
RULE FILTER "global":
	self.conf >= 0.5
RULEEND
''')

for detection in model("image.jpg"):
	postanvil.apply_ultralytics(program, detection)
	detection.save(filename="filtered.jpg")
```

也可以保留 PostAnvil `Scene`，自行读取动态属性、类别属性或导出值：

```python
scene = postanvil.from_ultralytics(detection)
output = program.evaluate(scene)
print(output.count("PERSON"))
```

`apply_ultralytics()` 会原地更新并返回输入的 Ultralytics `Results`。转换使用
`boxes.xyxy`，因为 PostAnvil 的 `x/y` 表示左上角，而 Ultralytics 的 `xywh`
使用中心点。跟踪结果中的 track ID 会保存在实例动态属性 `YOLO_TRACK_ID` 中并在
写回时恢复。

该集成目前只支持普通轴对齐目标检测框。为避免框与附加数据错位，包含分割掩码、
关键点、OBB、分类结果、语义掩码或深度数据的 `Results` 不允许写回。PostAnvil
动态属性和类别属性没有对应的 YOLO 张量字段，只保留在 `Scene` 中。若 `GROUP`、
`APPEND` 或类别修改产生模型名称表之外的新类别，默认会报错；确认需要分配新类别 ID
时显式传入 `allow_new_classes=True`。写回时以 `Scene` 的类别容器作为 YOLO 类别；
这是因为 YOLO 的单个框只有一个类别字段，无法同时保存源类别与派生分组。

Ultralytics `Results` 和 `Boxes` 的字段定义见其
[官方 Results API](https://docs.ultralytics.com/reference/engine/results/)。

### 发布新版本 wheel

发布新版本前，必须同步修改以下三个版本号，确保包元数据、CMake 包和原生模块一致：

1. `CMakeLists.txt` 中的 `project(PostAnvil VERSION ...)`；
2. `pyproject.toml` 中的 `[project].version`；
3. `src/api.cpp` 中 `postanvil::version()` 返回的字符串。

例如发布 `0.8.0` 时，三处都必须改为 `0.8.0`。然后执行：

```bash
python -m build --wheel
python -m pip install --force-reinstall --no-deps dist/postanvil-0.8.0-<python>-<abi>-<platform>.whl
python -c "import importlib.metadata as m, postanvil; assert m.version('postanvil') == '0.8.0'; assert postanvil.__version__ == '0.8.0'"
python -m pip check
```

请在每个需要支持的 Python 版本和平台上分别生成并测试 wheel。正式发布前还应运行
对应平台的 C++ 测试，并确认 `dist/` 中只包含本次版本的发布文件。

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

## 发布新版本原生包

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
