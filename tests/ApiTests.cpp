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
	scene.add("person", Instance(0, 0, 10, 10, 0.8));
	scene.add("person", Instance(0, 0, 10, 10, 0.2));
	const auto output = program.evaluate(scene);

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual<std::size_t>(
			1, output.get_inst_count("PERSON"));
}

} // namespace UnitTest1Basic
