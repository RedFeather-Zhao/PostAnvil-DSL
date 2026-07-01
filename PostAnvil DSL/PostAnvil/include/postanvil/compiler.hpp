/**
 * @file   compiler.hpp
 * @brief  场景规则编译器 —— 将 DSL 规则编译为可复用的算子管道（CompiledProgram）
 * @detail 本文件实现了 PostAnvil 的编译型评估架构，核心设计为"算子管道"模式：
 *
 * 算子体系（Operator Pipeline）：
 *         场景规则被编译为一系列算子（SceneOperator），每个算子对评估上下文
 *         （EvaluationContext）执行一次变换算子按序执行，后续算子可以消费
 *         前置算子产生的数据（如分值、临时属性、新类别等）
 *
 * 编译流程（Compile）：
 *         SceneRuleCompiler 遍历 AST 规则列表，将每个规则编译为对应的算子
 *         当前支持 OP_FILTER（过滤）和 OP_ATTRIBUTE（属性）算子
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
 * - 函数调用（解析保留，编译暂不实现）
 *
 * 注意：所有标识符在词法分析阶段已转为大写，属性名比较均使用大写。
 *
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/ast.hpp"
#include "postanvil/context.hpp"
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>
#include <memory>

namespace postanvil {

// ========================== Func Type ============================

/**
 * @brief 编译后的数值表达式函数
 */
using NumFunc = std::function<double(const Instance&, const Scene&, const Image&)>;

/**
 * @brief 编译后的布尔过滤函数
 */
using FilterFunc = std::function<bool(const Instance&, const Scene&, const Image&)>;

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
 * EvaluationContext 是算子间共享数据的载体每个算子通过 apply() 方法
 * 读取并修改上下文，实现管道式的数据变换
 *
 * 当前包含：
 * - scene：可变场景（算子逐步变换，如过滤、新增类别等）
 * - image：图像元信息（只读）
 */
struct EvaluationContext {
	Scene scene;		//< 可变场景，算子可修改（过滤、聚类、新增类别等）
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
 *
 * 定义了场景规则编译后支持的所有算子类型
 */
enum class OperatorKind {
	OP_BASE,           //< 基类（抽象）
	OP_FILTER,         //< 过滤算子：按条件保留/丢弃实例
	OP_ATTRIBUTE,      //< 属性算子：为实例添加计算字段
};

/**
 * @brief 算子基类 —— 管道中所有变换单元的抽象
 *
 * 每个算子代表管道中的一个变换步骤，接收 EvaluationContext 并对其执行变换
 * 派生类通过重写 apply() 实现具体的变换逻辑
 */
struct SceneOperator {
	OperatorKind kind = OperatorKind::OP_BASE;	//< 算子类型
	std::string target;							//< 目标类别名称

public:
	explicit SceneOperator(OperatorKind kind_ = OperatorKind::OP_BASE): kind(kind_)
	{
	}

	virtual ~SceneOperator() = default;

	/**
	 * @brief 对评估上下文执行变换，派生类必须实现此方法，定义具体的变换逻辑
	 * @param ctx - 评估上下文
	 */
	virtual void apply(EvaluationContext& ctx) const = 0;
};

/**
 * @brief 过滤算子 —— 按条件筛选实例
 *
 * 对目标类别（或全局）的每个实例执行过滤条件链，仅保留满足所有条件的实例
 * 过滤条件由 SceneRuleCompiler 将 AST 表达式编译为 FilterFunc 闭包链
 *
 * 使用示例（DSL）：
 * @code
 *   RULE FILTER GLOBAL:
 *       SELF.CONF > 0.5
 *   RULE FILTER PERSON:
 *       SELF.W > 20
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
	 * 遍历目标类别的所有实例，保留满足所有条件的实例
	 * 若 target == "GLOBAL"，则对所有类别生效
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
 * CompiledProgram 是 SceneRuleCompiler 的编译产物，内部持有
 * 一系列算子（SceneOperator），按序对输入场景执行变换
 *
 * 它可以安全地移动、存储，并反复对不同的场景数据执行相同评估
 *
 * 使用方式：
 * @code
 *   SceneRuleCompiler compiler;
 *   CompiledProgram program = compiler.compile(rules);
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

// ====================== SceneRuleCompiler =========================

/**
 * @brief 场景规则编译器，将 AST 规则编译为可复用的 CompiledProgram
 *
 * SceneRuleCompiler 是 PostAnvil 的"编译器"：它接收解析后的规则列表，
 * 将每个规则编译为对应的算子（SceneOperator），最终生成一个包含算子管道
 * 的 CompiledProgram 对象
 *
 * 编译器采用分发模式：根据 RuleKind 将规则分发到对应的编译方法
 *
 * 使用方式：
 * @code
 *   Parser parser;
 *   std::vector<Rule> rules;
 *   parser.parse(src, rules);
 *
 *   SceneRuleCompiler compiler;
 *   CompiledProgram program = compiler.compile(rules);  // 编译一次
 *
 *   // 对多个场景反复使用
 *   EvalResult r1 = program.evaluate(scene1, img1);
 *   EvalResult r2 = program.evaluate(scene2, img2);
 * @endcode
 */
class SceneRuleCompiler {
public:
	SceneRuleCompiler() = default;

