/**
 * @file   lexer.hpp
 * @brief  PostAnvil DSL 的词法分析器声明，用于将条件表达式拆分为 token 序列
 *
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <cctype>
#include <string>
#include <vector>

namespace postanvil {

	/**
	 * @brief PostAnvil DSL 词法分析器
	 */
	class Lexer {
	public: // Token
		/**
		 * @brief 词法单元类型
		 */
		enum class TokenKind {
			End,		//< 表示输入结束
			Identifier,	//< 标识符
			Number,		//< 数字常量
			Op,			//< 操作符和标点
			Keyword,	//< 关键字（AND/OR/NOT 等）

			Error,		//< 错误 token
		};

		/**
		 * @brief 词法单元结构
		 */
		struct Token {
			TokenKind kind;		//< 单元类型1
			std::string text;	//< 原始文本或错误信息
		};

	public: // public methods
		/**
		 * @brief 将表达式字符串拆分为 Token 序列，并以 End token 结尾
		 * @param s - 输入表达式字符串（单行）
		 * @return Token 向量，末尾包含一个 End token
		 */
		static std::vector<Token>
			tokenize_expr(const std::string& s)
		{
			std::vector<Token> out;
			size_t i = 0;
			auto len = s.size();

			while (i < len) {
				auto c = static_cast<unsigned char>(s[i]);

				// 跳过空白字符
				if (std::isspace(c)) {
					i = skip_whitespace(s, i);
				}
				// 标识符 & 关键字
				else if (std::isalpha(c) || c == '_') {
					auto [j, token] = parse_identifier(s, i);
					out.emplace_back(std::move(token));
					i = j;
				}
				// 数字字面量（整数或浮点数）
				else if (std::isdigit(c) || (c == '.' && i + 1 < s.size() && std::isdigit(static_cast<unsigned char>(s[i + 1])))) {
					auto [j, token] = parse_number(s, i);
					out.emplace_back(std::move(token));
					i = j;
				}
				// 操作符与标点
				else {
					auto [new_i, tok] = parse_operator(s, i);
					out.push_back(std::move(tok));
					i = new_i;
				}
			}
			out.emplace_back(TokenKind::End, "");
			return out;
		}

	private: // private methods
		/**
		 * @brief 跳过字符串中的空白字符，返回第一个非空白字符的位置
		 *
		 * @param str - 输入字符串视图
		 * @param pos - 起始位置
		 * @return size_t - 第一个非空白字符的位置，如果到达末尾则返回 str.size()
		 */
		static size_t
			skip_whitespace(std::string_view str, size_t pos)
		{
			while (pos < str.size() && std::isspace(static_cast<unsigned char>(str[pos]))) {
				++pos;
			}
			return pos;
		}

		/**
		 * @brief 解析标识符 token，返回标识符的结束位置和对应的 Token 对象
		 *
		 * @param str - 输入字符串视图
		 * @param pos - 起始位置
		 * @return std::pair<size_t, Token> - 标识符的结束位置和对应的 Token 对象
		 */
		static std::pair<size_t, Token>
			parse_identifier(std::string_view str, size_t pos)
		{
			auto is_ident_char = [](char c) {
				auto ch = static_cast<unsigned char>(c);
				return std::isalnum(ch) || ch == '_';
				};

			size_t j = pos + 1;
			while (j < str.size() && is_ident_char(str[j])) {
				++j;
			}

			// 全部转换为大写，实现大小写不敏感
			std::string txt(str.substr(pos, j - pos));
			for (auto& ch : txt) {
				ch = static_cast<char>(
					std::toupper(static_cast<unsigned char>(ch))
					);
			}

			TokenKind kind = (txt == "AND" || txt == "OR" || txt == "NOT")
				? TokenKind::Keyword
				: TokenKind::Identifier;
			return { j, Token{kind, std::move(txt)} };
		}

		/**
		 * @brief 解析数字 token，返回数字的结束位置和对应的 Token 对象
		 *
		 * @param str - 输入字符串视图
		 * @param pos - 起始位置
		 * @return std::pair<size_t, Token> - 数字的结束位置和对应的 Token 对象
		 */
		static std::pair<size_t, Token>
			parse_number(std::string_view str, size_t pos)
		{
			size_t j = pos;
			bool dot = false;
			while (j < str.size() && (std::isdigit(static_cast<unsigned char>(str[j])) || (!dot && str[j] == '.'))) {
				if (str[j] == '.') {
					dot = true;
				}
				++j;
			}
			return { j, Token{TokenKind::Number, std::string(str.substr(pos, j - pos))} };
		}

		/**
		 * @brief 解析操作符 token，返回操作符的结束位置和对应的 Token 对象
		 *
		 * @param str - 输入字符串视图
		 * @param pos - 起始位置
		 * @return std::pair<size_t, Token> - 操作符的结束位置和对应的 Token 对象
		 */
		static std::pair<size_t, Token>
			parse_operator(std::string_view str, size_t pos)
		{
			using enum postanvil::Lexer::TokenKind;

			if (pos + 1 < str.size()) {
				auto two = str.substr(pos, 2);
				if (two == ">=" || two == "<=" || two == "==" || two == "!=") {
					return { pos + 2, Token{Op, std::string(two)} };
				}
			}
			if (pos < str.size()) {
				return { pos + 1, Token{Op, std::string(1, str[pos])} };
			}
			return { pos, Token{Error, "Unexpected end of input"} };
		}
	};

} // namespace postanvil

