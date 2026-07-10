# PostAnvil DSL 用户说明文档

> 版本：**0.4** | 更新日期：**2026-07-08**

---

## 1. 简介

PostAnvil 是一个用于**目标检测结果后处理**的领域特定语言（DSL）。它允许你编写规则来筛选、过滤检测到的目标实例，为实例添加计算属性，创建新的类别子集，以及通过自定义函数封装复杂逻辑。

### 核心特性

- **大小写不敏感**：所有关键字、标识符、属性名均不区分大小写，导出到宿主语言的变量名例外，保留原始语言的大小写。
- **过滤规则**：按条件列表逐实例筛选
- **属性规则**：定义实例属性或整个类别的聚合属性
- **自定义函数**（**支持不完善**）：当前仅支持单表达式函数体，控制流和局部变量暂未实现
- **类别操作**：创建新类别（`GROUP`）、向已有类别追加实例（`APPEND`）
- **内置全局对象**：`self` 表示当前实例，`img` 提供图像尺寸，无需声明
- **排序原语**：`SORT` 可获取指定类别中按某键值排序后的第 N 名键值
- **管道执行**：规则按书写顺序执行，后续规则可引用之前规则计算的结果

### 典型使用场景

- 过滤低置信度的检测结果
- 基于空间关系筛选目标
- 为实例添加计算属性（如密度、风险评分等）
- 将高置信度实例组合成新类别
- 保留每个类别中面积最大 / 最小的前 N 个实例
- 编写可复用的简单统计函数（当前仅支持单一表达式）

### 不适宜场景

---

## 2. 实现状态（v0.4 重要说明）

当前编译器（v0.4）的**功能支持情况**如下：

| 功能模块                     | 实现状态               | 备注                                                                 |
|-----------------------------|------------------------|----------------------------------------------------------------------|
| `FILTER` 规则                | ✅ 完整支持             | 支持多行 AND，行内 OR/NOT，支持全局过滤（目标为 `"global"`）         |
| `ATTR` 规则                  | ✅ 完整支持             | 支持实例属性和类别属性                                               |
| `GROUP` / `APPEND` 规则      | ✅ 完整支持             | 支持多条件筛选                                                       |
| 基本表达式（算术、比较、逻辑   | ✅ 完整支持             | 支持 NUM/STR/BOOL 类型，STR 仅支持 `==` / `!=`                      |
| 属性访问（`self.*`）          | ✅ 完整支持             | 内置属性及自定义动态属性                                             |
| 属性访问（`"class".*`）       | ✅ 完整支持             | 包括内置 `COUNT` 和自定义类别属性                                    |
| 属性访问（`img.*`）           | ✅ 完整支持             | `w`、`h`、`area`、`aspect`                                           |
| 全局变量和导入/导出            | ✅ 完整支持             | `IMPORT`、`EXPORT`、顶层 `NUM/STR/BOOL` 变量定义                    |
| 自定义函数 `FUNC`             | ⚠️ **部分支持**         | **仅支持单表达式函数体**（如 `RETURN expr` 或直接写表达式）          |
| 函数内的 `IF-ELSE` 分支       | ❌ 未实现               | 语法已定义，编译器暂不处理                                           |
| 函数内的 `FOR` 循环           | ❌ 未实现               | 语法已定义，编译器暂不处理                                           |
| 函数内的局部变量定义及赋值      | ❌ 未实现               | 语法已定义，编译器暂不处理                                           |
| `FOR` 循环变量属性访问         | ❌ 未实现               | `inst.xxx` 暂不生效                                                  |
| `SORT` 原语                   | ✅ 完整支持             | 返回第 N 名的排序键值                                                |
| `self.x = 10` 修改可变内置属性 | ✅ 已实现              | 修改实例的内置属性                                               |
> **重要**：v0.4 版本中，**自定义函数（`FUNC`）仅支持单表达式返回**，所有控制流、循环、局部变量均不可用。未来版本将逐步补全这些功能。

---

## 3. 快速开始

### 3.1 基本语法

PostAnvil 程序由**声明部分**和**规则部分**组成。声明（导入、导出、全局变量）通常写在前面，规则部分由多个 `RULE ... RULEEND` 块构成。

**过滤规则**：
```
RULE FILTER "person":
    self.conf > 0.5
    self.w > 20
RULEEND
```

**属性规则**：
```
RULE ATTR "car":
    self.area = self.w * self.h
    "car".avg_conf = 0.8
RULEEND
```

