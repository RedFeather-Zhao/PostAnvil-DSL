# 实例身份与类别成员设计

[文档中心](../README.md) · [DSL 声明与规则](../dsl/language.md)

## 本页目录

- [核心概念](#核心概念)
- [ID、类别和内存](#id类别和内存)
- [已有类别操作](#已有类别操作)
- [后续语法建议](#后续语法建议)

> 状态：0.8.0 实例模型已落地；文末的新语法仅为后续候选，尚未实现。

## 核心概念

PostAnvil 只使用一个数据对象名称：`Instance`。

- Scene 的私有实例表保存全部 `Instance`，数组下标就是 `InstId`。
- 第 0 项是 dummy；真实实例的 ID 从 1 开始，按添加顺序增长。
- Scene 的私有类别关系表保存 `cls_name -> InstId 列表`，不保存 `Instance` 副本。
- `InstanceHandle` 保存 `id` 和可选的 `cls_name` 访问上下文；它不拥有、也不复制 `Instance`。

实例表使用 `std::vector<std::unique_ptr<Instance>>`。Scene 是实例生命周期的唯一管理者；vector 扩容只移动 `unique_ptr`，不会移动已有 `Instance`。Scene 复制时深复制实例，不会让两个 Scene 共享可变状态。

## ID、类别和内存

同一 Scene 内，同一 ID 始终对应同一个 `Instance` 和同一个内存地址。把某个 ID 加入另一个类别，只会修改类别索引，不会创建副本，也不会修改 ID。

`Instance` 不保存类别。`cls_name` 只存在于 Scene 的类别索引以及
`InstanceHandle::cls_name` 访问上下文中。`Scene::inst_add(instance)` 只创建实例并
分配 ID，`Scene::cls_add_inst(cls_name, id)` 单独建立类别关系。

DSL 中只暴露 `CLS / ID / INDEX`：

| 属性 | 含义 |
|---|---|
| `self.id` | Scene 内的实例 ID |
| `self.cls` | 句柄的 `cls_name`；句柄不带类别上下文时产生运行时错误 |
| `self.index` | 该 ID 在句柄 `cls_name` 对应列表中的 1-based 位置 |
| 坐标、置信度、动态属性 | `Instance` 本身的状态，所有包含该 ID 的类别共享 |

`_INST_ID(id)` 返回不带 `cls_name` 的句柄，因此不能读取 `cls` 或 `index`。
`_INST_INDEX(cls_name, index)` 返回带类别上下文的句柄。
`_HAS_INST_ID(id)` 和 `_HAS_INST_INDEX(cls_name, index)` 用于无异常地检查目标是否存在。

## 已有类别操作

```postanvil
// 用符合条件的 ID 替换目标类别，源类别不变
RULE GROUP "vip" FROM "person" {
    self.conf >= 0.9
}

// 把符合条件的 ID 加入目标类别，已存在的 ID 不重复添加
RULE APPEND "review" FROM "person" {
    self.id == selected.id
}

// 只改变 person 的 ID 列表，不删除 Instance
RULE FILTER "person" {
    self.conf >= 0.5
}

// 只重排 person 的 ID 列表
RULE SORT "person" {
    self.conf DESC
}
```

当前把实例加入另一个类别应使用 `APPEND`。加入后 ID 不变，通过源类别和目标类别读写的都是同一个 `Instance`。

## 组与全部实例

规则目标现在使用显式选择器，不再让 `"global"` 同时表示类别集合和实例全集：

- `"person", "car"` 是临时类别组，按书写顺序逐类别处理；同一 ID 在不同类别中的成员关系
  是不同访问上下文，因此可能执行多次。
- `@ALL_CLASS` 是内置类别组，运行时展开为 Scene 当前全部普通类别。
- `ALL_INST` 是内置类别。Scene 每次创建实例时都会把新的稳定 ID 加入该类别，因此它初始覆盖全部传入实例。
- 所有 `@` 开头名称均保留给内置和未来命名类别组；未知组在编译期报错。

所有算子都只处理类别及其 ID 视图，不存在 DSL 直接操作实例表的语义。`FILTER ALL_INST`
只替换该内置类别的成员列表；`SORT ALL_INST` 只重排该列表。它们都不删除实例、不改变稳定 ID，也不隐式修改其他类别。
`@ALL_CLASS` 展开时排除 `ALL_INST`，避免内置类别造成重复处理。

## 后续语法建议

普通函数保持值计算，不加入 `_ADD_TO()` 或 `item.cls = ...` 这类隐式修改 Scene 的操作。类别变更继续使用顶层 `RULE`，执行顺序和影响范围更清楚。

建议优先级：

1. `RULE MOVE "target" FROM "source" { ... }`：将匹配 ID 加入目标类别，再从源类别移除；ID 和 `Instance` 均不变。
2. `RULE REMOVE "class" { ... }`：从指定类别移除匹配 ID；可用反向 `FILTER` 表达，因此优先级较低。
3. `RULE CLONE "target" FROM "source" { ... }`：创建新 `Instance` 和新 ID。实现前需先定义动态属性及宿主扩展数据的复制规则。
4. `RULE DELETE ...`：删除 `Instance` 并从全部类别清理该 ID。为保持 ID 不变，需要墓碑位以及已有句柄失效规则，近期不建议实现。

`MOVE` 建议先对源类别的 ID 快照计算全部条件，全部成功后再一次性修改两个 ID 列表。源类别和目标类别相同时为空操作；任何条件求值失败时，两个列表都不改变。

---

[返回文档中心](../README.md)
