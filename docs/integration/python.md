# Python 接入

[文档中心](../README.md) · [Python 包构建与发布](../development/python-package.md)

## 本页目录

- [基本用法](#基本用法)
- [实例句柄与类别成员](#实例句柄与类别成员)
- [结构化编译错误](#结构化编译错误)
- [Ultralytics YOLO 集成](#ultralytics-yolo-集成)

## 基本用法

安装与当前 Python 版本和平台匹配的 wheel 后，可以直接导入 `postanvil`。Python 绑定提供
`Compiler`、`Program`、`Image`、`Instance`、`InstanceHandle`、`Scene` 以及对应的异常类型。

```python
import postanvil

source = '''
IMPORT NUM min_conf
RULE FILTER "person" {
    self.conf > min_conf
}
EXPORT "person".count AS kept
'''

program = postanvil.Compiler().compile(source)
scene = postanvil.Scene(postanvil.Image(640, 480))
scene.add("person", postanvil.Instance(10, 20, 80, 120, 0.90))
scene.add("person", postanvil.Instance(30, 40, 60, 100, 0.40))
scene.add_import("MIN_CONF", 0.60)

result = program.evaluate(scene)
assert result.count("PERSON") == 1
assert result.get_export("kept") == 1.0
```

也可以使用模块级便捷函数：

```python
program = postanvil.compile(source)
```

`postanvil.__version__` 返回原生模块版本。发布包的元数据版本与原生模块版本应保持一致。

## 实例句柄与类别成员

`Scene.add()` 会创建一个 Scene 内实例，建立初始类别成员关系，并返回
`InstanceHandle`。句柄的 `id` 在该 Scene 内稳定；`cls_name` 是句柄的当前类别上下文，
不是 `Instance` 的字段。

```python
scene = postanvil.Scene(postanvil.Image(640, 480))
person = scene.add("person", postanvil.Instance(10, 20, 80, 120, 0.90))
scene.append_to_class("foreground", person)

assert person.id == 1
assert person.cls_name == "PERSON"
assert scene.instance_ids("PERSON") == [1]
assert scene.instance_ids("FOREGROUND") == [1]
assert scene.instance_count == 1
```

`append_to_class(cls_name, handle)` 和 `append_id_to_class(cls_name, id)` 都是幂等操作。
`replace_class_ids(cls_name, ids)` 用给定 ID 列表整体替换类别成员。`instance_ids()`
返回 ID 列表；`instances()` 返回实例引用；`handles()` 返回带该类别上下文的句柄。
`get_by_id()` 的句柄无类别上下文，`get_by_index()` 的 `index` 从 1 开始。

Python 的 `add_import()` 接受 `bool`、数字、字符串和 `InstanceHandle`；DSL 导出
`INST` 时，`get_export()` 也返回 `InstanceHandle`。句柄只能在其所属 Scene 中使用。

## 结构化编译错误

`PACompileError` 的 `str(error)` 是面向人的完整诊断。如需构建 CLI、编辑器插件或
自定义界面，可以直接读取结构化属性：

```python
try:
    postanvil.compile(source)
except postanvil.PACompileError as error:
    assert error.kind in (
        postanvil.CompileErrorKind.SYNTAX,
        postanvil.CompileErrorKind.SEMANTIC,
        postanvil.CompileErrorKind.INTERNAL,
    )
    print(error.message)
    print(error.line, error.column)       # 未知时为 -1
    print(error.source_line or "")
    print(error.hint or "")
    print(error.raw_message)              # 仅建议用于诊断工具
```

## Ultralytics YOLO 集成

Ultralytics 是可选依赖；不使用 YOLO 集成时无需安装。需要集成时执行：

```bash
python -m pip install "postanvil[ultralytics]"
```

`from_ultralytics()` 将单个轴对齐目标检测 `Results` 转成 `Scene`；
`update_ultralytics()` 将处理后的 `Scene` 写回原结果；`apply_ultralytics()` 组合这两个
步骤。规则应在推理循环外编译一次：

```python
from ultralytics import YOLO
import postanvil

model = YOLO("model.pt")
program = postanvil.compile('''
IMPORT NUM min_conf
RULE FILTER "global" {
    self.conf >= min_conf
}
''')

for detection in model("image.jpg"):
    postanvil.apply_ultralytics(
        program,
        detection,
        imports={"MIN_CONF": 0.5},
    )
    detection.save(filename="filtered.jpg")
```

坐标转换读取 Ultralytics 的 `[x1, y1, x2, y2]`，并转换成 PostAnvil 的左上角坐标、
宽和高。跟踪结果的 track ID 保存在 `YOLO_TRACK_ID` 动态属性中。PostAnvil 自身的
稳定 `id` 与 YOLO track ID 含义不同，不应混用。

当前适配器只允许把普通轴对齐检测框写回 YOLO。分割、姿态、OBB、分类、语义掩码和
深度结果包含与框逐项关联的额外数据，单独更新框会造成不同步，因此会被明确拒绝。
动态属性、类别属性和导出值只保留在 `Scene`。新类别默认不写入 YOLO 名称表；确需新增
类别时传入 `allow_new_classes=True`。一个 PostAnvil 实例可以属于多个类别，但 YOLO 单个
检测框只有一个类别字段。写回时优先使用实例仍然所属的原始标签类别；若该成员关系已被
移除，则实例必须只剩一个候选类别，否则适配器会报告歧义而不会静默复制检测框。

---

上一篇：[C++ 接入](cpp.md) · 下一篇：[Android 接入](android.md)
