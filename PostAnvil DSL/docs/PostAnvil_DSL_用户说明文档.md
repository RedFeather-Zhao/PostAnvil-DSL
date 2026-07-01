# PostAnvil DSL 用户说明文档

> 版本：2.0 | 更新日期：2026-07-01

---

## 1. 简介

PostAnvil 是一个用于**目标检测结果后处理**的领域特定语言（DSL）。它允许你编写规则来筛选和过滤检测到的目标实例，以及为实例添加计算属性，基于实例的属性、表达式计算来决定保留哪些检测结果。

### 核心特性

- **大小写不敏感**：所有关键字、标识符、属性名均不区分大小写
- **过滤规则**：按条件筛选实例
- **属性规则**：为实例计算并添加自定义属性
- **管道执行**：属性规则和过滤规则按序执行，后续规则可引用前置规则计算的属性

### 典型使用场景

- 过滤低置信度的检测结果
- 基于空间关系筛选目标
- 为实例添加计算属性（如密度、风险评分等）
- 组合多个条件进行复杂筛选

---

## 2. 快速开始

### 2.1 基本语法

**过滤规则**：
```
RULE FILTER <目标类别>:
    <条件1>
    <条件2>
    ...
```

**属性规则**：
```
RULE ATTR <目标类别>:
    <属性名> = <表达式>
    ...
```

- 过滤规则以 `RULE FILTER` 开头，后跟目标类别名（或 `GLOBAL`），以冒号结尾
- 属性规则以 `RULE ATTR` 开头，后跟目标类别名（或 `GLOBAL`），以冒号结尾
- 条件/赋值写在缩进块中，每行一个
- 同一过滤规则内的所有条件为 **AND（与）** 关系

### 2.2 第一个规则

```
RULE FILTER GLOBAL:
    self.conf > 0.5
```

这个规则表示：**对于所有类别的实例，置信度必须大于 0.5 才保留。**

### 2.3 属性计算示例

```
RULE ATTR Person:
    density = self.conf / (self.w * self.h)
    risk = self.conf * 2.0

RULE FILTER Person:
    self.density < 0.5
    self.risk > 1.0
```

这个示例中：
- 先为每个 Person 实例计算 density 和 risk 属性
- 再过滤：只保留 density < 0.5 且 risk > 1.0 的实例

### 2.4 完整示例

```
RULE FILTER GLOBAL:
    self.conf > 0.7

RULE FILTER Person:
    self.w > 20
    self.h > 30

RULE FILTER Car:
    self.w > 50
    self.area > 2000
```

这个示例中：
- 全局规则：所有实例置信度 > 0.7
- Person 规则：宽度 > 20 且高度 > 30
- Car 规则：宽度 > 50 且面积 > 2000

---

## 3. 规则结构

### 3.1 RULE FILTER（过滤规则）

```
RULE FILTER <target>:
    <条件表达式>
```

- `target` 为 `GLOBAL` 时对所有类别生效
- `target` 为具体类别名时仅对该类生效
- 条件表达式每行一个，所有条件为 AND 关系

### 3.2 RULE ATTR（属性规则）

```
RULE ATTR <target>:
    <属性名> = <数值表达式>
```

- `target` 为 `GLOBAL` 时对所有类别生效
- 属性名由用户自定义，可包含字母、数字和下划线
- 数值表达式支持算术运算、属性访问等
- 计算后的属性存储在实例中，后续 RULE FILTER 可通过 `self.<属性名>` 引用

### 3.3 GLOBAL 规则

目标类别为 `GLOBAL` 的规则对**所有类别**的实例生效。

```
RULE FILTER GLOBAL:
    self.conf > 0.5
    self.area > 100
```

### 3.4 注释

支持行注释，以 `#` 或 `//` 开头：

```
RULE FILTER GLOBAL:
    # 过滤低置信度
    self.conf > 0.5

RULE FILTER Cat:
    // 要求猫的尺寸足够大
    self.w > 20
```

---

## 4. 条件表达式

### 4.1 属性访问

使用 `对象.属性` 语法访问属性：

