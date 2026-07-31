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
#include <format>

namespace postanvil {

/**
 * @brief PostAnvil 所有异常的基类型，派生自 std::runtime_error
 */
using PostAnvilError = std::runtime_error;

/**
 * @brief 解析阶段错误（如语法错误），由 ANTLR 解析器抛出
 */
struct ParseError : public PostAnvilError {
	using runtime_error::runtime_error;
};

/**
 * @brief 编译阶段错误，包含错误发生的源码位置（行、列）
 */
struct CompileError : public PostAnvilError {
	/**
	 * @brief 构造编译错误
	 * @param msg 错误描述信息
	 * @param line 错误所在行号（从1开始），默认-1表示未知
	 * @param col  错误所在列号（从1开始），默认-1表示未知
	 */
	explicit CompileError(const std::string& msg, int line = -1, int col = -1)
		: PostAnvilError(std::format("PostAnvil error while compiling: l:{},c:{} {}\n", line, col, msg))
	{}
};

/**
 * @brief 运行时错误（如执行 DSL 规则时发生的逻辑错误或类型错误）
 */
struct RuntimeError : public PostAnvilError {
	using runtime_error::runtime_error;

	/**
	 * @brief 程序运行错误
	 * @param msg		错误描述信息
	 * @param op_idx	算子索引
	 * @param op_type	算子类型
	 */
	RuntimeError(const std::string& msg, int op_idx, const std::string& op_type)
		: PostAnvilError(std::format("PostAnvil error while running: operation index = {}, operation type = {} : {}\n", op_idx, op_type, msg))
	{}
};

} // namespace postanvil

