# PostAnvil DSL

## 解决方案结构

- `PostAnvil DSL`：核心静态库，仅包含 PostAnvil 头文件和 ANTLR 生成源文件，不包含测试。
- `PostAnvil Test`：基础规则、属性、分组与追加测试。
- `PostAnvil Test Language`：类型、函数、控制流、排序与内置函数测试。
- `PostAnvil Test Integration`：导入导出和端到端测试。

ANTLR 解析器必须编译其生成的 `.cpp`，因此核心项目使用静态库而不是纯头文件库，避免每个测试项目重复编译 ANTLR。日常开发可在 Visual Studio 中只生成需要运行的测试项目。

## 新建测试项目

1. 在当前解决方案中新建 C++ 空项目，将配置类型设为“应用程序”，平台选择 `x64`。
2. 添加对 `PostAnvil DSL\PostAnvil DSL.vcxproj` 的项目引用。
3. 在项目属性管理器中导入 `PostAnvil Test\PostAnvil.Test.props`。该属性表统一配置 C++20、UTF-8、PostAnvil/ANTLR 头文件目录和 ANTLR 静态库。
4. 添加自己的测试源文件；若要复用现有测试输出与统计逻辑，同时加入 `PostAnvil\tests\test_common.hpp` 和 `test_common.cpp`，并在 `main` 中调用 `run_test_suite`。

测试源码使用 UTF-8 执行字符集。公共测试运行器会在 Windows 上将控制台输入、输出代码页切换为 UTF-8，避免中文被系统默认 GBK 代码页错误解释。若自定义入口不使用 `run_test_suite`，应在输出中文前自行调用 `SetConsoleOutputCP(CP_UTF8)`。

`PostAnvil.Test.props` 中的 `AntlrRuntimeRoot` 默认指向 `D:\UserBin\antlr-vs2022-runtime`。如果本机 ANTLR 运行库位于其他位置，请在导入属性表前覆盖该属性；目前运行库目录仅配置了 `x64` 链接路径。
