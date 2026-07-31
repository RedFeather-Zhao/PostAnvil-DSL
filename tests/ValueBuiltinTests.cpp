#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(StringConcatenationAndGlobalReference)
	{
		auto output = evaluate_and_expect_counts(R"(
				NUM threshold = 0.5
				RULE FUNC get_prefix() -> STR:
					"class_"
				RULEEND
				STR label = get_prefix() + "person"
				RULE FILTER "global":
					self.conf > threshold
				RULEEND
				EXPORT label AS generated_label
			)",
			make_confidence_scene("PERSON", { 0.9, 0.3 }),
			{ { "PERSON", 1 } }
		);

		Assert::AreEqual(
			std::string("class_person"),
			output.get_export("generated_label").as_str());
	}

	PA_TEST(NormalizedProperties)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "obj":
				self.wn > 0.1
				self.hn > 0.1
				self.x1n > 0
				self.y1n > 0
				self.x2n < 1.0
				self.y2n < 1.0
				self.arean > 0.01
			RULEEND
		)", make_scene({
			Instance("OBJ", 10, 10, 60, 30, 0.5),
			Instance("OBJ", 5, 5, 5, 5, 0.5),
			Instance("OBJ", 0, 0, 200, 100, 0.5)
		}, { 200, 100 }), { { "OBJ", 1 } });
	}

	PA_TEST(CustomClassProperties)
	{
		auto output = evaluate(R"(
			NUM test_val = 0.5
			RULE ATTR "car":
				"car".avg_conf = test_val
				"car".total_area = 400 * 2 / 2
			RULEEND
		)", make_confidence_scene("CAR", { 0.9, 0.5 }));

		expect_class_num(output, "CAR", "AVG_CONF", 0.5);
		expect_class_num(output, "CAR", "TOTAL_AREA", 400.0);
	}

	PA_TEST(StringVariableAsClassExpression)
	{
		evaluate_and_expect_counts(R"(
			STR target = "animal"
			RULE FILTER target:
				self.conf > 0.7
			RULEEND
		)", make_scene({
			Instance("ANIMAL", 0, 0, 10, 10, 0.9),
			Instance("ANIMAL", 0, 0, 10, 10, 0.5),
			Instance("CAR", 0, 0, 10, 10, 0.9)
		}), { { "ANIMAL", 1 }, { "CAR", 1 } });
	}

	PA_TEST(GlobalNumericVariables)
	{
		evaluate_and_expect_counts(R"(
			NUM min_conf = 0.6
			NUM min_w = 15
			RULE FILTER "global":
				self.conf > min_conf
				self.w > min_w
			RULEEND
		)", make_scene({
			Instance("A", 0, 0, 20, 20, 0.7),
			Instance("A", 0, 0, 20, 20, 0.5),
			Instance("A", 0, 0, 10, 20, 0.7)
		}), { { "A", 1 } });
	}

	PA_TEST(GlobalBooleanVariable)
	{
		evaluate_and_expect_counts(R"(
			BOOL debug = FALSE
			RULE FILTER "global":
				debug == FALSE
				self.conf > 0.5
			RULEEND
		)", make_confidence_scene("A", { 0.9, 0.3 }), { { "A", 1 } });
	}

	PA_TEST(MathAndSpatialBuiltins)
	{
		auto output = evaluate(R"(
			INST first = _INST_INDEX("box", 1)
			INST second = _INST_ID(2)
			INST inner = _INST_ID(3)
			RULE ATTR "box":
				"box".math = _SQRT(9) + _ABS(-2) + _POW(2, 3) + _MIN(4, 5) + _MAX(6, 5)
				"box".rounding = _FLOOR(1.9) + _CEIL(1.1) + _ROUND(1.5)
				"box".logs = _LOG(1) + _EXP(0) + _LOG10(100)
				"box".clamped = _CLAMP(12, 0, 10)
				"box".intersection = _INTER_AREA(first, second)
				"box".iou = _IOU(first, second)
				"box".over_a = _OVERLAP_A(first, second)
				"box".over_b = _OVERLAP_B(first, second)
				"box".distance = _DISTANCE(first, second)
				"box".overlapping = _OVERLAPS(first, second)
				"box".contained = _CONTAINS(inner, first)
				"box".nearby = _NEARBY(first, second, 10)
			RULEEND
		)", make_scene({
			Instance("BOX", 0, 0, 10, 10, 0.9),
			Instance("BOX", 5, 0, 20, 10, 0.8),
			Instance("BOX", 2, 2, 2, 2, 0.7)
		}));

		expect_class_num(output, "BOX", "MATH", 23.0);
		expect_class_num(output, "BOX", "ROUNDING", 5.0);
		expect_class_num(output, "BOX", "LOGS", 3.0);
		expect_class_num(output, "BOX", "CLAMPED", 10.0);
		expect_class_num(output, "BOX", "INTERSECTION", 50.0);
		expect_class_num(output, "BOX", "IOU", 0.2);
		expect_class_num(output, "BOX", "OVER_A", 0.5);
		expect_class_num(output, "BOX", "OVER_B", 0.25);
		expect_class_num(output, "BOX", "DISTANCE", 10.0);
		expect_class_bool(output, "BOX", "OVERLAPPING", true);
		expect_class_bool(output, "BOX", "CONTAINED", true);
		expect_class_bool(output, "BOX", "NEARBY", true);
	}

	PA_TEST(InstanceIdentityAndLookup)
	{
		auto output = evaluate_and_expect_counts(R"(
			INST selected_by_id = _INST_ID(2)
			INST selected_by_index = _INST_INDEX("person", 2)
			RULE FILTER "person":
				self.id == selected_by_id.id
				self.id == selected_by_index.id
			RULEEND
			RULE ATTR "person":
				self.saved_id = self.id
				self.saved_index = self.index
				self.saved_cls = self.cls
			RULEEND
		)", make_confidence_scene("PERSON", { 0.4, 0.8, 0.6 }),
			{ { "PERSON", 1 } });

		expect_num_prop(output, "PERSON", 0, "SAVED_ID", 2.0);
		expect_num_prop(output, "PERSON", 0, "SAVED_INDEX", 1.0);
		expect_str_prop(output, "PERSON", 0, "SAVED_CLS", "PERSON");
	}

	PA_TEST(WritableBuiltinInstanceProperties)
	{
		auto output = evaluate(R"(
			RULE ATTR "box":
				self.x1 = 3
				self.y1 = 4
				self.w = 20
				self.h = 30
				self.conf = 0.75
			RULEEND
		)", make_confidence_scene("BOX", { 0.5 }));

		const auto& box = instance_at(output, "BOX");
		Assert::AreEqual(3.0, box.x1());
		Assert::AreEqual(4.0, box.y1());
		Assert::AreEqual(20.0, box.w());
		Assert::AreEqual(30.0, box.h());
		Assert::AreEqual(0.75, box.conf());
	}

	PA_TEST(MissingClassesBehaveAsEmptyCollections)
	{
		auto output = evaluate_and_expect_counts(R"(
			RULE FUNC count_missing(cls: STR) -> NUM:
				NUM total = 0
				FOR item IN cls
					total = total + 1
				FOREND
				RETURN total
			RULEEND
			NUM missing_count = "missing".count
			NUM iterated_count = count_missing("missing")
			RULE GROUP "empty_group" FROM "missing":
				TRUE
			RULEEND
			RULE APPEND "empty_group" FROM "also_missing":
				TRUE
			RULEEND
			RULE ATTR "person":
				self.empty_total = missing_count + iterated_count + "empty_group".count
			RULEEND
		)", make_confidence_scene("PERSON", { 0.9 }),
			{ { "PERSON", 1 }, { "EMPTY_GROUP", 0 } });

		expect_num_prop(output, "PERSON", 0, "EMPTY_TOTAL", 0.0);
	}

} // namespace UnitTest1Basic
