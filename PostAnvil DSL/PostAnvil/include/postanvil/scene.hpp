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

namespace postanvil {

/**
 * @brief 图像元信息
 */
struct Image {
	double width = 0;      // 图像宽度，像素单位
	double height = 0;     // 图像高度，像素单位
	std::string path = ""; // 图像文件路径

	double area()	const		{ return width * height; }
	double aspect()	const		{ return width / height; }
};

/**
 * @brief DSL 执行的完整场景上下文
 * @details 包含图像信息、按类别组织的实例列表、全局变量以及类别级自定义属性
 */
struct Scene {
	using Objects = detail::str_map<std::string, Instances>;
	using ClassProps = detail::str_map<std::string, detail::str_map<std::string, Val>>;

	/**
	 * @brief 构造场景
	 * @param img 图像元信息
	 * @param instances 初始实例列表
	 */
	explicit Scene(const Image& img, const Instances& instances = {})
		: image(img)
	{
		this->add(instances);
	}

	/**
	 * @brief 向场景中添加单个实例
	 * @param inst 待添加的实例
	 * @return 场景自身的引用，便于链式调用
	 */
	Scene& add(const Instance& inst) {
		objects[inst.cls()].push_back(inst);
		return *this;
	}

	/**
	 * @brief 向场景中添加多个实例
	 * @param instances 实例列表
	 * @return 场景自身的引用
	 */
	Scene& add(const std::vector<Instance>& instances) {
		for (const auto& inst : instances) {
			objects[inst.cls()].push_back(inst);
		}
		return *this;
	}

	Image image;                               // 图像信息
	Objects objects;                           // 类别名到实例列表的映射
	detail::str_map<std::string, Val> variables; // 全局变量，包含导入的宿主变量
	ClassProps class_props;                    // 类别级属性
};


/**
 * @brief 构造占位实例的静态工厂方法，尝试通过 get_instance_prop 访问占位实例将会报错
 *
 * @return dummy 实例
 */
static inline Instance make_dummy_instance() {
	return Instance("__DUMMY", 0, 0, 0, 0, 0);
}

/**
 * @brief 获取实例的指定属性值，包括内置属性和动态属性
 * @param inst 目标实例
 * @param scene 场景上下文，用于获取图像尺寸
 * @param prop 属性名称，大小写不敏感
 * @return double 属性值
 * @throws RuntimeError 属性不存在时抛出
 */
static inline double get_instance_prop(const Instance& inst, const Scene& scene, std::string_view prop) {
	if (inst.cls() == "__DUMMY") {
		throw RuntimeError("Try to access a dummy instance by self.*");
	}

	if (prop == "CONF")   return inst.conf();

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

	if (prop == "WN")      return inst.wn(scene.image.width);
	if (prop == "HN")      return inst.hn(scene.image.height);
	if (prop == "X1N")     return inst.x1n(scene.image.width);
	if (prop == "X2N")     return inst.x2n(scene.image.width);
	if (prop == "Y1N")     return inst.y1n(scene.image.height);
	if (prop == "Y2N")     return inst.y2n(scene.image.height);
	if (prop == "CXN")     return inst.cxn(scene.image.width);
	if (prop == "CYN")     return inst.cyn(scene.image.height);
	if (prop == "AREAN")   return inst.arean(scene.image.width, scene.image.height);

	return inst.get_prop(std::string(prop));
}

/**
 * @brief 获取图像属性
 * @param img 图像元信息
 * @param prop 属性名称，W 或 H
 * @return double 对应的宽度或高度值
 * @throws RuntimeError 未知属性名时抛出
 */
static inline double get_image_prop(const Image& img, std::string_view prop) {
	if (prop == "W")		return img.width;
	if (prop == "H")		return img.height;
	if (prop == "AREA")		return img.area();
	if (prop == "ASPECT")	return img.aspect();

	throw RuntimeError("Unknown property '" + std::string(prop) + "' for image");
}

/**
 * @brief 获取类别属性
 * @param scene 场景上下文
 * @param class_name 类别名称
 * @param prop 属性名称
 * @return Val 属性值
 * @throws RuntimeError 类别或属性不存在时抛出
 */
inline Val get_class_prop(const Scene& scene, std::string_view class_name, std::string_view prop) {
	auto it = scene.objects.find(class_name);
	if (it == scene.objects.end()) {
		throw RuntimeError("Class '" + std::string(class_name) + "' not found in scene");
	}

	if (prop == "COUNT") {
		return Val(static_cast<double>(it->second.size()));
	}

	if (auto cls_it = scene.class_props.find(class_name); cls_it != scene.class_props.end()) {
		auto prop_it = cls_it->second.find(prop);
		if (prop_it != cls_it->second.end()) {
			return prop_it->second;
		}
	}

	throw RuntimeError("Unknown property '" + std::string(prop) + "' for class '" + std::string(class_name) + "'");
}

} // namespace postanvil