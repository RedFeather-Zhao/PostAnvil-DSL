/**
 * @file   error.hpp
 * @brief  PostAnvil 编译与运行时错误类型定义
 *
 * 本文件定义了 PostAnvil 在整个处理流水线中可能抛出的所有异常类型
 * 异常体系分为三个层级：
 * - PAParseError       预留的独立解析阶段错误
 * - PACompileError     编译阶段错误，并通过 Kind 区分语法、语义和内部错误
 * - PARuntimeError     规则执行阶段错误：类型不匹配、越界访问、未定义函数等
 *
 * 所有异常均派生自 PostAnvilError
 * PACompileError 额外携带源码位置、行文本、修复提示以及原始诊断信息，
 * 方便宿主程序生成人类可读的错误报告。
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <algorithm>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <optional>

namespace postanvil {


/**
 * @brief 源码位置，不依赖 ANTLR，可安全暴露给 C++ 和 Python 宿主
 *
 * 该结构体记录了错误发生的行号、列号以及对应行的原始文本。
 * 当无法获得源码文本时，text 字段保持 std::nullopt。
 * 行号和列号均从 1 开始计数，-1 表示未知。
 */
struct SourceLocation {
	int line = -1;						//< 行号，从 1 开始，-1 表示未知
	int column = -1;					//< 列号，从 1 开始，-1 表示未知
	std::optional<std::string> text;	//< 对应行的源码文本，可能缺失
};

/**
 * @brief 所有异常的基类型，继承于 std::runtime_error
 */
class PostAnvilError : public std::runtime_error {
public:
	/**
	 * @brief 静态工具函数，用于从完整源码字符串中截取指定行的文本
	 *
	 * @param source 完整源码内容
	 * @param line   目标行号，从 1 开始
	 * @param column 目标列号，当前实现仅用于记录在返回结构中，不参与文本截取逻辑
	 * @return 包含行文本的 SourceLocation 结构
	 */
	static SourceLocation locate_source(std::string_view source, int line, int column)
	{
		SourceLocation location{ line, column, std::nullopt };
		if (line < 1) {
			return location;
		}

		// 从源文本开头开始查找当前行起始位置
		std::size_t begin = 0;
		for (size_t curr = 1; curr < line; curr++) {
			begin = source.find('\n', begin);
			if (begin == std::string_view::npos) {
				return location;
			}
			begin++; // 跳过换行符
		}

		// 查找当前行结束位置
		std::size_t end = source.find('\n', begin);
		if (end == std::string_view::npos) {
			end = source.size();
		}
		if (end > begin && source[end - 1] == '\r') {
			--end;	// 处理 Windows 换行符
		}

		auto line_text = source.substr(begin, end - begin);
		location.text = line_text;
		return location;
	}

	using std::runtime_error::runtime_error;
};

/**
 * @brief 语法解析错误，由 ANTLR 解析器抛出
 *
 * PAParseError 是语法分析阶段的专用异常，通常由 ANTLR 生成的 Lexer/Parser
 * 在遇到不符合语法规则的输入时抛出。宿主程序可以单独捕获该类型以区分
 * “源码不合法”与“编译/运行时逻辑错误”。
 */
struct PAParseError : public PostAnvilError {
	using PostAnvilError::PostAnvilError;

	// TODO: 未来可扩展为包含 ANTLR 错误上下文信息
};

/**
 * @brief 编译阶段错误，携带源码位置、提示和原始诊断信息
 *
 * PACompileError 是编译过程中抛出的主要异常类型，覆盖语义错误、类型错误、
 * 未定义符号、重复定义等。它通过 Kind 枚举区分错误的粗略类别。
 *
 * 构造函数有两种形式：
 * 1. 简单形式 PACompileError(msg, line, col)
 *    默认将 Kind 设为 Semantic，适用于大多数手工抛出的错误。
 * 2. 完整形式 PACompileError(kind, message, location, hint, raw_message)
 *    用于 ANTLR 错误监听器或更精细的错误报告场景。
 *
 * 最终的 what 字符串由内部的 format_error 静态方法生成，包含：
 * - 错误类别名称及位置行号、列号
 * - 对应源码行及插入符
 * - 错误描述信息
 * - 可选的修复提示 help:
 *
 * 访问器方法允许宿主程序提取各字段以自定义呈现方式。
 */
struct PACompileError : public PostAnvilError {
	// using PostAnvilError::PostAnvilError;

	enum class Kind {
		Syntax,			//< 语法
		Semantic,		//< 语义
		Internal		//< 内部
	};

	/**
	 * @brief 获取错误类别名称
	 *
	 * @param k		- 错误类别
	 * @return 错误类别名称
	 */
	static constexpr std::string_view kind_name(Kind k) noexcept {
		using enum Kind;
		switch (k) {
		case Syntax:	return "syntax";
		case Semantic:	return "semantic";
		case Internal:	return "internal compiler";
		default:		return "compile";
		}
	}

