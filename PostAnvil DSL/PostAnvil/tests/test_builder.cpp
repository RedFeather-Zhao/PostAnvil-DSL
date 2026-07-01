/**
 * @file test_builder.cpp
 * @brief SceneRuleCompiler 编译型场景规则编译器独立测试。
 *
 * 测试覆盖范围：
 * - 基础编译：GLOBAL 规则 → CompiledProgram → 执行
 * - 多类别组合：GLOBAL + 各类别规则
 * - 空间谓词：CONTAINS / INSIDE / OVERLAP / CLOSE_TO
 * - 解码器复用：编译一次，对多个场景执行
 * - 数值运算：算术 + 比较 + 逻辑
 * - 内置函数：abs / iou
 * - 属性访问：self.* / image.* / 类名.*
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
static Instance make_sq(std::string_view cls, double x, double y, double size, double conf = 1.0) {
	Instance inst;
	inst.cls = cls;
	inst.x = x; inst.y = y;
	inst.width = size; inst.height = size;
	inst.conf = conf;
	return inst;
}

/**
 * @brief 辅助函数：创建指定尺寸的矩形实例。
 */
static Instance make_rect(std::string_view cls, double x, double y, double w, double h, double conf = 1.0) {
	Instance inst;
	inst.cls = cls;
	inst.x = x; inst.y = y;
	inst.width = w; inst.height = h;
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
RULE FOR GLOBAL:
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
 * 规则：self.width > 10 AND self.height > 10 AND self.area > 200
 * 预期：20x30(area=600) 和 15x15(area=225) 保留，5x5 和 10x15 被过滤。
 */
static void test02_global_size_and_area() {
	const char* src = R"(
RULE FOR GLOBAL:
	self.width > 10
	self.height > 10
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
	report("GLOBAL 多条件：尺寸+面积 (width>10, height>10, area>200)", ok);
}

/**
 * @brief 测试 3：比较运算符（>=, <=, !=）
 *
 * 规则：self.x >= 50 AND self.x <= 100 AND self.x != 75
 * 预期：x=50 和 x=100 保留，x=10/x=75/x=200 被过滤。
 */
static void test03_comparison_operators() {
	const char* src = R"(
RULE FOR C:
	self.x >= 50
	self.x <= 100
	self.x != 75
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
 * 规则：self.x + self.width > 100 AND -self.y > -100
 * 预期：1 个保留。
 */
static void test04_arithmetic_and_unary_minus() {
	const char* src = R"(
RULE FOR D:
	self.x + self.width > 100
	-self.y > -100
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["D"].push_back(make_rect("D", 10, 50, 20, 10));   // 30!>100 ✗
	scene["D"].push_back(make_rect("D", 50, 50, 200, 10));  // 250>100✓, -50>-100✓ → kept
	scene["D"].push_back(make_rect("D", 100, 150, 10, 10)); // 110>100✓, -150>-100✗

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "D", 1);
	report("算术加法 + 一元取负 (x+w>100, -y>-100)", ok);
}

/**
 * @brief 测试 5：乘法
 *
 * 规则：self.width * self.height > 300
 * 预期：20x30=600 > 300 ✓，其余被过滤 → 1 个保留。
 */
static void test05_multiplication() {
	const char* src = R"(
RULE FOR E:
	self.width * self.height > 300
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
	report("乘法 (width * height > 300)", ok);
}

/**
 * @brief 测试 6：逻辑 OR + 括号分组
 *
 * 规则：(self.width > 100 OR self.height > 100) AND self.conf > 0.5
 * 预期：2 个保留。
 */
static void test06_logical_or_with_parens() {
	const char* src = R"(
RULE FOR F:
	(self.width > 100 OR self.height > 100) AND self.conf > 0.5
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
RULE FOR G:
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
 * 规则：self.x + self.width <= image.width AND self.y + self.height <= image.height
 * 预期：仅 (10,10,20,20) 完全在图像内。
 */
static void test08_image_properties() {
	const char* src = R"(
RULE FOR H:
	self.x + self.width <= image.width
	self.y + self.height <= image.height
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
 * @brief 测试 9：CONTAINS 谓词 —— 单值计数
 *
 * 规则：CONTAINS J 1
 * 预期：I 包含 2 个 J，cnt=2 >= 1 → I 保留；J 无规则全部保留。
 */
static void test09_contains_single_count() {
	const char* src = R"(
RULE FOR I:
	CONTAINS J 1
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["I"].push_back(make_rect("I", 0, 0, 100, 100));
	scene["J"].push_back(make_sq("J", 10, 10, 5));
	scene["J"].push_back(make_sq("J", 20, 20, 5));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "I", 1) && check_count(res, "J", 2);
	report("CONTAINS 单值计数 (CONTAINS J 1)", ok);
	if (!ok) {
		int i_cnt = res.kept.contains("I") ? (int)res.kept.at("I").size() : 0;
		int j_cnt = res.kept.contains("J") ? (int)res.kept.at("J").size() : 0;
		std::cout << "    期望: I=1, J=2; 实际: I=" << i_cnt << ", J=" << j_cnt << std::endl;
	}
}

/**
 * @brief 测试 10：CONTAINS 谓词 —— 范围计数
 *
 * 规则：CONTAINS L 2-4
 * 预期：cnt=3 在 [2,4] 内 → K 保留。
 */
static void test10_contains_range_count() {
	const char* src = R"(
RULE FOR K:
	CONTAINS L 2-4
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["K"].push_back(make_rect("K", 0, 0, 100, 100));
	scene["L"].push_back(make_sq("L", 10, 10, 5));
	scene["L"].push_back(make_sq("L", 30, 30, 5));
	scene["L"].push_back(make_sq("L", 50, 50, 5));

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "K", 1);
	report("CONTAINS 范围计数 (CONTAINS L 2-4)", ok);
}

/**
 * @brief 测试 11：INSIDE 谓词
 *
 * 规则：INSIDE Container
 * 预期：Q1 在 Container 内保留，Q2 在外部被过滤。
 */
static void test11_inside_predicate() {
	const char* src = R"(
RULE FOR Q:
	INSIDE Container
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Container"].push_back(make_rect("Container", 0, 0, 200, 200));
	scene["Q"].push_back(make_rect("Q", 50, 50, 20, 20));     // inside → kept
	scene["Q"].push_back(make_rect("Q", 250, 250, 20, 20));   // not inside → filtered

	Image img{300, 300};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "Q", 1);
	report("INSIDE 谓词 (INSIDE Container)", ok);
}

