/**
 * @file   scene.hpp
 * @brief  场景上下文定义，包含图像信息、实例存储、类别索引、全局变量和类别属性
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include "instance.hpp"
#include "type.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <limits>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

namespace postanvil {

struct FilterOperator;
struct SortOperator;

/**
 * @brief 图像元信息
 */
struct Image {
	double width		= 0.0;	//< 图像宽度，像素单位
	double height		= 0.0;	//< 图像高度，像素单位
	std::string path	= "";	//< 图像文件路径

	[[nodiscard]] double w() const noexcept			{ return width; }
	[[nodiscard]] double h() const noexcept			{ return height; }
	[[nodiscard]] double area() const noexcept		{ return width * height; }
	[[nodiscard]] double aspect() const noexcept	{ return height == 0.0 ? 0.0 : width / height; }
};

/**
 * @brief DSL 执行的完整场景上下文
 * @details Scene 统一持有所有 Instance，并单独维护 cls_name 到 InstanceId 列表的类别索引。
 *          Instance 本身不保存类别；同一 ID 出现在多个类别时仍指向同一个 Instance。
 */
struct Scene {

	// ===================== Type Alias =====================

	using InstanceIds	= std::vector<InstanceId>;
	using ClassIndex		= detail::str_map<InstanceIds>;
	using ClassProps		= detail::str_map<detail::str_map<Val>>;
	using Variables			= detail::str_map<Val>;

	// ===================== Constructor =====================

	/**
	 * @brief 构造后处理场景，并在实例表第 0 项创建全局占位实例
	 *
	 * @param image_info	- 图像元信息
	 */
	explicit Scene(Image image_info)
		: image(std::move(image_info))
	{
		m_instances.emplace_back(
			std::make_unique<Instance>(0.0, 0.0, 0.0, 0.0, 0.0));
	}

	/**
	 * @brief 深拷贝场景
	 * @details 类别索引和属性按值复制，Instance 逐项复制，副本拥有独立实例存储。
	 */
	Scene(const Scene& other)
		: image(other.image),
		  variables(other.variables),
		  class_props(other.class_props),
		  m_class_index(other.m_class_index)
	{
		m_instances.reserve(other.m_instances.size());
		for (const auto& instance : other.m_instances) {
			m_instances.emplace_back(std::make_unique<Instance>(*instance));
		}
	}

	Scene(Scene&&) noexcept = default;

	Scene& operator=(const Scene& other) {
		if (this == &other) { return *this; }

		Scene copy(other);
		swap(copy);
		return *this;
	}

	Scene& operator=(Scene&&) noexcept = default;

	/**
	 * @brief 交换两个场景的完整状态
	 */
	void swap(Scene& other) noexcept {
		using std::swap;

		swap(image, other.image);
		swap(variables, other.variables);
		swap(class_props, other.class_props);
		swap(m_class_index, other.m_class_index);
		swap(m_instances, other.m_instances);
	}

	// ===================== Instances =====================

	/**
	 * @brief 获取全局占位实例
	 * @details 占位实例固定存储在实例表第 0 项，不属于任何类别。
	 */
	[[nodiscard]] const Instance& inst_dummy() const noexcept {
		return *m_instances.front();
	}

	/**
	 * @brief 按稳定 ID 获取只读实例
	 *
	 * @param id				- Scene 分配的实例 ID
	 * @return const Instance&	- 实例引用
	 * @throw PARuntimeError	- ID 为 0、越界或对应实例不存在时抛出
	 */
	[[nodiscard]] const Instance& inst(InstanceId id) const {
		validate_inst_id(id);
		return *m_instances[id];
	}

	/**
	 * @brief 按稳定 ID 获取可写实例
	 *
	 * @param id			- Scene 分配的实例 ID
	 * @return Instance&	- 实例引用
	 * @throw PARuntimeError	- ID 为 0、越界或对应实例不存在时抛出
	 */
	[[nodiscard]] Instance& inst(InstanceId id) {
		validate_inst_id(id);
		return *m_instances[id];
	}

