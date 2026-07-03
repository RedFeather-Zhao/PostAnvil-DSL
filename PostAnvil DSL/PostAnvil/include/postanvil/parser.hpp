/**
 * @file   parser.hpp
 * @brief  PostAnvil DSL 解析器，将 RULE FILTER / RULE ATTR 语法文本解析为 AST
 * @detail 解析器负责：
 *         识别缩进感知的 RULE FILTER / RULE ATTR 块结构
 *         使用递归下降法将条件表达式解析为 AST
 *         支持注释行（# 和 // 开头）
 *         所有标识符在词法分析阶段已转为大写，实现大小写不敏感
 *
 * 支持的递归下降表达式语法：
 * @code
 *        expr      := or_expr
 *        or_expr   := and_expr ("OR" and_expr)*
 *        and_expr  := not_expr ("AND" not_expr)*
 *        not_expr  := "NOT" not_expr | cmp_expr
 *        cmp_expr  := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
 *        add_expr  := mul_expr ( ("+"|"-") mul_expr )*
 *        mul_expr  := unary_expr ( ("*"|"/") unary_expr )*
 *        unary_expr:= ("-" )? primary
 *        primary   := number
 *                   | identifier [ '(' arglist ')' | arg+ [qty_range] | '.' identifier ]
 *                   | '(' expr ')'
 *        arg       := identifier | number | identifier '.' identifier
 *        arglist   := expr (',' expr)*
 *        qty_range := number | number '-' number
 *
 *        attr_assign := identifier '=' expr
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
#include <format>
#include "postanvil/ast.hpp"
#include "postanvil/lexer.hpp"

namespace postanvil {

/**
 * @brief 解析异常类，携带行号和列号信息
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
	explicit ParseError(const std::string &m, int l = -1, int c = -1)
		: std::runtime_error(std::format("parse error: {}, line: {}, col: {}", m, l, c))
		, line(l), col(c)
	{
	}
};

/**
 * @brief PostAnvil DSL 解析器
 *
 * 解析器读取 DSL 源文本，通过状态机识别 RULE FILTER / RULE ATTR 块结构，
 * 内部 ExprParser 使用递归下降法将每个条件表达式解析为 AST 节点
 */
class Parser {
	/**
	 * @brief 解析状态机：识别 RULE 块结构的当前状态
	 */
	enum class State {
		OUT_RULE,	//< 规则块外，等待 RULE FILTER / RULE ATTR 头部
		IN_RULE,	//< 规则块内，解析条件表达式或属性赋值
	};

