/**
 * @file   expr_compiler.hpp
 * @brief  PostAnvil 表达式编译器，递归遍历 ANTLR4 ParseTree 生成 TypedExpr 闭包
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include "PostAnvilParser.h"
#include <functional>
#include <string>
#include <cmath>
#include <unordered_map>
#include <algorithm>

#include "utils.hpp"
#include "type.hpp"
#include "scene.hpp"
#include "compiler_error.hpp"

namespace postanvil {

// ====================== TreeExprCompiler =========================

/**
 * @brief 表达式编译器
 * @details 接收 ANTLR4 表达式 ParseTree 节点，递归编译为 TypedExpr 闭包
 *          编译期完成类型推导和检查，运行时通过 Val 传递值
 *          支持的表达式层级：expr → or/and/not/cmp/add/mul/unary → primary
 */
class TreeExprCompiler {
public:
	static inline constexpr std::string_view OBJECT_SELF = "SELF";
	static inline constexpr std::string_view OBJECT_IMAGE = "IMG";

	TreeExprCompiler() = default;

	void set_functions(detail::str_map<FunctionInfo>* function_table) noexcept {
		m_functions = function_table;
	}

	void set_type_scope(detail::ScopeChain<Type>* type_scope) noexcept {
		m_type_scope = type_scope;
	}

public: // public method:

	/**
	 * @brief 编译表达式为闭包的入口方法
	 *
	 * @param ctx			- ANTLR4 ExprContext 节点
	 * @return TypedExpr	- 带类型的表达式闭包
	 * @throw PACompileError	- 编译错误，包含编译信息
	 */
	TypedExpr compile(::PostAnvilParser::ExprContext* ctx) {
		if (!ctx || !ctx->or_expr()) {
			report_internal_error("Empty ExprContext node type", ctx);
		}
		return compileOr(ctx->or_expr());
	}

	/**
	 * @brief 编译布尔表达式闭包
	 *
	 * @param ctx			- ANTLR4 Or_exprContext 节点
	 * @return BoolFunc		- 布尔类型的表达式闭包
	 */
	BoolFunc compileAsBool(::PostAnvilParser::Or_exprContext* ctx) {
		auto typed = compileOr(ctx);
		if (!type_compatible(typed.type, Type::T_BOOL)) {
			auto err = std::format(
				"Bool-expr must be BOOL or ANY(runtime bool), got {}",
				type_name(typed.type));
			report_semantic_error(err, ctx);
		}
		const auto& func = typed.func;
		return [func](EvaluationContext& ctx) {
			return func(ctx).as_bool();
		};
	}

	/**
	 * @brief 编译数值表达式闭包
	 *
	 * @param ctx			- ANTLR4 ExprContext 节点
	 * @return NumFunc		- 数值类型的表达式闭包
	 */
	NumFunc compileAsNum(::PostAnvilParser::ExprContext* ctx) {
		auto typed = compile(ctx);
		if (!type_compatible(typed.type, Type::T_NUM)) {
			auto err = std::format(
				"Num-expr must be NUM or ANY(runtime NUM), got {}",
				type_name(typed.type));
			report_semantic_error(err, ctx);
		}
		const auto& func = typed.func;
		return [func](EvaluationContext& ctx) {
			return func(ctx).as_num();
		};
	}

	/**
	 * @brief 编译字符串表达式闭包
	 *
	 * @param ctx            - ExprContext 节点
	 * @return StrFunc       - 字符串类型表达式闭包
	 */
	StrFunc compileAsStr(::PostAnvilParser::ExprContext* ctx) {
		auto typed = compile(ctx);
		if (!type_compatible(typed.type, Type::T_STR)) {
			auto err = std::format(
				"Str-expr must be STR or ANY(runtime STR), got {}",
				type_name(typed.type));
			report_semantic_error(err, ctx);
		}
		const auto& func = typed.func;
		return [func](EvaluationContext& ctx) {
			return func(ctx).as_str();
		};
	}


