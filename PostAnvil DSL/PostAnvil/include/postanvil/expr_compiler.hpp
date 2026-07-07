/**
 * @file   expr_compiler.hpp
 * @brief  PostAnvil 表达式编译器 —— 递归遍历 ANTLR4 ParseTree，编译为 NumFunc
 * @detail TreeExprCompiler 接收 ANTLR4 解析产生的表达式 ParseTree 节点，
 *         通过递归遍历将表达式编译为可执行的 NumFunc 闭包。
 *         支持的表达式层级：expr → or/and/not/cmp/add/mul/unary → primary
 *         不使用中间 AST，直接从 ParseTree 编译为闭包。
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

namespace postanvil {

// ====================== TreeExprCompiler =========================

/**
 * @brief 表达式编译器 —— 递归遍历 ANTLR4 ParseTree，直接编译为 NumFunc
 *
 * TreeExprCompiler 接收 ANTLR4 解析产生的表达式 ParseTree 节点，
 * 通过递归遍历将表达式编译为可执行的 NumFunc 闭包。
 *
 * 支持的表达式层级：
 *   expr → or_expr → and_expr → not_expr → cmp_expr → add_expr → mul_expr
 *        → unary_expr → primary
 */
class TreeExprCompiler {
public:
	static const inline char* OBJECT_SELF = "SELF";
	static const inline char* OBJECT_IMAGE = "IMG";

	/**
	 * @brief 函数注册表指针，由编译器在编译前设置
	 */
	std::unordered_map<std::string, CompiledFunc>* functions = nullptr;

	TreeExprCompiler() = default;

	/**
	 * @brief 编译表达式入口（ExprContext）
	 * @param ctx - ANTLR4 表达式 ParseTree 节点
	 * @return NumFunc - 编译后的数值计算函数
	 */
	NumFunc compile(::PostAnvilParser::ExprContext* ctx) {
		if (!ctx || !ctx->or_expr()) {
			return [](const Instance&, const Scene&) { return 0.0; };
		}
		return compileOr(ctx->or_expr());
	}

	/**
	 * @brief 编译或表达式入口（Or_exprContext）
	 * @param ctx - ANTLR4 or_expr ParseTree 节点
	 * @return NumFunc - 编译后的数值计算函数
	 */
	NumFunc compile(::PostAnvilParser::Or_exprContext* ctx) {
		if (!ctx) {
			return [](const Instance&, const Scene&) { return 0.0; };
		}
		return compileOr(ctx);
	}

private:
	// ======================== 递归编译方法 ============================

	/**
	 * @brief 编译逻辑或表达式：and_expr (OR and_expr)*
	 */
	NumFunc compileOr(::PostAnvilParser::Or_exprContext* ctx) {
		auto and_exprs = ctx->and_expr();
		auto left = compileAnd(and_exprs[0]);

		size_t or_count = ctx->OR().size();
		for (size_t i = 0; i < or_count; i++) {
			auto right = compileAnd(and_exprs[i + 1]);
			left = [l = std::move(left), r = std::move(right)]
				(const Instance& self, const Scene& scene) -> double {
				return ((l(self, scene) != 0.0) || (r(self, scene) != 0.0)) ? 1.0 : 0.0;
			};
		}
		return left;
	}

	/**
	 * @brief 编译逻辑与表达式：not_expr (AND not_expr)*
	 */
	NumFunc compileAnd(::PostAnvilParser::And_exprContext* ctx) {
		auto not_exprs = ctx->not_expr();
		auto left = compileNot(not_exprs[0]);

		size_t and_count = ctx->AND().size();
		for (size_t i = 0; i < and_count; i++) {
			auto right = compileNot(not_exprs[i + 1]);
			left = [l = std::move(left), r = std::move(right)]
				(const Instance& self, const Scene& scene) -> double {
				return ((l(self, scene) != 0.0) && (r(self, scene) != 0.0)) ? 1.0 : 0.0;
			};
		}
		return left;
	}

	/**
	 * @brief 编译逻辑非表达式：NOT not_expr | cmp_expr
	 */
	NumFunc compileNot(::PostAnvilParser::Not_exprContext* ctx) {
		if (ctx->NOT()) {
			auto rhs = compileNot(ctx->not_expr());
			return [r = std::move(rhs)]
				(const Instance& self, const Scene& scene) -> double {
				return r(self, scene) == 0.0 ? 1.0 : 0.0;
			};
		}
		return compileCmp(ctx->cmp_expr());
	}

	/**
	 * @brief 编译比较表达式：add_expr (comp_op add_expr)?
	 */
	NumFunc compileCmp(::PostAnvilParser::Cmp_exprContext* ctx) {
		auto add_exprs = ctx->add_expr();
		auto left = compileAdd(add_exprs[0]);

		if (add_exprs.size() > 1 && ctx->comp_op()) {
			std::string op = getCompOp(ctx->comp_op());
			auto right = compileAdd(add_exprs[1]);
			return [l = std::move(left), r = std::move(right), op = std::move(op)]
				(const Instance& self, const Scene& scene) {
				double lv = l(self, scene);
				double rv = r(self, scene);
				if (op == ">")   return lv >  rv ? 1.0 : 0.0;
				if (op == "<")   return lv <  rv ? 1.0 : 0.0;
				if (op == ">=")  return lv >= rv ? 1.0 : 0.0;
				if (op == "<=")  return lv <= rv ? 1.0 : 0.0;
				if (op == "==")  return lv == rv ? 1.0 : 0.0;
				if (op == "!=")  return lv != rv ? 1.0 : 0.0;
				return 0.0;
			};
		}
		return left;
	}

