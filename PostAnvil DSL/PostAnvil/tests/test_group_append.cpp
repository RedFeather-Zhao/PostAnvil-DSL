#include "test_common.hpp"

std::vector<TestCase> get_group_append_tests() {
    std::vector<TestCase> tests;

    tests.push_back({
        "GROUP 创建新类别 (large_car = area > 5000)",
        R"(
            RULE GROUP "large_car" FROM "car":
                self.area > 5000
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("CAR",0,0,100,60,0.5),
                Instance("CAR",0,0,50,50,0.5),
                Instance("CAR",0,0,80,80,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "LARGE_CAR", 2) && check_count(res, "CAR", 3);
            if (!ok) {
                int c = res.objects.count("CAR") ? (int)res.objects.at("CAR").size() : 0;
                int l = res.objects.count("LARGE_CAR") ? (int)res.objects.at("LARGE_CAR").size() : 0;
                err = "期望 CAR=3, LARGE_CAR=2，实际 CAR=" + std::to_string(c) + ", LARGE_CAR=" + std::to_string(l);
            }
            return ok;
        }
        });

    tests.push_back({
        "APPEND 追加实例 (vip = conf > 0.9)",
        R"(
            RULE APPEND "vip" FROM "person":
                self.conf > 0.9
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.95),
                Instance("PERSON",0,0,10,10,0.85),
                Instance("PERSON",0,0,10,10,0.91),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "VIP", 2) && check_count(res, "PERSON", 3);
            if (!ok) {
                int p = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
                int v = res.objects.count("VIP") ? (int)res.objects.at("VIP").size() : 0;
                err = "期望 PERSON=3, VIP=2，实际 PERSON=" + std::to_string(p) + ", VIP=" + std::to_string(v);
            }
            return ok;
        }
        });

    tests.push_back({
        "GROUP + FILTER 组合 (先分组再过滤)",
        R"(
            RULE GROUP "big" FROM "item":
                self.w > 30
            RULEEND

            RULE FILTER "big":
                self.h > 20
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("ITEM",0,0,40,30,0.5),
                Instance("ITEM",0,0,35,15,0.5),
                Instance("ITEM",0,0,20,40,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "BIG", 1) && check_count(res, "ITEM", 3);
            if (!ok) {
                int i = res.objects.count("ITEM") ? (int)res.objects.at("ITEM").size() : 0;
                int b = res.objects.count("BIG") ? (int)res.objects.at("BIG").size() : 0;
                err = "期望 ITEM=3, BIG=1，实际 ITEM=" + std::to_string(i) + ", BIG=" + std::to_string(b);
            }
            return ok;
        }
        });

    tests.push_back({
        "类属性 — \"person\".count > 0",
        R"(
            RULE GROUP "big" FROM "person":
                self.w > 30
            RULEEND

            RULE FILTER "big":
                "person".count > 0
            RULEEND
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,40,30,0.5),
                Instance("PERSON",0,0,20,20,0.5),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "BIG", 1) && check_count(res, "PERSON", 2);
            if (!ok) {
                int p = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
                int b = res.objects.count("BIG") ? (int)res.objects.at("BIG").size() : 0;
                err = "期望 PERSON=2, BIG=1，实际 PERSON=" + std::to_string(p) + ", BIG=" + std::to_string(b);
            }
            return ok;
        }
        });

    return tests;
}