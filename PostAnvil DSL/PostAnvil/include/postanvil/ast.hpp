/**
 * @file   ast.hpp
 * @brief  定义 PostAnvil DSL 的抽象语法树（AST）节点类型。
 * @detail 本文件包含了 PostAnvil DSL 的所有 AST 节点定义，包括：
 *		   表达式节点（常量、标识符、属性访问、一元/二元运算、谓词调用）
 *		   数量范围节点（用于谓词中的数量约束）
 *		   规则节点（Rule），关联目标类别与条件表达式
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include <memory>
#include <string>
#include <vector>

namespace postanvil {

/**
 * @brief 所有表达式的基类。
 */
struct Expr {
	/**
	 * @brief Type 枚举，表示表达式的具体类型。
	 */
	enum class Type {
		CONST_NUM,		//< 数值常量
		IDENT,			//< 标识符
		PROP_ACCESS,	//< 属性访问
		BINARY,			//< 二元运算
		UNARY,			//< 一元运算
		CALL,			//< 函数/谓词调用
		UNDEFINED		//< 未定义类型
	};

	Type type = Type::UNDEFINED;

	/**
	 * @brief 虚析构函数，确保派生类正确析构。
	 */
	virtual ~Expr() = default;
};

/**
 * @brief 数值常量表达式。
 */
struct NumberExpr : Expr {
	double value;		//< 常量值

	/**
	 * @brief 构造数值常量表达式
	 * @param v 常量值
	 */
	explicit NumberExpr(double v): value(v)
	{
		type = Type::CONST_NUM;
	}
};

/**
 * @brief 标识符表达式，变量或类名。
 */
struct IdentExpr : Expr {
	std::string name;	//< 标识符名称

	/**
	 * @brief 构造标识符表达式
	 * @param n 标识符名称
	 */
	explicit IdentExpr(std::string n): name(std::move(n))
	{
		type = Type::IDENT;
	}
};

/**
 * @brief 属性访问表达式，例如 object.property。
 *
 * object 可以是 'self'、'image' 或类别名。
 */
struct PropAccessExpr : Expr {
	std::string object;		//< 对象名（self/image/类名）
	std::string prop;		//< 属性名（width/height/conf 等）
	
	/**
	 * @brief 构造属性访问表达式
	 * @param o 对象名
	 * @param p 属性名
	 */
	PropAccessExpr(std::string o, std::string p)
		: object(std::move(o)), prop(std::move(p))
	{
		type = Type::PROP_ACCESS;
	}
};

/**
 * @brief 一元表达式，例如 -x 或 NOT x。
 */
struct UnaryExpr : Expr {
	std::string op;				//< 操作符，例如 "NOT" 或 "-"
	std::unique_ptr<Expr> rhs;	//< 右操作数表达式

	/**
	 * @brief 构造一元表达式
	 * @param op_ 操作符字符串
	 * @param r 右操作数（唯一指针，所有权转移）
	 */
	UnaryExpr(std::string op_, std::unique_ptr<Expr> r)
		: op(std::move(op_)), rhs(std::move(r))
	{
		type = Type::UNARY;
	}
};

/**
 * @brief 二元表达式，例如 a + b、a AND b、a > b 等。
 */
struct BinaryExpr : Expr {
	std::string op;				//< 操作符
	std::unique_ptr<Expr> lhs;	//< 左操作数
	std::unique_ptr<Expr> rhs;	//< 右操作数
	
	/**
	 * @brief 构造二元表达式
	 * @param l 左操作数（唯一指针，所有权转移）
	 * @param op_ 操作符字符串
	 * @param r 右操作数（唯一指针，所有权转移）
	 */
	BinaryExpr(std::unique_ptr<Expr> l, std::string op_, std::unique_ptr<Expr> r)
		: op(std::move(op_)), lhs(std::move(l)), rhs(std::move(r))
	{
		type = Type::BINARY;
	}
};

/**
 * @brief 用于表示谓词中的数量范围，例如 "3"（单值）或 "3-5"（范围）。
 */
struct QuantityRange {
	int min;					//< 最小数量
	int max;					//< 最大数量，当 is_range==false 时等于 min
	bool is_range;				//< 是否为范围模式（true 表示 [min, max] 区间，false 表示精确匹配）

	/**
	 * @brief 构造单值数量（精确匹配）
	 * @param v 数量值
	 */
	explicit QuantityRange(int v): min(v), max(v), is_range(false)
	{
	}

	/**
	 * @brief 构造范围数量
	 * @param a 最小数量
	 * @param b 最大数量
	 */
	QuantityRange(int a, int b): min(a), max(b), is_range(true)
	{
	}
};

/**
 * @brief 函数/谓词调用表达式。
 *
 * 用于表示以下形式的调用：
 * - 函数调用：`abs(x)`、`iou(self, B)`
 * - 空格分隔谓词：`CONTAINS B 3`、`CLOSE_TO A 50`
 *
 * 谓词可以附带可选的数量范围（qtyRange）。
 */
struct CallExpr : Expr {
	std::string name;									//< 函数或谓词名称
	std::vector<std::unique_ptr<Expr>> args;			//< 参数列表
	std::unique_ptr<QuantityRange> qtyRange = nullptr;	//< 可选的数量范围，无则 nullptr
	
	/**
	 * @brief 构造调用表达式
	 * @param n 函数/谓词名称
	 */
	explicit CallExpr(std::string n)
		: name(std::move(n))
	{
		type = Type::CALL;
	}
};

/**
 * @brief 一个规则（Rule），包含目标类别（或 GLOBAL）和一组条件表达式。
 *
 * 规则是 DSL 的核心单元。每个规则指定一个目标类别，当所有条件满足时，
 * 该类别下的实例被保留。GLOBAL 规则对所有实例生效。
 */
struct Rule {
	std::string target;								//< 目标类别名称，或 "GLOBAL" 表示全局规则
	std::vector<std::unique_ptr<Expr>> conditions;	//< 条件表达式列表（AND 关系）
};

} // namespace postanvil