	/**
	 * @brief 将规则列表编译为算子管道
	 *
	 * 根据 RuleKind 分发到不同的编译方法：
	 * - FILTER → compile_filter_rule()
	 * - ATTR   → compile_attr_rule()
	 *
	 * @param rules 解析后的规则列表
	 * @return 编译后的 CompiledProgram 对象
	 */
	CompiledProgram compile(const std::vector<Rule>& rules) const {
		CompiledProgram program;

		using enum RuleKind;
		for (const auto& rule : rules) {
			switch (rule.kind) {
			case FILTER: {
				program.operators.emplace_back(compile_filter_rule(rule));
				break;
			}
			case ATTR: {
				program.operators.emplace_back(compile_attr_rule(rule));
				break;
			}
			default: {
				throw ParseError("Unsupported rule kind in compiler");
			}
			}
		}

		return program;
	}

private:
	// ======================== Compile ============================

	/**
	 * @brief 将一条 FILTER 规则编译为 FilterOperator
	 *
	 * 对规则中的每个条件表达式调用 compile_filter() 进行编译，
	 * 将所有编译后的条件函数打包到 FilterOperator 中
	 *
	 * @param rule 规则 AST
	 * @return 编译后的过滤算子
	 */
	std::unique_ptr<FilterOperator> compile_filter_rule(const Rule& rule) const {
		auto op = std::make_unique<FilterOperator>();
		op->target = rule.target;
		op->conditions.reserve(rule.conditions.size());

		for (const auto& cond : rule.conditions) {
			op->conditions.emplace_back(compile_filter(cond.get()));
		}
		return op;
	}

	/**
	 * @brief 将一条 ATTR 规则编译为 AttributeOperator
	 *
	 * 对规则中的每个属性赋值编译其表达式，打包到 AttributeOperator 中
	 *
	 * @param rule 规则 AST
	 * @return 编译后的属性算子
	 */
	std::unique_ptr<AttributeOperator> compile_attr_rule(const Rule& rule) const {
		auto op = std::make_unique<AttributeOperator>();
		op->target = rule.target;
		op->attr_defs.reserve(rule.assignments.size());

		for (const auto& assign : rule.assignments) {
			AttributeOperator::AttrDef def;
			def.name = assign.attr_name;
			def.expression = compile_num(assign.value_expr.get());
			op->attr_defs.push_back(std::move(def));
		}
		return op;
	}

	FilterFunc compile_filter(const Expr* e) const {
		auto num = compile_num(e);
		return [num](const Instance& self, const Scene& scene, const Image& image) {
			return num(self, scene, image) != 0.0;
		};
	}

