# DSL 声明与规则

[文档中心](../README.md) · [DSL 快速开始](README.md)

## 本页目录

- [顶层声明](#顶层声明)
- [导入与导出](#导入与导出)
- [变量与实例句柄](#变量与实例句柄)
- [规则](#规则)

## 顶层声明

### 导入与导出

#### 导入

```postanvil
IMPORT NUM min_conf
IMPORT STR host_class AS target_class
IMPORT NUM threshold, BOOL debug, STR host_name AS local_name
IMPORT INST host_anchor AS anchor
```

每个导入项为 `类型 宿主名 [AS DSL本地名]`。执行前，宿主使用 DSL 本地名（无别名时即宿主名）注入值。C++ 侧建议使用大写形式，例如 `scene.io_import("MIN_CONF", 0.6)`；Python 绑定会自动规范化名称大小写。

#### 导出

```postanvil
EXPORT "person".count AS person_count
EXPORT "car".avg_conf AS carAverage
EXPORT 3.14159 AS pi
```

一个 `EXPORT` 可用逗号包含多项。C++ 和 Python 均用 `result.io_export("person_count")` 读取；名称必须与 `AS` 后的拼写一致。

### 变量与实例句柄

#### 全局变量

```postanvil
NUM threshold = 0.7
STR target = "person"
BOOL debug = FALSE
ANY value = threshold

threshold = 0.8
```

赋值前必须先声明变量，赋值类型必须兼容。`ANY` 声明会根据初始化表达式确定实际类型。

#### 实例变量（INST）

`INST` 是 Scene 内实例的轻量句柄。句柄保存实例 `id`；从类别规则或类别遍历中产生时，还保存当前 `cls_name`，以便解析 `cls` 和 `index`。句柄不复制、也不拥有 `Instance`。`self` 和普通类别 `FOR` 循环变量都是 `INST`，可以赋给变量、传入函数或作为返回值：

```postanvil
RULE FUNC confidence(item: INST) -> NUM {
    RETURN item.conf
}
RULE FUNC first_inst(cls: STR) -> INST {
    FOR obj IN cls {
        INST selected = obj
        RETURN selected
    }
    RETURN self
}
```

实例变量通过 `<变量>.<属性>` 读取属性，例如 `selected.area`。句柄通过所属 Scene 和 `id` 查找实例；`FILTER`、`GROUP`、`APPEND` 和 `SORT` 只修改类别中的 ID 列表，不会使句柄悬空。句柄不能跨 Scene 使用。

Scene 内部的实例表按 ID 存放：第 `0` 项是 dummy，不属于任何用户类别；真实实例按插入顺序获得从 `1` 开始的 ID。每个类别对应一个有序、去重的 ID 列表，但内部容器不会对外暴露。同一 Scene 内，同一 ID 在不同类别中始终指向同一个 `Instance`；对坐标、置信度或动态属性的修改会在所有包含该 ID 的类别中可见。复制 Scene 时会深复制实例，新 Scene 与原 Scene 不共享可变实例。

`self.cls` 表示当前句柄的 `cls_name`，`self.index` 表示该 ID 在当前类别中的 1-based 位置。按 ID 查询得到的句柄不带类别上下文，因此 `cls` 和 `index` 均不可用并会产生运行时错误。`Instance` 本身不保存类别归属，DSL 也不另外定义 `label` 或 `category` 属性。

```postanvil
NUM stable_id = self.id
NUM current_position = self.index
STR cls_name = self.cls

INST by_id = _INST_ID(12)
INST by_position = _INST_INDEX("person", 3)
BOOL has_id = _HAS_INST_ID(12)
BOOL has_position = _HAS_INST_INDEX("person", 3)
```

`_INST_ID(id)` 在场景中按稳定编号查询；`_INST_INDEX(class, index)` 按类别的当前位置查询。编号必须是正整数，目标不存在或索引越界时产生运行时错误。需要在查询前判断时使用 `_HAS_INST_ID` 或 `_HAS_INST_INDEX`；非法数值、不存在类别和越界位置均返回 `FALSE`。

当前限制：

- 只能读取 `INST` 属性，暂不支持 `item.conf = ...` 形式的实例变量属性写入。
- `INST` 不支持算术、逻辑或直接比较；请比较其属性，例如 `a.conf > b.conf`。
- 在没有当前实例的上下文求值 `self` 会产生运行时错误。

## 规则

### FILTER
语法结构如下，由规则名、目标选择器、规则块和若干并列的布尔表达式组成：

```postanvil
RULE FILTER <类别选择器> {
    <布尔表达式>
    ...
}
```

单个类别可以是字符串字面量或字符串变量；用逗号分隔多个类别可组成临时类别组：

```postanvil
RULE FILTER "person", "car", target_class {
    self.conf >= 0.7
}
```

`@` 开头的名称只表示类别组；不带 `@` 的 `ALL_INST` 是内置类别：

| 名称 | 类型 | 含义 | 实例上下文 |
|---|---|---|---|
| `@ALL_CLASS` | 类别组 | 当前 Scene 的全部类别，逐类别执行 | 有 `self.cls` 和 `self.index`；同一 ID 可因属于多个类别而执行多次 |
| `ALL_INST` | 内置类别 | Scene 创建实例时自动记录其稳定 ID，初始覆盖全部传入实例 | 与普通类别一致，有 `self.cls` 和 `self.index` |

`"global"` 不再具有特殊含义，现在只是普通的 `GLOBAL` 类别名。`FILTER ALL_INST`
仅筛选内置类别的成员列表；它不删除实例、不改变稳定 ID，也不修改其他类别。`@ALL_CLASS`
展开时不包含 `ALL_INST`，避免同一实例因内置类别而额外执行一次。
当且仅当一个实例满足所有条件表达式为真，该类别成员关系才会保留。

```postanvil
RULE FILTER "person" {
    self.conf >= 0.7
    (self.w > 100 OR self.h > 100)
    NOT self.area < 500
}
```

`FILTER` 中只允许条件表达式，不允许赋值。

### ATTR

```postanvil
RULE ATTR "car" {
    self.density = self.conf / self.area
    "car".quality = 0.8
}
```

- `self.name = expr`：逐实例设置动态属性；写入 `w`、`h`、`x1`、`y1`、`conf` 时会同步修改对应内置值。`cls` 是句柄的只读类别上下文，修改类别关系应使用 `GROUP` 或 `APPEND`。
- `"class".name = expr`：设置类别共享属性。
- 目标写法必须是 `self.<属性>` 或字符串字面量类别的 `<类别>.<属性>`。
- `ATTR` 规则体只接受属性赋值；需要条件计算时，将控制流写入函数，再从 `ATTR` 调用该函数。
- `RULE ATTR ALL_INST` 会遍历内置类别当前的成员；`RULE ATTR @ALL_CLASS`
  和逗号临时组则逐类别执行，并保留类别上下文。

### FUNC

```postanvil
RULE FUNC <函数名>(参数: 类型, ...) -> 返回类型 {
    <函数语句>
}
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
RULE FUNC is_large(w: NUM, h: NUM) -> BOOL {
    w * h > 1000
}
```

函数定义应先于调用它的规则或函数。当前不提供递归、`BREAK`、`CONTINUE` 或用户自定义重载。

### GROUP

```postanvil
RULE GROUP "large_object" FROM "person", "car" {
    self.area > 1000
    self.conf > 0.8
}
```

从一个或多个源类别选择满足全部条件的实例，用同一批实例 ID 替换目标类别成员；不会复制实例，源类别不受影响。目标类别必须是单个类别，源选择器支持逗号临时组、`@ALL_CLASS` 和内置类别 `ALL_INST`。同一 ID 在目标中只保留一次；对类别组求值时，每个来源成员保留其类别上下文。

### APPEND

```postanvil
RULE APPEND "vip" FROM "person" {
    self.conf > 0.95
}
```

将源选择器中满足条件的实例 ID 合并到目标类别，目标不存在时会创建。源选择器与 `GROUP` 相同；追加是幂等操作，目标中已经存在的 ID 不会重复插入。

---

上一篇：[快速开始](README.md) · 下一篇：[控制流、表达式与类型](control-flow.md)