	/**
	 * @brief 获取有效实例数量，不包含第 0 项占位实例
	 */
	[[nodiscard]] std::size_t inst_count() const noexcept {
		return m_instances.size() - 1;
	}

	/**
	 * @brief 创建实例并加入指定类别
	 * @details Scene 分配稳定 ID 并取得实例所有权；类别只记录该 ID，不复制 Instance。
	 *
	 * @param cls_name	- 目标类别名
	 * @param instance	- 实例数据
	 * @return InstanceHandle 带该类别访问上下文的轻量句柄
	 */
	InstanceHandle add(std::string_view cls_name, Instance instance) {
		auto normalized_cls_name = normalize_cls_name(cls_name);
		const auto id = m_instances.size();
		instance.set_id(id);

		auto stored = std::make_unique<Instance>(std::move(instance));
		auto [class_it, class_inserted] =
			m_class_index.try_emplace(std::move(normalized_cls_name));
		auto& ids = class_it->second;

		try {
			m_instances.emplace_back(std::move(stored));
			ids.emplace_back(id);
		}
		catch (...) {
			if (m_instances.size() > id) { m_instances.pop_back(); }
			if (class_inserted) { m_class_index.erase(class_it); }
			throw;
		}

		return InstanceHandle{ id, class_it->first };
	}

	/**
	 * @brief 用指定 ID 列表替换类别内容
	 * @details 所有 ID 必须已存在；保留首次出现顺序并移除重复 ID，不复制 Instance。
	 *
	 * @param cls_name	- 目标类别名
	 * @param ids		- 新的实例 ID 列表
	 */
	void replace_class(std::string_view cls_name, InstanceIds ids) {
		auto normalized_cls_name = normalize_cls_name(cls_name);

		InstanceIds unique_ids;
		unique_ids.reserve(ids.size());

		std::unordered_set<InstanceId> visited;
		visited.reserve(ids.size());

		for (const auto id : ids) {
			validate_inst_id(id);
			if (visited.emplace(id).second) { unique_ids.emplace_back(id); }
		}

		m_class_index.insert_or_assign(
			std::move(normalized_cls_name), std::move(unique_ids));
	}

	/**
	 * @brief 将已有实例加入指定类别
	 * @details 仅增加类别到 ID 的关系，不复制或移动 Instance。
	 *
	 * @param cls_name	- 目标类别名
	 * @param id		- 已存在的实例 ID
	 * @return bool 成功加入返回 true，该类别已包含此 ID 时返回 false
	 */
	bool append_to_class(std::string_view cls_name, InstanceId id) {
		validate_inst_id(id);
		auto normalized_cls_name = normalize_cls_name(cls_name);
		auto [class_it, class_inserted] =
			m_class_index.try_emplace(std::move(normalized_cls_name));
		auto& ids = class_it->second;

		if (std::ranges::find(ids, id) != ids.end()) { return false; }

		try {
			ids.emplace_back(id);
		}
		catch (...) {
			if (class_inserted) { m_class_index.erase(class_it); }
			throw;
		}

		return true;
	}

	/**
	 * @brief 确保指定类别存在；已存在时不修改其内容
	 */
	void ensure_class(std::string_view cls_name) {
		m_class_index.try_emplace(normalize_cls_name(cls_name));
	}

	/**
	 * @brief 获取指定类别的实例 ID 列表
	 *
	 * @throw PARuntimeError	- 类别不存在时抛出
	 */
	[[nodiscard]] const InstanceIds& get_inst_ids(std::string_view cls_name) const {
		if (const auto it = find_class(cls_name); it != m_class_index.end()) {
			return it->second;
		}

		throw PARuntimeError(std::string("Class '") + std::string(cls_name) + "' not found in scene");
	}

