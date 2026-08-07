#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(FalseLiteralFiltersEverything)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "global" {
				FALSE
			}
		)", make_confidence_scene("A", { 0.9, 0.6 }), { { "A", 0 } });
	}

	PA_TEST(TrueLiteralKeepsEverything)
	{
		evaluate_and_expect_counts(R"(
			RULE FILTER "global" {
				TRUE
			}
		)", make_confidence_scene("A", { 0.9, 0.6 }), { { "A", 2 } });
	}

	PA_TEST(SortDescendingThenFilterByLiveIndex)
	{
		auto output = evaluate_and_expect_counts(R"(
			RULE SORT "person" {
				self.area DESC
			}
			RULE FILTER "person" {
				self.index <= 1
			}
		)", make_scene({
			Instance("PERSON", 0, 0, 10, 10, 0.5),
			Instance("PERSON", 0, 0, 20, 20, 0.5),
			Instance("PERSON", 0, 0, 30, 30, 0.5)
		}), { { "PERSON", 1 } });

		const auto& first = instance_at(output, "PERSON");
		Assert::AreEqual(900.0, first.area());
		Assert::AreEqual<std::size_t>(3, first.id());
		Assert::AreEqual<std::size_t>(1, first.index());
	}

	PA_TEST(StableMultiKeySort)
	{
		auto output = evaluate(R"(
			RULE SORT "person" {
				self.area ASC
				self.conf DESC
			}
		)", make_scene({
			Instance("PERSON", 0, 0, 10, 10, 0.5),
			Instance("PERSON", 10, 0, 10, 10, 0.9),
			Instance("PERSON", 20, 0, 20, 20, 0.8),
			Instance("PERSON", 30, 0, 10, 10, 0.5)
		}));

		const auto& people = output.objects.at("PERSON");
		const std::vector<std::size_t> expected_ids{ 2, 1, 4, 3 };
		Assert::AreEqual(expected_ids.size(), people.size());
		for (std::size_t i = 0; i < people.size(); ++i) {
			Assert::AreEqual(expected_ids[i], people[i].id());
			Assert::AreEqual(i + 1, people[i].index());
		}
	}

	PA_TEST(SortMissingClassIsNoOp)
	{
		evaluate_and_expect_counts(R"(
			RULE SORT "missing" {
				self.area DESC
			}
		)", make_confidence_scene("PERSON", { 0.5 }),
			{ { "PERSON", 1 }, { "MISSING", 0 } });
	}

	PA_TEST(FunctionReturningTrue)
	{
		evaluate_and_expect_counts(R"(
			RULE FUNC always_true() -> BOOL {
				TRUE
			}
			RULE FILTER "global" {
				always_true()
			}
		)", make_scene({
			Instance("A", 0, 0, 10, 10, 0.9),
			Instance("B", 0, 0, 10, 10, 0.3)
		}), { { "A", 1 }, { "B", 1 } });
	}

	PA_TEST(FunctionReturningFalse)
	{
		evaluate_and_expect_counts(R"(
			RULE FUNC always_false() -> BOOL {
				FALSE
			}
			RULE FILTER "global" {
				always_false()
			}
		)", make_scene({
			Instance("A", 0, 0, 10, 10, 0.9),
			Instance("B", 0, 0, 10, 10, 0.3)
		}), { { "A", 0 }, { "B", 0 } });
	}

} // namespace UnitTest1Basic