	/**
	 * @brief 编译加法表达式：mul_expr (add_op mul_expr)*
	 */
	NumFunc compileAdd(::PostAnvilParser::Add_exprContext* ctx) {
		auto mul_exprs = ctx->mul_expr();
		auto left = compileMul(mul_exprs[0]);

		auto add_ops = ctx->add_op();
		for (size_t i = 0; i < add_ops.size(); i++) {
			std::string op = getAddOp(add_ops[i]);
			auto right = compileMul(mul_exprs[i + 1]);
			left = [l = std::move(left), r = std::move(right), op = std::move(op)]
				(const Instance& self, const Scene& scene) {
				double lv = l(self, scene);
				double rv = r(self, scene);
				if (op == "+") return lv + rv;
				if (op == "-") return lv - rv;
				return 0.0;
			};
		}
		return left;
	}

	/**
	 * @brief 编译乘法表达式：unary_expr (mul_op unary_expr)*
	 */
	NumFunc compileMul(::PostAnvilParser::Mul_exprContext* ctx) {
		auto unary_exprs = ctx->unary_expr();
		auto left = compileUnary(unary_exprs[0]);

		auto mul_ops = ctx->mul_op();
		for (size_t i = 0; i < mul_ops.size(); i++) {
			std::string op = getMulOp(mul_ops[i]);
			auto right = compileUnary(unary_exprs[i + 1]);
			left = [l = std::move(left), r = std::move(right), op = std::move(op)]
				(const Instance& self, const Scene& scene) {
				double lv = l(self, scene);
				double rv = r(self, scene);
				if (op == "*") return lv * rv;
				if (op == "/") return rv != 0.0 ? lv / rv : 0.0;
				return 0.0;
			};
		}
		return left;
	}

	/**
	 * @brief 编译一元表达式：MINUS unary_expr | primary
	 */
	NumFunc compileUnary(::PostAnvilParser::Unary_exprContext* ctx) {
		if (ctx->MINUS()) {
			auto rhs = compileUnary(ctx->unary_expr());
			return [r = std::move(rhs)]
				(const Instance& self, const Scene& scene) -> double {
				return -r(self, scene);
			};
		}
		return compilePrimary(ctx->primary());
	}

	/**
	 * @brief 编译基本表达式：NUMBER | STRING | BOOL_LIT | func_call | attribute | sortExpr | '(' expr ')'
	 */
	NumFunc compilePrimary(::PostAnvilParser::PrimaryContext* ctx) {
		// 数字字面量
		if (ctx->NUMBER()) {
			double v = std::stod(ctx->NUMBER()->getText());
			return [v](const Instance&, const Scene&) { return v; };
		}

		// 字符串字面量（返回 0.0，在数值上下文中无意义）
		if (ctx->STRING()) {
			return [](const Instance&, const Scene&) { return 0.0; };
		}

		// 布尔字面量：TRUE = 1.0, FALSE = 0.0
		if (ctx->BOOL_LIT()) {
			std::string text = ctx->BOOL_LIT()->getText();
			utils::to_upper_inplace(text);
			double v = (text == "TRUE") ? 1.0 : 0.0;
			return [v](const Instance&, const Scene&) { return v; };
		}

		// 函数调用（Phase 4 完整实现）
		if (ctx->func_call()) {
			return compileFuncCall(ctx->func_call());
		}

		// 属性访问
		if (ctx->attribute()) {
			return compileAttribute(ctx->attribute());
		}

		// 排序原语（Phase 4 完整实现）
		if (ctx->sortExpr()) {
			return compileSortExpr(ctx->sortExpr());
		}

		// 括号表达式
		if (ctx->LPAREN() && ctx->expr()) {
			return compile(ctx->expr());
		}

		return [](const Instance&, const Scene&) { return 0.0; };
	}

	/**
	 * @brief 编译属性访问表达式
	 *
	 * 支持三种形式：
	 * - InstanceAttr:  SELF '.' IDENTIFIER     → self.x1, self.conf
	 * - ClassAttr:     STRING '.' IDENTIFIER   → "person".count
	 * - VarInstanceAttr: IDENTIFIER '.' IDENTIFIER → 循环变量.属性 (Phase 4)
	 */
	NumFunc compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
		// InstanceAttr: SELF '.' IDENTIFIER
		if (auto* inst = dynamic_cast<::PostAnvilParser::InstanceAttrContext*>(ctx)) {
			std::string prop = inst->IDENTIFIER()->getText();
			utils::to_upper_inplace(prop);
			return [prop](const Instance& self, const Scene& scene) -> double {
				return get_instance_prop(self, scene, prop);
			};
		}

