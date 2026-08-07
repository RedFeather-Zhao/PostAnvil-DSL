import postanvil


class FakeArray:
    def __init__(self, values):
        self.values = values

    def tolist(self):
        return self.values


class FakeData:
    def __init__(self, values):
        self.values = values

    def new_tensor(self, values):
        return FakeData(values)

    def new_empty(self, shape):
        return FakeData([])


class FakeBoxes:
    def __init__(self, rows, *, tracked=False):
        self.data = FakeData(rows)
        self.xyxy = FakeArray([row[:4] for row in rows])
        offset = 1 if tracked else 0
        self.conf = FakeArray([row[4 + offset] for row in rows])
        self.cls = FakeArray([row[5 + offset] for row in rows])
        self.is_track = tracked
        self.id = FakeArray([row[4] for row in rows]) if tracked else None

    def cpu(self):
        return self


class FakeResult:
    def __init__(self, rows, *, tracked=False):
        self.orig_shape = (100, 200)
        self.path = "example.jpg"
        self.names = {0: "person", 1: "car"}
        self.boxes = FakeBoxes(rows, tracked=tracked)
        self.masks = None
        self.keypoints = None
        self.obb = None
        self.probs = None
        self.semantic_mask = None
        self.depth = None

    def update(self, *, boxes):
        self.boxes = FakeBoxes(boxes.values, tracked=len(boxes.values[0]) == 7 if boxes.values else False)


program = postanvil.compile(
    '''
    IMPORT NUM min_conf
    RULE FILTER "global":
        self.conf >= min_conf
    RULEEND
    '''
)

result = FakeResult(
    [
        [10, 20, 30, 50, 0.9, 0],
        [40, 10, 60, 20, 0.2, 1],
    ]
)
postanvil.apply_ultralytics(program, result, imports={"MIN_CONF": 0.5})
assert result.boxes.data.values == [[10.0, 20.0, 30.0, 50.0, 0.9, 0.0]]

tracked = FakeResult([[1, 2, 6, 8, 42, 0.8, 0]], tracked=True)
postanvil.apply_ultralytics(program, tracked, imports={"MIN_CONF": 0.5})
assert tracked.boxes.data.values == [[1.0, 2.0, 6.0, 8.0, 42.0, 0.8, 0.0]]

group_program = postanvil.compile(
    '''
    RULE GROUP "selected" FROM "person":
        TRUE
    RULEEND
    '''
)
new_class_result = FakeResult([[1, 2, 6, 8, 0.8, 0]])
try:
    postanvil.apply_ultralytics(group_program, new_class_result)
except ValueError as error:
    assert "allow_new_classes=True" in str(error)
else:
    raise AssertionError("New YOLO classes must require explicit permission")

new_class_result = FakeResult([[1, 2, 6, 8, 0.8, 0]])
postanvil.apply_ultralytics(
    group_program,
    new_class_result,
    allow_new_classes=True,
)
assert "SELECTED" in new_class_result.names.values()

segmentation_result = FakeResult([[1, 2, 6, 8, 0.8, 0]])
segmentation_result.masks = object()
try:
    postanvil.apply_ultralytics(program, segmentation_result, imports={"MIN_CONF": 0.5})
except ValueError as error:
    assert "desynchronise" in str(error)
else:
    raise AssertionError("Task-specific result data must not be silently desynchronised")

print("Ultralytics adapter smoke test passed")
