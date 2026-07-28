#include "test_common.hpp"

std::vector<TestCase> get_new_features_tests() {
    std::vector<TestCase> tests;

    tests.emplace_back("字符串拼接与全局变量引用",
        R"(
            NUM threshold = 0.5

            RULE FILTER "global":
                self.conf > threshold
            RULEEND

            RULE FUNC get_prefix() -> STR:
                "class_"
            RULEEND

            RULE FILTER "person":
                TRUE
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.9),
                Instance("PERSON",0,0,10,10,0.3),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "PERSON", 1);
            if (!ok) {
                int cnt = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
                err = "期望 PERSON=1, 实际 PERSON=" + std::to_string(cnt);
            }
            return ok;
        });

    tests.emplace_back("归一化属性 (wn, hn, x1n, y1n, x2n, y2n, arean)",
        R"(
            RULE FILTER "obj":
                self.wn > 0.1
                self.hn > 0.1
                self.x1n > 0
                self.y1n > 0
                self.x2n < 1.0
                self.y2n < 1.0
                self.arean > 0.01
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,100}, {
                Instance("OBJ",10,10,60,30,0.5),
                Instance("OBJ",5,5,5,5,0.5),
                Instance("OBJ",0,0,200,100,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "OBJ", 1);
            if (!ok) {
                int cnt = res.objects.count("OBJ") ? (int)res.objects.at("OBJ").size() : 0;
                err = "期望 OBJ=1, 实际 OBJ=" + std::to_string(cnt);
            }
            return ok;
        });

    tests.emplace_back("自定义类属性 (\"car\".avg_conf, \"car\".total_area)",
        R"(
            NUM test_val = 0.5

            RULE ATTR "car":
                "car".avg_conf = test_val
                "car".total_area = 400 * 2 / 2
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("CAR",0,0,10,10,0.9),
                Instance("CAR",0,0,20,20,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.5) &&
                check_class_prop(res, "CAR", "TOTAL_AREA", 400.0);
            if (!ok) err = "类别属性值不匹配";
            return ok;
        });

    tests.emplace_back("字符串变量作为 class_expr (STR target = \"animal\")",
        R"(
            STR target = "animal"

            RULE FILTER target:
                self.conf > 0.7
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("ANIMAL",0,0,10,10,0.9),
                Instance("ANIMAL",0,0,10,10,0.5),
                Instance("CAR",0,0,10,10,0.9),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "ANIMAL", 1) && check_count(res, "CAR", 1);
            if (!ok) {
                int a = res.objects.count("ANIMAL") ? (int)res.objects.at("ANIMAL").size() : 0;
                int c = res.objects.count("CAR") ? (int)res.objects.at("CAR").size() : 0;
                err = "期望 ANIMAL=1, CAR=1，实际 ANIMAL=" + std::to_string(a) + ", CAR=" + std::to_string(c);
            }
            return ok;
        });

    tests.emplace_back("全局数值变量 (min_conf=0.6, min_w=15)",
        R"(
            NUM min_conf = 0.6
            NUM min_w = 15

            RULE FILTER "global":
                self.conf > min_conf
                self.w > min_w
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,20,20,0.7),
                Instance("A",0,0,20,20,0.5),
                Instance("A",0,0,10,20,0.7),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 1);
            if (!ok) {
                int cnt = res.objects.count("A") ? (int)res.objects.at("A").size() : 0;
                err = "期望 A=1, 实际 A=" + std::to_string(cnt);
            }
            return ok;
        });

    tests.emplace_back("全局布尔变量 (debug == FALSE)",
        R"(
            BOOL debug = FALSE

            RULE FILTER "global":
                debug == FALSE
                self.conf > 0.5
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,10,10,0.9),
                Instance("A",0,0,10,10,0.3),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 1);
            if (!ok) {
                int cnt = res.objects.count("A") ? (int)res.objects.at("A").size() : 0;
                err = "期望 A=1, 实际 A=" + std::to_string(cnt);
            }
            return ok;
        });

    tests.emplace_back("原生数学与检测框空间内置函数",
        R"(
            INST first = _INST_INDEX("box", 1)
            INST second = _INST_ID(2)
            INST inner = _INST_ID(3)

            RULE ATTR "box":
                "box".math = _SQRT(9) + _ABS(-2) + _POW(2, 3) + _MIN(4, 5) + _MAX(6, 5)
                "box".rounding = _FLOOR(1.9) + _CEIL(1.1) + _ROUND(1.5)
                "box".logs = _LOG(1) + _EXP(0) + _LOG10(100)
                "box".clamped = _CLAMP(12, 0, 10)
                "box".intersection = _INTER_AREA(first, second)
                "box".iou = _IOU(first, second)
                "box".over_a = _OVERLAP_A(first, second)
                "box".over_b = _OVERLAP_B(first, second)
                "box".distance = _DISTANCE(first, second)
                "box".overlapping = _OVERLAPS(first, second)
                "box".contained = _CONTAINS(inner, first)
                "box".nearby = _NEARBY(first, second, 10)
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("BOX",0,0,10,10,0.9),
                Instance("BOX",5,0,20,10,0.8),
                Instance("BOX",2,2,2,2,0.7),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_class_prop(res, "BOX", "MATH", 23.0) &&
                check_class_prop(res, "BOX", "ROUNDING", 5.0) &&
                check_class_prop(res, "BOX", "LOGS", 3.0) &&
                check_class_prop(res, "BOX", "CLAMPED", 10.0) &&
                check_class_prop(res, "BOX", "INTERSECTION", 50.0) &&
                check_class_prop(res, "BOX", "IOU", 0.2) &&
                check_class_prop(res, "BOX", "OVER_A", 0.5) &&
                check_class_prop(res, "BOX", "OVER_B", 0.25) &&
                check_class_prop(res, "BOX", "DISTANCE", 10.0) &&
                check_class_prop(res, "BOX", "OVERLAPPING", true) &&
                check_class_prop(res, "BOX", "CONTAINED", true) &&
                check_class_prop(res, "BOX", "NEARBY", true);
            if (!ok) err = "数学或空间内置函数结果不匹配";
            return ok;
        });

    tests.emplace_back("实例 id/index/cls 与按编号获取实例",
        R"(
            INST selected_by_id = _INST_ID(2)
            INST selected_by_index = _INST_INDEX("person", 2)

            RULE FILTER "person":
                self.id == selected_by_id.id
                self.id == selected_by_index.id
            RULEEND

            RULE ATTR "person":
                self.saved_id = self.id
                self.saved_index = self.index
                self.saved_cls = self.cls
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.4),
                Instance("PERSON",10,0,10,10,0.8),
                Instance("PERSON",20,0,10,10,0.6),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "PERSON", 1) &&
                check_prop(res, "PERSON", 0, "SAVED_ID", 2.0) &&
                check_prop(res, "PERSON", 0, "SAVED_INDEX", 1.0) &&
                check_prop(res, "PERSON", 0, "SAVED_CLS", "PERSON");
            if (!ok) err = "实例 id/index/cls 或实例查询结果不匹配";
            return ok;
        });

    tests.emplace_back("可写内置实例属性",
        R"(
            RULE ATTR "box":
                self.x1 = 3
                self.y1 = 4
                self.w = 20
                self.h = 30
                self.conf = 0.75
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("BOX",0,0,10,10,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            const auto& box = res.objects.at("BOX").front();
            const bool ok = box.x1() == 3.0 && box.y1() == 4.0 &&
                box.w() == 20.0 && box.h() == 30.0 && box.conf() == 0.75;
            if (!ok) err = "可写内置属性未正确更新";
            return ok;
        });

    tests.emplace_back("不存在类别按空集合处理",
        R"(
            RULE FUNC count_missing(cls: STR) -> NUM:
                NUM total = 0
                FOR item IN cls
                    total = total + 1
                ENDFOR
                RETURN total
            RULEEND

            NUM missing_count = "missing".count
            NUM iterated_count = count_missing("missing")

            RULE GROUP "empty_group" FROM "missing":
                TRUE
            RULEEND

            RULE APPEND "empty_group" FROM "also_missing":
                TRUE
            RULEEND

            RULE ATTR "person":
                self.empty_total = missing_count + iterated_count + "empty_group".count
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.9),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "PERSON", 1) &&
                check_count(res, "EMPTY_GROUP", 0) &&
                check_prop(res, "PERSON", 0, "EMPTY_TOTAL", 0.0);
            if (!ok) err = "不存在类别没有按空集合处理";
            return ok;
        });

    return tests;
}
