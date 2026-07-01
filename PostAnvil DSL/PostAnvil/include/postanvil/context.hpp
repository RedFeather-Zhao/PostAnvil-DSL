/**
 * @file   context.hpp
 * @brief  定义评估上下文：图像与实例的基本数据结构
 * @detail 本文件包含 PostAnvil 评估器使用的核心数据结构：
 *         Image：图像尺寸信息
 *         Instance：目标检测结果实例
 *         Scene：按类别组织的实例集合
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace postanvil {

namespace detail {
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
} // namespace detail

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
	double x1 = 0;		//< 边界框左上角 x 坐标
	double y1 = 0;		//< 边界框左上角 y 坐标
	double w = 0;		//< 边界框宽度
	double h = 0;		//< 边界框高度
	double conf = 0.0;	//< 检测置信度，范围 [0.0, 1.0]

	/** @brief 动态属性存储，用于属性算子（RULE ATTR）计算的结果 */
	std::unordered_map<std::string, double> props;

	/**
	 * @brief 返回右下角 x 坐标
	 * @return x1 + w
	 */
	double x2() const { return x1 + w; }

	/**
	 * @brief 返回右下角 y 坐标
	 * @return y1 + h
	 */
	double y2() const { return y1 + h; }

	/**
	 * @brief 返回中心点 x 坐标
	 * @return x1 + w / 2
	 */
	double cx() const { return x1 + w / 2.0; }

	/**
	 * @brief 返回中心点 y 坐标
	 * @return y1 + h / 2
	 */
	double cy() const { return y1 + h / 2.0; }

	/**
	 * @brief 计算边界框面积
	 * @return w * h
	 */
	double area() const { return w * h; }

	/**
	 * @brief 计算宽高比
	 * @return w / h；若 h 为 0 则返回 0
	 */
	double aspect() const {
		if (w == 0 || h == 0) {
			return 0.0;
		}
		return w / h;
	}
};

/**
 * @brief 实例列表类型别名
 * 
 * @see   Instance
 */
using Instances = std::vector<Instance>;

/**
 * @brief 目标检测场景：按类别名组织的实例集合
 *
 * @see   Instances
 */
using Scene = std::unordered_map<std::string, Instances,
	detail::TransparentStrHash, std::equal_to<>>;

} // namespace postanvil