/**
 * @file   scene.hpp
 * @brief  场景上下文定义，包含图像信息、实例集合、全局变量和类别属性
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include "type.hpp"
#include "instance.hpp"

#include <cmath>
#include <cstdint>
#include <format>
#include <limits>

namespace postanvil {

/**
 * @brief 图像元信息
 */
struct Image {
	double width		= 0;	// 图像宽度，像素单位
	double height		= 0;	// 图像高度，像素单位
	std::string path	= "";	// 图像文件路径

	double w()		const		{ return width; }
	double h()		const		{ return height; }
	double area()	const		{ return width * height; }
	double aspect()	const		{ return width / height; }
};

/**
 * @brief DSL 执行的完整场景上下文
 * @details 包含图像信息、按类别组织的实例列表、全局变量以及类别级自定义属性
 */
struct Scene {
	
	// ===================== Type Alias =====================
	
	using Objects = detail::str_map<Instances>;
	using ClassProps = detail::str_map<detail::str_map<Val>>;
	using Variables = detail::str_map<Val>;

	// ===================== Constructor =====================

	/**
	 * @brief 构造后处理初始场景
	 * @param img			- 图像元信息
	 * @param instances		- 初始实例列表
	 */
	explicit Scene(const Image& img, const Instances& instances = {})
		: image(img)
	{
		this->add(instances);
	}

	/**
	 * @brief 构造占位实例的静态工厂方法，尝试通过 get_instance_prop 访问占位实例将会报错
	 *
	 * @return Instance		- dummy 实例
	 */
	static Instance make_dummy() {
		return Instance("__DUMMY", 0, 0, 0, 0, 0);
	}

	// ===================== Instances =====================

	/**
	 * @brief 向场景中添加单个实例
	 * 
	 * @param inst			- 待添加的实例
	 * @return Scene&		- 场景自身的引用，便于链式调用
	 */
	Scene& add(const Instance& inst) {
		Instance stored = inst;
		stored.set_id(m_next_instance_id++);
		auto& instances = objects[stored.cls()];
		stored.set_index(instances.size() + 1);
		instances.push_back(std::move(stored));
		return *this;
	}

	/**
	 * @brief 向场景中添加多个实例
	 * 
	 * @param instances		- 实例列表
	 * @return Scene&		- 场景自身的引用，便于链式调用
	 */
	Scene& add(const std::vector<Instance>& instances) {
		for (const auto& inst : instances) {
			add(inst);
		}
		return *this;
	}

	/** @brief 用保留逻辑 id 的实例副本替换一个派生类别，并重建实时索引。 */
	void replace_class(const std::string& class_name, Instances instances) {
		for (std::size_t i = 0; i < instances.size(); ++i) {
			instances[i].set_index(i + 1);
		}
		objects[class_name] = std::move(instances);
	}

	/** @brief 向类别追加一个实例副本；保留 id，并设置其新类别索引。 */
	void append_to_class(const std::string& class_name, const Instance& inst) {
		auto& instances = objects[class_name];
		Instance stored = inst;
		stored.set_index(instances.size() + 1);
		instances.push_back(std::move(stored));
	}

	/** @brief 在过滤或重排后重建类别内的 1-based 实时索引。 */
	void reindex_class(const std::string& class_name) {
		auto it = objects.find(class_name);
		if (it == objects.end()) return;
		for (std::size_t i = 0; i < it->second.size(); ++i) {
			it->second[i].set_index(i + 1);
		}
	}

	/** @brief 按 Scene 分配的稳定 id 获取当前实例快照。 */
	const Instance& get_inst_by_id(double value) const {
		const auto id = checked_positive_integer(value, "Instance id");

		// 优先返回原始类别中的逻辑实例，避免派生类别副本依赖哈希遍历顺序。
		for (const auto& [class_name, instances] : objects) {
			for (const auto& inst : instances) {
				if (inst.id() == id && inst.cls() == class_name) return inst;
			}
		}
		for (const auto& [_, instances] : objects) {
			for (const auto& inst : instances) {
				if (inst.id() == id) return inst;
			}
		}
		throw RuntimeError(std::format("Instance id {} not found", id));
	}

	/** @brief 按类别和 1-based 实时索引获取当前实例快照。 */
	const Instance& get_inst_by_index(const std::string& class_name, double value) const {
		const auto index = checked_positive_integer(value, "Instance index");
		auto it = objects.find(class_name);
		if (it == objects.end() || index > it->second.size()) {
			throw RuntimeError(std::format(
				"Instance index {} out of range for class '{}' (count {})",
				index, class_name, it == objects.end() ? 0 : it->second.size()));
		}
		return it->second[index - 1];
	}

