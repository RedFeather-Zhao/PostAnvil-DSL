#include "pch.h"

using namespace postanvil;

namespace UnitTest1Basic {

PA_TEST(PublicApiVersionAndFacade)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(
		std::string("0.8.0"), std::string(version()));

	Compiler compiler;
	auto program = compiler.compile(R"(
		rule filter "person" { self.conf >= 0.5 }
	)");

	Scene scene(Image{ 100, 100 });
	const auto first = scene.inst_add(Instance(0, 0, 10, 10, 0.8));
	const auto second = scene.inst_add(Instance(0, 0, 10, 10, 0.2));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(
		std::string("ALL_INST"), std::string(Scene::ALL_INST_CLASS));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual<std::size_t>(
		2, scene.cls_inst_count(Scene::ALL_INST_CLASS));
	const auto class_names = scene.cls_names();
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		std::ranges::find(class_names, std::string(Scene::ALL_INST_CLASS))
			== class_names.end());
	scene.cls_add_inst("person", first.id);
	scene.cls_add_inst("person", second.id);
	const auto output = program.evaluate(scene);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual<std::size_t>(
			1, output.cls_inst_count("PERSON"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual<std::size_t>(
			2, output.cls_inst_count(Scene::ALL_INST_CLASS));
}

} // namespace UnitTest1Basic