/**
 * @brief 测试 12：OVERLAP 谓词
 *
 * 规则：OVERLAP S
 * 预期：R1 与 S 重叠保留，R2 不重叠被过滤。
 */
static void test12_overlap_predicate() {
	const char* src = R"(
RULE FOR R:
	OVERLAP S
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["S"].push_back(make_rect("S", 0, 0, 50, 50));
	scene["R"].push_back(make_rect("R", 30, 30, 50, 50));    // overlaps → kept
	scene["R"].push_back(make_rect("R", 100, 100, 50, 50));  // no overlap → filtered

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "R", 1);
	report("OVERLAP 谓词 (OVERLAP S)", ok);
}

/**
 * @brief 测试 13：CLOSE_TO 谓词
 *
 * 规则：CLOSE_TO U 50
 * 预期：T1 中心距离 ~14.14 ≤ 50 保留，T2 距离 ~212 > 50 被过滤。
 */
static void test13_close_to_predicate() {
	const char* src = R"(
RULE FOR T:
	CLOSE_TO U 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["U"].push_back(make_rect("U", 40, 40, 20, 20));
	scene["T"].push_back(make_rect("T", 50, 50, 20, 20));
	scene["T"].push_back(make_rect("T", 190, 190, 20, 20));

	Image img{300, 300};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "T", 1);
	report("CLOSE_TO 谓词 (CLOSE_TO U 50)", ok);
	if (!ok) {
		int t_cnt = res.kept.contains("T") ? (int)res.kept.at("T").size() : 0;
		std::cout << "    期望: T=1; 实际: T=" << t_cnt << std::endl;
	}
}

