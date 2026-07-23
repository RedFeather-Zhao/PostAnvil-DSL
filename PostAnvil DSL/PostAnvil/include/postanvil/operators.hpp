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
using CompiledFunc = std::function<Val(
	const std::vector<Val>& args,
	const Instance& self,
	EvaluationContext& ctx
)>;


/**
 * @brief 评估上下文，承载算子管道执行过程中的可变状态
 * 包含：
 *	1.场景信息，包含图片元数据、按类别分组的检测实例、全局变量信息
 *	2.前后帧场景信息，预留帧间一致性配置
 *  3.局部变量与函数参数栈空间，仅当前函数体可见栈顶变量
 *  4. 
 */
struct EvaluationContext {
	const static inline char* GLOBAL_TARGET = "GLOBAL";

	/**
	 * @brief 构造评估上下文
	 * @param s 初始场景
	 */
	explicit EvaluationContext(const Scene& s)
		: scene(s), is_returned(false)
	{
	}

	Scene to_result() const {
		return scene;
	}

	void push_scope() {
		local_stack.emplace_back();
	}

	void pop_scope() {
		local_stack.pop_back();
	}

	/**
	 * @brief 获取当前作用域局部/全局变量
	 * 
	 * @param name	- 变量名
	 * @return Val	- 变量值
	 */
	Val get_var(const std::string& name) const {
		// 从最近的局部作用域向上查找
		for (auto it = local_stack.rbegin(); it != local_stack.rend(); ++it) {
			if (auto found = it->find(name); found != it->end()) {
				return found->second;
			}
		}

		// 未找到则查找全局变量
		auto it = scene.variables.find(name);
		if (it == scene.variables.end()) {
			throw RuntimeError("Undefined variable '" + name + "'");
		}
		return it->second;
	}

	/**
	 * @brief 设置当前作用域局部/全局变量
	 * 
	 * @param name	- 变量名
	 * @param val	- 变量值
	 */
	void set_var(const std::string& name, const Val& val) {
		// 从内向外查找，若找到则更新；否则在最近的作用域中创建
		for (auto it = local_stack.rbegin(); it != local_stack.rend(); ++it) {
			if (auto found = it->find(name); found != it->end()) {
				found->second = val;
				return;
			}
		}
		// 局部作用域存在时，在当前最内层创建
		if (!local_stack.empty()) {
			local_stack.back()[name] = val;
			return;
		}
		// 无局部作用域（顶层），视为全局变量
		scene.variables[name] = val;
	}

	/**
	 * @brief 执行返回调用，保存缓存结果
	 */
	void do_return(Val&& val) {
		is_returned = true;
		return_value = std::move(val);
	}
public:

	Scene scene;									// 当前场景，被算子逐步变换

	detail::str_map<CompiledFunc> functions;		// 函数注册表

	std::vector<detail::str_map<Val>> local_stack;	// 栈空间，存储局部变量
	detail::str_map<const Instance*> loop_vars;		// 循环变量名，用于 for 语句遍历实例

	std::queue<Scene> frame_cache;					// 临近帧缓存

	const Instance* curr_inst	= nullptr;			// 当前实例对象
	bool is_returned			= true;				// 当前函数返回
	Val return_value;								// 函数返回缓存
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

static const char* operation_kind_to_string(OperatorKind kind) {
	switch (kind) {
	using enum postanvil::OperatorKind;
	case OP_BASE:		return "BASE";
	case OP_FILTER:		return "FILTER";
	case OP_ATTRIBUTE:	return "ATTRIBUTE";
	case OP_GROUP:		return "GROUP";
	case OP_APPEND:		return "APPEND";
	case OP_FUNC:		return "FUNC";
	case OP_VARDEF:		return "VARDEF";
	case OP_IMPORT:		return "IMPORT";
	case OP_EXPORT:		return "EXPORT";
	default:			return "UNKNOWN";
	}
}

/**
 * @brief 场景算子的抽象基类
 */
struct SceneOperator {
	OperatorKind kind = OperatorKind::OP_BASE;
	StrFunc target;		// 运行时解析目标类别名，若返回 "GLOBAL" 则应用于所有类别

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
				return cond(inst, ctx);
			});
		};

		auto filterInstances = [&](Instances& instances) {
			std::erase_if(instances, [&](const auto& inst) {
				return !is_valid(inst);
			});
		};

		auto target_name = target(Scene::make_dummy(), ctx);

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
		auto target_name = target(Scene::make_dummy(), ctx);

		auto compute_attrs = [&](Instances& instances) {
			// 逐语句计算
			for (const auto& def : attr_defs) {
				if (def.is_class_attr == true) {
					// 类属性赋值
					Val val = def.expression(Scene::make_dummy(), ctx);
					ctx.scene.class_props[def.class_name][def.name] = val;
				}
				else {
					// 实例属性
					for (auto& inst : instances) {
						Val val = def.expression(inst, ctx);
						inst.set_prop(def.name, val);
					}
				}
			}
		};

		if (target_name == EvaluationContext::GLOBAL_TARGET) {
			for (auto& [name, instances] : ctx.scene.objects) {
				compute_attrs(instances);
			}
			return;
		}

		// 类别不存在则创建
		compute_attrs(ctx.scene.objects[target_name]);
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
		auto source_cls = source_class(Scene::make_dummy(), ctx);
		auto new_cls = new_class(Scene::make_dummy(), ctx);

		auto it = ctx.scene.objects.find(source_cls);
		if (it == ctx.scene.objects.end()) {
			throw RuntimeError("Source class '" + source_cls + "' not found in scene");
		}

		Instances selected;
		for (const auto& inst : it->second) {
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx);
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
	StrFunc dest_class;						// 目标类别名
	StrFunc source_class;					// 源类别名
	std::vector<BoolFunc> conditions;		// 追加条件

	AppendOperator() : SceneOperator(OperatorKind::OP_APPEND) {}

	void apply(EvaluationContext& ctx) const override {
		auto dest_cls = dest_class(Scene::make_dummy(), ctx);
		auto source_cls = source_class(Scene::make_dummy(), ctx);

		auto it = ctx.scene.objects.find(source_cls);
		if (it == ctx.scene.objects.end()) {
			throw RuntimeError("Source class '" + source_cls + "' not found in scene");
		}

		for (const auto& inst : it->second) {
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(inst, ctx);
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
		Val val = initializer(Scene::make_dummy(), ctx);
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
		Val result = expression(Scene::make_dummy(), ctx);
		ctx.scene.variables["__export__" + host_name] = result;
	}
};

} // namespace postanvil