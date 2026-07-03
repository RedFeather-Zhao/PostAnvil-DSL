/**
 * @file   compiler.hpp
 * @brief  PostAnvil DSL 编译器 —— 基于 ANTLR4 ParseTree 的规则编译
 * @detail 本文件实现了 PostAnvil 的编译型评估架构，核心设计为"算子管道"模式：
 *
 * 编译流程（基于 ANTLR4 Listener）：
 *         PostAnvilCompiler 使用 ANTLR4 生成的 Lexer/Parser 将 DSL 源文本解析为
 *         ParseTree，然后通过 Listener 模式遍历 ParseTree，直接编译为算子管道。
 *         表达式部分使用 TreeExprCompiler 递归遍历 ParseTree 节点，生成闭包。
 *
 * 执行流程（Evaluate）：
 *         CompiledProgram 持有算子序列，对输入场景依次执行每个算子的 apply()，
 *         最终输出 EvalResult
 *
 * 算子类型（Operator）：
 *         1. OP_FILTER：按条件过滤实例，保留满足条件的实例
 *         2. OP_ATTRIBUTE：为类别每个实例添加计算属性
 *
 * 支持的表达式类型：
 * - 数值常量、属性访问（self.* / image.*）
 * - 比较运算（< > <= >= == !=）
 * - 算术运算（+ - * /）
 * - 逻辑运算（AND / OR / NOT）
 *
 * 注意：ANTLR4 语法使用 caseInsensitive = true 选项，标识符的原始大小写保留在
 * token 文本中。编译器在内部统一转换为大写进行比较。
 *
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/context.hpp"
#include "antlr4-runtime.h"
#include "PostAnvilLexer.h"
#include "PostAnvilParser.h"
#include "PostAnvilBaseListener.h"
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <format>
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
	auto it = inst.props.find(std::string(prop));
	if (it != inst.props.end()) {
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

// ========================== Eval Struct ============================

/**
 * @brief 评估结果，包含每个类别中保留的实例列表
 */
struct EvalResult {
	Scene kept;		//< 评估保留的场景，保留按类别组织的实例映射

public:
	explicit EvalResult(Scene scene = {})
		: kept(std::move(scene))
	{
	}

	EvalResult(EvalResult&&) noexcept = default;

	EvalResult& operator=(EvalResult&&) noexcept = default;
};

/**
 * @brief 评估上下文，在算子管道中传递的可变状态
 *
 * EvaluationContext 是算子间共享数据的载体。每个算子通过 apply() 方法
 * 读取并修改上下文，实现管道式的数据变换。
 *
 * 当前包含：
 * - scene：可变场景（算子逐步变换，如过滤、新增类别等）
 * - image：图像元信息（只读）
 */
struct EvaluationContext {
	Scene scene;		//< 可变场景，算子可修改
	const Image& image;	//< 图像信息，算子可读取但不可修改

	/**
	 * @brief 构造评估上下文
	 * @param s   - 初始输入场景
	 * @param img - 图像信息
	 */
	EvaluationContext(const Scene& s, const Image& img)
		: scene(s), image(img)
	{
	}

	/**
	 * @brief 将当前上下文转换为评估结果
	 * @return 包含当前场景的评估结果
	 */
	EvalResult to_result() const {
		EvalResult res;
		res.kept = scene;
		return res;
	}
};

// ========================= Operator ============================

/**
 * @brief 算子类型枚举
 */
enum class OperatorKind {
	OP_BASE,           //< 基类（抽象）
	OP_FILTER,         //< 过滤算子：按条件保留/丢弃实例
	OP_ATTRIBUTE,      //< 属性算子：为实例添加计算字段
};

/**
 * @brief 算子基类 —— 管道中所有变换单元的抽象
 *
 * 每个算子代表管道中的一个变换步骤，接收 EvaluationContext 并对其执行变换。
 * 派生类通过重写 apply() 实现具体的变换逻辑。
 */
