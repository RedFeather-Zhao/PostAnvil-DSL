/**
 * @file   parser.hpp
 * @brief  PostAnvil DSL 解析器，将 RULE FOR 语法文本解析为 AST
 * @detail 解析器负责：
 *         识别缩进感知的 RULE FOR 块结构
 *         使用递归下降法将条件表达式解析为 AST
 *         支持注释行（# 和 // 开头）
 * 
 * 支持的递归下降表达式语法：
 * @code
 *		expr      := or_expr
 *		or_expr   := and_expr ("OR" and_expr)*
 *		and_expr  := not_expr ("AND" not_expr)*
 *		not_expr  := "NOT" not_expr | cmp_expr
 *		cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
 *		add_expr  := mul_expr ( ("+"|"-") mul_expr )*
 *		mul_expr  := unary_expr ("*" unary_expr)*
 *		unary_expr:= ("-" )? primary
 *		primary   := number | identifier [ ("." identifier)* | '(' arglist ')' ] | '(' expr ')'
 * @endcode
 * 
 * 
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <functional>
#include "postanvil/ast.hpp"
#include "postanvil/lexer.hpp"

namespace postanvil {

/**
 * @brief 解析异常类，携带行号和列号信息。
 */
class ParseError : public std::runtime_error {
public:
	int line; //< 出错行号（-1 表示未知）
	int col;  //< 出错列号（-1 表示未知）
	
	/**
	 * @brief 构造解析异常
	 * @param m 错误消息
	 * @param l 行号，默认为 -1
	 * @param c 列号，默认为 -1
	 */
	explicit ParseError(const std::string &m, int l=-1, int c=-1)
		: std::runtime_error(m), line(l), col(c)
	{
	}
};

/**
 * @brief PostAnvil DSL 解析器。
 *
 * 解析器读取 DSL 源文本，识别 RULE FOR 块结构，
 * 并将每个条件表达式解析为 AST 节点。
 */
class Parser {
	enum class State {
		OUT_RULE,	// 
		IN_RULE,	// 
	}; //< 状态机

public:
	/**
	 * @brief 解析 DSL 源文本，生成规则列表。
	 *
	 * 解析过程：
	 * 1. 按行读取源文本
	 * 2. 识别 `RULE FOR <target>:` 头部
	 * 3. 收集缩进块内的条件表达式
	 * 4. 对每个条件表达式调用递归下降解析器
	 *
	 * @param src DSL 源文本
	 * @param[out] out_rules 解析生成的规则列表
	 * @return 解析成功返回 true
	 * @throws ParseError 语法错误时抛出
	 * @throws std::runtime_error 格式错误时抛出
	 */
	bool parse(const std::string& src, std::vector<Rule>& out_rules) {
		out_rules.clear();
		
		std::istringstream ss(src);
		std::string raw_line;
		Rule current;
		State state = State::OUT_RULE;
		int rule_indent = -1;
		int lineno = 0;
		bool reparse_line = false; // 是否重新解析当前行（用于规则块结束后检查新规则头部）

		// 循环主体，按行读取解析源文本
		while (true) {
			if (reparse_line == false && !std::getline(ss, raw_line)) {
				break;
			}
			reparse_line = false;
			
			std::string line = trim(raw_line);

			// 1. 跳过空行和注释行
			if (line.empty()) {
				continue;
			}
			if (starts_with(line, "#") || starts_with(line, "//")) {
				continue;
			}

			// 2. 状态机：规则块外，解析规则头部 "RULE FOR"
			if (state == State::OUT_RULE) {
				std::string up = to_upper(line);
				auto [matched, pos] = starts_with_seg(up, {"RULE", "FOR"});
				if (matched) {
					size_t colon = line.find(':', pos);
					if (colon == std::string::npos) {
						throw ParseError("Missing ':' in RULE FOR header", lineno, (int)line.size());
					}
					current = Rule();
					current.target = trim(std::string_view(line).substr(pos, colon - pos));
					state = State::IN_RULE;
					rule_indent = -1;
				}
				continue;
			}

			// 3. 状态机：规则块内，解析条件表达式
			if (state == State::IN_RULE) {
				int leading = count_leading(raw_line);
				
				// 记录规则块的缩进量，首次遇到非空行时确定缩进
				if (rule_indent == -1) {
					if (leading == 0) {
						throw ParseError("Expected indented block after RULE FOR header", lineno);
					}
					rule_indent = leading;
				}

				// 检查缩进是否小于规则块缩进，若是且非空行，则表示规则块结束，否则继续解析条件表达式
				if (leading < rule_indent && !trim(raw_line).empty()) {
					// 块结束，保存当前规则并重置状态
					out_rules.push_back(std::move(current));
					current = Rule();
					state = State::OUT_RULE;
					rule_indent = -1;

					// 重解析当前行
					reparse_line = true;
					continue;
				}

				// 解析条件表达式字符串为 AST
				const std::string& cond = line;
				auto expr = parse_condition_expr(cond, lineno);
				current.conditions.push_back(std::move(expr));
			}
		}

		// 处理文件末尾的规则块，如果仍在规则块内，则保存当前规则
		if (state== State::IN_RULE) {
			out_rules.push_back(std::move(current));
		}
		return true;
	}

private: // Tool functions for parsing