/**
 * @brief 测试 14：abs() 内置函数
 *
 * 规则：abs(self.center_x - 70) < 50
 * 预期：2 个保留。
 */
static void test14_abs_function() {
	const char* src = R"(
RULE FOR V:
	abs(self.center_x - 70) < 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["V"].push_back(make_rect("V", 20, 0, 20, 20));   // center_x=30
	scene["V"].push_back(make_rect("V", 60, 0, 20, 20));   // center_x=70
	scene["V"].push_back(make_rect("V", 110, 0, 20, 20));  // center_x=120

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "V", 2);
	report("abs() 函数 (abs(center_x - 70) < 50)", ok);
}

/**
 * @brief 测试 15：iou() 内置函数
 *
 * 规则：iou(self, X) > 0.1
 * 预期：W1(iou≈0.1428) 保留，W2(iou=0) 被过滤。
 */
static void test15_iou_function() {
	const char* src = R"(
RULE FOR W:
	iou(self, X) > 0.1
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["X"].push_back(make_rect("X", 0, 0, 100, 100));
	scene["W"].push_back(make_rect("W", 50, 50, 100, 100));
	scene["W"].push_back(make_rect("W", 200, 200, 100, 100));

	Image img{400, 400};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "W", 1);
	report("iou() 函数 (iou(self, X) > 0.1)", ok);
}

/**
 * @brief 测试 16：类属性访问（OtherClass.property）
 *
 * 规则：self.width > Y.width
 * 预期：Z1(60>50) 保留，Z2(30<50) 被过滤。
 */
static void test16_class_property_access() {
	const char* src = R"(
RULE FOR Z:
	self.width > 40
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Y"].push_back(make_rect("Y", 0, 0, 50, 50));
	scene["Z"].push_back(make_rect("Z", 0, 0, 60, 60));   // 60 > 40 ✓
	scene["Z"].push_back(make_rect("Z", 0, 0, 30, 30));   // 30 > 40 ✗

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "Z", 1);
	report("类属性访问已移除 (self.width > 40)", ok);
}

/**
 * @brief 测试 17：派生属性 center_x, center_y, right, bottom, aspect_ratio
 *
 * 规则：self.center_x > 50 AND self.center_y > 50 AND self.right < 200 AND self.aspect_ratio > 1.0
 * 预期：AA3 保留。
 */
static void test17_derived_properties() {
	const char* src = R"(
RULE FOR AA:
	self.center_x > 50
	self.center_y > 50
	self.right < 200
	self.aspect_ratio >= 1.0
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["AA"].push_back(make_rect("AA", 0, 0, 100, 100));    // center=(50,50) ✗
	scene["AA"].push_back(make_rect("AA", 41, 0, 20, 20));     // center=(51,10) ✗ (y)
	scene["AA"].push_back(make_rect("AA", 41, 41, 20, 20));    // center=(51,51) ✓

	Image img{200, 200};

	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);
	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "AA", 1);
	report("派生属性 center_x, center_y, right, aspect_ratio", ok);
}

/**
 * @brief 测试 18：多类别 + GLOBAL + 类别规则组合
 *
 * 规则：
 *   GLOBAL：self.conf > 0.5
 *   Person：self.width > 20
 *   Vehicle：self.width > 100
 * 预期：Person=1, Vehicle=1, Animal=1
 */
