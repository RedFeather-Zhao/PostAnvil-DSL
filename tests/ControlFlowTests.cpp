#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(NestedIfElseFunction)
	{
		auto output = evaluate_and_expect_counts(R"(
			rule func risk_level(conf: num) -> num {
				if conf > 0.8 {
					return 3
				} else {
					if conf > 0.5 {
						return 2
					} else {
						return 1
					}
				}
			}
			rule attr "person" {
				self.level = risk_level(self.conf)
			}
			rule filter "person" {
				self.level >= 2
			}
		)", make_confidence_scene("person", { 0.9, 0.6, 0.3 }),
			{ { "PERSON", 2 } });

		expect_num_prop(output, "PERSON", 0, "LEVEL", 3.0);
		expect_num_prop(output, "PERSON", 1, "LEVEL", 2.0);
	}

	PA_TEST(MultipleElifBranchesMayStartOnNewLines)
	{
		auto output = evaluate(R"(
			RULE FUNC level(conf: NUM) -> NUM {
				IF conf > 0.9 {
					RETURN 4
				}
				ELIF conf > 0.7 {
					RETURN 3
				}
				ELIF conf > 0.5 {
					RETURN 2
				}
				ELSE {
					RETURN 1
				}
			}
			RULE ATTR "person" {
				self.level = level(self.conf)
			}
		)", make_confidence_scene("PERSON", { 0.95, 0.8, 0.6, 0.4 }));

		expect_num_prop(output, "PERSON", 0, "LEVEL", 4.0);
		expect_num_prop(output, "PERSON", 1, "LEVEL", 3.0);
		expect_num_prop(output, "PERSON", 2, "LEVEL", 2.0);
		expect_num_prop(output, "PERSON", 3, "LEVEL", 1.0);
	}

	PA_TEST(ForLoopComputesAverage)
	{
		auto output = evaluate(R"(
			RULE FUNC avg_conf(cls: STR) -> NUM {
				NUM total = 0
				FOR obj IN cls {
					total = total + obj.conf
				}
				RETURN total / cls.count
			}
			RULE ATTR "car" {
				"car".avg_conf = avg_conf("car")
			}
		)", make_confidence_scene("CAR", { 0.9, 0.7, 0.5 }));

		expect_class_num(output, "CAR", "AVG_CONF", 0.7);
	}

	PA_TEST(ForLoopOverEmptyClass)
	{
		auto output = evaluate(R"(
			RULE FUNC safe_avg(cls: STR) -> NUM {
				NUM total = 0
				FOR obj IN cls {
					total = total + obj.conf
				}
				IF cls.count == 0 {
					RETURN 0
				} ELSE {
					RETURN total / cls.count
				}
			}
			RULE ATTR "car" {
				"car".avg_conf = safe_avg("car")
			}
		)", make_scene({}));

		expect_class_num(output, "CAR", "AVG_CONF", 0.0);
	}

	PA_TEST(NestedForLoops)
	{
		auto output = evaluate(R"(
			RULE FUNC sum_areas() -> NUM {
				NUM total = 0
				FOR cls IN @ALL_CLASS {
					FOR obj IN cls {
						total = total + obj.area
					}
				}
				RETURN total
			}
			RULE ATTR ALL_INST {
				"global".total_area = sum_areas()
			}
		)", make_scene({
			make_instance("A", 0, 0, 10, 10, 0.5),
			make_instance("A", 0, 0, 20, 20, 0.5),
			make_instance("B", 0, 0, 30, 30, 0.5)
		}));

		expect_class_num(output, "GLOBAL", "TOTAL_AREA", 1400.0);
	}

	PA_TEST(InstanceFunctionParameterReadsSelf)
	{
		auto output = evaluate(R"(
			RULE FUNC copy_conf(item: INST) -> NUM {
				INST current_self = self
				INST current_arg = item
				IF current_self.conf == current_arg.conf {
					RETURN current_arg.conf
				} ELSE {
					RETURN 0
				}
			}
			RULE ATTR "person" {
				self.copied_conf = copy_conf(self)
			}
		)", make_confidence_scene("PERSON", { 0.9, 0.6 }));

		expect_num_prop(output, "PERSON", 0, "COPIED_CONF", 0.9);
		expect_num_prop(output, "PERSON", 1, "COPIED_CONF", 0.6);
	}

	PA_TEST(ForInstanceCanBePassedThroughLocal)
	{
		auto output = evaluate(R"(
			RULE FUNC read_conf(item: INST) -> NUM {
				RETURN item.conf
			}
			RULE FUNC max_conf(cls: STR) -> NUM {
				NUM best = 0
				FOR obj IN cls {
					INST current = obj
					IF read_conf(current) > best {
						best = read_conf(current)
					}
				}
				RETURN best
			}
			RULE ATTR "car" {
				"car".max_conf = max_conf("car")
			}
		)", make_confidence_scene("CAR", { 0.5, 0.95, 0.7 }));

		expect_class_num(output, "CAR", "MAX_CONF", 0.95);
	}

	PA_TEST(FunctionReturnsInstance)
	{
		evaluate_and_expect_counts(R"(
			RULE FUNC first_inst(cls: STR) -> INST {
				FOR obj IN cls {
					INST selected = obj
					RETURN selected
				}
				RETURN self
			}
			INST anchor = first_inst("person")
			RULE FILTER "person" {
				self.conf >= anchor.conf
			}
		)", make_confidence_scene("PERSON", { 0.75, 0.5 }),
			{ { "PERSON", 1 } });
	}

	PA_TEST(DynamicInstancePropertyAccess)
	{
		auto output = evaluate(R"(
			RULE FUNC fn_avg(cls: STR, prop: STR) -> NUM {
				NUM total = 0
				FOR item IN cls {
					total = total + item.(prop)
				}
				RETURN total / cls.count
			}
			NUM avg_conf = fn_avg("person", "conf")
			NUM avg_area = fn_avg("person", "area")
			RULE ATTR "person" {
				"person".avg_conf = avg_conf
				"person".avg_area = avg_area
			}
		)", make_scene({
			make_instance("PERSON", 0, 0, 10, 10, 0.9),
			make_instance("PERSON", 0, 0, 20, 20, 0.7),
			make_instance("PERSON", 0, 0, 30, 30, 0.5)
		}));

		expect_class_num(output, "PERSON", "AVG_CONF", 0.7);
		expect_class_num(output, "PERSON", "AVG_AREA", 1400.0 / 3.0);
	}

} // namespace UnitTest1Basic