	/**
	 * @brief 去除字符串首尾空白字符。
	 * @param s 输入字符串
	 * @return 去除首尾空白后的字符串
	 */
	static inline std::string
	trim(std::string_view s)
	{
		size_t a = 0;
		while (a < s.size() && std::isspace((unsigned char)s[a])) {
			++a;
		}
		size_t b = s.size();
		while (b > a && std::isspace((unsigned char)s[b - 1])) {
			--b;
		}
		return std::string(s.substr(a, b - a));
	}

	/**
	 * @brief 检查字符串视图是否以指定前缀开头，低内存开销
	 * @param str    - 待检查字符串视图
	 * @param prefix - 前缀视图
	 * @return 匹配返回true
	 */
	static inline bool
	starts_with(std::string_view str, std::string_view prefix)
	{
		return str.size() >= prefix.size()
			&& str.compare(0, prefix.size(), prefix) == 0;
	}

	/**
	 * @brief 检查字符串是否以指定前缀列表开头，列表元素按序匹配，忽略元素间隔空白符号。
	 * @note  首个前缀严格匹配，后续前缀允许空白间隔
	 * 如
	 *	str = "RULE FOR   CLASSA   :   "
	 *	prefixes = {"RULE", "FOR"}
	 * 则返回 true。
	 * @param str      - 待检查字符串
	 * @param prefixes - 前缀列表
	 * @return 返回 std::pair<bool, size_t>，first 为是否匹配，second 为当前匹配到的字符位置
	 */
	static inline std::pair<bool, size_t>
	starts_with_seg(std::string_view str, const std::vector<std::string_view>& prefixes)
	{
		size_t pos = 0;
		for (const auto& p : prefixes) {
			if (starts_with(str.substr(pos), p) == false) {
				return std::make_pair(false, pos);
			}
			pos += p.size();

			while (pos < str.size() && std::isspace((unsigned char)str[pos])) {
				pos++;
			}
		}
		return std::make_pair(true, pos);
	}

	/**
	 * @brief 计算行首空白字符数，制表符按指定对齐宽度计算。
	 * @param s - 输入字符串
	 * @return 行首空白字符数
	 */
	static inline int
	count_leading(std::string_view s, int tab_width = 4)
	{
		int total = 0;
		for (unsigned char c : s) {
			if (c == ' ') {
				total += 1;
			}
			else if (c == '\t') {
				if (total % tab_width != 0) {
					total += tab_width - (total % tab_width);
				}
				else {
					total += tab_width;
				}
			}
			else {
				break;
			}
		}
		return total;
	}

	/**
	 * @brief 将字符串转换为大写。
	 * @param s 输入字符串视图
	 * @return 大写字符串
	 */
	static inline std::string
	to_upper(std::string_view s)
	{
		std::string res(s);
		for (char& c : res) {
			c = static_cast<char>(toupper(static_cast<unsigned char>(c)));
		}
		return res;
	}

