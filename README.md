# PostAnvil CMake 工程

这是 PostAnvil 0.8 的跨平台工程根目录，可独立完成构建、测试、安装、打包以及
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
├─ tests/                   62 项跨平台测试与预编译头
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
python -m pip install /path/to/postanvil-0.8.0-cp314-cp314-linux_x86_64.whl
```

Windows PowerShell 示例：

```powershell
python -m pip install .\downloads\postanvil-0.8.0-cp314-cp314-win_amd64.whl
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
python -m pip install -U build scikit-build-core pybind11
```

Windows 还需要安装带“使用 C++ 的桌面开发”组件的 Visual Studio 2022 或更高版本，
并在对应的 **x64 Native Tools Command Prompt/Developer PowerShell** 中运行构建命令。
Windows 构建推荐直接使用 Visual Studio 自带的 CMake、Ninja 和 MSVC，不必把
`cmake`、`ninja` 安装到 Conda 环境。Linux 和 macOS 需要可用的 C++20 编译器及 Ninja；
若系统未提供 CMake/Ninja，可以在隔离的 Conda 构建环境中安装：

```bash
python -m pip install -U cmake ninja
```

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

Windows 如果要求 C++ 构建完全使用 Visual Studio 自带工具，请先激活 Conda 环境，
再打开 Visual Studio 的 **Developer PowerShell**，在工程根目录执行：

```powershell
$vsCmake = Join-Path $env:VSINSTALLDIR 'Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
$vsNinja = Join-Path $env:VSINSTALLDIR 'Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe'
$compiler = (Get-Command cl.exe -ErrorAction Stop).Source
$mt = (Get-Command mt.exe -ErrorAction Stop).Source
$rc = (Get-Command rc.exe -ErrorAction Stop).Source

$env:PYTHONNOUSERSITE = '1'
$env:CMAKE_EXECUTABLE = $vsCmake
$env:CMAKE_MAKE_PROGRAM = $vsNinja
$env:CMAKE_GENERATOR = 'Ninja'
$env:CXX = $compiler
$env:CC = $compiler
$env:CMAKE_BUILD_PARALLEL_LEVEL = '1'
$env:SKBUILD_BUILD_DIR = 'out/build/wheel-vs-release'