| 对象 | 说明 | 示例 |
|------|------|------|
| `self` | 当前评估的实例 | `self.conf`, `self.w`, `self.cx` |
| `image` | 图像尺寸 | `image.width`, `image.height` |

#### 实例属性列表

| 属性 | 类型 | 说明 |
|------|------|------|
| `x1` | 数值 | 边界框左上角 x 坐标 |
| `y1` | 数值 | 边界框左上角 y 坐标 |
| `w` | 数值 | 边界框宽度 |
| `h` | 数值 | 边界框高度 |
| `x2` | 数值 | 右下角 x 坐标（x1 + w） |
| `y2` | 数值 | 右下角 y 坐标（y1 + h） |
| `cx` | 数值 | 中心点 x 坐标（x1 + w/2） |
| `cy` | 数值 | 中心点 y 坐标（y1 + h/2） |
| `area` | 数值 | 边界框面积（w × h） |
| `aspect` | 数值 | 宽高比（w / h） |
| `conf` | 数值 | 置信度（0.0 ~ 1.0） |

#### 图像属性

| 属性 | 类型 | 说明 |
|------|------|------|
| `image.width` | 数值 | 图像宽度（像素） |
| `image.height` | 数值 | 图像高度（像素） |

#### 动态属性

通过 `RULE ATTR` 规则计算的自定义属性，同样可通过 `self.<属性名>` 访问。

### 4.2 比较运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `>` | 大于 | `self.conf > 0.5` |
| `<` | 小于 | `self.w < 100` |
| `>=` | 大于等于 | `self.area >= 500` |
| `<=` | 小于等于 | `self.x1 <= 10` |
| `==` | 等于 | `self.w == 30` |
| `!=` | 不等于 | `self.conf != 0` |

### 4.3 算术运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `+` | 加法 | `self.x1 + self.w > 100` |
| `-` | 减法 | `self.x2 - self.x1 > 50` |
| `*` | 乘法 | `self.w * self.h > 1000` |
| `/` | 除法 | `self.conf / self.area < 0.01` |
| `-` | 一元取负 | `-self.x1 > -10` |

> **注意**：运算符优先级为 `*` / `/` > `+` / `-` > 比较运算符。除数为 0 时除法结果为 0。

### 4.4 逻辑运算符

| 运算符 | 说明 | 示例 |
|--------|------|------|
| `AND` | 逻辑与 | `self.conf > 0.5 AND self.w > 20` |
| `OR` | 逻辑或 | `self.w > 100 OR self.h > 100` |
| `NOT` | 逻辑非 | `NOT self.conf < 0.3` |

> **注意**：同一规则内的多个条件行**默认是 AND 关系**。如需 OR 逻辑，请在单行内使用 `OR` 运算符。

### 4.5 括号

使用括号 `()` 控制运算优先级：

```
(self.w > 100 OR self.h > 100) AND self.conf > 0.5
```

---

## 5. 属性规则详解

### 5.1 基本语法

```
RULE ATTR <类别名>:
    <属性名> = <表达式>
```

属性规则为指定类别的每个实例计算一个属性值，结果存储在实例中，供后续过滤规则使用。

### 5.2 表达式支持

属性值表达式支持所有数值运算：

```
RULE ATTR Person:
    density = self.area / (self.w * self.h)
    score = self.conf * 100.0
    cx_norm = self.cx / image.width
    cy_norm = self.cy / image.height
```

### 5.3 全局属性

```
RULE ATTR GLOBAL:
    area_calc = self.w * self.h
```

为所有类别的所有实例计算 `area_calc` 属性。

### 5.4 属性引用

属性规则按顺序执行，后续的过滤规则可以直接引用属性规则计算的结果：

```
RULE ATTR Person:
    risk = self.conf * 2.0

RULE FILTER Person:
    self.risk > 1.0
    self.w > 20
```

---

## 6. 完整语法参考

### 6.1 表达式语法（BNF 风格）

