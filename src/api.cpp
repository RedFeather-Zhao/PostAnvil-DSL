#include "postanvil/api.hpp"

#include "postanvil/compiler.hpp"

#include <memory>
#include <string>
#include <utility>

namespace postanvil {

struct Program::Impl {
	explicit Impl(CompiledProgram compiled_program)
		: program(std::move(compiled_program)) {}

	CompiledProgram program;
};

const char* version() noexcept
{
	return "0.6.4";
}

Program::Program(std::unique_ptr<Impl> impl) noexcept
	: m_impl(std::move(impl)) {}

Program::Program(Program&&) noexcept = default;
Program& Program::operator=(Program&&) noexcept = default;
Program::~Program() = default;

Scene Program::evaluate(const Scene& scene) const
{
	if (!m_impl) {
		throw RuntimeError("Cannot evaluate a moved-from program");
	}
	return m_impl->program.evaluate(scene);
}

Program Compiler::compile(std::string_view source) const
{
	PostAnvilCompiler compiler;
	auto compiled = compiler.compile(std::string(source));
	return Program(std::make_unique<Program::Impl>(std::move(compiled)));
}

} // namespace postanvil
