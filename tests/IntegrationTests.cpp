#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(ImportsHostVariables)
	{
		auto input = make_scene({
			make_instance("PERSON", 0, 0, 10, 10, 0.8),
			make_instance("PERSON", 0, 0, 10, 10, 0.4),
			make_instance("CAR", 0, 0, 10, 10, 0.8)
		});
		input.add_import("EXTERNAL_THRESHOLD", Val(0.6));
		input.add_import("TARGET_CLASS", Val("PERSON"));

		evaluate_and_expect_counts(R"(
			IMPORT NUM external_threshold
			IMPORT STR target_class
			RULE FILTER target_class {
				self.conf > external_threshold
			}
		)", std::move(input), { { "PERSON", 1 }, { "CAR", 1 } });
	}

	PA_TEST(ImportAlias)
	{
		auto input = make_confidence_scene("A", { 0.8, 0.3 });
		input.add_import("CONF_THRESHOLD", Val(0.6));

		evaluate_and_expect_counts(R"(
			IMPORT NUM host_conf AS conf_threshold
			RULE FILTER "global" {
				self.conf > conf_threshold
			}
		)", std::move(input), { { "A", 1 } });
	}

PA_TEST(ExportsValues)
	{
		auto output = evaluate_and_expect_counts(R"(
			RULE ATTR "person" {
				self.risk = self.conf * 2.0
			}
			RULE FILTER "person" {
				self.conf > 0.5
			}
			EXPORT "person".count AS person_count
			EXPORT 1.8 AS max_risk
		)", make_confidence_scene("PERSON", { 0.9, 0.6, 0.3 }),
			{ { "PERSON", 2 } });

		expect_export_num(output, "person_count", 2.0);
		expect_export_num(output, "max_risk", 1.8);
	}

	PA_TEST(TopLevelDeclarationMayEndAtEndOfFile)
	{
		auto output = evaluate(
			"NUM answer = 42\n"
			"EXPORT answer AS answer",
			make_scene({}));
		expect_export_num(output, "answer", 42.0);
	}

	PA_TEST(ImportsAndExportsInstance)
	{
		auto input = make_confidence_scene("PERSON", { 0.9, 0.5 });
		const auto anchor = input.add("ANCHOR", Instance(0, 0, 10, 10, 0.7));
		input.add_import(
			"ANCHOR",
			Val(anchor));

		auto output = evaluate_and_expect_counts(R"(
			IMPORT INST anchor
			RULE FILTER "person" {
				self.conf >= anchor.conf
			}
			EXPORT anchor AS selected_anchor
		)", std::move(input), { { "PERSON", 1 } });

		const auto exported = output.get_export("selected_anchor");
		Assert::IsTrue(type_strict_equal(exported.type(), Type::T_INST));
		Assert::AreEqual(0.7, output.inst(exported.as_inst().id).conf(), 1e-9);
	}

	PA_TEST(EndToEndPipeline)
	{
		auto input = make_scene({
			make_instance("PERSON", 0, 0, 30, 20, 0.9),
			make_instance("PERSON", 0, 0, 20, 20, 0.6),
			make_instance("PERSON", 0, 0, 40, 30, 0.7),
			make_instance("PERSON", 0, 0, 30, 20, 0.3)
		});
		input.add_import("MIN_CONF", Val(0.5));

		auto output = evaluate_and_expect_counts(R"(
			IMPORT NUM min_conf
			NUM area_threshold = 500
			RULE ATTR "person" {
				self.risk = self.conf * 2.0
				self.norm_area = self.arean
			}
			RULE FILTER "person" {
				self.conf > min_conf
				self.area > area_threshold
			}
			RULE GROUP "high_risk" FROM "person" {
				self.risk > 1.0
			}
			EXPORT "high_risk".count AS high_risk_count
			EXPORT "person".count AS total_person
		)", std::move(input), { { "PERSON", 2 }, { "HIGH_RISK", 2 } });

		expect_export_num(output, "total_person", 2.0);
		expect_export_num(output, "high_risk_count", 2.0);
	}

} // namespace UnitTest1Basic
