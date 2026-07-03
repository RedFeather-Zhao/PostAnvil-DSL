/**
 * @file   expr_compiler.hpp
 * @brief  PostAnvil 表达式编译器 —— 递归遍历 ANTLR4 ParseTree，编译为 NumFunc
 * @detail TreeExprCompiler 接收 ANTLR4 解析产生的表达式 ParseTree 节点，
 *         通过递归遍历将表达式编译为可执行的 NumFunc 闭包。
 *         支持的表达式层级：expr → or/and/not/cmp/add/mul/unary → primary
 *         不使用中间 AST，直接从 ParseTree 编译为闭包。
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "antlr4-runtime.h"
#include "PostAnvilParser.h"
#include <functional>
#include <string>
#include <cmath>

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
	TreeExprCompiler() = default;

	/**
	 * @brief 编译表达式入口
	 * @param ctx - ANTLR4 表达式 ParseTree 节点
	 * @return NumFunc - 编译后的数值计算函数
	 */
	NumFunc compile(::PostAnvilParser::ExprContext* ctx) {
		if (!ctx || !ctx->or_expr()) {
			return [](const Instance&, const Scene&, const Image&) { return 0.0; };
		}
		return compileOr(ctx->or_expr());
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				return ((l(self, scene, img) != 0.0) || (r(self, scene, img) != 0.0)) ? 1.0 : 0.0;
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				return ((l(self, scene, img) != 0.0) && (r(self, scene, img) != 0.0)) ? 1.0 : 0.0;
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				return r(self, scene, img) == 0.0 ? 1.0 : 0.0;
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				double lv = l(self, scene, img);
				double rv = r(self, scene, img);
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				double lv = l(self, scene, img);
				double rv = r(self, scene, img);
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				double lv = l(self, scene, img);
				double rv = r(self, scene, img);
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
				(const Instance& self, const Scene& scene, const Image& img) -> double {
				return -r(self, scene, img);
			};
		}
		return compilePrimary(ctx->primary());
	}

	/**
	 * @brief 编译基本表达式：NUMBER | attribute | '(' expr ')'
	 */
	NumFunc compilePrimary(::PostAnvilParser::PrimaryContext* ctx) {
		// 数字字面量
		if (ctx->NUMBER()) {
			double v = std::stod(ctx->NUMBER()->getText());
			return [v](const Instance&, const Scene&, const Image&) { return v; };
		}

		// 属性访问
		if (ctx->attribute()) {
			return compileAttribute(ctx->attribute());
		}

		// 括号表达式
		if (ctx->LPAREN() && ctx->expr()) {
			return compile(ctx->expr());
		}

		return [](const Instance&, const Scene&, const Image&) { return 0.0; };
	}

	/**
	 * @brief 编译属性访问表达式：(SELF | IDENTIFIER) ('.' IDENTIFIER)*
	 *
	 * 支持 self.x1, self.conf, image.w, image.h 等属性访问。
	 * 对象名和属性名在编译时转为大写，确保与内部存储一致。
	 */
	NumFunc compileAttribute(::PostAnvilParser::AttributeContext* ctx) {
		std::string object;
		size_t prop_start_idx = 0;

		if (ctx->SELF()) {
			object = "SELF";
			// 第一个 IDENTIFIER 是属性名
		} else {
			object = ctx->IDENTIFIER(0)->getText();
			prop_start_idx = 1;
		}

		// 转大写
		to_upper_inplace(object);

		// 获取属性名（取最后一个 IDENTIFIER，支持链式访问）
		auto identifiers = ctx->IDENTIFIER();
		std::string prop;
		if (identifiers.size() > prop_start_idx) {
			prop = identifiers[identifiers.size() - 1]->getText();
			to_upper_inplace(prop);
		}

		return [object, prop](const Instance& self, const Scene&, const Image& img) -> double {
			if (object == "SELF") {
				return get_instance_prop(self, prop);
			}
			if (object == "IMAGE") {
				return get_image_prop(img, prop);
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