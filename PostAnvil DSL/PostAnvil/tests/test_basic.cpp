#include "test_common.hpp"
#include <format>

std::vector<TestCase> get_basic_tests() {
    std::vector<TestCase> tests;

    tests.emplace_back(
        "Basic Test 1: 单条件，全局过滤",
        R"(
            RULE FILTER "global":
                self.conf > 0.5
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("A", 0, 0, 10, 10, 0.9),
                Instance("A", 0, 0, 10, 10, 0.6),
                Instance("A", 0, 0, 10, 10, 0.4),
                Instance("A", 0, 0, 10, 10, 0.2),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("A") || res.objects.at("A").size() != 2) {
                int cnt = res.objects.contains("A") ? (int)res.objects.at("A").size() : 0;
                err = std::format("期望 A 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "全局多条件：尺寸+面积 (w>10, h>10, area>200)",
        R"(
            RULE FILTER "global":
                self.w > 10
                self.h > 10
                self.area > 200
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("B", 0, 0, 20, 30, 0.5),
                Instance("B", 0, 0, 5, 5, 0.5),
                Instance("B", 0, 0, 15, 15, 0.5),
                Instance("B", 0, 0, 10, 15, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("B") || res.objects.at("B").size() != 2) {
                int cnt = res.objects.contains("B") ? (int)res.objects.at("B").size() : 0;
                err = std::format("期望 B 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "比较运算符 (>=, <=, !=)",
        R"(
            RULE FILTER "c":
                self.x1 >= 50
                self.x1 <= 100
                self.x1 != 75
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("C", 10, 0, 10, 10, 0.5),
                Instance("C", 50, 0, 10, 10, 0.5),
                Instance("C", 100, 0, 10, 10, 0.5),
                Instance("C", 200, 0, 10, 10, 0.5),
                Instance("C", 75, 0, 10, 10, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("C") || res.objects.at("C").size() != 2) {
                int cnt = res.objects.contains("C") ? (int)res.objects.at("C").size() : 0;
                err = std::format("期望 C 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "算术加法 + 一元取负 (x1+w>100, -y1>-100)",
        R"(
            RULE FILTER "d":
                self.x1 + self.w > 100
                -self.y1 > -100
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("D", 10, 50, 20, 10, 0.5),
                Instance("D", 50, 50, 200, 10, 0.5),
                Instance("D", 100, 150, 10, 10, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("D") || res.objects.at("D").size() != 1) {
                int cnt = res.objects.contains("D") ? (int)res.objects.at("D").size() : 0;
                err = std::format("期望 D 有 1 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "乘法 (w * h > 300)",
        R"(
            RULE FILTER "e":
                self.w * self.h > 300
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("E", 0, 0, 20, 30, 0.5),
                Instance("E", 0, 0, 10, 10, 0.5),
                Instance("E", 0, 0, 15, 15, 0.5),
                Instance("E", 0, 0, 5, 20, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("E") || res.objects.at("E").size() != 1) {
                int cnt = res.objects.contains("E") ? (int)res.objects.at("E").size() : 0;
                err = std::format("期望 E 有 1 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "除法 (x1 / w < 2)",
        R"(
            RULE FILTER "e2":
                self.x1 / self.w < 2
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("E2", 10, 0, 20, 10, 0.5),
                Instance("E2", 100, 0, 20, 10, 0.5),
                Instance("E2", 30, 0, 30, 10, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("E2") || res.objects.at("E2").size() != 2) {
                int cnt = res.objects.contains("E2") ? (int)res.objects.at("E2").size() : 0;
                err = std::format("期望 E2 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "逻辑 OR + 括号 ((w>100 OR h>100) AND conf>0.5)",
        R"(
            RULE FILTER "f":
                (self.w > 100 OR self.h > 100) AND self.conf > 0.5
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("F", 0, 0, 150, 10, 0.9),
                Instance("F", 0, 0, 10, 150, 0.9),
                Instance("F", 0, 0, 150, 150, 0.3),
                Instance("F", 0, 0, 10, 10, 0.9),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("F") || res.objects.at("F").size() != 2) {
                int cnt = res.objects.contains("F") ? (int)res.objects.at("F").size() : 0;
                err = std::format("期望 F 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "逻辑 NOT (NOT conf < 0.3)",
        R"(
            RULE FILTER "g":
                NOT self.conf < 0.3
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("G", 0, 0, 10, 10, 0.2),
                Instance("G", 0, 0, 10, 10, 0.5),
                Instance("G", 0, 0, 10, 10, 0.8),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("G") || res.objects.at("G").size() != 2) {
                int cnt = res.objects.contains("G") ? (int)res.objects.at("G").size() : 0;
                err = std::format("期望 G 有 2 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "图像属性 (img.w, img.h 边界检查)",
        R"(
            RULE FILTER "h":
                self.x1 + self.w <= img.w
                self.y1 + self.h <= img.h
            RULEEND
        )",
        [] {
            return Scene({ 200, 100 }, {
                Instance("H", 10, 10, 20, 20, 0.5),
                Instance("H", 180, 10, 30, 20, 0.5),
                Instance("H", 10, 80, 20, 30, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("H") || res.objects.at("H").size() != 1) {
                int cnt = res.objects.contains("H") ? (int)res.objects.at("H").size() : 0;
                err = std::format("期望 H 有 1 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "派生属性 cx, cy, x2, aspect",
        R"(
            RULE FILTER "aa":
                self.cx > 50
                self.cy > 50
                self.x2 < 200
                self.aspect >= 1.0
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("AA", 0, 0, 100, 100, 0.5),
                Instance("AA", 41, 0, 20, 20, 0.5),
                Instance("AA", 41, 41, 20, 20, 0.5),
                });
        },
        [](const Scene& res, std::string& err) {
            if (!res.objects.contains("AA") || res.objects.at("AA").size() != 1) {
                int cnt = res.objects.contains("AA") ? (int)res.objects.at("AA").size() : 0;
                err = std::format("期望 AA 有 1 个实例，实际 {}", cnt);
                return false;
            }
            return true;
        }
    );

    tests.emplace_back(
        "多类别 + 全局 + 类别规则组合",
        R"(
            RULE FILTER "global":
                self.conf > 0.5
            RULEEND

            RULE FILTER "person":
                self.w > 20
            RULEEND

            RULE FILTER "vehicle":
                self.w > 100
            RULEEND
        )",
        [] {
            return Scene({ 200, 200 }, {
                Instance("PERSON", 0, 0, 30, 30, 0.9),
                Instance("PERSON", 0, 0, 15, 15, 0.9),
                Instance("PERSON", 0, 0, 30, 30, 0.3),
                Instance("VEHICLE", 0, 0, 150, 50, 0.9),
                Instance("VEHICLE", 0, 0, 80, 50, 0.9),
                Instance("ANIMAL", 0, 0, 10, 10, 0.9),
                });
        },
        [](const Scene& res, std::string& err) {
            bool ok = true;
            int p = 0, v = 0, a = 0;

            if (auto it = res.objects.find("PERSON"); it != res.objects.end()) {
                p = (int)it->second.size();
                if (p != 1) ok = false;
            }
            else {
                ok = false;
            }

            if (auto it = res.objects.find("VEHICLE"); it != res.objects.end()) {
                v = (int)it->second.size();
                if (v != 1) ok = false;
            }
            else {
                ok = false;
            }

            if (auto it = res.objects.find("ANIMAL"); it != res.objects.end()) {
                a = (int)it->second.size();
                if (a != 1) ok = false;
            }
            else {
                ok = false;
            }

            if (!ok) {
                err = std::format("期望 PERSON=1, VEHICLE=1, ANIMAL=1，实际 PERSON={}, VEHICLE={}, ANIMAL={}", p, v, a);
                return false;
            }
            return true;
        }
    );

    return tests;
}