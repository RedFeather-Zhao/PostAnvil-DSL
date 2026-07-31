#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(InstanceAttributesAndTypedGlobals)
	{
		auto output = evaluate(R"(
			NUM bilibili = 114514
			STR ganbei = "QwQ"
			BOOL are_you_happy = TRUE
			ANY inferred_count = "person".count

			RULE ATTR "person":
				self.risk = self.conf * 2.0
				self.is_child = FALSE
			RULEEND

			bilibili = 514
			EXPORT bilibili AS BiliBili, ganbei AS GanBei
			EXPORT are_you_happy AS YouAreHappy
		)", make_confidence_scene("PERSON", { 0.9, 0.5 }));

		expect_num_prop(output, "PERSON", 0, "RISK", 1.8);
		expect_num_prop(output, "PERSON", 1, "RISK", 1.0);
		expect_bool_prop(output, "PERSON", 0, "IS_CHILD", false);
		expect_export_num(output, "BiliBili", 514.0);
		Assert::AreEqual(std::string("QwQ"), output.get_export("GanBei").as_str());
		Assert::IsTrue(output.get_export("YouAreHappy").as_bool());
	}

	PA_TEST(AttributeThenFilter)
	{
		evaluate_and_expect_counts(R"(
			RULE ATTR "person":
				self.density = self.conf / (self.w * self.h)
			RULEEND
			RULE FILTER "person":
				self.density < 0.5
			RULEEND
		)", make_scene({
			Instance("PERSON", 0, 0, 20, 30, 0.9),
			Instance("PERSON", 0, 0, 10, 10, 0.5),
			Instance("PERSON", 0, 0, 1, 1, 0.9)
		}), { { "PERSON", 2 } });
	}

	PA_TEST(KeywordsAndNamesAreCaseInsensitive)
	{
		evaluate_and_expect_counts(R"(
			rule attr "X":
				"X".test = 1
			ruleend
			RULE FILTER "global":
				SELF.CONF > 0.5
				SELF.W > 10
			RULEEND
		)", make_scene({
			Instance("X", 0, 0, 20, 20, 0.9),
			Instance("X", 0, 0, 5, 5, 0.9),
			Instance("X", 0, 0, 20, 20, 0.3)
		}), { { "X", 1 } });
	}

	PA_TEST(GlobalAttributeRule)
	{
		auto output = evaluate(R"(
			RULE ATTR "global":
				self.area_calc = self.w * self.h
			RULEEND
		)", make_scene({
			Instance("CAT", 0, 0, 10, 20, 0.5),
			Instance("DOG", 0, 0, 30, 40, 0.5)
		}));

		expect_num_prop(output, "CAT", 0, "AREA_CALC", 200.0);
		expect_num_prop(output, "DOG", 0, "AREA_CALC", 1200.0);
	}

	PA_TEST(GroupCreatesDerivedClass)
	{
		evaluate_and_expect_counts(R"(
			RULE GROUP "large_car" FROM "car":
				self.area > 5000
			RULEEND
		)", make_scene({
			Instance("CAR", 0, 0, 100, 60, 0.5),
			Instance("CAR", 0, 0, 50, 50, 0.5),
			Instance("CAR", 0, 0, 80, 80, 0.5)
		}), { { "CAR", 3 }, { "LARGE_CAR", 2 } });
	}

	PA_TEST(AppendCreatesDerivedClass)
	{
		evaluate_and_expect_counts(R"(
			RULE APPEND "vip" FROM "person":
				self.conf > 0.9
			RULEEND
		)", make_confidence_scene("PERSON", { 0.95, 0.85, 0.91 }),
			{ { "PERSON", 3 }, { "VIP", 2 } });
	}

	PA_TEST(GroupThenFilter)
	{
		evaluate_and_expect_counts(R"(
			RULE GROUP "big" FROM "item":
				self.w > 30
			RULEEND
			RULE FILTER "big":
				self.h > 20
			RULEEND
		)", make_scene({
			Instance("ITEM", 0, 0, 40, 30, 0.5),
			Instance("ITEM", 0, 0, 35, 15, 0.5),
			Instance("ITEM", 0, 0, 20, 40, 0.5)
		}), { { "ITEM", 3 }, { "BIG", 1 } });
	}

	PA_TEST(ClassCountProperty)
	{
		evaluate_and_expect_counts(R"(
			RULE GROUP "big" FROM "person":
				self.w > 30
			RULEEND
			RULE FILTER "big":
				"person".count > 0
			RULEEND
		)", make_scene({
			Instance("PERSON", 0, 0, 40, 30, 0.5),
			Instance("PERSON", 0, 0, 20, 20, 0.5)
		}), { { "PERSON", 2 }, { "BIG", 1 } });
	}

} // namespace UnitTest1Basic
