/**
 * @file   builtins.hpp
 * @brief  PostAnvil 原生内置函数注册表及实现
 *		   1. 内置函数采用标准函数调用语法，并通过 FunctionInfo 完成签名校验
 *		   2. 运行时求值会直接调用原生 C++ 闭包
 * 
 * @author RedFeather-Zhao
 * @date   August 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <format>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "operators.hpp"
#include "utils.hpp"


namespace postanvil::builtin_detail {

/**
 * @brief 构建原生函数
 *
 * @param ret_type		- 返回类型
 * @param param_types	- 参数类型列表
 * @param function		- 函数闭包
 * @return FunctionInfo	- 编译后的函数闭包
 */
inline FunctionInfo make_builtin		(Type ret_type,
										 std::vector<Type> param_types,
										 CompiledFunc function)
{
	return FunctionInfo{
		.func = std::move(function),
		.ret_type = ret_type,
		.param_types = std::move(param_types),
		.is_builtin = true,
	};
}

/**
 * @brief 检查浮点数是否为有限值
 *
 * @param name			- 函数名称，用于错误信息
 * @param value			- 待检查的浮点数值
 * @return double		- 返回原始值（如果有限）
 * @throw PARuntimeError	- 当 value 为非有限值（无穷大或 NaN）时抛出
 */
inline double checked_finite(std::string_view name, double value)
{
	if (!std::isfinite(value)) {
		throw PARuntimeError(std::format("{} produced a non-finite result", name));
	}
	return value;
}

/**
 * @brief 计算两个实例的交集面积
 *
 * @param a			- 第一个实例
 * @param b			- 第二个实例
 * @return double	- 交集面积
 */
inline double inter_area(const Instance& a, const Instance& b)
{
	const double left = std::max(a.x1(), b.x1());
	const double top = std::max(a.y1(), b.y1());
	const double right = std::min(a.x2(), b.x2());
	const double bottom = std::min(a.y2(), b.y2());
	return std::max(0.0, right - left) * std::max(0.0, bottom - top);
}

/**
 * @brief 安全计算比率，处理分母为零的情况
 *
 * @param numerator		- 分子
 * @param denominator	- 分母
 * @return double		- 当分母大于0时返回 numerator/denominator，否则返回0
 */
inline double safe_ratio(double numerator, double denominator)
{
	return denominator > 0.0 ? numerator / denominator : 0.0;
}

/**
 * @brief 从参数列表中提取实例引用
 *
 * @param args				- 参数值列表
 * @param index				- 参数索引
 * @return const Instance&	- 对应索引的实例引用
 * @throw PARuntimeError	- 当参数不是实例类型或实例为空时抛出
 */
inline const Instance& instance_arg(const std::vector<Val>& args,
	size_t index,
	EvaluationContext& ctx)
{
	return ctx.scene.inst(args[index].as_inst().id);
}

} // namespace postanvil::builtin_detail


namespace postanvil {

/**
 * @brief 注册所有内置函数
 * 
 * @param functions - 函数注册表，将函数名映射到 FunctionInfo
 * @note  内置函数声明不能被用户函数声明覆盖
 */
inline void register_builtin_functions(detail::str_map<FunctionInfo>& functions)
{
	using namespace builtin_detail;

	auto add = [&functions](std::string name, FunctionInfo info) {
		functions.try_emplace(std::move(name), std::move(info));
	};

	//=========================== 数学计算 ===========================//

	const auto unary_math = [&add](std::string name, auto operation) {
		auto display_name = name;
		add(std::move(name), make_builtin(Type::T_NUM, { Type::T_NUM },
			[display_name = std::move(display_name), operation]
			(const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
				return checked_finite(display_name, operation(args[0].as_num()));
			})
		);
	};

	//< 1.绝对值
	unary_math("_ABS",   [](double value) { return std::abs(value); });

	//< 2.自然指数
	unary_math("_EXP",   [](double value) { return std::exp(value); });

	//< 3.向下取整
	unary_math("_FLOOR", [](double value) { return std::floor(value); });

	//< 4.向上取整
	unary_math("_CEIL",  [](double value) { return std::ceil(value); });

	//< 5.四舍五入
	unary_math("_ROUND", [](double value) { return std::round(value); });

	//< 6.开平方根
	add("_SQRT", make_builtin(Type::T_NUM, { Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			const double value = args[0].as_num();
			if (value < 0.0) {
				throw PARuntimeError("_SQRT requires a non-negative argument");
			}
			return checked_finite("_SQRT", std::sqrt(value));
		})
	);

	//< 7.自然对数
	add("_LOG", make_builtin(Type::T_NUM, { Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			const double value = args[0].as_num();
			if (value <= 0.0) {
				throw PARuntimeError("_LOG requires a positive argument");
			}
			return checked_finite("_LOG", std::log(value));
		})
	);

	//< 8.以10为底对数
	add("_LOG10", make_builtin(Type::T_NUM, { Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			const double value = args[0].as_num();
			if (value <= 0.0) {
				throw PARuntimeError("_LOG10 requires a positive argument");
			}
			return checked_finite("_LOG10", std::log10(value));
		})
	);

	//< 9最小值
	add("_MIN", make_builtin(Type::T_NUM, { Type::T_NUM, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			return checked_finite("_MIN", std::min(args[0].as_num(), args[1].as_num()));
		})
	);

	//< 10.最大值
	add("_MAX", make_builtin(Type::T_NUM, { Type::T_NUM, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			return checked_finite("_MAX", std::max(args[0].as_num(), args[1].as_num()));
		})
	);

	//< 11.幂运算
	add("_POW", make_builtin(Type::T_NUM, { Type::T_NUM, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			return checked_finite("_POW", std::pow(args[0].as_num(), args[1].as_num()));
		})
	);

	//< 12.限制范围
	add("_CLAMP", make_builtin(Type::T_NUM, { Type::T_NUM, Type::T_NUM, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext&) -> Val {
			const double value = args[0].as_num();
			const double low = args[1].as_num();
			const double high = args[2].as_num();
			if (low > high) {
				throw PARuntimeError("_CLAMP requires low <= high");
			}
			return checked_finite("_CLAMP", std::clamp(value, low, high));
		})
	);

	//< 13. 实例交集
	add("_INTER_AREA", make_builtin(Type::T_NUM, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			return inter_area(instance_arg(args, 0, ctx), instance_arg(args, 1, ctx));
		})
	);

