/**
 * @file api.hpp
 * @brief 不暴露 ANTLR 类型的稳定编译与执行接口。
 */
#pragma once

#include "export.hpp"
#include "scene.hpp"

#include <memory>
#include <string_view>

namespace postanvil {

/** @brief 获取当前 PostAnvil 库版本。 */
POSTANVIL_API const char* version() noexcept;

/**
 * @brief 已编译的 DSL 程序。
 * @details 实现通过 PImpl 隐藏解析器、Listener 和算子管道，适合跨动态库边界使用。
 */
class POSTANVIL_API Program {
public:
	Program(Program&&) noexcept;
	Program& operator=(Program&&) noexcept;
	~Program();

	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;

	/** @brief 在输入场景上执行程序，并返回新的结果场景。 */
	[[nodiscard]] Scene evaluate(const Scene& scene) const;

private:
	struct Impl;
	explicit Program(std::unique_ptr<Impl> impl) noexcept;
	std::unique_ptr<Impl> m_impl;

	friend class Compiler;
};

/** @brief PostAnvil DSL 编译入口。 */
class POSTANVIL_API Compiler {
public:
	/** @throws CompileError 源代码存在词法、语法或语义错误。 */
	[[nodiscard]] Program compile(std::string_view source) const;
};

} // namespace postanvil
