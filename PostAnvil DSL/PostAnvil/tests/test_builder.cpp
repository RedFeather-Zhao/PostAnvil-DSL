/**
 * @file test_builder.cpp
 * @brief SceneRuleCompiler 编译型场景规则编译器独立测试。
 *
 * 测试覆盖范围：
 * - 基础编译：GLOBAL 规则 → CompiledProgram → 执行
 * - 多类别组合：GLOBAL + 各类别规则
 * - 属性算子：RULE ATTR 计算属性
 * - 解码器复用：编译一次，对多个场景执行
 * - 数值运算：算术 + 比较 + 逻辑
 * - 属性访问：self.* / image.*（大小写不敏感）
 *
 * 每个测试用例独立构造场景与规则，验证后统计通过/失败。
 *
 * @author RedFeather-Zhao
 * @date   June 2026
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
 * @brief 辅助函数：创建简单的正方形实例。
 */
static Instance make_sq(std::string_view cls, double x1, double y1, double size, double conf = 1.0) {
	Instance inst;
	inst.cls = cls;
	inst.x1 = x1; inst.y1 = y1;
	inst.w = size; inst.h = size;
	inst.conf = conf;
	return inst;
}

/**
 * @brief 辅助函数：创建指定尺寸的矩形实例。
 */
static Instance make_rect(std::string_view cls, double x1, double y1, double w, double h, double conf = 1.0) {
	Instance inst;
	inst.cls = cls;
	inst.x1 = x1; inst.y1 = y1;
	inst.w = w; inst.h = h;
	inst.conf = conf;
	return inst;
}

/**
 * @brief 辅助函数：验证评估结果中指定类别的保留实例数。
 */
static bool check_count(const EvalResult& res, const std::string& cls, int expected_count) {
	auto it = res.kept.find(cls);
	int actual = (it != res.kept.end()) ? (int)it->second.size() : 0;
	return actual == expected_count;
}

/**
 * @brief 辅助函数：打印测试结果。
 */
static void report(const char* name, bool passed, const std::string& detail = "") {
	if (passed) {
		TEST_PASS_COUNT(1);
		std::cout << "  [PASS] " << name;
	} else {
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
 * @brief 测试 1：GLOBAL 置信度过滤（编译型）
 *
 * 规则：self.conf > 0.5
 * 预期：4 个实例中，conf=0.9 和 0.6 的保留，共 2 个。
 */
static void test01_global_confidence_filter() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.9));
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.6));
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.4));
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.2));

	Image img{200, 200};

	// 编译一次
	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);

	// 执行解码
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "A", 2);
	report("GLOBAL 置信度过滤 (self.conf > 0.5)", ok);
	if (!ok) {
		int a_cnt = res.kept.contains("A") ? (int)res.kept.at("A").size() : 0;
		std::cout << "    期望 A=2, 实际 A=" << a_cnt << std::endl;
	}
}

/**
 * @brief 测试 2：GLOBAL 多条件（尺寸 + 面积 + 宽高比）
 *
 * 规则：self.w > 10 AND self.h > 10 AND self.area > 200
 * 预期：20x30(area=600) 和 15x15(area=225) 保留，5x5 和 10x15 被过滤。
 */
static void test02_global_size_and_area() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.w > 10
	self.h > 10
	self.area > 200
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["B"].push_back(make_rect("B", 0, 0, 20, 30));  // area=600 ✓
	scene["B"].push_back(make_rect("B", 0, 0, 5, 5));     // w=5 ✗
	scene["B"].push_back(make_rect("B", 0, 0, 15, 15));   // area=225 ✓
	scene["B"].push_back(make_rect("B", 0, 0, 10, 15));   // w=10 ✗ (not >)

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "B", 2);
	report("GLOBAL 多条件：尺寸+面积 (w>10, h>10, area>200)", ok);
}

/**
 * @brief 测试 3：比较运算符（>=, <=, !=）
 *
 * 规则：self.x1 >= 50 AND self.x1 <= 100 AND self.x1 != 75
 * 预期：x1=50 和 x1=100 保留，x1=10/x1=75/x1=200 被过滤。
 */
