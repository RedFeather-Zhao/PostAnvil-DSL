#include "test_common.hpp"

std::vector<TestCase> get_new_features_tests() {
    std::vector<TestCase> tests;

    tests.push_back({
        "字符串拼接与全局变量引用",
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
        }
        });

    tests.push_back({
        "归一化属性 (wn, hn, x1n, y1n, x2n, y2n, arean)",
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
        }
        });

    tests.push_back({
        "自定义类属性 (\"car\".avg_conf, \"car\".total_area)",
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
        }
        });

    tests.push_back({
        "字符串变量作为 class_expr (STR target = \"animal\")",
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
        }
        });

    tests.push_back({
        "全局数值变量 (min_conf=0.6, min_w=15)",
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
        }
        });

    tests.push_back({
        "全局布尔变量 (debug == FALSE)",
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
        }
        });

    return tests;
}