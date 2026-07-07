/**
 * @file   detail.hpp
 * @brief  
 * 
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
	* @brief 支持透明哈希的字符串哈希函数
	*/
	struct TransparentStrHash
	{
		using is_transparent = void;

		template<typename TStr>
		size_t operator()(const TStr& s) const noexcept
		{
			return std::hash<std::string_view>{}(s);
		}
	};

	template<typename K, typename V>
	using str_map = std::unordered_map<K, V, TransparentStrHash, std::equal_to<>>;

} // namespace postanvil::detail