struct SceneOperator {
	OperatorKind kind = OperatorKind::OP_BASE;	//< 算子类型
	std::string target;							//< 目标类别名称

public:
	explicit SceneOperator(OperatorKind kind_ = OperatorKind::OP_BASE) : kind(kind_)
	{
	}

	virtual ~SceneOperator() = default;

	/**
	 * @brief 对评估上下文执行变换
	 * @param ctx - 评估上下文
	 */
	virtual void apply(EvaluationContext& ctx) const = 0;
};

/**
 * @brief 过滤算子 —— 按条件筛选实例
 *
 * 对目标类别（或全局）的每个实例执行过滤条件链，仅保留满足所有条件的实例。
 * 过滤条件由 TreeExprCompiler 编译表达式为 FilterFunc 闭包链。
 *
 * 使用示例（DSL）：
 * @code
 *   RULE FILTER GLOBAL:
 *       SELF.CONF > 0.5
 *   RULEEND
 * @endcode
 */
struct FilterOperator : SceneOperator {

	std::vector<FilterFunc> conditions;		//< 过滤条件链，按顺序执行，AND 关系

public:
	FilterOperator() : SceneOperator(OperatorKind::OP_FILTER)
	{
	}

	/**
	 * @brief 执行过滤变换
	 *
	 * 遍历目标类别的所有实例，保留满足所有条件的实例。
	 * 若 target == "GLOBAL"，则对所有类别生效。
	 *
	 * @param ctx 评估上下文
	 */
	void apply(EvaluationContext& ctx) const override
	{
		// 单实例合法性校验：所有条件均满足则返回 true
		auto is_valid = [&](const auto& inst) {
			return std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx.scene, ctx.image);
			});
		};

		// 容器过滤：原地删除不合法的实例
		auto filterInstances = [&](Instances& instances) {
			std::erase_if(instances, [&](const auto& inst) {
				return !is_valid(inst);
			});
		};

		if (target == "GLOBAL") {
			for (auto& [name, instances] : ctx.scene) {
				filterInstances(instances);
			}
			return;
		}

		auto it = ctx.scene.find(target);
		if (it != ctx.scene.end()) {
			filterInstances(it->second);
		}
	}
};

/**
 * @brief 属性算子 —— 为实例添加计算字段
 *
 * 对目标类别的每个实例，计算并存储自定义属性值。
 * 计算后的属性存储在 Instance::props 中，后续过滤算子可通过属性访问引用。
 *
 * 使用示例（DSL）：
 * @code
 *   RULE ATTR PERSON:
 *       RISK = SELF.CONF * 2.0
 *       SIZE = SELF.W * SELF.H
 *   RULEEND
 * @endcode
 */
struct AttributeOperator : SceneOperator {

	/**
	 * @brief 单个属性定义：属性名 + 编译后的值表达式
	 */
	struct AttrDef {
		std::string name;			//< 属性名（大写）
		NumFunc expression;			//< 编译后的数值计算函数
	};

	std::vector<AttrDef> attr_defs;		//< 属性定义列表

	AttributeOperator() : SceneOperator(OperatorKind::OP_ATTRIBUTE)
	{
	}

	/**
	 * @brief 执行属性计算变换
	 *
	 * 遍历目标类别的所有实例，为每个实例计算并存储属性值。
	 * 若 target == "GLOBAL"，则对所有类别生效。
	 *
	 * @param ctx 评估上下文
	 */
	void apply(EvaluationContext& ctx) const override
	{
		auto compute_attrs = [&](Instances& instances) {
			for (auto& inst : instances) {
				for (const auto& def : attr_defs) {
					inst.props[def.name] = def.expression(inst, ctx.scene, ctx.image);
				}
			}
		};

		if (target == "GLOBAL") {
			for (auto& [name, instances] : ctx.scene) {
				compute_attrs(instances);
			}
			return;
		}

		auto it = ctx.scene.find(target);
		if (it != ctx.scene.end()) {
			compute_attrs(it->second);
		}
	}
};

// ========================== Program ===========================

