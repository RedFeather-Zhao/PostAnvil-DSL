#include "pch.h"
#include "TestSupport.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace postanvil;
using namespace postanvil::test;

namespace UnitTest1Basic {

PA_TEST(DummyUsesIdZeroAndRealInstanceIdsAreSequential)
{
	Scene scene(Image{ 100, 100 });
	Assert::AreEqual(static_cast<InstId>(0), scene.inst_dummy().id());

	const auto person = scene.inst_add(Instance(0, 0, 10, 10, 0.9));
	const auto car = scene.inst_add(Instance(0, 0, 10, 10, 0.8));
	scene.cls_add_inst("person", person.id);
	scene.cls_add_inst("car", car.id);
	Assert::AreEqual(static_cast<InstId>(1), scene.inst_at(1).id());
	Assert::AreEqual(static_cast<InstId>(2), scene.inst_at(2).id());
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

	Assert::AreEqual(static_cast<std::size_t>(2), output.cls_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("SELECTED"));
	const auto person_id = output.cls_insts("PERSON")[0];
	const auto selected_id = output.cls_insts("SELECTED")[0];
	Assert::AreEqual(person_id, selected_id);
	Assert::IsTrue(&output.inst_at(person_id) == &output.inst_at(selected_id));
	Assert::AreEqual(42.0, output.inst_at(person_id).get_prop("SHARED_SCORE").as_num());
}

PA_TEST(FilterChangesClassListWithoutDeletingInstance)
{
	auto input = make_confidence_scene("PERSON", { 0.9, 0.4 });
	const auto removed_id = input.cls_insts("PERSON")[1];
	auto output = evaluate(R"(
		RULE FILTER "person" {
			self.conf > 0.5
		}
	)", std::move(input));

	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(2), output.inst_count());
	Assert::AreEqual(0.4, output.inst_at(removed_id).conf(), 1e-9);
}

PA_TEST(AppendIsAnIdempotentMembershipUnion)
{
	auto output = evaluate(R"(
		RULE APPEND "selected" FROM "person" {}
		RULE APPEND "selected" FROM "person" {}
	)", make_confidence_scene("PERSON", { 0.9, 0.7 }));

	Assert::AreEqual(static_cast<std::size_t>(2), output.cls_inst_count("SELECTED"));
	Assert::AreEqual(output.cls_insts("PERSON")[0], output.cls_insts("SELECTED")[0]);
	Assert::AreEqual(output.cls_insts("PERSON")[1], output.cls_insts("SELECTED")[1]);
}

PA_TEST(ClassNameAndIndexBelongToTheHandleContext)
{
	auto scene = make_confidence_scene("PERSON", { 0.9, 0.7 });
	const auto first = scene.cls_insts("PERSON")[0];
	const auto second = scene.cls_insts("PERSON")[1];
	scene.cls_set_insts("REVERSED", { second, first });

	Assert::AreEqual(std::string("PERSON"),
		scene.inst_prop(InstanceHandle{ first, "PERSON" }, "CLS").as_str());
	Assert::AreEqual(1.0,
		scene.inst_prop(InstanceHandle{ first, "PERSON" }, "INDEX").as_num());
	Assert::AreEqual(2.0,
		scene.inst_prop(InstanceHandle{ first, "REVERSED" }, "INDEX").as_num());
}

PA_TEST(SceneCopyOwnsIndependentInstances)
{
	auto original = make_confidence_scene("PERSON", { 0.9 });
	Scene copied = original;
	const auto id = original.cls_insts("PERSON")[0];

	Assert::IsTrue(&original.inst_at(id) != &copied.inst_at(id));
	copied.inst_at(id).set_conf(0.1);
	Assert::AreEqual(0.9, original.inst_at(id).conf(), 1e-9);
	Assert::AreEqual(0.1, copied.inst_at(id).conf(), 1e-9);
}