static void test03_comparison_operators() {
	const char* src = R"(
RULE FILTER C:
	self.x1 >= 50
	self.x1 <= 100
	self.x1 != 75
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["C"].push_back(make_rect("C", 10, 0, 10, 10));
	scene["C"].push_back(make_rect("C", 50, 0, 10, 10));
	scene["C"].push_back(make_rect("C", 100, 0, 10, 10));
	scene["C"].push_back(make_rect("C", 200, 0, 10, 10));
	scene["C"].push_back(make_rect("C", 75, 0, 10, 10));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "C", 2);
	report("比较运算符 (>=, <=, !=)", ok);
}

/**
 * @brief 测试 4：算术运算 + 一元取负
 *
 * 规则：self.x1 + self.w > 100 AND -self.y1 > -100
 * 预期：1 个保留。
 */
static void test04_arithmetic_and_unary_minus() {
	const char* src = R"(
RULE FILTER D:
	self.x1 + self.w > 100
	-self.y1 > -100
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["D"].push_back(make_rect("D", 10, 50, 20, 10));   // 30!>100 ✗
	scene["D"].push_back(make_rect("D", 50, 50, 200, 10));  // 250>100 ✓, -50>-100 ✓ → kept
	scene["D"].push_back(make_rect("D", 100, 150, 10, 10)); // 110>100 ✓, -150>-100 ✗

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "D", 1);
	report("算术加法 + 一元取负 (x1+w>100, -y1>-100)", ok);
}

/**
 * @brief 测试 5：乘法
 *
 * 规则：self.w * self.h > 300
 * 预期：20x30=600 > 300 ✓，其余被过滤 → 1 个保留。
 */
static void test05_multiplication() {
	const char* src = R"(
RULE FILTER E:
	self.w * self.h > 300
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["E"].push_back(make_rect("E", 0, 0, 20, 30));  // 600 ✓
	scene["E"].push_back(make_rect("E", 0, 0, 10, 10));  // 100 ✗
	scene["E"].push_back(make_rect("E", 0, 0, 15, 15));  // 225 ✗
	scene["E"].push_back(make_rect("E", 0, 0, 5, 20));   // 100 ✗

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "E", 1);
	report("乘法 (w * h > 300)", ok);
}

/**
 * @brief 测试 5b：除法
 *
 * 规则：self.x1 / self.w < 2
 * 预期：x1=10,w=20→0.5<2 ✓, x1=100,w=20→5<2 ✗, x1=30,w=30→1<2 ✓ → 2 个保留。
 */
static void test05b_division() {
	const char* src = R"(
RULE FILTER E2:
	self.x1 / self.w < 2
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["E2"].push_back(make_rect("E2", 10, 0, 20, 10));   // 10/20=0.5 < 2 ✓
	scene["E2"].push_back(make_rect("E2", 100, 0, 20, 10));  // 100/20=5 < 2 ✗
	scene["E2"].push_back(make_rect("E2", 30, 0, 30, 10));   // 30/30=1 < 2 ✓

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "E2", 2);
	report("除法 (x1 / w < 2)", ok);
}

/**
 * @brief 测试 6：逻辑 OR + 括号分组
 *
 * 规则：(self.w > 100 OR self.h > 100) AND self.conf > 0.5
 * 预期：2 个保留。
 */
static void test06_logical_or_with_parens() {
	const char* src = R"(
RULE FILTER F:
	(self.w > 100 OR self.h > 100) AND self.conf > 0.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["F"].push_back(make_rect("F", 0, 0, 150, 10, 0.9));
	scene["F"].push_back(make_rect("F", 0, 0, 10, 150, 0.9));
	scene["F"].push_back(make_rect("F", 0, 0, 150, 150, 0.3));
	scene["F"].push_back(make_rect("F", 0, 0, 10, 10, 0.9));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "F", 2);
	report("逻辑 OR + 括号 ((w>100 OR h>100) AND conf>0.5)", ok);
}

/**
 * @brief 测试 7：逻辑 NOT
 *
 * 规则：NOT self.conf < 0.3
 * 预期：conf=0.2 被过滤，0.5 和 0.8 保留。
 */
static void test07_logical_not() {
	const char* src = R"(
RULE FILTER G:
	NOT self.conf < 0.3
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["G"].push_back(make_sq("G", 0, 0, 10, 0.2));
	scene["G"].push_back(make_sq("G", 0, 0, 10, 0.5));
	scene["G"].push_back(make_sq("G", 0, 0, 10, 0.8));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "G", 2);
	report("逻辑 NOT (NOT conf < 0.3)", ok);
}

