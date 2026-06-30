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
 * @brief 词法单元类型
 */
enum class TokenKind {
	End,		//< 表示输入结束
	Identifier,	//< 标识符
	Number,		//< 数字常量
	Op,			//< 操作符和标点
	Keyword,	//< 关键字（AND/OR/NOT 等）
};

/**
 * @brief 词法单元结构
 */
struct Token {
	TokenKind kind;		//< 单元类型1
	std::string text;	//< 原始文本
};

/**
 * @brief 判断字符是否可用于标识符的后续位置（字母/数字/下划线）。
 */
inline bool is_ident_char(unsigned char c) {
	return std::isalnum(c) || c == '_';
}

/**
 * @brief 将表达式字符串拆分为 Token 序列，最后追加一个 End token
 * @param s 输入表达式字符串（单行）
 * @return Token 向量，末尾包含一个 End token
 */
inline std::vector<Token> tokenize_expr(const std::string& s) {
	std::vector<Token> out;
	size_t i = 0;
	while (i < s.size()) {
		auto c = static_cast<unsigned char>(s[i]);

		// 跳过空白字符
		if (std::isspace(c)) {
			++i;
			continue;
		}

		// 标识符 & 关键字
		if (std::isalpha(c) || c == '_') {
			size_t j = i + 1;
			while (j < s.size() && is_ident_char(static_cast<unsigned char>(s[j]))) {
				++j;
			}
			// 关键字识别（大小写不敏感）
			std::string txt = s.substr(i, j - i);
			std::string up = txt;
			for (auto& ch : up) {
				ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
			}

			if (up == "AND" || up == "OR" || up == "NOT") {
				out.emplace_back(TokenKind::Keyword, up);
			} else {
				out.emplace_back(TokenKind::Identifier, txt);
			}
			i = j;
			continue;
		}

		// 数字字面量（整数或浮点数）
		if (std::isdigit(c) || (c == '.' && i + 1 < s.size() && std::isdigit(static_cast<unsigned char>(s[i + 1])))) {
			size_t j = i;
			bool dot = false;
			while (j < s.size() && (std::isdigit(static_cast<unsigned char>(s[j])) || (!dot && s[j] == '.'))) {
				if (s[j] == '.') {
					dot = true;
				}
				++j;
			}
			out.emplace_back(TokenKind::Number, s.substr(i, j - i));
			i = j;
			continue;
		}

		// 操作符与标点
		if (i + 1 < s.size()) {
			std::string two = s.substr(i, 2);
			if (two == ">=" || two == "<=" || two == "==" || two == "!=") {
				out.emplace_back(TokenKind::Op, two);
				i += 2;
				continue;
			}
		}
		std::string one(1, c);
		out.emplace_back(TokenKind::Op, one);
		++i;
	}
	out.emplace_back(TokenKind::End, "");
	return out;
}

} // namespace postanvil
