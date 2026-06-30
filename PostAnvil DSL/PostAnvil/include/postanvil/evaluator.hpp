/**
 * @file   evaluator.hpp
 * @brief  规则评估器，对场景中的实例执行规则过滤。
 * @detail 评估器接收已解析的规则列表和场景数据，对每个实例：
 * 1. 先评估 GLOBAL 规则条件
 * 2. 再评估该实例所属类别的规则条件
 * 3. 所有条件均满足则保留该实例
 *
 * 支持的条件表达式类型：
 * - 数值常量、属性访问（self.width / image.width / OtherClass.prop）
 * - 比较运算（< > <= >= == !=）
 * - 算术运算（+ - *）
 * - 逻辑运算（AND / OR / NOT）
 * - 内置函数：abs(x)、iou(self, other)
 * - 空间谓词：CONTAINS、INSIDE、OVERLAP、CLOSE_TO
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */
#pragma once
#include "postanvil/ast.hpp"
#include "postanvil/context.hpp"
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <unordered_map>

namespace postanvil {

/**
 * @brief 评估结果，包含每个类别中通过过滤的实例列表。
 */
struct EvalResult {
	/**
	 * @brief 按类别组织的保留实例映射
	 */
	Scene kept;
};

/**
 * @brief 规则评估器。
 *
 * 评估器实现了 PostAnvil DSL 的运行时语义，将解析后的规则
 * 应用于场景中的实例，执行滤波并返回结果。
 */
class Evaluator {
public:
	Evaluator() = default;

	/**
	 * @brief 对场景中的所有实例执行规则评估。
	 *
	 * 评估流程：
	 * 1. 将规则分为 GLOBAL 规则和各类别专用规则
	 * 2. 遍历场景中每个类别的每个实例
	 * 3. 对每个实例先评估 GLOBAL 规则，再评估类别规则
	 * 4. 所有条件均满足（返回 true）的实例加入 kept 结果
	 *
	 * @param scene 场景数据（按类别组织的实例集合）
	 * @param image 图像尺寸信息
	 * @param rules 解析后的规则列表
	 * @return 评估结果，包含每个类别中保留的实例
	 */
	EvalResult evaluate(
		const Scene& scene,
		const Image& image,
		const std::vector<Rule>& rules)
	{
		EvalResult res;

		std::unordered_map<std::string, std::vector<std::unique_ptr<Expr>>> class_rules_storage;
		std::vector<std::unique_ptr<Expr>> global_rules;
		std::unordered_map<std::string, std::vector<Expr*>> class_rules;

		// separate GLOBAL rules
		for (const auto& r: rules) {
			if (r.target == "GLOBAL") {
				for (const auto& c : r.conditions) {
					global_rules.push_back(clone_expr(c.get()));
				}
			}
			else {
				auto &vec = class_rules_storage[r.target];
				for (const auto& c : r.conditions) {
					vec.push_back(clone_expr(c.get()));
				}
				// store pointers
				auto &ptrs = class_rules[r.target];
				for (auto &e : vec) {
					ptrs.push_back(e.get());
				}
			}
		}

		// For each class in scene
		for (const auto &kv : scene) {
			auto& cls = kv.first;
			auto& instances = kv.second;

			for (const auto &inst : instances) {
				// evaluate GLOBAL rules
				bool ok = true;
				for (const auto &g : global_rules) {
					if (!eval_bool(g.get(), inst, scene, image)) {
						ok=false;
						break;
					}
				}
				if (!ok) {
					continue;
				}

				// evaluate class-specific rules
				auto it = class_rules.find(cls);
				if (it != class_rules.end()) {
					for (Expr* e : it->second) {
						if (!eval_bool(e, inst, scene, image)) {
							ok = false;
							break;
						}
					}
				}
				if (ok) {
					res.kept[cls].push_back(inst);
				}
			}
		}
		return res;
	}

private:
	/**
	 * @brief 深拷贝表达式 AST 节点。
	 *
	 * 递归复制整个表达式树，确保评估器拥有独立的 AST 副本。
	 *
	 * @param e 源表达式指针
	 * @return 深拷贝后的表达式（唯一指针）
	 */
	std::unique_ptr<Expr> clone_expr(const Expr* e) {
		if (!e) {
			return nullptr;
		}
		switch (e->type) {
			case Expr::CONST_NUM: {
				auto ne = static_cast<const NumberExpr*>(e);
				return std::make_unique<NumberExpr>(ne->value);
			}
			case Expr::IDENT: {
				auto ie = static_cast<const IdentExpr*>(e);
				return std::make_unique<IdentExpr>(ie->name);
			}
			case Expr::PROP_ACCESS: {
				auto pe = static_cast<const PropAccessExpr*>(e);
				return std::make_unique<PropAccessExpr>(pe->object, pe->prop);
			}
			case Expr::UNARY: {
				auto ue = static_cast<const UnaryExpr*>(e);
				auto rhs = clone_expr(ue->rhs.get());
				return std::make_unique<UnaryExpr>(ue->op, std::move(rhs));
			}
			case Expr::BINARY: {
				auto be = static_cast<const BinaryExpr*>(e);
				auto l = clone_expr(be->lhs.get());
				auto r = clone_expr(be->rhs.get());
				return std::make_unique<BinaryExpr>(std::move(l), be->op, std::move(r));
			}
			case Expr::CALL: {
				auto ce = static_cast<const CallExpr*>(e);
				auto c = std::make_unique<CallExpr>(ce->name);
				for (const auto &a : ce->args) c->args.push_back(clone_expr(a.get()));
				if (ce->qtyRange) {
					if (ce->qtyRange->is_range)
						c->qtyRange = std::make_unique<QuantityRange>(ce->qtyRange->min, ce->qtyRange->max);
					else
						c->qtyRange = std::make_unique<QuantityRange>(ce->qtyRange->min);
				}
				return c;
			}
		}
		return nullptr;
	}

