/**
 * @file   scene.hpp
 * @brief  场景上下文定义，统一维护图像信息、类别关系和实例实体
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
#include <optional>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

namespace postanvil {

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
 * @details Scene 分别维护图像信息、类别到实例 ID 的关系和实例实体
 *          Instance 本身不保存类别；同一 ID 出现在多个类别时仍指向同一个 Instance
 */
class Scene {
public:
	// ===================== Type Alias =====================

	using SizeType			= std::size_t;
	using InstIdList		= std::vector<InstId>;
	using ClsNameList		= std::vector<std::string>;
	static constexpr std::string_view ALL_INST_CLASS = "ALL_INST";

private:
	using ClsInstMap		= detail::str_map<InstIdList>;
	using ClsPropsMap		= detail::str_map<detail::str_map<Val>>;
	using VarsMap			= detail::str_map<Val>;
	using InstPtrList		= std::vector<std::unique_ptr<Instance>>;

public:

	// ===================== Constructor =====================

	/**
	 * @brief 构造后处理场景，并在实例表第 0 项创建全局占位实例
	 *
	 * @param image_info	- 图像元信息
	 */
	explicit Scene(Image image_info) : m_img(std::move(image_info))
	{
		m_insts.emplace_back(
			std::make_unique<Instance>(0.0, 0.0, 0.0, 0.0, 0.0)
		);
		m_cls_insts.try_emplace(std::string(ALL_INST_CLASS));
	}

	/**
	 * @brief 深拷贝场景，Instance 逐项复制，副本拥有独立实例存储
	 *
	 * @param other	- 另一个场景对象
	 */
	Scene(const Scene& other)
		: m_img(other.m_img),
		  m_cls_insts(other.m_cls_insts),
		  m_cls_props(other.m_cls_props),
		  m_vars(other.m_vars)
	{
		m_insts.reserve(other.m_insts.size());
		for (const auto& instance : other.m_insts) {
			m_insts.emplace_back(std::make_unique<Instance>(*instance));
		}
	}

	Scene& operator=(const Scene& other) {
		if (this == &other) { return *this; }

		Scene copy(other);
		swap(copy);
		return *this;
	}

	Scene(Scene&&) noexcept = default;
	Scene& operator=(Scene&&) noexcept = default;

	/**
	 * @brief 交换两个场景的完整状态
	 *
	 * @param other	- 另一个场景对象
	 */
	void swap(Scene& other) noexcept {
		using std::swap;

		swap(m_img, other.m_img);
		swap(m_cls_insts, other.m_cls_insts);
		swap(m_cls_props, other.m_cls_props);
		swap(m_insts, other.m_insts);
		swap(m_vars, other.m_vars);
	}

	// ===================== Image =====================

	/**
	 * @brief 获取只读图像信息
	 */
	[[nodiscard]]
	const Image& img_info() const noexcept {
		return m_img;
	}

	/**
	 * @brief 替换图像信息
	 */
	void img_set(Image image_info) {
		m_img = std::move(image_info);
	}

	/**
	 * @brief 获取图像属性
	 *
	 * @param prop			- 属性名称
	 * @return Val			- 属性值
	 * @throw PARuntimeError	- 属性不存在时抛出
	 */
	[[nodiscard]]
	Val img_prop(std::string_view prop) const {
		if (prop == "W")		{ return m_img.width; }
		if (prop == "H")		{ return m_img.height; }
		if (prop == "PATH")	{ return m_img.path; }
		if (prop == "AREA")	{ return m_img.area(); }
		if (prop == "ASPECT")	{ return m_img.aspect(); }

		throw PARuntimeError(std::format("Unknown image property '{}'", prop));
	}

	// ===================== Instances =====================

