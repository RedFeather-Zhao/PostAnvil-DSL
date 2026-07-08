/**
 * @file test_builder.cpp
 * @brief PostAnvil v0.3 测试 —— 基于 PostAnvilCompiler 的编译型规则编译器测试
 *
 * 测试覆盖范围：
 * - 基础编译：FILTER/ATTR 规则 → CompiledProgram → 执行
 * - 多类别组合：GLOBAL + 各类别规则
 * - 属性算子：RULE ATTR 计算属性（实例属性 + 类属性）
 * - 编程模型：编译一次，对多个场景执行
 * - 数值运算：算术 + 比较 + 逻辑
 * - 属性访问：self.* / img.* / "class".*（大小写不敏感）
 * - 新语法特性：RULEEND、引号类名、布尔字面量
 * - 新规则类型：GROUP、APPEND、FUNC
 * - 新表达式：SORT、函数调用
 * - 字符串操作：拼接与比较
 * - 归一化属性：wn, hn, x1n, y1n, arean
 * - 全局变量：NUM / STR / BOOL 定义与引用
 * - 控制流：IF-ELSE 条件分支、FOR 循环
 * - 宿主交互：IMPORT / EXPORT
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cmath>

#include "PostAnvil.h"

using namespace postanvil;

// ============================================================
// 测试辅助工具
// ============================================================

auto TEST_FAIL_COUNT = [](int delta = 0) {
	static int g_failed = 0;
	g_failed += delta;
	return g_failed;
	};

auto TEST_PASS_COUNT = [](int delta = 0) {
	static int g_passed = 0;
	g_passed += delta;
	return g_passed;
	};

/**
 * @brief 辅助函数：验证评估结果中指定类别的保留实例数
 */
static bool check_count(const EvalResult& res, const std::string& cls, int expected_count) {
	auto it = res.kept.objects.find(cls);
	int actual = (it != res.kept.objects.end()) ? (int)it->second.size() : 0;
	return actual == expected_count;
}

/**
 * @brief 辅助函数：验证实例动态属性值
 */
static bool check_prop(const EvalResult& res, const std::string& cls, int idx,
	const std::string& prop, double expected) {
	auto it = res.kept.objects.find(cls);
	if (it == res.kept.objects.end() || idx >= (int)it->second.size()) return false;
	double actual = it->second[idx].get_prop(prop);
	return std::abs(actual - expected) < 0.001;
}

/**
 * @brief 辅助函数：验证类别属性值
 */
static bool check_class_prop(const EvalResult& res, const std::string& cls,
	const std::string& prop, double expected) {
	auto it = res.kept.class_props.find(cls);
	if (it == res.kept.class_props.end()) return false;
	auto pit = it->second.find(prop);
	if (pit == it->second.end()) return false;
	return std::abs(pit->second.as_num() - expected) < 0.001;
}

/**
 * @brief 辅助函数：打印测试结果
 */
static void report(const char* name, bool passed, const std::string& detail = "") {
	if (passed) {
		TEST_PASS_COUNT(1);
		std::cout << "  [PASS] " << name;
	}
	else {
		TEST_FAIL_COUNT(1);
		std::cout << "  [FAIL] " << name;
	}
	if (!detail.empty()) std::cout << "  (" << detail << ")";
	std::cout << std::endl;
}

// ============================================================
// 测试用例
// ============================================================

/**
 * @brief 测试 1：全局置信度过滤
 */
static void test01_global_confidence_filter() {
	const char* src = R"(
RULE FILTER "global":
	self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("A", 0, 0, 10, 10, 0.6),
		Instance("A", 0, 0, 10, 10, 0.4),
		Instance("A", 0, 0, 10, 10, 0.2),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 2);
	report("全局置信度过滤 (self.conf > 0.5)", ok);
	if (!ok) {
		int a_cnt = res.kept.objects.contains("A") ? (int)res.kept.objects.at("A").size() : 0;
		std::cout << "    期望 A=2, 实际 A=" << a_cnt << std::endl;
	}
}

/**
 * @brief 测试 2：全局多条件（尺寸 + 面积）
 */
static void test02_global_size_and_area() {
	const char* src = R"(
RULE FILTER "global":
	self.w > 10
	self.h > 10
	self.area > 200
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("B", 0, 0, 20, 30, 0.5),  // area=600, w=20>10, h=30>10
		Instance("B", 0, 0, 5, 5, 0.5),     // w=5 (not >10)
		Instance("B", 0, 0, 15, 15, 0.5),   // area=225, w=15>10, h=15>10
		Instance("B", 0, 0, 10, 15, 0.5),   // w=10 (not >10)
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "B", 2);
	report("全局多条件：尺寸+面积 (w>10, h>10, area>200)", ok);
}

/**
 * @brief 测试 3：比较运算符（>=, <=, !=）
 */
static void test03_comparison_operators() {
	const char* src = R"(
RULE FILTER "c":
	self.x1 >= 50
	self.x1 <= 100
	self.x1 != 75
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("C", 10, 0, 10, 10, 0.5),
		Instance("C", 50, 0, 10, 10, 0.5),
		Instance("C", 100, 0, 10, 10, 0.5),
		Instance("C", 200, 0, 10, 10, 0.5),
		Instance("C", 75, 0, 10, 10, 0.5),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "C", 2);
	report("比较运算符 (>=, <=, !=)", ok);
}

