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
	 *          编译期完成类型推导和检查，运行时通过 Val 传递多态值
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

		/**
		 * @brief 编译表达式，入口方法
		 * @param ctx ANTLR4 ExprContext 节点
		 * @return TypedExpr 带类型的表达式闭包
		 */
		TypedExpr compile(::PostAnvilParser::ExprContext* ctx) {
			if (!ctx || !ctx->or_expr()) {
				return { [](const Instance&, const Scene&) { return Val(0.0); }, Type::T_NUM };
			}
			return compileOr(ctx->or_expr());
		}

		/**
		 * @brief 编译 or_expr 节点
		 * @param ctx ANTLR4 Or_exprContext 节点
		 * @return TypedExpr 带类型的表达式闭包
		 */
		TypedExpr compile(::PostAnvilParser::Or_exprContext* ctx) {
			if (!ctx) {
				return { [](const Instance&, const Scene&) { return Val(0.0); }, Type::T_NUM };
			}
			return compileOr(ctx);
		}

		/**
		 * @brief 编译为布尔过滤闭包
		 * @param ctx ANTLR4 Or_exprContext 节点
		 * @return BoolFunc 布尔型过滤函数
		 * @throws CompileError 表达式类型不是 BOOL 或 NUM 时抛出
		 * @details NUM 类型按非零为真处理
		 */
		BoolFunc compileAsFilter(::PostAnvilParser::Or_exprContext* ctx) {
			auto typed = compileOr(ctx);
			if (typed.type != Type::T_BOOL && typed.type != Type::T_NUM) {
				throw CompileError("Filter condition must be BOOL or NUM, got " + std::string(type_name(typed.type)));
			}
			auto const& func = typed.func;
			return [func](const Instance& self, const Scene& scene) -> bool {
				return func(self, scene).as_bool();
				};
		}

		/**
		 * @brief 编译为数值闭包
		 * @param ctx ANTLR4 ExprContext 节点
		 * @return NumFunc 数值型函数
		 * @throws CompileError 表达式类型不是 NUM 时抛出
		 * @details 用于属性值计算等必须为数值的上下文
		 */
		NumFunc compileAsNum(::PostAnvilParser::ExprContext* ctx) {
			auto typed = compile(ctx);
			if (typed.type != Type::T_NUM) {
				throw CompileError("Expected NUM expression, got " + std::string(type_name(typed.type)));
			}
			auto func = typed.func;
			return [func](const Instance& self, const Scene& scene) -> double {
				return func(self, scene).as_num();
				};
		}

	private:
		// ======================== 递归编译方法 ============================

		/**
		 * @brief 编译逻辑或表达式
		 * @param ctx Or_exprContext 节点
		 * @return TypedExpr
		 * @details 若存在 OR 运算符，左右操作数必须为 BOOL，结果 BOOL
		 *          若无 OR 运算符则直接透传子表达式
		 */
		TypedExpr compileOr(::PostAnvilParser::Or_exprContext* ctx) {
			auto and_exprs = ctx->and_expr();
			auto left = compileAnd(and_exprs[0]);

			size_t or_count = ctx->OR().size();
			if (or_count == 0) {
				return left;
			}

			if (left.type != Type::T_BOOL) {
				throw CompileError("Left operand of OR must be BOOL, got " + std::string(type_name(left.type)));
			}

			for (size_t i = 0; i < or_count; i++) {
				auto right = compileAnd(and_exprs[i + 1]);
				if (right.type != Type::T_BOOL) {
					throw CompileError("Right operand of OR must be BOOL, got " + std::string(type_name(right.type)));
				}
				left = { [l = std::move(left.func), r = std::move(right.func)]
					(const Instance& self, const Scene& scene) -> Val {
					return Val(l(self, scene).as_bool() || r(self, scene).as_bool());
				}, Type::T_BOOL };
			}
			return left;
		}

		/**
		 * @brief 编译逻辑与表达式
		 * @param ctx And_exprContext 节点
		 * @return TypedExpr
		 * @details 若存在 AND 运算符，左右操作数必须为 BOOL，结果 BOOL
		 *          若无 AND 运算符则直接透传子表达式
		 */
		TypedExpr compileAnd(::PostAnvilParser::And_exprContext* ctx) {
			auto not_exprs = ctx->not_expr();
			auto left = compileNot(not_exprs[0]);

			size_t and_count = ctx->AND().size();
			if (and_count == 0) {
				return left;
			}

			if (left.type != Type::T_BOOL) {
				throw CompileError("Left operand of AND must be BOOL, got " + std::string(type_name(left.type)));
			}

			for (size_t i = 0; i < and_count; i++) {
				auto right = compileNot(not_exprs[i + 1]);
				if (right.type != Type::T_BOOL) {
					throw CompileError("Right operand of AND must be BOOL, got " + std::string(type_name(right.type)));
				}
				left = { [l = std::move(left.func), r = std::move(right.func)]
					(const Instance& self, const Scene& scene) -> Val {
					return Val(l(self, scene).as_bool() && r(self, scene).as_bool());
				}, Type::T_BOOL };
			}
			return left;
		}

		/**
		 * @brief 编译逻辑非表达式
		 * @param ctx Not_exprContext 节点
		 * @return TypedExpr
		 * @details NOT 操作数必须为 BOOL，结果 BOOL
		 *          无 NOT 时直接透传比较表达式
		 */
		TypedExpr compileNot(::PostAnvilParser::Not_exprContext* ctx) {
			if (ctx->NOT()) {
				auto rhs = compileNot(ctx->not_expr());
				if (rhs.type != Type::T_BOOL) {
					throw CompileError("NOT operand must be BOOL, got " + std::string(type_name(rhs.type)));
				}
				return { [r = std::move(rhs.func)]
					(const Instance& self, const Scene& scene) -> Val {
					return Val(!r(self, scene).as_bool());
				}, Type::T_BOOL };
			}
			return compileCmp(ctx->cmp_expr());
		}

		/**
		 * @brief 编译比较表达式
		 * @param ctx Cmp_exprContext 节点
		 * @return TypedExpr
		 * @details 无比较运算符时透传 add_expr
		 *          有比较运算符时左右类型必须相同
		 *          NUM 支持全部六种比较符，STR 和 BOOL 仅支持 == 和 !=
		 *          结果为 BOOL
		 */
		TypedExpr compileCmp(::PostAnvilParser::Cmp_exprContext* ctx) {
			auto add_exprs = ctx->add_expr();
			auto left = compileAdd(add_exprs[0]);

			if (add_exprs.size() > 1 && ctx->comp_op()) {
				std::string op = getCompOp(ctx->comp_op());
				auto right = compileAdd(add_exprs[1]);

				if (left.type != right.type) {
					throw CompileError("Comparison type mismatch: " +
						std::string(type_name(left.type)) + " vs " + std::string(type_name(right.type)));
				}

				if (left.type == Type::T_STR && op != "==" && op != "!=") {
					throw CompileError("Operator '" + op + "' not supported for STR");
				}
				if (left.type == Type::T_BOOL && op != "==" && op != "!=") {
					throw CompileError("Operator '" + op + "' not supported for BOOL");
				}

				Type ltype = left.type;
				return { [l = std::move(left.func), r = std::move(right.func), op = std::move(op), ltype]
					(const Instance& self, const Scene& scene) -> Val {
					if (ltype == Type::T_NUM) {
						double lv = l(self, scene).as_num();
						double rv = r(self, scene).as_num();
						if (op == ">")  return Val(lv > rv);
						if (op == "<")  return Val(lv < rv);
						if (op == ">=") return Val(lv >= rv);
						if (op == "<=") return Val(lv <= rv);
						if (op == "==") return Val(lv == rv);
						if (op == "!=") return Val(lv != rv);
					}
					else if (ltype == Type::T_STR) {
						std::string lv = l(self, scene).as_str();
						std::string rv = r(self, scene).as_str();
						if (op == "==") return Val(lv == rv);
						if (op == "!=") return Val(lv != rv);
					}
					else { // BOOL
						bool lv = l(self, scene).as_bool();
						bool rv = r(self, scene).as_bool();
						if (op == "==") return Val(lv == rv);
						if (op == "!=") return Val(lv != rv);
					}
					return Val(false);
				}, Type::T_BOOL };
			}
			return left;
		}

		/**
		 * @brief 编译加法表达式
		 * @param ctx Add_exprContext 节点
		 * @return TypedExpr
		 * @details + 支持 NUM+NUM 和 STR+STR 拼接
		 *          - 仅支持 NUM
		 *          左右操作数类型必须相同
		 */
		TypedExpr compileAdd(::PostAnvilParser::Add_exprContext* ctx) {
			auto mul_exprs = ctx->mul_expr();
			auto left = compileMul(mul_exprs[0]);

			auto add_ops = ctx->add_op();
			for (size_t i = 0; i < add_ops.size(); i++) {
				std::string op = getAddOp(add_ops[i]);
				auto right = compileMul(mul_exprs[i + 1]);

				if (op == "+") {
					if (left.type != right.type) {
						throw CompileError("Addition type mismatch: " +
							std::string(type_name(left.type)) + " + " + std::string(type_name(right.type)));
					}
					if (left.type == Type::T_BOOL) {
						throw CompileError("Addition not supported for BOOL");
					}

					if (left.type == Type::T_NUM) {
						left = { [l = std::move(left.func), r = std::move(right.func)]
							(const Instance& self, const Scene& scene) -> Val {
							return Val(l(self, scene).as_num() + r(self, scene).as_num());
						}, Type::T_NUM };
					}
					else { // STR 拼接
						left = { [l = std::move(left.func), r = std::move(right.func)]
							(const Instance& self, const Scene& scene) -> Val {
							return Val(l(self, scene).as_str() + r(self, scene).as_str());
						}, Type::T_STR };
					}
				}
				else { // '-'
					if (left.type != Type::T_NUM || right.type != Type::T_NUM) {
						throw CompileError("Subtraction requires NUM operands, got " +
							std::string(type_name(left.type)) + " and " + std::string(type_name(right.type)));
					}
					left = { [l = std::move(left.func), r = std::move(right.func)]
						(const Instance& self, const Scene& scene) -> Val {
						return Val(l(self, scene).as_num() - r(self, scene).as_num());
					}, Type::T_NUM };
				}
			}
			return left;
		}

		/**
		 * @brief 编译乘法表达式
		 * @param ctx Mul_exprContext 节点
		 * @return TypedExpr
		 * @details * 和 / 仅支持 NUM，结果为 NUM
		 *          除数为 0 时结果为 0
		 */
		TypedExpr compileMul(::PostAnvilParser::Mul_exprContext* ctx) {
			auto unary_exprs = ctx->unary_expr();
			auto left = compileUnary(unary_exprs[0]);

			auto mul_ops = ctx->mul_op();
			for (size_t i = 0; i < mul_ops.size(); i++) {
				std::string op = getMulOp(mul_ops[i]);
				auto right = compileUnary(unary_exprs[i + 1]);

				if (left.type != Type::T_NUM || right.type != Type::T_NUM) {
					throw CompileError("Arithmetic requires NUM operands, got " +
						std::string(type_name(left.type)) + " and " + std::string(type_name(right.type)));
				}

				left = { [l = std::move(left.func), r = std::move(right.func), op = std::move(op)]
					(const Instance& self, const Scene& scene) -> Val {
					double lv = l(self, scene).as_num();
					double rv = r(self, scene).as_num();
					if (op == "*") return Val(lv * rv);
					if (op == "/") return Val(rv != 0.0 ? lv / rv : 0.0);
					return Val(0.0);
				}, Type::T_NUM };
			}
			return left;
		}

		/**
		 * @brief 编译一元表达式
		 * @param ctx Unary_exprContext 节点
		 * @return TypedExpr
		 * @details 一元负号仅支持 NUM，结果 NUM
		 *          无负号时直接透传基本表达式
		 */
		TypedExpr compileUnary(::PostAnvilParser::Unary_exprContext* ctx) {
			if (ctx->MINUS()) {
				auto rhs = compileUnary(ctx->unary_expr());
				if (rhs.type != Type::T_NUM) {
					throw CompileError("Unary minus requires NUM operand, got " + std::string(type_name(rhs.type)));
				}
				return { [r = std::move(rhs.func)]
					(const Instance& self, const Scene& scene) -> Val {
					return Val(-r(self, scene).as_num());
				}, Type::T_NUM };
			}
			return compilePrimary(ctx->primary());
		}

		/**
		 * @brief 编译基本表达式
		 * @param ctx PrimaryContext 节点
		 * @return TypedExpr
		 * @details 处理字面量、变量引用、函数调用、属性访问、排序原语和括号表达式
		 */
		TypedExpr compilePrimary(::PostAnvilParser::PrimaryContext* ctx) {
			if (ctx->NUMBER()) {
				double v = std::stod(ctx->NUMBER()->getText());
				return { [v](const Instance&, const Scene&) { return Val(v); }, Type::T_NUM };
			}

			if (ctx->STRING()) {
				std::string s = utils::strip_quotes(ctx->STRING()->getText());
				return { [s](const Instance&, const Scene&) { return Val(s); }, Type::T_STR };
			}

			if (ctx->BOOL_LIT()) {
				std::string text = ctx->BOOL_LIT()->getText();
				utils::to_upper_inplace(text);
				bool v = (text == "TRUE");
				return { [v](const Instance&, const Scene&) { return Val(v); }, Type::T_BOOL };
			}

			if (ctx->IDENTIFIER()) {
				std::string var = ctx->IDENTIFIER()->getText();
				utils::to_upper_inplace(var);

				Type var_type = Type::T_NUM;
				if (global_types) {
					auto it = global_types->find(var);
					if (it != global_types->end()) {
						var_type = it->second;
					}
				}

				return { [var](const Instance&, const Scene& scene) -> Val {
				auto it = scene.variables.find(var);
				if (it == scene.variables.end()) {
					throw RuntimeError("Undefined variable '" + var + "'");
				}
				return it->second;
			}, var_type };
			}

			if (ctx->func_call()) {
				return compileFuncCall(ctx->func_call());
			}

			if (ctx->attribute()) {
				return compileAttribute(ctx->attribute());
			}

			if (ctx->sortExpr()) {
				return compileSortExpr(ctx->sortExpr());
			}

			if (ctx->LPAREN() && ctx->expr()) {
				return compile(ctx->expr());
			}

			return { [](const Instance&, const Scene&) { return Val(0.0); }, Type::T_NUM };
		}

		/**
		 * @brief 编译属性访问表达式
		 * @param ctx AttributeContext 节点
		 * @return TypedExpr
		 * @details 支持三种形式：
		 *          - self.属性：实例内置或动态属性
		 *          - "类别".属性：类别级属性（内置 COUNT 或自定义）
		 *          - 变量.属性：如 img.w / img.h
		 *          所有属性访问结果均为 NUM
		 */
		TypedExpr compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
			if (auto* inst = dynamic_cast<::PostAnvilParser::InstanceAttrContext*>(ctx)) {
				std::string prop = inst->IDENTIFIER()->getText();
				utils::to_upper_inplace(prop);
				return { [prop](const Instance& self, const Scene& scene) -> Val {
					return Val(get_instance_prop(self, scene, prop));
				}, Type::T_NUM };
			}

			if (auto* cls = dynamic_cast<::PostAnvilParser::ClassAttrContext*>(ctx)) {
				std::string cls_name = utils::strip_quotes(cls->STRING()->getText());
				utils::to_upper_inplace(cls_name);
				std::string prop = cls->IDENTIFIER()->getText();
				utils::to_upper_inplace(prop);

				return { [cls_name, prop](const Instance&, const Scene& scene) -> Val {
					return get_class_prop(scene, cls_name, prop);
				}, Type::T_NUM };
			}

			if (auto* var = dynamic_cast<::PostAnvilParser::VarInstanceAttrContext*>(ctx)) {
				auto identifiers = var->IDENTIFIER();
				if (identifiers.size() >= 2) {
					std::string object = identifiers[0]->getText();
					utils::to_upper_inplace(object);
					std::string prop = identifiers[1]->getText();
					utils::to_upper_inplace(prop);

					if (object == OBJECT_IMAGE) {
						return { [prop](const Instance&, const Scene& scene) -> Val {
							return Val(get_image_prop(scene.image, prop));
						}, Type::T_NUM };
					}

					// 循环变量属性暂未实现，返回占位
				}
				return { [](const Instance&, const Scene&) { return Val(0.0); }, Type::T_NUM };
			}

			return { [](const Instance&, const Scene&) { return Val(0.0); }, Type::T_NUM };
		}

		/**
		 * @brief 编译函数调用表达式
		 * @param ctx Func_callContext 节点
		 * @return TypedExpr
		 * @throws CompileError 函数未定义或参数类型不匹配时抛出
		 * @details 当前仅支持 NUM 类型参数，返回 NUM
		 */
		TypedExpr compileFuncCall(::PostAnvilParser::Func_callContext* ctx) {
			std::string name = ctx->IDENTIFIER()->getText();
			utils::to_upper_inplace(name);

			if (!functions) {
				throw CompileError("Function registry not available when compiling '" + name + "'");
			}
			auto func_it = functions->find(name);
			if (func_it == functions->end()) {
				throw CompileError("Function '" + name + "' not found");
			}
			CompiledFunc func_body = func_it->second;

			std::vector<NumFunc> args;
			for (auto* arg : ctx->expr()) {
				auto typed = compile(arg);
				if (typed.type != Type::T_NUM) {
					throw CompileError("Function argument must be NUM, got " + std::string(type_name(typed.type)));
				}
				auto func = typed.func;
				args.push_back([func](const Instance& self, const Scene& scene) -> double {
					return func(self, scene).as_num();
					});
			}

			return { [name, args, func_body](const Instance& self, const Scene& scene) -> Val {
				std::vector<double> arg_vals;
				for (auto& arg : args) {
					arg_vals.push_back(arg(self, scene));
				}
				Scene temp_scene(scene.image);
				EvaluationContext temp_ctx(temp_scene);
				return Val(func_body(arg_vals, temp_ctx));
			}, Type::T_NUM };
		}

		/**
		 * @brief 编译排序原语 SORT
		 * @param ctx SortExprContext 节点
		 * @return TypedExpr
		 * @details 形式：SORT(类别, 排序键, 名次)
		 *          名次为正数表示降序第 N 名，负数表示升序第 |N| 名
		 *          返回对应名次的键值，结果为 NUM
		 */
		TypedExpr compileSortExpr(::PostAnvilParser::SortExprContext* ctx) {
			std::string cls_name;
			auto* class_ctx = ctx->class_expr();
			if (class_ctx) {
				if (class_ctx->STRING()) {
					cls_name = utils::strip_quotes(class_ctx->STRING()->getText());
				}
				else if (class_ctx->IDENTIFIER()) {
					cls_name = class_ctx->IDENTIFIER()->getText();
				}
				utils::to_upper_inplace(cls_name);
			}

			auto key_expr = compileAsNum(ctx->expr(0));
			auto rank_expr = compileAsNum(ctx->expr(1));

			return { [cls_name, key_expr, rank_expr](const Instance& self, const Scene& scene) -> Val {
				double rank_val = rank_expr(self, scene);
				int rank = static_cast<int>(rank_val);

				auto it = scene.objects.find(cls_name);
				if (it == scene.objects.end() || it->second.empty()) return Val(0.0);

				std::vector<double> keys;
				for (const auto& inst : it->second) {
					keys.push_back(key_expr(inst, scene));
				}

				int idx = std::abs(rank) - 1;
				if (rank < 0) {
					std::sort(keys.begin(), keys.end());
				}
				else {
					std::sort(keys.begin(), keys.end(), std::greater<double>());
				}

				if (idx >= 0 && idx < static_cast<int>(keys.size())) {
					return Val(keys[idx]);
				}
				return Val(0.0);
			}, Type::T_NUM };
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
			return "";
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