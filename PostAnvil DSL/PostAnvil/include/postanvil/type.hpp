/**
 * @file   value.hpp
 * @brief  PostAnvil 类型系统、值类型及表达式闭包定义
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include <functional>
#include <variant>
#include <string>
#include <stdexcept>
#include <compare>
#include <memory>

#include "error.hpp"

namespace postanvil {

class Instance;
struct Scene;

/**
 * @brief DSL 编译期类型掩码枚举，描述表达式值类型
 * @details 采用位掩码设计，单值互斥；T_ANY 万能兼容，T_ERROR 代表类型不匹配
 * @note 前缀 T_ 规避 Windows SDK 全局宏 STR / BOOL / NUM 命名冲突
 */
enum class Type : std::uint32_t
{
	T_ERROR	= 0b0000'0000'0000'0000,	// 类型不匹配、运算非法
	T_ANY	= 0b1111'1111'1111'1111,	// 任意类型万能匹配

	// 基础原子类型，互不兼容

	T_NUM	= 0b0000'0000'0000'0001,
	T_STR	= 0b0000'0000'0000'0010,
	T_BOOL	= 0b0000'0000'0000'0100,
	T_INST	= 0b0000'0000'0000'1000,
};

/**
 * @brief 类型掩码合并运算符 &，实现类型兼容推导规则
 * 
 * @param lhs 左操作数类型
 * @param rhs 右操作数类型
 * @return 合并后最终推导类型 Type
 *
 * 规则定义：
 * 1. 任意一方为 T_ERROR				→ T_ERROR；
 * 2. 两方都是 T_ANY					→ T_ANY；
 * 3. 一方 T_ANY、另一方具体类型		→ 返回具体类型；
 * 4. 两方为同一种具体类型			→ 返回该类型；
 * 5. 两方为互不相同的具体类型			→ T_ERROR；
 */
[[nodiscard]]
constexpr Type operator&(Type lhs, Type rhs) {
	return static_cast<Type>(
		static_cast<std::underlying_type_t<Type>>(lhs) &
		static_cast<std::underlying_type_t<Type>>(rhs)
	);
}

/**
 * @brief 判断两个类型是否兼容可运算
 * @param lhs 类型A
 * @param rhs 类型B
 * @return true：兼容；false：类型冲突/错误
 * @note 兼容判定规则与 operator& 完全统一
 */
[[nodiscard]]
constexpr bool type_compatible(Type lhs, Type rhs)
{
	return (lhs & rhs) != Type::T_ERROR;
}

/**
 * @brief 判断两个类型是否严格相等（忽略ANY万能匹配）
 * @param lhs 类型A
 * @param rhs 类型B
 * @return 完全一致返回true
 */
[[nodiscard]]
constexpr bool type_strict_equal(Type lhs, Type rhs)
{
	return lhs == rhs;
}

/**
 * @brief 获取类型枚举对应的可读名称字符串
 * @param t 目标类型枚举值
 * @return 静态常量C字符串，无需释放
 */
[[nodiscard]]
inline const char* type_name(Type t)
{
	using enum postanvil::Type;
	switch (t)
	{
	case T_NUM:     return "NUM";
	case T_STR:     return "STR";
	case T_BOOL:    return "BOOL";
	case T_INST:    return "INST";
	case T_ANY:     return "ANY";
	case T_ERROR:   return "ERROR";
	default:        return "UNKNOWN_TYPE";
	}
}

/**
 * @brief 判断是否为合法具体值类型（排除 ANY/ERROR）
 * @param t 待检测类型
 * @return true：NUM/STR/BOOL/INST 其中之一
 */
[[nodiscard]]
constexpr bool is_primitive_type(Type t)
{
	return t != Type::T_ANY && t != Type::T_ERROR;
}

/**
 * @brief 规则类型枚举，区分 DSL 中五种规则块
 */
enum class RuleKind {
	FILTER,
	ATTR,
	GROUP,
	APPEND,
	FUNC,
};

template<typename T>
concept ValAllowedType = std::is_same_v<std::decay_t<T>, double>
					  || std::is_same_v<std::decay_t<T>, bool>
					  || std::is_same_v<std::decay_t<T>, std::string>
					  || std::is_same_v<std::decay_t<T>, std::shared_ptr<Instance>>
					  || std::is_same_v<std::decay_t<T>, const char*>;

/**
 * @brief 运行时多态值，可承载数值、字符串或布尔三种类型
 * @details 提供类型查询和安全转换方法，类型不匹配时抛出 RuntimeError
 */
struct Val {

	std::variant<double, std::string, bool, std::shared_ptr<Instance>> data;

	Val() : data(0.0) {}
	Val(const Instance& inst) 
		: data(std::make_shared<Instance>(inst))
	{}

	template<ValAllowedType T>
	Val(T&& arg) noexcept(std::is_nothrow_constructible_v<decltype(data), T>)
		: data(std::forward<T>(arg))
	{}

