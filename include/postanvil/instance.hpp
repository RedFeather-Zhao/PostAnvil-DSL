/**
 * @file   instance.hpp
 * @brief  目标检测实例定义
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include "detail.hpp"
#include "error.hpp"
#include "type.hpp"

#include <algorithm>
#include <array>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace postanvil {

/**
 * @brief 目标检测实例
 * @details Instance 只保存框、置信度和动态属性。
 *          类别属于 Scene 中的索引关系，不属于 Instance 本身。
 */
class Instance {
public:
	/**
	 * @brief 构造目标检测实例
	 *
	 * @param x		- 边界框左上角 x 坐标
	 * @param y		- 边界框左上角 y 坐标
	 * @param w		- 边界框宽度
	 * @param h		- 边界框高度
	 * @param conf	- 检测置信度
	 */
	Instance(double x, double y, double w, double h, double conf)
		: m_x1(x),
		  m_y1(y),
		  m_w(w),
		  m_h(h),
		  m_conf(conf)
	{
	}

	// ========================= 内置属性 ============================

	[[nodiscard]] double w()		const noexcept	{ return m_w; }
	[[nodiscard]] double h()		const noexcept	{ return m_h; }
	[[nodiscard]] double x1()		const noexcept	{ return m_x1; }
	[[nodiscard]] double y1()		const noexcept	{ return m_y1; }
	[[nodiscard]] double conf()		const noexcept	{ return m_conf; }
	[[nodiscard]] InstId id()		const noexcept	{ return m_id; }

	void set_w(double value)		noexcept		{ m_w = value; }
	void set_h(double value)		noexcept		{ m_h = value; }
	void set_x1(double value)		noexcept		{ m_x1 = value; }
	void set_y1(double value)		noexcept		{ m_y1 = value; }
	void set_conf(double value)		noexcept		{ m_conf = value; }

	// ========================= 衍生属性 ============================

	[[nodiscard]] double x2()		const noexcept	{ return m_x1 + m_w; }
	[[nodiscard]] double y2()		const noexcept	{ return m_y1 + m_h; }
	[[nodiscard]] double cx()		const noexcept	{ return m_x1 + m_w / 2.0; }
	[[nodiscard]] double cy()		const noexcept	{ return m_y1 + m_h / 2.0; }
	[[nodiscard]] double area()		const noexcept	{ return m_w * m_h; }
	[[nodiscard]] double aspect()	const noexcept	{ return m_h == 0.0 ? 0.0 : m_w / m_h; }

	[[nodiscard]] double wn(double image_width)		const noexcept	{ return w() / image_width; }
	[[nodiscard]] double hn(double image_height)	const noexcept	{ return h() / image_height; }
	[[nodiscard]] double x1n(double image_width)	const noexcept	{ return x1() / image_width; }
	[[nodiscard]] double x2n(double image_width)	const noexcept	{ return x2() / image_width; }
	[[nodiscard]] double y1n(double image_height)	const noexcept	{ return y1() / image_height; }
	[[nodiscard]] double y2n(double image_height)	const noexcept	{ return y2() / image_height; }
	[[nodiscard]] double cxn(double image_width)	const noexcept	{ return cx() / image_width; }
	[[nodiscard]] double cyn(double image_height)	const noexcept	{ return cy() / image_height; }

	[[nodiscard]] double arean(double image_width, double image_height) const noexcept {
		return area() / (image_width * image_height);
	}

	// ======================== 动态属性 ============================

	/**
	 * @brief 设置实例属性
	 *
	 * @param name				- 属性名
	 * @param value				- 属性值
	 * @throws PARuntimeError	- 内置只读属性或值类型非法时抛出
	 */
	void set_prop(const std::string& name, Val value) {
		if (name == "W")		{ set_w(value.as_num());	return; }
		if (name == "H")		{ set_h(value.as_num());	return; }
		if (name == "X1")		{ set_x1(value.as_num());	return; }
		if (name == "Y1")		{ set_y1(value.as_num());	return; }
		if (name == "CONF")		{ set_conf(value.as_num());	return; }

		if (s_builtin_props.contains(name)) {
			throw PARuntimeError("Property '" + name + "' is a read-only built-in property");
		}
		m_props.insert_or_assign(name, std::move(value));
	}

	/**
	 * @brief 获取动态属性
	 *
	 * @param name				- 属性名
	 * @return Val				- 属性值
	 * @throws PARuntimeError	- 属性不存在时抛出
	 */
	[[nodiscard]]
	Val get_prop(const std::string& name) const {
		if (const auto it = m_props.find(name); it != m_props.end()) {
			return it->second;
		}
		throw PARuntimeError("Property '" + name + "' not found in instance");
	}

	/**
	 * @brief 删除动态属性
	 *
	 * @param name				- 属性名
	 * @throws PARuntimeError	- 属性不存在时抛出
	 */
	void del_prop(const std::string& name) {
		if (m_props.erase(name) == 0) {
			throw PARuntimeError("Property '" + name + "' not found in instance");
		}
	}

private:

	friend class Scene;
	void set_id(InstId id) noexcept {
		m_id = id;
	}
	InstId m_id = 0;			//< 实例 ID，由 Scene 统一分配

	double m_x1		= 0.0;			//< 左上角 x 坐标
	double m_y1		= 0.0;			//< 左上角 y 坐标
	double m_w		= 0.0;			//< 宽度
	double m_h		= 0.0;			//< 高度
	double m_conf	= 0.0;			//< 置信度

	detail::str_map<Val> m_props;	//< 动态属性集合

	//< 内置属性集合，方便判断是否为内置属性
	static inline const std::set<std::string_view> s_builtin_props{
		"W", "H", "X1", "Y1", "CONF", "CLS", "ID", "INDEX",
		"X2", "Y2", "CX", "CY", "AREA", "ASPECT",
		"WN", "HN", "X1N", "X2N", "Y1N", "Y2N", "CXN", "CYN", "AREAN"
	};
};

using Instances = std::vector<Instance>;

} // namespace postanvil