static void test18_multi_class_combined() {
	const char* src = R"(
RULE FOR GLOBAL:
	self.conf > 0.5

RULE FOR Person:
	self.width > 20

RULE FOR Vehicle:
	self.width > 100
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
 * @brief 测试 19：解码器复用 —— 编译一次，多个场景执行
 *
 * 规则：CONTAINS J 1
 * 场景1：I 包含 2 个 J → 保留
 * 场景2：I 不包含 J → 过滤
 * 场景3：I 包含 1 个 J → 保留
 * 预期：场景1 I=1, J=2；场景2 I=0, J=2；场景3 I=1, J=1
 */
static void test19_program_reuse() {
	const char* src = R"(
RULE FOR I:
	CONTAINS J 1
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	// 编译一次
	SceneRuleCompiler compiler;
	CompiledProgram program = compiler.compile(rules);

	Image img{200, 200};

	// 场景1：I 包含 2 个 J
	Scene scene1;
	scene1["I"].push_back(make_rect("I", 0, 0, 100, 100));
	scene1["J"].push_back(make_sq("J", 10, 10, 5));
	scene1["J"].push_back(make_sq("J", 20, 20, 5));
	EvalResult res1 = program.evaluate(scene1, img);
	bool ok1 = check_count(res1, "I", 1) && check_count(res1, "J", 2);

	// 场景2：I 不包含 J
	Scene scene2;
	scene2["I"].push_back(make_rect("I", 0, 0, 100, 100));
	scene2["J"].push_back(make_sq("J", 200, 200, 5));
	scene2["J"].push_back(make_sq("J", 250, 250, 5));
	EvalResult res2 = program.evaluate(scene2, img);
	bool ok2 = check_count(res2, "I", 0) && check_count(res2, "J", 2);

	// 场景3：I 包含 1 个 J
	Scene scene3;
	scene3["I"].push_back(make_rect("I", 0, 0, 100, 100));
	scene3["J"].push_back(make_sq("J", 50, 50, 5));
	EvalResult res3 = program.evaluate(scene3, img);
	bool ok3 = check_count(res3, "I", 1) && check_count(res3, "J", 1);

	bool ok = ok1 && ok2 && ok3;
	report("解码器复用 —— 编译一次，三个场景", ok);
	if (!ok) {
		std::cout << "    场景1: I=" << (res1.kept.contains("I") ? (int)res1.kept.at("I").size() : 0)
				  << ", J=" << (res1.kept.contains("J") ? (int)res1.kept.at("J").size() : 0) << std::endl;
		std::cout << "    场景2: I=" << (res2.kept.contains("I") ? (int)res2.kept.at("I").size() : 0)
				  << ", J=" << (res2.kept.contains("J") ? (int)res2.kept.at("J").size() : 0) << std::endl;
		std::cout << "    场景3: I=" << (res3.kept.contains("I") ? (int)res3.kept.at("I").size() : 0)
				  << ", J=" << (res3.kept.contains("J") ? (int)res3.kept.at("J").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 20：CompiledProgram 移动语义
 *
 * 验证 CompiledProgram 支持移动构造，移动后目标对象可正常使用。
 * 规则：GLOBAL self.conf > 0.5
 * 预期：移动后 program2 得到与 program1 相同的结果。
 */
static void test20_program_move() {
	const char* src = R"(
RULE FOR GLOBAL:
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

	// ---------- 空间谓词 ----------
	std::cout << "--- 空间谓词 ---" << std::endl;
	test09_contains_single_count();
	test10_contains_range_count();
	test11_inside_predicate();
	test12_overlap_predicate();
	test13_close_to_predicate();
	std::cout << std::endl;

	// ---------- 内置函数 ----------
	std::cout << "--- 内置函数 ---" << std::endl;
	test14_abs_function();
	test15_iou_function();
	std::cout << std::endl;

	// ---------- 属性访问 ----------
	std::cout << "--- 属性访问 ---" << std::endl;
	test16_class_property_access();
	test17_derived_properties();
	std::cout << std::endl;

	// ---------- 组合场景 ----------
	std::cout << "--- 组合场景 ---" << std::endl;
	test18_multi_class_combined();
	std::cout << std::endl;

	// ---------- 解码器特性 ----------
	std::cout << "--- 解码器特性 ---" << std::endl;
	test19_program_reuse();
	test20_program_move();
	std::cout << std::endl;

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