# PostAnvil DSL 用户说明文档

> 版本：**0.6** | 更新日期：**2026-07-28**

## 1. 简介

PostAnvil 是用于目标检测结果后处理的领域特定语言（DSL）。它可以按规则过滤检测实例、计算实例或类别属性、创建和扩充类别，并通过函数、条件分支与循环封装较复杂的统计逻辑。

当前版本的主要能力：

- 关键字、DSL 标识符、类别名和属性名大小写不敏感；`EXPORT ... AS` 的宿主导出名保留原始拼写。
- `FILTER`、`ATTR`、`GROUP`、`APPEND`、`SORT` 规则按书写顺序组成执行管道。
- 支持 `NUM`、`STR`、`BOOL`、`INST`、`ANY` 类型，以及全局变量、函数参数和函数局部变量。
- 函数内支持 `IF` / `ELIF` / `ELSE`、嵌套 `FOR`、局部变量声明与赋值、`RETURN`。
- 内置 `self`、`img`、类别属性和原地稳定 `SORT` 规则。
- 提供原生数学、检测框空间关系和实例查询函数，并支持稳定 `id` 与实时 `index`。
- 通过 `IMPORT` / `EXPORT` 与 C++ 宿主交换值。

## 2. 快速开始

下面的程序先计算风险值，再过滤低置信度实例，最后导出剩余数量：

```postanvil
IMPORT NUM min_conf

RULE FUNC risk_level(conf: NUM) -> NUM:
    IF conf > 0.8
        RETURN 3
    ELIF conf > 0.5
        RETURN 2
    ELSE
        RETURN 1
    IFEND
RULEEND

RULE ATTR "person":
    self.risk = risk_level(self.conf)
RULEEND

RULE FILTER "person":
    self.conf > min_conf
    self.risk >= 2
RULEEND

EXPORT "person".count AS person_count
```

基本约定：

- 每个 `RULE` 块以 `RULEEND` 结束。
- 冒号只出现在规则头部；`IF`、`ELIF`、`ELSE`、`FOR` 后不写冒号。
- 换行是语句分隔符。
- `FILTER`、`GROUP`、`APPEND` 中不同行条件自动按 `AND` 连接。
- `#` 和 `//` 均可开始行注释。

## 3. 程序结构与执行顺序

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
| `RULE GROUP` | 从源类别复制满足条件的实例，形成目标类别 |
| `RULE APPEND` | 将满足条件的实例追加到目标类别 |
| `RULE SORT` | 按一个或多个键原地稳定排序类别实例 |

声明和规则按源文件中的顺序形成算子管道。后续规则可以读取前面规则产生的属性或类别；`EXPORT` 读取的是执行到该位置时的值，因此通常放在程序末尾。

## 4. 顶层声明

### 4.1 导入

```postanvil
IMPORT NUM min_conf
IMPORT STR host_class AS target_class
IMPORT NUM threshold, BOOL debug, STR host_name AS local_name
IMPORT INST host_anchor AS anchor
```

每个导入项为 `类型 宿主名 [AS DSL本地名]`。执行前，C++ 侧使用 DSL 本地名（无别名时即宿主名）的大写形式注入值，例如 `scene.add_import("MIN_CONF", 0.6)`。

### 4.2 导出

```postanvil
EXPORT "person".count AS person_count
EXPORT "car".avg_conf AS carAverage
EXPORT 3.14159 AS pi
```

一个 `EXPORT` 可用逗号包含多项。C++ 侧用 `result.get_export("person_count")` 读取；名称必须与 `AS` 后的拼写一致。

### 4.3 全局变量

```postanvil
NUM threshold = 0.7
STR target = "person"
BOOL debug = FALSE
ANY value = threshold

threshold = 0.8
```

赋值前必须先声明变量，赋值类型必须兼容。`ANY` 声明会根据初始化表达式确定实际类型。

### 4.4 实例变量（INST）

`INST` 表示一个检测实例快照。`self` 是 `INST` 表达式，普通类别 `FOR` 循环中的循环变量也是 `INST`，因此都可以赋给变量、传入函数或作为返回值：

```postanvil
RULE FUNC confidence(item: INST) -> NUM:
    RETURN item.conf
RULEEND

RULE FUNC first_inst(cls: STR) -> INST:
    FOR obj IN cls
        INST selected = obj
        RETURN selected
    FOREND
    RETURN self
RULEEND
```

