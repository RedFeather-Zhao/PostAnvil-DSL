/**
 * @file   context.hpp
 * @brief  定义评估上下文：图像与实例的基本数据结构
 * @detail 本文件包含 PostAnvil 评估器使用的核心数据结构：
 *         Image：图像尺寸信息
 *         Instance：目标检测结果实例（含静态工厂 Create）
 *         Scene：按类别组织的实例集合
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

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
 * @brief 图像信息
 */
struct Image {
	double width = 0;	//< 图像宽度，单位 px
	double height = 0;	//< 图像高度，单位 px
	std::string path = "";	//< 图像路径，path/to/image.jpg
};

/**
 * @brief 目标检测结果实例表示
 *
 * 每个实例对应一个检测到的目标，包含其边界框、类别和置信度信息
 * 所有坐标以像素为单位，以图像左上角为原点
 *
 * 内部统一使用大写类别名，通过静态工厂 Create() 构造实例
 */
struct Instance {

private:
	// 禁止直接构造，必须使用静态工厂 Create()，以确保类别名统一大写
	Instance() = default;

public:
	/**
	 * @brief 静态工厂方法，创建实例，类别名不区分大小写，内部统一转大写
	 *
	 * @param cls   类别名
	 * @param x1    左上角 x 坐标
	 * @param y1    左上角 y 坐标
	 * @param w     检测框宽度
	 * @param h     检测框高度
	 * @param conf  置信度，默认 1.0
	 * @return      Instance 检测实例对象
	 */
	static Instance
	Create(std::string_view cls, double x1, double y1, double w, double h, double conf = 1.0)
	{
		Instance inst;
		inst.x1 = x1; inst.y1 = y1;
		inst.w = w; inst.h = h;
		inst.conf = conf;
		inst.cls.reserve(cls.size());
		for (auto ch : cls) {
			inst.cls.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(ch))));
		}
		return inst;
	}

	// ==================== 原生属性 ====================

	std::string cls;	//< 类别名
	double x1 = 0;		//< 边界框左上角 x 坐标
	double y1 = 0;		//< 边界框左上角 y 坐标
	double w = 0;		//< 边界框宽度
	double h = 0;		//< 边界框高度
	double conf = 0.0;	//< 检测置信度，范围 [0.0, 1.0]

	/** @brief 动态属性存储，用于存储属性算子计算的结果 */
	std::unordered_map<std::string, double,
		detail::TransparentStrHash, std::equal_to<>> props;

	// ==================== 派生属性 ====================

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

/**
 * @brief 场景静态工厂，用于从其他语言便捷构建 Scene
 *
 * 支持两种调用方式：
 * 1. 批量构造：从实例列表自动按类别分组
 * 2. 逐步添加：通过 Add 方法链式添加实例
 */
struct SceneBuilder {
	/**
	 * @brief 创建 SceneBuilder 实例（用于链式调用）
	 * @return SceneBuilder 构建器对象
	 *
	 * @example
	 * auto scene = SceneBuilder::Create()
	 *     .Add("AA", 0, 0, 100, 100)
	 *     .Add("AA", 41, 0, 20, 20)
	 *     .Build();
	 */
	static SceneBuilder Create() {
		return SceneBuilder{};
	}

	/**
	 * @brief 从实例列表直接构建 Scene（自动按类别分组）
	 *
	 * @param instances 实例列表（类别名大小写不限，内部自动转大写）
	 * @return Scene 按类别组织的场景
	 *
	 * @example
	 * auto scene = SceneBuilder::FromInstances({
	 *     Instance::Create("AA", 0, 0, 100, 100),
	 *     Instance::Create("AA", 41, 0, 20, 20),
	 *     Instance::Create("BB", 10, 10, 30, 30)
	 * });
	 */
	static Scene FromInstances(const std::vector<Instance>& instances) {
		Scene scene;
		for (const auto& inst : instances) {
			scene[inst.cls].push_back(inst);
		}
		return scene;
	}

	/**
	 * @brief 向场景添加实例（类别名自动转大写）
	 *
	 * @param cls   类别名（任意大小写）
	 * @param x1    左上角 x 坐标
	 * @param y1    左上角 y 坐标
	 * @param w     检测框宽度
	 * @param h     检测框高度
	 * @param conf  置信度，默认 1.0
	 * @return SceneBuilder& 返回自身引用，支持链式调用
	 *
	 * @example
	 * auto scene = SceneBuilder::Create()
	 *     .Add("AA", 0, 0, 100, 100)
	 *     .Add("AA", 41, 0, 20, 20)
	 *     .Add("AA", 41, 41, 20, 20)
	 *     .Build();
	 */
	SceneBuilder& Add(std::string_view cls, double x1, double y1, double w, double h, double conf = 1.0) {
		std::string upper_cls;
		upper_cls.reserve(cls.size());
		for (auto ch : cls) {
			upper_cls.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(ch))));
		}
		m_scene[upper_cls].emplace_back(
			Instance::Create(cls, x1, y1, w, h, conf)
		);
		return *this;
	}

	/**
	 * @brief 构建最终 Scene 对象
	 *
	 * @return Scene 构建完成的场景
	 */
	Scene Build() const {
		return m_scene;
	}

private:
	Scene m_scene;  // 内部累积的场景数据
};

} // namespace postanvil