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

namespace postanvil {

// ====================== TreeExprCompiler =========================


[[noreturn]]
static void handle_compile_error(const std::string& msg, const ::antlr4::ParserRuleContext* ctx = nullptr) {
	if (!ctx) {
		throw CompileError(msg);
	}
	auto start = ctx->getStart();
	throw CompileError(msg,
		static_cast<int>(start->getLine()),
		static_cast<int>(start->getCharPositionInLine())
	);
}


/**
 * @brief 表达式编译器
 * @details 接收 ANTLR4 表达式 ParseTree 节点，递归编译为 TypedExpr 闭包
 *          编译期完成类型推导和检查，运行时通过 Val 传递值
 *          支持的表达式层级：expr → or/and/not/cmp/add/mul/unary → primary
 */
class TreeExprCompiler {
	/**
	 * @brief 函数注册表指针，由外部编译器设置
	 * @details 用于编译函数调用时查找已定义的函数体
	 */
	detail::str_map<CompiledFunc>* functions = nullptr;

	/**
	 * @brief 全局变量类型表指针，由外部编译器设置
	 * @details 用于编译 IDENTIFIER 表达式时确定变量的声明类型
	 */
	detail::str_map<Type>* global_types = nullptr;

	/**
	 * @brief 局部变量类型表
	 * @details 用于编译函数和循环变量时的局部变量类型
	 */
	std::vector<detail::str_map<Type>> local_type_stack;

public:
	static const inline char* OBJECT_SELF = "SELF";
	static const inline char* OBJECT_IMAGE = "IMG";

	TreeExprCompiler() = default;

	void set_functions(detail::str_map<CompiledFunc>* functions) {
		this->functions = functions;
	}

	void set_global_types(detail::str_map<Type>* global_types) {
		this->global_types = global_types;
	}

	void push_local_scope() {
		local_type_stack.emplace_back();
	}

	void pop_local_scope() {
		local_type_stack.pop_back();
	}

	void setLocalType(const std::string& name, Type t) {
		if (!local_type_stack.empty()) {
			local_type_stack.back()[name] = t;
		}
	}

public: // public method:

	/**
	 * @brief 编译表达式为闭包的入口方法
	 * 
	 * @param ctx			- ANTLR4 ExprContext 节点
	 * @return TypedExpr	- 带类型的表达式闭包
	 * @throw CompileError	- 编译错误，包含编译信息
	 */
	TypedExpr compile(::PostAnvilParser::ExprContext* ctx) {
		if (!ctx || !ctx->or_expr()) {
			handle_compile_error("Empty ExprContext node type", ctx);
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
		if (typed.type != Type::T_BOOL && typed.type != Type::T_ANY) {
			auto err = std::format("Bool-expr must be BOOL or ANY(runtime bool), got {}", type_name(typed.type));
			handle_compile_error(err, ctx);
		}
		const auto& func = typed.func;
		return [func](const Instance& self, EvaluationContext& ctx) {
			return func(self, ctx).as_bool();
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
		if (typed.type != Type::T_NUM && typed.type != Type::T_ANY) {
			auto err = std::format("Num-expr must be NUM or ANY(runtime NUM), got {}", type_name(typed.type));
			handle_compile_error(err, ctx);
		}
		const auto& func = typed.func;
		return [func](const Instance& self, EvaluationContext& ctx) {
			return func(self, ctx).as_num();
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
			return [s = std::move(s)](const Instance&, EvaluationContext&) {
				return s;
			};
		}

		// 字符串变量
		if (ctx->IDENTIFIER()) {
			std::string var = utils::get_upper_text(ctx->IDENTIFIER());

			return [var = std::move(var)](const Instance&, EvaluationContext& ctx) {
				Val val = ctx.get_var(var);
				auto str = val.as_str();
				utils::to_upper_inplace(str);
				return str;
			};
		}
		handle_compile_error("Invalid class_expr: expected STRING or IDENTIFIER", ctx);
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
		if (left.type != Type::T_BOOL && left.type != Type::T_ANY) {
			auto err = std::format("Left OR-expr must be BOOL or ANY(runtime bool), got {}", type_name(left.type));
			handle_compile_error(err, ctx);
		}

		// 递归右式类别检查
		for (size_t i = 0; i < or_count; i++) {
			auto right = compileAnd(and_exprs[i + 1]);
			if (right.type != Type::T_BOOL && right.type != Type::T_ANY) {
				auto err = std::format("Right OR-expr must be BOOL or ANY(runtime bool), got {}", type_name(right.type));
				handle_compile_error(err, ctx);
			}
			left = {
				[l = std::move(left.func), r = std::move(right.func)]
				(const Instance& self, EvaluationContext& ctx) -> Val {
					return l(self, ctx).as_bool() || r(self, ctx).as_bool();
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
		if (left.type != Type::T_BOOL && left.type != Type::T_ANY) {
			auto err = std::format("Left AND-expr must be BOOL or ANY(runtime bool), got {}", type_name(left.type));
			handle_compile_error(err, ctx);
		}

		// 递归右式类别检查
		for (size_t i = 0; i < and_count; i++) {
			auto right = compileNot(not_exprs[i + 1]);
			if (right.type != Type::T_BOOL && right.type != Type::T_ANY) {
				auto err = std::format("Right AND-expr must be BOOL or ANY(runtime bool), got {}", type_name(right.type));
				handle_compile_error(err, ctx);
			}
			left = { [l = std::move(left.func), r = std::move(right.func)]
				(const Instance& self, EvaluationContext& ctx) -> Val {
					return l(self, ctx).as_bool() && r(self, ctx).as_bool();
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
		if (rhs.type != Type::T_BOOL && rhs.type != Type::T_ANY) {
			auto err = std::format("NOT-expr must be BOOL or ANY(runtime bool), got {}", type_name(rhs.type));
			handle_compile_error(err, ctx);
		}
		return { [r = std::move(rhs.func)]
			(const Instance& self, EvaluationContext& ctx) -> Val {
				return !r(self, ctx).as_bool();
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

		if (res_type == Type::T_ERROR) {
			auto err = std::format("Comparison type mismatch: {} vs {}", type_name(left.type), type_name(right.type));
			handle_compile_error(err, ctx);
		}

		// 布尔类型仅支持相等/不等判断
		if (res_type == Type::T_BOOL && op != "==" && op != "!=") {
			auto err = std::format("Operator '{}' not supported for BOOL", op);
			handle_compile_error(err, ctx);
		}

		return { [l = std::move(left.func), r = std::move(right.func), op = std::move(op)]
			(const Instance& self, EvaluationContext& ctx) -> Val {
				auto lval = l(self, ctx);
				auto rval = r(self, ctx);
				if (op == ">")  return lval >  rval;
				if (op == "<")  return lval <  rval;
				if (op == ">=") return lval >= rval;
				if (op == "<=") return lval <= rval;
				if (op == "==") return lval == rval;
				if (op == "!=") return lval != rval;
				throw RuntimeError(std::format("Unknown compare operation: {}", op));
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
			if (left.type != right.type && left.type != Type::T_ANY && right.type != Type::T_ANY) {
				auto err = std::format("Add/Sub type mismatch: {} vs {}", type_name(left.type), type_name(right.type));
				handle_compile_error(err, ctx);
			}
			Type res_type = left.type & right.type;	// 获取运算结果类别

			// 布尔类型检查
			if (res_type == Type::T_BOOL) {
				handle_compile_error("Add expr not supported for BOOL", ctx);
			}
			if (op == "-" && res_type == Type::T_STR) {
				handle_compile_error("Subtraction not supported for STR", ctx);
			}
			if (op == "-" && res_type != Type::T_NUM && res_type != Type::T_ANY) {
				handle_compile_error("Add expr only supporte NUM", ctx);
			}

			left = {
				[l = std::move(left.func), r = std::move(right.func), o = std::move(op)]
				(const Instance& self, EvaluationContext& ctx) {
					Val lv = l(self, ctx);
					Val rv = r(self, ctx);
					if (o == "+") return lv + rv;
					if (o == "-") return lv - rv;
					throw RuntimeError(std::format("Unknown operation: {}", o));
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
			if (left.type != right.type && left.type != Type::T_ANY && right.type != Type::T_ANY) {
				auto err = std::format("Mul/Div type mismatch: {} vs {}", type_name(left.type), type_name(right.type));
				handle_compile_error(err, ctx);
			}
			Type res_type = left.type & right.type; // 获取运算结果类别

			// 只允许数值类型
			if (res_type != Type::T_NUM && res_type != Type::T_ANY) {
				handle_compile_error("Mul/Div requires NUM operands", ctx);
			}

			left = {
				[l = std::move(left.func), r = std::move(right.func), o = std::move(op)]
				(const Instance& self, EvaluationContext& ctx) {
					Val lv = l(self, ctx);
					Val rv = r(self, ctx);
					if (o == "*") return lv * rv;
					if (o == "/") return lv / rv;
					throw RuntimeError(std::format("Unknown operation: {}", o));
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
			if (rhs.type != Type::T_NUM && rhs.type != Type::T_ANY) {
				auto err = std::format("Unary minus requires NUM operand, got {}", type_name(rhs.type));
				handle_compile_error(err, ctx);
			}

			return {
				[r = std::move(rhs.func)]
				(const Instance& self, EvaluationContext& ctx) -> Val {
					return -(r(self, ctx).as_num());
				},
				Type::T_NUM
			};
		}

		auto err = std::format("Unknown unary operation: {}", op);
		handle_compile_error(err, ctx);
	}

	/**
	 * @brief 编译基本表达式，处理字面量、变量引用、函数调用、属性访问、排序原语和括号表达式等
	 * 
	 * @param ctx			- PrimaryContext 节点
	 * @return TypedExpr	- 表达式解析闭包
	 */
	TypedExpr compilePrimary(::PostAnvilParser::PrimaryContext* ctx) {
		// NUMBER
		if (ctx->NUMBER()) {
			return compileNumber(ctx->NUMBER());
		}

		// STRING
		if (ctx->STRING()) {
			return compileString(ctx->STRING());
		}

		// BOOL_LIT
		if (ctx->BOOL_LIT()) {
			return compileBoolean(ctx->BOOL_LIT());
		}

		//  IDENTIFIER 局部/全局变量
		if (ctx->IDENTIFIER()) {
			return compileVariable(ctx->IDENTIFIER());
		}

		// func_call 函数调用闭包
		if (ctx->func_call()) {
			return compileFuncCall(ctx->func_call());
		}

		// 属性调用闭包
		if (ctx->attribute()) {
			return compileAttribute(ctx->attribute());
		}

		// 排序原语闭包
		if (ctx->sortExpr()) {
			return compileSortExpr(ctx->sortExpr());
		}

		// 括号表达式闭包
		if (ctx->LPAREN() && ctx->expr() && ctx->RPAREN()) {
			return compile(ctx->expr());
		}

		auto err = std::format("Unknown primary item {}", ctx->getText());
		handle_compile_error(err, ctx);
	}

	/**
	 * @brief 编译数字终结符，返回数字常量闭包
	 * 
	 * @param node			- 终结节点
	 * @return TypedExpr	- T_NUM 类型的闭包
	 */
	TypedExpr compileNumber(antlr4::tree::TerminalNode* node) {
		double v = std::stod(node->getText());
		return {
			[v](const Instance&, EvaluationContext&) {
				return Val(v);
			},
			Type::T_NUM
		};
	}

	/**
	 * @brief 编译字串字面量终结符，返回字串字面量闭包
	 * 
	 * @param node			- 终结节点
	 * @return TypedExpr	- T_STR 类型的闭包
	 */
	TypedExpr compileString(antlr4::tree::TerminalNode* node) {
		std::string s = utils::strip_quotes(node->getText());
		return {
			[s = std::move(s)](const Instance&, EvaluationContext&) {
				return Val(s);
			},
			Type::T_STR
		};
	}

	/**
	 * @brief 编译布尔终结符，返回布尔闭包
	 *
	 * @param node			- 终结节点
	 * @return TypedExpr	- T_STR 类型的闭包
	 */
	TypedExpr compileBoolean(antlr4::tree::TerminalNode* node) {
		std::string text = utils::get_upper_text(node);
		bool v = (text == "TRUE");
		return {
			[v](const Instance&, EvaluationContext&) {
				return Val(v);
			},
			Type::T_BOOL
		};
	}

	/**
	 * @brief 编译变量终结符，返回变量对应类型闭包
	 * 
	 * @param node			- 终结节点
	 * @return	TypedExpr	- T_STR 类型的闭包
	 */
	TypedExpr compileVariable(antlr4::tree::TerminalNode* node) {
		std::string var = utils::get_upper_text(node);
		Type var_type = Type::T_ANY;

		if (!global_types) {
			auto it = global_types->find(var);
			if (it != global_types->end()) {
				var_type = it->second;
			}
		}

		// TODO: 缺当前局部变量的类型判定

		return {
			[var](const Instance&, EvaluationContext& ctx) -> Val {
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
	 * 
	 * @param ctx			- AttributeContext 节点
	 * @return TypedExpr	- T_ANY 类型的闭包
	 */
	TypedExpr compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
		// 1. self.prop		: SELF '.' IDENTIFIER
		if (auto* inst = dynamic_cast<::PostAnvilParser::InstanceAttrContext*>(ctx)) {
			auto prop = utils::get_upper_text(inst->IDENTIFIER());
			return {
				[prop](const Instance& self, EvaluationContext& ctx) -> Val {
					return ctx.scene.get_inst_prop(self, prop);
				},
				Type::T_ANY
			};
		}

		// 2. class.prop	: STRING '.' IDENTIFIER
		if (auto* cls = dynamic_cast<::PostAnvilParser::ClassAttrContext*>(ctx)) {
			auto cls_name = utils::strip_quotes(utils::get_upper_text(cls->STRING()));
			auto prop = utils::get_upper_text(cls->IDENTIFIER());
			return {
				[cls_name, prop](const Instance&, EvaluationContext& ctx) -> Val {
					return ctx.scene.get_cls_prop(cls_name, prop);
				},
				Type::T_ANY
			};
		}

		// 3. var.prop		: IDENTIFIER '.' IDENTIFIER
		if (auto* var = dynamic_cast<::PostAnvilParser::VarInstanceAttrContext*>(ctx)) {
			auto identifiers = var->IDENTIFIER();
			if (identifiers.size() < 2) {
				handle_compile_error("Invalid VarInstanceAttr syntax, missing identifier", ctx);
			}

			auto object = utils::get_upper_text(identifiers[0]);
			auto prop = utils::get_upper_text(identifiers[1]);
			
			// 1. img.prop	: 预定义图像对象属性
			if (object == OBJECT_IMAGE) {
				return {
					[prop](const Instance&, EvaluationContext& ctx) -> Val {
						return ctx.scene.get_img_prop(prop);
					},
					Type::T_ANY
				};
			}

			// 2. loop_var.prop: 循环实例的属性
			// TODO: 应改为编译期检查

			return {
				[object, prop](const Instance&, EvaluationContext& ctx) -> Val {
					// 循环实例
					auto loop_it = ctx.loop_vars.find(object);
					if (loop_it != ctx.loop_vars.end()) {
						return ctx.scene.get_inst_prop(*loop_it->second, prop);
					}

					// 类别变量-字串类型
					Val cls_val = ctx.get_var(object);
					std::string cls_name = cls_val.as_str();
					utils::to_upper_inplace(cls_name);
					return ctx.scene.get_cls_prop(cls_name, prop);
				},
				Type::T_ANY
			};
		}

		// 无法识别的属性访问节点类型
		handle_compile_error("Unknown AttributeContext node type", ctx);
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

		return {
			[func_name, arg_exprs = std::move(arg_exprs)]
			(const Instance& self, EvaluationContext& ctx) -> Val {
				auto it = ctx.functions.find(func_name);
				if (it == ctx.functions.end()) {
					throw RuntimeError("Undefined function '" + func_name + "'");
				}
				const auto& compiled_func = it->second;

				// 求值参数
				std::vector<Val> args;
				args.reserve(arg_exprs.size());
				for (auto& arg_expr : arg_exprs) {
					args.emplace_back(arg_expr.func(self, ctx));
				}

				return compiled_func(args, self, ctx);
			},
			Type::T_ANY // TODO: 编译时应该维护函数表，确定编译类型，当前为运行时推断
		};
	}

	/**
	 * @brief 编译排序原语 SORT
	 *		  形式：SORT(类别 : STR, 排序键表达式 : ANY, 名次: NUM)
	 * 		  名次为正数表示降序第 N 名，负数表示升序第 |N| 名
	 * 		  返回对应名次的键值
	 * 
	 * @param ctx			- SortExprContext 节点
	 * @return TypedExpr	- 排序原语闭包
	 * 
	 * TODO: 排序原语仍需要设计，此为暂定实现
	 */
	TypedExpr compileSortExpr(::PostAnvilParser::SortExprContext* ctx) {
		// 编译类别表达式
		auto cls = compileClassExpr(ctx->class_expr());

		// 编译排序表达式
		auto key = compile(ctx->expr(0));

		// 编译名次表达式
		auto rank = compileAsNum(ctx->expr(1));

		return {[cls = std::move(cls), key = std::move(key.func), rank = std::move(rank)]
				(const Instance& self, EvaluationContext& ctx) -> Val {
				auto cls_name = cls(self, ctx);

				const auto it = ctx.scene.objects.find(cls_name);
				if (it == ctx.scene.objects.end() || it->second.empty()) {
					throw RuntimeError(std::format("SORT: class '{}' not found or empty", cls_name));
				}

				const auto& instances = it->second;
				std::vector<Val> keys;
				keys.reserve(instances.size());
				for (const auto& inst : instances) {
					keys.emplace_back(key(inst, ctx));
				}

				double rank_val = rank(self, ctx);
				auto rank_int = static_cast<int>(rank_val);
				int index = std::abs(rank_int) - 1;

				if (index < 0 || index >= static_cast<int>(keys.size())) {
					throw RuntimeError(std::format(
						"SORT: index {} out of range (valid 0..{})",
						index, keys.size() - 1));
				}

				if (rank_int < 0) {
					std::nth_element(keys.begin(), keys.begin() + index, keys.end(),
						[](const Val& a, const Val& b) { return a < b; });
				}
				else {
					std::nth_element(keys.begin(), keys.begin() + index, keys.end(),
						[](const Val& a, const Val& b) { return a > b; });
				}

				return keys[index];
			},
			key.type
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
		handle_compile_error("Unknown comp op, expected: >,<,>=,<=,==,!=", ctx);
	}

	/**
	 * @brief 从加减操作符上下文提取操作符字符串
	 */
	static std::string getAddOp(::PostAnvilParser::Add_opContext* ctx) {
		if (ctx->PLUS())  return "+";
		if (ctx->MINUS()) return "-";
		return "";
	}

	/**
	 * @brief 从乘除操作符上下文提取操作符字符串
	 */
	static std::string getMulOp(::PostAnvilParser::Mul_opContext* ctx) {
		if (ctx->STAR())  return "*";
		if (ctx->SLASH()) return "/";
		return "";
	}

};

} // namespace postanvil