**自定义函数（仅单表达式）**：
```
RULE FUNC is_big(area: NUM) -> BOOL:
    area > 1000
RULEEND
```

- 规则块以 `RULE` 开头，`RULEEND` 结尾
- `RULE FILTER` 目标必须为字符串字面量（如 `"person"`）或字符串变量
- 同一个过滤规则内的多行条件为 **AND（与）** 关系

### 3.2 第一个规则

```
RULE FILTER "cat":
    self.conf > 0.5
RULEEND
```

这个规则表示：**对于 "cat" 类别的实例，置信度必须大于 0.5 才保留**。

### 3.3 属性计算示例

```
RULE ATTR "person":
    self.risk = self.conf * 2.0
RULEEND

RULE FILTER "person":
    self.risk > 1.0
RULEEND
```

- 先为每个 person 实例计算 `risk` 属性
- 再过滤：只保留 `risk > 1.0` 的实例

### 3.4 完整示例

```
# 全局过滤（所有类别）
RULE FILTER "global":
    self.conf > 0.7
RULEEND

# 特定类别过滤
RULE FILTER "person":
    self.w > 20
    self.h > 30
RULEEND

RULE FILTER "car":
    self.w > 50
    self.area > 2000
RULEEND
```

---

## 4. 程序结构

### 4.1 声明部分

声明部分在规则之前书写（非强制，但推荐），包括：

#### 导入宿主变量（`IMPORT`）

从宿主程序（C++）中导入只读变量，可重命名

```
IMPORT NUM minConf
IMPORT STR targetClass AS cls
IMPORT NUM a, BOOL b, STR c AS d
```

#### 导出结果（`EXPORT`）

将表达式的值写回宿主程序

```
EXPORT "person".count AS totalPerson
EXPORT avg_conf("car") AS carAvgConf
```

#### 全局变量

在顶层定义的数值、字符串、布尔变量，在整个程序中可用

```
NUM threshold = 0.7
STR target = "person"
BOOL debug = FALSE
```

### 4.2 规则部分

按书写顺序执行的规则块，支持以下五种：

- `RULE FILTER`：逐实例过滤
- `RULE ATTR`：定义实例或类别属性
- `RULE FUNC`：自定义函数（**当前仅支持单表达式**）
- `RULE GROUP`：创建新类别（从已有类别中选择实例）
- `RULE APPEND`：将实例追加到目标类别

### 4.3 注释

行注释，以 `#` 或 `//` 开头：

```
RULE FILTER "person":
    # 过滤低置信度
    self.conf > 0.5
RULEEND
```

---

## 5. 规则详解

### 5.1 `RULE FILTER`（过滤规则）

```
RULE FILTER <class_expr>:
    <布尔表达式>
    ...
RULEEND
```

- `<class_expr>` 可以是字符串字面量（如 `"person"`）或字符串变量
- 每行必须为一个布尔表达式，**行间自动为 AND 关系**，行内可使用 `AND`/`OR`/`NOT` 自由组合
- **不允许在 FILTER 内部进行任何赋值**

#### 示例

```
RULE FILTER "person":
    self.conf > 0.7
    (self.w > 100 OR self.h > 100)
    NOT (self.area < 500)
RULEEND
```

### 5.2 `RULE ATTR`（属性规则）

```
RULE ATTR <class_expr>:
    self.<属性名> = <表达式>            # 实例属性
    "<类别名>".<属性名> = <表达式>      # 类型属性
RULEEND
```

- 实例属性：每个实例拥有独立值
- 类型属性：属于整个类别，所有实例共享，通常用于存储聚合结果
- **只能在 ATTR 中定义新属性**，其它地方只能读取或修改已存在的变量

#### 示例

```
RULE ATTR "car":
    self.density = self.area / img.area
    "car".avg_conf = 0.85
RULEEND
```

### 5.3 `RULE FUNC`（自定义函数）— **当前限制**

```
RULE FUNC <函数名>( <参数>:<类型>, ... ) [-> <返回类型>]:
    <单个表达式> 或 RETURN <表达式>
RULEEND
```

- 支持参数类型标注（`NUM`、`STR`、`BOOL`）
- 返回类型可选；若不写，函数体表达式的类型即为返回类型
- **当前版本不支持**：
  - 局部变量定义
  - 变量赋值
  - `IF-ELSE` 分支
  - `FOR` 循环
  - 多条语句（除 `RETURN` 外）
- 函数调用统一为 `函数名(实参, ...)`