/**
 * @brief 编译后的场景规则程序（CompiledProgram）
 *
 * CompiledProgram 是 PostAnvilCompiler 的编译产物，内部持有
 * 一系列算子（SceneOperator），按序对输入场景执行变换。
 *
 * 它可以安全地移動、存储，并反复对不同的场景数据执行相同评估。
 *
 * 使用方式：
 * @code
 *   PostAnvilCompiler compiler;
 *   CompiledProgram program = compiler.compile(source);
 *   EvalResult result = program.evaluate(scene, image);
 * @endcode
 */
class CompiledProgram {
public:
	CompiledProgram() = default;
	CompiledProgram(const CompiledProgram&)				= delete;
	CompiledProgram(CompiledProgram&&)					= default;
	CompiledProgram& operator=(const CompiledProgram&)	= delete;
	CompiledProgram& operator=(CompiledProgram&&)		= default;

	/**
	 * @brief 对场景执行所有算子，返回最终结果
	 *
	 * 执行流程：
	 * 1. 拷贝输入场景，构造 EvaluationContext
	 * 2. 按序执行每个算子的 apply() 方法
	 * 3. 将最终上下文转换为 EvalResult 返回
	 *
	 * @param scene 输入场景数据
	 * @param image 图像尺寸信息
	 * @return 评估结果
	 */
	EvalResult evaluate(const Scene& scene, const Image& image) const {
		EvaluationContext ctx(scene, image);

		for (const auto& op : operators) {
			op->apply(ctx);
		}

		return ctx.to_result();
	}

	/**
	 * @brief 算子序列（按执行顺序排列）
	 */
	std::vector<std::unique_ptr<SceneOperator>> operators;
};

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
 *
 * 不使用中间 AST，直接从 ParseTree 编译为闭包。
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

// ====================== ANTLR4 Error Listener ======================

/**
 * @brief 自定义 ANTLR4 错误监听器，收集语法错误信息
 */
struct PostAnvilErrorListener : public antlr4::BaseErrorListener {
	struct Error {
		int line;
		int col;
		std::string message;
	};

	std::vector<Error> errors;

	void syntaxError(antlr4::Recognizer* /*recognizer*/, antlr4::Token* /*offendingSymbol*/,
	                 size_t line, size_t charPositionInLine,
	                 const std::string& msg, std::exception_ptr /*e*/) override {
		errors.push_back({static_cast<int>(line), static_cast<int>(charPositionInLine), msg});
	}

	bool hasErrors() const { return !errors.empty(); }
};

// ====================== PostAnvilCompiler =========================

/**
 * @brief PostAnvil DSL 编译器 —— 基于 ANTLR4 Listener
 *
 * PostAnvilCompiler 是 PostAnvil 的主编译器。它使用 ANTLR4 生成的
 * Lexer/Parser 将 DSL 源文本解析为 ParseTree，然后通过 Listener 模式
 * 遍历 ParseTree，直接编译为 CompiledProgram（算子管道）。
 *
 * 架构设计：
 * - 顶层结构（program/rule/statement）→ 使用 Listener 回调处理
 * - 表达式编译 → 使用 TreeExprCompiler 递归遍历 ParseTree
 *
 * 使用方式：
 * @code
 *   PostAnvilCompiler compiler;
 *   CompiledProgram program = compiler.compile(source);
 *   EvalResult result = program.evaluate(scene, image);
 * @endcode
 */
class PostAnvilCompiler : public ::PostAnvilBaseListener {
public:
	PostAnvilCompiler() = default;

