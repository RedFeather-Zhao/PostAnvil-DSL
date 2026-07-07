/**
 * @file   common.hpp
 * @brief  PostAnvil 公共类型、枚举与辅助函数
 * @detail 本文件包含编译器使用的公共类型定义
 *         RuleKind：规则类型枚举
 *         NumFunc / FilterFunc：编译后的函数类型别名
 *         以及各种辅助函数
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/context.hpp"
#include <functional>
#include <string>
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <cctype>

namespace postanvil {


// ========================== RuleKind ============================

/**
 * @brief 规则类型枚举
 */
enum class RuleKind {
	FILTER,		//< 过滤规则：按条件筛选实例
	ATTR,		//< 属性规则：为实例添加计算属性
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

// ========================== Helper Functions ============================

/**
 * @brief 将字符串转为大写（原地）
 */
inline void to_upper_inplace(std::string& s) {
	for (auto& ch : s) {
		ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
	}
}

/**
 * @brief 获取实例的属性值，包括内置属性和动态属性
 *
 * 内置属性：
 * - X1, Y1：左上角坐标
 * - X2, Y2：右下角坐标（计算值）
 * - W, H：宽度和高度
 * - CX, CY：中心点坐标（计算值）
 * - AREA：面积（计算值）
 * - ASPECT：宽高比（计算值）
 * - CONF：置信度
 *
 * 若内置属性未匹配，则查找动态属性（props 映射）。
 *
 * @param inst - 实例
 * @param prop - 属性名
 */
inline double get_instance_prop(const Instance& inst, const Scene& scene, std::string_view prop) {
	// 内置属性
	if (prop == "CONF")   return inst.conf();

	// 几何属性（像素坐标）
	if (prop == "W")      return inst.w();
	if (prop == "H")      return inst.h();
	if (prop == "X1")     return inst.x1();
	if (prop == "Y1")     return inst.y1();
	if (prop == "X2")     return inst.x2();
	if (prop == "Y2")     return inst.y2();
	if (prop == "CX")     return inst.cx();
	if (prop == "CY")     return inst.cy();
	if (prop == "AREA")   return inst.area();
	if (prop == "ASPECT") return inst.aspect();
	
	// 归一化属性 (0.0 ~ 1.0)
	if (prop == "WN")      return inst.wn(scene.image.width);
	if (prop == "HN")      return inst.hn(scene.image.height);
	if (prop == "X1N")     return inst.x1n(scene.image.width);
	if (prop == "X2N")     return inst.x2n(scene.image.width);
	if (prop == "Y1N")     return inst.y1n(scene.image.height);
	if (prop == "Y2N")     return inst.y2n(scene.image.height);
	if (prop == "CXN")     return inst.cxn(scene.image.width);
	if (prop == "CYN")     return inst.cyn(scene.image.height);
	if (prop == "AREAN")   return inst.arean(scene.image.width, scene.image.height);

	// 动态属性
	return inst.get_prop(std::string(prop));
}

/**
 * @brief 获取图像属性
 *
 * @param img  - 图像信息
 * @param prop - 属性名，当前仅支持 "W"（宽度）和 "H"（高度）
 * @return double - 属性值；若属性不存在则抛出 CompileError
 */
inline double get_image_prop(const Image& img, std::string_view prop) {
	if (prop == "W") return img.width;
	if (prop == "H") return img.height;
	throw RuntimeError("Unknown property '" + std::string(prop) + "' for image");
}

} // namespace postanvil