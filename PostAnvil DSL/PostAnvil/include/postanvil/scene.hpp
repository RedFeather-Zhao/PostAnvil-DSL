/**
 * @file   scene.hpp
 * @brief  
 * 
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include "instance.hpp"

namespace postanvil {

/**
 * @brief 图像信息
 */
struct Image {
	double width = 0;		//< 图像宽度，单位 px
	double height = 0;		//< 图像高度，单位 px
	std::string path = "";	//< 图像路径，path/to/image.jpg
};

/**
 * @brief 场景数据结构，包含图像信息和按类别组织的实例集合
 *
 * @see   Image
 */
struct Scene {
	using Objects = detail::str_map<std::string, Instances>;

	explicit Scene(const Image& img, const Instances& instances = {})
		: image(img)
	{
		this->add(instances);
	}

	/**
	 * @brief 将单个实例添加到场景中，按类别组织
	 *
	 * @param inst - 待添加的实例
	 * @return Scene& - 返回当前场景对象，支持链式调用
	 */
	Scene& add(const Instance& inst) {
		objects[inst.cls()].push_back(inst);
		return *this;
	}

	/**
	 * @brief 将多个实例添加到场景中，按类别组织
	 *
	 * @param instances - 待添加的实例列表
	 * @return Scene& - 返回当前场景对象，支持链式调用
	 */
	Scene& add(const std::vector<Instance>& instances) {
		for (const auto& inst : instances) {
			objects[inst.cls()].push_back(inst);
		}
		return *this;
	}

	Image image;		// 场景图像信息
	Objects objects;	// 物体检测结果，按照类别组织的实例集合
};


/**
 * @brief 获取实例的属性值，包括内置属性和动态属性，若内置属性未匹配，则查找动态属性
 *
 * @param inst  - 实例
 * @param scene - 场景
 * @param prop  - 属性名
 */
static inline double get_instance_prop(const Instance& inst, const Scene& scene, std::string_view prop) {
	// 内置属性
	if (prop == "CONF")   return inst.conf();

	// 几何属性（像素坐标）
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

	// 归一化属性 (0.0 ~ 1.0)
	if (prop == "WN")      return inst.wn(scene.image.width);
	if (prop == "HN")      return inst.hn(scene.image.height);
	if (prop == "X1N")     return inst.x1n(scene.image.width);
	if (prop == "X2N")     return inst.x2n(scene.image.width);
	if (prop == "Y1N")     return inst.y1n(scene.image.height);
	if (prop == "Y2N")     return inst.y2n(scene.image.height);
	if (prop == "CXN")     return inst.cxn(scene.image.width);
	if (prop == "CYN")     return inst.cyn(scene.image.height);
	if (prop == "AREAN")   return inst.arean(scene.image.width, scene.image.height);

	// 动态属性
	return inst.get_prop(std::string(prop));
}

/**
 * @brief 获取图像属性
 *
 * @param img  - 图像信息
 * @param prop - 属性名，当前仅支持 "W"（宽度）和 "H"（高度）
 * @return double - 属性值；若属性不存在则抛出 RuntimeError
 */
static inline double get_image_prop(const Image& img, std::string_view prop) {
	if (prop == "W") return img.width;
	if (prop == "H") return img.height;

	throw RuntimeError("Unknown property '" + std::string(prop) + "' for image");
}

/**
 * @brief 获取类别属性
 *
 * 支持的内置属性：
 * - COUNT：类别中实例的数量
 *
 * @param scene      - 场景
 * @param class_name - 类别名
 * @param prop       - 属性名
 * @return double    - 属性值
 */
inline double get_class_prop(const Scene& scene, std::string_view class_name, std::string_view prop) {
	auto it = scene.objects.find(class_name);
	if (it == scene.objects.end()) {
		throw RuntimeError("Class '" + std::string(class_name) + "' not found in scene");
	}
	
	if (prop == "COUNT") {
		return static_cast<double>(it->second.size());
	}
	// TODO: 类级别自定义属性（阶段 4）

	throw RuntimeError("Unknown property '" + std::string(prop) + "' for class '" + std::string(class_name) + "'");
}

} // namespace postanvil
