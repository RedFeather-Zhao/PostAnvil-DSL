/**
 * @file   operators.hpp
 * @brief  PostAnvil 算子层次结构 —— 评估上下文与变换算子
 * @detail 本文件定义了算子管道中的核心组件：
 *         EvalResult：评估结果
 *         EvaluationContext：评估上下文（算子间传递的可变状态和相邻帧缓存）
 *         SceneOperator / FilterOperator / AttributeOperator：算子层次结构
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/common.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace postanvil {

// ========================== Eval Struct ============================

/**
 * @brief 评估结果，包含每个类别中保留的实例列表
 */
struct EvalResult {
	Scene kept;		//< 评估保留的场景，保留按类别组织的实例映射

public:
	explicit EvalResult(const Scene& scene)
		: kept(scene)
	{
	}

	explicit EvalResult(Scene&& scene)
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
 * - scene：场景（算子逐步变换，图像元数据，如过滤、新增类别等）
 */
struct EvaluationContext {
	const static inline char* GLOBAL_TARGET = "GLOBAL";	//< 全局目标类别名

	Scene scene;		//< 场景
	
	// TODO 更多上下文字段计划在未来扩展，如：
	// std::unordered_map<std::string, double> global_vars; //< 全局变量
	// 帧缓存：用于跨算子或跨帧传递信息，如多帧一致性过滤
	// 其他上下文信息，如日志、统计数据等
	// 用于聚类、跟踪等高级算子
	// ...

	/**
	 * @brief 构造评估上下文
	 * @param s   - 初始输入场景
	 * @param img - 图像信息
	 */
	explicit EvaluationContext(const Scene& s)
		: scene(s)
	{
	}

	/**
	 * @brief 将当前上下文转换为评估结果
	 * @return 包含当前场景的评估结果
	 */
	EvalResult to_result() const {
		return EvalResult(scene);
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
	 * 若 target == GLOBAL_TARGET，则对所有类别生效。
	 *
	 * @param ctx 评估上下文
	 */
	void apply(EvaluationContext& ctx) const override
	{
		// 单实例合法性校验：所有条件均满足则返回 true
		auto is_valid = [&](const auto& inst) {
			return std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx.scene);
			});
		};

		// 容器过滤：原地删除不合法的实例
		auto filterInstances = [&](Instances& instances) {
			std::erase_if(instances, [&](const auto& inst) {
				return !is_valid(inst);
			});
		};

		if (target == EvaluationContext::GLOBAL_TARGET) {
			for (auto& [name, instances] : ctx.scene.objects) {
				filterInstances(instances);
			}
			return;
		}

		auto it = ctx.scene.objects.find(target);
		if (it != ctx.scene.objects.end()) {
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
	 * 若 target == GLOBAL_TARGET，则对所有类别生效。
	 *
	 * @param ctx 评估上下文
	 */
	void apply(EvaluationContext& ctx) const override
	{
		auto compute_attrs = [&](Instances& instances) {
			for (auto& inst : instances) {
				for (const auto& def : attr_defs) {
					inst.set_prop(def.name, def.expression(inst, ctx.scene));
				}
			}
		};

		if (target == EvaluationContext::GLOBAL_TARGET) {
			for (auto& [name, instances] : ctx.scene.objects) {
				compute_attrs(instances);
			}
			return;
		}

		auto it = ctx.scene.objects.find(target);
		if (it != ctx.scene.objects.end()) {
			compute_attrs(it->second);
		}
	}
};

} // namespace postanvil