	/**
	 * @brief 创建实例，为其分配稳定 ID 并取得所有权
	 * @details 创建实例会自动将稳定 ID 追加到内置 ALL_INST 类别；
	 *          其他类别关系由 cls_add_inst 单独维护
	 *
	 * @param instance		- 实例数据
	 * @return InstanceHandle	- 不带类别上下文的实例句柄
	 */
	InstanceHandle inst_add(Instance instance) {
		const auto id = m_insts.size();
		instance.set_id(id);
		m_insts.emplace_back(std::make_unique<Instance>(std::move(instance)));
		try {
			m_cls_insts.find(ALL_INST_CLASS)->second.emplace_back(id);
		}
		catch (...) {
			m_insts.pop_back();
			throw;
		}
		return InstanceHandle{ id, std::nullopt };
	}

	/**
	 * @brief 获取全局占位实例
	 * @details 占位实例固定存储在实例表第 0 项，不属于任何类别
	 */
	[[nodiscard]]
	const Instance& inst_dummy() const noexcept {
		return *m_insts.front();
	}

	/**
	 * @brief 按稳定 ID 获取只读实例
	 *
	 * @param id				- Scene 分配的实例 ID
	 * @return const Instance&	- 实例引用
	 * @throw PARuntimeError	- ID 为 0、越界或对应实例不存在时抛出
	 */
	[[nodiscard]]
	const Instance& inst_at(InstId id) const {
		inst_require(id);
		return *m_insts[id];
	}

	/**
	 * @brief 按稳定 ID 获取可写实例
	 *
	 * @param id				- Scene 分配的实例 ID
	 * @return Instance&		- 实例引用
	 * @throw PARuntimeError	- ID 为 0、越界或对应实例不存在时抛出
	 */
	[[nodiscard]]
	Instance& inst_at(InstId id) {
		inst_require(id);
		return *m_insts[id];
	}

	/**
	 * @brief 获取有效实例数量，不包含第 0 项占位实例
	 */
	[[nodiscard]]
	SizeType inst_count() const noexcept {
		return m_insts.size() - 1;
	}

	/**
	 * @brief 检查稳定 ID 是否指向有效实例
	 */
	[[nodiscard]]
	bool inst_exists(InstId id) const noexcept {
		return id != 0 && id < m_insts.size() && m_insts[id] != nullptr;
	}

	/**
	 * @brief 检查 DSL 数值是否表示有效实例 ID
	 */
	[[nodiscard]]
	bool inst_id_exists(double value) const noexcept {
		const auto id = inst_number(value);
		return id.has_value() && inst_exists(*id);
	}

	/**
	 * @brief 按 DSL 数值获取不带类别上下文的实例句柄
	 *
	 * @throw PARuntimeError	- 输入不是有效正整数或 ID 不存在时抛出
	 */
	[[nodiscard]]
	InstanceHandle inst_handle(double value) const {
		const auto id = inst_number_require(value, "Instance id");
		inst_require(id);
		return InstanceHandle{ id, std::nullopt };
	}