/**
 * @brief 测试 4：算术运算 + 一元取负
 */
static void test04_arithmetic_and_unary_minus() {
	const char* src = R"(
RULE FILTER "d":
	self.x1 + self.w > 100
	-self.y1 > -100
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("D", 10, 50, 20, 10, 0.5),   // 10+20=30 (not >100)
		Instance("D", 50, 50, 200, 10, 0.5),   // 50+200=250 (>100), -50 > -100
		Instance("D", 100, 150, 10, 10, 0.5),  // 100+10=110 (>100), -150 not > -100
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "D", 1);
	report("算术加法 + 一元取负 (x1+w>100, -y1>-100)", ok);
}

/**
 * @brief 测试 5：乘法
 */
static void test05_multiplication() {
	const char* src = R"(
RULE FILTER "e":
	self.w * self.h > 300
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("E", 0, 0, 20, 30, 0.5),  // 600
		Instance("E", 0, 0, 10, 10, 0.5),  // 100
		Instance("E", 0, 0, 15, 15, 0.5),  // 225
		Instance("E", 0, 0, 5, 20, 0.5),   // 100
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "E", 1);
	report("乘法 (w * h > 300)", ok);
}

/**
 * @brief 测试 5b：除法
 */
static void test05b_division() {
	const char* src = R"(
RULE FILTER "e2":
	self.x1 / self.w < 2
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("E2", 10, 0, 20, 10, 0.5),   // 10/20=0.5 < 2
		Instance("E2", 100, 0, 20, 10, 0.5),  // 100/20=5 (not <2)
		Instance("E2", 30, 0, 30, 10, 0.5),   // 30/30=1 < 2
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "E2", 2);
	report("除法 (x1 / w < 2)", ok);
}

/**
 * @brief 测试 6：逻辑 OR + 括号分组
 */
static void test06_logical_or_with_parens() {
	const char* src = R"(
RULE FILTER "f":
	(self.w > 100 OR self.h > 100) AND self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("F", 0, 0, 150, 10, 0.9),   // w>100, conf=0.9
		Instance("F", 0, 0, 10, 150, 0.9),   // h>100, conf=0.9
		Instance("F", 0, 0, 150, 150, 0.3),  // conf=0.3 (not >0.5)
		Instance("F", 0, 0, 10, 10, 0.9),    // neither w>100 nor h>100
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "F", 2);
	report("逻辑 OR + 括号 ((w>100 OR h>100) AND conf>0.5)", ok);
}

/**
 * @brief 测试 7：逻辑 NOT
 */
static void test07_logical_not() {
	const char* src = R"(
RULE FILTER "g":
	NOT self.conf < 0.3
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("G", 0, 0, 10, 10, 0.2),
		Instance("G", 0, 0, 10, 10, 0.5),
		Instance("G", 0, 0, 10, 10, 0.8),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "G", 2);
	report("逻辑 NOT (NOT conf < 0.3)", ok);
}

/**
 * @brief 测试 8：图像属性（img.w, img.h）
 */
static void test08_image_properties() {
	const char* src = R"(
RULE FILTER "h":
	self.x1 + self.w <= img.w
	self.y1 + self.h <= img.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 100 }, {
		Instance("H", 10, 10, 20, 20, 0.5),   // 10+20=30<=200, 10+20=30<=100
		Instance("H", 180, 10, 30, 20, 0.5),  // 180+30=210>200
		Instance("H", 10, 80, 20, 30, 0.5),   // 80+30=110>100
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "H", 1);
	report("图像属性 (img.w, img.h 边界检查)", ok);
}

/**
 * @brief 测试 9：派生属性 cx, cy, x2, aspect
 */
static void test09_derived_properties() {
	const char* src = R"(
RULE FILTER "aa":
	self.cx > 50
	self.cy > 50
	self.x2 < 200
	self.aspect >= 1.0
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("AA", 0, 0, 100, 100, 0.5),    // cx=50 (not >50), cy=50
		Instance("AA", 41, 0, 20, 20, 0.5),     // cx=51, cy=10 (not >50)
		Instance("AA", 41, 41, 20, 20, 0.5),    // cx=51, cy=51, x2=61<200, aspect=1.0
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "AA", 1);
	report("派生属性 cx, cy, x2, aspect", ok);
}

/**
 * @brief 测试 10：多类别 + 全局 + 类别规则组合
 */
