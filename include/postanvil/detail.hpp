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
#include <format>

namespace postanvil::detail {

//========================= StrMap ==========================

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
template<typename V>
using str_map = std::unordered_map<std::string, V, TransparentStrHash, std::equal_to<>>;

//========================= Scope ==========================

/**
 * @brief 链式符号表，定义层级作用域，编译期实现全局/局部变量的定义
 * @detals 可视为一个可访问底部的栈结构，每层存储符号到特定值的映射关系
 */
template<typename T>
class ScopeChain {
	using Scope = str_map<T>;
	std::vector<Scope> scopes;

public:
	ScopeChain() {
		push(); // global
	}

	/**
	 * @brief 提升作用域
	 */
	void push() {
		scopes.emplace_back();
	}

	/**
	 * @brief 降低作用域
	 */
	void pop() {
		if (scopes.size() > 1) {
			scopes.pop_back();
		}
	}

	/**
	 * @brief 在当前作用域设置符号
	 * 
	 * @param name	- 符号名
	 * @param val	- 值
	 */
	void set_local(const std::string& name, T val) {
		if (scopes.size() == 1) {
			push(); // first
		}
		scopes.back()[name] = val;
	}

	/**
	 * @brief 在全局作用域设置符号
	 * 
	 * @param name	- 符号名
	 * @param val	- 值
	 */
	void set_global(const std::string& name, T val) {
		scopes.front()[name] = val;
	}

	/**
	 * @brief 自顶向下查找符号并取值
	 * 
	 * @param name	- 符号名
	 * @param out	- 输出值
	 * @return bool	- 是否查找到符号
	 */
	bool lookup(const std::string& name, T& out) const {
		for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
			auto found = it->find(name);
			if (found != it->end()) {
				out = found->second;
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief 自顶向下查找符号并取值
	 *
	 * @param name	- 符号名
	 * @return T	- 输出值
	 */
	T lookup(const std::string& name) const {
		for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
			auto found = it->find(name);
			if (found != it->end()) {
				return found->second;
			}
		}
		throw std::runtime_error(std::format("Unknowd symbol: {}", name));
	}

	/**
	 * @brief 自顶向下查找符号
	 *
	 * @param name	- 符号名
	 * @return bool	- 是否查找到符号
	 */
	bool checkup(const std::string& name) const {
		for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
			auto found = it->find(name);
			if (found != it->end()) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief 清空符号表
	 */
	void clear() {
		scopes.clear();
		push();
	}
};

} // namespace postanvil::detail

