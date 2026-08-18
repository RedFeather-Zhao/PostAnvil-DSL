#include <PostAnvil.h>

#include <string_view>

int main()
{
	using namespace std::literals;
	postanvil::Compiler compiler;
	auto program = compiler.compile(R"(
		RULE FILTER "global" {
			self.conf >= 0.5
		}
	)"sv);

	postanvil::Scene input(postanvil::Image{ 100, 100 });
	const auto first = input.inst_add(postanvil::Instance(0, 0, 10, 10, 0.8));
	const auto second = input.inst_add(postanvil::Instance(0, 0, 10, 10, 0.2));
	input.cls_add_inst("person", first.id);
	input.cls_add_inst("person", second.id);
	const auto output = program.evaluate(input);
	return output.cls_inst_count("PERSON") == 1 ? 0 : 1;
}