实例变量通过 `<变量>.<属性>` 读取属性，例如 `selected.area`。`INST` 使用快照语义：赋值或传参时保留当时的实例值，不持有场景容器中的裸指针；后续过滤、分组或追加不会令该值悬空。

每个输入实例在构造 `Scene` 时都会按传入顺序获得从 `1` 开始、场景内稳定的 `id`。`GROUP` / `APPEND` 产生的副本保留源实例 `id`，用于表示同一个逻辑检测结果。`index` 是实例在当前类别中的从 `1` 开始的位置；过滤、分组或追加后会自动重建。

```postanvil
NUM stable_id = self.id
NUM current_position = self.index
STR class_name = self.cls

INST by_id = _INST_ID(12)
INST by_position = _INST_INDEX("person", 3)
```

`_INST_ID(id)` 在场景中按稳定编号查询；`_INST_INDEX(class, index)` 按类别的当前位置查询。编号必须是正整数，目标不存在或索引越界时产生运行时错误。

当前限制：

- 只能读取 `INST` 属性，暂不支持 `item.conf = ...` 形式的实例变量属性写入。
- `INST` 不支持算术、逻辑或直接比较；请比较其属性，例如 `a.conf > b.conf`。
- 在没有当前实例的上下文求值 `self` 会产生运行时错误。

## 5. 规则

### 5.1 FILTER

```postanvil
RULE FILTER <类别表达式>:
    <布尔表达式>
    ...
RULEEND
```

类别表达式只能是字符串字面量或字符串变量。`"global"` 表示对所有类别应用过滤。

```postanvil
RULE FILTER "person":
    self.conf >= 0.7
    (self.w > 100 OR self.h > 100)
    NOT self.area < 500
RULEEND
```

`FILTER` 中只允许条件表达式，不允许赋值。

### 5.2 ATTR

```postanvil
RULE ATTR "car":
    self.density = self.conf / self.area
    "car".quality = 0.8
RULEEND
```

- `self.name = expr`：逐实例设置动态属性；写入 `w`、`h`、`x1`、`y1`、`conf`、`cls` 时会同步修改对应内置值。
- `"class".name = expr`：设置类别共享属性。
- 目标写法必须是 `self.<属性>` 或字符串字面量类别的 `<类别>.<属性>`。
- `ATTR` 规则体只接受属性赋值；需要条件计算时，将控制流写入函数，再从 `ATTR` 调用该函数。
- `RULE ATTR "global"` 会遍历全部类别的实例。

### 5.3 FUNC

```postanvil
RULE FUNC <函数名>(参数: 类型, ...) -> 返回类型:
    <函数语句>
RULEEND
```

返回类型可省略；类型可为 `NUM`、`STR`、`BOOL`、`INST` 或 `ANY`。函数体支持：

```postanvil
NUM total = 0       // 局部变量声明
total = total + 1   // 已声明变量赋值
some_call()         // 表达式语句
RETURN total        // 返回并结束函数
```

简单函数仍可直接用最后一个表达式作为结果：

```postanvil
RULE FUNC is_large(w: NUM, h: NUM) -> BOOL:
    w * h > 1000
RULEEND
```

函数定义应先于调用它的规则或函数。当前不提供递归、`BREAK`、`CONTINUE` 或用户自定义重载。

### 5.4 GROUP

```postanvil
RULE GROUP "large_person" FROM "person":
    self.area > 1000
    self.conf > 0.8
RULEEND
```

从源类别选择满足全部条件的实例，复制到目标类别；源类别不受影响。目标和源均可使用字符串变量。

### 5.5 APPEND

```postanvil
RULE APPEND "vip" FROM "person":
    self.conf > 0.95
RULEEND
```

将源类别中满足条件的实例追加到目标类别，目标不存在时会创建。

## 6. 函数控制流

块结束关键字统一使用“块声明关键字 + `END`”的顺序：规则块使用 `RULEEND`，条件块使用 `IFEND`，循环块使用 `FOREND`。旧写法 `ENDIF` 和 `ENDFOR` 不再接受。

### 6.1 IF / ELIF / ELSE

