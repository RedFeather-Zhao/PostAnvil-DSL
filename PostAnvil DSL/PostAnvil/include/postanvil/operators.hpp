/**
 * @file   operators.hpp
 * @brief  PostAnvil 算子层次结构，定义评估上下文和各类变换算子
 *
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

#include "type.hpp"
#include "scene.hpp"


namespace postanvil {

// ========================== Eval Struct ============================

/**
 * @brief 编译后的函数体类型
 * @param args 参数值列表
 * @param ctx 评估上下文
 * @return double 计算结果
 */
using CompiledFunc = std::function<double(
	const std::vector<double>& args,
	struct EvaluationContext& ctx
)>;


/**
 * @brief 评估上下文，承载算子管道执行过程中的可变状态
 * @details 算子通过 apply 方法读取并修改上下文，实现管道式的数据变换
 */
struct EvaluationContext {
	const static inline char* GLOBAL_TARGET = "GLOBAL";

	/**
	 * @brief 构造评估上下文
	 * @param s 初始场景
	 */
	explicit EvaluationContext(const Scene& s)
		: scene(s)
	{
	}

	Scene to_result() const {
		// TODO: 后续添加更多上下文处理
		return scene;
	}

public:

	Scene scene;											 // 当前场景，被算子逐步变换
	std::unordered_map<std::string, CompiledFunc> functions; // 函数注册表

	// TODO: 未来扩展字段，帧缓存用于跨帧信息传递
	std::queue<Scene> frame_cache;
};

// ========================= Operator ============================

/**
 * @brief 算子类型枚举
 */
enum class OperatorKind {
	OP_BASE,      // 基类，抽象类型
	OP_FILTER,    // 过滤算子
	OP_ATTRIBUTE, // 属性算子
	OP_GROUP,     // 分组算子
	OP_APPEND,    // 追加算子
	OP_FUNC,      // 函数算子
	OP_VARDEF,    // 变量定义算子
	OP_IMPORT,    // 导入算子
	OP_EXPORT,    // 导出算子
};

/**
 * @brief 场景算子的抽象基类
 */
struct SceneOperator {
	OperatorKind kind = OperatorKind::OP_BASE;
	StrFunc target;		// 运行时解析目标类别名，若返回 GLOBAL 则应用于所有类别

public:
	explicit SceneOperator(OperatorKind kind_ = OperatorKind::OP_BASE) : kind(kind_)
	{}

	virtual ~SceneOperator() = default;

	/**
	 * @brief 对上下文应用算子变换
	 * @param ctx 评估上下文，将被就地修改
	 */
	virtual void apply(EvaluationContext& ctx) const = 0;
};

// ====================== FilterOperator ========================

/**
 * @brief 过滤算子，按条件保留或丢弃实例
 */
struct FilterOperator : SceneOperator {
	std::vector<BoolFunc> conditions; // 过滤条件列表，全部满足才保留

	FilterOperator() : SceneOperator(OperatorKind::OP_FILTER) {}

	void apply(EvaluationContext& ctx) const override
	{
		auto is_valid = [&](const auto& inst) {
			return std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx.scene);
			});
		};

		auto filterInstances = [&](Instances& instances) {
			std::erase_if(instances, [&](const auto& inst) {
				return !is_valid(inst);
			});
		};

		auto target_name = target(Scene::make_dummy(), ctx.scene);

		if (target_name == EvaluationContext::GLOBAL_TARGET) {
			for (auto& [name, instances] : ctx.scene.objects) {
				filterInstances(instances);
			}
			return;
		}

		auto it = ctx.scene.objects.find(target_name);
		if (it != ctx.scene.objects.end()) {
			filterInstances(it->second);
		}
	}
};

// ====================== AttributeOperator =====================

/**
 * @brief 属性算子，为实例添加计算字段
 */
struct AttributeOperator : SceneOperator {
	/**
	 * @brief 属性定义
	 */
	struct AttrDef {
		std::string name;				// 属性名
		ValFunc expression;				// 求值表达式
		bool is_class_attr = false;		// 是否为类别级属性
		std::string class_name;			// 类别名，仅类别属性有效
	};

	std::vector<AttrDef> attr_defs;

	AttributeOperator() : SceneOperator(OperatorKind::OP_ATTRIBUTE) {}

	void apply(EvaluationContext& ctx) const override
	{
		auto compute_attrs = [&](Instances& instances) {
			for (auto& inst : instances) {
				for (const auto& def : attr_defs) {
					if (def.is_class_attr) {
						ctx.scene.class_props[def.class_name][def.name]
							= def.expression(Scene::make_dummy(), ctx.scene);
					}
					else {
						Val val = def.expression(inst, ctx.scene);
						inst.set_prop(def.name, val);
					}
				}
			}
		};

		auto target_name = target(Scene::make_dummy(), ctx.scene);

		if (target_name == EvaluationContext::GLOBAL_TARGET) {
			for (auto& [name, instances] : ctx.scene.objects) {
				compute_attrs(instances);
			}
			return;
		}

		auto it = ctx.scene.objects.find(target_name);
		if (it != ctx.scene.objects.end()) {
			compute_attrs(it->second);
		}
	}
};

