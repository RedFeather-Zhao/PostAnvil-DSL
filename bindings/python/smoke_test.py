import postanvil


source = """
IMPORT INST anchor
RULE FILTER "global" {
    self.conf >= 0.5
}
EXPORT anchor AS selected_anchor
"""

scene = postanvil.Scene(postanvil.Image(100, 100))
anchor = scene.inst_add(postanvil.Instance(0, 0, 10, 10, 0.8))
second = scene.inst_add(postanvil.Instance(0, 0, 10, 10, 0.2))
scene.cls_add_inst("person", anchor)
scene.cls_add_inst("person", second)
scene.io_import("anchor", anchor)

assert anchor.id == 1
assert anchor.cls_name is None
assert scene.cls_add_inst("selected", anchor)
assert not scene.cls_add_inst("selected", anchor)
assert scene.cls_insts("selected") == [anchor.id]
assert scene.cls_instances("selected")[0].id == anchor.id
assert scene.cls_handles("selected")[0].cls_name == "SELECTED"
assert "SELECTED" in scene.cls_names()

by_id = scene.inst_handle(anchor.id)
assert by_id.cls_name is None
scene.inst_set_prop(by_id, "reviewed", True)
assert scene.inst_prop(by_id, "reviewed") is True

result = postanvil.compile(source).evaluate(scene)

assert result.cls_inst_count("PERSON") == 1
assert result.inst_count == 2
assert result.io_export("selected_anchor") == anchor
assert result.inst_prop(result.cls_inst_at("person", 1), "cls") == "PERSON"
print(f"PostAnvil {postanvil.__version__}: Python smoke test passed")
