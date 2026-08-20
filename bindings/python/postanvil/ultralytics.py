"""Adapters between Ultralytics detection results and PostAnvil scenes.

The module deliberately avoids importing Ultralytics at import time.  Users who
need this integration can install the optional dependency with
``pip install postanvil[ultralytics]``; normal PostAnvil use remains independent
of Ultralytics and PyTorch.
"""

from __future__ import annotations

from collections.abc import Mapping
from typing import Any

from ._postanvil import ALL_INST, Image, Instance, PARuntimeError, Scene


_TRACK_ID_PROPERTY = "YOLO_TRACK_ID"
_CLASS_ID_PROPERTY = "YOLO_CLASS_ID"
_UNSUPPORTED_RESULT_FIELDS = (
    "masks",
    "keypoints",
    "obb",
    "probs",
    "semantic_mask",
    "depth",
)


def _names_dict(names: Any) -> dict[int, str]:
    if isinstance(names, Mapping):
        return {int(class_id): str(name) for class_id, name in names.items()}
    return {class_id: str(name) for class_id, name in enumerate(names)}


def _tolist(value: Any) -> list[Any]:
    if hasattr(value, "tolist"):
        return value.tolist()
    return list(value)


def _require_detection_result(result: Any) -> None:
    if not hasattr(result, "orig_shape") or not hasattr(result, "names"):
        raise TypeError("Expected an Ultralytics Results-like object")

    boxes = getattr(result, "boxes", None)
    if boxes is None and any(
        getattr(result, field, None) is not None
        for field in _UNSUPPORTED_RESULT_FIELDS
    ):
        raise ValueError(
            "Only axis-aligned object-detection results are supported; "
            "classification, segmentation, pose, OBB, semantic-mask, and "
            "depth results require task-specific adapters"
        )


def _require_user_class_name(name: str) -> None:
    if name.casefold() == ALL_INST.casefold():
        raise ValueError(
            f"Ultralytics class name {name!r} conflicts with the reserved "
            f"PostAnvil built-in class {ALL_INST!r}"
        )


def from_ultralytics(result: Any) -> Scene:
    """Convert one Ultralytics detection ``Results`` object to a Scene.

    Coordinates are read from ``boxes.xyxy`` because PostAnvil stores the
    top-left corner plus width and height.  Tracking IDs, when present, are
    retained as the numeric dynamic property ``YOLO_TRACK_ID``.  The original
    YOLO class ID is retained as ``YOLO_CLASS_ID`` so that a scene in which one
    instance belongs to multiple PostAnvil classes can still be written back
    to YOLO deterministically.
    """

    _require_detection_result(result)
    height, width = result.orig_shape
    scene = Scene(
        Image(float(width), float(height), str(getattr(result, "path", "") or ""))
    )

    if result.boxes is None:
        return scene

    boxes = result.boxes.cpu()
    names = _names_dict(result.names)
    coordinates = _tolist(boxes.xyxy)
    confidences = _tolist(boxes.conf)
    class_ids = _tolist(boxes.cls)

    track_ids: list[Any] | None = None
    if bool(getattr(boxes, "is_track", False)) and boxes.id is not None:
        track_ids = _tolist(boxes.id)

    if not (len(coordinates) == len(confidences) == len(class_ids)):
        raise ValueError("Ultralytics box coordinates, confidence, and class arrays differ in length")
    if track_ids is not None and len(track_ids) != len(coordinates):
        raise ValueError("Ultralytics tracking IDs and boxes differ in length")

    for index, (xyxy, confidence, raw_class_id) in enumerate(
        zip(coordinates, confidences, class_ids)
    ):
        if len(xyxy) != 4:
            raise ValueError("Each Ultralytics box must contain x1, y1, x2, and y2")

        class_id = int(raw_class_id)
        if class_id not in names:
            raise ValueError(f"Ultralytics class ID {class_id} is missing from result.names")
        _require_user_class_name(names[class_id])

        x1, y1, x2, y2 = (float(value) for value in xyxy)
        instance = Instance(
            x1,
            y1,
            x2 - x1,
            y2 - y1,
            float(confidence),
        )
        instance.set_property(_CLASS_ID_PROPERTY, float(class_id))
        if track_ids is not None:
            instance.set_property(_TRACK_ID_PROPERTY, float(track_ids[index]))
        handle = scene.inst_add(instance)
        scene.cls_add_inst(names[class_id], handle)

    return scene


def _reject_unsynchronised_tasks(result: Any) -> None:
    populated = [
        field
        for field in _UNSUPPORTED_RESULT_FIELDS
        if getattr(result, field, None) is not None
    ]
    if populated:
        fields = ", ".join(populated)
        raise ValueError(
            f"Cannot write PostAnvil boxes back while Results contains {fields}; "
            "updating boxes alone would desynchronise task-specific data"
        )