	/**
	 * @brief 编译类别字串表达式闭包
	 *
	 * @param ctx			- ANTLR4 ClassExprContext 节点
	 * @return StrFunc		- 类别名闭包，支持两种形式
	 *						  1.字符串字面量："person"
	 *						  2.字符串变量: cls_name : STR
	 */
	StrFunc compileClassExpr(::PostAnvilParser::Class_exprContext* ctx) {
		// 字符串字面量
		if (ctx->STRING()) {
			std::string s = utils::strip_quotes(utils::get_upper_text(ctx->STRING()));
			return [s = std::move(s)](EvaluationContext&) {
				return s;
			};
		}

		// 字符串变量
		if (ctx->IDENTIFIER()) {
			std::string var = utils::get_upper_text(ctx->IDENTIFIER());
			Type var_type = Type::T_ANY;
			if (!m_type_scope || !m_type_scope->lookup(var, var_type)) {
				report_semantic_error(std::format("Undefined class variable: {}", var), ctx);
			}
			if (!type_compatible(var_type, Type::T_STR)) {
				report_semantic_error(std::format(
					"Class expression requires STR, got {}", type_name(var_type)), ctx);
			}

			return [var = std::move(var)](EvaluationContext& ctx) {
				Val val = ctx.get_var(var);
				auto str = val.as_str();
				utils::to_upper_inplace(str);
				return str;
			};
		}
		report_internal_error("Invalid class_expr: expected STRING or IDENTIFIER", ctx);
	}

private:
	// ======================== 递归编译方法 ============================

	/**
	 * @brief 编译逻辑或表达式
	 *
	 * @param ctx			- Or_exprContext 节点
	 * @return TypedExpr	- 若存在 OR 运算符，返回布尔类型的表达式闭包
	 *						  若不存在，则透传任意类型的表达式闭包
	 */
	TypedExpr compileOr(::PostAnvilParser::Or_exprContext* ctx) {
		auto and_exprs = ctx->and_expr();
		auto left = compileAnd(and_exprs[0]);

		// 不存在 OR 运算，透传
		size_t or_count = ctx->OR().size();
		if (or_count == 0) {
			return left;
		}

		// 左式类别检查
		if (!type_compatible(left.type, Type::T_BOOL)) {
			auto err = std::format(
				"Left OR-expr must be BOOL or ANY(runtime bool), got {}",
				type_name(left.type));
			report_semantic_error(err, ctx);
		}

		// 递归右式类别检查
		for (size_t i = 0; i < or_count; i++) {
			auto right = compileAnd(and_exprs[i + 1]);
			if (!type_compatible(right.type, Type::T_BOOL)) {
				auto err = std::format(
					"Right OR-expr must be BOOL or ANY(runtime bool), got {}",
					type_name(right.type));
				report_semantic_error(err, ctx);
			}
			left = {
				[l = std::move(left.func), r = std::move(right.func)]
				(EvaluationContext& ctx) -> Val {
					return l(ctx).as_bool() || r(ctx).as_bool();
				},
				Type::T_BOOL
			};
		}

		return left;
	}

	/**
	 * @brief 编译逻辑与表达式
	 *
	 * @param ctx			- And_exprContext 节点
	 * @return TypedExpr	- 若存在 AND 运算符，返回布尔类型的表达式闭包
	 * 						  若不存在，则透传任意类型的表达式闭包
	 */
	TypedExpr compileAnd(::PostAnvilParser::And_exprContext* ctx) {
		auto not_exprs = ctx->not_expr();
		auto left = compileNot(not_exprs[0]);

		// 若不存在 AND 运算，透传
		size_t and_count = ctx->AND().size();
		if (and_count == 0) {
			return left;
		}

		// 左式类别检查
		if (!type_compatible(left.type, Type::T_BOOL)) {
			auto err = std::format(
				"Left AND-expr must be BOOL or ANY(runtime bool), got {}",
				type_name(left.type));
			report_semantic_error(err, ctx);
		}

		// 递归右式类别检查
		for (size_t i = 0; i < and_count; i++) {
			auto right = compileNot(not_exprs[i + 1]);
			if (!type_compatible(right.type, Type::T_BOOL)) {
				auto err = std::format(
					"Right AND-expr must be BOOL or ANY(runtime bool), got {}",
					type_name(right.type));
				report_semantic_error(err, ctx);
			}
			left = { [l = std::move(left.func), r = std::move(right.func)]
				(EvaluationContext& ctx) -> Val {
					return l(ctx).as_bool() && r(ctx).as_bool();
				},
				Type::T_BOOL
			};
		}
		return left;
	}

