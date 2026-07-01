/**
 * @file   context.hpp
 * @brief  定义评估上下文：图像与实例的基本数据结构
 * @detail 本文件包含 PostAnvil 评估器使用的核心数据结构：
 *		   Image：图像尺寸信息
 *		   Instance：目标检测结果实例
 *		   Scene：按类别组织的实例集合
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace postanvil {

/**
 * @brief 图像尺寸信息
 */
struct Image {
	double width = 0;  //< 图像宽度（像素）
	double height = 0; //< 图像高度（像素）
};

/**
 * @brief 目标检测结果实例表示
 *
 * 每个实例对应一个检测到的目标，包含其边界框、类别和置信度信息
 * 所有坐标以像素为单位，以图像左上角为原点
 */
struct Instance {
	std::string cls;	//< 类别名
	double x = 0;		//< 边界/外接框左上角 x 坐标
	double y = 0;		//< 边界/外接框左上角 y 坐标
	double width = 0;	//< 边界/外接框宽度
	double height = 0;	//< 边界/外接框高度
	double conf = 0.0;	//< 检测置信度，范围 [0.0, 1.0]

	/**
	 * @brief 返回右边界 x 坐标
	 * @return x + width
	 */
	double right() const { return x + width; }

	/**
	 * @brief 返回下边界 y 坐标
	 * @return y + height
	 */
	double bottom() const { return y + height; }

	/**
	 * @brief 返回中心点 x 坐标
	 * @return x + width / 2
	 */
	double center_x() const { return x + width / 2.0; }

	/**
	 * @brief 返回中心点 y 坐标
	 * @return y + height / 2
	 */
	double center_y() const { return y + height / 2.0; }

	/**
	 * @brief 计算边界框面积
	 * @return width * height
	 */
	double area() const { return width * height; }

	/**
	 * @brief 计算宽高比
	 * @return width / height；若 height 为 0 则返回 0
	 */
	double aspect_ratio() const {
		if (width == 0 || height == 0) {
			return 0.0;
		}
		return width / height;
	}
};

/**
 * @brief 实例列表类型别名
 */
using Instances = std::vector<Instance>;

/**
 * @brief 支持透明哈希的字符串哈希函数	
 */
struct TransparentStrHash
{
	using is_transparent = void;

	template<typename TStr>
	size_t operator()(const TStr& s) const noexcept
	{
		return std::hash<std::string_view>{}(s);
	}
};

/**
 * @brief 场景类型：按类别名组织的实例集合
 */
using Scene = std::unordered_map<std::string, Instances,
	TransparentStrHash, std::equal_to<>>;
} // namespace postanvil