def update_ultralytics(
    result: Any,
    scene: Scene,
    *,
    allow_new_classes: bool = False,
) -> Any:
    """Update an Ultralytics detection result from a PostAnvil scene.

    The supplied ``result`` is updated in place and returned.  Dynamic and
    class-level PostAnvil properties remain in ``scene`` because the native
    Ultralytics box tensor has no fields for them.
    """

    _require_detection_result(result)
    _reject_unsynchronised_tasks(result)
    if result.boxes is None:
        raise ValueError("Cannot update a Results object whose boxes field is None")

    names = _names_dict(result.names)
    name_to_id = {name.casefold(): class_id for class_id, name in names.items()}
    next_class_id = max(names, default=-1) + 1
    tracked = bool(getattr(result.boxes, "is_track", False))
    rows: list[list[float]] = []

    # PostAnvil 允许同一实例 ID 出现在多个类别中，YOLO 的一行结果则只能属于
    # 一个类别。优先保留适配器记录的原始 YOLO 类别；若该关系已被过滤，必须
    # 只剩一个输出类别。
    # 按选中类别的列表输出，以保留 SORT 顺序并避免 GROUP/APPEND 重复输出。
    instances_by_class = {
        str(cls_name): list(scene.cls_instances(cls_name))
        for cls_name in scene.cls_names()
    }
    instances_by_id: dict[int, Any] = {}
    cls_names_by_id: dict[int, list[str]] = {}
    for cls_name, instances in instances_by_class.items():
        for instance in instances:
            instance_id = int(instance.id)
            instances_by_id.setdefault(instance_id, instance)
            cls_names_by_id.setdefault(instance_id, []).append(cls_name)

    selected_cls_name: dict[int, str] = {}
    for instance_id, cls_names in cls_names_by_id.items():
        instance = instances_by_id[instance_id]
        try:
            original_class_id = int(instance.get_property(_CLASS_ID_PROPERTY))
        except PARuntimeError:
            original_class_id = None
        original_cls_name = names.get(original_class_id)
        original_match = next(
            (
                cls_name
                for cls_name in cls_names
                if original_cls_name is not None
                and cls_name.casefold() == original_cls_name.casefold()
            ),
            None,
        )
        if original_match is not None:
            selected_cls_name[instance_id] = original_match
        elif len(cls_names) == 1:
            selected_cls_name[instance_id] = cls_names[0]
        else:
            rendered = ", ".join(repr(cls_name) for cls_name in cls_names)
            raise ValueError(
                f"PostAnvil instance id {instance_id} belongs to multiple derived "
                f"classes ({rendered}), but YOLO can store only one class; keep "
                "the original YOLO-class membership or reduce it to one output class"
            )

    for cls_name, instances in instances_by_class.items():
        for instance in instances:
            instance_id = int(instance.id)
            if selected_cls_name[instance_id] != cls_name:
                continue

            lookup_name = cls_name.casefold()
            class_id = name_to_id.get(lookup_name)
            if class_id is None:
                if not allow_new_classes:
                    raise ValueError(
                        f"PostAnvil produced class {cls_name!r}, which is absent "
                        "from result.names; pass allow_new_classes=True to assign an ID"
                    )
                class_id = next_class_id
                next_class_id += 1
                names[class_id] = cls_name
                name_to_id[lookup_name] = class_id

            row = [
                float(instance.x),
                float(instance.y),
                float(instance.x2),
                float(instance.y2),
            ]
            if tracked:
                try:
                    track_id = float(instance.get_property(_TRACK_ID_PROPERTY))
                except PARuntimeError as error:
                    raise ValueError(
                        "A tracked Ultralytics result contains an instance without "
                        f"the {_TRACK_ID_PROPERTY} property"
                    ) from error
                row.append(track_id)
            row.extend((float(instance.confidence), float(class_id)))
            rows.append(row)

    source_data = result.boxes.data
    column_count = 7 if tracked else 6
    if rows:
        new_boxes = source_data.new_tensor(rows)
    else:
        new_boxes = source_data.new_empty((0, column_count))

    result.names = names
    result.update(boxes=new_boxes)
    return result


def apply_ultralytics(
    program: Any,
    result: Any,
    *,
    imports: Mapping[str, Any] | None = None,
    allow_new_classes: bool = False,
) -> Any:
    """Evaluate a compiled PostAnvil program and update one YOLO result."""

    scene = from_ultralytics(result)
    if imports:
        for name, value in imports.items():
            scene.io_import(str(name), value)
    output = program.evaluate(scene)
    return update_ultralytics(
        result,
        output,
        allow_new_classes=allow_new_classes,
    )