	/**
	 * @brief 编译逻辑非表达式
	 *
	 * @param ctx			- Not_exprContext 节点
	 * @return TypedExpr	- 若存在 NOT 运算符，返回布尔类型的表达式闭包
	 * 						  若不存在，则透传任意类型的表达式闭包
	 */
	TypedExpr compileNot(::PostAnvilParser::Not_exprContext* ctx) {
		// 若不存在 NOT 表达式，透传
		if (!ctx->NOT()) {
			return compileCmp(ctx->cmp_expr());
		}

		// 右式类型检查
		auto rhs = compileNot(ctx->not_expr());
		if (!type_compatible(rhs.type, Type::T_BOOL)) {
			auto err = std::format(
				"NOT-expr must be BOOL or ANY(runtime bool), got {}",
				type_name(rhs.type));
			report_semantic_error(err, ctx);
		}
		return { [r = std::move(rhs.func)]
			(EvaluationContext& ctx) -> Val {
				return !r(ctx).as_bool();
			},
			Type::T_BOOL
		};
	}

	/**
	 * @brief 编译比较表达式
	 *
	 * @param ctx			- Cmp_exprContext 节点
	 * @return TypedExpr	- 若存在比较运算符，返回布尔类型的表达式闭包
	 * 						  若不存在，则透传任意类型的表达式闭包
	 * @details				- NUM、STR 支持全部六种比较符
	 *						  BOOL 仅支持 == 和 !=
	 */
	TypedExpr compileCmp(::PostAnvilParser::Cmp_exprContext* ctx) {
		auto add_exprs = ctx->add_expr();
		auto left = compileAdd(add_exprs[0]);

		// 不存在比较运算符，透传
		if (add_exprs.size() <= 1 || !ctx->comp_op()) {
			return left;
		}

		auto op = getCompOp(ctx->comp_op());
		auto right = compileAdd(add_exprs[1]);

		// 类型判等检查
		Type res_type = left.type & right.type;

		if (type_strict_equal(res_type, Type::T_ERROR)) {
			auto err = std::format(
				"Comparison type mismatch: {} vs {}",
				type_name(left.type),
				type_name(right.type));
			report_semantic_error(err, ctx);
		}

		// 布尔类型仅支持相等/不等判断
		if (type_strict_equal(res_type, Type::T_BOOL) && op != "==" && op != "!=") {
			auto err = std::format("Operator '{}' not supported for BOOL", op);
			report_semantic_error(err, ctx);
		}
		if (type_strict_equal(res_type, Type::T_INST)) {
			report_semantic_error(
				"INST values cannot be compared directly; compare their properties instead",
				ctx);
		}

		return { [l = std::move(left.func), r = std::move(right.func), op = std::move(op)]
			(EvaluationContext& ctx) -> Val {
				auto lval = l(ctx);
				auto rval = r(ctx);
				if (op == ">")  return lval >  rval;
				if (op == "<")  return lval <  rval;
				if (op == ">=") return lval >= rval;
				if (op == "<=") return lval <= rval;
				if (op == "==") return lval == rval;
				if (op == "!=") return lval != rval;
				throw PARuntimeError(std::format("Unknown compare operation: {}", op));
			},
			Type::T_BOOL
		};
	}

