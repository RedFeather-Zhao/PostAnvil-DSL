/**
 * @file   utils.hpp
 * @brief  提供字符串处理的通用工具函数
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <string>

namespace postanvil::utils {

/**
 * @brief 将字符串原地转换为大写
 * @param s 待转换的字符串
 */
inline void to_upper_inplace(std::string& s) {
	for (auto& ch : s) {
		ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
	}
}

/**
 * @brief 去除字符串首尾的双引号
 * @param s 输入字符串
 * @return 去除引号后的字符串副本，若首尾不是双引号则返回原字符串
 */
inline std::string strip_quotes(const std::string& s) {
	if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
		return s.substr(1, s.size() - 2);
	}
	return s;
}

} // namespace postanvil::utils