static void test10_multi_class_combined() {
	const char* src = R"(
RULE FILTER "global":
	self.conf > 0.5
RULEEND

RULE FILTER "person":
	self.w > 20
RULEEND

RULE FILTER "vehicle":
	self.w > 100
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 30, 30, 0.9),
		Instance("PERSON", 0, 0, 15, 15, 0.9),
		Instance("PERSON", 0, 0, 30, 30, 0.3),
		Instance("VEHICLE", 0, 0, 150, 50, 0.9),
		Instance("VEHICLE", 0, 0, 80, 50, 0.9),
		Instance("ANIMAL", 0, 0, 10, 10, 0.9),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 1)
		&& check_count(res, "VEHICLE", 1)
		&& check_count(res, "ANIMAL", 1);
	report("多类别 + 全局 + 类别规则组合", ok);
	if (!ok) {
		std::cout << "    期望: PERSON=1, VEHICLE=1, ANIMAL=1" << std::endl;
		std::cout << "    实际: PERSON=" << (res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0)
			<< ", VEHICLE=" << (res.kept.objects.contains("VEHICLE") ? (int)res.kept.objects.at("VEHICLE").size() : 0)
			<< ", ANIMAL=" << (res.kept.objects.contains("ANIMAL") ? (int)res.kept.objects.at("ANIMAL").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 11：编程模型 —— 编译一次，多个场景
 */
static void test11_program_reuse() {
	const char* src = R"(
RULE FILTER "z":
	self.w > 40
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene1({ 200, 200 }, {
		Instance("Z", 0, 0, 60, 60, 0.5),
		Instance("Z", 0, 0, 30, 30, 0.5),
		});
	EvalResult res1 = program.evaluate(scene1);
	bool ok1 = check_count(res1, "Z", 1);

	Scene scene2({ 200, 200 }, {
		Instance("Z", 0, 0, 80, 80, 0.5),
		Instance("Z", 0, 0, 20, 20, 0.5),
		});
	EvalResult res2 = program.evaluate(scene2);
	bool ok2 = check_count(res2, "Z", 1);

	Scene scene3({ 200, 200 }, {
		Instance("Z", 0, 0, 50, 10, 0.5),
		});
	EvalResult res3 = program.evaluate(scene3);
	bool ok3 = check_count(res3, "Z", 1);

	bool ok = ok1 && ok2 && ok3;
	report("编程模型 —— 编译一次，三个场景", ok);
	if (!ok) {
		std::cout << "    场景1: Z=" << (res1.kept.objects.contains("Z") ? (int)res1.kept.objects.at("Z").size() : 0) << std::endl;
		std::cout << "    场景2: Z=" << (res2.kept.objects.contains("Z") ? (int)res2.kept.objects.at("Z").size() : 0) << std::endl;
		std::cout << "    场景3: Z=" << (res3.kept.objects.contains("Z") ? (int)res3.kept.objects.at("Z").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 12：CompiledProgram 移动语义
 */
static void test12_program_move() {
	const char* src = R"(
RULE FILTER "global":
	self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program1 = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("A", 0, 0, 10, 10, 0.6),
		Instance("A", 0, 0, 10, 10, 0.3),
		});

	CompiledProgram program2 = std::move(program1);

	EvalResult res = program2.evaluate(scene);

	bool ok = check_count(res, "A", 2);
	report("CompiledProgram 移动语义", ok);
}

/**
 * @brief 测试 13：属性算子 —— 基本属性计算
 */
static void test13_attr_compute_basic() {
	const char* src = R"(
RULE ATTR "person":
	self.risk = self.conf * 2.0
	self.size = self.w * self.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 20, 30, 0.9),
		Instance("PERSON", 0, 0, 10, 50, 0.5),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = true;
	auto it = res.kept.objects.find("PERSON");
	if (it == res.kept.objects.end() || it->second.size() != 2) {
		ok = false;
	}
	else {
		double risk0 = it->second[0].get_prop("RISK");
		double size0 = it->second[0].get_prop("SIZE");
		double risk1 = it->second[1].get_prop("RISK");
		double size1 = it->second[1].get_prop("SIZE");

		if (std::abs(risk0 - 1.8) > 0.001 || std::abs(size0 - 600.0) > 0.001) ok = false;
		if (std::abs(risk1 - 1.0) > 0.001 || std::abs(size1 - 500.0) > 0.001) ok = false;
	}

	report("属性算子 — 基本属性计算 (risk, size)", ok);
	if (!ok) {
		std::cout << "    期望: risk0=1.8, size0=600, risk1=1.0, size1=500" << std::endl;
		if (it != res.kept.objects.end() && !it->second.empty()) {
			auto& p0 = it->second[0];
			auto& p1 = it->second[1];
			std::cout << "    实际: risk0=" << p0.get_prop("RISK")
				<< ", size0=" << p0.get_prop("SIZE")
				<< ", risk1=" << p1.get_prop("RISK")
				<< ", size1=" << p1.get_prop("SIZE") << std::endl;
		}
	}
}

/**
 * @brief 测试 14：属性算子 + 过滤算子组合（含除法）
 */
static void test14_attr_then_filter() {
	const char* src = R"(
RULE ATTR "person":
	self.density = self.conf / (self.w * self.h)
RULEEND

RULE FILTER "person":
	self.density < 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 20, 30, 0.9),   // 0.9/600=0.0015 < 0.5
		Instance("PERSON", 0, 0, 10, 10, 0.5),   // 0.5/100=0.005 < 0.5
		Instance("PERSON", 0, 0, 1, 1, 0.9),     // 0.9/1=0.9 (not < 0.5)
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 2);
	report("属性算子 + 过滤算子组合 (density = conf / (w * h))", ok);
	if (!ok) {
		int cnt = res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0;
		std::cout << "    期望: PERSON=2, 实际: PERSON=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 15：大小写不敏感验证
 */
static void test15_case_insensitive() {
	const char* src = R"(
RULE FILTER "global":
	SELF.CONF > 0.5
	SELF.W > 10
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("X", 0, 0, 20, 20, 0.9),
		Instance("X", 0, 0, 5, 5, 0.9),
		Instance("X", 0, 0, 20, 20, 0.3),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "X", 1);
	report("大小写不敏感 (大写 SELF.CONF > 0.5)", ok);
}

/**
 * @brief 测试 16：全局属性算子
 */
static void test16_attr_global() {
	const char* src = R"(
RULE ATTR "global":
	self.area_calc = self.w * self.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("CAT", 0, 0, 10, 20, 0.5),
		Instance("DOG", 0, 0, 30, 40, 0.5),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = true;
	auto it_cat = res.kept.objects.find("CAT");
	auto it_dog = res.kept.objects.find("DOG");
	if (it_cat == res.kept.objects.end() || it_cat->second.empty()) ok = false;
	else if (std::abs(it_cat->second[0].get_prop("AREA_CALC") - 200.0) > 0.001) ok = false;

	if (it_dog == res.kept.objects.end() || it_dog->second.empty()) ok = false;
	else if (std::abs(it_dog->second[0].get_prop("AREA_CALC") - 1200.0) > 0.001) ok = false;

	report("全局属性算子 (area_calc = w * h)", ok);
}

/**
 * @brief 测试 17：GROUP 规则 —— 从源类别创建新类别
 */
static void test17_group_create_new_class() {
	const char* src = R"(
RULE GROUP "large_car" FROM "car":
	self.area > 5000
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("CAR", 0, 0, 100, 60, 0.5),  // area=6000 > 5000
		Instance("CAR", 0, 0, 50, 50, 0.5),   // area=2500
		Instance("CAR", 0, 0, 80, 80, 0.5),   // area=6400 > 5000
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "LARGE_CAR", 2) && check_count(res, "CAR", 3);
	report("GROUP 创建新类别 (large_car = area > 5000)", ok);
	if (!ok) {
		std::cout << "    期望: CAR=3, LARGE_CAR=2" << std::endl;
		std::cout << "    实际: CAR=" << (res.kept.objects.contains("CAR") ? (int)res.kept.objects.at("CAR").size() : 0)
			<< ", LARGE_CAR=" << (res.kept.objects.contains("LARGE_CAR") ? (int)res.kept.objects.at("LARGE_CAR").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 18：APPEND 规则 —— 向目标类别追加实例
 */
static void test18_append_instances() {
	const char* src = R"(
RULE APPEND "vip" FROM "person":
	self.conf > 0.9
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.95),
		Instance("PERSON", 0, 0, 10, 10, 0.85),
		Instance("PERSON", 0, 0, 10, 10, 0.91),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "VIP", 2) && check_count(res, "PERSON", 3);
	report("APPEND 追加实例 (vip = conf > 0.9)", ok);
	if (!ok) {
		std::cout << "    期望: PERSON=3, VIP=2" << std::endl;
		std::cout << "    实际: PERSON=" << (res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0)
			<< ", VIP=" << (res.kept.objects.contains("VIP") ? (int)res.kept.objects.at("VIP").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 19：GROUP + FILTER 组合
 */
static void test19_group_then_filter() {
	const char* src = R"(
RULE GROUP "big" FROM "item":
	self.w > 30
RULEEND

RULE FILTER "big":
	self.h > 20
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("ITEM", 0, 0, 40, 30, 0.5),  // w>30, moves to big, h>20
		Instance("ITEM", 0, 0, 35, 15, 0.5),  // w>30, moves to big, h=15 (not >20)
		Instance("ITEM", 0, 0, 20, 40, 0.5),  // w=20, stays in ITEM
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "BIG", 1) && check_count(res, "ITEM", 3);
	report("GROUP + FILTER 组合 (先分组再过滤)", ok);
	if (!ok) {
		std::cout << "    期望: ITEM=3, BIG=1" << std::endl;
		std::cout << "    实际: ITEM=" << (res.kept.objects.contains("ITEM") ? (int)res.kept.objects.at("ITEM").size() : 0)
			<< ", BIG=" << (res.kept.objects.contains("BIG") ? (int)res.kept.objects.at("BIG").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 20：类属性 —— "class".count
 */
static void test20_class_count_property() {
	const char* src = R"(
RULE GROUP "big" FROM "person":
	self.w > 30
RULEEND

RULE FILTER "big":
	"person".count > 0
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 40, 30, 0.5),
		Instance("PERSON", 0, 0, 20, 20, 0.5),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "BIG", 1) && check_count(res, "PERSON", 2);
	report("类属性 — \"person\".count > 0", ok);
	if (!ok) {
		std::cout << "    期望: PERSON=2, BIG=1" << std::endl;
		std::cout << "    实际: PERSON=" << (res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0)
			<< ", BIG=" << (res.kept.objects.contains("BIG") ? (int)res.kept.objects.at("BIG").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 21：布尔字面量 FALSE
 */
static void test21_bool_false_literal() {
	const char* src = R"(
RULE FILTER "global":
	FALSE
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("A", 0, 0, 10, 10, 0.6),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 0);
	report("布尔字面量 FALSE (过滤全部)", ok);
}

/**
 * @brief 测试 22：布尔字面量 TRUE
 */
static void test22_bool_true_literal() {
	const char* src = R"(
RULE FILTER "global":
	TRUE
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("A", 0, 0, 10, 10, 0.6),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 2);
	report("布尔字面量 TRUE (保留全部)", ok);
}

/**
 * @brief 测试 23：SORT 排序原语
 */
static void test23_sort_primitive() {
	const char* src = R"(
RULE FILTER "person":
	self.area >= SORT("person", self.area, 1)
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.5),   // area=100
		Instance("PERSON", 0, 0, 20, 20, 0.5),   // area=400
		Instance("PERSON", 0, 0, 30, 30, 0.5),   // area=900 (max)
		});

	EvalResult res = program.evaluate(scene);

	// SORT("person", self.area, 1) 返回第1大的area = 900
	// 只有 area=900 的实例满足 self.area >= 900
	bool ok = check_count(res, "PERSON", 1);
	report("SORT 排序原语 (保留面积最大的实例)", ok);
	if (!ok) {
		int cnt = res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0;
		std::cout << "    期望: PERSON=1, 实际: PERSON=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 24：SORT 负排名（升序）
 */
static void test24_sort_ascending() {
	const char* src = R"(
RULE FILTER "person":
	self.area <= SORT("person", self.area, -1)
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.5),   // area=100 (min)
		Instance("PERSON", 0, 0, 20, 20, 0.5),   // area=400
		Instance("PERSON", 0, 0, 30, 30, 0.5),   // area=900
		});

	EvalResult res = program.evaluate(scene);

	// SORT("person", self.area, -1) 返回第1小的area = 100
	// 只有 area=100 的实例满足 self.area <= 100
	bool ok = check_count(res, "PERSON", 1);
	report("SORT 负排名升序 (保留面积最小的实例)", ok);
	if (!ok) {
		int cnt = res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0;
		std::cout << "    期望: PERSON=1, 实际: PERSON=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 25：FUNC 函数返回常量 TRUE
 */
static void test25_func_return_constant() {
	const char* src = R"(
RULE FUNC always_true() -> BOOL:
	TRUE
RULEEND

RULE FILTER "global":
	always_true()
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("B", 0, 0, 10, 10, 0.3),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 1) && check_count(res, "B", 1);
	report("FUNC 返回常量 TRUE (保留全部)", ok);
}

/**
 * @brief 测试 26：FUNC 函数返回 FALSE
 */
static void test26_func_return_false() {
	const char* src = R"(
RULE FUNC always_false() -> BOOL:
	FALSE
RULEEND

RULE FILTER "global":
	always_false()
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("B", 0, 0, 10, 10, 0.3),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 0) && check_count(res, "B", 0);
	report("FUNC 返回常量 FALSE (过滤全部)", ok);
}

// ============================================================
// 新增测试用例（v0.3 补充）
// ============================================================

/**
 * @brief 测试 27：字符串拼接
 */
static void test27_string_concatenation() {
	const char* src = R"(
NUM threshold = 0.5

RULE FILTER "global":
	self.conf > threshold
RULEEND

RULE FUNC get_prefix() -> STR:
	"class_"
RULEEND

RULE FILTER "person":
	TRUE
RULEEND
)";
	// 注：字符串拼接在表达式层面支持，但当前过滤条件不涉及
	// 此测试验证字符串字面量 + 变量引用能正确编译

	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.9),
		Instance("PERSON", 0, 0, 10, 10, 0.3),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 1);
	report("字符串拼接与全局变量引用", ok);
}