#### 示例（合法）

```
RULE FUNC is_large(w:NUM, h:NUM) -> BOOL:
    (w * h) > 1000
RULEEND

RULE FUNC square(x:NUM) -> NUM:
    RETURN x * x
RULEEND
```

#### 示例（非法，当前不支持）

```
RULE FUNC bad_func() -> NUM:
    NUM tmp = 0
    FOR obj IN "person"
        tmp = tmp + obj.conf
    ENDFOR
    RETURN tmp
RULEEND
```
此写法在当前版本中**无法编译通过**，将导致 `CompileError`。

### 5.4 `RULE GROUP`（创建新类别）

```
RULE GROUP "<新类别名>" FROM <class_expr>:
    <布尔表达式>
    ...
RULEEND
```

- 从源类别中挑选满足所有条件的实例，组成一个全新的类别
- 新类别名必须为字符串字面量
- 源类别实例不受影响

#### 示例

```
RULE GROUP "large_car" FROM "car":
    self.area > 5000
RULEEND
```

### 5.5 `RULE APPEND`（追加实例）

```
RULE APPEND <目标class_expr> FROM <源class_expr>:
    <布尔表达式>
    ...
RULEEND
```

- 将源类别中满足条件的实例追加到目标类别中
- 若目标类别不存在则自动创建

#### 示例

```
RULE APPEND "vip" FROM "person":
    self.conf > 0.95
RULEEND
```

---

## 6. 表达式与运算符

### 6.1 原子表达式

| 形式 | 说明 | 示例 |
|------|------|------|
| 数值字面量 | 整数或小数 | `100`, `0.5`, `.8` |
| 字符串字面量 | 双引号包围 | `"person"`, `"hello"` |
| 布尔字面量 | `TRUE` / `FALSE` | `TRUE` |
| 属性访问 | `self.` 或 `"类别".` 或循环变量 | `self.conf`, `"car".count` |
| 函数调用 | `函数名(参数,...)` | `is_large(self.w, self.h)` |
| 排序原语 | `SORT(类别, 排序键, 名次)` | `SORT("person", self.conf, 3)` |
| 括号 | 改变优先级 | `(self.w + self.h) > 200` |

> **注意**：循环变量属性访问（如 `inst.w`）在 v0.4 中**未实现**，请勿在 `FOR` 循环内使用（`FOR` 本身亦未实现）。

### 6.2 运算符优先级

| 优先级 | 运算符 | 结合性 |
|--------|--------|--------|
| 1（最低） | `OR` | 左 |
| 2 | `AND` | 左 |
| 3 | `NOT` | 右（一元） |
| 4 | `>`, `<`, `>=`, `<=`, `==`, `!=` | 左 |
| 5 | `+`, `-` | 左 |
| 6 | `*`, `/` | 左 |
| 7（最高） | `-`（一元负号） | 右 |

> 除数为 0 时除法结果为 0。

### 6.3 属性访问

#### 实例属性（`self`）

| 属性 | 类型 | 说明 |
|------|------|------|
| `x1`, `y1` | 数值 | 边界框左上角坐标 |
| `w`, `h` | 数值 | 边界框宽度、高度 |
| `x2`, `y2` | 数值 | 右下角坐标（计算值） |
| `cx`, `cy` | 数值 | 中心点坐标（计算值） |
| `area` | 数值 | 边界框面积 |
| `aspect` | 数值 | 宽高比（w/h） |
| `conf` | 数值 | 检测置信度（0.0 ~ 1.0） |

#### 归一化实例属性（相对于图像尺寸）

| 属性 | 说明 |
|------|------|
| `x1n`, `y1n` | 归一化左上角 |
| `x2n`, `y2n` | 归一化右下角 |
| `cxn`, `cyn` | 归一化中心点 |
| `wn`, `hn` | 归一化宽高 |
| `arean` | 归一化面积 |

#### 类型属性

| 形式 | 说明 |
|------|------|
| `"类别名".count` | 该类别当前实例总数（运行时自动维护） |
| `"类别名".<自定义属性>` | 在 `ATTR` 中定义的类型属性 |

#### 图像属性（`img`）

| 属性 | 类型 | 说明 |
|------|------|------|
| `img.w` | 数值 | 图像宽度（像素） |
| `img.h` | 数值 | 图像高度（像素） |
| `img.area` | 数值 | 图像总面积（w * h） |

---

## 7. 控制流 — **当前版本不支持**

