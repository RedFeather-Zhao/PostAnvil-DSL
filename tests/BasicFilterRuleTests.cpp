#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(FilterTest_1_Conf)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER "global":
					self.conf > 0.5
				RULEEND
			)",
			make_confidence_scene("A", { 0.9, 0.6, 0.4, 0.2 }),
			{ { "A", 2 } }	// 保留两个置信度 > 0.5的实例
		);
	}

	PA_TEST(FilterTest_2_Area_W_H)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER "Global":
					self.w > 10
					self.h > 10
					self.area > 200
				RULEEND
			)",
			make_scene({
				Instance("B", 0, 0, 5, 50, 0.5),
				Instance("B", 0, 0, 50, 5, 0.5),
				Instance("B", 0, 0, 15, 15, 0.5),	// 保留
				Instance("B", 0, 0, 10, 15, 0.5)
			}),
			{ { "B", 1 } }
		);
	}

	PA_TEST(FilterTest_3_X_Y)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER "c":
					self.x1 >= 50
					self.x2 <= 100
					self.y1 >= 40
					self.y2 <= 75
				RULEEND
			)",
			make_scene({
				Instance("A", 100, 110, 10, 10, 0.5),	// 保留
				Instance("C", 50, 65, 10, 10, 0.5),		// 保留
				Instance("C", 100, 60, 10, 10, 0.5),
				Instance("C", 100, 40, 10, 10, 0.5),
				Instance("C", 75, 0, 10, 10, 0.5)
			}),
			{ { "C", 1 }, { "A", 1 } }
		);
	}

	PA_TEST(FilterTest_4_Add_Minus)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "d":
				self.x1 + self.w > 100
				-self.y1 > -100
			RULEEND
		)", make_scene({
			Instance("D", 10, 50, 20, 10, 0.5),
			Instance("D", 50, 50, 200, 10, 0.5),
			Instance("D", 100, 150, 10, 10, 0.5)
		}), { { "D", 1 } });
	}

	PA_TEST(FilterTest_5_Mul_Dev)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "e":
				self.w * self.h > 300
			RULEEND

			RULE FILTER "e2":
				self.x1 / self.w < 2
			RULEEND
		)", make_scene({
			Instance("E", 0, 0, 20, 30, 0.5),
			Instance("E", 0, 0, 10, 10, 0.5),
			Instance("E", 0, 0, 15, 15, 0.5),
			Instance("E", 0, 0, 5, 20, 0.5),
			Instance("E2", 10, 0, 20, 10, 0.5),
			Instance("E2", 100, 0, 20, 10, 0.5),
			Instance("E2", 30, 0, 30, 10, 0.5)
		}), { { "E", 1 }, { "E2", 2 } });
	}

	PA_TEST(FilterTest_6_Or_And)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "f":
				(self.w > 100 OR self.h > 100) AND self.conf > 0.5
			RULEEND
		)", make_scene({
			Instance("F", 0, 0, 150, 10, 0.9),
			Instance("F", 0, 0, 10, 150, 0.9),
			Instance("F", 0, 0, 150, 150, 0.3),
			Instance("F", 0, 0, 10, 10, 0.9)
		}), { { "F", 2 } });
	}

	PA_TEST(FilterTest_7_Not)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "g":
				NOT self.conf < 0.3
			RULEEND
		)", make_confidence_scene("G", { 0.2, 0.5, 0.8 }), { { "G", 2 } });
	}

	PA_TEST(FilterTest_7_Image)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "h":
				self.x1 + self.w <= img.w
				self.y1 + self.h <= img.h
			RULEEND
		)", make_scene({
			Instance("H", 10, 10, 20, 20, 0.5),
			Instance("H", 180, 10, 30, 20, 0.5),
			Instance("H", 10, 80, 20, 30, 0.5)
		}, { 200, 100 }), { { "H", 1 } });
	}

	PA_TEST(FilterTest_8_DerivedProperties)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "aa":
				self.cx > 50
				self.cy > 50
				self.x2 < 200
				self.aspect >= 1.0
			RULEEND
		)", make_scene({
			Instance("AA", 0, 0, 100, 100, 0.5),
			Instance("AA", 41, 0, 20, 20, 0.5),
			Instance("AA", 41, 41, 20, 20, 0.5)
		}), { { "AA", 1 } });
	}

	PA_TEST(FilterTest_8_MultiClass)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "global":
				self.conf > 0.5
			RULEEND
			RULE FILTER "person":
				self.w > 20
			RULEEND
			RULE FILTER "vehicle":
				self.w > 100
			RULEEND
		)", make_scene({
			Instance("PERSON", 0, 0, 30, 30, 0.9),
			Instance("PERSON", 0, 0, 15, 15, 0.9),
			Instance("PERSON", 0, 0, 30, 30, 0.3),
			Instance("VEHICLE", 0, 0, 150, 50, 0.9),
			Instance("VEHICLE", 0, 0, 80, 50, 0.9),
			Instance("ANIMAL", 0, 0, 10, 10, 0.9)
		}), { { "PERSON", 1 }, { "VEHICLE", 1 }, { "ANIMAL", 1 } });
	}

} // namespace UnitTest1Basic
