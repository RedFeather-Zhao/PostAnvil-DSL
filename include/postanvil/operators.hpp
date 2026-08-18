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
#include <cmath>
#include <numeric>
#include <utility>

#include "type.hpp"
#include "scene.hpp"


namespace postanvil {

// ========================== Eval Struct ============================

/**
 * @brief 编译后的的函数体闭包
 *
 */
using CompiledFunc = std::function<Val(
	const std::vector<Val>&		args,					//< 参数值列表
	EvaluationContext&			ctx						//< 评估上下文
)>;

/**
 * @brief 函数信息结构体，包含函数体、返回类型和参数类型列表
 *
 */
struct FunctionInfo {
	CompiledFunc				func;					//< 编译后的的函数体闭包
	Type						ret_type;				//< 返回类型
	std::vector<Type>			param_types;			//< 参数类型列表
	bool						is_builtin = false;		//< 是否为内置函数
};

/**
 * @brief 评估上下文，承载算子管道执行过程中的可变状态，
 *		  包含场景信息、前后帧缓存、局部变量与函数参数栈
 *
 */
struct EvaluationContext {
	const static inline char* GLOBAL_TARGET = "GLOBAL";

	/**
	 * @brief 构造评估上下文
	 *
	 * @param s 初始场景
	 */
	explicit EvaluationContext(const Scene& s)
		: scene(s), is_returned(false)
	{}

	/**
	 * @brief 当前实例上下文守卫，离开作用域时恢复原实例句柄
	 *
	 */
	class CurrentInstanceScope {
	public:
		CurrentInstanceScope(EvaluationContext& context, InstanceHandle handle)
			: m_context(&context),
			  m_previous_handle(context.curr_handle)
		{
			(void)context.scene.inst_at(handle.id);
			context.curr_handle = std::move(handle);
		}

		CurrentInstanceScope(const CurrentInstanceScope&) = delete;
		CurrentInstanceScope& operator=(const CurrentInstanceScope&) = delete;
		CurrentInstanceScope(CurrentInstanceScope&& other) noexcept
			: m_context(std::exchange(other.m_context, nullptr)),
			  m_previous_handle(std::move(other.m_previous_handle))
		{}

		~CurrentInstanceScope() {
			if (!m_context) {
				return;
			}
			m_context->curr_handle = std::move(m_previous_handle);
		}


	private:
		EvaluationContext*	m_context;
		InstanceHandle		m_previous_handle;
	};

	[[nodiscard]]
	CurrentInstanceScope enter_instance(InstanceHandle handle) {
		return CurrentInstanceScope(*this, std::move(handle));
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
		return scene.io_value(name);
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
		scene.io_set(name, val);
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

	detail::str_map<FunctionInfo> functions;		// 函数注册表

	std::vector<detail::str_map<Val>> local_stack;	// 栈空间，存储局部变量
	std::queue<Scene> frame_cache;					// 临近帧缓存

	InstanceHandle curr_handle;						// 当前实例及其类名上下文
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
	OP_SORT,      // 排序算子
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
	case OP_SORT:		return "SORT";
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
	StrFunc target_cls_expr;

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
		auto is_valid = [&](InstId id, const std::string& cls_name) {
			auto scope = ctx.enter_instance(InstanceHandle{ id, cls_name });
			return std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(ctx);
			});
		};

		auto filter_instances = [&](const std::string& cls_name) {
			auto ids = ctx.scene.cls_insts(cls_name);
			std::erase_if(ids, [&](InstId id) {
				return !is_valid(id, cls_name);
			});
			ctx.scene.cls_set_insts(cls_name, std::move(ids));
		};

		auto target_cls_name = target_cls_expr(ctx);

		if (target_cls_name == EvaluationContext::GLOBAL_TARGET) {
			for (const auto& cls_name : ctx.scene.cls_names()) {
				filter_instances(cls_name);
			}
			return;
		}

		if (ctx.scene.cls_exists(target_cls_name)) {
			filter_instances(target_cls_name);
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
		std::string cls_name;			// 类别名，仅类别属性有效
	};

	std::vector<AttrDef> attr_defs;

	AttributeOperator() : SceneOperator(OperatorKind::OP_ATTRIBUTE) {}