	/**
	 * @brief 获取指定类别的实例数量
	 * @return std::size_t 类别不存在时返回 0
	 */
	[[nodiscard]] std::size_t get_inst_count(std::string_view cls_name) const {
		if (const auto it = find_class(cls_name); it != m_class_index.end()) {
			return it->second.size();
		}

		return 0;
	}

	/**
	 * @brief 获取只读类别索引
	 */
	[[nodiscard]] const ClassIndex& class_index() const noexcept {
		return m_class_index;
	}

	// ===================== Instance Handle =====================

	/**
	 * @brief 按稳定 ID 获取实例句柄
	 * @details ID 本身不携带类别信息，因此返回的句柄没有类别上下文。
	 *
	 * @throw PARuntimeError	- 输入不是有效正整数或 ID 不存在时抛出
	 */
	[[nodiscard]] InstanceHandle get_inst_by_id(double value) const {
		const auto id = checked_positive_integer(value, "Instance id");
		validate_inst_id(id);
		return InstanceHandle{ id, std::nullopt };
	}

	/**
	 * @brief 按类别和 1-based 实时索引获取实例句柄
	 *
	 * @param cls_name	- 类别名
	 * @param value		- 类别内的 1-based 索引
	 * @throw PARuntimeError	- 索引非法、越界或类别不存在时抛出
	 */
	[[nodiscard]] InstanceHandle get_inst_by_index	(std::string_view cls_name,
												 double value) const
	{
		const auto index = checked_positive_integer(value, "Instance index");
		const auto class_it = find_class(cls_name);
		const auto count = class_it == m_class_index.end()
			? std::size_t{ 0 }
			: class_it->second.size();

		if (index > count) {
			throw PARuntimeError(std::string("Instance index ") + std::to_string(index) +
				" out of range for class '" + std::string(cls_name) + "' (count " +
				std::to_string(count) + ")");
		}

		return InstanceHandle{ class_it->second[index - 1], class_it->first };
	}

	/**
	 * @brief 获取句柄在其类别上下文中的 1-based 实时索引
	 *
	 * @throw PARuntimeError	- 句柄没有类别上下文、类别不存在或 ID 不属于该类别时抛出
	 */
	[[nodiscard]] std::size_t index_of_class(const InstanceHandle& handle) const {
		validate_inst_id(handle.id);
		const auto class_it = get_handle_class(handle);

		const auto position = std::ranges::find(class_it->second, handle.id);
		if (position == class_it->second.end()) {
			throw PARuntimeError(std::string("Instance id ") + std::to_string(handle.id) +
				" is not a member of class '" + class_it->first + "'");
		}

		return static_cast<std::size_t>(
			std::distance(class_it->second.begin(), position)) + 1;
	}

	/**
	 * @brief 获取实例属性
	 * @details CLS 和 INDEX 依赖句柄的类别上下文；ID 句柄访问这两个属性时会报错。
	 *
	 * @param handle		- 实例句柄
	 * @param prop			- 属性名
	 * @return Val			- 属性值
	 * @throw PARuntimeError	- 实例、类别上下文或属性无效时抛出
	 */
	[[nodiscard]] Val get_inst_prop	(const InstanceHandle& handle,
								 std::string_view prop) const
	{
		validate_inst_id(handle.id);
		const auto& self = inst(handle.id);

		if (prop == "CONF")		{ return self.conf(); }
		if (prop == "CLS")		{ return get_handle_class(handle)->first; }
		if (prop == "ID")		{ return static_cast<double>(handle.id); }
		if (prop == "INDEX")	{ return static_cast<double>(index_of_class(handle)); }

		if (prop == "W")		{ return self.w(); }
		if (prop == "H")		{ return self.h(); }
		if (prop == "X1")		{ return self.x1(); }
		if (prop == "Y1")		{ return self.y1(); }
		if (prop == "X2")		{ return self.x2(); }
		if (prop == "Y2")		{ return self.y2(); }
		if (prop == "CX")		{ return self.cx(); }
		if (prop == "CY")		{ return self.cy(); }
		if (prop == "AREA")	{ return self.area(); }
		if (prop == "ASPECT")	{ return self.aspect(); }

		if (prop == "WN")		{ return self.wn(image.width); }
		if (prop == "HN")		{ return self.hn(image.height); }
		if (prop == "X1N")		{ return self.x1n(image.width); }
		if (prop == "X2N")		{ return self.x2n(image.width); }
		if (prop == "Y1N")		{ return self.y1n(image.height); }
		if (prop == "Y2N")		{ return self.y2n(image.height); }
		if (prop == "CXN")		{ return self.cxn(image.width); }
		if (prop == "CYN")		{ return self.cyn(image.height); }
		if (prop == "AREAN")	{ return self.arean(image.width, image.height); }

		return self.get_prop(std::string(prop));
	}

