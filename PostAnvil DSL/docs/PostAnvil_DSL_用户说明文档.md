# PostAnvil DSL 用户说明文档

> 版本：1.0 | 更新日期：2026-06-27

---

## 1. 简介

PostAnvil 是一个用于**目标检测结果后处理**的领域特定语言（DSL）。它允许你编写规则来筛选和过滤检测到的目标实例，基于实例的属性、空间关系以及逻辑条件来决定保留哪些检测结果。

### 典型使用场景

- 过滤低置信度的检测结果
- 基于空间关系筛选目标（如 A 包含 B）
- 组合多个条件进行复杂筛选

---

## 2. 快速开始

### 2.1 基本语法

```
RULE FOR <目标类别>:
    <条件1>
    <条件2>
    ...
```

- 规则以 `RULE FOR` 开头，后跟目标类别名（或 `GLOBAL`），以冒号结尾
- 条件写在缩进块中，每行一个条件
- 同一规则内的所有条件为 **AND（与）** 关系

### 2.2 第一个规则

```
RULE FOR GLOBAL:
    self.conf > 0.5
```

这个规则表示：**对于所有类别的实例，置信度必须大于 0.5 才保留。**

### 2.3 完整示例

```
RULE FOR GLOBAL:
    self.conf > 0.7

RULE FOR Person:
    self.width > 20
    CONTAINS Face 1

RULE FOR Car:
    self.width > 50
    OVERLAP Road
```

这个示例中：
- 全局规则：所有实例置信度 > 0.7
- Person 规则：宽度 > 20 且包含恰好 1 个 Face
- Car 规则：宽度 > 50 且与 Road 重叠

---

## 3. 规则结构

### 3.1 GLOBAL 规则

目标类别为 `GLOBAL` 的规则对**所有类别**的实例生效。

```
RULE FOR GLOBAL:
    self.conf > 0.5
    self.area > 100
```

### 3.2 类别规则

目标类别为具体类别的规则仅对**该类**的实例生效。

```
RULE FOR Dog:
    self.width > 30
    self.height > 30
```

### 3.3 注释

支持行注释，以 `#` 或 `//` 开头：

```
RULE FOR GLOBAL:
    # 过滤低置信度
    self.conf > 0.5

RULE FOR Cat:
    // 要求猫的尺寸足够大
    self.width > 20
```

---

## 4. 条件表达式

### 4.1 属性访问

使用 `对象.属性` 语法访问属性：

| 对象 | 说明 | 示例 |
|------|------|------|
| `self` | 当前评估的实例 | `self.conf`, `self.width`, `self.center_x` |
| `image` | 图像尺寸 | `image.width`, `image.height` |
| `<类名>` | 该类别的第一个实例 | `Person.center_x`, `Car.width` |

#### 实例属性列表

| 属性 | 类型 | 说明 |
|------|------|------|
| `x` | 数值 | 边界框左上角 x 坐标 |
| `y` | 数值 | 边界框左上角 y 坐标 |
| `width` | 数值 | 边界框宽度 |
| `height` | 数值 | 边界框高度 |
| `right` | 数值 | 右边界 x 坐标（x + width） |
| `bottom` | 数值 | 下边界 y 坐标（y + height） |
| `center_x` | 数值 | 中心点 x 坐标 |
| `center_y` | 数值 | 中心点 y 坐标 |
| `area` | 数值 | 边界框面积（width × height） |
| `aspect_ratio` | 数值 | 宽高比（width / height） |
| `conf` | 数值 | 置信度（0.0 ~ 1.0） |
| `confidence` | 数值 | 置信度（同 conf） |

#### 图像属性

| 属性 | 类型 | 说明 |
|------|------|------|
| `image.width` | 数值 | 图像宽度（像素） |
| `image.height` | 数值 | 图像高度（像素） |

