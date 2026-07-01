---
name: cpp-code-style-generator-reviewer
description: 通用 C++ 代码与注释风格规范，适用于头文件（.hpp）和源文件（.cpp）的生成与审查。
metadata:
  type: skill
  author: RedFeather-Zhao
  date: June 2026
  version: 1.0
---

# C++ 代码与注释风格规范（通用版）

## 适用场景

本规范适用于所有 C++ 项目的代码生成和代码审查。无论是新写文件还是修改现有文件，均应遵循以下约定，以确保代码风格统一、可读性强、易于维护。
未标注的代码规则按照常见的 SonalLint 规则检查

---

## 一、文件结构

### 1.1 文件头注释

每个源文件/头文件应以 Doxygen 风格的文件头注释开头：

```cpp
/**
 * @file   filename.hpp
 * @brief  一句话描述文件用途
 * @detail 详细描述（可选，多行）
 * @author 作者名
 * @date   年月
 * @copyright Copyright (c) 年份 作者名, All Rights Reserved.
 */
```

### 1.2 包含顺序

- 先包含必要的标准库头文件
- 再包含项目内部头文件
- 检查是否有未使用的头文件，避免不必要的依赖

示例：
```cpp
#pragma once

#include <string>
#include <vector>
// ...

#include "project/a.hpp"
#include "project/b.hpp"
```

### 1.3 命名空间

所有代码置于项目的专属命名空间中（以实际项目命名空间为准）：

```cpp
namespace project_namespace {
// 所有代码
} // namespace project_namespace
```

---

## 二、注释风格

### 2.1 类/结构体注释

```cpp
/**
 * @brief 简短描述。
 *
 * 详细描述（可选，多行）
 */
class Foo {
```

### 2.2 成员变量注释

同类成员变量对齐，`//<` 尽量对齐（可用 Tab）：

```cpp
	std::vector<Token> m_tokens; //< 词法分析后的 token 序列
	size_t m_pos    = 0;         //< 当前解析位置
	int    m_lineno = 0;         //< 当前行号
```

### 2.3 枚举值注释

同成员变量

```cpp
	enum class State {
		STATE_A, //< 状态 A 描述
		STATE_B, //< 状态 B 描述
	};
```

### 2.4 函数注释

**标准格式（无参数）：**
```cpp
/**
 * @brief 描述
 *
 * @return std::unique_ptr<Expr> - 解析得到的 AST 节点
 */
```

**有参数：**
```cpp
/**
 * @brief 描述
 *
 * @param name   - 描述
 * @param result - 描述
 * @return std::unique_ptr<Expr> - 解析得到的 AST 节点
 */
```

**void 返回：**
```cpp
/**
 * @brief 描述
 *
 * @param node - 目标节点
 */
```

**有异常：**
```cpp
/**
 * @brief 描述
 *
 * @param src - 描述
 * @return 描述
 * @throws 描述
 */
```

### 2.5 内联代码注释

用 `//` 开头，描述代码逻辑：
```cpp
// 循环主体，执行渲染循环
while (true) {
```

内联注释：
```cpp
consume();  // xxx
```

### 2.6 节分隔符

使用注释行分隔不同功能区域：
```cpp
//==================== Expression ========================
//==================== Function ========================
//==================== Constuctor ========================
```

```cpp
private: // Tool functions for parsing
```

---

## 三、代码风格

### 3.1 缩进与括号

- 使用 **Tab** 缩进，格数默认 4
- 左大括号与函数/语句同行
- `else` 另起一行：
- 对于 if、while、for、switch、case、default 等语句，必须存在对应"{}"代码块，常规情况至少要占三行

```cpp
if (cond) {
	// ...
}
else if (cond2) {
	// ...
}
else {
	// ...
}

```

```cpp
switch() {
	case 1: {
		return Type::One;
	},
	case 2: {
		return Type::Two;
	}
	default: { // 默认必须要有default
		return Type::Zero;
	}
}
```

### 3.2 命名约定

| 类型 | 风格 | 示例 |
|------|------|------|
| 类/结构体 | PascalCase | `Parser`, `ParseError` |
| 函数/方法 | snake_case | `parse_expr()`, `parse_header()` |
| 成员变量 | m_ 前缀 + snake_case | `m_tokens`, `m_pos` |
| 枚举值 | UPPER_SNAKE_CASE | `STATE_A`, `STATE_B` |
| 局部变量 | snake_case | `rule_indent`, `raw_line` |
| 全局常量 | g_ 前缀 | `g_passed`, `g_failed` |

### 3.3 返回类型

长函数签名将返回类型单独一行：

```cpp
static bool
parse(const std::string& src, std::vector<Rule>& out_rules)
```

### 3.4 using 声明

为简化类型名称，可使用 `using`：

```cpp
using Token = Lexer::Token;
using enum Lexer::TokenKind; // C++20
```

### 3.5 结构化绑定

推荐使用
```cpp
auto [matched, pos] = starts_with_seg(up, { "KEYWORD1", "KEYWORD2" });
```

---

## 四、禁止事项


---

## 五、审查要点

在代码审查时，重点检查以下方面：

- [ ] 文件头注释是否完整、准确
- [ ] 包含顺序是否合理，有无冗余
- [ ] 命名是否符合约定
- [ ] 注释是否与代码一致
- [ ] 缩进、括号、空格是否符合规范
- [ ] 是否有良好的资源管理情况
- [ ] 是否遵循禁止事项

---

## 六、生成代码时的应用

在生成新代码时，应自动应用本规范：

1. 自动生成文件头注释（填充作者、日期等信息）
2. 使用正确的命名约定
3. 生成合适的注释骨架（类、函数、成员变量）
4. 保持一致的缩进和括号风格

---

**本规范适用于所有 C++ 项目的代码生成和审查，可根据项目具体需求进行微调。**