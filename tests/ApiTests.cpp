#include "pch.h"

using namespace postanvil;

namespace UnitTest1Basic {

PA_TEST(PublicApiVersionAndFacade)
{
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(
		std::string("0.7.0"), std::string(version()));

	Compiler compiler;
	auto program = compiler.compile(R"(
		RULE FILTER "person" {
			self.conf >= 0.5
		}
	)");

	Scene scene(Image{ 100, 100 });
	scene.add(Instance("person", 0, 0, 10, 10, 0.8));
	scene.add(Instance("person", 0, 0, 10, 10, 0.2));
	const auto output = program.evaluate(scene);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual<std::size_t>(
		1, output.objects.at("PERSON").size());
}

} // namespace UnitTest1Basic