### 4.2 比较运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `>` | 大于 | `self.conf > 0.5` |
| `<` | 小于 | `self.width < 100` |
| `>=` | 大于等于 | `self.area >= 500` |
| `<=` | 小于等于 | `self.x <= 10` |
| `==` | 等于 | `self.width == 30` |
| `!=` | 不等于 | `self.conf != 0` |

### 4.3 算术运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `+` | 加法 | `self.x + self.width > 100` |
| `-` | 减法 | `self.right - self.x > 50` |
| `*` | 乘法 | `self.width * self.height > 1000` |
| `-` | 一元取负 | `-self.x > -10` |

> **注意**：运算符优先级为 `*` > `+` / `-` > 比较运算符。

### 4.4 逻辑运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `AND` | 逻辑与 | `self.conf > 0.5 AND self.width > 20` |
| `OR` | 逻辑或 | `self.width > 100 OR self.height > 100` |
| `NOT` | 逻辑非 | `NOT self.conf < 0.3` |

> **注意**：同一规则内的多个条件行**默认是 AND 关系**。如需 OR 逻辑，请在单行内使用 `OR` 运算符。

### 4.5 括号

使用括号 `()` 控制运算优先级：

```
(self.width > 100 OR self.height > 100) AND self.conf > 0.5
```

---

## 5. 空间谓词

空间谓词用于表达实例之间的空间关系。谓词名称**不区分大小写**。

### 5.1 CONTAINS — 包含

检查当前实例是否包含指定类别的实例。

```
CONTAINS <类名> [数量]
CONTAINS <类名> <最小数量>-<最大数量>
```

| 形式 | 语义 |
|------|------|
| `CONTAINS B` | 包含至少 1 个 B |
| `CONTAINS B 1` | 精确包含 1 个 B |
| `CONTAINS B 3` | 精确包含 3 个 B |
| `CONTAINS B 0-2` | 包含 0~2 个 B |
| `CONTAINS B 2-5` | 包含 2~5 个 B |

**包含的判断标准**：目标实例的边界框完全在当前实例的边界框内。

```
RULE FOR Room:
    CONTAINS Chair 2-10
    CONTAINS Table 1
```

### 5.2 INSIDE — 被包含

检查当前实例是否在指定类别的实例内部。

```
INSIDE <类名>
```

**判断标准**：当前实例的边界框完全在目标实例的边界框内。

```
RULE FOR Eye:
    INSIDE Face
```

### 5.3 OVERLAP — 重叠

检查当前实例是否与指定类别的实例重叠（IoU > 0）。

```
OVERLAP <类名>
```

```
RULE FOR Person:
    OVERLAP Sidewalk
```

### 5.4 CLOSE_TO — 靠近

检查当前实例的中心点与指定类别实例的中心点距离是否在阈值内。

```
CLOSE_TO <类名> <距离阈值>
```

**距离**：欧几里得距离（基于中心点坐标）。

```
RULE FOR Person:
    CLOSE_TO Car 50
```

---

## 6. 内置函数

### 6.1 abs(x) — 绝对值

返回参数的绝对值。

```
abs(self.x - self.center_x) < 10
```

### 6.2 iou(self, other) — 交并比

计算当前实例与指定类别第一个实例的 IoU（Intersection over Union）。

```
iou(self, B) > 0.5
```

返回值范围：`[0.0, 1.0]`。

---

## 7. 完整语法参考

### 7.1 表达式语法（BNF 风格）

```
expr      := or_expr
or_expr   := and_expr ("OR" and_expr)*
and_expr  := not_expr ("AND" not_expr)*
not_expr  := "NOT" not_expr | cmp_expr
cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
add_expr  := mul_expr ( ("+"|"-") mul_expr )*
mul_expr  := unary_expr ("*" unary_expr)*
unary_expr:= ("-" | "NOT")? primary
primary   := number
           | identifier ( "." identifier )*
           | identifier "(" arg_list ")"
           | identifier predicate_args
           | "(" expr ")"
```

### 7.2 关键字

| 关键字 | 说明 |
|--------|------|
| `RULE FOR` | 规则声明头部 |
| `GLOBAL` | 全局规则目标 |
| `AND` | 逻辑与 |
| `OR` | 逻辑或 |
| `NOT` | 逻辑非 |