	/**
	 * @brief 设置实例属性
	 *
	 * @param handle		- 实例句柄
	 * @param prop			- 属性名
	 * @param value			- 属性值
	 * @throw PARuntimeError	- 实例不存在或属性不可写时抛出
	 */
	void set_inst_prop	(const InstanceHandle& handle,
						 std::string_view prop,
						 Val value)
	{
		validate_inst_id(handle.id);
		inst(handle.id).set_prop(std::string(prop), std::move(value));
	}

	// ===================== Image =====================

	/**
	 * @brief 获取当前场景下图像的指定属性值
	 *
	 * @param prop			- 属性名称
	 * @return Val			- 属性值
	 * @throw PARuntimeError	- 属性不存在时抛出
	 */
	[[nodiscard]] Val get_img_prop(std::string_view prop) const {
		if (prop == "W")		{ return image.width; }
		if (prop == "H")		{ return image.height; }
		if (prop == "PATH")	{ return image.path; }
		if (prop == "AREA")	{ return image.area(); }
		if (prop == "ASPECT")	{ return image.aspect(); }

		throw PARuntimeError(std::string("Unknown image property '") + std::string(prop) + "'");
	}

	// ===================== Class =====================

	/**
	 * @brief 获取当前场景下某类别的指定属性值
	 *
	 * @param cls_name		- 类别名称
	 * @param prop			- 属性名称
	 * @return Val			- 属性值
	 * @throw PARuntimeError	- 类别或属性不存在时抛出
	 */
	[[nodiscard]] Val get_cls_prop	(std::string_view cls_name,
								std::string_view prop) const
	{
		const auto class_it = find_class(cls_name);

		if (prop == "COUNT") {
			return static_cast<double>(
				class_it == m_class_index.end() ? 0 : class_it->second.size());
		}

		if (class_it == m_class_index.end()) {
			throw PARuntimeError(std::string("Class '") + std::string(cls_name) + "' not found in scene");
		}

		if (const auto props_it = class_props.find(class_it->first);
			props_it != class_props.end()) {
			if (const auto prop_it = props_it->second.find(prop);
				prop_it != props_it->second.end()) {
				return prop_it->second;
			}
		}

		throw PARuntimeError(std::string("Unknown property '") + std::string(prop) +
			"' for class '" + class_it->first + "'");
	}

	// ===================== Import / Export =====================

	/**
	 * @brief 向场景中导入预设外部变量
	 *
	 * @param local_name	- DSL 内使用的变量名
	 * @param value		- 预设变量值
	 * @return Scene& 场景自身引用，便于链式调用
	 */
	Scene& add_import(std::string_view local_name, Val value) {
		variables.insert_or_assign(std::string(local_name), std::move(value));
		return *this;
	}

