/**
 * @file   common.hpp
 * @brief  PostAnvil 公共类型、枚举与辅助函数
 * @detail 本文件包含编译器使用的公共类型定义：
 *         CompileError：编译异常类
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
#include <format>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <cctype>

namespace postanvil {

// ========================== CompileError ============================

/**
 * @brief 编译异常类，携带行号和列号信息
 */
class CompileError : public std::runtime_error {
public:
	int line; //< 出错行号（-1 表示未知）
	int col;  //< 出错列号（-1 表示未知）

	/**
	 * @brief 构造解析异常
	 * @param m 错误消息
	 * @param l 行号，默认为 -1
	 * @param c 列号，默认为 -1
	 */
	explicit CompileError(const std::string& m, int l = -1, int c = -1)
		: std::runtime_error(std::format("parse error: {}, line: {}, col: {}", m, l, c))
		, line(l), col(c)
	{
	}
};

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
using NumFunc = std::function<double(const Instance&, const Scene&, const Image&)>;

/**
 * @brief 编译后的布尔过滤函数
 */
using FilterFunc = std::function<bool(const Instance&, const Scene&, const Image&)>;

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
 * @param prop - 属性名（大写）
 * @return double - 属性值；若属性不存在则抛出 CompileError
 */
inline double get_instance_prop(const Instance& inst, std::string_view prop) {
	// 内置属性
	if (prop == "X1")     return inst.x1;
	if (prop == "Y1")     return inst.y1;
	if (prop == "W")      return inst.w;
	if (prop == "H")      return inst.h;
	if (prop == "X2")     return inst.x2();
	if (prop == "Y2")     return inst.y2();
	if (prop == "CX")     return inst.cx();
	if (prop == "CY")     return inst.cy();
	if (prop == "AREA")   return inst.area();
	if (prop == "ASPECT") return inst.aspect();
	if (prop == "CONF")   return inst.conf;

	// 动态属性（由 RULE ATTR 计算添加）
	if (auto it = inst.props.find(prop); it != inst.props.end()) {
		return it->second;
	}
	throw CompileError("Unknown property '" + std::string(prop) + "' for instance of class '" + inst.cls + "'");
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
	throw CompileError("Unknown property '" + std::string(prop) + "' for image");
}

/**
 * @brief 计算两个实例的 IoU（交并比）
 *
 * @param a - 实例 A
 * @param b - 实例 B
 * @return double - IoU 值 [0.0, 1.0]
 */
inline double compute_iou(const Instance& a, const Instance& b) {
	double ix1 = std::max(a.x1, b.x1);
	double iy1 = std::max(a.y1, b.y1);
	double ix2 = std::min(a.x2(), b.x2());
	double iy2 = std::min(a.y2(), b.y2());
	double iw = ix2 - ix1;
	double ih = iy2 - iy1;
	if (iw <= 0.0 || ih <= 0.0) {
		return 0.0;
	}
	double inter = iw * ih;
	double uni = a.area() + b.area() - inter;
	return uni > 0.0 ? inter / uni : 0.0;
}

} // namespace postanvil