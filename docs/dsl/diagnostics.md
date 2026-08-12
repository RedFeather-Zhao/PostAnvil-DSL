# DSL 编译诊断与常见问题

[文档中心](../README.md) · [DSL 快速开始](README.md)

## 本页目录

- [关键字](#关键字)
- [编译错误诊断](#编译错误诊断)
- [常见问题](#常见问题)

## 关键字

`RULE`、`FILTER`、`ATTR`、`FUNC`、`GROUP`、`APPEND`、`SORT`、`ASC`、`DESC`、
`FROM`、`AND`、`OR`、`NOT`、`SELF`、`NUM`、`STR`、`BOOL`、`INST`、`ANY`、
`RETURN`、`IMPORT`、`EXPORT`、`AS`、`IF`、`ELIF`、`ELSE`、`FOR`、`IN`、
`TRUE`、`FALSE`。

## 编译错误诊断

`Compiler::compile()` 遇到词法、语法或语义错误时会抛出 `PACompileError`。错误文本默认包含
错误阶段、从 1 开始的行列号、对应源码行、插入符以及可执行的修复提示。例如，把 `OR`
单独放到下一行会得到类似输出：

```text
PostAnvil syntax error at line 3, column 5:
  3 |     OR self.area > 10
    |     ^
Logical operator 'OR' cannot start a new statement.
help: Move the operator to the previous line, or end the previous line with '\' to continue the expression.
```

首个诊断会展示源码行和插入符；若解析器同时发现其他问题，后续诊断只提供简化说明。由于
后续错误可能是首个错误触发的连锁结果，应先修复第一处再重新编译。ANTLR 内部的原始 token
信息不会写入面向用户的 `what()` 文本，因此不会再出现冗长的 `expecting {...}` 列表。

C++ 宿主可以捕获 `PACompileError` 并读取结构化字段：

```cpp
try {
    auto program = postanvil::Compiler{}.compile(source);
}
catch (const postanvil::PACompileError& error) {
    std::cerr << error.what() << '\n';
    auto stage = error.kind();       // Syntax / Semantic / Internal
    int line = error.line();         // 从 1 开始，未知时为 -1
    int column = error.column();     // 从 1 开始，未知时为 -1
    if (error.has_source_line()) {
        auto source_line = error.source_line();
    }
    auto hint = error.hint();
    auto parser_detail = error.raw_message(); // 仅供诊断工具使用
}
```

Python API 与 C++ 使用相同的异常名称。捕获 `postanvil.PACompileError` 后，
`str(error)` 返回同样的人类可读文本；`kind`、`message`、`line`、`column`、
`source_line`、`hint` 和 `raw_message` 是属性，其中 `kind` 使用
`postanvil.CompileErrorKind`。C++ 的 `raw_message()` 和 Python 的 `raw_message` 面向
CLI、编辑器集成和编译器维护者，不建议直接展示给普通用户。

## 常见问题

**如何删除某类别的全部实例？**

```postanvil
RULE FILTER "person" {
    FALSE
}
```

**多行条件是 AND 还是 OR？**

`FILTER`、`GROUP`、`APPEND` 的多行条件自动按 `AND` 连接；需要 `OR` 时在表达式内明确写出。

**`self` 和 `img` 需要导入吗？**

不需要，它们是内置对象。

**函数中能使用 `self` 吗？**

函数从实例规则调用时可访问当前 `self`。做聚合计算时更推荐显式传参或通过 `FOR` 的循环变量访问实例，以避免脱离实例上下文调用时发生错误。

**如何在分数并列时仍精确保留 N 个实例？**

先使用 `RULE SORT` 排序，再用 `RULE FILTER` 保留 `self.index <= N`。稳定排序会维持完全同键实例原有顺序；也可以增加 `self.id ASC` 作为最终确定性排序键。

**控制流能写在 ATTR 或 FILTER 里吗？**

不能。`IF` 和 `FOR` 是函数语句；把逻辑封装在 `FUNC` 中，再由规则调用。

---

本手册描述 PostAnvil 0.8.x 的公开行为。若文档与具体补丁版本存在差异，请以该发布版本的
`grammar/PostAnvil.g4`、公开头文件、Python 绑定和测试结果为准；内部头文件和实现细节不属于
兼容性承诺。

---

上一篇：[属性、内置函数与排序](reference.md) · [返回文档中心](../README.md)