	/**
	 * @brief 获取由 DSL 导出的变量
	 *
	 * @param host_name		- 宿主端变量名
	 * @return Val			- 导出值
	 * @throw PARuntimeError	- 导出变量不存在时抛出
	 */
	[[nodiscard]] Val get_export(std::string_view host_name) const {
		std::string key = "__export__";
		key.append(host_name);

		if (const auto it = variables.find(key); it != variables.end()) {
			return it->second;
		}

		throw PARuntimeError(std::format(
			"Exported value '{}' not found", host_name));
	}

public:
	Image image;					//< 图像信息
	Variables variables;		//< 全局变量，包含导入的宿主变量
	ClassProps class_props;		//< 类别级动态属性

private:
	/**
	 * @brief 校验并规范化类别名
	 * @details 类别名统一转换为大写，保证创建、查询和类别操作使用同一键值。
	 */
	[[nodiscard]] static std::string normalize_cls_name(std::string_view cls_name) {
		if (cls_name.empty()) {
			throw PARuntimeError("Class name cannot be empty");
		}

		std::string normalized_cls_name(cls_name);
		utils::to_upper_inplace(normalized_cls_name);
		return normalized_cls_name;
	}

	/**
	 * @brief 查找类别，已规范化名称使用透明查找且不产生临时 std::string
	 * @details 仅当直接查找失败且名称含小写 ASCII 字符时才创建大写副本再次查找。
	 */
	[[nodiscard]] ClassIndex::const_iterator find_class(std::string_view cls_name) const {
		if (cls_name.empty()) {
			throw PARuntimeError("Class name cannot be empty");
		}

		if (const auto it = m_class_index.find(cls_name); it != m_class_index.end()) {
			return it;
		}

		const bool contains_lowercase = std::ranges::any_of(cls_name, [](char ch) {
			return ch >= 'a' && ch <= 'z';
		});
		if (!contains_lowercase) { return m_class_index.end(); }

		return m_class_index.find(normalize_cls_name(cls_name));
	}

	/**
	 * @brief 检查实例 ID 是否指向有效的非占位实例
	 */
	void validate_inst_id(InstanceId id) const {
		if (id == 0 || id >= m_instances.size() || !m_instances[id]) {
			throw PARuntimeError(std::format("Instance id {} not found", id));
		}
	}

	/**
	 * @brief 将 DSL 数值校验并转换为实例 ID 或类别索引
	 *
	 * @param value	- 待转换数值
	 * @param label	- 错误信息中的参数名称
	 */
	[[nodiscard]] static InstanceId checked_positive_integer	(double value,
														 std::string_view label)
	{
		constexpr double max_exact_double_integer = 9'007'199'254'740'991.0;
		constexpr auto max_instance_id = std::numeric_limits<InstanceId>::max();
		constexpr auto max_acceptable = std::min(
			max_exact_double_integer, static_cast<double>(max_instance_id));

		const bool is_valid = std::isfinite(value)
			&& value >= 1.0
			&& std::trunc(value) == value
			&& value <= max_acceptable;

		if (!is_valid) {
			throw PARuntimeError(std::format(
				"{} must be a positive integer, got {}", label, value));
		}

		return static_cast<InstanceId>(value);
	}

	/**
	 * @brief 获取句柄所指向的类别
	 * @throw PARuntimeError	- 句柄没有类别上下文或类别不存在时抛出
	 */
	[[nodiscard]] ClassIndex::const_iterator
	get_handle_class					(const InstanceHandle& handle) const
	{
		if (!handle.cls_name.has_value()) {
			throw PARuntimeError(
				"Instance handle has no class context; CLS and INDEX are unavailable");
		}

		const auto class_it = find_class(*handle.cls_name);
		if (class_it == m_class_index.end()) {
			throw PARuntimeError(std::format(
				"Class '{}' not found in scene", *handle.cls_name));
		}

		return class_it;
	}

	ClassIndex m_class_index;						//< 类别名到实例 ID 列表的映射
	std::vector<std::unique_ptr<Instance>> m_instances;	//< 实例所有权表，第 0 项为 dummy

	friend struct FilterOperator;
	friend struct SortOperator;
};

} // namespace postanvil