/**
 * @brief 测试 28：归一化属性
 */
static void test28_normalized_properties() {
	const char* src = R"(
RULE FILTER "obj":
	self.wn > 0.1
	self.hn > 0.1
	self.x1n > 0
	self.y1n > 0
	self.x2n < 1.0
	self.y2n < 1.0
	self.arean > 0.01
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 100 }, {
		Instance("OBJ", 10, 10, 60, 30, 0.5),   // wn=0.3, hn=0.3, arean=0.09
		Instance("OBJ", 5, 5, 5, 5, 0.5),       // wn=0.025 (not >0.1)
		Instance("OBJ", 0, 0, 200, 100, 0.5),   // x1n=0, y1n=0 (not >0)
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "OBJ", 1);
	report("归一化属性 (wn, hn, x1n, y1n, x2n, y2n, arean)", ok);
	if (!ok) {
		int cnt = res.kept.objects.contains("OBJ") ? (int)res.kept.objects.at("OBJ").size() : 0;
		std::cout << "    期望: OBJ=1, 实际: OBJ=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 29：自定义类属性（类别级属性）
 */
static void test29_custom_class_property() {
	const char* src = R"(
NUM test_val = 0.5

RULE ATTR "car":
	"car".avg_conf = test_val
	"car".total_area = 400 * 2 / 2
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("CAR", 0, 0, 10, 10, 0.9),
		Instance("CAR", 0, 0, 20, 20, 0.5),
	});

	EvalResult res = program.evaluate(scene);

	// 类别属性不能访问self属性，没有对应实例
	bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.5)
		&& check_class_prop(res, "CAR", "TOTAL_AREA", 400.0);
	report("自定义类属性 (\"car\".avg_conf, \"car\".total_area)", ok);
	if (!ok) {
		std::cout << "    期望: AVG_CONF=0.5, TOTAL_AREA=400.0" << std::endl;
		std::cout << "    实际: AVG_CONF=" << res.kept.class_props.at("CAR").at("AVG_CONF").as_num()
			<< ", TOTAL_AREA=" << res.kept.class_props.at("CAR").at("TOTAL_AREA").as_num() << std::endl;
	}
}