	//< 14.实例交并比，Intersection over Union
	add("_IOU", make_builtin(Type::T_NUM, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& a = instance_arg(args, 0, ctx);
			const auto& b = instance_arg(args, 1, ctx);
			const double intersection = inter_area(a, b);
			return safe_ratio(intersection, a.area() + b.area() - intersection);
		})
	);

	//< 15.实例重叠率，Intersection over First
	add("_IOF", make_builtin(Type::T_NUM, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& a = instance_arg(args, 0, ctx);
			const auto& b = instance_arg(args, 1, ctx);
			return safe_ratio(inter_area(a, b), a.area());
		})
	);

	//< 16.实例重叠率，Intersection over Second
	add("_IOS", make_builtin(Type::T_NUM, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& a = instance_arg(args, 0, ctx);
			const auto& b = instance_arg(args, 1, ctx);
			return safe_ratio(inter_area(a, b), b.area());
		})
	);

	//< 17.实例中心点距离
	add("_DISTANCE", make_builtin(Type::T_NUM, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& a = instance_arg(args, 0, ctx);
			const auto& b = instance_arg(args, 1, ctx);
			return std::hypot(a.cx() - b.cx(), a.cy() - b.cy());
		})
	);

	//=========================== 位置谓词 ===========================//

	//< 18.实例是否重叠
	add("_OVERLAPS", make_builtin(Type::T_BOOL, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			return inter_area(instance_arg(args, 0, ctx), instance_arg(args, 1, ctx)) > 0.0;
		})
	);

	//< 19.实例是否包含
	add("_CONTAINS", make_builtin(Type::T_BOOL, { Type::T_INST, Type::T_INST },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& inner = instance_arg(args, 0, ctx);
			const auto& outer = instance_arg(args, 1, ctx);
			return inner.x1() >= outer.x1() && inner.y1() >= outer.y1() &&
				inner.x2() <= outer.x2() && inner.y2() <= outer.y2();
		})
	);

	//< 20.实例是否接近
	add("_NEARBY", make_builtin(Type::T_BOOL, { Type::T_INST, Type::T_INST, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			const auto& a = instance_arg(args, 0, ctx);
			const auto& b = instance_arg(args, 1, ctx);
			const double threshold = args[2].as_num();
			if (threshold < 0.0) {
				throw PARuntimeError("_NEARBY requires a non-negative threshold");
			}
			const double dx = a.cx() - b.cx();
			const double dy = a.cy() - b.cy();
			return dx * dx + dy * dy <= threshold * threshold;
		})
	);

	//=========================== 实例访问 ===========================//

	//< 21.通过实例 ID 获取实例
	add("_INST_ID", make_builtin(Type::T_INST, { Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			return ctx.scene.get_inst_by_id(args[0].as_num());
		})
	);

	//< 22.通过实例类别和索引获取实例
	add("_INST_INDEX", make_builtin(Type::T_INST, { Type::T_STR, Type::T_NUM },
		[](const std::vector<Val>& args, const Instance&, EvaluationContext& ctx) -> Val {
			std::string cls_name = args[0].as_str();
			utils::to_upper_inplace(cls_name);
			return ctx.scene.get_inst_by_index(cls_name, args[1].as_num());
		})
	);
}

} // namespace postanvil
