/**
 * @file   detail.hpp
 * @brief  提供透明哈希支持及字符串键映射类型，供 DSL 执行器高效管理类别/属性名
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

namespace postanvil::detail {

/**
 * @brief 支持透明查找的字符串哈希函数，允许以 std::string_view 等类型直接查找，
 *        避免构造临时 std::string 对象，提升性能
 */
struct TransparentStrHash
{
	using is_transparent = void;   ///< 启用透明查找

	template<typename TStr>
	size_t operator()(const TStr& s) const noexcept
	{
		// 将所有字符串类型统一转为 string_view 计算哈希
		return std::hash<std::string_view>{}(s);
	}
};

/**
 * @brief 使用透明哈希的字符串键 unordered_map 别名
 *        适合需要以字符串（或 string_view）为键的快速查找场景
 */
template<typename K, typename V>
using str_map = std::unordered_map<K, V, TransparentStrHash, std::equal_to<>>;

} // namespace postanvil::detail