		// ClassAttr: STRING '.' IDENTIFIER
		if (auto* cls = dynamic_cast<::PostAnvilParser::ClassAttrContext*>(ctx)) {
			std::string cls_name = utils::strip_quotes(cls->STRING()->getText());
			utils::to_upper_inplace(cls_name);
			std::string prop = cls->IDENTIFIER()->getText();
			utils::to_upper_inplace(prop);

			return [cls_name, prop](const Instance&, const Scene& scene) -> double {
				return get_class_prop(scene, cls_name, prop);
			};
		}

		// VarInstanceAttr: IDENTIFIER '.' IDENTIFIER
		// 支持 img.w/img.h 和循环变量属性（Phase 4）
		if (auto* var = dynamic_cast<::PostAnvilParser::VarInstanceAttrContext*>(ctx)) {
			auto identifiers = var->IDENTIFIER();
			if (identifiers.size() >= 2) {
				std::string object = identifiers[0]->getText();
				utils::to_upper_inplace(object);
				std::string prop = identifiers[1]->getText();
				utils::to_upper_inplace(prop);

				// img.w / img.h 图像属性
				if (object == OBJECT_IMAGE) {
					return [prop](const Instance&, const Scene& scene) -> double {
						return get_image_prop(scene.image, prop);
					};
				}

				// 循环变量属性（Phase 4 实现）
				// 当前返回 0.0 作为占位
			}
			return [](const Instance&, const Scene&) { return 0.0; };
		}

		return [](const Instance&, const Scene&) { return 0.0; };
	}

	/**
	 * @brief 编译函数调用表达式
	 */
	NumFunc compileFuncCall(::PostAnvilParser::Func_callContext* ctx) {
		std::string name = ctx->IDENTIFIER()->getText();
		utils::to_upper_inplace(name);

		// 编译参数
		std::vector<NumFunc> args;
		for (auto* arg : ctx->expr()) {
			args.push_back(compile(arg));
		}

		return [name, args, this](const Instance& self, const Scene& scene) -> double {
			if (!functions) {
				throw RuntimeError("Function registry not available when calling '" + name + "'");
			}
			auto it = functions->find(name);
			if (it == functions->end()) {
				throw RuntimeError("Function '" + name + "' not found");
			}

			// 计算参数值
			std::vector<double> arg_vals;
			for (auto& arg : args) {
				arg_vals.push_back(arg(self, scene));
			}

			// 创建临时 EvaluationContext 调用函数
			Scene temp_scene(scene.image);
			EvaluationContext temp_ctx(temp_scene);
			temp_ctx.functions = *functions;
			return it->second(arg_vals, temp_ctx);
		};
	}

	/**
	 * @brief 编译排序原语表达式
	 *
	 * SORT(class_expr, sort_key, rank)
	 * - rank > 0: 降序第 N 名（1-based）
	 * - rank < 0: 升序第 |N| 名
	 */
	NumFunc compileSortExpr(::PostAnvilParser::SortExprContext* ctx) {
		// 解析类别名
		std::string cls_name;
		auto* class_ctx = ctx->class_expr();
		if (class_ctx) {
			if (class_ctx->STRING()) {
				cls_name = utils::strip_quotes(class_ctx->STRING()->getText());
			} else if (class_ctx->IDENTIFIER()) {
				cls_name = class_ctx->IDENTIFIER()->getText();
			}
			utils::to_upper_inplace(cls_name);
		}

		auto key_expr = compile(ctx->expr(0));  // 排序键
		auto rank_expr = compile(ctx->expr(1)); // 名次

		return [cls_name, key_expr, rank_expr](const Instance& self, const Scene& scene) -> double {
			double rank_val = rank_expr(self, scene);
			int rank = static_cast<int>(rank_val);

			auto it = scene.objects.find(cls_name);
			if (it == scene.objects.end() || it->second.empty()) return 0.0;

			// 收集所有键值
			std::vector<double> keys;
			for (const auto& inst : it->second) {
				keys.push_back(key_expr(inst, scene));
			}

			int idx = std::abs(rank) - 1;
			if (rank < 0) {
				// 负排名 = 升序
				std::sort(keys.begin(), keys.end());
			} else {
				// 正排名 = 降序
				std::sort(keys.begin(), keys.end(), std::greater<double>());
			}

			if (idx >= 0 && idx < static_cast<int>(keys.size())) {
				return keys[idx];
			}
			return 0.0;
		};
	}

	// ======================== 操作符提取 ============================

	/**
	 * @brief 从 Comp_opContext 提取比较操作符字符串
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
	 * @brief 从 Add_opContext 提取加减操作符字符串
	 */
	static std::string getAddOp(::PostAnvilParser::Add_opContext* ctx) {
		if (ctx->PLUS())  return "+";
		if (ctx->MINUS()) return "-";
		return "";
	}

	/**
	 * @brief 从 Mul_opContext 提取乘除操作符字符串
	 */
	static std::string getMulOp(::PostAnvilParser::Mul_opContext* ctx) {
		if (ctx->STAR())  return "*";
		if (ctx->SLASH()) return "/";
		return "";
	}
};

} // namespace postanvil