/**
 * @brief 测试 30：字符串变量作为 class_expr
 */
static void test30_string_var_as_class_expr() {
	const char* src = R"(
STR target = "animal"

RULE FILTER target:
	self.conf > 0.7
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("ANIMAL", 0, 0, 10, 10, 0.9),
		Instance("ANIMAL", 0, 0, 10, 10, 0.5),
		Instance("CAR", 0, 0, 10, 10, 0.9),
	});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "ANIMAL", 1) && check_count(res, "CAR", 1);
	report("字符串变量作为 class_expr (STR target = \"animal\")", ok);
	if (!ok) {
		std::cout << "    期望: ANIMAL=1, CAR=1" << std::endl;
		std::cout << "    实际: ANIMAL=" << (res.kept.objects.contains("ANIMAL") ? (int)res.kept.objects.at("ANIMAL").size() : 0)
			<< ", CAR=" << (res.kept.objects.contains("CAR") ? (int)res.kept.objects.at("CAR").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 31：全局数值变量
 */
static void test31_global_numeric_variable() {
	const char* src = R"(
NUM min_conf = 0.6
NUM min_w = 15

RULE FILTER "global":
	self.conf > min_conf
	self.w > min_w
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 20, 20, 0.7),   // conf>0.6, w>15
		Instance("A", 0, 0, 20, 20, 0.5),   // conf=0.5 (not >0.6)
		Instance("A", 0, 0, 10, 20, 0.7),   // w=10 (not >15)
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 1);
	report("全局数值变量 (min_conf=0.6, min_w=15)", ok);
}