/**
 * @brief 测试 8：图像属性 image.width / image.height
 *
 * 规则：self.x1 + self.w <= image.width AND self.y1 + self.h <= image.height
 * 预期：仅 (10,10,20,20) 完全在图像内。
 */
static void test08_image_properties() {
	const char* src = R"(
RULE FILTER H:
	self.x1 + self.w <= image.w
	self.y1 + self.h <= image.h
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["H"].push_back(make_rect("H", 10, 10, 20, 20));   // 30≤200, 30≤100 ✓
	scene["H"].push_back(make_rect("H", 180, 10, 30, 20));  // 210≤200 ✗
	scene["H"].push_back(make_rect("H", 10, 80, 20, 30));   // 30≤200, 110≤100 ✗

	Image img{200, 100};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "H", 1);
	report("图像属性 (image.width, image.height 边界检查)", ok);
}

/**
 * @brief 测试 9：派生属性 cx, cy, x2, aspect
 *
 * 规则：self.cx > 50 AND self.cy > 50 AND self.x2 < 200 AND self.aspect >= 1.0
 * 预期：AA3 保留。
 */
static void test09_derived_properties() {
	const char* src = R"(
RULE FILTER AA:
	self.cx > 50
	self.cy > 50
	self.x2 < 200
	self.aspect >= 1.0
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["AA"].push_back(make_rect("AA", 0, 0, 100, 100));    // cx=50, cy=50 ✗
	scene["AA"].push_back(make_rect("AA", 41, 0, 20, 20));     // cx=51, cy=10 ✗ (y)
	scene["AA"].push_back(make_rect("AA", 41, 41, 20, 20));    // cx=51, cy=51 ✓

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "AA", 1);
	report("派生属性 cx, cy, x2, aspect", ok);
}

/**
 * @brief 测试 10：多类别 + GLOBAL + 类别规则组合
 *
 * 规则：
 *   GLOBAL：self.conf > 0.5
 *   Person：self.w > 20
 *   Vehicle：self.w > 100
 * 预期：Person=1, Vehicle=1, Animal=1
 */
static void test10_multi_class_combined() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5

RULE FILTER Person:
	self.w > 20