	/**
	 * @brief PostAnvil编译错误构造，默认为常用的语义错误类型
	 * @param msg 错误描述信息
	 * @param line 错误所在行号，默认-1表示未知
	 * @param col  错误所在列号，默认-1表示未知
	 */
	explicit PACompileError(std::string_view msg, int line = -1, int col = -1)
		: PACompileError(Kind::Semantic,
						 msg,
						 SourceLocation{ line, col, std::nullopt })
	{
	}

	/**
	 * @brief 完整构造，可指定错误类别、源码位置与提示
	 *
	 * 通常由 ANTLR 错误监听器或编译器内部在获得详细上下文后使用。
	 *
	 * @param kind        错误类别
	 * @param message     错误描述
	 * @param location    源码位置
	 * @param hint        可选的修正提示，例如正确的用法示例
	 * @param raw_message 原始诊断信息，保留用于调试或日志
	 */
	PACompileError(Kind kind,
				   std::string_view message,
				   SourceLocation location		= {},
				   std::string_view hint		= {},
				   std::string_view raw_message = {})
		: PostAnvilError(format_error(kind, message, location, hint)),
		  m_kind(kind),
		  m_message(message),
		  m_location(std::move(location)),
		  m_hint(hint),
		  m_raw_message(raw_message)
	{
	}

	[[nodiscard]] Kind kind()						const noexcept { return m_kind; }
	[[nodiscard]] const std::string& message()		const noexcept { return m_message; }
	[[nodiscard]] int line()						const noexcept { return m_location.line; }
	[[nodiscard]] int column()						const noexcept { return m_location.column; }
	[[nodiscard]] const std::string& source_line()	const noexcept { return m_location.text.value(); }
	[[nodiscard]] bool has_source_line()			const noexcept { return m_location.text.has_value(); }
	[[nodiscard]] const std::string& hint()			const noexcept { return m_hint; }
	[[nodiscard]] const std::string& raw_message()	const noexcept { return m_raw_message; }

private:
	/**
	 * @brief 生成最终的 what 字符串，包含完整诊断信息
	 *
	 * @param kind		- 错误类别
	 * @param message	- 错误描述
	 * @param location	- 源码位置
	 * @param hint		- 修正提示
	 *
	 * 输出格式示例：
	 * @code
		PostAnvil semantic error at line 3, column 14
		  3 | self.conf > 0.5
		    |               ^
		Type mismatch: expected BOOL, got NUM
		help: Use a comparison operator like '> 0.5' to produce a BOOL.
	 * @endcode
	 */
	static std::string format_error(Kind kind,
									std::string_view message,
									const SourceLocation& location,
									std::string_view hint)
	{
		// 头部：错误类型与位置
		std::string header;
		if (location.line > 0) {
			header = std::format("PostAnvil {} error at line {}", kind_name(kind), location.line);
			if (location.column > 0) {
				header += std::format(", column {}", location.column);
			}
		}
		else {
			header = std::format("PostAnvil {} error", kind_name(kind));
		}

		// 源码引用与插入符，等宽字符下对齐
		std::string source_context;
		if (location.text.has_value()) {
			const auto& line_str = location.text.value();
			const auto line_label = std::to_string(location.line);

			source_context = std::format("  {} | {}\n", line_label, line_str);
			source_context += "  " + std::string(line_label.size(), ' ') + " | ";

			std::size_t col = 0;
			if (location.column > 0) {
				col = static_cast<std::size_t>(location.column - 1);
			}
			for (std::size_t i = 0; i < col && i < line_str.size(); ++i) {
				source_context += (line_str[i] == '\t') ? '\t' : ' ';
			}
			source_context += "^\n";
		}

		// 组合完整错误信息
		std::string result = std::format("{}\n{}{}", header, source_context, message);
		if (!hint.empty()) {
			result += std::format("\nhelp: {}", hint);
		}
		return result;
	}

private:
	Kind					m_kind;
	std::string				m_message;
	SourceLocation			m_location;
	std::string				m_hint;
	std::string				m_raw_message;
};

/**
 * @brief 运行时错误（如执行 DSL 规则时发生的逻辑错误或类型错误）
 */
struct PARuntimeError : public PostAnvilError {
	using PostAnvilError::PostAnvilError;

	/**
	 * @brief 程序运行错误
	 * @param msg		错误描述信息
	 * @param op_idx	算子索引
	 * @param op_type	算子类型
	 */
	PARuntimeError(const std::string& msg, int op_idx, const std::string& op_type)
		: PostAnvilError(std::format(
			"PostAnvil error while running: operation index = {}, "
			"operation type = {} : {}\n",
			op_idx,
			op_type,
			msg))
	{
	}
};

} // namespace postanvil

