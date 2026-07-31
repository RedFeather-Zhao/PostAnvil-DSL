#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

TEST_CLASS(ControlFlowTests)
{
public:
	TEST_METHOD(NestedIfElseFunction)
	{
		auto output = evaluate_and_expect_counts(R"(
			RULE FUNC risk_level(conf: NUM) -> NUM:
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
		)", make_confidence_scene("PERSON", { 0.9, 0.6, 0.3 }),
			{ { "PERSON", 2 } });

		expect_num_prop(output, "PERSON", 0, "LEVEL", 3.0);
		expect_num_prop(output, "PERSON", 1, "LEVEL", 2.0);
	}

	TEST_METHOD(ForLoopComputesAverage)
	{
		auto output = evaluate(R"(
			RULE FUNC avg_conf(cls: STR) -> NUM:
				NUM total = 0
				FOR obj IN cls
					total = total + obj.conf
				FOREND
				RETURN total / cls.count
			RULEEND
			RULE ATTR "car":
				"car".avg_conf = avg_conf("car")
			RULEEND
		)", make_confidence_scene("CAR", { 0.9, 0.7, 0.5 }));

		expect_class_num(output, "CAR", "AVG_CONF", 0.7);
	}

	TEST_METHOD(ForLoopOverEmptyClass)
	{
		auto output = evaluate(R"(
			RULE FUNC safe_avg(cls: STR) -> NUM:
				NUM total = 0
				FOR obj IN cls
					total = total + obj.conf
				FOREND
				IF cls.count == 0
					RETURN 0
				ELSE
					RETURN total / cls.count
				IFEND
			RULEEND
			RULE ATTR "car":
				"car".avg_conf = safe_avg("car")
			RULEEND
		)", make_scene({}));

		expect_class_num(output, "CAR", "AVG_CONF", 0.0);
	}

	TEST_METHOD(NestedForLoops)
	{
		auto output = evaluate(R"(
			RULE FUNC sum_areas() -> NUM:
				NUM total = 0
				FOR cls IN "global"
					FOR obj IN cls
						total = total + obj.area
					FOREND
				FOREND
				RETURN total
			RULEEND
			RULE ATTR "global":
				"global".total_area = sum_areas()
			RULEEND
		)", make_scene({
			Instance("A", 0, 0, 10, 10, 0.5),
			Instance("A", 0, 0, 20, 20, 0.5),
			Instance("B", 0, 0, 30, 30, 0.5)
		}));

		expect_class_num(output, "GLOBAL", "TOTAL_AREA", 1400.0);
	}

	TEST_METHOD(InstanceFunctionParameterReadsSelf)
	{
		auto output = evaluate(R"(
			RULE FUNC copy_conf(item: INST) -> NUM:
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
		)", make_confidence_scene("PERSON", { 0.9, 0.6 }));

		expect_num_prop(output, "PERSON", 0, "COPIED_CONF", 0.9);
		expect_num_prop(output, "PERSON", 1, "COPIED_CONF", 0.6);
	}

	TEST_METHOD(ForInstanceCanBePassedThroughLocal)
	{
		auto output = evaluate(R"(
			RULE FUNC read_conf(item: INST) -> NUM:
				RETURN item.conf
			RULEEND
			RULE FUNC max_conf(cls: STR) -> NUM:
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
		)", make_confidence_scene("CAR", { 0.5, 0.95, 0.7 }));

		expect_class_num(output, "CAR", "MAX_CONF", 0.95);
	}

	TEST_METHOD(FunctionReturnsInstance)
	{
		evaluate_and_expect_counts(R"(
			RULE FUNC first_inst(cls: STR) -> INST:
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
		)", make_confidence_scene("PERSON", { 0.75, 0.5 }),
			{ { "PERSON", 1 } });
	}

	TEST_METHOD(DynamicInstancePropertyAccess)
	{
		auto output = evaluate(R"(
			RULE FUNC fn_avg(cls: STR, prop: STR) -> NUM:
				NUM total = 0
				FOR item IN cls
					total = total + item.(prop)
				FOREND
				RETURN total / cls.count
			RULEEND
			NUM avg_conf = fn_avg("person", "conf")
			NUM avg_area = fn_avg("person", "area")
			RULE ATTR "person":
				"person".avg_conf = avg_conf
				"person".avg_area = avg_area
			RULEEND
		)", make_scene({
			Instance("PERSON", 0, 0, 10, 10, 0.9),
			Instance("PERSON", 0, 0, 20, 20, 0.7),
			Instance("PERSON", 0, 0, 30, 30, 0.5)
		}));

		expect_class_num(output, "PERSON", "AVG_CONF", 0.7);
		expect_class_num(output, "PERSON", "AVG_AREA", 1400.0 / 3.0);
	}
};

} // namespace UnitTest1Basic
