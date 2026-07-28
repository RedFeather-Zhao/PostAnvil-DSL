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
					IFEND
				IFEND
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
				FOREND
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
				FOREND
				IF cls.count == 0
					RETURN 0
				ELSE
					return total / cls.count
				IFEND
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
					FOREND
				FOREND
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

	tests.emplace_back(
		"INST 参数接收 self 并读取实例属性",
		R"(
			RULE FUNC copy_conf(item:INST) -> NUM:
				INST current_self = self
				INST current_arg = item
				IF current_self.conf == current_arg.conf
					RETURN current_arg.conf
				ELSE
					RETURN 0
				IFEND
			RULEEND

			RULE ATTR "person":
				self.copied_conf = copy_conf(self)
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {
				Instance("PERSON",0,0,10,10,0.9),
				Instance("PERSON",0,0,10,10,0.6),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_prop(res, "PERSON", 0, "COPIED_CONF", 0.9) &&
				check_prop(res, "PERSON", 1, "COPIED_CONF", 0.6);
			if (!ok) err = "INST 参数读取到的置信度不匹配";
			return ok;
		});

	tests.emplace_back(
		"FOR 实例可赋给 INST 局部变量并传递",
		R"(
			RULE FUNC read_conf(item:INST) -> NUM:
				RETURN item.conf
			RULEEND

			RULE FUNC max_conf(cls:STR) -> NUM:
				NUM best = 0
				FOR obj IN cls
					INST current = obj
					IF read_conf(current) > best
						best = read_conf(current)
					IFEND
				FOREND
				RETURN best
			RULEEND

			RULE ATTR "car":
				"car".max_conf = max_conf("car")
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {
				Instance("CAR",0,0,10,10,0.5),
				Instance("CAR",0,0,10,10,0.95),
				Instance("CAR",0,0,10,10,0.7),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_class_prop(res, "CAR", "MAX_CONF", 0.95);
			if (!ok) err = "通过 INST 局部变量计算的最大置信度不匹配";
			return ok;
		});

	tests.emplace_back(
		"函数返回 INST 并保存为全局变量",
		R"(
			RULE FUNC first_inst(cls:STR) -> INST:
				FOR obj IN cls
					INST selected = obj
					RETURN selected
				FOREND
				RETURN self
			RULEEND

			INST anchor = first_inst("person")

			RULE FILTER "person":
				self.conf >= anchor.conf
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {
				Instance("PERSON",0,0,10,10,0.75),
				Instance("PERSON",0,0,10,10,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_count(res, "PERSON", 1);
			if (!ok) err = "全局 INST 变量的属性过滤结果不匹配";
			return ok;
		});

	tests.emplace_back(
		"显式动态属性访问 (_inst.(_prop))",
		R"(
			RULE FUNC fn_avg(_cls:STR, _prop:STR) -> NUM:
				NUM _sum = 0
				FOR _inst IN _cls
					_sum = _sum + _inst.(_prop)
				FOREND
				RETURN _sum / _cls.count
			RULEEND

			NUM avg_conf = fn_avg("person", "conf")
			NUM avg_area = fn_avg("person", "area")

			RULE ATTR "person":
				"person".avg_conf = avg_conf
				"person".avg_area = avg_area
			RULEEND
		)",
		[]() -> Scene {
			return Scene({ 200,200 }, {
				Instance("PERSON",0,0,10,10,0.9),
				Instance("PERSON",0,0,20,20,0.7),
				Instance("PERSON",0,0,30,30,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_class_prop(res, "PERSON", "AVG_CONF", 0.7) &&
				check_class_prop(res, "PERSON", "AVG_AREA", 1400.0 / 3.0);
			if (!ok) err = "动态属性平均值不匹配";
			return ok;
		});

	return tests;
}