	using Token = Lexer::Token;
	using enum Lexer::TokenKind;

public:
	/**
	 * @brief 解析 DSL 源文本，生成规则列表
	 *
	 * 状态机流程：
	 * 1. OUT_RULE  - 逐行扫描，调用 parse_rule_header() 识别 RULE FILTER <target>: 或 RULE ATTR <target>: 头部
	 * 2. IN_RULE   - 收集缩进块内的内容，根据 RuleKind 分发：
	 *                - FILTER: 条件表达式，交给 ExprParser 递归下降解析
	 *                - ATTR:   属性赋值（name = expr），交给 ExprParser::parse_attr_assign()
	 * 3. 缩进回归  - 规则块结束，保存当前规则，reparse_line 标记当前行重新检查
	 * 4. EOF       - 若仍在规则块内，保存最后一个规则
	 *
	 * @param src DSL    - 源文本
	 * @param out_rules  - 解析生成的规则列表
	 * @return bool 解析成功返回 true
	 * @throws ParseError 语法错误时抛出
	 */
	static bool parse(const std::string& src, std::vector<Rule>& out_rules) {
		out_rules.clear();

		// 将源文本按行拆分，保留原始行内容
		std::vector<std::string> raw_lines;
		std::istringstream ss(src);
		std::string line;
		while (std::getline(ss, line)) {
			for (auto& ch : line) {
				ch = (char)std::toupper(static_cast<unsigned char>(ch));
			}
			raw_lines.push_back(line);
		}

		ExprParser parser;
		Rule curr_rule;
		auto state = State::OUT_RULE;
		int rule_indent = -1;

		size_t i = 0;
		while (i < raw_lines.size()) {
			const std::string& raw_line = raw_lines[i];
			std::string trimmed = trim(raw_line);
			int lineno = static_cast<int>(i) + 1;

			// 空行或注释，直接跳过
			if (trimmed.empty() || starts_with(trimmed, "#") || starts_with(trimmed, "//")) {
				++i;
				continue;
			}

			if (state == State::OUT_RULE) {
				// 处理 RULE FILTER / RULE ATTR 头部
				if (parse_rule_header(trimmed, lineno, curr_rule)) {
					state = State::IN_RULE;
					rule_indent = -1;   // 等待首次缩进确定
				}
				++i;
				continue;
			}

			// IN_RULE
			int leading = count_leading(raw_line);

			if (rule_indent == -1) {
				if (leading == 0) {
					throw ParseError("Expected indented block after RULE header", lineno);
				}
				rule_indent = leading;
			}

			// 缩进减少且当前行非空：规则块结束
			if (leading < rule_indent && !trim(raw_line).empty()) {
				out_rules.push_back(std::move(curr_rule));
				curr_rule = Rule();
				state = State::OUT_RULE;
				rule_indent = -1;
				// 注意：这里不 ++i，让当前行在下一次循环中以 OUT_RULE 状态重新处理
				continue;
			}

			// 根据规则类型解析行内容
			if (curr_rule.kind == RuleKind::FILTER) {
				auto expr = parser.parse_condition_expr(trimmed, lineno);
				curr_rule.conditions.push_back(std::move(expr));
			} else if (curr_rule.kind == RuleKind::ATTR) {
				auto [name, expr] = parser.parse_attr_assign(trimmed, lineno);
				curr_rule.assignments.emplace_back(std::move(name), std::move(expr));
			}
			++i;
		}

		// 文件末尾若还在规则块内，则保存最后一个规则
		if (state == State::IN_RULE) {
			out_rules.push_back(std::move(curr_rule));
		}

		return true;
	}

private: // Tool functions for parsing
	/**
	 * @brief 解析 RULE FILTER / RULE ATTR 头部，提取目标类别名称和规则类型
	 *
	 * 匹配格式：RULE FILTER <target>: 或 RULE ATTR <target>:
	 * - 先匹配 "RULE" 前缀（大小写不敏感）
	 * - 再匹配 "FILTER" 或 "ATTR" 关键字
	 * - 最后查找冒号分隔符，提取中间的目标类别名
	 *
	 * @param line   - 当前行内容（已去除首尾空白）
	 * @param lineno - 当前行号，用于错误报告
	 * @param[out] rule - 解析结果写入此规则对象
	 * @return true 表示成功匹配 RULE 头部，false 表示当前行不是规则头部
	 * @throws ParseError 如果匹配到前缀但缺少冒号
	 */
	static bool
	parse_rule_header(std::string_view line, int lineno, Rule& rule)
	{
		// 匹配 "RULE" 前缀
		if (!starts_with(line, "RULE")) {
			return false;
		}

		size_t pos = 4; // 跳过 "RULE"
		while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
			++pos;
		}

		// 匹配 "FILTER" 或 "ATTR"
		bool is_filter = false;
		bool is_attr = false;

		if (starts_with(line.substr(pos), "FILTER")) {
			is_filter = true;
			pos += 6;
		} else if (starts_with(line.substr(pos), "ATTR")) {
			is_attr = true;
			pos += 4;
		} else {
			return false;
		}