// ====================== GroupOperator =========================

/**
 * @brief 分组算子，从源类别中挑选实例创建新类别
 */
struct GroupOperator : SceneOperator {
	StrFunc new_class;                // 目标新类别名
	StrFunc source_class;             // 源类别名
	std::vector<BoolFunc> conditions;    // 挑选条件

	GroupOperator() : SceneOperator(OperatorKind::OP_GROUP) {}

	void apply(EvaluationContext& ctx) const override {
		auto source_cls = source_class(Scene::make_dummy(), ctx.scene);
		auto new_cls = new_class(Scene::make_dummy(), ctx.scene);

		auto it = ctx.scene.objects.find(source_cls);
		if (it == ctx.scene.objects.end()) {
			throw RuntimeError("Source class '" + source_cls + "' not found in scene");
		}

		Instances selected;
		for (const auto& inst : it->second) {
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx.scene);
			});
			if (all_pass) {
				selected.emplace_back(inst);
			}
		}
		ctx.scene.objects[new_cls] = std::move(selected);
	}
};

// ====================== AppendOperator ========================

/**
 * @brief 追加算子，将源类别中满足条件的实例追加到目标类别
 */
struct AppendOperator : SceneOperator {
	StrFunc dest_class;              // 目标类别名
	StrFunc source_class;            // 源类别名
	std::vector<BoolFunc> conditions;    // 追加条件

	AppendOperator() : SceneOperator(OperatorKind::OP_APPEND) {}

	void apply(EvaluationContext& ctx) const override {
		auto dest_cls = dest_class(Scene::make_dummy(), ctx.scene);
		auto source_cls = source_class(Scene::make_dummy(), ctx.scene);

		auto it = ctx.scene.objects.find(source_cls);
		if (it == ctx.scene.objects.end()) {
			throw RuntimeError("Source class '" + source_cls + "' not found in scene");
		}

		for (const auto& inst : it->second) {
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx.scene);
			});
			if (all_pass) {
				ctx.scene.objects[dest_cls].emplace_back(inst);
			}
		}
	}
};

// ====================== FuncOperator ==========================

/**
 * @brief 函数算子，注册自定义函数到上下文
 * @details 函数不通过 apply 执行，而是存入函数表供表达式调用
 */
struct FuncOperator : SceneOperator {
	std::string name;						// 函数名
	std::vector<std::string> param_names;	// 参数名列表
	CompiledFunc body;						// 函数体

	FuncOperator() : SceneOperator(OperatorKind::OP_FUNC) {}

	void apply(EvaluationContext& /*ctx*/) const override {
		// 函数通过函数表调用，不由 apply 执行
		// 可选，在此处注册函数表
	}
};

// ====================== VarDefOperator ========================

/**
 * @brief 变量定义算子，初始化全局变量
 */
struct VarDefOperator : SceneOperator {
	std::string var_name;		// 变量名
	Type var_type;				// 变量类型
	ValFunc initializer;		// 初始化表达式

	VarDefOperator() : SceneOperator(OperatorKind::OP_VARDEF) {}

	void apply(EvaluationContext& ctx) const override {
		Val val = initializer(Scene::make_dummy(), ctx.scene);
		ctx.scene.variables[var_name] = val;
	}
};

// ====================== ImportOperator ========================

/**
 * @brief 导入算子，验证宿主导入的变量是否存在且类型匹配
 */
struct ImportOperator : SceneOperator {
	std::string host_name;    // 宿主变量名
	std::string local_name;   // 本地别名
	Type var_type;            // 期望类型

	ImportOperator() : SceneOperator(OperatorKind::OP_IMPORT) {}

	void apply(EvaluationContext& ctx) const override {
		if (!ctx.scene.variables.contains(local_name)) {
			throw RuntimeError("Imported variable '" + local_name + "' not provided by host");
		}
		Val const& val = ctx.scene.variables[local_name];
		if (val.type() != var_type) {
			throw RuntimeError("Imported variable '" + local_name + "' type mismatch");
		}
	}
};

// ====================== ExportOperator ========================

/**
 * @brief 导出算子，将表达式结果存回宿主
 */
struct ExportOperator : SceneOperator {
	std::string host_name;    // 宿主导出名
	ValFunc expression;       // 导出表达式

	ExportOperator() : SceneOperator(OperatorKind::OP_EXPORT) {}

	void apply(EvaluationContext& ctx) const override {
		Val result = expression(Scene::make_dummy(), ctx.scene);
		ctx.scene.variables["__export__" + host_name] = result;
	}
};

} // namespace postanvil