语法已定义，但编译器未实现。以下内容仅供未来参考，**不可在 v0.4 中使用**。

### 7.1 `IF-ELSE`（未实现）

```
IF 布尔表达式
    语句...
[ELSE
    语句...]
ENDIF
```

### 7.2 `FOR` 循环（未实现）

```
FOR 循环变量 IN <class_expr>
    语句...
ENDFOR
```

---

## 8. 排序原语 `SORT`（已实现）

`SORT( <类别表达式>, <排序键>, <名次> )`

- 返回指定类别中按排序键降序排列后，第 N 名的键值（1‑based）
- 名次为负数表示倒数第 |N| 名（升序）
- 这是语言原语，不可被重定义

**示例**：保留面积前 5 的 person

```
RULE FUNC is_top5() -> BOOL:
    self.area >= SORT("person", self.area, 5)
RULEEND

RULE FILTER "person":
    is_top5()
RULEEND
```

---

## 9. 完整语法参考

### 9.1 关键字总览

| 关键字 | 用途 |
|--------|------|
| `RULE`, `RULEEND` | 规则块边界 |
| `FILTER`, `ATTR`, `FUNC`, `GROUP`, `APPEND` | 规则类型 |
| `FROM` | 源类别指定 |
| `AND`, `OR`, `NOT` | 逻辑运算 |
| `IF`, `ELSE`, `ENDIF` | 条件分支（未实现） |
| `FOR`, `IN`, `ENDFOR` | 循环（未实现） |
| `SORT` | 排序原语 |
| `NUM`, `STR`, `BOOL` | 类型声明 |
| `RETURN` | 函数返回 |
| `IMPORT`, `EXPORT`, `AS` | 宿主交互 |

---

## 10. 实战示例（仅使用已实现功能）

### 10.1 基础过滤

```
RULE FILTER "global":
    self.conf > 0.6
RULEEND

RULE FILTER "person":
    self.w > 10
    self.h > 10
RULEEND
```

### 10.2 属性计算 + 过滤

```
RULE ATTR "person":
    self.density = self.conf / self.area
RULEEND

RULE FILTER "person":
    self.density < 0.01
    self.conf > 0.5
RULEEND
```

### 10.3 边界检查（使用 `img`）

```
RULE FILTER "face":
    self.conf > 0.8
    self.x1 > 0
    self.y1 > 0
    self.x2 <= img.w
    self.y2 <= img.h
RULEEND
```

### 10.4 自定义聚合函数（单表达式）

```
RULE FUNC avg_conf(cls:STR) -> NUM:
    "cls".count == 0 ? 0 : (SORT(cls, self.conf, 1) + SORT(cls, self.conf, -1)) / 2
RULEEND

RULE ATTR "car":
    "car".avg_quality = avg_conf("car")
RULEEND
```

### 10.5 创建子类别并追加

```
RULE GROUP "high_conf_person" FROM "person":
    self.conf > 0.95
RULEEND

RULE APPEND "high_conf_person" FROM "car":
    self.conf > 0.95
RULEEND
```

### 10.6 保留每个类别面积最大的 3 个实例

```
RULE FUNC top3_area() -> BOOL:
    self.area >= SORT("person", self.area, 3)
RULEEND

RULE FILTER "person":
    top3_area()
RULEEND
```

---

## 11. 常见问题

**Q：如何删除某个类别的所有实例？**  
A：使用永远为假的条件：
```
RULE FILTER "person":
    FALSE
RULEEND
```

**Q：条件之间是 AND 还是 OR？**  
A：不同行之间默认 AND；需要 OR 时在同一行内使用 `OR` 运算符。

**Q：`self` 和 `img` 需要导入吗？**  
A：不需要，两者均为语言内置对象，直接使用。

**Q：自定义函数可以递归吗？**  
A：当前不支持递归调用。

**Q：`SORT` 可以获取第 N 名本身的实例吗？**  
A：`SORT` 只返回第 N 名的排序键值，不能直接返回实例。但可配合 `FILTER` 与阈值比较实现保留前 N 名的效果。

**Q：我可以在函数内写 `IF` 或 `FOR` 吗？**  
A：**不能**，v0.4 版本不支持这些控制流。请只使用单表达式函数体。

**Q：循环变量属性访问为什么不能用？**  
A：因为 `FOR` 循环本身未实现，因此 `循环变量.属性` 自然也无效。未来版本将一并支持。

---

*本手册随 PostAnvil DSL 版本更新而更新，最新语法文件及运行时库请参考项目仓库。*