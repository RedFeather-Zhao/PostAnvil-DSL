import postanvil


source = """
IMPORT INST anchor
RULE FILTER "global" {
    self.conf >= 0.5
}
EXPORT anchor AS selected_anchor
"""

scene = postanvil.Scene(postanvil.Image(100, 100))
anchor = scene.add("person", postanvil.Instance(0, 0, 10, 10, 0.8))
scene.add("person", postanvil.Instance(0, 0, 10, 10, 0.2))
scene.add_import("anchor", anchor)

assert anchor.id == 1
assert anchor.cls_name == "PERSON"
assert scene.append_to_class("selected", anchor)
assert not scene.append_to_class("selected", anchor)
assert scene.instance_ids("selected") == [anchor.id]
assert scene.instances("selected")[0].id == anchor.id
assert scene.handles("selected")[0].cls_name == "SELECTED"
assert "SELECTED" in scene.class_names()

by_id = scene.get_by_id(anchor.id)
assert by_id.cls_name is None
scene.set_instance_property(by_id, "reviewed", True)
assert scene.get_instance_property(by_id, "reviewed") is True

result = postanvil.compile(source).evaluate(scene)

assert result.count("PERSON") == 1
assert result.instance_count == 2
assert result.get_export("selected_anchor") == anchor
assert result.get_instance_property(result.get_by_index("person", 1), "cls") == "PERSON"
print(f"PostAnvil {postanvil.__version__}: Python smoke test passed")