### 7.3 谓词列表

| 谓词 | 参数 | 说明 |
|------|------|------|
| `CONTAINS` | 类名 [, 数量/范围] | 检查是否包含指定类的实例 |
| `INSIDE` | 类名 | 检查是否在指定类实例内部 |
| `OVERLAP` | 类名 | 检查是否与指定类实例重叠 |
| `CLOSE_TO` | 类名, 距离 | 检查中心距离是否在阈值内 |

### 7.4 函数列表

| 函数 | 参数 | 说明 |
|------|------|------|
| `abs(x)` | 1 个数值参数 | 返回绝对值 |
| `iou(self, class)` | 2 个参数 | 返回与指定类第一个实例的 IoU |

---

## 8. 实战示例

### 8.1 基础过滤

```
# 过滤低置信度实例
RULE FOR GLOBAL:
    self.conf > 0.6

# 过滤太小的实例
RULE FOR GLOBAL:
    self.width > 10
    self.height > 10
```

### 8.2 空间关系过滤

```
# 人脸检测：人脸在图像内，包含眼睛
RULE FOR Face:
    self.conf > 0.8
    CONTAINS Eye 2
    self.x > 0
    self.y > 0

# 眼睛在人脸内
RULE FOR Eye:
    INSIDE Face
    self.conf > 0.5
```

### 8.3 场景理解

```
# 车辆检测
RULE FOR Car:
    self.conf > 0.7
    self.width > 50
    OVERLAP Road

# 行人检测
RULE FOR Person:
    self.conf > 0.6
    self.width > 20
    CLOSE_TO Car 100
```

### 8.4 数量约束

```
# 一个房间应该有 1-2 把椅子和 1 张桌子
RULE FOR Room:
    self.conf > 0.5
    CONTAINS Chair 1-2
    CONTAINS Table 1

# 应该有多个窗户
RULE FOR Room:
    CONTAINS Window 1-5
```

### 8.5 复杂逻辑组合

```
# 使用 OR 组合条件
RULE FOR Vehicle:
    self.conf > 0.7
    (self.width > 100 OR self.height > 80)
    (OVERLAP Road OR OVERLAP Parking)

# 使用 NOT 排除
RULE FOR Animal:
    self.conf > 0.5
    NOT INSIDE Cage
```

---

## 9. 常见问题

### Q: GLOBAL 规则和类别规则的区别？
**A:** GLOBAL 规则对所有实例生效，类别规则仅对特定类别的实例生效。一个实例必须同时满足所有 GLOBAL 规则和其自身类别的规则才会被保留。

### Q: 条件之间是 AND 还是 OR？
**A:** 同一规则内不同行的条件之间是 **AND** 关系。如需 OR，请在同一行内使用 `OR` 运算符。

### Q: 谓词名称大小写敏感吗？
**A:** 不敏感。`CONTAINS`、`contains`、`Contains` 都是等价的。

### Q: 数量范围怎么用？
**A:** 使用 `CONTAINS Class min-max` 语法。例如 `CONTAINS B 2-5` 表示包含 2 到 5 个 B。单值 `CONTAINS B 1` 表示精确匹配 1 个 B。

### Q: 类别属性访问指的是哪个实例？
**A:** 当通过类名访问属性时（如 `Person.center_x`），返回的是该类别中**第一个实例**的属性值。

---

## 10. 附录：技术架构

PostAnvil 由以下组件构成：

| 组件 | 文件 | 说明 |
|------|------|------|
| 数据结构 | `context.hpp` | Image、Instance、Scene 定义 |
| AST 节点 | `ast.hpp` | 表达式、规则、数量范围 |
| 词法分析器 | `lexer.hpp` / `lexer.cpp` | Token 拆分 |
| 解析器 | `parser.hpp` | 递归下降解析 |
| 评估器 | `evaluator.hpp` | 运行时规则评估 |