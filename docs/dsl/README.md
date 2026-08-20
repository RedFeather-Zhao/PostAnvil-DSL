# DSL 快速开始

[文档中心](../README.md) · [项目首页](../../README.md)

## 本页目录

- [项目定位](#项目定位)
- [第一个规则](#第一个规则)
- [程序结构与执行顺序](#程序结构与执行顺序)

> 适用版本：**PostAnvil 0.8.x**
> 文档更新日期：**2026-08-11**

本文档面向使用 PostAnvil 编写后处理规则，以及通过公开 C++、Python 或 Android API 执行规则的用户。
构建、安装、打包和平台支持信息请参阅项目根目录的 `README.md`。

**注意**，本文档描述的 DSL 语法正在快速迭代期，可能与未来版本不兼容；未来也不保证对旧语法的向前兼容，一切以简化实际应用场景而更改；请以实际发布版本为准。

## 项目定位

PostAnvil 是用于目标检测结果后处理的领域特定语言（DSL）。它可以按规则过滤检测实例、计算实例或类别属性、创建和扩充类别，并通过函数、条件分支与循环封装较复杂的统计逻辑。

PostAnvil 0.8.x 提供以下主要能力：

- 关键字、DSL 标识符、类别名和属性名大小写不敏感；`EXPORT ... AS` 的宿主导出名保留原始拼写。
- `FILTER`、`ATTR`、`GROUP`、`APPEND`、`SORT` 规则按书写顺序组成执行管道。
- 支持 `NUM`、`STR`、`BOOL`、`INST`、`ANY` 类型，以及全局变量、函数参数和函数局部变量。
- 函数内支持 `IF` / `ELIF` / `ELSE`、嵌套 `FOR`、局部变量声明与赋值、`RETURN`。
- 内置 `self`、`img`、类别属性和原地稳定 `SORT` 规则。
- 提供原生数学、检测框空间关系和实例查询函数，并支持稳定 `id` 与实时 `index`。
- 通过 `IMPORT` / `EXPORT` 与 C++ 或 Python 宿主交换值。

## 第一个规则

下面的程序先计算风险值，再过滤低置信度实例，最后导出剩余数量：

```postanvil
IMPORT NUM min_conf

RULE FUNC risk_level(conf: NUM) -> NUM {
    IF conf > 0.8 {
        RETURN 3
    } ELIF conf > 0.5 {
        RETURN 2
    } ELSE {
        RETURN 1
    }
}
RULE ATTR "person" {
    self.risk = risk_level(self.conf)
}
RULE FILTER "person" {
    self.conf > min_conf
    self.risk >= 2
}
EXPORT "person".count AS person_count
```

基本约定：

- 规则、函数、条件分支和循环统一使用 `{ ... }` 定义块，不使用 `XXXEND` 结束关键字。
- `{` 可以与块头写在同一行，也可以放在下一行；块头后不写冒号。
- 换行是语句分隔符。
- `FILTER`、`GROUP`、`APPEND` 中不同行条件自动按 `AND` 连接。
- 逗号分隔类别可组成临时类别组；`@ALL_CLASS` 表示全部普通类别，`ALL_INST` 是维护全部传入实例 ID 的内置类别。
- `#` 和 `//` 均可开始行注释。
- 对于较长表达式，可以使用 `\` 续行符

## 程序结构与执行顺序

顶层可以包含声明和六类规则：

| 结构 | 作用 |
|---|---|
| `IMPORT` | 从宿主场景读取变量 |
| `EXPORT` | 将表达式结果写入宿主可读取的导出项 |
| `NUM/STR/BOOL/INST/ANY name = expr` | 声明全局变量 |
| `name = expr` | 给已声明的全局变量赋值 |
| `RULE FILTER` | 过滤类别中的实例 |
| `RULE ATTR` | 设置实例属性或类别属性 |
| `RULE FUNC` | 定义自定义函数 |
| `RULE GROUP` | 从源类别选择满足条件的实例，以同一身份形成目标类别 |
| `RULE APPEND` | 将满足条件的实例身份合并到目标类别 |
| `RULE SORT` | 按一个或多个键原地稳定排序类别实例 |

声明和规则按源文件中的顺序形成算子管道。后续规则可以读取前面规则产生的属性或类别；`EXPORT` 读取的是执行到该位置时的值，因此通常放在程序末尾。

---

[文档中心](../README.md) · 下一篇：[声明与规则](language.md)