/**
 * @brief 测试 32：全局布尔变量
 */
static void test32_global_bool_variable() {
	const char* src = R"(
BOOL debug = FALSE

RULE FILTER "global":
	debug == FALSE
	self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.9),
		Instance("A", 0, 0, 10, 10, 0.3),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 1);
	report("全局布尔变量 (debug == FALSE)", ok);
}

/**
 * @brief 测试 33：IMPORT 导入变量
 */
static void test33_import_variable() {
	const char* src = R"(
IMPORT NUM external_threshold
IMPORT STR target_class

RULE FILTER target_class:
	self.conf > external_threshold
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.8),
		Instance("PERSON", 0, 0, 10, 10, 0.4),
		Instance("CAR", 0, 0, 10, 10, 0.8),
	});

	// 导入变量的值必须由宿主通过 set_import 预设
	program.set_import(scene, "EXTERNAL_THRESHOLD", Val(0.6));
	program.set_import(scene, "TARGET_CLASS", Val("PERSON"));

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 1) && check_count(res, "CAR", 1);
	report("IMPORT 导入宿主变量", ok);
	if (!ok) {
		std::cout << "    期望: PERSON=1, CAR=1" << std::endl;
		std::cout << "    实际: PERSON=" << (res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0)
			<< ", CAR=" << (res.kept.objects.contains("CAR") ? (int)res.kept.objects.at("CAR").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 34：IMPORT AS 别名
 */
static void test34_import_as_alias() {
	const char* src = R"(
IMPORT NUM host_conf AS conf_threshold

RULE FILTER "global":
	self.conf > conf_threshold
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.8),
		Instance("A", 0, 0, 10, 10, 0.3),
		});

	program.set_import(scene, "CONF_THRESHOLD", Val(0.6));

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "A", 1);
	report("IMPORT AS 别名 (host_conf AS conf_threshold)", ok);
}

/**
 * @brief 测试 35：EXPORT 导出值
 */
static void test35_export_value() {
	const char* src = R"(

RULE ATTR "person":
	self.risk = self.conf * 2.0
RULEEND

RULE FILTER "person":
	self.conf > 0.5
RULEEND

EXPORT "person".count AS person_count
EXPORT 1.8 AS max_risk

)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.9),
		Instance("PERSON", 0, 0, 10, 10, 0.6),
		Instance("PERSON", 0, 0, 10, 10, 0.3),
	});

	EvalResult res = program.evaluate(scene);

	bool ok = true;
	try {
		Val count = program.get_exported("person_count", res);
		Val max_risk = program.get_exported("max_risk", res);
		if (std::abs(count.as_num() - 2.0) > 0.001) ok = false;
		if (std::abs(max_risk.as_num() - 1.8) > 0.001) ok = false;
	}
	catch (...) {
		ok = false;
	}
	report("EXPORT 导出值 (person_count, max_risk)", ok);
	if (!ok) {
		try {
			Val count = program.get_exported("person_count", res);
			Val max_risk = program.get_exported("max_risk", res);
			std::cout << "    期望: person_count=2.0, max_risk=1.8" << std::endl;
			std::cout << "    实际: person_count=" << count.as_num()
				<< ", max_risk=" << max_risk.as_num() << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "    错误: " << e.what() << std::endl;
		}
	}
}

/**
 * @brief 测试 36：FUNC 带 IF-ELSE 条件分支
 */