	void apply(EvaluationContext& ctx) const override
	{
		auto target_cls_name = target_cls_expr(ctx);

		auto compute_attrs = [&](const std::string& cls_name, const Scene::InstIdList& ids) {
			// 逐语句计算
			for (const auto& def : attr_defs) {
				if (def.is_class_attr) {
					// 类属性赋值
					Val val = def.expression(ctx);
					ctx.scene.cls_set_prop(def.cls_name, def.name, std::move(val));
				}
				else {
					// 实例属性
					for (const auto id : ids) {
						auto scope = ctx.enter_instance(InstanceHandle{ id, cls_name });
						Val val = def.expression(ctx);
						ctx.scene.inst_set_prop(ctx.curr_handle, def.name, std::move(val));
					}
				}
			}
		};

		if (target_cls_name == EvaluationContext::GLOBAL_TARGET) {
			for (const auto& def : attr_defs) {
				if (def.is_class_attr) {
					Val val = def.expression(ctx);
					ctx.scene.cls_set_prop(def.cls_name, def.name, std::move(val));
					continue;
				}

				// GLOBAL 直接遍历实例，同一实例只计算一次
				for (InstId id = 1; id <= ctx.scene.inst_count(); ++id) {
					auto scope = ctx.enter_instance(
						InstanceHandle{ id, std::nullopt });
					Val val = def.expression(ctx);
					ctx.scene.inst_set_prop(ctx.curr_handle, def.name, std::move(val));
				}
			}
			return;
		}

		ctx.scene.cls_create(target_cls_name);
		compute_attrs(target_cls_name, ctx.scene.cls_insts(target_cls_name));
	}
};

// ====================== GroupOperator =========================

/**
 * @brief 分组算子，从源类别中挑选实例创建新类别
 */
struct GroupOperator : SceneOperator {
	StrFunc new_cls_expr;
	StrFunc source_cls_expr;
	std::vector<BoolFunc> conditions;

	GroupOperator() : SceneOperator(OperatorKind::OP_GROUP) {}

	void apply(EvaluationContext& ctx) const override {
		auto source_cls_name = source_cls_expr(ctx);
		auto new_cls_name = new_cls_expr(ctx);

		if (!ctx.scene.cls_exists(source_cls_name)) {
			ctx.scene.cls_set_insts(new_cls_name, {});
			return;
		}

		Scene::InstIdList selected;
		for (const auto id : ctx.scene.cls_insts(source_cls_name)) {
			auto scope = ctx.enter_instance(InstanceHandle{ id, source_cls_name });
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(ctx);
			});
			if (all_pass) {
				selected.emplace_back(id);
			}
		}
		ctx.scene.cls_set_insts(new_cls_name, std::move(selected));
	}
};

// ====================== AppendOperator ========================

/**
 * @brief 追加算子，将源类别中满足条件的实例追加到目标类别
 */
struct AppendOperator : SceneOperator {
	StrFunc dest_cls_expr;
	StrFunc source_cls_expr;
	std::vector<BoolFunc> conditions;

	AppendOperator() : SceneOperator(OperatorKind::OP_APPEND) {}

	void apply(EvaluationContext& ctx) const override {
		auto dest_cls_name = dest_cls_expr(ctx);
		auto source_cls_name = source_cls_expr(ctx);

		if (!ctx.scene.cls_exists(source_cls_name)) {
			return;
		}

		Scene::InstIdList selected;
		for (const auto id : ctx.scene.cls_insts(source_cls_name)) {
			auto scope = ctx.enter_instance(InstanceHandle{ id, source_cls_name });
			bool all_pass = std::ranges::all_of(conditions, [&](const auto& cond) {
				return cond(ctx);
			});
			if (all_pass) {
				selected.emplace_back(id);
			}
		}
		for (const auto id : selected) {
			ctx.scene.cls_add_inst(dest_cls_name, id);
		}
	}
};

// ======================= SortOperator =========================

/**
 * @brief 对目标类别执行原地稳定排序
 * @details 每个实例的全部排序键在排序前仅求值一次；多个键按声明顺序进行字典序比较。
 *          所有键均相等时 stable_sort 保留实例原有顺序。
 */
struct SortOperator : SceneOperator {
	/**
	 * @brief 排序键及排序方向
	 */
	struct Key {
		ValFunc expression;
		bool descending = false;
	};

