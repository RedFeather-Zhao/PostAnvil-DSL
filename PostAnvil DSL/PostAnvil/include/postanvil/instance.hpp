/**
 * @file   instance.hpp
 * @brief  目标检测实例的定义，提供内置属性和动态属性管理
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once

#include "detail.hpp"
#include "error.hpp"

#include <set>

namespace postanvil {

/**
 * @brief 目标检测结果实例
 * @details 封装单个检测框的坐标、尺寸、置信度及类别信息
 *          提供内置衍生属性（如中心点、面积、归一化坐标）
 *          支持运行时动态扩展自定义属性
 *          类别名在构造时自动转为大写
 */
class Instance {
public:
	/**
	 * @brief 构造检测实例
	 * @param class_name 类别名称
	 * @param x 边界框左上角 x 坐标
	 * @param y 边界框左上角 y 坐标
	 * @param width 边界框宽度
	 * @param height 边界框高度
	 * @param confidence 检测置信度，范围 [0.0, 1.0]
	 */
	Instance(std::string_view class_name, double x, double y,
		double width, double height, double confidence)
		: m_cls(class_name), m_x1(x), m_y1(y), m_w(width), m_h(height), m_conf(confidence)
	{
		for (auto& ch : m_cls) {
			ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
		}
	}

	// ========================= 内置动态属性 ============================

	double w()					const { return m_w; }
	double h()					const { return m_h; }
	double x1()					const { return m_x1; }
	double y1()					const { return m_y1; }
	double conf()				const { return m_conf; }
	const std::string& cls()	const { return m_cls; }

	void set_w(double width)					{ m_w = width; }
	void set_h(double height)					{ m_h = height; }
	void set_x1(double x)						{ m_x1 = x; }
	void set_y1(double y)						{ m_y1 = y; }
	void set_conf(double confidence)			{ m_conf = confidence; }
	void set_cls(std::string_view class_name)	{ m_cls = class_name; }

	// ========================= 内置衍生属性 ============================

	double x2()         const { return m_x1 + m_w; }
	double y2()         const { return m_y1 + m_h; }
	double cx()         const { return m_x1 + m_w / 2.0; }
	double cy()         const { return m_y1 + m_h / 2.0; }
	double area()       const { return m_w * m_h; }
	double aspect()     const { return (m_w == 0 || m_h == 0) ? 0.0 : m_w / m_h; }

	double wn(double img_w)      const { return w() / img_w; }
	double hn(double img_h)      const { return h() / img_h; }
	double x1n(double img_w)     const { return x1() / img_w; }
	double x2n(double img_w)     const { return x2() / img_w; }
	double y1n(double img_h)     const { return y1() / img_h; }
	double y2n(double img_h)     const { return y2() / img_h; }
	double cxn(double img_w)     const { return cx() / img_w; }
	double cyn(double img_h)     const { return cy() / img_h; }
	double arean(double img_w, double img_h) const { return area() / (img_w * img_h); }

	// ======================== 实例动态属性 ============================

	/**
	 * @brief 设置动态属性
	 * @param name 属性名
	 * @param value 属性值
	 * @throws RuntimeError 在 Debug 模式下若与内置属性名冲突则抛出
	 */
	void set_prop(const std::string& name, Val value) {

		if (name == "W")		set_w(value.as_num());
		if (name == "H")		set_h(value.as_num());
		if (name == "X1")		set_x1(value.as_num());
		if (name == "Y1")		set_y1(value.as_num());
		if (name == "CONF")		set_conf(value.as_num());
		if (name == "CLS")		set_cls(value.as_str());

#ifdef _DEBUG
		if (_props.contains(name)) {
			throw RuntimeError("Property '" + name + "' conflicts with const built-in property!");
		}
#endif
		this->m_props[name] = value;
	}

	/**
	 * @brief 获取动态属性值
	 * @param name 属性名
	 * @return double 属性值
	 * @throws RuntimeError 属性不存在时抛出
	 */
	Val get_prop(const std::string& name) const {
		if (auto it = this->m_props.find(name); it != this->m_props.end()) {
			return it->second;
		}
		throw RuntimeError("Property '" + name + "' not found in instance of class '" + this->cls() + "'");
	}

	/**
	 * @brief 删除动态属性
	 * @param name 属性名
	 * @throws RuntimeError 属性不存在时抛出
	 */
	void del_prop(const std::string& name) {
		if (!this->m_props.contains(name)) {
			throw RuntimeError("Property '" + name + "' not found in instance of class '" + this->cls() + "'");
		}
		this->m_props.erase(name);
	}

private:
	std::string m_cls;      // 类别名
	double m_x1 = 0;        // 左上角 x 坐标
	double m_y1 = 0;        // 左上角 y 坐标
	double m_w = 0;         // 宽度
	double m_h = 0;         // 高度
	double m_conf = 0.0;    // 置信度

	/**
	 * @brief 动态属性存储表，键为属性名，值为数值
	 */
	detail::str_map<std::string, Val> m_props;

#ifdef _DEBUG
	/**
	 * @brief 内置属性名集合（用于冲突检测）
	 */
	static inline const std::set<std::string_view> _props = {
		"W", "H", "X1", "Y1", "CONF", "CLS",
		"X2", "Y2", "CX", "CY", "AREA", "ASPECT",
		"WN", "HN", "X1N", "X2N", "Y1N", "Y2N",
		"CXN", "CYN", "AREAN"
	};
#endif // _DEBUG
};

/**
 * @brief 实例列表类型别名（std::vector<Instance>）
 */
using Instances = std::vector<Instance>;

} // namespace postanvil