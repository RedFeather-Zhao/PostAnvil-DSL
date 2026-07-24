#include "test_common.hpp"

std::vector<TestCase> get_import_export_tests() {
    std::vector<TestCase> tests;

    tests.push_back({
        "IMPORT 导入宿主变量",
        R"(
            IMPORT NUM external_threshold
            IMPORT STR target_class

            RULE FILTER target_class:
                self.conf > external_threshold
            RULEEND
        )",
        []() -> Scene {
            Scene s({200,200}, {
                Instance("PERSON",0,0,10,10,0.8),
                Instance("PERSON",0,0,10,10,0.4),
                Instance("CAR",0,0,10,10,0.8),
            });
            s.add_import("EXTERNAL_THRESHOLD", Val(0.6));
            s.add_import("TARGET_CLASS", Val("PERSON"));
            return s;
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "PERSON", 1) && check_count(res, "CAR", 1);
            if (!ok) {
                int p = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
                int c = res.objects.count("CAR") ? (int)res.objects.at("CAR").size() : 0;
                err = "期望 PERSON=1, CAR=1，实际 PERSON=" + std::to_string(p) + ", CAR=" + std::to_string(c);
            }
            return ok;
        }
        });

    tests.push_back({
        "IMPORT AS 别名 (host_conf AS conf_threshold)",
        R"(
            IMPORT NUM host_conf AS conf_threshold

            RULE FILTER "global":
                self.conf > conf_threshold
            RULEEND
        )",
        []() -> Scene {
            Scene s({200,200}, {
                Instance("A",0,0,10,10,0.8),
                Instance("A",0,0,10,10,0.3),
            });
            s.add_import("CONF_THRESHOLD", Val(0.6));
            return s;
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
        "EXPORT 导出值精确验证",
        R"(
            RULE ATTR "person":
                self.risk = self.conf * 2.0
            RULEEND

            RULE FILTER "person":
                self.conf > 0.5
            RULEEND

            EXPORT "person".count AS person_count
            EXPORT 1.8 AS max_risk
        )",
        []() -> Scene {
            return Scene({200,200}, {
                Instance("PERSON",0,0,10,10,0.9),
                Instance("PERSON",0,0,10,10,0.6),
                Instance("PERSON",0,0,10,10,0.3),
            });
        },
        [](const Scene& res, std::string& err) -> bool {
            try {
                Val count = res.get_export("person_count");
                Val max_risk = res.get_export("max_risk");
                if (count != 2.0) { err = "person_count 期望 2.0，实际 " + std::to_string(count.as_num()); return false; }
                if (max_risk != 1.8) { err = "max_risk 期望 1.8，实际 " + std::to_string(max_risk.as_num()); return false; }
                return true;
            }
 catch (const std::exception& e) {
  err = e.what();
  return false;
}
}
        });

    tests.push_back({
        "INST 类型 IMPORT / EXPORT",
        R"(
            IMPORT INST anchor

            RULE FILTER "person":
                self.conf >= anchor.conf
            RULEEND

            EXPORT anchor AS selected_anchor
        )",
        []() -> Scene {
            Scene s({200,200}, {
                Instance("PERSON",0,0,10,10,0.9),
                Instance("PERSON",0,0,10,10,0.5),
            });
            s.add_import("ANCHOR", Val(Instance("PERSON",0,0,10,10,0.7)));
            return s;
        },
        [](const Scene& res, std::string& err) -> bool {
            try {
                Val exported = res.get_export("selected_anchor");
                bool ok = check_count(res, "PERSON", 1) &&
                    exported.type() == Type::T_INST &&
                    std::abs(exported.as_inst()->conf() - 0.7) < 1e-6;
                if (!ok) err = "INST 导入、属性读取或导出值不匹配";
                return ok;
            }
            catch (const std::exception& e) {
                err = e.what();
                return false;
            }
        }
        });

    return tests;
}