PA_TEST(GlobalAttributeVisitsEachInstanceForEveryDefinition)
{
	auto input = make_confidence_scene("PERSON", { 0.9 });
	input.cls_add_inst("ALSO_PERSON", input.cls_insts("PERSON")[0]);
	auto output = evaluate(R"(
		RULE ATTR ALL_INST {
			self.first = self.conf
			self.second = self.conf * 2
		}
	)", std::move(input));

	const auto id = output.cls_insts("PERSON")[0];
	Assert::AreEqual(0.9, output.inst_at(id).get_prop("FIRST").as_num(), 1e-9);
	Assert::AreEqual(1.8, output.inst_at(id).get_prop("SECOND").as_num(), 1e-9);
}

PA_TEST(AllInstVisitsSharedAndOrphanInstancesExactlyOnce)
{
	auto input = make_confidence_scene("PERSON", { 0.9 });
	const auto shared_id = input.cls_insts("PERSON")[0];
	input.cls_add_inst("ALSO_PERSON", shared_id);
	const auto orphan = input.inst_add(Instance(0, 0, 10, 10, 0.5));

	auto output = evaluate(R"(
		RULE ATTR ALL_INST {
			self.conf = self.conf + 1
			self.all_index = self.index
		}
	)", std::move(input));

	Assert::AreEqual(1.9, output.inst_at(shared_id).conf(), 1e-9);
	Assert::AreEqual(1.5, output.inst_at(orphan.id).conf(), 1e-9);
	Assert::AreEqual(1.0, output.inst_at(shared_id).get_prop("ALL_INDEX").as_num(), 1e-9);
	Assert::AreEqual(2.0, output.inst_at(orphan.id).get_prop("ALL_INDEX").as_num(), 1e-9);
}

PA_TEST(FilterAllInstOnlyChangesBuiltInClass)
{
	auto output = evaluate(R"(
		RULE FILTER ALL_INST {
			self.conf >= 0.5
		}
	)", make_confidence_scene("PERSON", { 0.9, 0.4 }));

	Assert::AreEqual(static_cast<std::size_t>(2), output.inst_count());
	Assert::AreEqual(static_cast<std::size_t>(2), output.cls_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("ALL_INST"));
}

PA_TEST(AllClassAndTemporaryClassGroupPreserveClassContexts)
{
	auto input = make_confidence_scene("PERSON", { 0.9, 0.4 });
	const auto shared_id = input.cls_insts("PERSON")[0];
	input.cls_add_inst("ALSO_PERSON", shared_id);

	auto output = evaluate(R"(
		RULE ATTR @ALL_CLASS {
			self.conf = self.conf + 1
		}
		RULE FILTER "person", "also_person" {
			self.index == 1
		}
	)", std::move(input));

	// shared_id 在两个类别视图中各处理一次；临时组随后分别过滤两个类别。
	Assert::AreEqual(2.9, output.inst_at(shared_id).conf(), 1e-9);
	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("PERSON"));
	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("ALSO_PERSON"));
}

PA_TEST(GroupAndAppendAcceptTemporaryAndBuiltInGroups)
{
	auto input = make_scene({
		make_instance("PERSON", 0, 0, 10, 10, 0.9),
		make_instance("CAR", 0, 0, 10, 10, 0.8),
	});
	const auto shared_id = input.cls_insts("PERSON")[0];
	input.cls_add_inst("CAR", shared_id);
	const auto orphan = input.inst_add(Instance(0, 0, 10, 10, 0.7));

	auto output = evaluate(R"(
		RULE GROUP "VISIBLE" FROM "person", "car" {}
		RULE APPEND "EVERYTHING" FROM ALL_INST {}
	)", std::move(input));

	Assert::AreEqual(static_cast<std::size_t>(2), output.cls_inst_count("VISIBLE"));
	Assert::AreEqual(static_cast<std::size_t>(3), output.cls_inst_count("EVERYTHING"));
	Assert::AreEqual(orphan.id, output.cls_insts("EVERYTHING")[2]);
}

PA_TEST(GlobalIsNowAnOrdinaryClassName)
{
	auto output = evaluate(R"(
		RULE FILTER "global" {
			self.conf > 0.5
		}
	)", make_scene({
		make_instance("GLOBAL", 0, 0, 10, 10, 0.9),
		make_instance("PERSON", 0, 0, 10, 10, 0.1),
	}));

	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("GLOBAL"));
	Assert::AreEqual(static_cast<std::size_t>(1), output.cls_inst_count("PERSON"));
}

} // namespace UnitTest1Basic