	std::vector<Key> keys;

	SortOperator() : SceneOperator(OperatorKind::OP_SORT) {}

	void apply(EvaluationContext& ctx) const override {
		const auto target_cls_name = target_cls_expr(ctx);

		auto sort_instances = [&](const std::string& cls_name) {
			auto ids = ctx.scene.cls_insts(cls_name);
			if (ids.size() < 2 || keys.empty()) {
				return;
			}

			// 装饰阶段：预先缓存每个实例的全部键，避免排序比较器重复执行 DSL 表达式。
			std::vector<std::vector<Val>> cached_keys(ids.size());
			for (std::size_t i = 0; i < ids.size(); ++i) {
				auto scope = ctx.enter_instance(InstanceHandle{ ids[i], cls_name });
				auto& values = cached_keys[i];
				values.reserve(keys.size());
				for (const auto& key : keys) {
					values.emplace_back(key.expression(ctx));
				}
			}

			// 仅排序下标，完成后一次性重排 ID，不移动 Instance。
			std::vector<std::size_t> order(ids.size());
			std::iota(order.begin(), order.end(), 0);
			std::stable_sort(order.begin(), order.end(), [&](std::size_t lhs, std::size_t rhs) {
				for (std::size_t key_index = 0; key_index < keys.size(); ++key_index) {
					const int comparison = compare_key_values(
						cached_keys[lhs][key_index], cached_keys[rhs][key_index]);
					if (comparison == 0) {
						continue;
					}
					return keys[key_index].descending ? comparison > 0 : comparison < 0;
				}
				return false;
			});

			Scene::InstIdList sorted;
			sorted.reserve(ids.size());
			for (const auto index : order) {
				sorted.emplace_back(ids[index]);
			}
			ctx.scene.cls_set_insts(cls_name, std::move(sorted));
		};

		if (target_cls_name == EvaluationContext::GLOBAL_TARGET) {
			for (const auto& cls_name : ctx.scene.cls_names()) {
				sort_instances(cls_name);
			}
			return;
		}

		// 不存在类别按空集合处理，排序为空操作。
		if (ctx.scene.cls_exists(target_cls_name)) {
			sort_instances(target_cls_name);
		}
	}

private:
	/**
	 * @brief 对排序键执行严格全序比较
	 * @return 小于返回 -1，相等返回 0，大于返回 1
	 * @note 数值排序不使用 Val 比较中的 epsilon，确保比较器满足严格弱序要求。
	 */
	static int compare_key_values(const Val& lhs, const Val& rhs) {
		if (!type_strict_equal(lhs.type(), rhs.type())) {
			throw PARuntimeError(std::format(
				"SORT key type mismatch: {} vs {}", type_name(lhs.type()), type_name(rhs.type())));
		}

		switch (lhs.type()) {
		using enum postanvil::Type;
		case T_NUM: {
			const double a = lhs.as_num();
			const double b = rhs.as_num();
			if (std::isnan(a) || std::isnan(b)) {
				throw PARuntimeError("SORT key cannot be NaN");
			}
			return a < b ? -1 : (a > b ? 1 : 0);
		}
		case T_STR: {
			const auto& a = std::get<std::string>(lhs.data);
			const auto& b = std::get<std::string>(rhs.data);
			return a < b ? -1 : (a > b ? 1 : 0);
		}
		case T_BOOL: {
			const bool a = lhs.as_bool();
			const bool b = rhs.as_bool();
			return a == b ? 0 : (a ? 1 : -1);
		}
		case T_INST:
			throw PARuntimeError("SORT does not support INST keys; sort by an instance property instead");
		default:
			throw PARuntimeError(std::format("SORT key has unsupported type {}", type_name(lhs.type())));
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
		Val val = initializer(ctx);
		ctx.scene.io_set(var_name, std::move(val));
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
		if (!ctx.scene.io_contains(local_name)) {
			throw PARuntimeError("Imported variable '" + local_name + "' not provided by host");
		}
		const auto& val = ctx.scene.io_value(local_name);
		if (!type_strict_equal(val.type(), var_type)) {
			throw PARuntimeError("Imported variable '" + local_name + "' type mismatch");
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
		Val result = expression(ctx);
		ctx.scene.io_set("__export__" + host_name, std::move(result));
	}
};

} // namespace postanvil