```
expr      := or_expr
or_expr   := and_expr ("OR" and_expr)*
and_expr  := not_expr ("AND" not_expr)*
not_expr  := "NOT" not_expr | cmp_expr
cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
add_expr  := mul_expr ( ("+"|"-") mul_expr )*
mul_expr  := unary_expr ( ("*"|"/") unary_expr )*
unary_expr:= ("-" | "NOT")? primary
primary   := number
           | identifier ( "." identifier )*
           | identifier "(" arg_list ")"
           | "(" expr ")"

attr_assign := identifier "=" expr
```

### 6.2 关键字

| 关键字 | 说明 |
|--------|------|
| `RULE FILTER` | 过滤规则声明头部 |
| `RULE ATTR` | 属性规则声明头部 |
| `GLOBAL` | 全局规则目标 |
| `AND` | 逻辑与 |
| `OR` | 逻辑或 |
| `NOT` | 逻辑非 |

### 6.3 大小写不敏感

所有关键字、标识符、属性名均**不区分大小写**。以下写法等价：

```
self.conf > 0.5
SELF.CONF > 0.5
Self.Conf > 0.5
RULE FILTER GLOBAL:
rule filter global:
```

---

## 7. 实战示例

### 7.1 基础过滤

```
# 过滤低置信度实例
RULE FILTER GLOBAL:
    self.conf > 0.6

# 过滤太小的实例
RULE FILTER GLOBAL:
    self.w > 10
    self.h > 10
```

### 7.2 属性计算 + 过滤

```
# 计算密度，然后过滤低密度实例
RULE ATTR Person:
    density = self.conf / self.area

RULE FILTER Person:
    self.density < 0.01
    self.w > 20
    self.conf > 0.5
```

### 7.3 边界检查

```
# 确保实例在图像内
RULE FILTER Face:
    self.conf > 0.8
    self.x1 > 0
    self.y1 > 0
    self.x1 + self.w <= image.width
    self.y1 + self.h <= image.height
```

### 7.4 归一化坐标过滤

```
# 使用中心点归一化坐标
RULE ATTR Person:
    cx_norm = self.cx / image.width
    cy_norm = self.cy / image.height

RULE FILTER Person:
    self.cx_norm > 0.2
    self.cx_norm < 0.8
    self.cy_norm > 0.1
    self.cy_norm < 0.9
```

### 7.5 复杂逻辑组合

```
# 使用 OR 组合条件
RULE FILTER Vehicle:
    self.conf > 0.7
    (self.w > 100 OR self.h > 80)
    self.area > 2000

# 使用 NOT 排除
RULE ATTR Animal:
    size_score = self.w * self.h * self.conf

RULE FILTER Animal:
    self.conf > 0.5
    NOT self.size_score < 100
```

### 7.6 多类别组合

```
RULE FILTER GLOBAL:
    self.conf > 0.5

RULE ATTR Person:
    body_area = self.w * self.h

RULE FILTER Person:
    self.body_area > 500
    self.w > 20

RULE FILTER Vehicle:
    self.w > 100
    self.area > 3000
```

---

## 8. 常见问题

### Q: GLOBAL 规则和类别规则的区别？
**A:** GLOBAL 规则对所有实例生效，类别规则仅对特定类别的实例生效。一个实例必须同时满足所有 GLOBAL 规则和其自身类别的规则才会被保留。

### Q: 条件之间是 AND 还是 OR？
**A:** 同一规则内不同行的条件之间是 **AND** 关系。如需 OR，请在同一行内使用 `OR` 运算符。

### Q: 大小写敏感吗？
**A:** 不敏感。所有关键字、属性名、标识符均不区分大小写。`self.conf`、`SELF.CONF`、`Self.Conf` 都是等价的。

### Q: RULE ATTR 和 RULE FILTER 的执行顺序？
**A:** 按源代码中出现的顺序依次执行。先出现的 RULE ATTR 计算的属性，后续的 RULE FILTER 可以直接引用。

### Q: 属性规则可以覆盖内置属性吗？
**A:** 不建议覆盖内置属性（如 x1, w, conf 等）。自定义属性应使用不同的名称。

### Q: 动态属性支持哪些运算？
**A:** 支持所有数值运算：算术（+、-、*）、比较、逻辑运算，以及内置属性和图像属性的访问。

---