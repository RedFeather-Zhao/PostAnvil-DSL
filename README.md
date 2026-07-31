# PostAnvil DSL

## 解决方案结构

- `PostAnvil DSL`：核心静态库，包含 PostAnvil 公共头文件和 ANTLR 生成源文件，输出 `PostAnvil.lib`。
- `UnitTest1_Basic`：Visual Studio 原生 C++ 单元测试项目，通过项目引用使用核心库，输出由测试资源管理器加载的 `UnitTest1_Basic.dll`。

ANTLR 生成的 `.cpp` 只在核心静态库中编译一次。单元测试项目负责链接核心库和 `antlr4-runtime.lib`，不重复编译解析器源文件。

## 运行单元测试

1. 在 Visual Studio 顶部选择 `Debug | x64`。
2. 使用“生成”→“生成解决方案”（`Ctrl+Shift+B`）。
3. 打开“测试”→“测试资源管理器”。
4. 运行全部测试，或者右键某个 `TEST_METHOD` 单独运行/调试。

单元测试项目生成 DLL 而不是控制台 EXE，因此不需要设置启动项目，也不通过 `F5` 直接启动。

## 测试代码结构

- `pch.h`：预编译单元测试框架、PostAnvil 和常用标准库头文件。
- `TestSupport.hpp/.cpp`：复用场景构造、DSL 编译执行和常用断言。
- `UnitTest1_Basic.cpp`：基础表达式与过滤规则。
- `AttributeCollectionTests.cpp`：属性、分组和追加规则。
- `SortFunctionTests.cpp`：布尔值、排序和简单函数。
- `ValueBuiltinTests.cpp`：类型、变量、实例身份和内置函数。
- `ControlFlowTests.cpp`：条件、循环和实例函数。
- `IntegrationTests.cpp`：宿主导入导出与端到端流程。

当前共有 49 个可被测试资源管理器独立发现的测试方法。

## 添加测试样例

通常无需新建测试项目。右键 `UnitTest1_Basic`，选择“添加”→“新建项”并添加 `.cpp` 文件；首行包含 `pch.h`，随后包含 `TestSupport.hpp`：

```cpp
#include "pch.h"
#include "TestSupport.hpp"
```

简单测试优先调用 `make_scene`、`make_confidence_scene`、`evaluate` 或 `evaluate_and_expect_counts`，只在测试方法内保留该场景特有的输入和断言，避免重复编写编译器及运行逻辑。

当前 ANTLR 运行库路径配置为 `D:\UserBin\antlr-vs2022-runtime`，并使用 x64 静态库。如果运行库位置改变，需要通过测试项目“属性”中的 C/C++ 包含目录及链接器库目录进行调整。