	/**
	 * @brief 编译加法/减法表达式
	 *
	 * @param ctx			- Add_exprContext 节点
	 * @return TypedExpr	- 若存在加减级别运算符，返回数值/字串类型的表达式闭包
	 * 						  若不存在，则透传任意类型的表达式闭包
	 * @details				- 对于 STR 类型，仅支持字串拼接，即 "+" 运算符
	 */
	TypedExpr compileAdd(::PostAnvilParser::Add_exprContext* ctx) {
		auto mul_exprs = ctx->mul_expr();
		auto left = compileMul(mul_exprs[0]);
		auto add_ops = ctx->add_op();

		// 不存在加减级别运算符
		if (add_ops.empty()) {
			return left;
		}

		// 递归右式计算
		for (size_t i = 0; i < add_ops.size(); i++) {
			std::string op = getAddOp(add_ops[i]);
			auto right = compileMul(mul_exprs[i + 1]);

			// 左右式类别检查
			if (!type_compatible(left.type, right.type)) {
				auto err = std::format(
					"Add/Sub type mismatch: {} vs {}",
					type_name(left.type),
					type_name(right.type));
				report_semantic_error(err, ctx);
			}
			Type res_type = left.type & right.type;	// 获取运算结果类别

			// 布尔类型检查
			if (type_strict_equal(res_type, Type::T_BOOL)) {
				report_semantic_error("Add expr not supported for BOOL", ctx);
			}
			if (type_strict_equal(res_type, Type::T_INST)) {
				report_semantic_error("Arithmetic is not supported for INST values", ctx);
			}
			if (op == "-" && type_strict_equal(res_type, Type::T_STR)) {
				report_semantic_error("Subtraction not supported for STR", ctx);
			}
			if (op == "-" && !type_compatible(res_type, Type::T_NUM)) {
				report_semantic_error("Add expr only supporte NUM", ctx);
			}

			left = {
				[l = std::move(left.func), r = std::move(right.func), o = std::move(op)]
				(EvaluationContext& ctx) {
					Val lv = l(ctx);
					Val rv = r(ctx);
					if (o == "+") return lv + rv;
					if (o == "-") return lv - rv;
					throw PARuntimeError(std::format("Unknown operation: {}", o));
				},
				res_type
			};
		}
		return left;
	}

	 /**
	  * @brief 编译乘法/除法表达式
	  *
	  * @param ctx			- Mul_exprContext 节点
	  * @return TypedExpr	- 若存在乘除级别运算符，返回数值类型的表达式闭包；
	  *						  否则透传任意类型的表达式闭包
	  * @details			- 仅支持 NUM 类型的乘法与除法（编译期检查）；
	  *						  T_ANY 类型在运行时检查，除零返回 0。
	  */
	TypedExpr compileMul(::PostAnvilParser::Mul_exprContext* ctx) {
		auto unary_exprs = ctx->unary_expr();
		auto left = compileUnary(unary_exprs[0]);
		auto mul_ops = ctx->mul_op();

		// 不存在乘除级别运算符，透传
		if (mul_ops.empty()) {
			return left;
		}

		// 递归右式计算
		for (size_t i = 0; i < mul_ops.size(); i++) {
			std::string op = getMulOp(mul_ops[i]);
			auto right = compileUnary(unary_exprs[i + 1]);

			// 左右式类别检查
			if (!type_compatible(left.type, right.type)) {
				auto err = std::format(
					"Mul/Div type mismatch: {} vs {}",
					type_name(left.type),
					type_name(right.type));
				report_semantic_error(err, ctx);
			}
			Type res_type = left.type & right.type; // 获取运算结果类别

			// 只允许数值类型
			if (!type_compatible(res_type, Type::T_NUM)) {
				report_semantic_error("Mul/Div requires NUM operands", ctx);
			}

			left = {
				[l = std::move(left.func), r = std::move(right.func), o = std::move(op)]
				(EvaluationContext& ctx) {
					Val lv = l(ctx);
					Val rv = r(ctx);
					if (o == "*") return lv * rv;
					if (o == "/") return lv / rv;
					throw PARuntimeError(std::format("Unknown operation: {}", o));
				},
				res_type
			};
		}
		return left;
	}

