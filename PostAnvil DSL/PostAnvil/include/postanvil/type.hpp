/**
 * @file   type.hpp
 * @brief  
 * 
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <functional>
#include "scene.hpp"

namespace postanvil {


// ========================== RuleKind ============================

/**
 * @brief 规则类型枚举
 */
enum class RuleKind {
	FILTER,		//< 过滤规则：按条件筛选实例
	ATTR,		//< 属性规则：为实例添加计算属性
	GROUP,		//< 分组规则：从源类别创建新类别
	APPEND,		//< 追加规则：向目标类别追加实例
	FUNC,		//< 函数规则：自定义函数
};

// ========================== Func Type ============================

/**
 * @brief 编译后的数值表达式函数
 */
using NumFunc = std::function<double(const Instance&, const Scene& scene)>;

/**
 * @brief 编译后的布尔过滤函数
 */
using FilterFunc = std::function<bool(const Instance&, const Scene& scene)>;


} // namespace postanvil