	/**
	 * @brief 编译 DSL 源文本，返回可复用的 CompiledProgram
	 *
	 * 编译流程：
	 * 1. 创建 ANTLR4 输入流、词法分析器、token 流、语法分析器
	 * 2. 安装自定义错误监听器
	 * 3. 解析为 ParseTree
	 * 4. 使用 Listener 遍历 ParseTree，构建算子管道
	 * 5. 返回 CompiledProgram
	 *
	 * @param source - DSL 源文本
	 * @return CompiledProgram - 编译后的算子管道
	 * @throws CompileError - 语法错误或编译错误时抛出
	 */
	CompiledProgram compile(const std::string& source) {
		// 重置状态
		m_program = CompiledProgram();
		m_current_filter.reset();
		m_current_attr.reset();
		m_current_kind = RuleKind::FILTER;

		// 创建 ANTLR4 组件
		antlr4::ANTLRInputStream input(source);
		::PostAnvilLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		::PostAnvilParser parser(&tokens);

		// 安装自定义错误监听器
		lexer.removeErrorListeners();
		parser.removeErrorListeners();

		PostAnvilErrorListener error_listener;
		lexer.addErrorListener(&error_listener);
		parser.addErrorListener(&error_listener);

		// 解析
		::PostAnvilParser::ProgramContext* tree = parser.program();

		// 检查语法错误
		if (error_listener.hasErrors()) {
			const auto& err = error_listener.errors[0];
			throw CompileError(err.message, err.line, err.col);
		}

		// 使用 Listener 遍历 ParseTree，构建算子管道
		antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, tree);
		
		return std::move(m_program);
	}

	// ======================== Listener 回调 ============================

	/**
	 * @brief 进入规则节点：识别规则类型（FILTER/ATTR）和目标，创建对应算子
	 */
	void enterRuledef(::PostAnvilParser::RuledefContext* ctx) override {
		// 获取目标类别名
		m_current_target = ctx->target->getText();
		to_upper_inplace(m_current_target);

		if (ctx->FILTER()) {
			m_current_kind = RuleKind::FILTER;
			m_current_filter = std::make_unique<FilterOperator>();
			m_current_filter->target = m_current_target;
		} else if (ctx->ATTR()) {
			m_current_kind = RuleKind::ATTR;
			m_current_attr = std::make_unique<AttributeOperator>();
			m_current_attr->target = m_current_target;
		}
	}

	/**
	 * @brief 退出规则节点：将当前算子加入 CompiledProgram
	 */
	void exitRuledef(::PostAnvilParser::RuledefContext* /*ctx*/) override {
		if (m_current_kind == RuleKind::FILTER && m_current_filter) {
			m_program.operators.push_back(std::move(m_current_filter));
		} else if (m_current_kind == RuleKind::ATTR && m_current_attr) {
			m_program.operators.push_back(std::move(m_current_attr));
		}
	}

	/**
	 * @brief 进入表达式语句：编译过滤条件表达式，添加到 FilterOperator
	 */
	void enterExprStmt(::PostAnvilParser::ExprStmtContext* ctx) override {
		if (!m_current_filter) return;

		auto numFunc = m_expr_compiler.compile(ctx->expr());
		m_current_filter->conditions.push_back(
			[numFunc](const Instance& self, const Scene& scene, const Image& img) {
				return numFunc(self, scene, img) != 0.0;
			}
		);
	}

	/**
	 * @brief 进入赋值语句：编译属性赋值表达式，添加到 AttributeOperator
	 */
	void enterAssignStmt(::PostAnvilParser::AssignStmtContext* ctx) override {
		if (!m_current_attr) return;

		auto* attr_assign = ctx->attr_assign();
		if (!attr_assign) return;

		// 获取属性名并转大写
		std::string attr_name = attr_assign->attr_name->getText();
		to_upper_inplace(attr_name);

		// 编译属性值表达式
		auto numFunc = m_expr_compiler.compile(attr_assign->expr());

		m_current_attr->attr_defs.push_back({std::move(attr_name), std::move(numFunc)});
	}

private:
	CompiledProgram m_program;                          //< 编译结果
	std::unique_ptr<FilterOperator> m_current_filter;    //< 当前正在编译的 FILTER 算子
	std::unique_ptr<AttributeOperator> m_current_attr;   //< 当前正在编译的 ATTR 算子
	std::string m_current_target;                        //< 当前规则目标类别名
	RuleKind m_current_kind = RuleKind::FILTER;          //< 当前规则类型
	TreeExprCompiler m_expr_compiler;                    //< 表达式编译器
};

} // namespace postanvil