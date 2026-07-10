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

/**
 * @brief 表达式编译器
 * @details 接收 ANTLR4 表达式 ParseTree 节点，递归编译为 TypedExpr 闭包
 *          编译期完成类型推导和检查，运行时通过 Val 传递值
 *          支持的表达式层级：expr → or/and/not/cmp/add/mul/unary → primary
 */
class TreeExprCompiler {
public:
	static const inline char* OBJECT_SELF = "SELF";
	static const inline char* OBJECT_IMAGE = "IMG";

	/**
	 * @brief 函数注册表指针，由外部编译器设置
	 * @details 用于编译函数调用时查找已定义的函数体
	 */
	std::unordered_map<std::string, CompiledFunc>* functions = nullptr;

	/**
	 * @brief 全局变量类型表指针，由外部编译器设置
	 * @details 用于编译 IDENTIFIER 表达式时确定变量的声明类型
	 */
	std::unordered_map<std::string, Type>* global_types = nullptr;

	TreeExprCompiler() = default;

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
		return [func](const Instance& self, const Scene& scene) {
			return func(self, scene).as_bool();
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
		return [func](const Instance& self, const Scene& scene) {
			return func(self, scene).as_num();
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
			std::string s = utils::strip_quotes(ctx->STRING()->getText());
			utils::to_upper_inplace(s);
			return [s = std::move(s)](const Instance&, const Scene&) {
				return s;
			};
		}

		// 字符串变量
		if (ctx->IDENTIFIER()) {
			std::string var = ctx->IDENTIFIER()->getText();
			utils::to_upper_inplace(var);

			return [var = std::move(var)](const Instance&, const Scene& scene) {
				if (auto it = scene.variables.find(var); it == scene.variables.end()) {
					throw RuntimeError("Target variable '" + var +
						"' not found in scene (used as class_expr)");
				}
				auto str = scene.variables.at(var).as_str();
				utils::to_upper_inplace(str);
				return str;
			};
		}
		throw CompileError("Invalid class_expr: expected STRING or IDENTIFIER");
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
				(const Instance& self, const Scene& scene) -> Val {
					return l(self, scene).as_bool() || r(self, scene).as_bool();
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
				(const Instance& self, const Scene& scene) -> Val {
					return l(self, scene).as_bool() && r(self, scene).as_bool();
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
			(const Instance& self, const Scene& scene) -> Val {
				return !r(self, scene).as_bool();
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
			(const Instance& self, const Scene& scene) -> Val {
				auto lval = l(self, scene);
				auto rval = r(self, scene);
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
				(const Instance& self, const Scene& scene) {
					Val lv = l(self, scene);
					Val rv = r(self, scene);
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
				(const Instance& self, const Scene& scene) {
					Val lv = l(self, scene);
					Val rv = r(self, scene);
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
				(const Instance& self, const Scene& scene) -> Val {
					return -(r(self, scene).as_num());
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
		// 数字字面量闭包
		if (ctx->NUMBER()) {
			double v = std::stod(ctx->NUMBER()->getText());
			return {
				[v](const Instance&, const Scene&) {
					return Val(v);
				},
				Type::T_NUM
			};
		}

		// 字串字面量闭包
		if (ctx->STRING()) {
			std::string s = utils::strip_quotes(ctx->STRING()->getText());
			return {
				[s = std::move(s)](const Instance&, const Scene&) {
					return Val(s);
				},
				Type::T_STR
			};
		}

		// 布尔字面量闭包
		if (ctx->BOOL_LIT()) {
			std::string text = ctx->BOOL_LIT()->getText();
			utils::to_upper_inplace(text);
			bool v = (text == "TRUE");
			return {
				[v](const Instance&, const Scene&) {
					return Val(v);
				},
				Type::T_BOOL
			};
		}

		// 标识符-变量闭包
		if (ctx->IDENTIFIER()) {
			std::string var = ctx->IDENTIFIER()->getText();
			utils::to_upper_inplace(var);

			// 若是声明过全局变量或者导入全局变量，指定类型，否则为 ANY
			Type var_type = Type::T_ANY;
			if (global_types) {
				auto it = global_types->find(var);
				if (it != global_types->end()) {
					var_type = it->second;
				}
			}

			return {
				[var](const Instance&, const Scene& scene) -> Val {
					auto it = scene.variables.find(var);
					if (it == scene.variables.end()) {
						throw RuntimeError("Undefined variable '" + var + "'");
					}
					return it->second;
				},
				var_type
			};
		}

		// 函数调用闭包
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
	 * @brief 编译属性访问表达式，属性均为动态可变类型，故闭包返回 ANY ，支持以下形式
	 *			1. self.prop	: 实例的属性访问，T_ANY
	 *			2. class.prop	: 类别的属性访问，T_ANY
	 *			3. var.prop		: 变量的属性访问，T_ANY
	 * 
	 * @param ctx			- AttributeContext 节点
	 * @return TypedExpr	- T_ANY 类型的闭包
	 */
	TypedExpr compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
		// 1. self.prop
		if (auto* inst = dynamic_cast<::PostAnvilParser::InstanceAttrContext*>(ctx)) {
			auto prop = inst->IDENTIFIER()->getText();
			utils::to_upper_inplace(prop);
			return {
				[prop](const Instance& self, const Scene& scene) -> Val {
					return scene.get_inst_prop(self, prop);
				},
				Type::T_ANY
			};
		}

		// 2. class.prop
		if (auto* cls = dynamic_cast<::PostAnvilParser::ClassAttrContext*>(ctx)) {
			auto cls_name = utils::strip_quotes(cls->STRING()->getText());
			auto prop = cls->IDENTIFIER()->getText();
			utils::to_upper_inplace(cls_name);
			utils::to_upper_inplace(prop);

			return {
				[cls_name, prop](const Instance&, const Scene& scene) -> Val {
					return scene.get_cls_prop(cls_name, prop);
				},
				Type::T_ANY
			};
		}

		// 3. var.prop
		if (auto* var = dynamic_cast<::PostAnvilParser::VarInstanceAttrContext*>(ctx)) {
			auto identifiers = var->IDENTIFIER();
			if (identifiers.size() < 2) {
				throw CompileError("Invalid VarInstanceAttr syntax, missing identifier");
			}

			auto object = identifiers[0]->getText();
			auto prop = identifiers[1]->getText();
			utils::to_upper_inplace(object);
			utils::to_upper_inplace(prop);

			if (object == OBJECT_IMAGE) {
				return {
					[prop](const Instance&, const Scene& scene) -> Val {
						return scene.get_img_prop(prop);
					},
					Type::T_ANY
				};
			}
			// 除 img.prop 外其他变量属性暂未实现
			throw CompileError("Unimplemented var.prop expression (only img.prop supported)");
		}

		// 无法识别的属性访问节点类型
		throw CompileError("Unknown AttributeContext node type");
	}

	/**
	 * @brief 编译函数调用表达式
	 * 
	 * @param ctx			- Func_callContext 节点
	 * @return TypedExpr	- 函数声明返回值类型的闭包，若未声明则为 T_ANY
	 */
	TypedExpr compileFuncCall(::PostAnvilParser::Func_callContext* ctx) {
		handle_compile_error("Unimplemented function call", ctx);
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
				(const Instance& self, const Scene& scene) -> Val {
				auto cls_name = cls(self, scene);

				const auto it = scene.objects.find(cls_name);
				if (it == scene.objects.end() || it->second.empty()) {
					throw RuntimeError(std::format("SORT: class '{}' not found or empty", cls_name));
				}

				const auto& instances = it->second;
				std::vector<Val> keys;
				keys.reserve(instances.size());
				for (const auto& inst : instances) {
					keys.emplace_back(key(inst, scene));
				}

				double rank_val = rank(self, scene);
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