	NumFunc compile_num(const Expr* e) const {
		if (!e) {
			return [](const Instance&, const Scene&, const Image&) { return 0.0; };
		}

		switch (e->type) {
			case Expr::Type::CONST_NUM: {
				double v = static_cast<const NumberExpr*>(e)->value;
				return [v](const Instance&, const Scene&, const Image&) { return v; };
			}

			case Expr::Type::IDENT: {
				return [](const Instance&, const Scene&, const Image&) { return 0.0; };
			}

			case Expr::Type::PROP_ACCESS: {
				const auto* pe = static_cast<const PropAccessExpr*>(e);
				std::string obj = pe->object;
				std::string prop = pe->prop;
				return [obj, prop](const Instance& self, const Scene& scene, const Image& image) {
					if (obj == "SELF") {
						return get_instance_prop(self, prop);
					}
					if (obj == "IMAGE") {
						return get_image_prop(image, prop);
					}
					return 0.0; // TODO 更多变量
				};
			}

			case Expr::Type::UNARY: {
				const auto* ue = static_cast<const UnaryExpr*>(e);
				auto rhs = compile_num(ue->rhs.get());
				std::string op = ue->op;
				return [rhs, op](const Instance& self, const Scene& scene, const Image& image) {
					double v = rhs(self, scene, image);
					if (op == "-")  return -v;
					if (op == "NOT") return v == 0.0 ? 1.0 : 0.0;
					throw ParseError("Unknown unary operator: " + op);
				};
			}

			case Expr::Type::BINARY: {
				const auto* be = static_cast<const BinaryExpr*>(e);
				auto lhs = compile_num(be->lhs.get());
				auto rhs = compile_num(be->rhs.get());
				std::string op = be->op;
				return [lhs, rhs, op](const Instance& self, const Scene& scene, const Image& image) {
					double l = lhs(self, scene, image);
					double r = rhs(self, scene, image);
					if (op == "+")   return l + r;
					if (op == "-")   return l - r;
					if (op == "*")   return l * r;
					if (op == "/")   return r != 0.0 ? l / r : 0.0;
					if (op == ">")   return l >  r ? 1.0 : 0.0;
					if (op == "<")   return l <  r ? 1.0 : 0.0;
					if (op == ">=")  return l >= r ? 1.0 : 0.0;
					if (op == "<=")  return l <= r ? 1.0 : 0.0;
					if (op == "==")  return l == r ? 1.0 : 0.0;
					if (op == "!=")  return l != r ? 1.0 : 0.0;
					if (op == "AND") return ((l != 0.0) && (r != 0.0)) ? 1.0 : 0.0;
					if (op == "OR")  return ((l != 0.0) || (r != 0.0)) ? 1.0 : 0.0;
					return 0.0;
				};
			}

			case Expr::Type::CALL: {
				return compile_call(static_cast<const CallExpr*>(e));
			}
			case Expr::Type::UNDEFINED: {
				throw ParseError("Cannot compile undefined expression");
			}
		}

		return [](const Instance&, const Scene&, const Image&) { return 0.0; };
	}

	/**
	 * @brief 编译函数/谓词调用
	 *
	 * 当前保留函数调用解析骨架，但编译阶段暂不实现任何函数/谓词。
	 * 所有调用均返回 0.0，待未来重新设计谓词和函数功能。
	 */
	NumFunc compile_call(const CallExpr* ce) const {
		// TODO: 未来重新设计谓词和函数功能时在此处添加实现
		return [](const Instance&, const Scene&, const Image&) { return 0.0; };
	}


	// ======================== Tool Functions =========================

	static std::string
	extract_class_name(const Expr* e)
	{
		if (!e) {
			return {};
		}

		switch (e->type) {
		case Expr::Type::IDENT: {
			return static_cast<const IdentExpr*>(e)->name;
		}
		case Expr::Type::PROP_ACCESS: {
			return static_cast<const PropAccessExpr*>(e)->object;
		}
		default:
			return {};
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
	 * @return double - 属性值；若属性不存在则返回 0.0
	 */
	static double
	get_instance_prop(const Instance& inst, std::string_view prop)
	{
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
		throw ParseError("Unknown property '" + std::string(prop) + "' for instance of class '" + inst.cls + "'");
	}

	/**
	 * @brief 获取图像属性
	 * 
	 * @param img  - 图像信息
	 * @param prop - 属性名，当前仅支持 "W"（宽度）和 "H"（高度）
	 * @return double - 属性值；若属性不存在则返回 0.0
	 */
	static double
	get_image_prop(const Image& img, std::string_view prop)
	{
		if (prop == "W") return img.width;
		if (prop == "H") return img.height;
		throw ParseError("Unknown property '" + std::string(prop) + "' for image");
	}

	/**
	 * @brief 计算两个实例的 IoU（交并比）
	 *
	 * @param a - 实例 A
	 * @param b - 实例 B
	 * @return double - IoU 值 [0.0, 1.0]
	 */
	static double
	compute_iou(const Instance& a, const Instance& b)
	{
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
};

} // namespace postanvil