	/**
	 * @brief 对表达式求值，返回数值结果。
	 *
	 * 这是评估器的核心方法，递归遍历 AST 并计算数值。
	 * 比较运算返回 1.0（真）或 0.0（假）；逻辑运算 AND/OR/NOT 同理。
	 *
	 * 支持的节点类型：
	 * - CONST_NUM：返回常量值
	 * - PROP_ACCESS：访问 self/image/类名 的属性
	 * - IDENT：返回 0.0
	 * - UNARY：支持 `-` 和 `NOT`
	 * - BINARY：支持 +, -, *, 比较, AND, OR
	 * - CALL：支持 abs(), iou(), CONTAINS, INSIDE, OVERLAP, CLOSE_TO
	 *
	 * @param e 表达式 AST 节点
	 * @param self 当前正在评估的实例
	 * @param scene 全局场景数据
	 * @param image 图像尺寸信息
	 * @return 表达式的数值结果
	 */
	double eval_num(const Expr* e, const Instance& self, const Scene& scene, const Image& image) {
		if (!e) return 0.0;
		switch (e->type) {
			case Expr::CONST_NUM: {
				return static_cast<const NumberExpr*>(e)->value;
			}
			case Expr::PROP_ACCESS: {
				auto pe = static_cast<const PropAccessExpr*>(e);
				if (pe->object == "self") {
					return get_instance_prop(self, pe->prop);
				}
				if (pe->object == "image") {
					return get_image_prop(image, pe->prop);
				}
				
				// other class property: take first instance if exists
				auto it = scene.find(pe->object);
				if (it != scene.end() && !it->second.empty()) {
					return get_instance_prop(it->second.front(), pe->prop);
				}
				return 0.0;
			}
			case Expr::IDENT: {
				// treat identifier as 0
				return 0.0;
			}
			case Expr::UNARY: {
				auto ue = static_cast<const UnaryExpr*>(e);
				double v = eval_num(ue->rhs.get(), self, scene, image);
				if (ue->op == "-") {
					return -v;
				}
				else if (ue->op == "NOT") {
					return v == 0.0 ? 1.0 : 0.0;
				}
				else {
					throw std::runtime_error("Unknown unary operator: " + ue->op);
				}
				// return v;
			}
			case Expr::BINARY: {
				auto be = static_cast<const BinaryExpr*>(e);
				double l = eval_num(be->lhs.get(), self, scene, image);
				double r = eval_num(be->rhs.get(), self, scene, image);
				if (be->op == "+")		return l + r;
				if (be->op == "-")		return l - r;
				if (be->op == "*")		return l * r;
				// comparisons return 1.0 or 0.0
				if (be->op == ">")		return l >  r ? 1.0 : 0.0;
				if (be->op == "<")		return l <  r ? 1.0 : 0.0;
				if (be->op == ">=")		return l >= r ? 1.0 : 0.0;
				if (be->op == "<=")		return l <= r ? 1.0 : 0.0;
				if (be->op == "==")		return l == r ? 1.0 : 0.0;
				if (be->op == "!=")		return l != r ? 1.0 : 0.0;
				if (be->op == "AND")	return ((l!=0.0) && (r!=0.0)) ? 1.0 : 0.0;
				if (be->op == "OR")		return ((l!=0.0) || (r!=0.0)) ? 1.0 : 0.0;
				return 0.0;
			}
			case Expr::CALL: {
				auto ce = static_cast<const CallExpr*>(e);
				if (ce->name == "abs" && ce->args.size()==1) {
					double a = eval_num(ce->args[0].get(), self, scene, image);
					return std::abs(a);
				}
				if (ce->name == "iou" && ce->args.size()==2) {
					const Expr* b = ce->args[1].get();
					std::string other_class;
					if (b->type==Expr::PROP_ACCESS) {
						other_class = static_cast<const PropAccessExpr*>(b)->object;
					}
					else if (b->type==Expr::IDENT) {
						other_class = static_cast<const IdentExpr*>(b)->name;
					}
					if (other_class.empty()) {
						return 0.0;
					}
					auto it = scene.find(other_class);
					if (it == scene.end() || it->second.empty()) return 0.0;
					return compute_iou(self, it->second.front());
				}
				
				// Predicates: CONTAINS, INSIDE, OVERLAP, CLOSE_TO
				std::string name_up = ce->name;
				for (auto &c: name_up) {
					c = (char)toupper((unsigned char)c);
				}

				if (name_up == "CONTAINS") {
					if (ce->args.size() < 1) {
						return 0.0;
					}
					// first arg: class name
					std::string target;
					const Expr* a0 = ce->args[0].get();
					if (a0->type == Expr::IDENT) {
						target = static_cast<const IdentExpr*>(a0)->name;
					}
					else if (a0->type == Expr::PROP_ACCESS) {
						target = static_cast<const PropAccessExpr*>(a0)->object;
					}
					if (target.empty()) {
						return 0.0;
					}
					
					// check quantity range in CallExpr->qtyRange or second numeric arg
					int need = 1;
					bool hasExplicitCount=false;
					if (ce->qtyRange) {
						need = ce->qtyRange->min; // min used when single-valued
						hasExplicitCount = true;
					}
					if (ce->args.size() >= 2 && ce->args[1]->type == Expr::CONST_NUM) {
						need = (int)static_cast<const NumberExpr*>(ce->args[1].get())->value;
						hasExplicitCount=true;
					}
					
					int cnt = 0;
					auto it = scene.find(target);
					if (it != scene.end()) {
						for (const auto &b : it->second) {
							if (   b.x >= self.x
								&& b.y >= self.y
								&& b.right() <= self.right()
								&& b.bottom() <= self.bottom())
							{
								++cnt;
							}
						}
					}

					if (ce->qtyRange) {
						if (ce->qtyRange->is_range) {
							return (cnt >= ce->qtyRange->min && cnt <= ce->qtyRange->max) ? 1.0 : 0.0;
						}
						return (cnt >= ce->qtyRange->min) ? 1.0 : 0.0;
					}
					// if explicit count was provided, require equality, otherwise require cnt>=need
					if (hasExplicitCount) {
						return cnt == need ? 1.0 : 0.0;
					}
					return cnt >= need ? 1.0 : 0.0;
				}
				if (name_up == "INSIDE") {
					if (ce->args.size() < 1) return 0.0;
					std::string target;
					const Expr* a0 = ce->args[0].get();
					if (a0->type == Expr::IDENT) target = static_cast<const IdentExpr*>(a0)->name;
					else if (a0->type == Expr::PROP_ACCESS) target = static_cast<const PropAccessExpr*>(a0)->object;
					if (target.empty()) return 0.0;
					auto it = scene.find(target);
					if (it == scene.end()) return 0.0;
					for (const auto &b : it->second) {
						bool inside = self.x >= b.x && self.right() <= b.right() && self.y >= b.y && self.bottom() <= b.bottom();
						if (inside) return 1.0;
					}
					return 0.0;
				}
				if (name_up == "OVERLAP") {
					if (ce->args.size() < 1) return 0.0;
					std::string target;
					const Expr* a0 = ce->args[0].get();
					if (a0->type == Expr::IDENT) target = static_cast<const IdentExpr*>(a0)->name;
					else if (a0->type == Expr::PROP_ACCESS) target = static_cast<const PropAccessExpr*>(a0)->object;
					if (target.empty()) return 0.0;
					auto it = scene.find(target);
					if (it == scene.end()) return 0.0;
					for (const auto &b : it->second) {
						double iou = compute_iou(self, b);
						if (iou > 0.0) return 1.0;
					}
					return 0.0;
				}
				if (name_up == "CLOSE_TO") {
					if (ce->args.size() < 1) return 0.0;
					std::string target;
					const Expr* a0 = ce->args[0].get();
					if (a0->type == Expr::IDENT) target = static_cast<const IdentExpr*>(a0)->name;
					else if (a0->type == Expr::PROP_ACCESS) target = static_cast<const PropAccessExpr*>(a0)->object;
					if (target.empty()) return 0.0;
					double thr = 0.0;
					if (ce->args.size() >= 2 && ce->args[1]->type == Expr::CONST_NUM) thr = static_cast<const NumberExpr*>(ce->args[1].get())->value;
						else if (ce->qtyRange) thr = static_cast<double>(ce->qtyRange->min);
					auto it = scene.find(target);
					if (it == scene.end()) return 0.0;
					for (const auto &b : it->second) {
						double dx = self.center_x() - b.center_x();
						double dy = self.center_y() - b.center_y();
						double dist = std::sqrt(dx*dx + dy*dy);
						if (dist <= thr) return 1.0;
					}
					return 0.0;
				}
				return 0.0;
			}
		}
		return 0.0;
	}

