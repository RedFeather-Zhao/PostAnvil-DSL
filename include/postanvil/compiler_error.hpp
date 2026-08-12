/**
 * @file   compiler_error.hpp
 * @brief  PostAnvil 编译器公共错误报告工具
 *
 * @author RedFeather-Zhao
 * @date   August 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include <string_view>

#include "antlr4-runtime.h"

#include "error.hpp"

namespace postanvil {

// ====================== Compiler Error Report ======================

/**
 * @brief 抛出编译错误，并从解析树上下文中提取源码位置
 *
 * @param kind	- 编译错误类别
 * @param msg	- 错误消息
 * @param ctx	- 解析树上下文，可以为空
 */
[[noreturn]] inline void
throw_compile_error		(PACompileError::Kind kind,
						 std::string_view msg,
						 const ::antlr4::ParserRuleContext* ctx = nullptr)
{
	if (!ctx || !ctx->getStart()) {
		throw PACompileError(kind, msg);
	}

	const auto* start = ctx->getStart();
	throw PACompileError(
		kind,
		msg,
		SourceLocation{
			static_cast<int>(start->getLine()),
			static_cast<int>(start->getCharPositionInLine()) + 1,
			std::nullopt
		}
	);
}

/**
 * @brief 报告语义错误，抛出 PACompileError-Semantic 异常
 *
 * @param msg	- 错误消息
 * @param ctx	- 解析树上下文
 */
[[noreturn]] inline void
report_semantic_error	(std::string_view msg,
						 const ::antlr4::ParserRuleContext* ctx)
{
	throw_compile_error(PACompileError::Kind::Semantic, msg, ctx);
}

/**
 * @brief 报告内部错误，抛出 PACompileError-Internal 异常
 *
 * @param msg	- 错误消息
 * @param ctx	- 解析树上下文，可以为空
 */
[[noreturn]] inline void
report_internal_error	(std::string_view msg,
						 const ::antlr4::ParserRuleContext* ctx = nullptr)
{
	throw_compile_error(PACompileError::Kind::Internal, msg, ctx);
}

/**
 * @brief 为编译错误补充对应的源码行并重新抛出
 *
 * @param source	- DSL 源代码文本
 * @param error		- 待补充源码信息的编译错误
 */
[[noreturn]] inline void
rethrow_compile_error	(std::string_view source,
						 const PACompileError& error)
{
	if (error.line() > 0 && !error.has_source_line()) {
		throw PACompileError(
			error.kind(),
			error.message(),
			PostAnvilError::locate_source(source, error.line(), error.column()),
			error.hint(),
			error.raw_message()
		);
	}
	throw error;
}

} // namespace postanvil
