/**
 * @file   error_listener.hpp
 * @brief  PostAnvil ANTLR4 语法错误监听器
 *
 * @author RedFeather-Zhao
 * @date   August 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include <format>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "antlr4-runtime.h"

#include "error.hpp"
#include "utils.hpp"

namespace postanvil {

// ====================== ANTLR4 Error Listener ======================

/**
 * @brief 自定义 ANTLR4 错误监听器，用于收集并报告语法分析过程中的错误信息
 */
struct PostAnvilErrorListener final : public antlr4::BaseErrorListener {
private:
	struct Error {
		int line;						// 行号
		int column;						// 列号
		std::string offending_text;		// 错误源文本
		std::string raw_message;		// ANTLR4 原始错误信息
	};

	struct FriendlyError {
		std::string message;			// 面向用户的错误说明
		std::string hint;				// 修改建议
	};

public:
	/**
	 * @brief 重载 ANTLR4 语法错误信息回调，收集错误信息
	 *
	 * @param recognizer			- ANTLR4 识别器
	 * @param offendingSymbol	- 出错的 Token
	 * @param line					- 错误所在行号
	 * @param charPositionInLine	- 错误所在列号
	 * @param msg					- 错误信息
	 * @param e						- 异常指针
	 */
	void syntaxError		(antlr4::Recognizer* /*recognizer*/,
							 antlr4::Token* offendingSymbol,
							 size_t line,
							 size_t charPositionInLine,
							 const std::string& msg,
							 std::exception_ptr /*e*/) override
	{
		m_errors.emplace_back(
			static_cast<int>(line),
			static_cast<int>(charPositionInLine) + 1,
			offendingSymbol ? offendingSymbol->getText() : "",
			msg
		);
	}

	/**
	 * @brief 存在语法错误时生成完整诊断并抛出 PACompileError-Syntax 异常
	 *
	 * @param source - DSL 源代码文本
	 */
	void throw_if_error(std::string_view source) const {
		if (m_errors.empty()) {
			return;
		}

		std::string combined_msg;
		std::string combined_hint;
		SourceLocation first_loc;
		bool first = true;

		for (const auto& error : m_errors) {
			auto friendly = explain(error);
			auto location = PostAnvilError::locate_source(source, error.line, error.column);

			if (first) {
				first_loc = std::move(location);
				combined_hint = friendly.hint;
				first = false;
			}

			combined_msg += std::format(
				"Error at line {}, column {}: {}\n  {}\n",
				error.line,
				error.column,
				friendly.message,
				friendly.hint
			);
		}

		if (m_errors.size() > 1) {
			combined_msg += std::format(
				"Total {} parser errors. Fix the first error first.\n",
				m_errors.size()
			);
			combined_hint += std::format(
				" Fix this first error before reviewing the {} following parser error(s).",
				m_errors.size() - 1
			);
		}

		throw PACompileError(
			PACompileError::Kind::Syntax,
			std::move(combined_msg),
			std::move(first_loc),
			std::move(combined_hint),
			m_errors.front().raw_message
		);
	}

private: // Friendly Error

	/**
	 * @brief 将 ANTLR4 错误信息转换为面向用户的友好提示
	 *
	 * @param error			- ANTLR4 错误信息
	 * @return FriendlyError	- 面向用户的错误说明和修改建议
	 */
	static FriendlyError explain(const Error& error) noexcept {
		const auto& token = error.offending_text;
		const auto& raw = error.raw_message;
		auto token_up = token;
		utils::to_upper_inplace(token_up);

		// TODO: 及时更新错误提示，覆盖更多常见语法错误场景

		// 逻辑运算符开头而未添加续行符的情况
		if (token_up == "OR" || token_up == "AND") {
			return {
				std::format("Logical operator '{}' cannot start a new statement.", token),
				"Move the operator to the previous line, or end the previous line "
				"with '\\' to continue the expression."
			};
		}

		// 文件终止符导致的意外结束
		if (token == "<EOF>") {
			return {
				"Unexpected end of input.",
				"Check for a missing ')' or '}' before the end of the script."
			};
		}

		const bool is_newline = token == "\n" || token == "\r\n";
		const bool expects_left_brace = raw.find("'{'") != std::string::npos
			|| raw.find("LCURLY") != std::string::npos;
		if (is_newline && expects_left_brace) {
			return {
				"Expected '{' before the end of the line.",
				"Add '{' after the rule, branch, or loop header."
			};
		}
		if (is_newline) {
			return {
				"Unexpected end of line.",
				"Complete the statement on this line, or use '\\' at the end of the line to continue it."
			};
		}
		if (raw.find("token recognition error") != std::string::npos) {
			return {
				"The input contains an unrecognized character or token.",
				"Check spelling, quotes, and supported PostAnvil operators near the marked column."
			};
		}

		std::string hint = "Check the statement structure and keyword spelling near the marked token.";
		const bool expects_right_brace = raw.find("'}'") != std::string::npos
			|| raw.find("RCURLY") != std::string::npos;
		if (expects_right_brace) {
			hint = "Close the current block with '}' and check that all braces are balanced.";
		}
		else if (raw.find("NEWLINE") != std::string::npos) {
			hint = "Put each declaration or statement on its own line.";
		}

		if (!token.empty()) {
			return { std::format("Unexpected token '{}'.", token), std::move(hint) };
		}
		return { "The source cannot be parsed near this position.", std::move(hint) };
	}

private:
	std::vector<Error> m_errors;
};

} // namespace postanvil