	/**
	 * @brief 对表达式求值，返回布尔结果。
	 *
	 * 将 eval_num() 的数值结果转换为布尔值（非零为真）。
	 *
	 * @param e 表达式 AST 节点
	 * @param self 当前实例
	 * @param scene 场景数据
	 * @param image 图像尺寸
	 * @return 表达式为真时返回 true
	 */
	bool eval_bool(const Expr* e, const Instance& self, const Scene& scene, const Image& image) {
		double v = eval_num(e, self, scene, image);
		return v != 0.0;
	}

	/**
	 * @brief 获取实例的指定属性值。
	 *
	 * 支持的属性：
	 * - x, y, width, height — 边界框坐标和尺寸
	 * - right, bottom — 右边界和下边界
	 * - center_x, center_y — 中心点坐标
	 * - area — 面积
	 * - aspect_ratio — 宽高比
	 * - conf, confidence — 置信度
	 *
	 * @param inst 实例对象
	 * @param prop 属性名
	 * @return 属性值，未匹配到则返回 0.0
	 */
	static double get_instance_prop(const Instance& inst, const std::string& prop) {
		if (prop=="x")							return inst.x;
		if (prop=="y")							return inst.y;
		if (prop=="width")						return inst.width;
		if (prop=="height")						return inst.height;
		if (prop=="right")						return inst.right();
		if (prop=="bottom")						return inst.bottom();
		if (prop=="center_x")					return inst.center_x();
		if (prop=="center_y")					return inst.center_y();
		if (prop=="area")						return inst.area();
		if (prop=="aspect_ratio")				return inst.aspect_ratio();
		if (prop=="conf" || prop=="confidence") return inst.conf;
		return 0.0;
	}