	/**
	 * @brief 编译一元表达式，当前仅支持负号
	 *
	 * @param ctx			- Unary_exprContext 节点
	 * @return TypedExpr	- 若存在一元表达式，则返回数值类型的表达式闭包
	 *						  否则透传任意类型的表达式闭包
	 */
	TypedExpr compileUnary(::PostAnvilParser::Unary_exprContext* ctx) {
		if (!ctx->MINUS()) {
			return compilePrimary(ctx->primary());
		}

		auto op = ctx->MINUS()->getText();
		auto rhs = compileUnary(ctx->unary_expr());
		if (op == "-") {
			if (!type_compatible(rhs.type, Type::T_NUM)) {
				auto err = std::format("Unary minus requires NUM operand, got {}", type_name(rhs.type));
				report_semantic_error(err, ctx);
			}

			return {
				[r = std::move(rhs.func)]
				(EvaluationContext& ctx) -> Val {
					return -(r(ctx).as_num());
				},
				Type::T_NUM
			};
		}

		auto err = std::format("Unknown unary operation: {}", op);
		report_internal_error(err, ctx);
	}

	/**
	 * @brief 编译基本表达式，处理字面量、变量引用、函数调用、属性访问和括号表达式等
	 *
	 * @param ctx			- PrimaryContext 节点
	 * @return TypedExpr	- 表达式解析闭包
	 */
	TypedExpr compilePrimary(::PostAnvilParser::PrimaryContext* ctx) {
		// NUMBER
		if (ctx->NUMBER()) {
			return compileNumber(ctx);
		}

		// STRING
		if (ctx->STRING()) {
			return compileString(ctx);
		}

		// BOOL_LIT
		if (ctx->BOOL_LIT()) {
			return compileBoolean(ctx);
		}

		// SELF 当前实例值
		if (ctx->SELF()) {
			return {
				[](EvaluationContext& eval_ctx) -> Val {
					if (!eval_ctx.curr_handle) {
						throw PARuntimeError("SELF is unavailable outside an instance context");
					}
					return Val(eval_ctx.curr_handle);
				},
				Type::T_INST
			};
		}

		//  IDENTIFIER 局部/全局变量
		if (ctx->IDENTIFIER()) {
			return compileVariable(ctx);
		}

		// func_call 函数调用闭包
		if (ctx->func_call()) {
			return compileFuncCall(ctx->func_call());
		}

		// 属性调用闭包
		if (ctx->attribute()) {
			return compileAttribute(ctx->attribute());
		}

		// 括号表达式闭包
		if (ctx->LPAREN() && ctx->expr() && ctx->RPAREN()) {
			return compile(ctx->expr());
		}

		auto err = std::format("Unknown primary item {}", ctx->getText());
		report_internal_error(err, ctx);
	}

	/**
	 * @brief 编译数字终结符，返回数字常量闭包
	 *
	 * @param ctx			- PrimaryContext 节点
	 * @return TypedExpr	- T_NUM 类型的闭包
	 */
	TypedExpr compileNumber(::PostAnvilParser::PrimaryContext* ctx) {
		double v = std::stod(ctx->NUMBER()->getText());
		return {
			[v](EvaluationContext&) {
				return Val(v);
			},
			Type::T_NUM
		};
	}

	/**
	 * @brief 编译字串字面量终结符，返回字串字面量闭包
	 *
	 * @param ctx			- PrimaryContext 节点
	 * @return TypedExpr	- T_STR 类型的闭包
	 */
	TypedExpr compileString(::PostAnvilParser::PrimaryContext* ctx) {
		std::string s = utils::strip_quotes(ctx->STRING()->getText());
		return {
			[s = std::move(s)](EvaluationContext&) {
				return Val(s);
			},
			Type::T_STR
		};
	}

