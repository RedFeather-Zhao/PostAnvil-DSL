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
 *         当前支持 OP_FILTER（过滤）算子，同时预留了 Score、ScoreFilter、Cluster、
 *         CategoryCreate、OP_ATTRIBUTE 等算子类型供后续扩展
 *
 * 执行流程（Evaluate）：
 *         CompiledProgram 持有算子序列，对输入场景依次执行每个算子的 apply()，
 *         最终输出 EvalResult
 *
 * 算子类型（Operator）：
 *         1. OP_FILTER：按条件过滤实例，保留满足条件的实例
 *         2. OP_ATTRIBUTE：为类别每个实例添加临时属性（预留）
 *
 * 支持的表达式类型：
 * - 数值常量、属性访问（self.width / image.width / OtherClass.prop）
 * - 比较运算（< > <= >= == !=）
 * - 算术运算（+ - *）
 * - 逻辑运算（AND / OR / NOT）
 * - 内置函数：abs(x)、iou(self, other)
 * - 空间谓词：CONTAINS、INSIDE、OVERLAP、CLOSE_TO
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
 * - attrs: 按类别和实例索引存储的自定义属性
 * 
 * 预留字段：
 * - scores：按类别和实例索引存储的自定义分值
 * - temp_attrs：按类别和实例索引存储的临时属性
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
	OP_ATTRIBUTE,      //< 属性算子：为实例添加计算字段（预留）
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
 *   RULE FOR GLOBAL:
 *       self.conf > 0.5
 *   RULE FOR Person:
 *       self.width > 20
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
 * @brief 临时属性算子 —— 为实例添加计算字段（预留）
 *
 * TODO:实现 DSL 语法
 * @code
 *   ATTR FOR Person:
 *       risk_score = self.conf < 0.3 ? 1.0 : 0.0
 *       density = self.area / (self.width * self.height)
 * @endcode
 *
 * 为每个实例计算指定的属性值，存储到 EvaluationContext::temp_attrs 中
 * 后续算子可通过特殊的属性访问语法引用这些临时属性
 */
struct AttributeOperator : SceneOperator {
	/**
	 * @brief 临时属性名
	 */
	std::string attr_name;

	/**
	 * @brief 属性值计算表达式（编译后的数值函数）
	 */
	NumFunc expression;

	AttributeOperator() { kind = OperatorKind::OP_ATTRIBUTE; }

	void apply(EvaluationContext& /*ctx*/) const override {
		// TODO: 为 target 类别的每个实例计算 attr_name 的值，存储到 ctx.temp_attrs[target][i][attr_name]
	}
};

// ========================== Program ===========================

/**
 * @brief 编译后的场景规则程序（CompiledProgram）
 *
 * CompiledProgram 是 SceneRuleCompiler 的编译产物，内部持有
 * 一系列算子（SceneOperator），按序对输入场景执行变换
 *
 * 它可以安全地复制、存储，并反复对不同的场景数据执行相同评估
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
 * 编译器采用分发模式：根据规则类型（当前仅支持 OP_FILTER）将规则分发到
 * 对应的编译方法未来新增算子类型时，只需添加新的编译方法并在 compile()
 * 中添加分发逻辑
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
	 * 当前所有规则均编译为 FilterOperator未来可根据规则类型分发到
	 * 不同的编译方法（如 compile_score_rule、compile_cluster_rule 等）
	 *
	 * @param rules 解析后的规则列表
	 * @return 编译后的 CompiledProgram 对象
	 */
	CompiledProgram compile(const std::vector<Rule>& rules) const {
		CompiledProgram program;

		for (const auto& rule : rules) {
			program.operators.emplace_back(compile_filter_rule(rule));
		}

		return program;
	}

