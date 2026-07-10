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

#include "error.hpp"

namespace postanvil {

class Instance;
struct Scene;

/**
 * @brief 编译期类型枚举，表示 DSL 支持的数据类型
 * @note T_ 前缀用于避免与 Windows SDK 宏 STR、BOOL 冲突
 */
enum class Type: uint32_t {
	T_ERROR		= 0b0000'0000'0000'0000,
	T_ANY		= 0b1111'1111'1111'1111,

	// 注意，以下类型并不兼容

	T_NUM		= 0b0000'0000'0000'0001,
	T_STR		= 0b0000'0000'0000'0010,
	T_BOOL		= 0b0000'0000'0000'0100,
};

// 按位与
/**
 * @brief 类型按位与运算，用于解决类型判断问题的复杂逻辑
 * 如
 * 1.仅支持 NUM 和 ANY 的场景，两操作数类型未知
 * type = op1 & op2
 * 若均为 ANY，则 type = ANY
 * 若均为 NUM，则 type = NUM
 * 若其中一个为ANY，则 type = 另一个操作数类型
 * 若不同类型且均不为 ANY，type = T_ERROR
 * 
 * 2.T_ERROR 对任意类型运算均报错
 * 
 * @return 指定类型 | T_ANY | T_ERROR
 */
constexpr Type operator&(Type lhs, Type rhs) {
	return static_cast<Type>(
		static_cast<std::underlying_type_t<Type>>(lhs) &
		static_cast<std::underlying_type_t<Type>>(rhs)
	);
}

/**
 * @brief 获取类型枚举对应的名称字符串
 * @param t 类型枚举值
 * @return 类型名称的 C 字符串
 */
inline const char* type_name(Type t) {
	switch (t) {
		using enum postanvil::Type;
	case T_NUM:		return "NUM";
	case T_STR:		return "STR";
	case T_BOOL:	return "BOOL";
	case T_ANY:		return "ANY";
	case T_ERROR:	return "ERROR";
	default:		return "UNKNOW";
	}
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

/**
 * @brief 运行时多态值，可承载数值、字符串或布尔三种类型
 * @details 提供类型查询和安全转换方法，类型不匹配时抛出 RuntimeError
 */
struct Val {
	std::variant<double, std::string, bool> data;

	Val() : data(0.0) {}
	Val(double v) : data(v) {}
	Val(const std::string& v) : data(v) {}
	Val(const char* v) : data(std::string(v)) {}
	Val(bool v) : data(v) {}

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
		default:	 throw RuntimeError("");
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
		if (std::holds_alternative<double>(data))      return Type::T_NUM;
		if (std::holds_alternative<std::string>(data)) return Type::T_STR;
		return Type::T_BOOL;
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
};

/**
 * @brief 带类型的表达式闭包函数类型
 * @param instance 当前求值的实例
 * @param scene 当前场景上下文
 * @return 表达式求值结果
 */
using ValFunc = std::function<Val(const Instance&, const Scene&)>;

/**
 * @brief 类型化表达式，包含求值函数及其返回类型
 */
struct TypedExpr {
	ValFunc func;
	Type type;
};

using NumFunc		= std::function<double		(const Instance&, const Scene& scene)>;
using BoolFunc		= std::function<bool		(const Instance&, const Scene& scene)>;
using StrFunc		= std::function<std::string	(const Instance&, const Scene& scene)>;

} // namespace postanvil