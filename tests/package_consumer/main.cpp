#include <PostAnvil.h>

#include <string_view>

int main()
{
	using namespace std::literals;
	postanvil::Compiler compiler;
	auto program = compiler.compile(R"(
		RULE FILTER "global":
			self.conf >= 0.5
		RULEEND
	)"sv);

	postanvil::Scene input(postanvil::Image{ 100, 100 }, {
		postanvil::Instance("person", 0, 0, 10, 10, 0.8),
		postanvil::Instance("person", 0, 0, 10, 10, 0.2),
	});
	const auto output = program.evaluate(input);
	return output.objects.at("PERSON").size() == 1 ? 0 : 1;
}