private:
	// ======================== Compile ============================

	/**
	 * @brief 将一条规则编译为 FilterOperator
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
					if (obj == "self") {
						return get_instance_prop(self, prop);
					}
					if (obj == "image") {
						return get_image_prop(image, prop);
					}
					return 0.0;
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

	NumFunc compile_call(const CallExpr* ce) const {
		if (ce->name == "abs" && ce->args.size() == 1) {
			auto arg = compile_num(ce->args[0].get());
			return [arg](const Instance& self, const Scene& scene, const Image& image) {
				return std::abs(arg(self, scene, image));
			};
		}

		if (ce->name == "iou" && ce->args.size() == 2) {
			std::string other_class = extract_class_name(ce->args[1].get());
			return [other_class](const Instance& self, const Scene& scene, const Image&) {
				if (other_class.empty()) return 0.0;
				auto it = scene.find(other_class);
				if (it == scene.end() || it->second.empty()) return 0.0;
				return compute_iou(self, it->second.front());
			};
		}

		std::string name_up = ce->name;
		for (auto& ch : name_up) {
			ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		}

		if (name_up == "CONTAINS") return compile_contains(ce);
		if (name_up == "INSIDE")   return compile_inside(ce);
		if (name_up == "OVERLAP")  return compile_overlap(ce);
		if (name_up == "CLOSE_TO") return compile_close_to(ce);

		return [](const Instance&, const Scene&, const Image&) { return 0.0; };
	}

	NumFunc compile_contains(const CallExpr* ce) const {
		std::string target;
		if (ce->args.size() >= 1) target = extract_class_name(ce->args[0].get());

		bool has_qty = (ce->qtyRange != nullptr);
		bool is_range = has_qty && ce->qtyRange->is_range;
		int qty_min = has_qty ? ce->qtyRange->min : 1;
		int qty_max = (has_qty && is_range) ? ce->qtyRange->max : qty_min;

		bool has_explicit_count = false;
		int explicit_count = 1;
		if (ce->args.size() >= 2 && ce->args[1]->type == Expr::Type::CONST_NUM) {
			has_explicit_count = true;
			explicit_count = static_cast<int>(static_cast<const NumberExpr*>(ce->args[1].get())->value);
		}

		return [=](const Instance& self, const Scene& scene, const Image&) {
			if (target.empty()) {
				return 0.0;
			}
			int cnt = 0;
			if (auto it = scene.find(target); it != scene.end()) {
				for (const auto& b : it->second) {
					if (b.x >= self.x && b.y >= self.y
						&& b.right() <= self.right() && b.bottom() <= self.bottom()) {
						++cnt;
					}
				}
			}
			if (has_qty) {
				if (is_range) return (cnt >= qty_min && cnt <= qty_max) ? 1.0 : 0.0;
				return (cnt >= qty_min) ? 1.0 : 0.0;
			}
			if (has_explicit_count) return (cnt == explicit_count) ? 1.0 : 0.0;
			return (cnt >= 1) ? 1.0 : 0.0;
		};
	}

	NumFunc compile_inside(const CallExpr* ce) const {
		std::string target;
		if (ce->args.size() >= 1) target = extract_class_name(ce->args[0].get());
		return [target](const Instance& self, const Scene& scene, const Image&) {
			if (target.empty()) return 0.0;
			auto it = scene.find(target);
			if (it == scene.end()) return 0.0;
			for (const auto& b : it->second) {
				if (self.x >= b.x && self.right() <= b.right()
					&& self.y >= b.y && self.bottom() <= b.bottom()) {
					return 1.0;
				}
			}
			return 0.0;
		};
	}

	NumFunc compile_overlap(const CallExpr* ce) const {
		std::string target;
		if (ce->args.size() >= 1) target = extract_class_name(ce->args[0].get());
		return [target](const Instance& self, const Scene& scene, const Image&) {
			if (target.empty()) return 0.0;
			auto it = scene.find(target);
			if (it == scene.end()) return 0.0;
			for (const auto& b : it->second) {
				if (compute_iou(self, b) > 0.0) return 1.0;
			}
			return 0.0;
		};
	}

	NumFunc compile_close_to(const CallExpr* ce) const {
		std::string target;
		if (ce->args.size() >= 1) target = extract_class_name(ce->args[0].get());
		double threshold = 0.0;
		if (ce->args.size() >= 2 && ce->args[1]->type == Expr::Type::CONST_NUM) {
			threshold = static_cast<const NumberExpr*>(ce->args[1].get())->value;
		} else if (ce->qtyRange) {
			threshold = static_cast<double>(ce->qtyRange->min);
		}
		return [target, threshold](const Instance& self, const Scene& scene, const Image&) {
			if (target.empty()) return 0.0;
			auto it = scene.find(target);
			if (it == scene.end()) return 0.0;
			for (const auto& b : it->second) {
				double dx = self.center_x() - b.center_x();
				double dy = self.center_y() - b.center_y();
				if (std::sqrt(dx * dx + dy * dy) <= threshold) return 1.0;
			}
			return 0.0;
		};
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
	 * @brief 获取实例的属性值，包括临时属性
	 * 
	 * @param inst - 实例
	 * @param prop - 属性名（如 "x", "y", "width", "height", "conf" 等）
	 * @return double - 属性值；若属性不存在则返回 0.0
	 */
	static double
	get_instance_prop(const Instance& inst, std::string_view prop)
	{
		if (prop == "x")				return inst.x;
		if (prop == "y")				return inst.y;
		if (prop == "width")			return inst.width;
		if (prop == "height")			return inst.height;
		if (prop == "right")			return inst.right();
		if (prop == "bottom")			return inst.bottom();
		if (prop == "center_x")			return inst.center_x();
		if (prop == "center_y")			return inst.center_y();
		if (prop == "area")				return inst.area();
		if (prop == "aspect_ratio")		return inst.aspect_ratio();
		if (prop == "conf")				return inst.conf;
		return 0.0;
	}

	/**
	 * 
	 * 
	 * @param img
	 * @param prop
	 * @return 
	 */
	static double
	get_image_prop(const Image& img, std::string_view prop)
	{
		if (prop == "width")  return img.width;
		if (prop == "height") return img.height;
		return 0.0;
	}

	/**
	 * .
	 * 
	 * @param a
	 * @param b
	 * @return 
	 */
	static double
	compute_iou(const Instance& a, const Instance& b)
	{
		double ix1 = std::max(a.x, b.x);
		double iy1 = std::max(a.y, b.y);
		double ix2 = std::min(a.right(), b.right());
		double iy2 = std::min(a.bottom(), b.bottom());
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