```postanvil
IF condition
    statements
ELIF other_condition
    statements
ELSE
    statements
IFEND
```

支持零个或多个 `ELIF` 和可选的 `ELSE`，也可以嵌套。分支内声明的局部变量只在该分支作用域内有效。

```postanvil
RULE FUNC level(conf: NUM) -> NUM:
    IF conf > 0.8
        RETURN 3
    ELIF conf > 0.5
        RETURN 2
    ELSE
        RETURN 1
    IFEND
RULEEND
```

### 6.2 FOR

```postanvil
FOR obj IN <类别表达式>
    statements
FOREND
```

普通类别循环中，循环变量的类型为 `INST`，可读取 `obj.conf`、`obj.area` 等属性，也可赋给其他 `INST` 变量或传入函数：

```postanvil
RULE FUNC avg_conf(cls: STR) -> NUM:
    NUM total = 0
    FOR obj IN cls
        total = total + obj.conf
    FOREND
    IF cls.count == 0
        RETURN 0
    ELSE
        RETURN total / cls.count
    IFEND
RULEEND
```

`FOR cls IN "global"` 遍历类别名，因此可以嵌套遍历全部实例：

```postanvil
RULE FUNC total_area() -> NUM:
    NUM total = 0
    FOR cls IN "global"
        FOR obj IN cls
            total = total + obj.area
        FOREND
    FOREND
    RETURN total
RULEEND
```

循环体拥有独立作用域；`RETURN` 会立即结束循环和函数。空类别和不存在的类别均视为空集合，循环执行零次。

## 7. 表达式与类型

### 7.1 字面量与访问形式

| 形式 | 示例 |
|---|---|
| 数值 | `100`、`0.5`、`.8` |
| 字符串 | `"person"`、`"hello\\\"world"` |
| 布尔 | `TRUE`、`FALSE` |
| 当前实例值 | `self`（类型为 `INST`） |
| 变量 | `threshold` |
| 当前实例属性 | `self.conf`、`self.id`、`self.index`、`self.cls` |
| 类别属性 | `"car".count`、`cls.count` |
| 图像属性 | `img.w` |
| 循环实例属性 | `obj.area` |
| 实例变量属性 | `selected.conf` |
| 动态属性 | `obj.(prop_name)` |
| 函数调用 | `avg_conf("car")`、`_SQRT(9)`、`_IOU(a, b)` |

字符串仅支持 `==` 和 `!=` 比较。表达式系统没有三元运算符、`LET`、对象构造或幂运算符；幂运算使用 `_POW(base, exponent)`。

### 7.2 显式动态属性

静态属性写法中的点号右侧是固定属性名：

```postanvil
obj.conf
cls.count
img.w
```

需要由字符串表达式在运行时决定属性名时，在点号后使用括号：

```postanvil
obj.(prop_name)
self.(prop_name)
cls.(prop_name)
"person".(prop_name)
img.(prop_name)
```

括号内表达式必须返回 `STR`（或运行时值为 `STR` 的 `ANY`）。属性名大小写不敏感，运行时会统一转换为大写。静态写法和动态写法互不影响：即使存在名为 `conf` 的变量，`obj.conf` 仍固定读取 `CONF` 属性，只有 `obj.(conf)` 才会读取变量 `conf` 指定的属性。

以下函数可以按属性名计算类别实例的数值平均值：

```postanvil
RULE FUNC fn_avg(_cls: STR, _prop: STR) -> NUM:
    NUM _sum = 0
    FOR _inst IN _cls
        _sum = _sum + _inst.(_prop)
    FOREND
    RETURN _sum / _cls.count
RULEEND

NUM avg_conf = fn_avg("person", "conf")
NUM avg_area = fn_avg("person", "area")
```

如果动态属性不存在，或属性值不能参与所在表达式要求的运算，将产生运行时错误。类别为空时当前数值除零规则会返回 `0`。

### 7.3 运算符优先级

从低到高：

| 优先级 | 运算符 |
|---|---|
| 1 | `OR` |
| 2 | `AND` |
| 3 | `NOT` |
| 4 | `>`、`<`、`>=`、`<=`、`==`、`!=` |
| 5 | `+`、`-` |
| 6 | `*`、`/` |
| 7 | 一元 `-` |