	/**
	 * @brief 使用递归下降法将单行条件表达式解析为 AST。
	 *
	 * 支持的语法层次：
	 * @code
	 * expr      := or_expr
	 * or_expr   := and_expr ("OR" and_expr)*
	 * and_expr  := not_expr ("AND" not_expr)*
	 * not_expr  := "NOT" not_expr | cmp_expr
	 * cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
	 * add_expr  := mul_expr ( ("+"|"-") mul_expr )*
	 * mul_expr  := unary_expr ("*" unary_expr)*
	 * unary_expr:= ("-")? primary
	 * primary   := number | identifier [ ("." identifier)* | '(' arglist ')' ] | '(' expr ')'
	 * @endcode
	 *
	 * @param s 条件表达式字符串
	 * @param lineno 行号（用于错误报告）
	 * @return 解析后的 AST 根节点
	 * @throws std::runtime_error 语法错误时抛出
	 */
	std::unique_ptr<Expr> parse_condition_expr(const std::string& s, int lineno = 0) {
		auto tokens = tokenize_expr(s);
		size_t pos = 0;
		
		// 递归下降解析器的辅助函数：peek - 查看当前 token，consume - 消耗当前 token 并前进
		auto peek = [&](size_t k = 0) -> Token& {
			return tokens[pos + k];
		};
		auto consume = [&](void) ->Token& {
			return tokens[pos++];
		};

		// 递归下降解析函数声明
		using ParseFunc = std::function<std::unique_ptr<Expr>()>;
		ParseFunc parse_expr;		// 
		ParseFunc parse_or;			// 
		ParseFunc parse_and;		// 
		ParseFunc parse_not;		// 
		ParseFunc parse_cmp;		// 
		ParseFunc parse_add;		// 
		ParseFunc parse_mul;		// 
		ParseFunc parse_unary;		// 
		ParseFunc parse_primary;	// 
		
		using enum TokenKind;

		// expr      := or_expr
		parse_expr = [&] {
			return parse_or();
		};

		// or_expr   := and_expr ("OR" and_expr)*
		parse_or = [&] {
			auto left = parse_and();
			while (peek().kind == Keyword && to_upper(peek().text) == "OR") {
				consume();
				auto right = parse_and();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), "OR", std::move(right)));
			}
			return left;
		};

		// and_expr  := not_expr ("AND" not_expr)*
		parse_and = [&] {
			auto left = parse_not();
			while (peek().kind == Keyword && to_upper(peek().text) == "AND") {
				consume();
				auto right = parse_not();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), "AND", std::move(right)));
			}
			return left;
		};

		// not_expr  := "NOT" not_expr | cmp_expr
		parse_not = [&] {
			if (peek().kind == Keyword && to_upper(peek().text) == "NOT") {
				consume();
				auto rhs = parse_not();
				return std::unique_ptr<Expr>(std::make_unique<UnaryExpr>("NOT", std::move(rhs)));
			}
			return parse_cmp();
		};

		// cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
		parse_cmp = [&] {
			auto left = parse_add();
			while (peek().kind == Op
				&& (peek().text == "<"
				|| peek().text == ">"
				|| peek().text == "<="
				|| peek().text == ">="
				|| peek().text == "=="
				|| peek().text == "!="))
			{
				std::string op = consume().text;
				auto right = parse_add();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), op, std::move(right)));
			}
			return left;
		};

		// add_expr  := mul_expr ( ("+"|"-") mul_expr )*
		parse_add = [&] {
			auto left = parse_mul();
			while (peek().kind == Op && (peek().text == "+" || peek().text == "-")) {
				std::string op = consume().text;
				auto right = parse_mul();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), op, std::move(right)));
			}
			return left;
		};

		// mul_expr  := unary_expr ("*" unary_expr)*
		parse_mul = [&] {
			auto left = parse_unary();
			while (peek().kind == Op && peek().text == "*") {
				consume();
				auto right = parse_unary();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), "*", std::move(right)));
			}
			return left;
		};

		// unary_expr:= ("-")? primary
		parse_unary = [&] {
			if (peek().kind == Op && peek().text == "-") {
				consume();
				auto rhs = parse_unary();
				return std::unique_ptr<Expr>(std::make_unique<UnaryExpr>("-", std::move(rhs)));
			}
			return parse_primary();
		};

		// primary   := number | identifier [ ("." identifier)* | '(' arglist ')' ] | '(' expr ')'
		parse_primary = [&] {
			// 数字终结符
			if (peek().kind == Number) {
				double v = std::stod(consume().text);
				return std::unique_ptr<Expr>(std::make_unique<NumberExpr>(v));
			}

			// 标识符终结符，可能是函数调用或属性访问
			if (peek().kind == Identifier) {
				std::string id = consume().text;
				
				// 函数调用形式：name(arg1, arg2, ...)
				if (peek().kind == Op && peek().text == "(") {
					consume();
					auto call = std::make_unique<CallExpr>(id);

					if (!(peek().kind == Op && peek().text == ")")) {
						while (true) {
							call->args.push_back(parse_expr());
							if (peek().kind == Op && peek().text == ",") {
								consume();
								continue;
							}
							break;
						}
					}
					if (!(peek().kind == Op && peek().text == ")")) {
						throw ParseError("Expected ) in call", lineno);
					}
					consume(); // "("
					
					return std::unique_ptr<Expr>(call.release());
				}

				// 空格分隔的断言式调用语法：函数名 参数 1 参数 2 … [数量范围]
				if (peek().kind == Identifier || peek().kind == Number) {
					auto call = std::make_unique<CallExpr>(id);

					// 收集所有位置参数（支持标识符、数字、属性访问表达式）
					while (peek().kind == Identifier || peek().kind == Number || (peek().kind == Op && peek().text == ".")) {
						// 标识符参数
						if (peek().kind == Identifier) {
							call->args.push_back(std::unique_ptr<Expr>(std::make_unique<IdentExpr>(consume().text)));
							continue;
						}

						// 数字参数，此处的数字可能是独立参数数量限制（单值），或是区间范围的起始数字
						if (peek().kind == Number) {
							std::string numtxt = consume().text;
							auto v = (int)std::stod(numtxt);

							// 判断是否为 a-b 形式的区间范围
							if (peek().kind == Op && peek().text == "-") {
								consume();
								if (peek().kind == Number) {
									auto v2 = (int)std::stod(consume().text);
									call->qtyRange = std::make_unique<QuantityRange>(v, v2);
									break;
								}
								else {
									throw ParseError("Expected number after - in quantity range", lineno);
								}
							}
							else {
								// 单个数量限制
								call->qtyRange = std::make_unique<QuantityRange>(v);
								break;
							}
						}

						// 处理形如 Class.prop 的点号属性访问语法，将其构建为属性访问表达式 PropAccessExpr
						if (peek().kind == Op && peek().text == ".") {
							// 前一个token必须是代表对象的标识符 for obj
							// 消费掉点号 '.' 以及后续的属性标识符r
							// 我们会用参数列表里最后一个标识符构造属性访问表达式 PropAccessExprExpr constructed from the last identifier argument
							// 如果前面没有任何参数，则直接抛出错误
							consume();
							if (peek().kind != Identifier) {
								throw ParseError("Expected identifier after .", lineno);
							}
							std::string prop = consume().text;

							if (call->args.empty()) {
								throw ParseError("Unexpected . without object in predicate args", lineno);
							}

							// 取出最后一个参数标识符作为对象名，并将其替换为属性访问表达式
							auto&& last = std::move(call->args.back());
							auto const* ie = static_cast<IdentExpr*>(last.get());
							std::string obj = ie->name;
							call->args.pop_back();
							call->args.push_back(std::unique_ptr<Expr>(std::make_unique<PropAccessExpr>(obj, prop)));
							continue;
						}
					}
					return std::unique_ptr<Expr>(call.release());
				}
				
				// 属性访问链 id(.id)*
				if (peek().kind == Op && peek().text == ".") {
					std::string obj = id;
					if (peek().kind == Op && peek().text == ".") {
						consume();
						if (peek().kind != Identifier) {
							throw ParseError("Expected identifier after .", lineno);
						}
						std::string prop = consume().text;
						return std::unique_ptr<Expr>(std::make_unique<PropAccessExpr>(obj, prop));
					}
				}
				return std::unique_ptr<Expr>(std::make_unique<IdentExpr>(id));
			}

			// 括号表达式
			if (peek().kind == Op && peek().text == "(") {
				consume();
				auto e = parse_expr();
				if (!(peek().kind == Op && peek().text == ")")) {
					throw ParseError("Expected )", lineno);
				}
				consume();
				return e;
			}
			throw ParseError("Unexpected token in expression", lineno);
		};

		auto res = parse_expr();
		if (peek().kind != End) {
			// allow trailing
		}
		return res;
	}

};

} // namespace postanvil