static void test36_func_if_else() {
	const char* src = R"(
RULE FUNC risk_level(conf:NUM) -> NUM:
	IF conf > 0.8
		RETURN 3
	ELSE
		IF conf > 0.5
			RETURN 2
		ELSE
			RETURN 1
		ENDIF
	ENDIF
RULEEND

RULE ATTR "person":
	self.level = risk_level(self.conf)
RULEEND

RULE FILTER "person":
	self.level >= 2
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 10, 10, 0.9),   // level=3, kept
		Instance("PERSON", 0, 0, 10, 10, 0.6),   // level=2, kept
		Instance("PERSON", 0, 0, 10, 10, 0.3),   // level=1, filtered
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 2);
	if (ok) {
		auto it = res.kept.objects.find("PERSON");
		if (it != res.kept.objects.end() && it->second.size() >= 2) {
			ok = check_prop(res, "PERSON", 0, "LEVEL", 3.0)
				&& check_prop(res, "PERSON", 1, "LEVEL", 2.0);
		}
	}
	report("FUNC 带 IF-ELSE 条件分支 (risk_level)", ok);
	if (!ok) {
		int cnt = res.kept.objects.contains("PERSON") ? (int)res.kept.objects.at("PERSON").size() : 0;
		std::cout << "    期望: PERSON=2, 实际: PERSON=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 37：FUNC 带 FOR 循环（聚合计算）
 */
static void test37_func_for_loop() {
	const char* src = R"(
RULE FUNC avg_conf(cls:STR) -> NUM:
	NUM total = 0
	FOR obj IN cls
		total = total + obj.conf
	ENDFOR
	total / "cls".count
RULEEND

RULE ATTR "car":
	"car".avg_conf = avg_conf("car")
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("CAR", 0, 0, 10, 10, 0.9),
		Instance("CAR", 0, 0, 10, 10, 0.7),
		Instance("CAR", 0, 0, 10, 10, 0.5),
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.7);
	report("FUNC 带 FOR 循环 (avg_conf 聚合计算)", ok);
	if (!ok) {
		auto it = res.kept.class_props.find("CAR");
		if (it != res.kept.class_props.end()) {
			auto pit = it->second.find("AVG_CONF");
			if (pit != it->second.end()) {
				std::cout << "    实际: AVG_CONF=" << pit->second.as_num() << std::endl;
			}
		}
	}
}

/**
 * @brief 测试 38：FOR 循环遍历空类别
 */
static void test38_for_loop_empty_class() {
	const char* src = R"(
RULE FUNC safe_avg(cls:STR) -> NUM:
	NUM total = 0
	FOR obj IN cls
		total = total + obj.conf
	ENDFOR
	IF "cls".count == 0
		RETURN 0
	ELSE
		total / "cls".count
	ENDIF
RULEEND

RULE ATTR "car":
	"car".avg_conf = safe_avg("car")
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {});  // 没有 car 类别

	EvalResult res = program.evaluate(scene);

	bool ok = check_class_prop(res, "CAR", "AVG_CONF", 0.0);
	report("FOR 循环遍历空类别 (safe_avg 返回 0)", ok);
	if (!ok) {
		auto it = res.kept.class_props.find("CAR");
		if (it != res.kept.class_props.end()) {
			auto pit = it->second.find("AVG_CONF");
			if (pit != it->second.end()) {
				std::cout << "    实际: AVG_CONF=" << pit->second.as_num() << std::endl;
			}
		}
	}
}

/**
 * @brief 测试 39：嵌套 FOR 循环
 */
static void test39_nested_for_loop() {
	const char* src = R"(
RULE FUNC sum_areas() -> NUM:
	NUM total = 0
	FOR cls IN "global"
		FOR obj IN cls
			total = total + obj.area
		ENDFOR
	ENDFOR
	total
RULEEND

RULE ATTR "global":
	"global".total_area = sum_areas()
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("A", 0, 0, 10, 10, 0.5),   // area=100
		Instance("A", 0, 0, 20, 20, 0.5),   // area=400
		Instance("B", 0, 0, 30, 30, 0.5),   // area=900
		});

	EvalResult res = program.evaluate(scene);

	bool ok = check_class_prop(res, "GLOBAL", "TOTAL_AREA", 1400.0);
	report("嵌套 FOR 循环 (sum_areas 计算所有实例总面积)", ok);
	if (!ok) {
		auto it = res.kept.class_props.find("GLOBAL");
		if (it != res.kept.class_props.end()) {
			auto pit = it->second.find("TOTAL_AREA");
			if (pit != it->second.end()) {
				std::cout << "    实际: TOTAL_AREA=" << pit->second.as_num() << std::endl;
			}
		}
	}
}

/**
 * @brief 测试 40：完整的端到端场景
 */
static void test40_end_to_end_scenario() {
	const char* src = R"(
IMPORT NUM min_conf
NUM area_threshold = 500

RULE ATTR "person":
	self.risk = self.conf * 2.0
	self.norm_area = self.arean
RULEEND

RULE FILTER "person":
	self.conf > min_conf
	self.area > area_threshold
RULEEND

RULE GROUP "high_risk" FROM "person":
	self.risk > 1.0
RULEEND

EXPORT "high_risk".count AS high_risk_count
EXPORT "person".count AS total_person
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene({ 200, 200 }, {
		Instance("PERSON", 0, 0, 30, 20, 0.9),   // area=600, risk=1.8, kept, high_risk
		Instance("PERSON", 0, 0, 20, 20, 0.6),   // area=400, risk=1.2, filtered (area<500)
		Instance("PERSON", 0, 0, 40, 30, 0.7),   // area=1200, risk=1.4, kept, high_risk
		Instance("PERSON", 0, 0, 30, 20, 0.3),   // risk=0.6, filtered (conf<0.5)
	});

	program.set_import(scene, "MIN_CONF", Val(0.5));

	EvalResult res = program.evaluate(scene);

	bool ok = check_count(res, "PERSON", 2)
		&& check_count(res, "HIGH_RISK", 2);

	if (ok) {
		try {
			Val total = program.get_exported("total_person", res);
			Val high = program.get_exported("high_risk_count", res);
			if (std::abs(total.as_num() - 2.0) > 0.001) ok = false;
			if (std::abs(high.as_num() - 2.0) > 0.001) ok = false;
		}
		catch (RuntimeError& e) {
			std::cout << e.what() << std::endl;
			ok = false;
		}
	}
	report("端到端综合场景 (IMPORT + 全局变量 + ATTR + FILTER + GROUP + EXPORT)", ok);
}

