#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

TEST_CLASS(HostIntegrationTests)
{
public:
	TEST_METHOD(ImportsHostVariables)
	{
		auto input = make_scene({
			Instance("PERSON", 0, 0, 10, 10, 0.8),
			Instance("PERSON", 0, 0, 10, 10, 0.4),
			Instance("CAR", 0, 0, 10, 10, 0.8)
		});
		input.add_import("EXTERNAL_THRESHOLD", Val(0.6));
		input.add_import("TARGET_CLASS", Val("PERSON"));

		evaluate_and_expect_counts(R"(
			IMPORT NUM external_threshold
			IMPORT STR target_class
			RULE FILTER target_class:
				self.conf > external_threshold
			RULEEND
		)", std::move(input), { { "PERSON", 1 }, { "CAR", 1 } });
	}

	TEST_METHOD(ImportAlias)
	{
		auto input = make_confidence_scene("A", { 0.8, 0.3 });
		input.add_import("CONF_THRESHOLD", Val(0.6));

		evaluate_and_expect_counts(R"(
			IMPORT NUM host_conf AS conf_threshold
			RULE FILTER "global":
				self.conf > conf_threshold
			RULEEND
		)", std::move(input), { { "A", 1 } });
	}

	TEST_METHOD(ExportsValues)
	{
		auto output = evaluate_and_expect_counts(R"(
			RULE ATTR "person":
				self.risk = self.conf * 2.0
			RULEEND
			RULE FILTER "person":
				self.conf > 0.5
			RULEEND
			EXPORT "person".count AS person_count
			EXPORT 1.8 AS max_risk
		)", make_confidence_scene("PERSON", { 0.9, 0.6, 0.3 }),
			{ { "PERSON", 2 } });

		expect_export_num(output, "person_count", 2.0);
		expect_export_num(output, "max_risk", 1.8);
	}

	TEST_METHOD(ImportsAndExportsInstance)
	{
		auto input = make_confidence_scene("PERSON", { 0.9, 0.5 });
		input.add_import(
			"ANCHOR",
			Val(Instance("PERSON", 0, 0, 10, 10, 0.7)));

		auto output = evaluate_and_expect_counts(R"(
			IMPORT INST anchor
			RULE FILTER "person":
				self.conf >= anchor.conf
			RULEEND
			EXPORT anchor AS selected_anchor
		)", std::move(input), { { "PERSON", 1 } });

		const auto exported = output.get_export("selected_anchor");
		Assert::IsTrue(type_strict_equal(exported.type(), Type::T_INST));
		Assert::AreEqual(0.7, exported.as_inst()->conf(), 1e-9);
	}

	TEST_METHOD(EndToEndPipeline)
	{
		auto input = make_scene({
			Instance("PERSON", 0, 0, 30, 20, 0.9),
			Instance("PERSON", 0, 0, 20, 20, 0.6),
			Instance("PERSON", 0, 0, 40, 30, 0.7),
			Instance("PERSON", 0, 0, 30, 20, 0.3)
		});
		input.add_import("MIN_CONF", Val(0.5));

		auto output = evaluate_and_expect_counts(R"(
			IMPORT NUM min_conf
			NUM area_threshold = 500
			RULE ATTR "person":
				self.risk = self.conf * 2.0
				self.norm_area = self.arean
			RULEEND
			RULE FILTER "person":
				self.conf > min_conf
				self.area > area_threshold
			RULEEND
			RULE GROUP "high_risk" FROM "person":
				self.risk > 1.0
			RULEEND
			EXPORT "high_risk".count AS high_risk_count
			EXPORT "person".count AS total_person
		)", std::move(input), { { "PERSON", 2 }, { "HIGH_RISK", 2 } });

		expect_export_num(output, "total_person", 2.0);
		expect_export_num(output, "high_risk_count", 2.0);
	}
};

} // namespace UnitTest1Basic