	std::partial_ordering operator<=>(const Val& other) const {
		if (type() != other.type()) {
			throw RuntimeError("Cannot compare values of different types: " +
				std::string(type_name(type())) + " vs " +
				std::string(type_name(other.type())));
		}

		switch (type()) {
		using enum postanvil::Type;
		case T_NUM: {
			constexpr double eps = 1e-6;
			double a = as_num();
			double b = other.as_num();
			double diff = a - b;
			if (std::abs(diff) < eps)
				return std::partial_ordering::equivalent;
			if (diff < 0)
				return std::partial_ordering::less;
			return std::partial_ordering::greater;
		}
		case T_BOOL: return as_bool() <=> other.as_bool();
		case T_STR:  return as_str() <=> other.as_str();
		case T_INST: throw RuntimeError("INST values cannot be compared directly");
		default:	 throw RuntimeError("Unknown type");
		}
	}

	bool operator==(const Val& other) const {
		return (*this <=> other) == 0;
	}

	friend Val operator+(const Val& lhs, const Val& rhs) {
		if (lhs.type() != rhs.type()) {
			throw RuntimeError("Cannot add values of different types");
		}
		if (lhs.type() == Type::T_BOOL || rhs.type() == Type::T_BOOL) {
			throw RuntimeError("Cannot add values of boolean type");
		}

		return std::visit(
			[](const auto& a, const auto& b) -> Val {
				using A = std::decay_t<decltype(a)>;
				using B = std::decay_t<decltype(b)>;
				if constexpr (std::is_same_v<A, double> && std::is_same_v<B, double>) {
					return a + b;
				}
				else if constexpr (std::is_same_v<A, std::string> && std::is_same_v<B, std::string>) {
					return a + b;
				}
				else {
					throw RuntimeError("Unsupported addition types");
				}
			},
			lhs.data, rhs.data
		);
	}

	friend Val operator-(const Val& lhs, const Val& rhs) {
		if (lhs.type() != rhs.type() || lhs.type() != Type::T_NUM) {
			throw RuntimeError("Subtraction requires NUM operands of the same type");
		}
		return lhs.as_num() - rhs.as_num();
	}

	friend Val operator*(const Val& lhs, const Val& rhs) {
		if (lhs.type() != rhs.type() || lhs.type() != Type::T_NUM) {
			throw RuntimeError("Multiplication requires NUM operands of the same type");
		}
		return lhs.as_num() * rhs.as_num();
	}

	friend Val operator/(const Val& lhs, const Val& rhs) {
		if (lhs.type() != rhs.type() || lhs.type() != Type::T_NUM) {
			throw RuntimeError("Division requires NUM operands of the same type");
		}
		double b = rhs.as_num();
		return b != 0.0 ? lhs.as_num() / b : 0.0;
	}

	/**
	 * @brief 获取当前值的数据类型
	 * @return Type 枚举值
	 */
	Type type() const {
		using enum postanvil::Type;
		if (std::holds_alternative<double>(data))		return T_NUM;
		if (std::holds_alternative<std::string>(data))	return T_STR;
		if (std::holds_alternative<bool>(data))			return T_BOOL;
		if (std::holds_alternative<std::shared_ptr<Instance>>(data)) return T_INST;
		return T_ERROR;
	}

	/**
	 * @brief 转换为数值类型
	 * @return double 值
	 * @throws RuntimeError 当前值非数值类型时抛出
	 */
	double as_num() const {
		if (auto* p = std::get_if<double>(&data)) return *p;
		throw RuntimeError("Expected NUM, got " + std::string(type_name(type())));
	}

	/**
	 * @brief 转换为字符串类型
	 * @return std::string 副本
	 * @throws RuntimeError 当前值非字符串类型时抛出
	 */
	std::string as_str() const {
		if (auto* p = std::get_if<std::string>(&data)) return *p;
		throw RuntimeError("Expected STR, got " + std::string(type_name(type())));
	}

	/**
	 * @brief 转换为布尔类型
	 * @return bool 值
	 * @details 若当前为数值，按非零为真进行转换；若当前为字符串则抛出异常
	 * @throws RuntimeError 当前值非数值且非布尔类型时抛出
	 */
	bool as_bool() const {
		if (auto* p = std::get_if<bool>(&data)) return *p;
		if (auto* pn = std::get_if<double>(&data)) return *pn != 0.0;
		throw RuntimeError("Expected BOOL, got " + std::string(type_name(type())));
	}

	/**
	 * @brief 获取实例快照
	 * @return 指向不可变实例快照的共享指针
	 * @throws RuntimeError 当前值不是 INST 或实例为空时抛出
	 */
	std::shared_ptr<const Instance> as_inst() const {
		if (auto* p = std::get_if<std::shared_ptr<Instance>>(&data); p && *p) return *p;
		throw RuntimeError("Expected INST, got " + std::string(type_name(type())));
	}
};


struct EvaluationContext;	// 评估环境前向声明

/**
 * @brief 带类型的表达式闭包函数类型
 * @param instance 当前求值的实例
 * @param scene 当前场景上下文
 * @return 表达式求值结果
 */
using ValFunc = std::function<Val(const Instance&, EvaluationContext&)>;

/**
 * @brief 类型化表达式，包含求值函数及其返回类型
 */
struct TypedExpr {
	ValFunc func;
	Type type;
};

using NumFunc		= std::function<double		(const Instance&, EvaluationContext& scene)>;
using BoolFunc		= std::function<bool		(const Instance&, EvaluationContext& scene)>;
using StrFunc		= std::function<std::string	(const Instance&, EvaluationContext& scene)>;

using StatementFunc	= std::function<void		(EvaluationContext&)>;



} // namespace postanvil