$ninjaArg = $vsNinja.Replace('\', '/')
$mtArg = $mt.Replace('\', '/')
$rcArg = $rc.Replace('\', '/')
$env:CMAKE_ARGS = "-DCMAKE_MAKE_PROGRAM=`"$ninjaArg`" -DCMAKE_MT:FILEPATH=`"$mtArg`" -DCMAKE_RC_COMPILER:FILEPATH=`"$rcArg`""

python -c "import sys; print(sys.executable)"
python -m build --wheel --no-isolation
```

`PYTHONNOUSERSITE=1` 防止构建后端读取用户级 Python 包；`python`、`build`、
`scikit-build-core` 和 `pybind11` 仍来自当前 Conda 环境。显式设置原生工具路径可以避免
机器上其他 Python/Conda 环境中的 CMake 或 Ninja 被误选。首次 Release 编译较慢；
`SKBUILD_BUILD_DIR` 会保留构建目录，后续未改变工具链时可增量构建。

产物位于 `dist/`，例如：

```text
dist/postanvil-0.8.0-cp314-cp314-win_amd64.whl
```

`python -m build` 只负责生成发布文件，不会自动把它安装到当前环境。构建结束后仍需执行
下一节的 `python -m pip install`。

### 安装并测试刚构建的 wheel

将下面的文件名替换为 `dist/` 中的实际产物：

```bash
python -m pip install --force-reinstall --no-deps \
  dist/postanvil-0.8.0-cp314-cp314-win_amd64.whl
python -m pip check
python -c "import postanvil; print(postanvil.__version__); print(postanvil.__file__)"
```

Windows PowerShell 可以写成一行：

```powershell
python -m pip install --force-reinstall --no-deps .\dist\postanvil-0.8.0-cp314-cp314-win_amd64.whl
```

从工程根目录运行仓库自带的冒烟测试：

```bash
python -c "import runpy; runpy.run_path('bindings/python/smoke_test.py', run_name='__main__')"
python -c "import runpy; runpy.run_path('bindings/python/compile_error_smoke_test.py', run_name='__main__')"
python -c "import runpy; runpy.run_path('bindings/python/ultralytics_smoke_test.py', run_name='__main__')"
```

不要直接运行 `python bindings/python/smoke_test.py`。直接运行时，脚本目录中的源码包
可能优先于环境中安装的 wheel，导致测试对象不是刚安装的产物。
这些命令不把 `bindings/python` 加入模块搜索路径，因此会测试当前环境中实际安装的 wheel，
并分别验证基础绑定、编译错误诊断和无需安装 Ultralytics 的适配层替身测试。

也可以手工验证主要功能：

```python
import postanvil

source = '''
RULE FILTER "global" {
	self.conf >= 0.5
}
'''

scene = postanvil.Scene(postanvil.Image(640, 640))
scene.add("person", postanvil.Instance(10, 20, 100, 200, 0.9))
scene.add("person", postanvil.Instance(30, 40, 80, 120, 0.2))
result = postanvil.compile(source).evaluate(scene)
assert result.count("PERSON") == 1
```

`Instance` 只保存检测框、置信度和动态属性，不保存类别。类别关系由
`Scene.add(cls_name, instance)` 建立；同一实例 ID 可以属于多个类别，但始终对应
Scene 中同一个实例对象。

`Scene.add()` 返回一个 `InstanceHandle`，句柄包含 Scene 内稳定 `id`和当前
类别上下文 `cls_name`。可以用句柄将同一实例加入其他类别，不会复制检测框：

```python
scene = postanvil.Scene(postanvil.Image(640, 640))
person = scene.add("person", postanvil.Instance(10, 20, 100, 200, 0.9))
scene.append_to_class("foreground", person)

assert person.id == 1
assert scene.instance_ids("PERSON") == [1]
assert scene.instance_ids("FOREGROUND") == [1]
assert scene.instance_count == 1
```

`Scene.handles(cls_name)` 返回带该类别上下文的句柄；`get_by_id(id)` 返回不带类别
上下文的句柄；`get_by_index(cls_name, index)` 使用从 1 开始的类别内位置。
`append_id_to_class()` 适用于已有 ID，`replace_class_ids()` 用一组 ID 整体替换类别
成员。这些操作只修改类别成员关系，不改变实例本身。

Python 也支持用 `InstanceHandle` 交换 DSL `INST` 值：

```python
scene.add_import("ANCHOR", person)
result = postanvil.compile("IMPORT INST anchor\nEXPORT anchor AS selected").evaluate(scene)
selected = result.get_export("selected")
assert isinstance(selected, postanvil.InstanceHandle)
assert selected.id == person.id
```

编译失败时，`PACompileError` 除了可读的 `str(error)`，还提供 `kind`、`message`、
`line`、`column`、`source_line`、`hint` 和 `raw_message` 属性。`kind` 是
`CompileErrorKind.SYNTAX`、`SEMANTIC` 或 `INTERNAL`：

```python
try:
    postanvil.compile(source)
except postanvil.PACompileError as error:
    print(error.kind, error.line, error.column)
    print(error.message)
    if error.hint:
        print("help:", error.hint)
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
python -m pip install "./dist/postanvil-0.8.0-<python>-<abi>-<platform>.whl[ultralytics]"
```

编译一次规则，然后复用于每个 `Results`：

```python
from ultralytics import YOLO
import postanvil

model = YOLO("model.pt")
program = postanvil.compile('''
RULE FILTER "global" {
	self.conf >= 0.5
}
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
时显式传入 `allow_new_classes=True`。一个 PostAnvil 实例可以同时属于多个类别，而 YOLO
单个框只有一个类别字段；写回时优先使用实例仍然所属的原始标签类别。原始类别成员关系
已被移除时，实例必须只剩一个候选类别，否则适配器会报告类别歧义，避免静默复制检测框。

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

当前 Android 预设面向 **API 32 及以上**，支持 `arm64-v8a` 和 `armeabi-v7a`，
使用 Android NDK、CMake 和 Ninja 交叉编译。项目不会把开发者本机的 NDK
绝对路径写入公共预设。构建时可通过 `POSTANVIL_ANDROID_NDK` 指定 NDK，或将
`ANDROID_NDK_HOME` 指向 NDK 根目录。项目的 Android toolchain 入口同时兼容
真正的 NDK 根目录，以及其下只有一个 NDK 版本子目录的外层目录。

### 一次构建两个 ABI

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

每个 ABI 目录都包含 `lib/libpostanvil_static.a`、公开头文件和
`lib/cmake/PostAnvil`；启用 Android JNI 构建时还包含
`lib/libpostanvil_jni.so`。

### 单独使用 CMake 预设

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

### 在现有 C++ Android 工程中使用静态库

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

### 将预编译 JNI 库放入 Android 应用

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

### 由 Gradle externalNativeBuild 直接构建

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

### 真机最小验证

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

### Java 调用方式

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

只需类别数量时可使用 `evaluateCounts(..., outputClasses)`。应显式传入要查询的
`outputClasses`，这样才能读取 `GROUP` 或 `APPEND` 新建类别的数量。不带
`outputClasses` 的重载仅查询输入 `classes` 中出现过的类别。

DSL 编译失败在 Java 层映射为 `IllegalArgumentException`；输入数组无效也使用
`IllegalArgumentException`；DSL 执行错误映射为 `IllegalStateException`；其他原生异常映射为
`RuntimeException`。当前 Android 轻量绑定专注检测框输入和类别成员输出，尚未暴露
`IMPORT` / `EXPORT`、动态属性和类别属性；需要这些能力时应使用 C++ 或 Python API。

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
