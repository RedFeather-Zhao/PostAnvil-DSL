#include "test_common.hpp"
#include <format>   // 若 test_common.hpp 未包含则需添加

std::vector<TestCase> get_attr_tests() {
	std::vector<TestCase> tests;

	tests.emplace_back(
		"属性算子 — 基本属性计算",
		R"(
		RULE ATTR "person":
			self.risk = self.conf * 2.0
			self.ischild = False
		RULEEND
		)",
		[] {
			return Scene({ 200, 200 }, {
				Instance("PERSON", 0, 0, 20, 30, 0.9),
				Instance("PERSON", 0, 0, 10, 50, 0.5),
			});
		},
		[](const Scene& res, std::string& err) {
			auto it = res.objects.find("PERSON");
			if (it == res.objects.end() || it->second.size() != 2) {
				err = std::format("期望 PERSON 有 2 个实例，实际 {}",
					it == res.objects.end() ? 0 : it->second.size());
				return false;
			}
			const auto& inst0 = it->second[0];
			const auto& inst1 = it->second[1];

			// 验证 risk（使用 init-statement 分别检查）
			if (Val risk0 = inst0.get_prop("RISK"); risk0 != 1.8) {
				err = std::format("risk0 值错误：期望 1.8，实际 {}", risk0.as_num());
				return false;
			}
			if (Val risk1 = inst1.get_prop("RISK"); risk1 != 1.0) {
				err = std::format("risk1 值错误：期望 1.0，实际 {}", risk1.as_num());
				return false;
			}

			// 验证 ischild（布尔类型）
			if (Val child0 = inst0.get_prop("ISCHILD"); child0 != false) {
				err = std::format("child0 值错误：期望 false，实际 {}", child0.as_bool() ? "true" : "false");
				return false;
			}
			if (Val child1 = inst1.get_prop("ISCHILD"); child1 != false) {
				err = std::format("child1 值错误：期望 false，实际 {}", child1.as_bool() ? "true" : "false");
				return false;
			}
			return true;
		}
	);

	tests.emplace_back(
		"属性算子 + 过滤算子组合 (density = conf / (w * h))",
		R"(
			RULE ATTR "person":
				self.density = self.conf / (self.w * self.h)
			RULEEND

			RULE FILTER "person":
				self.density < 0.5
			RULEEND
		)",
		[] {
			return Scene({ 200, 200 }, {
				Instance("PERSON", 0, 0, 20, 30, 0.9),
				Instance("PERSON", 0, 0, 10, 10, 0.5),
				Instance("PERSON", 0, 0, 1, 1, 0.9),
				});
		},
		[](const Scene& res, std::string& err) {
			if (!res.objects.contains("PERSON") || res.objects.at("PERSON").size() != 2) {
				int cnt = res.objects.contains("PERSON") ? (int)res.objects.at("PERSON").size() : 0;
				err = std::format("期望 PERSON 有 2 个实例，实际 {}", cnt);
				return false;
			}
			return true;
		}
	);

	tests.emplace_back(
		"大小写不敏感 (大写 SELF.CONF > 0.5)",
		R"(
			RULE FILTER "global":
				SELF.CONF > 0.5
				SELF.W > 10
			RULEEND
		)",
		[] {
			return Scene({ 200, 200 }, {
				Instance("X", 0, 0, 20, 20, 0.9),
				Instance("X", 0, 0, 5, 5, 0.9),
				Instance("X", 0, 0, 20, 20, 0.3),
				});
		},
		[](const Scene& res, std::string& err) {
			if (!res.objects.contains("X") || res.objects.at("X").size() != 1) {
				int cnt = res.objects.contains("X") ? (int)res.objects.at("X").size() : 0;
				err = std::format("期望 X 有 1 个实例，实际 {}", cnt);
				return false;
			}
			return true;
		}
	);

	tests.emplace_back(
		"全局属性算子 (area_calc = w * h)",
		R"(
			RULE ATTR "global":
				self.area_calc = self.w * self.h
			RULEEND
		)",
		[] {
			return Scene({ 200, 200 }, {
				Instance("CAT", 0, 0, 10, 20, 0.5),
				Instance("DOG", 0, 0, 30, 40, 0.5),
				});
		},
		[](const Scene& res, std::string& err) {
			auto it_cat = res.objects.find("CAT");
			auto it_dog = res.objects.find("DOG");

			if (it_cat == res.objects.end() || it_cat->second.empty()) {
				err = "缺少 CAT 实例";
				return false;
			}
			if (it_dog == res.objects.end() || it_dog->second.empty()) {
				err = "缺少 DOG 实例";
				return false;
			}

			if (Val area_cat = it_cat->second[0].get_prop("AREA_CALC"); area_cat != 200.0) {
				err = std::format("CAT 的 AREA_CALC 错误：期望 200，实际 {}", area_cat.as_num());
				return false;
			}
			if (Val area_dog = it_dog->second[0].get_prop("AREA_CALC"); area_dog != 1200.0) {
				err = std::format("DOG 的 AREA_CALC 错误：期望 1200，实际 {}", area_dog.as_num());
				return false;
			}
			return true;
		}
	);

	return tests;
}