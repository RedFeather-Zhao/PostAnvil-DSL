# Python 包构建与发布

[文档中心](../README.md) · [Python 接入](../integration/python.md)

Python wheel 使用 `scikit-build-core` 调用同一份 CMake 工程。`pybind11` 扩展会静态
链接 PostAnvil 和 ANTLR Runtime，因此安装 wheel 的最终用户不需要另外安装 CMake、
ANTLR 或本机动态库。

## 本页目录

- [选择 Python 环境](#选择-python-环境)
- [安装已发布版本](#安装已发布版本)
- [创建隔离构建环境](#创建隔离构建环境)
- [从源码构建 wheel](#从源码构建-wheel)
- [安装并验证 wheel](#安装并验证-wheel)
- [开发者构建方式](#开发者构建方式)
- [常见问题](#常见问题)
- [发布新版本](#发布新版本)

## 选择 Python 环境

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

## 安装已发布版本

### 从 PyPI 安装

如果 wheel 已发布到 PyPI，最终用户直接安装：

```bash
python -m pip install postanvil
```

需要 Ultralytics YOLO 适配功能时安装可选依赖：

```bash
python -m pip install "postanvil[ultralytics]"
```

### 安装本地 wheel

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

## 创建隔离构建环境

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

## 从源码构建 wheel

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

## 安装并验证 wheel

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

## 开发者构建方式

### 从 GitHub Actions 下载多平台 wheel

仓库的 `.github/workflows/wheels.yml` 会在 push、Pull Request、推送 `v*` 标签时运行，
也可以在 GitHub 的 **Actions → python-wheels → Run workflow** 中手工触发。普通 push 和
Pull Request 构建 Python 3.12 作为快速回归；`v*` 版本标签和手动触发构建 Python
3.9–3.14 的完整发布矩阵。工作流会分别在 Windows、Linux 和 macOS 上构建，并上传按
平台、运行器架构区分的 artifact，例如：

```text
postanvil-wheels-windows-X64
postanvil-wheels-linux-X64
postanvil-wheels-macos-ARM64
```

每个 wheel 都会先安装到 cibuildwheel 的隔离测试环境，然后验证包版本，并运行基础绑定、
结构化编译错误和 Ultralytics 适配器替身测试。只有测试通过的 wheel 才会上传。

当前 macOS 预编译 wheel 的最低系统版本为 macOS 14.0。核心使用的 C++20
`std::format` 会依赖 Apple libc++ 的浮点 `std::to_chars`；该接口不能安全向后部署到
macOS 13.2 及更早版本。Linux 和 Windows wheel 不受此项 macOS 限制。

开发者可以在对应的工作流运行页面下载 artifact，解压后选择与 Python 版本、操作系统
和 CPU 架构匹配的 `.whl`，再按“方式二”安装。已安装 GitHub CLI 时也可以执行：

```bash
gh run list --workflow wheels.yml
gh run download RUN_ID --name postanvil-wheels-windows-X64 --dir downloads/wheels-Windows
```

将 `RUN_ID` 替换为第一条命令显示的运行编号。
Linux 或 macOS 将 artifact 名称替换为对应平台和运行器架构。GitHub 下载的是
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

## 常见问题

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

## 发布新版本

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

---

上一篇：[原生项目构建](building.md) · [返回文档中心](../README.md)