比较表达式一次只能包含一个比较运算符；需要组合多个比较时使用 `AND` 或 `OR`。数值除以零的结果为 `0`。

## 8. 内置属性

### 8.1 实例属性

| 属性 | 含义 | 可通过 ATTR 修改 |
|---|---|---|
| `x1`、`y1` | 左上角坐标 | 是 |
| `w`、`h` | 宽、高 | 是 |
| `conf` | 置信度 | 是 |
| `cls` | 类别名 | 是 |
| `id` | Scene 为输入实例分配的稳定编号，从 1 开始 | 否 |
| `index` | 当前类别中的实时位置，从 1 开始 | 否 |
| `x2`、`y2` | 右下角坐标 | 否，派生值 |
| `cx`、`cy` | 中心坐标 | 否，派生值 |
| `area` | `w * h` | 否，派生值 |
| `aspect` | `w / h`；宽或高为零时为 `0` | 否，派生值 |
| `wn`、`hn` | 相对图像宽高的归一化尺寸 | 否 |
| `x1n`、`x2n`、`cxn` | 相对图像宽度的归一化横坐标 | 否 |
| `y1n`、`y2n`、`cyn` | 相对图像高度的归一化纵坐标 | 否 |
| `arean` | `area / img.area` | 否 |

除以上属性外，`ATTR` 可创建 `self.<自定义属性>`。

### 8.2 图像属性

`img.w`、`img.h`、`img.area`、`img.aspect`、`img.path`。

### 8.3 类别属性

- `<类别>.count`：当前实例数量，由运行时维护；类别不存在时返回 `0`。
- `<类别>.<自定义属性>`：此前由 `ATTR` 设置的类别属性。

不存在类别等价于空集合：`FOR` 执行零次、`FILTER` / `APPEND` 不产生实例、`GROUP` 创建空目标类别。读取不存在类别的非 `count` 属性，或读取尚未定义的属性，仍会产生运行时错误。

### 8.4 原生内置函数

内置函数使用与用户 `FUNC` 相同的调用形式，名称不区分大小写。编译器会检查参数数量和类型，运行时直接执行原生 C++ 实现。内置名称为保留名称，不能由用户 `RULE FUNC` 覆盖。

#### 数学函数

| 函数 | 返回类型 | 说明 |
|---|---|---|
| `_ABS(x)` | `NUM` | 绝对值 |
| `_MIN(a, b)`、`_MAX(a, b)` | `NUM` | 两数较小值、较大值 |
| `_SQRT(x)` | `NUM` | 平方根，要求 `x >= 0` |
| `_POW(base, exponent)` | `NUM` | 幂运算 |
| `_EXP(x)` | `NUM` | 自然指数 |
| `_LOG(x)`、`_LOG10(x)` | `NUM` | 自然对数、常用对数，要求 `x > 0` |
| `_FLOOR(x)`、`_CEIL(x)`、`_ROUND(x)` | `NUM` | 向下、向上、四舍五入取整 |
| `_CLAMP(x, low, high)` | `NUM` | 限制到闭区间，要求 `low <= high` |

数学函数产生非有限结果或参数不满足定义域时会抛出运行时错误。

#### 检测框与位置关系函数

| 函数 | 返回类型 | 说明 |
|---|---|---|
| `_INTER_AREA(a, b)` | `NUM` | 两个 `INST` 检测框的交集面积 |
| `_IOU(a, b)` | `NUM` | 交集面积除以并集面积 |
| `_OVERLAP_A(a, b)` | `NUM` | 交集面积除以第一个实例 `a` 的面积 |
| `_OVERLAP_B(a, b)` | `NUM` | 交集面积除以第二个实例 `b` 的面积 |
| `_OVERLAPS(a, b)` | `BOOL` | 交集面积是否大于零 |
| `_CONTAINS(inner, outer)` | `BOOL` | `inner` 是否完全位于 `outer` 内，边界相等也算包含 |
| `_DISTANCE(a, b)` | `NUM` | 两个检测框中心点的欧氏距离 |
| `_NEARBY(a, b, threshold)` | `BOOL` | 中心距离是否不大于非负阈值；内部使用距离平方比较 |

当参与比值的分母面积为零时，`_IOU`、`_OVERLAP_A`、`_OVERLAP_B` 返回 `0`。

#### 实例查询函数

