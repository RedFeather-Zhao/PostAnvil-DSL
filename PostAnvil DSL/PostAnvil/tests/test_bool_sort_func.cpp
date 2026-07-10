#include "test_common.hpp"

std::vector<TestCase> get_bool_sort_func_tests() {
    std::vector<TestCase> tests;

    tests.push_back({
        "布尔字面量 FALSE (过滤全部)",
        R"(
            RULE FILTER "global":
                FALSE
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,10,10,0.9),
                Instance("A",0,0,10,10,0.6),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 0);
            if (!ok) {
                int cnt = res.objects.count("A") ? (int)res.objects.at("A").size() : 0;
                err = "期望 A=0, 实际 A=" + std::to_string(cnt);
            }
            return ok;
        }
        });

    tests.push_back({
        "布尔字面量 TRUE (保留全部)",
        R"(
            RULE FILTER "global":
                TRUE
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,10,10,0.9),
                Instance("A",0,0,10,10,0.6),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 2);
            if (!ok) {
                int cnt = res.objects.count("A") ? (int)res.objects.at("A").size() : 0;
                err = "期望 A=2, 实际 A=" + std::to_string(cnt);
            }
            return ok;
        }
        });

    tests.push_back({
        "SORT 排序原语 (保留面积最大的实例)",
        R"(
            RULE FILTER "person":
                self.area >= SORT("person", self.area, 1)
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.5),
                Instance("PERSON",0,0,20,20,0.5),
                Instance("PERSON",0,0,30,30,0.5),
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
        "SORT 负排名升序 (保留面积最小的实例)",
        R"(
            RULE FILTER "person":
                self.area <= SORT("person", self.area, -1)
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.5),
                Instance("PERSON",0,0,20,20,0.5),
                Instance("PERSON",0,0,30,30,0.5),
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
        "FUNC 返回常量 TRUE (保留全部)",
        R"(
            RULE FUNC always_true() -> BOOL:
                TRUE
            RULEEND

            RULE FILTER "global":
                always_true()
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,10,10,0.9),
                Instance("B",0,0,10,10,0.3),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 1) && check_count(res, "B", 1);
            if (!ok) err = "期望 A=1, B=1";
            return ok;
        }
        });

    tests.push_back({
        "FUNC 返回常量 FALSE (过滤全部)",
        R"(
            RULE FUNC always_false() -> BOOL:
                FALSE
            RULEEND

            RULE FILTER "global":
                always_false()
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("A",0,0,10,10,0.9),
                Instance("B",0,0,10,10,0.3),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "A", 0) && check_count(res, "B", 0);
            if (!ok) err = "期望 A=0, B=0";
            return ok;
        }
        });

    return tests;
}