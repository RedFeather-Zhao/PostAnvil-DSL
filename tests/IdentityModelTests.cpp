#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(DummyUsesIdZeroAndRealInstanceIdsAreSequential)
{
	Scene scene(Image{ 100, 100 });
	Assert::AreEqual(static_cast<InstanceId>(0), scene.inst_dummy().id());

	scene.add("person", Instance(0, 0, 10, 10, 0.9));
	scene.add("car", Instance(0, 0, 10, 10, 0.8));
	Assert::AreEqual(static_cast<InstanceId>(1), scene.inst(1).id());
	Assert::AreEqual(static_cast<InstanceId>(2), scene.inst(2).id());
	Assert::AreEqual(static_cast<std::size_t>(2), scene.inst_count());
}

PA_TEST(GroupSharesInstanceIdentityAndProperties)
{
	auto output = evaluate(R"(
		RULE GROUP "selected" FROM "person" {
			self.conf > 0.8
		}
		RULE ATTR "selected" {
			self.shared_score = 42
		}
	)", make_confidence_scene("PERSON", { 0.9, 0.7 }));

	Assert::AreEqual(static_cast<std::size_t>(2), output.get_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(1), output.get_inst_count("SELECTED"));
	const auto person_id = output.get_inst_ids("PERSON")[0];
	const auto selected_id = output.get_inst_ids("SELECTED")[0];
	Assert::AreEqual(person_id, selected_id);
	Assert::IsTrue(&output.inst(person_id) == &output.inst(selected_id));
	Assert::AreEqual(42.0, output.inst(person_id).get_prop("SHARED_SCORE").as_num());
}

PA_TEST(FilterChangesClassListWithoutDeletingInstance)
{
	auto input = make_confidence_scene("PERSON", { 0.9, 0.4 });
	const auto removed_id = input.get_inst_ids("PERSON")[1];
	auto output = evaluate(R"(
		RULE FILTER "person" {
			self.conf > 0.5
		}
	)", std::move(input));

	Assert::AreEqual(static_cast<std::size_t>(1), output.get_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(2), output.inst_count());
	Assert::AreEqual(0.4, output.inst(removed_id).conf(), 1e-9);
}

PA_TEST(AppendIsAnIdempotentMembershipUnion)
{
	auto output = evaluate(R"(
		RULE APPEND "selected" FROM "person" {}
		RULE APPEND "selected" FROM "person" {}
	)", make_confidence_scene("PERSON", { 0.9, 0.7 }));

	Assert::AreEqual(static_cast<std::size_t>(2), output.get_inst_count("SELECTED"));
	Assert::AreEqual(output.get_inst_ids("PERSON")[0], output.get_inst_ids("SELECTED")[0]);
	Assert::AreEqual(output.get_inst_ids("PERSON")[1], output.get_inst_ids("SELECTED")[1]);
}

PA_TEST(ClassNameAndIndexBelongToTheHandleContext)
{
	auto scene = make_confidence_scene("PERSON", { 0.9, 0.7 });
	const auto first = scene.get_inst_ids("PERSON")[0];
	const auto second = scene.get_inst_ids("PERSON")[1];
	scene.replace_class("REVERSED", { second, first });

	Assert::AreEqual(std::string("PERSON"),
		scene.get_inst_prop(InstanceHandle{ first, "PERSON" }, "CLS").as_str());
	Assert::AreEqual(1.0,
		scene.get_inst_prop(InstanceHandle{ first, "PERSON" }, "INDEX").as_num());
	Assert::AreEqual(2.0,
		scene.get_inst_prop(InstanceHandle{ first, "REVERSED" }, "INDEX").as_num());
}

PA_TEST(SceneCopyOwnsIndependentInstances)
{
	auto original = make_confidence_scene("PERSON", { 0.9 });
	Scene copied = original;
	const auto id = original.get_inst_ids("PERSON")[0];

	Assert::IsTrue(&original.inst(id) != &copied.inst(id));
	copied.inst(id).set_conf(0.1);
	Assert::AreEqual(0.9, original.inst(id).conf(), 1e-9);
	Assert::AreEqual(0.1, copied.inst(id).conf(), 1e-9);
}

PA_TEST(GlobalAttributeVisitsEachInstanceForEveryDefinition)
{
	auto input = make_confidence_scene("PERSON", { 0.9 });
	input.append_to_class("ALSO_PERSON", input.get_inst_ids("PERSON")[0]);
	auto output = evaluate(R"(
		RULE ATTR "global" {
			self.first = self.conf
			self.second = self.conf * 2
		}
	)", std::move(input));

	const auto id = output.get_inst_ids("PERSON")[0];
	Assert::AreEqual(0.9, output.inst(id).get_prop("FIRST").as_num(), 1e-9);
	Assert::AreEqual(1.8, output.inst(id).get_prop("SECOND").as_num(), 1e-9);
}

} // namespace UnitTest1Basic
