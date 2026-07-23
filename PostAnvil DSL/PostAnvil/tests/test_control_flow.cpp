#include "test_common.hpp"

std::vector<TestCase> get_control_flow_tests() {
	std::vector<TestCase> tests;

	tests.emplace_back(
		"FUNC 带 IF-ELSE 条件分支 (risk_level)",
		R"(
			RULE FUNC risk_level(conf:NUM) -> NUM:
				IF conf > 0.8
					RETURN 3
				ELSE
					IF conf > 0.5
						RETURN 2
					ELSE
						RETURN 1
					ENDIF
				ENDIF
			RULEEND

			RULE ATTR "person":
				self.level = risk_level(self.conf)
			RULEEND

			RULE FILTER "person":
				self.level >= 2
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {
				Instance("PERSON",0,0,10,10,0.9),
				Instance("PERSON",0,0,10,10,0.6),
				Instance("PERSON",0,0,10,10,0.3),
				});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_count(res, "PERSON", 2);
			if (ok) {
				auto it = res.objects.find("PERSON");
				if (it != res.objects.end() && it->second.size() >= 2) {
					ok = check_prop(res, "PERSON", 0, "LEVEL", 3.0) &&
						check_prop(res, "PERSON", 1, "LEVEL", 2.0);
					if (!ok) err = "LEVEL 属性值不匹配";
				}
				else {
					err = "PERSON 实例数不足";
				}
			}
			else {
				int cnt = res.objects.count("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
				err = "期望 PERSON=2, 实际 PERSON=" + std::to_string(cnt);
			}
			return ok;
		});

	tests.emplace_back(
		"FUNC 带 FOR 循环 (avg_conf 聚合计算)",
		R"(
			RULE FUNC avg_conf(cls:STR) -> NUM:
				NUM total = 0
				FOR obj IN cls
					total = total + obj.conf
				ENDFOR
				return total / cls.count
			RULEEND

			RULE ATTR "car":
				"car".avg_conf = avg_conf("car")
			RULEEND
		)",
		[]() {
			return Scene({ 200,200 }, {
				Instance("CAR",0,0,10,10,0.9),
				Instance("CAR",0,0,10,10,0.7),
				Instance("CAR",0,0,10,10,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.7);
			if (!ok) {
				auto it = res.class_props.find("CAR");
				if (it != res.class_props.end()) {
					auto pit = it->second.find("AVG_CONF");
					if (pit != it->second.end()) {
						err = std::format("期望 AVG_CONF=0.7，实际 {}", pit->second.as_num());
					}
					else {
						err = "AVG_CONF 属性不存在";
					}
				}
				else {
					err = "CAR 类别属性不存在";
				}
			}
			return ok;
		});

	tests.emplace_back(
		"FOR 循环遍历空类别 (safe_avg 返回 0)",
		R"(
			RULE FUNC safe_avg(cls:STR) -> NUM:
				NUM total = 0
				FOR obj IN cls
					total = total + obj.conf
				ENDFOR
				IF cls.count == 0
					RETURN 0
				ELSE
					return total / cls.count
				ENDIF
			RULEEND

			RULE ATTR "CAR":
				"CAR".avg_conf = safe_avg("CAR")
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.0);
			if (!ok) {
				auto it = res.class_props.find("CAR");
				if (it != res.class_props.end()) {
					auto pit = it->second.find("avg_conf");
					if (pit != it->second.end()) {
						err = std::format("期望 AVG_CONF=0.0，实际 {}", pit->second.as_num());
					}
					else {
						err = "AVG_CONF 属性不存在";
					}
				}
				else {
					err = "CAR 类别属性不存在";
				}
			}
			return ok;
		});

	tests.emplace_back(
		"嵌套 FOR 循环 (sum_areas 计算所有实例总面积)",
		R"(
			RULE FUNC sum_areas() -> NUM:
				NUM total = 0
				FOR cls IN "global"
					FOR obj IN cls
						total = total + obj.area
					ENDFOR
				ENDFOR
				return total
			RULEEND

			RULE ATTR "global":
				"global".total_area = sum_areas()
			RULEEND
		)",
		[]() -> Scene {
			return Scene({200,200}, {
				Instance("A",0,0,10,10,0.5),
				Instance("A",0,0,20,20,0.5),
				Instance("B",0,0,30,30,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_class_prop(res, "GLOBAL", "TOTAL_AREA", 1400.0);
			if (!ok) {
				auto it = res.class_props.find("GLOBAL");
				if (it != res.class_props.end()) {
					auto pit = it->second.find("TOTAL_AREA");
					if (pit != it->second.end()) {
						err = "期望 TOTAL_AREA=1400.0，实际 " + std::to_string(pit->second.as_num());
					}
					else {
						err = "TOTAL_AREA 属性不存在";
					}
				}
				else {
					err = "GLOBAL 类别属性不存在";
				}
			}
			return ok;
		});

	return tests;
}