RULE FILTER Vehicle:
	self.w > 100
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Person"].push_back(make_rect("Person", 0, 0, 30, 30, 0.9));
	scene["Person"].push_back(make_rect("Person", 0, 0, 15, 15, 0.9));
	scene["Person"].push_back(make_rect("Person", 0, 0, 30, 30, 0.3));
	scene["Vehicle"].push_back(make_rect("Vehicle", 0, 0, 150, 50, 0.9));
	scene["Vehicle"].push_back(make_rect("Vehicle", 0, 0, 80, 50, 0.9));
	scene["Animal"].push_back(make_rect("Animal", 0, 0, 10, 10, 0.9));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "Person", 1)
		   && check_count(res, "Vehicle", 1)
		   && check_count(res, "Animal", 1);
	report("多类别 + GLOBAL + 类别规则组合", ok);
	if (!ok) {
		std::cout << "    期望: Person=1, Vehicle=1, Animal=1" << std::endl;
		std::cout << "    实际: Person=" << (res.kept.contains("Person") ? (int)res.kept.at("Person").size() : 0)
				  << ", Vehicle=" << (res.kept.contains("Vehicle") ? (int)res.kept.at("Vehicle").size() : 0)
				  << ", Animal=" << (res.kept.contains("Animal") ? (int)res.kept.at("Animal").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 11：解码器复用 —— 编译一次，多个场景执行
 *
 * 规则：self.w > 40
 * 场景1：Z1 保留；场景2：Z2 保留；场景3：Z3 保留
 * 预期：场景1 Z=1；场景2 Z=1；场景3 Z=1
 */
static void test11_program_reuse() {
	const char* src = R"(
RULE FILTER Z:
	self.w > 40
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	// 编译一次
	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);

	Image img{200, 200};

	// 场景1
	Scene scene1;
	scene1["Z"].push_back(make_rect("Z", 0, 0, 60, 60));   // 60 > 40 ✓
	scene1["Z"].push_back(make_rect("Z", 0, 0, 30, 30));   // 30 > 40 ✗
	EvalResult res1 = program.evaluate(scene1, img);
	bool ok1 = check_count(res1, "Z", 1);

	// 场景2
	Scene scene2;
	scene2["Z"].push_back(make_rect("Z", 0, 0, 80, 80));   // 80 > 40 ✓
	scene2["Z"].push_back(make_rect("Z", 0, 0, 20, 20));   // 20 > 40 ✗
	EvalResult res2 = program.evaluate(scene2, img);
	bool ok2 = check_count(res2, "Z", 1);

	// 场景3
	Scene scene3;
	scene3["Z"].push_back(make_rect("Z", 0, 0, 50, 10));   // 50 > 40 ✓
	EvalResult res3 = program.evaluate(scene3, img);
	bool ok3 = check_count(res3, "Z", 1);

	bool ok = ok1 && ok2 && ok3;
	report("解码器复用 —— 编译一次，三个场景", ok);
	if (!ok) {
		std::cout << "    场景1: Z=" << (res1.kept.contains("Z") ? (int)res1.kept.at("Z").size() : 0) << std::endl;
		std::cout << "    场景2: Z=" << (res2.kept.contains("Z") ? (int)res2.kept.at("Z").size() : 0) << std::endl;
		std::cout << "    场景3: Z=" << (res3.kept.contains("Z") ? (int)res3.kept.at("Z").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 12：CompiledProgram 移动语义
 *
 * 验证 CompiledProgram 支持移动构造，移动后目标对象可正常使用。
 * 规则：GLOBAL self.conf > 0.5
 * 预期：移动后 program2 得到与 program1 相同的结果。
 */
static void test12_program_move() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.9));
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.6));
	scene["A"].push_back(make_sq("A", 0, 0, 10, 0.3));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program1 = compiler.compile(rules);

	// 移动 program
	CompiledProgram program2 = std::move(program1);

	EvalResult res = program2.evaluate(scene, img);

	bool ok = check_count(res, "A", 2);
	report("CompiledProgram 移动语义", ok);
}

/**
 * @brief 测试 13：属性算子 —— 基本属性计算
 *
 * 规则：RULE ATTR Person: risk = self.conf * 2.0, size = self.w * self.h
 * 预期：每个实例的 props 中包含计算后的 RISK 和 SIZE 值。
 */
static void test13_attr_compute_basic() {
	const char* src = R"(
RULE ATTR Person:
	risk = self.conf * 2.0
	size = self.w * self.h
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Person"].push_back(make_rect("Person", 0, 0, 20, 30, 0.9));
	scene["Person"].push_back(make_rect("Person", 0, 0, 10, 50, 0.5));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	// 验证属性值
	bool ok = true;
	auto it = res.kept.find("Person");
	if (it == res.kept.end() || it->second.size() != 2) {
		ok = false;
	} else {
		double risk0 = it->second[0].props.at(std::string{"RISK"});
		double size0 = it->second[0].props.at(std::string{"SIZE"});
		double risk1 = it->second[1].props.at(std::string{"RISK"});
		double size1 = it->second[1].props.at(std::string{"SIZE"});

		// Person[0]: conf=0.9, w=20, h=30 → risk=1.8, size=600
		// Person[1]: conf=0.5, w=10, h=50 → risk=1.0, size=500
		if (std::abs(risk0 - 1.8) > 0.001 || std::abs(size0 - 600.0) > 0.001) ok = false;
		if (std::abs(risk1 - 1.0) > 0.001 || std::abs(size1 - 500.0) > 0.001) ok = false;
	}

	report("属性算子 — 基本属性计算 (risk, size)", ok);
	if (!ok) {
		std::cout << "    期望: risk0=1.8, size0=600, risk1=1.0, size1=500" << std::endl;
		if (it != res.kept.end() && !it->second.empty()) {
			auto& p0 = it->second[0];
			auto& p1 = it->second[1];
			std::cout << "    实际: risk0=" << (p0.props.contains("RISK") ? p0.props.at("RISK") : -1)
					  << ", size0=" << (p0.props.contains("SIZE") ? p0.props.at("SIZE") : -1)
					  << ", risk1=" << (p1.props.contains("RISK") ? p1.props.at("RISK") : -1)
					  << ", size1=" << (p1.props.contains("SIZE") ? p1.props.at("SIZE") : -1) << std::endl;
		}
	}
}

