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
#include <cctype>
#include <format>

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

template<typename K, typename V>
using str_map = std::unordered_map<K, V, TransparentStrHash, std::equal_to<>>;

} // namespace detail

struct CompileError : public std::runtime_error {
	using runtime_error::runtime_error;
};
struct RuntimeError : public std::runtime_error {
	using runtime_error::runtime_error;
};


/**
 * @brief 图像信息
 */
struct Image {
	double width = 0;		//< 图像宽度，单位 px
	double height = 0;		//< 图像高度，单位 px
	std::string path = "";	//< 图像路径，path/to/image.jpg
};

/**
 * @brief 目标检测结果实例表示
 *
 * 每个实例对应一个检测到的目标，包含其边界框、类别和置信度信息
 * 所有坐标以像素为单位，以图像左上角为原点
 *
 * 内部统一使用大写类别名
 */
class Instance {
public:
	/**
	 * @brief 构造检测对象实例，并将类别名转换为大写
	 * 
	 * @param class_name - 类名
	 * @param x			 - 左上点 x 坐标
	 * @param y			 - 左上点 y 坐标
	 * @param width		 - 边界框宽度
	 * @param height	 - 边界框高度
	 * @param confidence - 检测置信度，范围 [0.0, 1.0]
	 */
	Instance(std::string_view class_name, double x, double y,
		double width, double height, double confidence)
		: m_cls(class_name), m_x1(x), m_y1(y), m_w(width), m_h(height), m_conf(confidence)
	{
		for (auto& ch : m_cls) {
			ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		}
	}

	const std::string& cls()	const	{ return m_cls; }

	double w()					const	{ return m_w; }
	double h()					const	{ return m_h; }
	double x1()					const	{ return m_x1; }
	double x2()					const	{ return m_x1 + m_w; }
	double y1()					const	{ return m_y1; }
	double y2()					const	{ return m_y1 + m_h; }
	double cx()					const	{ return m_x1 + m_w / 2.0; }
	double cy()					const	{ return m_y1 + m_h / 2.0; }
	double conf()				const	{ return m_conf; }
	double area()				const	{ return m_w * m_h; }
	double aspect()				const	{ return (m_w == 0 || m_h == 0) ? 0.0 : m_w / m_h; }

	double wn(double img_w)						const	{ return w() / img_w; }
	double hn(double img_h)						const	{ return h() / img_h; }
	double x1n(double img_w)					const	{ return x1() / img_w; }
	double x2n(double img_w)					const	{ return x2() / img_w; }
	double y1n(double img_h)					const	{ return y1() / img_h; }
	double y2n(double img_h)					const	{ return y2() / img_h; }
	double cxn(double img_w)					const	{ return cx() / img_w; }
	double cyn(double img_h)					const	{ return cy() / img_h; }
	double arean(double img_w, double img_h)	const	{ return area() / (img_w * img_h); }

	void set_prop(const std::string& name, double value) {
		this->props[name] = value;
	}

	double get_prop(const std::string& name) const {
		auto it = this->props.find(name);
		if (it != this->props.end()) {
			return it->second;
		}
		throw RuntimeError("Property '" + name + "' not found in instance of class '" + this->cls() + "'");
	}

	void del_prop(const std::string& name) {
		this->props.erase(name);
	}

private:
	std::string m_cls;		//< 类别名，只读，大写
	double m_x1 = 0;		//< 边界框左上角 x 坐标
	double m_y1 = 0;		//< 边界框左上角 y 坐标
	double m_w = 0;			//< 边界框宽度
	double m_h = 0;			//< 边界框高度
	double m_conf = 0.0;	//< 检测置信度，范围 [0.0, 1.0]
	
	/**
	 * @brief 动态属性存储，用于存储属性算子计算的结果
	 */
	detail::str_map<std::string, double> props;
};

/**
 * @brief 实例列表类型别名
 *
 * @see   Instance
 */
using Instances = std::vector<Instance>;

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

} // namespace postanvil