| 函数 | 返回类型 | 说明 |
|---|---|---|
| `_INST_ID(id)` | `INST` | 按 Scene 稳定编号获取实例快照 |
| `_INST_INDEX(class, index)` | `INST` | 按类别和当前 1-based 位置获取实例快照 |

`_INST_ID` 和 `_INST_INDEX` 的数字参数必须是 DSL `NUM` 可精确表示的正整数。`_INST_INDEX` 的类别名不区分大小写；实例不存在或索引越界时会产生运行时错误。

## 9. SORT 排序规则

```postanvil
RULE SORT <类别表达式>:
    <键表达式> ASC|DESC
    ...
RULEEND
```

- `SORT` 会直接改变目标类别中的实例顺序，不再作为表达式返回键值。
- 支持多关键字排序；各行按书写顺序组成字典序比较。
- 每个键必须显式指定 `ASC`（升序）或 `DESC`（降序）。
- 排序是稳定的：所有键都相等时保持排序前的相对顺序。
- 每个实例的每个排序键只计算一次，之后仅比较缓存值。
- 排序键可以是 `NUM`、`STR`、`BOOL` 或运行时产生这些类型的 `ANY`，不能直接使用 `INST`。
- 排序完成后自动重建从 `1` 开始的 `self.index`；`self.id` 不变。
- 类别不存在或为空时不执行任何操作；`"global"` 表示分别排序所有类别。

按面积降序、置信度降序排列，然后精确保留前三个实例：

```postanvil
RULE SORT "person":
    self.area DESC
    self.conf DESC
    self.id ASC
RULEEND

RULE FILTER "person":
    self.index <= 3
RULEEND
```

取得综合得分最高的实例：

```postanvil
RULE SORT "spike":
    self.comprehensive_score DESC
    self.id ASC
RULEEND

INST best_spike = _INST_INDEX("spike", 1)
```

`self.id ASC` 可作为最终确定性排序键；即使其他键全部相同，也会按 Scene 输入编号稳定确定顺序。

## 10. C++ 宿主用法

统一包含头为 `PostAnvil.h`：

```cpp
#include "PostAnvil.h"

using namespace postanvil;

std::string source = R"(
    IMPORT NUM min_conf
    RULE FILTER "person":
        self.conf > min_conf
    RULEEND
    EXPORT "person".count AS kept
)";

PostAnvilCompiler compiler;
CompiledProgram program = compiler.compile(source);

Scene scene(
    Image{640, 480},
    {
        Instance("person", 10, 20, 80, 120, 0.90),
        Instance("person", 30, 40, 60, 100, 0.40)
    }
);
scene.add_import("MIN_CONF", Val(0.60));

Scene result = program.evaluate(scene);
double kept = result.get_export("kept").as_num();
```

C++ 可直接构造和读取 `INST` 值：

```cpp
scene.add_import(
    "ANCHOR",
    Val(Instance("person", 10, 20, 80, 120, 0.75))
);

Val selected = result.get_export("selected_anchor");
std::shared_ptr<const Instance> snapshot = selected.as_inst();
double confidence = snapshot->conf();
```

- `compile()` 在词法、语法或静态类型检查失败时抛出 `CompileError`。
- `evaluate()` 在缺少导入值、类型不匹配、类别/属性不存在等情况下抛出 `RuntimeError`。
- 类别和 DSL 内部名称会统一为大写；宿主注入变量时建议直接使用大写键。
- `CompiledProgram` 只支持移动，不支持复制。

## 11. 关键字

`RULE`、`RULEEND`、`FILTER`、`ATTR`、`FUNC`、`GROUP`、`APPEND`、`SORT`、`ASC`、`DESC`、`FROM`、`AND`、`OR`、`NOT`、`SELF`、`NUM`、`STR`、`BOOL`、`INST`、`ANY`、`RETURN`、`IMPORT`、`EXPORT`、`AS`、`IF`、`ELIF`、`ELSE`、`IFEND`、`FOR`、`IN`、`FOREND`、`TRUE`、`FALSE`。

## 12. 常见问题

**如何删除某类别的全部实例？**

```postanvil
RULE FILTER "person":
    FALSE
RULEEND
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

本手册以项目中的 `PostAnvil.g4`、公开 C++ 头文件和测试样例为准。
