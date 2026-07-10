#include "test_common.hpp"

std::vector<TestCase> get_end_to_end_tests() {
    std::vector<TestCase> tests;

    tests.push_back({
        "端到端综合场景 (IMPORT + 全局变量 + ATTR + FILTER + GROUP + EXPORT)",
        R"(
            IMPORT NUM min_conf
            NUM area_threshold = 500

            RULE ATTR "person":
                self.risk = self.conf * 2.0
                self.norm_area = self.arean
            RULEEND

            RULE FILTER "person":
                self.conf > min_conf
                self.area > area_threshold
            RULEEND

            RULE GROUP "high_risk" FROM "person":
                self.risk > 1.0
            RULEEND

            EXPORT "high_risk".count AS high_risk_count
            EXPORT "person".count AS total_person
        )",
        []() -> Scene {
            Scene s({200,200}, {
                Instance("PERSON",0,0,30,20,0.9),
                Instance("PERSON",0,0,20,20,0.6),
                Instance("PERSON",0,0,40,30,0.7),
                Instance("PERSON",0,0,30,20,0.3),
            });
            s.add_import("MIN_CONF", Val(0.5));
            return s;
        },
        [](const Scene& res, std::string& err) -> bool {
            bool ok = check_count(res, "PERSON", 2) && check_count(res, "HIGH_RISK", 2);
            if (!ok) {
                int p = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
                int h = res.objects.count("HIGH_RISK") ? (int)res.objects.at("HIGH_RISK").size() : 0;
                err = "期望 PERSON=2, HIGH_RISK=2，实际 PERSON=" + std::to_string(p) + ", HIGH_RISK=" + std::to_string(h);
            }
            if (ok) {
                try {
                    Val total = res.get_export("total_person");
                    Val high = res.get_export("high_risk_count");
                    if (total != 2.0 || high != 2.0) {
                        err = "EXPORT 值不匹配";
                        ok = false;
                    }
                }
 catch (...) {
  err = "EXPORT 值不存在";
  ok = false;
}
}
return ok;
}
        });

    return tests;
}