	/**
	 * @brief 编译布尔终结符，返回布尔闭包
	 *
	 * @param ctx			- PrimaryContext 节点
	 * @return TypedExpr	- T_STR 类型的闭包
	 */
	TypedExpr compileBoolean(::PostAnvilParser::PrimaryContext* ctx) {
		std::string text = utils::get_upper_text(ctx->BOOL_LIT());
		bool v = (text == "TRUE");
		return {
			[v](EvaluationContext&) {
				return Val(v);
			},
			Type::T_BOOL
		};
	}

	/**
	 * @brief 编译变量终结符，返回变量对应类型闭包
	 *
	 * @param ctx			- PrimaryContext 节点
	 * @return	TypedExpr	- 变量对应类型的闭包
	 */
	TypedExpr compileVariable(::PostAnvilParser::PrimaryContext* ctx) {
		std::string var = utils::get_upper_text(ctx->IDENTIFIER());
		Type var_type = Type::T_ANY;

		// 获取定义类型类型，否则报错
		if ((m_type_scope && m_type_scope->lookup(var, var_type)) == false) {
			report_semantic_error(std::format("Undefined variable: {}", var), ctx);
		}

		return {
			[var](EvaluationContext& ctx) -> Val {
				// 使用 get_var 查找局部/全局
				return ctx.get_var(var);
			},
			var_type
		};
	}

	/**
	 * @brief 编译属性访问表达式，属性均为动态可变类型，故闭包返回 ANY ，支持以下形式
	 *			1. self.prop	: 实例的属性访问，T_ANY，InstanceAttr
	 *			2. class.prop	: 类别的属性访问，T_ANY，ClassAttr
	 *			3. var.prop		: 变量的属性访问，T_ANY，VarInstanceAttr
	 *							对于 var 为预定义对象的情况，解析其属性
	 *							对于 var 为循环实例的情况，将其解析为实例，即 1 的情况
	 *							对于 var 为字串类型的情况，将其解析为类别，即 2 的情况
	 *			4. object.(expr): 显式动态属性访问，expr 必须在运行时产生 STR 属性名
	 *
	 * @param ctx			- AttributeContext 节点
	 * @return TypedExpr	- T_ANY 类型的闭包
	 */
	TypedExpr compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
		auto normalize_prop = [](std::string prop) {
			utils::to_upper_inplace(prop);
			return prop;
		};

		// 1. self.prop		: SELF '.' IDENTIFIER
		if (auto* inst = dynamic_cast<::PostAnvilParser::InstanceAttrContext*>(ctx)) {
			auto prop = utils::get_upper_text(inst->IDENTIFIER());
			return {
				[prop](EvaluationContext& ctx) -> Val {
					return ctx.scene.inst_prop(ctx.curr_handle, prop);
				},
				Type::T_ANY
			};
		}

		// 2. class.prop	: STRING '.' IDENTIFIER
		if (auto* cls = dynamic_cast<::PostAnvilParser::ClassAttrContext*>(ctx)) {
			auto cls_name = utils::strip_quotes(utils::get_upper_text(cls->STRING()));
			auto prop = utils::get_upper_text(cls->IDENTIFIER());
			return {
				[cls_name, prop](EvaluationContext& ctx) -> Val {
					return ctx.scene.cls_prop(cls_name, prop);
				},
				Type::T_ANY
			};
		}

