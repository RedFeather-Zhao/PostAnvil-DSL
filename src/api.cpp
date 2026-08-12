/**
 * @file   api.cpp
 * @brief  PostAnvil DSL 编译与执行接口的实现，不暴露 ANTLR 类型，适合跨动态库使用
 *
 * @author RedFeather-Zhao
 * @date   August 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#include "postanvil/api.hpp"
#include "postanvil/compiler.hpp"

#include <memory>
#include <string>
#include <utility>

namespace postanvil {

// ========================= API Functions ==========================

const char* version() noexcept {
	return "0.8.0";
}

// ========================= API Classes ==========================

/**
 * @brief Program 类的内部实现
 */
struct Program::Impl {
	explicit Impl(CompiledProgram compiled_program)
		: program(std::move(compiled_program))
	{
	}

	CompiledProgram program;
};

/**
 * @brief Program 类的私有构造函数，接受一个唯一指针指向 Impl 实例
 *
 * @param impl - 指向 Impl 实例的唯一指针
 */
Program::Program(std::unique_ptr<Impl> impl) noexcept
	: m_impl(std::move(impl))
{
}

Program::Program(Program&&) noexcept = default;
Program& Program::operator=(Program&&) noexcept = default;
Program::~Program() = default;


Scene Program::evaluate(const Scene& scene) const
{
	if (!m_impl) {
		throw PARuntimeError("Cannot evaluate a moved-from program");
	}
	return m_impl->program.evaluate(scene);
}

Program Compiler::compile(std::string_view source) const
{
	PostAnvilCompiler compiler;
	auto compiled = compiler.compile(source);
	return Program(std::make_unique<Program::Impl>(std::move(compiled)));
}

} // namespace postanvil
