/**
 * @file   error.hpp
 * @brief  PostAnvil 编译器与运行时错误类型定义
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <stdexcept>

namespace postanvil {

	using PostAnvilError = std::runtime_error;

	struct ParseError : public PostAnvilError {
		using runtime_error::runtime_error;
	};

	struct CompileError : public PostAnvilError {
		using runtime_error::runtime_error;
	};

	struct RuntimeError : public PostAnvilError {
		using runtime_error::runtime_error;
	};

}