		// 3. var.prop		: IDENTIFIER '.' IDENTIFIER
		if (auto* var = dynamic_cast<::PostAnvilParser::VarInstanceAttrContext*>(ctx)) {
			auto identifiers = var->IDENTIFIER();
			if (identifiers.size() < 2) {
				report_internal_error("Invalid VarInstanceAttr syntax, missing identifier", ctx);
			}

			auto object = utils::get_upper_text(identifiers[0]);
			auto prop = utils::get_upper_text(identifiers[1]);

			// 1. img.prop	: 预定义图像对象属性
			if (object == OBJECT_IMAGE) {
				return {
					[prop](EvaluationContext& ctx) -> Val {
						return ctx.scene.img_prop(prop);
					},
					Type::T_ANY
				};
			}

			Type object_type = Type::T_ANY;
			if (!m_type_scope || !m_type_scope->lookup(object, object_type)) {
				report_semantic_error(std::format("Undefined object variable: {}", object), ctx);
			}
			if (!type_compatible(object_type, Type::T_INST) &&
				!type_compatible(object_type, Type::T_STR)) {
				report_semantic_error(std::format(
					"Property access requires INST or STR, got {}", type_name(object_type)), ctx);
			}

			return {
				[object, prop](EvaluationContext& ctx) -> Val {
					Val object_val = ctx.get_var(object);
					if (type_strict_equal(object_val.type(), Type::T_INST)) {
						return ctx.scene.inst_prop(object_val.as_inst(), prop);
					}
					if (type_strict_equal(object_val.type(), Type::T_STR)) {
						std::string cls_name = object_val.as_str();
						utils::to_upper_inplace(cls_name);
						return ctx.scene.cls_prop(cls_name, prop);
					}
					throw PARuntimeError(std::format(
						"Property access on '{}' requires INST or STR, got {}",
						object, type_name(object_val.type())));
				},
				Type::T_ANY
			};
		}

		// 4. self.(expr)：动态实例属性
		if (auto* inst = dynamic_cast<::PostAnvilParser::DynamicInstanceAttrContext*>(ctx)) {
			auto prop_expr = compileAsStr(inst->expr());
			return {
				[prop_expr = std::move(prop_expr), normalize_prop]
				(EvaluationContext& ctx) -> Val {
					auto prop = normalize_prop(prop_expr(ctx));
					return ctx.scene.inst_prop(ctx.curr_handle, prop);
				},
				Type::T_ANY
			};
		}

		// 5. "class".(expr)：动态类别属性
		if (auto* cls = dynamic_cast<::PostAnvilParser::DynamicClassAttrContext*>(ctx)) {
			auto cls_name = utils::strip_quotes(utils::get_upper_text(cls->STRING()));
			auto prop_expr = compileAsStr(cls->expr());
			return {
				[cls_name, prop_expr = std::move(prop_expr), normalize_prop]
				(EvaluationContext& ctx) -> Val {
					auto prop = normalize_prop(prop_expr(ctx));
					return ctx.scene.cls_prop(cls_name, prop);
				},
				Type::T_ANY
			};
		}

		// 6. var.(expr)：动态实例/类别/图像属性
		if (auto* var = dynamic_cast<::PostAnvilParser::DynamicVarAttrContext*>(ctx)) {
			auto object = utils::get_upper_text(var->IDENTIFIER());
			auto prop_expr = compileAsStr(var->expr());

			if (object == OBJECT_IMAGE) {
				return {
					[prop_expr = std::move(prop_expr), normalize_prop]
					(EvaluationContext& ctx) -> Val {
						auto prop = normalize_prop(prop_expr(ctx));
						return ctx.scene.img_prop(prop);
					},
					Type::T_ANY
				};
			}

			Type object_type = Type::T_ANY;
			if (!m_type_scope || !m_type_scope->lookup(object, object_type)) {
				report_semantic_error(std::format("Undefined object variable: {}", object), ctx);
			}
			if (!type_compatible(object_type, Type::T_INST) &&
				!type_compatible(object_type, Type::T_STR)) {
				report_semantic_error(std::format(
					"Dynamic property access requires INST or STR object, got {}", type_name(object_type)), ctx);
			}

			return {
				[object, prop_expr = std::move(prop_expr), normalize_prop]
				(EvaluationContext& ctx) -> Val {
					auto prop = normalize_prop(prop_expr(ctx));
					Val object_val = ctx.get_var(object);
					if (type_strict_equal(object_val.type(), Type::T_INST)) {
						return ctx.scene.inst_prop(object_val.as_inst(), prop);
					}
					if (type_strict_equal(object_val.type(), Type::T_STR)) {
						std::string cls_name = object_val.as_str();
						utils::to_upper_inplace(cls_name);
						return ctx.scene.cls_prop(cls_name, prop);
					}
					throw PARuntimeError(std::format(
						"Dynamic property access on '{}' requires INST or STR, got {}",
						object, type_name(object_val.type())));
				},
				Type::T_ANY
			};
		}

