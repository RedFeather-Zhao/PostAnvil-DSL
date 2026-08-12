/**
 * @file   api.hpp
 * @brief  PostAnvil DSL 编译与执行接口
 *
 * @author RedFeather-Zhao
 * @date   August 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

// ========================= API Export Macro ==========================

#if defined(_WIN32) || defined(__CYGWIN__)
#  if defined(POSTANVIL_STATIC)
#    define POSTANVIL_API
#  elif defined(POSTANVIL_BUILD_SHARED)
#    define POSTANVIL_API __declspec(dllexport)
#  else
#    define POSTANVIL_API __declspec(dllimport)
#  endif
#elif defined(__GNUC__) && __GNUC__ >= 4
#  define POSTANVIL_API __attribute__((visibility("default")))
#else
#  define POSTANVIL_API
#endif

#include "scene.hpp"

#include <memory>
#include <string_view>

namespace postanvil {

// ========================= API Functions ==========================

/**
 * @brief 获取当前 PostAnvil 库版本
 */
POSTANVIL_API const char* version() noexcept;


// ========================= API Classes ==========================

/**
 * @brief PostAnvil DSL 程序类，本质为函数闭包的合集，可复用于执行场景计算
 */
class POSTANVIL_API Program {
public:
	Program(Program&&) noexcept;
	Program& operator=(Program&&) noexcept;
	~Program();

	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;

	/**
	 * @brief 在输入场景上执行程序，并返回新的结果场景
	 *
	 * @param scene		- 输入场景
	 * @return Scene	- 输出场景
	 */
	[[nodiscard]]
	Scene evaluate(const Scene& scene) const;

private:
	struct Impl;

	explicit Program(std::unique_ptr<Impl> impl) noexcept;

	std::unique_ptr<Impl> m_impl;

	friend class Compiler;
};

/**
 * @brief PostAnvil DSL 编译器类，提供 DSL 源代码编译为可执行程序/闭包的接口
 */
class POSTANVIL_API Compiler {
public:
	/**
	 * @brief 编译 DSL 源代码，将输入的 DSL 源代码编译为 PostAnvil DSL 程序类
	 *
	 * @param source			- DSL 源代码
	 * @return Program			- 编译后的程序
	 * @throws PACompileError	- 源代码存在词法、语法或语义错误
	 */
	[[nodiscard]]
	Program compile(std::string_view source) const;
};

} // namespace postanvil