/**
 * @brief 测试 14：属性算子 + 过滤算子组合（含除法）
 *
 * 规则：先 RULE ATTR 计算 density，再 RULE FILTER 用 density 过滤
 * 预期：只有 density < 0.5 的实例保留。
 */
static void test14_attr_then_filter() {
	const char* src = R"(
RULE ATTR Person:
	density = self.conf / (self.w * self.h)

RULE FILTER Person:
	self.density < 0.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	// Person[0]: conf=0.9, w=20, h=30 → density=0.9/600=0.0015 < 0.5 ✓
	// Person[1]: conf=0.5, w=10, h=10 → density=0.5/100=0.005  < 0.5 ✓
	// Person[2]: conf=0.9, w=1, h=1   → density=0.9/1=0.9     > 0.5 ✗
	scene["Person"].push_back(make_rect("Person", 0, 0, 20, 30, 0.9));
	scene["Person"].push_back(make_rect("Person", 0, 0, 10, 10, 0.5));
	scene["Person"].push_back(make_rect("Person", 0, 0, 1, 1, 0.9));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "Person", 2);
	report("属性算子 + 过滤算子组合 (density = conf / (w * h))", ok);
	if (!ok) {
		int cnt = res.kept.contains("Person") ? (int)res.kept.at("Person").size() : 0;
		std::cout << "    期望: Person=2, 实际: Person=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 15：大小写不敏感验证
 *
 * 验证同一规则以不同大小写书写均能正确工作。
 * 规则使用大写 SELF/W/CONF/AND 等关键字和属性名。
 */
static void test15_case_insensitive() {
	const char* src = R"(
RULE FILTER GLOBAL:
	SELF.CONF > 0.5
	SELF.W > 10
)";

	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["X"].push_back(make_rect("X", 0, 0, 20, 20, 0.9));   // ✓
	scene["X"].push_back(make_rect("X", 0, 0, 5, 5, 0.9));     // w=5 ✗
	scene["X"].push_back(make_rect("X", 0, 0, 20, 20, 0.3));   // conf=0.3 ✗

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "X", 1);
	report("大小写不敏感 (大写 SELF.CONF > 0.5)", ok);
}

/**
 * @brief 测试 16：GLOBAL 属性算子
 *
 * 规则：RULE ATTR GLOBAL: area_calc = self.w * self.h
 * 预期：所有类别所有实例的 props 中均包含 AREA_CALC。
 */
static void test16_attr_global() {
	const char* src = R"(
RULE ATTR GLOBAL:
	area_calc = self.w * self.h
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Cat"].push_back(make_rect("Cat", 0, 0, 10, 20));
	scene["Dog"].push_back(make_rect("Dog", 0, 0, 30, 40));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = true;
	auto it_cat = res.kept.find("Cat");
	auto it_dog = res.kept.find("Dog");
	if (it_cat == res.kept.end() || it_cat->second.empty()) ok = false;
	else if (std::abs(it_cat->second[0].props.at("AREA_CALC") - 200.0) > 0.001) ok = false;

	if (it_dog == res.kept.end() || it_dog->second.empty()) ok = false;
	else if (std::abs(it_dog->second[0].props.at("AREA_CALC") - 1200.0) > 0.001) ok = false;

	report("GLOBAL 属性算子 (area_calc = w * h)", ok);
}

// ============================================================
// 入口
// ============================================================

/**
 * @brief 编译型评估器测试入口。
 * 依次执行所有测试用例，统计并输出通过/失败结果。
 * @return 0 表示全部通过，1 表示存在失败。
 */
int main() {
	std::cout << "========================================" << std::endl;
	std::cout << "  PostAnvil SceneRuleCompiler 编译型规则编译器测试" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;
	
	try
	{
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

		// ---------- 解码器特性 ----------
		std::cout << "--- 解码器特性 ---" << std::endl;
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
	}
	catch (const std::exception& e) {
		std::cout << "[ERROR] 解析错误: " << e.what() << std::endl;
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