		// 跳过空白
		while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
			++pos;
		}

		size_t colon = line.find(':', pos);
		if (colon == std::string::npos) {
			throw ParseError("Missing ':' in RULE header", lineno, (int)line.size());
		}

		rule = Rule();
		rule.kind = is_filter ? RuleKind::FILTER : RuleKind::ATTR;
		rule.target = trim(line.substr(pos, colon - pos));
		return true;
	}

	/**
	 * @brief 去除字符串首尾空白字符
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
	 * @brief 计算行首空白字符数，制表符按指定对齐宽度计算
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

//==================== Expression parsing ========================

	/**
	 * @brief 内部递归下降解析器，将条件表达式字符串解析为 AST
	 */
	class ExprParser {
	private:
		/**
		 * @brief 查看当前 token，支持向前 k 个 token
		 * @param k - 向前偏移量，默认 0 表示当前 token
		 * @return const Token& - 当前 token 的引用
		 */
		const Token& peek(size_t k = 0) const {
			return m_tokens[m_pos + k];
		}

		/**
		 * @brief 消耗当前 token 并前进到下一个 token
		 * @return const Token& - 被消耗的 token 的引用
		 */
		const Token& consume() {
			return m_tokens[m_pos++];
		}

		/**
		 * @brief 解析表达式，规则：expr := or_expr
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_expr() {
			return parse_or();
		}

		/**
		 * @brief 解析逻辑或表达式，规则：or_expr := and_expr ("OR" and_expr)*
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的逻辑或表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_or() {
			auto left = parse_and();
			while (peek().kind == Keyword && peek().text == "OR") {
				consume();
				auto right = parse_and();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), "OR", std::move(right)));
			}
			return left;
		}

		/**
		 * @brief 解析逻辑与表达式，规则：and_expr := not_expr ("AND" not_expr)*
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的逻辑与表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_and() {
			auto left = parse_not();
			while (peek().kind == Keyword && peek().text == "AND") {
				consume();
				auto right = parse_not();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), "AND", std::move(right)));
			}
			return left;
		}

		/**
		 * @brief 解析逻辑非表达式，规则：not_expr := "NOT" not_expr | cmp_expr
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的逻辑非表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_not() {
			if (peek().kind == Keyword && peek().text == "NOT") {
				consume();
				auto rhs = parse_not();
				return std::unique_ptr<Expr>(std::make_unique<UnaryExpr>("NOT", std::move(rhs)));
			}
			return parse_cmp();
		}

		/**
		 * @brief 解析比较表达式，规则：cmp_expr := add_expr ( ("<"|">"|"<="|">="|"=="|"!=") add_expr )*
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的比较表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_cmp() {
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
		}

		/**
		 * @brief 解析加法表达式，规则：add_expr := mul_expr ( ("+"|"-") mul_expr )*
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的加法表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_add() {
			auto left = parse_mul();
			while (peek().kind == Op && (peek().text == "+" || peek().text == "-")) {
				std::string op = consume().text;
				auto right = parse_mul();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), op, std::move(right)));
			}
			return left;
		}

		/**
		 * @brief 解析乘法表达式，规则：mul_expr := unary_expr ("*" unary_expr)*
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的乘法表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_mul() {
			auto left = parse_unary();
			while (peek().kind == Op && (peek().text == "*" || peek().text == "/")) {
				std::string op = consume().text;
				auto right = parse_unary();
				left = std::unique_ptr<Expr>(std::make_unique<BinaryExpr>(std::move(left), op, std::move(right)));
			}
			return left;
		}

		/**
		 * @brief 解析一元表达式，规则：unary_expr := ("-")? primary
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的一元表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_unary() {
			if (peek().kind == Op && peek().text == "-") {
				consume();
				auto rhs = parse_unary();
				return std::unique_ptr<Expr>(std::make_unique<UnaryExpr>("-", std::move(rhs)));
			}
			return parse_primary();
		}

		/**
		 * @brief 解析基本表达式，规则：primary := number | identifier [ '(' arglist ')' | arg+ [qty_range] | '.' identifier ] | '(' expr ')'
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的基本表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_primary() {
			// 数字
			if (peek().kind == Number) {
				return parse_number();
			}

			// 标识符
			if (peek().kind == Identifier) {
				return parse_identifier_primary();
			}

			// 括号表达式
			if (peek().kind == Op && peek().text == "(") {
				return parse_paren_expr();
			}

			throw ParseError("Unexpected token in expression", m_lineno);
		}

		/**
		 * @brief 解析数字字面量，规则：number := [0-9]+(\.[0-9]+)?
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的数字表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_number() {
			double v = std::stod(consume().text);
			return std::make_unique<NumberExpr>(v);
		}

		/**
		 * @brief 解析标识符开头的基本表达式，规则：identifier [ '(' arglist ')' | arg+ [qty_range] | '.' identifier ]
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_identifier_primary() {
			std::string id = consume().text;

			// 函数调用形式：name(arg1, arg2, ...)
			if (peek().kind == Op && peek().text == "(") {
				return parse_function_call(id);
			}

			// 空格分隔的断言式调用语法：函数名 参数1 参数2 … [数量范围]
			// 保留解析能力，但编译阶段暂不实现（谓词功能待未来重新设计）
			if (peek().kind == Identifier || peek().kind == Number) {
				return parse_predicate_call(id);
			}

			// 属性访问链 id(.id)*
			if (peek().kind == Op && peek().text == ".") {
				return parse_property_access(id);
			}

			// 普通标识符
			return std::make_unique<IdentExpr>(id);
		}

		/**
		 * @brief 解析标准函数调用，规则：'(' arglist ')'
		 *
		 * 保留解析能力，编译阶段暂不实现（函数功能待未来重新设计）
		 *
		 * @param id 函数名
		 * @return std::unique_ptr<Expr> - 解析得到的 CallExpr AST 节点
		 */
		std::unique_ptr<Expr> parse_function_call(const std::string& id) {
			consume(); // 消耗 '('
			auto call = std::make_unique<CallExpr>(id);

			// 解析参数列表
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

			// 验证并消耗 ')'
			if (!(peek().kind == Op && peek().text == ")")) {
				throw ParseError("Expected ) in call", m_lineno);
			}
			consume(); // 消耗 ')'

			return call;
		}

		/**
		 * @brief 解析断言式调用，规则：arg+ [qty_range]
		 *
		 * 保留解析能力，但编译阶段暂不实现（谓词功能待未来重新设计）
		 *
		 * @param id 函数名
		 * @return std::unique_ptr<Expr> - 解析得到的 CallExpr AST 节点
		 */
		std::unique_ptr<Expr> parse_predicate_call(const std::string& id) {
			auto call = std::make_unique<CallExpr>(id);

			// 收集所有位置参数（支持标识符、数字、属性访问表达式）
			while (peek().kind == Identifier || peek().kind == Number || (peek().kind == Op && peek().text == ".")) {
				if (peek().kind == Identifier) {
					parse_identifier_argument(*call);
				}
				else if (peek().kind == Number) {
					if (parse_quantity_range(*call)) {
						break; // 数量范围是最后一个参数
					}
					// 否则是普通数字参数，继续循环
				}
				else if (peek().kind == Op && peek().text == ".") {
					parse_property_access_argument(*call);
				}
			}

			return call;
		}

		/**
		 * @brief 解析断言式调用中的标识符参数，规则：identifier
		 *
		 * @param[out] call 目标 CallExpr
		 */
		void parse_identifier_argument(CallExpr& call) {
			call.args.push_back(std::make_unique<IdentExpr>(consume().text));
		}

		/**
		 * @brief 解析数量范围，规则：qty_range := number | number '-' number
		 *
		 * @param[out] call 目标 CallExpr，数量范围写入 call.qtyRange
		 * @return true 表示已解析数量范围（断言式调用的参数列表结束）
		 */
		bool parse_quantity_range(CallExpr& call) {
			std::string numtxt = consume().text;
			auto v = (int)std::stod(numtxt);

			// 判断是否为 a-b 形式的区间范围
			if (peek().kind == Op && peek().text == "-") {
				consume();
				if (peek().kind != Number) {
					throw ParseError("Expected number after - in quantity range", m_lineno);
				}
				auto v2 = (int)std::stod(consume().text);
				call.qtyRange = std::make_unique<QuantityRange>(v, v2);
				return true;
			}
			else {
				// 单个数量限制
				call.qtyRange = std::make_unique<QuantityRange>(v);
				return true;
			}
		}

		/**
		 * @brief 解析断言式调用中的属性访问参数，规则：'.' identifier
		 *
		 * @param[out] call 目标 CallExpr
		 */
		void parse_property_access_argument(CallExpr& call) {
			consume(); // 消耗 '.'
			if (peek().kind != Identifier) {
				throw ParseError("Expected identifier after .", m_lineno);
			}
			std::string prop = consume().text;

			if (call.args.empty()) {
				throw ParseError("Unexpected . without object in predicate args", m_lineno);
			}

			// 取出最后一个参数标识符作为对象名，并将其替换为属性访问表达式
			auto&& last = std::move(call.args.back());
			auto const* ie = static_cast<IdentExpr*>(last.get());
			std::string obj = ie->name;
			call.args.pop_back();
			call.args.push_back(std::make_unique<PropAccessExpr>(obj, prop));
		}

		/**
		 * @brief 解析属性访问链，规则：'.' identifier
		 *
		 * @param obj 对象名
		 * @return std::unique_ptr<Expr> - 解析得到的 PropAccessExpr AST 节点
		 */
		std::unique_ptr<Expr> parse_property_access(const std::string& obj) {
			if (peek().kind == Op && peek().text == ".") {
				consume(); // 消耗 '.'
				if (peek().kind != Identifier) {
					throw ParseError("Expected identifier after .", m_lineno);
				}
				std::string prop = consume().text;
				return std::make_unique<PropAccessExpr>(obj, prop);
			}
			throw ParseError("Expected . for property access", m_lineno);
		}

		/**
		 * @brief 解析括号分组表达式，规则：'(' expr ')'
		 *
		 * @return std::unique_ptr<Expr> - 解析得到的括号内表达式 AST 节点
		 */
		std::unique_ptr<Expr> parse_paren_expr() {
			consume(); // 消耗 '('
			auto e = parse_expr();
			if (!(peek().kind == Op && peek().text == ")")) {
				throw ParseError("Expected )", m_lineno);
			}
			consume(); // 消耗 ')'
			return e;
		}

	public:
		/**
		 * @brief 使用递归下降法将单行条件表达式解析为 AST，规则：expr
		 *
		 * @param s       条件表达式字符串
		 * @param lineno  行号（用于错误报告）
		 * @return std::unique_ptr<Expr> - 解析后的 AST 根节点
		 * @throws ParseError 语法错误时抛出
		 */
		std::unique_ptr<Expr> parse_condition_expr(const std::string& s, int lineno = 0) {
			m_tokens = Lexer::tokenize_expr(s);
			m_pos = 0;
			m_lineno = lineno;

			using enum Lexer::TokenKind;

			auto res = parse_expr();
			if (peek().kind != End) {
				// allow trailing
			}
			return res;
		}

		/**
		 * @brief 解析属性赋值语句，规则：attr_assign := identifier '=' expr
		 *
		 * 用于 RULE ATTR 规则中的属性赋值行。
		 *
		 * @param s       赋值语句字符串
		 * @param lineno  行号（用于错误报告）
		 * @return std::pair<std::string, std::unique_ptr<Expr>> 属性名和值表达式
		 * @throws ParseError 语法错误时抛出
		 */
		std::pair<std::string, std::unique_ptr<Expr>> parse_attr_assign(const std::string& s, int lineno = 0) {
			m_tokens = Lexer::tokenize_expr(s);
			m_pos = 0;
			m_lineno = lineno;

			// 解析属性名（标识符）
			if (peek().kind != Identifier) {
				throw ParseError("Expected attribute name in assignment", m_lineno);
			}
			std::string attr_name = consume().text;

			// 解析 '='
			if (!(peek().kind == Op && peek().text == "=")) {
				throw ParseError("Expected '=' in attribute assignment", m_lineno);
			}
			consume();

			// 解析值表达式
			auto expr = parse_expr();

			return {std::move(attr_name), std::move(expr)};
		}

	private:
		std::vector<Lexer::Token> m_tokens;	//< 词法分析后的 token 序列
		size_t m_pos = 0;			//< 当前 token 位置
		int m_lineno = 0;			//< 当前行号（用于错误报告）
	};
};

} // namespace postanvil