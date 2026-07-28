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
		"SORT 规则降序 + index 精确保留第一名",
		R"(
			RULE SORT "person":
				self.area DESC
			RULEEND

			RULE FILTER "person":
				self.index <= 1
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
			bool ok = check_count(res, "PERSON", 1) &&
				res.objects.at("PERSON")[0].area() == 900.0 &&
				res.objects.at("PERSON")[0].id() == 3 &&
				res.objects.at("PERSON")[0].index() == 1;
			if (!ok) {
				err = "期望面积最大且 id=3 的实例排在第一位并被唯一保留";
			}
			return ok;
		}
		});

	tests.push_back({
		"SORT 多关键字稳定排序",
		R"(
			RULE SORT "person":
				self.area ASC
				self.conf DESC
			RULEEND
		)",
		[]() -> Scene {
			return Scene({200,200}, {
				Instance("PERSON",0,0,10,10,0.5),
				Instance("PERSON",10,0,10,10,0.9),
				Instance("PERSON",20,0,20,20,0.8),
				Instance("PERSON",30,0,10,10,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			const auto& people = res.objects.at("PERSON");
			bool ok = people.size() == 4 &&
				people[0].id() == 2 &&  // 面积相同时 conf 较高者优先
				people[1].id() == 1 &&  // 完全同键实例保持原始顺序
				people[2].id() == 4 &&
				people[3].id() == 3;
			for (std::size_t i = 0; ok && i < people.size(); ++i) {
				ok = people[i].index() == i + 1;
			}
			if (!ok) {
				err = "多关键字顺序、稳定性或排序后 index 不匹配";
			}
			return ok;
		}
		});

	tests.push_back({
		"SORT 不存在类别按空集合处理",
		R"(
			RULE SORT "missing":
				self.area DESC
			RULEEND
		)",
		[]() -> Scene {
			return Scene({200,200}, {
				Instance("PERSON",0,0,10,10,0.5),
			});
		},
		[](const Scene& res, std::string& err) -> bool {
			bool ok = check_count(res, "PERSON", 1) && check_count(res, "MISSING", 0);
			if (!ok) err = "不存在类别的 SORT 应为空操作";
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
