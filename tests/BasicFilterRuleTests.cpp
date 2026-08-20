#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(FilterTest_1_Conf)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER @ALL_CLASS {
					self.conf > 0.5	\
						OR self.conf > 0.5
				}
			)",
			make_confidence_scene("A", { 0.9, 0.6, 0.4, 0.2 }),
			{ { "A", 2 } }	// 保留两个置信度 > 0.5的实例
		);
	}

	PA_TEST(FilterTest_2_Area_W_H)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER @ALL_CLASS {
					self.w > 10
					self.h > 10
					self.area > 200
				}
			)",
			make_scene({
				make_instance("B", 0, 0, 5, 50, 0.5),
				make_instance("B", 0, 0, 50, 5, 0.5),
				make_instance("B", 0, 0, 15, 15, 0.5),	// 保留
				make_instance("B", 0, 0, 10, 15, 0.5)
			}),
			{ { "B", 1 } }
		);
	}

	PA_TEST(FilterTest_3_X_Y)
	{
		evaluate_and_expect_counts(R"(
				RULE FILTER "c" {
					self.x1 >= 50
					self.x2 <= 100
					self.y1 >= 40
					self.y2 <= 75
				}
			)",
			make_scene({
				make_instance("A", 100, 110, 10, 10, 0.5),	// 保留
				make_instance("C", 50, 65, 10, 10, 0.5),		// 保留
				make_instance("C", 100, 60, 10, 10, 0.5),
				make_instance("C", 100, 40, 10, 10, 0.5),
				make_instance("C", 75, 0, 10, 10, 0.5)
			}),
			{ { "C", 1 }, { "A", 1 } }
		);
	}

	PA_TEST(FilterTest_4_Add_Minus)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "d"

			{

				self.x1 + self.w > 100

				-self.y1 > -100

			}

		)", make_scene({
			make_instance("D", 10, 50, 20, 10, 0.5),
			make_instance("D", 50, 50, 200, 10, 0.5),
			make_instance("D", 100, 150, 10, 10, 0.5)
		}), { { "D", 1 } });
	}

	PA_TEST(FilterTest_5_Mul_Dev)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "e" {
				self.w * self.h > 300
			}

			RULE FILTER "e2"{
				self.x1 / self.w < 2
			}
		)", make_scene({
			make_instance("E", 0, 0, 20, 30, 0.5),
			make_instance("E", 0, 0, 10, 10, 0.5),
			make_instance("E", 0, 0, 15, 15, 0.5),
			make_instance("E", 0, 0, 5, 20, 0.5),
			make_instance("E2", 10, 0, 20, 10, 0.5),
			make_instance("E2", 100, 0, 20, 10, 0.5),
			make_instance("E2", 30, 0, 30, 10, 0.5)
		}), { { "E", 1 }, { "E2", 2 } });
	}

	PA_TEST(FilterTest_6_Or_And)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "f" {
				(self.w > 100 OR self.h > 100) AND self.conf > 0.5
			}
		)", make_scene({
			make_instance("F", 0, 0, 150, 10, 0.9),
			make_instance("F", 0, 0, 10, 150, 0.9),
			make_instance("F", 0, 0, 150, 150, 0.3),
			make_instance("F", 0, 0, 10, 10, 0.9)
		}), { { "F", 2 } });
	}

	PA_TEST(FilterTest_7_Not)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "g" {
				NOT self.conf < 0.3
			}
		)", make_confidence_scene("G", { 0.2, 0.5, 0.8 }), { { "G", 2 } });
	}

	PA_TEST(FilterTest_7_Image)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "h" {
				self.x1 + self.w <= img.w
				self.y1 + self.h <= img.h
			}
		)", make_scene({
			make_instance("H", 10, 10, 20, 20, 0.5),
			make_instance("H", 180, 10, 30, 20, 0.5),
			make_instance("H", 10, 80, 20, 30, 0.5)
		}, { 200, 100 }), { { "H", 1 } });
	}

	PA_TEST(FilterTest_8_DerivedProperties)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "aa" {
				self.cx > 50
				self.cy > 50
				self.x2 < 200
				self.aspect >= 1.0
			}
		)", make_scene({
			make_instance("AA", 0, 0, 100, 100, 0.5),
			make_instance("AA", 41, 0, 20, 20, 0.5),
			make_instance("AA", 41, 41, 20, 20, 0.5)
		}), { { "AA", 1 } });
	}

	PA_TEST(FilterTest_8_MultiClass)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER @ALL_CLASS {
				self.conf > 0.5
			}
			RULE FILTER "person" {
				self.w > 20
			}
			RULE FILTER "vehicle" {
				self.w > 100
			}
		)", make_scene({
			make_instance("PERSON", 0, 0, 30, 30, 0.9),
			make_instance("PERSON", 0, 0, 15, 15, 0.9),
			make_instance("PERSON", 0, 0, 30, 30, 0.3),
			make_instance("VEHICLE", 0, 0, 150, 50, 0.9),
			make_instance("VEHICLE", 0, 0, 80, 50, 0.9),
			make_instance("ANIMAL", 0, 0, 10, 10, 0.9)
		}), { { "PERSON", 1 }, { "VEHICLE", 1 }, { "ANIMAL", 1 } });
	}

} // namespace UnitTest1Basic