	/**
	 * @brief 获取图像的指定属性值。
	 *
	 * 支持的属性：width、height。
	 *
	 * @param img 图像对象
	 * @param prop 属性名
	 * @return 属性值，未匹配到则返回 0.0
	 */
	static double get_image_prop(const Image& img, const std::string& prop) {
		if (prop=="width")			return img.width;
		if (prop=="height")			return img.height;
		return 0.0;
	}

	/**
	 * @brief 计算两个实例的 IoU（交并比，Intersection over Union）。
	 *
	 * IoU = 交集面积 / 并集面积。若两实例不相交或并集为 0，则返回 0.0。
	 *
	 * @param a 实例 A
	 * @param b 实例 B
	 * @return IoU 值，范围 [0.0, 1.0]
	 */
	static double compute_iou(const Instance& a, const Instance& b) {
		double ix1 = std::max(a.x, b.x);
		double iy1 = std::max(a.y, b.y);
		double ix2 = std::min(a.right(), b.right());
		double iy2 = std::min(a.bottom(), b.bottom());
		double iw = ix2 - ix1;
		double ih = iy2 - iy1;
		if (iw <= 0 || ih <= 0) return 0.0;
		double inter = iw * ih;
		double uni = a.area() + b.area() - inter;
		return uni>0 ? inter/uni : 0.0;
	}
};

} // namespace postanvil