		// 无法识别的属性访问节点类型
		report_internal_error("Unknown AttributeContext node type", ctx);
	}

	/**
	 * @brief 编译函数调用表达式
	 *
	 * @param ctx			- Func_callContext 节点
	 * @return TypedExpr	- 函数声明返回值类型的闭包，若未声明则为 T_ANY
	 */
	TypedExpr compileFuncCall(::PostAnvilParser::Func_callContext* ctx) {
		std::string func_name = utils::get_upper_text(ctx->IDENTIFIER());

		// 编译参数列表
		std::vector<TypedExpr> arg_exprs;
		for (auto* expr_ctx : ctx->expr()) {
			arg_exprs.emplace_back(compile(expr_ctx));
		}

		// 查询函数返回类型
		Type ret_type = Type::T_ANY;
		auto it = m_functions->find(func_name);
		if (it != m_functions->end()) {
			ret_type = it->second.ret_type;
			const auto& param_types = it->second.param_types;
			if (arg_exprs.size() != param_types.size()) {
				report_semantic_error(std::format(
					"Function '{}' expects {} arguments, got {}",
					func_name, param_types.size(), arg_exprs.size()), ctx);
			}
			for (size_t i = 0; i < arg_exprs.size(); ++i) {
				if (!type_compatible(param_types[i], arg_exprs[i].type)) {
					report_semantic_error(std::format(
						"Function '{}' argument {} expects {}, got {}",
						func_name, i + 1, type_name(param_types[i]), type_name(arg_exprs[i].type)), ctx);
				}
			}
		}
		else {
			report_semantic_error(std::format("Undefined function: '{}'", func_name), ctx);
		}

		return {
			[func_name, arg_exprs = std::move(arg_exprs)]
			(EvaluationContext& ctx) -> Val {
				auto it = ctx.functions.find(func_name);
				if (it == ctx.functions.end()) {
					throw PARuntimeError(std::format("Undefined function: '{}'", func_name));
				}
				const auto& compiled_func = it->second;

				// 参数求值
				std::vector<Val> args;
				args.reserve(arg_exprs.size());
				for (auto& arg_expr : arg_exprs) {
					args.emplace_back(arg_expr.func(ctx));
				}

				return compiled_func.func(args, ctx);
			},
			ret_type
		};
	}

	// ======================== 操作符提取 ============================

	/**
	 * @brief 从比较操作符上下文提取操作符字符串
	 */
	static std::string getCompOp(::PostAnvilParser::Comp_opContext* ctx) {
		if (ctx->GT()) return ">";
		if (ctx->LT()) return "<";
		if (ctx->GE()) return ">=";
		if (ctx->LE()) return "<=";
		if (ctx->EQ()) return "==";
		if (ctx->NE()) return "!=";
		report_internal_error("Unknown comp op, expected: >,<,>=,<=,==,!=", ctx);
	}

	/**
	 * @brief 从加减操作符上下文提取操作符字符串
	 */
	static std::string getAddOp(::PostAnvilParser::Add_opContext* ctx) {
		if (ctx->PLUS())  return "+";
		if (ctx->MINUS()) return "-";
		report_internal_error("Unknown add op, expected '+' or '-'", ctx);
	}

	/**
	 * @brief 从乘除操作符上下文提取操作符字符串
	 */
	static std::string getMulOp(::PostAnvilParser::Mul_opContext* ctx) {
		if (ctx->STAR())  return "*";
		if (ctx->SLASH()) return "/";
		report_internal_error("Unknown mul op, expected '*' or '/'", ctx);
	}

	/**
	 * @brief 函数注册表指针，由主编译器设置，用于编译函数调用时查找已定义的函数体
	 */
	detail::str_map<FunctionInfo>* m_functions = nullptr;

	/**
	 * @brief 变量符号表，由主编译器设置
	 */
	detail::ScopeChain<Type>* m_type_scope = nullptr;
};

} // namespace postanvil