	/**
	 * @brief 获取实例属性
	 * @details CLS 和 INDEX 依赖句柄的类别上下文；ID 句柄访问这两个属性时会报错
	 *
	 * @param handle		- 实例句柄
	 * @param prop			- 属性名
	 * @return Val			- 属性值
	 * @throw PARuntimeError	- 实例、类别上下文或属性无效时抛出
	 */
	[[nodiscard]]
	Val inst_prop(const InstanceHandle& handle, std::string_view prop) const {
		const auto& self = inst_at(handle.id);

		if (prop == "CONF")		{ return self.conf(); }
		if (prop == "CLS")		{ return cls_from_handle(handle)->first; }
		if (prop == "ID")		{ return static_cast<double>(handle.id); }
		if (prop == "INDEX")	{ return static_cast<double>(cls_inst_index(handle)); }

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

		if (prop == "WN")		{ return self.wn(m_img.width); }
		if (prop == "HN")		{ return self.hn(m_img.height); }
		if (prop == "X1N")		{ return self.x1n(m_img.width); }
		if (prop == "X2N")		{ return self.x2n(m_img.width); }
		if (prop == "Y1N")		{ return self.y1n(m_img.height); }
		if (prop == "Y2N")		{ return self.y2n(m_img.height); }
		if (prop == "CXN")		{ return self.cxn(m_img.width); }
		if (prop == "CYN")		{ return self.cyn(m_img.height); }
		if (prop == "AREAN")	{ return self.arean(m_img.width, m_img.height); }

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
	void inst_set_prop(const InstanceHandle& handle, std::string_view prop, Val value) {
		inst_at(handle.id).set_prop(std::string(prop), std::move(value));
	}

	// ===================== Classes =====================

	/**
	 * @brief 创建空类别
	 *
	 * @return bool	- 新创建返回 true，已存在返回 false
	 */
	bool cls_create(std::string_view cls_name) {
		return m_cls_insts.try_emplace(cls_normalize(cls_name)).second;
	}

	/**
	 * @brief 检查类别是否存在
	 */
	[[nodiscard]]
	bool cls_exists(std::string_view cls_name) const {
		return cls_find(cls_name) != m_cls_insts.end();
	}

	/**
	 * @brief 获取所有类别名称
	 * @details 返回结果按名称排序，不包含内置 ALL_INST 类别，
	 *          也不暴露内部类别容器
	 */
	[[nodiscard]]
	ClsNameList cls_names() const {
		ClsNameList names;
		names.reserve(m_cls_insts.size());
		for (const auto& [cls_name, _] : m_cls_insts) {
			if (cls_name == ALL_INST_CLASS) { continue; }
			names.emplace_back(cls_name);
		}
		std::ranges::sort(names);
		return names;
	}

	/**
	 * @brief 获取指定类别的实例 ID 列表
	 *
	 * @throw PARuntimeError	- 类别不存在时抛出
	 */
	[[nodiscard]]
	const InstIdList& cls_insts(std::string_view cls_name) const {
		if (const auto it = cls_find(cls_name); it != m_cls_insts.end()) {
			return it->second;
		}
		throw PARuntimeError(std::format("Class '{}' not found in scene", cls_name));
	}

	/**
	 * @brief 获取指定类别的实例数量
	 * @return SizeType	- 类别不存在时返回 0
	 */
	[[nodiscard]]
	SizeType cls_inst_count(std::string_view cls_name) const {
		if (const auto it = cls_find(cls_name); it != m_cls_insts.end()) {
			return it->second.size();
		}
		return 0;
	}

	/**
	 * @brief 替换类别中的全部实例 ID，保留首次出现顺序并移除重复 ID
	 */
	void cls_set_insts(std::string_view cls_name, InstIdList ids) {
		InstIdList unique_ids;
		unique_ids.reserve(ids.size());

		std::unordered_set<InstId> visited;
		visited.reserve(ids.size());

		for (const auto id : ids) {
			inst_require(id);
			if (visited.emplace(id).second) {
				unique_ids.emplace_back(id);
			}
		}

		m_cls_insts.insert_or_assign(cls_normalize(cls_name), std::move(unique_ids));
	}

	/**
	 * @brief 将已有实例加入类别
	 *
	 * @return bool	- 成功加入返回 true，类别已包含该 ID 时返回 false
	 */
	bool cls_add_inst(std::string_view cls_name, InstId id) {
		inst_require(id);
		auto [cls_it, cls_inserted] = m_cls_insts.try_emplace(cls_normalize(cls_name));
		auto& ids = cls_it->second;

		if (std::ranges::find(ids, id) != ids.end()) { return false; }

		try {
			ids.emplace_back(id);
		}
		catch (...) {
			if (cls_inserted) { m_cls_insts.erase(cls_it); }
			throw;
		}

		return true;
	}

	/**
	 * @brief 按类别和 1-based 实时索引获取实例句柄
	 *
	 * @throw PARuntimeError	- 索引非法、越界或类别不存在时抛出
	 */
	[[nodiscard]]
	InstanceHandle cls_inst_at(std::string_view cls_name, double value) const {
		const auto index = inst_number_require(value, "Instance index");
		const auto cls_it = cls_find(cls_name);
		const auto count = cls_it == m_cls_insts.end() ? SizeType{ 0 } : cls_it->second.size();

		if (index > count) {
			throw PARuntimeError(std::format(
				"Instance index {} out of range for class '{}' (count {})",
				index, cls_name, count));
		}

		return InstanceHandle{ cls_it->second[index - 1], cls_it->first };
	}

	/**
	 * @brief 检查类别中是否存在指定 1-based 实时索引
	 * @details 非法数值、不存在类别和越界索引均返回 false
	 */
	[[nodiscard]]
	bool cls_inst_exists(std::string_view cls_name, double value) const {
		const auto index = inst_number(value);
		if (!index.has_value()) { return false; }

		const auto cls_it = cls_find(cls_name);
		return cls_it != m_cls_insts.end() && *index <= cls_it->second.size();
	}

	/**
	 * @brief 获取句柄在类别上下文中的 1-based 实时索引
	 *
	 * @throw PARuntimeError	- 句柄没有类别上下文、类别不存在或 ID 不属于类别时抛出
	 */
	[[nodiscard]]
	SizeType cls_inst_index(const InstanceHandle& handle) const {
		inst_require(handle.id);
		const auto cls_it = cls_from_handle(handle);
		const auto position = std::ranges::find(cls_it->second, handle.id);

		if (position == cls_it->second.end()) {
			throw PARuntimeError(std::format(
				"Instance id {} is not a member of class '{}'", handle.id, cls_it->first));
		}

		return static_cast<SizeType>(
			std::distance(cls_it->second.begin(), position)) + 1;
	}

	/**
	 * @brief 获取类别属性
	 *
	 * @throw PARuntimeError	- 类别或属性不存在时抛出
	 */
	[[nodiscard]]
	Val cls_prop(std::string_view cls_name, std::string_view prop) const {
		const auto cls_it = cls_find(cls_name);

		if (prop == "COUNT") {
			return static_cast<double>(
				cls_it == m_cls_insts.end() ? 0 : cls_it->second.size());
		}
		if (cls_it == m_cls_insts.end()) {
			throw PARuntimeError(std::format("Class '{}' not found in scene", cls_name));
		}

		if (const auto props_it = m_cls_props.find(cls_it->first);
			props_it != m_cls_props.end()) {
			if (const auto prop_it = props_it->second.find(prop);
				prop_it != props_it->second.end()) {
				return prop_it->second;
			}
		}

		throw PARuntimeError(std::format(
			"Unknown property '{}' for class '{}'", prop, cls_it->first));
	}

	/**
	 * @brief 设置类别属性，不存在类别会同步创建
	 */
	void cls_set_prop(std::string_view cls_name, std::string_view prop, Val value) {
		auto normalized = cls_normalize(cls_name);
		m_cls_insts.try_emplace(normalized);
		m_cls_props[std::move(normalized)].insert_or_assign(
			std::string(prop), std::move(value));
	}

	// ===================== Host IO =====================

	/**
	 * @brief 向场景中导入宿主变量
	 */
	Scene& io_import(std::string_view name, Val value) {
		m_vars.insert_or_assign(std::string(name), std::move(value));
		return *this;
	}

	/**
	 * @brief 获取由 DSL 导出的变量
	 *
	 * @throw PARuntimeError	- 导出变量不存在时抛出
	 */
	[[nodiscard]]
	Val io_export(std::string_view name) const {
		std::string key = "__export__";
		key.append(name);

		if (const auto it = m_vars.find(key); it != m_vars.end()) {
			return it->second;
		}
		throw PARuntimeError(std::format("Exported value '{}' not found", name));
	}

	[[nodiscard]]
	bool io_contains(std::string_view name) const {
		return m_vars.contains(name);
	}

	[[nodiscard]]
	const Val& io_value(std::string_view name) const {
		if (const auto it = m_vars.find(name); it != m_vars.end()) {
			return it->second;
		}
		throw PARuntimeError(std::format("Variable '{}' not found", name));
	}

	void io_set(std::string name, Val value) {
		m_vars.insert_or_assign(std::move(name), std::move(value));
	}

private:
	// ===================== Class Helpers =====================

	/**
	 * @brief 校验并规范化类别名
	 */
	[[nodiscard]]
	static std::string cls_normalize(std::string_view cls_name) {
		if (cls_name.empty()) {
			throw PARuntimeError("Class name cannot be empty");
		}

		std::string normalized(cls_name);
		utils::to_upper_inplace(normalized);
		return normalized;
	}

	/**
	 * @brief 查找类别，已规范化名称不会产生临时字符串
	 */
	[[nodiscard]]
	ClsInstMap::const_iterator cls_find(std::string_view cls_name) const {
		if (cls_name.empty()) { return m_cls_insts.end(); }
		if (const auto it = m_cls_insts.find(cls_name); it != m_cls_insts.end()) {
			return it;
		}

		const bool contains_lowercase = std::ranges::any_of(cls_name, [](char ch) {
			return ch >= 'a' && ch <= 'z';
		});
		if (!contains_lowercase) { return m_cls_insts.end(); }
		return m_cls_insts.find(cls_normalize(cls_name));
	}

	/**
	 * @brief 获取句柄的类别迭代器
	 */
	[[nodiscard]]
	ClsInstMap::const_iterator cls_from_handle(const InstanceHandle& handle) const {
		if (!handle.cls_name.has_value()) {
			throw PARuntimeError(
				"Instance handle has no class context; CLS and INDEX are unavailable");
		}

		const auto cls_it = cls_find(*handle.cls_name);
		if (cls_it == m_cls_insts.end()) {
			throw PARuntimeError(std::format(
				"Class '{}' not found in scene", *handle.cls_name));
		}
		return cls_it;
	}

	// ===================== Instance Helpers =====================

	/**
	 * @brief 要求实例 ID 有效
	 */
	void inst_require(InstId id) const {
		if (!inst_exists(id)) {
			throw PARuntimeError(std::format("Instance id {} not found", id));
		}
	}

	/**
	 * @brief 尝试将 DSL 数值转换为正整数 ID 或索引
	 */
	[[nodiscard]]
	static std::optional<InstId> inst_number(double value) noexcept {
		constexpr double max_exact_double_integer = 9'007'199'254'740'991.0;
		constexpr auto max_inst_id = std::numeric_limits<InstId>::max();
		constexpr auto max_acceptable = std::min(
			max_exact_double_integer, static_cast<double>(max_inst_id));

		const bool is_valid = std::isfinite(value)
			&& value >= 1.0
			&& std::trunc(value) == value
			&& value <= max_acceptable;
		if (!is_valid) { return std::nullopt; }
		return static_cast<InstId>(value);
	}

	/**
	 * @brief 将 DSL 数值转换为正整数 ID 或索引
	 */
	[[nodiscard]]
	static InstId inst_number_require(double value, std::string_view label) {
		if (const auto result = inst_number(value)) { return *result; }
		throw PARuntimeError(std::format(
			"{} must be a positive integer, got {}", label, value));
	}

	// ===================== Data =====================

	Image m_img;				//< 图像信息
	ClsInstMap m_cls_insts;		//< 类别到实例 ID 列表的关系
	ClsPropsMap m_cls_props;	//< 类别动态属性
	InstPtrList m_insts;		//< 实例所有权表，第 0 项为 dummy
	VarsMap m_vars;				//< 宿主导入、DSL 全局变量和导出结果
};

} // namespace postanvil