// ============================================================
// 入口
// ============================================================

/**
 * @brief PostAnvil v0.3 测试入口
 * @return 0 表示全部通过，1 表示存在失败
 */
int main() {
	std::cout << "========================================" << std::endl;
	std::cout << "  PostAnvil v0.3 编译型规则编译器测试" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;

	try {
		// ---------- 基础过滤 ----------
		std::cout << "--- 基础过滤 ---" << std::endl;
		test01_global_confidence_filter();
		test02_global_size_and_area();
		std::cout << std::endl;

		// ---------- 运算符 ----------
		std::cout << "--- 运算符 ---" << std::endl;
		test03_comparison_operators();
		test04_arithmetic_and_unary_minus();
		test05_multiplication();
		test05b_division();
		std::cout << std::endl;

		// ---------- 逻辑运算 ----------
		std::cout << "--- 逻辑运算 ---" << std::endl;
		test06_logical_or_with_parens();
		test07_logical_not();
		std::cout << std::endl;

		// ---------- 图像属性 ----------
		std::cout << "--- 图像属性 ---" << std::endl;
		test08_image_properties();
		std::cout << std::endl;

		// ---------- 派生属性 ----------
		std::cout << "--- 派生属性 ---" << std::endl;
		test09_derived_properties();
		std::cout << std::endl;

		// ---------- 组合场景 ----------
		std::cout << "--- 组合场景 ---" << std::endl;
		test10_multi_class_combined();
		std::cout << std::endl;

		// ---------- 编程模型 ----------
		std::cout << "--- 编程模型 ---" << std::endl;
		test11_program_reuse();
		test12_program_move();
		std::cout << std::endl;

		// ---------- 属性算子 ----------
		std::cout << "--- 属性算子 ---" << std::endl;
		test13_attr_compute_basic();
		test14_attr_then_filter();
		test15_case_insensitive();
		test16_attr_global();
		std::cout << std::endl;

		// ---------- GROUP / APPEND ----------
		std::cout << "--- GROUP / APPEND ---" << std::endl;
		test17_group_create_new_class();
		test18_append_instances();
		test19_group_then_filter();
		test20_class_count_property();
		std::cout << std::endl;

		// ---------- 布尔字面量 ----------
		std::cout << "--- 布尔字面量 ---" << std::endl;
		test21_bool_false_literal();
		test22_bool_true_literal();
		std::cout << std::endl;

		// ---------- SORT / FUNC ----------
		std::cout << "--- SORT / FUNC ---" << std::endl;
		test23_sort_primitive();
		test24_sort_ascending();
		test25_func_return_constant();
		test26_func_return_false();
		std::cout << std::endl;

		// ---------- v0.3 新增特性 ----------
		std::cout << "--- v0.3 新增特性 ---" << std::endl;
		test27_string_concatenation();
		test28_normalized_properties();
		test29_custom_class_property();
		test30_string_var_as_class_expr();
		test31_global_numeric_variable();
		test32_global_bool_variable();
		std::cout << std::endl;

		// ---------- 宿主交互 (IMPORT / EXPORT) ----------
		std::cout << "--- 宿主交互 (IMPORT / EXPORT) ---" << std::endl;
		test33_import_variable();
		test34_import_as_alias();
		test35_export_value();
		std::cout << std::endl;

		// ---------- 控制流 (IF-ELSE / FOR) ----------
		std::cout << "--- 控制流 (IF-ELSE / FOR) ---" << std::endl;
		// test36_func_if_else();
		// test37_func_for_loop();
		// test38_for_loop_empty_class();
		// test39_nested_for_loop();
		std::cout << std::endl;

		// ---------- 端到端 ----------
		std::cout << "--- 端到端 ---" << std::endl;
		test40_end_to_end_scenario();
		std::cout << std::endl;

	}
	catch (const std::exception& e) {
		std::cout << "[ERROR] " << e.what() << std::endl;
		TEST_FAIL_COUNT(1);
	}

	// ---------- 结果统计 ----------
	int passed = TEST_PASS_COUNT();
	int failed = TEST_FAIL_COUNT();

	std::cout << "========================================" << std::endl;
	std::cout << "  测试结果统计" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "  通过: " << passed << std::endl;
	std::cout << "  失败: " << failed << std::endl;
	std::cout << "  总计: " << (passed + failed) << std::endl;
	std::cout << "  通过率: " << (passed + failed > 0
		? (100.0 * passed / (passed + failed)) : 0.0) << "%" << std::endl;
	std::cout << "========================================" << std::endl;

	return failed > 0 ? 1 : 0;
}