	/**
	 * @brief 获取当前场景下某实例的指定属性值
	 * 
	 * @param inst			- 实例
	 * @param prop			- 属性
	 * @return Val			- 属性值
	 * @throw RuntimeError	- 实例非法或属性不存在时抛出
	 */
	Val get_inst_prop(const Instance& inst, const std::string& prop) const {
		// 实例非法
		if (inst.cls() == "__DUMMY") {
			throw RuntimeError("Try to access a dummy instance by self.*");
		}

		if (prop == "CONF")   return inst.conf();
		if (prop == "CLS")    return inst.cls();
		if (prop == "ID")     return static_cast<double>(inst.id());
		if (prop == "INDEX")  return static_cast<double>(inst.index());

		if (prop == "W")      return inst.w();
		if (prop == "H")      return inst.h();
		if (prop == "X1")     return inst.x1();
		if (prop == "Y1")     return inst.y1();
		if (prop == "X2")     return inst.x2();
		if (prop == "Y2")     return inst.y2();
		if (prop == "CX")     return inst.cx();
		if (prop == "CY")     return inst.cy();
		if (prop == "AREA")   return inst.area();
		if (prop == "ASPECT") return inst.aspect();

		if (prop == "WN")      return inst.wn(image.width);
		if (prop == "HN")      return inst.hn(image.height);
		if (prop == "X1N")     return inst.x1n(image.width);
		if (prop == "X2N")     return inst.x2n(image.width);
		if (prop == "Y1N")     return inst.y1n(image.height);
		if (prop == "Y2N")     return inst.y2n(image.height);
		if (prop == "CXN")     return inst.cxn(image.width);
		if (prop == "CYN")     return inst.cyn(image.height);
		if (prop == "AREAN")   return inst.arean(image.width, image.height);

		return inst.get_prop(prop);
	}

	// ===================== Image =====================

	/**
	 * @brief 获取当前场景下图像的指定属性值
	 * 
	 * @param prop			- 属性名称
	 * @return Val			- 属性值
	 * @throw RuntimeError	- 属性不存在时抛出
	 */
	Val get_img_prop(const std::string& prop) const {
		if (prop == "W")		return image.width;
		if (prop == "H")		return image.height;
		if (prop == "PATH")		return image.path;
		if (prop == "AREA")		return image.area();
		if (prop == "ASPECT")	return image.aspect();

		throw RuntimeError("Unknown property '" + std::string(prop) + "' for image");
	}

	// ===================== Class =====================

	/**
	 * @brief 获取当前场景下某类别的指定属性值
	 * 
	 * @param cls			- 类别名称
	 * @param prop			- 属性名称
	 * @return Val			- 属性值
	 * @throw RuntimeError	- 类别或属性不存在时抛出
	 */
	Val get_cls_prop(const std::string& cls, const std::string& prop) const {
		auto it = objects.find(cls);
		if (it == objects.end()) {
			if (prop == "COUNT") return 0.0;
			throw RuntimeError("Class '" + cls + "' not found in scene");
		}

		if (prop == "COUNT") {
			return Val(static_cast<double>(it->second.size()));
		}

		if (auto cls_it = class_props.find(cls); cls_it != class_props.end()) {
			auto prop_it = cls_it->second.find(prop);
			if (prop_it != cls_it->second.end()) {
				return prop_it->second;
			}
		}

		throw RuntimeError("Unknown property '" + prop + "' for class '" + cls + "'");
	}

	// ===================== Import/Export =====================

	/**
	 * @brief 向场景中导入预设外部变量
	 * 
	 * @param local_name	- 预设变量名
	 * @param value			- 预设变量值
	 * @return Scene& 场景自身引用，便于链式调用
	 */
	Scene& add_import(const std::string& local_name, const Val& value) {
		variables[local_name] = value;
		return *this;
	}

	/**
	 * @brief 从场景中获取导出的内部变量
	 * 
	 * @param host_name		- 宿主端变量名
	 * @return Val			- 值
	 * @throw  RuntimeError	- 变量名不存在时触发
	 */
	Val get_export(const std::string& host_name) const {
		auto key = "__export__" + host_name;	// 内置默认前缀
		if (auto it = variables.find(key); it != variables.end()) {
			return it->second;
		}
		throw RuntimeError("Exported value '" + host_name + "' not found");
	}

public:
	Image image;						// 图像信息
	Objects objects;					// 全体对象，类别名到实例列表的映射
	Variables variables;				// 全局变量，包含导入的宿主变量
	ClassProps class_props;				// 类别级属性

private:
	static std::uint64_t checked_positive_integer(double value, std::string_view label) {
		constexpr double max_exact_dsl_integer = 9007199254740991.0; // 2^53 - 1
		if (!std::isfinite(value) || value < 1.0 || std::trunc(value) != value ||
			value > max_exact_dsl_integer) {
			throw RuntimeError(std::format("{} must be a positive integer, got {}", label, value));
		}
		return static_cast<std::uint64_t>(value);
	}

	std::uint64_t m_next_instance_id = 1;
};

} // namespace postanvil
