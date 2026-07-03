/**
 * @file test_builder.cpp
 * @brief PostAnvil ANTLR4 迁移测试 —— 基于 PostAnvilCompiler 的编译型规则编译器测试。
 *
 * 测试覆盖范围：
 * - 基础编译：GLOBAL 规则 → CompiledProgram → 执行
 * - 多类别组合：GLOBAL + 各类别规则
 * - 属性算子：RULE ATTR 计算属性
 * - 解码器复用：编译一次，对多个场景执行
 * - 数值运算：算术 + 比较 + 逻辑
 * - 属性访问：self.* / image.*（大小写不敏感）
 *
 * 迁移变更：
 * - 所有规则使用 RULEEND 关键字结束
 * - 使用 PostAnvilCompiler::compile() 替代旧的 Parser::parse() + SceneRuleCompiler::compile()
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
 * @brief 测试 1：GLOBAL 置信度过滤
 *
 * 规则：self.conf > 0.5
 * 预期：4 个实例中，conf=0.9 和 0.6 的保留，共 2 个。
 */
static void test01_global_confidence_filter() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.9));
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.6));
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.4));
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.2));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "A", 2);
	report("GLOBAL 置信度过滤 (self.conf > 0.5)", ok);
	if (!ok) {
		int a_cnt = res.kept.contains("A") ? (int)res.kept.at("A").size() : 0;
		std::cout << "    期望 A=2, 实际 A=" << a_cnt << std::endl;
	}
}

/**
 * @brief 测试 2：GLOBAL 多条件（尺寸 + 面积）
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
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["B"].push_back(Instance::Create("B", 0, 0, 20, 30));  // area=600
	scene["B"].push_back(Instance::Create("B", 0, 0, 5, 5));     // w=5
	scene["B"].push_back(Instance::Create("B", 0, 0, 15, 15));   // area=225
	scene["B"].push_back(Instance::Create("B", 0, 0, 10, 15));   // w=10 (not >)

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "B", 2);
	report("GLOBAL 多条件：尺寸+面积 (w>10, h>10, area>200)", ok);
}

/**
 * @brief 测试 3：比较运算符（>=, <=, !=）
 *
 * 规则：self.x1 >= 50 AND self.x1 <= 100 AND self.x1 != 75
 * 预期：x1=50 和 x1=100 保留。
 */
static void test03_comparison_operators() {
	const char* src = R"(
RULE FILTER C:
	self.x1 >= 50
	self.x1 <= 100
	self.x1 != 75
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["C"].push_back(Instance::Create("C", 10, 0, 10, 10));
	scene["C"].push_back(Instance::Create("C", 50, 0, 10, 10));
	scene["C"].push_back(Instance::Create("C", 100, 0, 10, 10));
	scene["C"].push_back(Instance::Create("C", 200, 0, 10, 10));
	scene["C"].push_back(Instance::Create("C", 75, 0, 10, 10));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "C", 2);
	report("比较运算符 (>=, <=, !=)", ok);
}

/**
 * @brief 测试 4：算术运算 + 一元取负
 */
static void test04_arithmetic_and_unary_minus() {
	const char* src = R"(
RULE FILTER D:
	self.x1 + self.w > 100
	-self.y1 > -100
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["D"].push_back(Instance::Create("D", 10, 50, 20, 10));
	scene["D"].push_back(Instance::Create("D", 50, 50, 200, 10));
	scene["D"].push_back(Instance::Create("D", 100, 150, 10, 10));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "D", 1);
	report("算术加法 + 一元取负 (x1+w>100, -y1>-100)", ok);
}

/**
 * @brief 测试 5：乘法
 */
static void test05_multiplication() {
	const char* src = R"(
RULE FILTER E:
	self.w * self.h > 300
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["E"].push_back(Instance::Create("E", 0, 0, 20, 30));  // 600
	scene["E"].push_back(Instance::Create("E", 0, 0, 10, 10));  // 100
	scene["E"].push_back(Instance::Create("E", 0, 0, 15, 15));  // 225
	scene["E"].push_back(Instance::Create("E", 0, 0, 5, 20));   // 100

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "E", 1);
	report("乘法 (w * h > 300)", ok);
}

/**
 * @brief 测试 5b：除法
 */
static void test05b_division() {
	const char* src = R"(
RULE FILTER E2:
	self.x1 / self.w < 2
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["E2"].push_back(Instance::Create("E2", 10, 0, 20, 10));
	scene["E2"].push_back(Instance::Create("E2", 100, 0, 20, 10));
	scene["E2"].push_back(Instance::Create("E2", 30, 0, 30, 10));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "E2", 2);
	report("除法 (x1 / w < 2)", ok);
}

/**
 * @brief 测试 6：逻辑 OR + 括号分组
 */
static void test06_logical_or_with_parens() {
	const char* src = R"(
RULE FILTER F:
	(self.w > 100 OR self.h > 100) AND self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["F"].push_back(Instance::Create("F", 0, 0, 150, 10, 0.9));
	scene["F"].push_back(Instance::Create("F", 0, 0, 10, 150, 0.9));
	scene["F"].push_back(Instance::Create("F", 0, 0, 150, 150, 0.3));
	scene["F"].push_back(Instance::Create("F", 0, 0, 10, 10, 0.9));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "F", 2);
	report("逻辑 OR + 括号 ((w>100 OR h>100) AND conf>0.5)", ok);
}

/**
 * @brief 测试 7：逻辑 NOT
 */
static void test07_logical_not() {
	const char* src = R"(
RULE FILTER G:
	NOT self.conf < 0.3
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["G"].push_back(Instance::Create("G", 0, 0, 10, 10, 0.2));
	scene["G"].push_back(Instance::Create("G", 0, 0, 10, 10, 0.5));
	scene["G"].push_back(Instance::Create("G", 0, 0, 10, 10, 0.8));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "G", 2);
	report("逻辑 NOT (NOT conf < 0.3)", ok);
}

/**
 * @brief 测试 8：图像属性
 */
static void test08_image_properties() {
	const char* src = R"(
RULE FILTER H:
	self.x1 + self.w <= image.w
	self.y1 + self.h <= image.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["H"].push_back(Instance::Create("H", 10, 10, 20, 20));
	scene["H"].push_back(Instance::Create("H", 180, 10, 30, 20));
	scene["H"].push_back(Instance::Create("H", 10, 80, 20, 30));

	Image img{200, 100};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "H", 1);
	report("图像属性 (image.width, image.height 边界检查)", ok);
}

/**
 * @brief 测试 9：派生属性 cx, cy, x2, aspect
 */
static void test09_derived_properties() {
	const char* src = R"(
RULE FILTER AA:
	self.cx > 50
	self.cy > 50
	self.x2 < 200
	self.aspect >= 1.0
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["AA"].push_back(Instance::Create("AA", 0, 0, 100, 100));
	scene["AA"].push_back(Instance::Create("AA", 41, 0, 20, 20));
	scene["AA"].push_back(Instance::Create("AA", 41, 41, 20, 20));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "AA", 1);
	report("派生属性 cx, cy, x2, aspect", ok);
}

/**
 * @brief 测试 10：多类别 + GLOBAL + 类别规则组合
 */
static void test10_multi_class_combined() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5
RULEEND

RULE FILTER PERSON:
	self.w > 20
RULEEND

RULE FILTER VEHICLE:
	self.w > 100
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 30, 30, 0.9));
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 15, 15, 0.9));
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 30, 30, 0.3));
	scene["VEHICLE"].push_back(Instance::Create("VEHICLE", 0, 0, 150, 50, 0.9));
	scene["VEHICLE"].push_back(Instance::Create("VEHICLE", 0, 0, 80, 50, 0.9));
	scene["ANIMAL"].push_back(Instance::Create("ANIMAL", 0, 0, 10, 10, 0.9));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "PERSON", 1)
		   && check_count(res, "VEHICLE", 1)
		   && check_count(res, "ANIMAL", 1);
	report("多类别 + GLOBAL + 类别规则组合", ok);
	if (!ok) {
		std::cout << "    期望: PERSON=1, VEHICLE=1, ANIMAL=1" << std::endl;
		std::cout << "    实际: PERSON=" << (res.kept.contains("PERSON") ? (int)res.kept.at("PERSON").size() : 0)
				  << ", VEHICLE=" << (res.kept.contains("VEHICLE") ? (int)res.kept.at("VEHICLE").size() : 0)
				  << ", ANIMAL=" << (res.kept.contains("ANIMAL") ? (int)res.kept.at("ANIMAL").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 11：解码器复用
 */
static void test11_program_reuse() {
	const char* src = R"(
RULE FILTER Z:
	self.w > 40
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Image img{200, 200};

	Scene scene1;
	scene1["Z"].push_back(Instance::Create("Z", 0, 0, 60, 60));
	scene1["Z"].push_back(Instance::Create("Z", 0, 0, 30, 30));
	EvalResult res1 = program.evaluate(scene1, img);
	bool ok1 = check_count(res1, "Z", 1);

	Scene scene2;
	scene2["Z"].push_back(Instance::Create("Z", 0, 0, 80, 80));
	scene2["Z"].push_back(Instance::Create("Z", 0, 0, 20, 20));
	EvalResult res2 = program.evaluate(scene2, img);
	bool ok2 = check_count(res2, "Z", 1);

	Scene scene3;
	scene3["Z"].push_back(Instance::Create("Z", 0, 0, 50, 10));
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
 */
static void test12_program_move() {
	const char* src = R"(
RULE FILTER GLOBAL:
	self.conf > 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program1 = compiler.compile(src);

	Scene scene;
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.9));
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.6));
	scene["A"].push_back(Instance::Create("A", 0, 0, 10, 10, 0.3));

	Image img{200, 200};

	CompiledProgram program2 = std::move(program1);

	EvalResult res = program2.evaluate(scene, img);

	bool ok = check_count(res, "A", 2);
	report("CompiledProgram 移动语义", ok);
}

/**
 * @brief 测试 13：属性算子 —— 基本属性计算
 */
static void test13_attr_compute_basic() {
	const char* src = R"(
RULE ATTR PERSON:
	risk = self.conf * 2.0
	size = self.w * self.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 20, 30, 0.9));
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 10, 50, 0.5));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = true;
	auto it = res.kept.find("PERSON");
	if (it == res.kept.end() || it->second.size() != 2) {
		ok = false;
	} else {
		double risk0 = it->second[0].props.at("RISK");
		double size0 = it->second[0].props.at("SIZE");
		double risk1 = it->second[1].props.at("RISK");
		double size1 = it->second[1].props.at("SIZE");

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
 */
static void test14_attr_then_filter() {
	const char* src = R"(
RULE ATTR PERSON:
	density = self.conf / (self.w * self.h)
RULEEND

RULE FILTER PERSON:
	self.density < 0.5
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 20, 30, 0.9));
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 10, 10, 0.5));
	scene["PERSON"].push_back(Instance::Create("PERSON", 0, 0, 1, 1, 0.9));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "PERSON", 2);
	report("属性算子 + 过滤算子组合 (density = conf / (w * h))", ok);
	if (!ok) {
		int cnt = res.kept.contains("PERSON") ? (int)res.kept.at("PERSON").size() : 0;
		std::cout << "    期望: PERSON=2, 实际: PERSON=" << cnt << std::endl;
	}
}

/**
 * @brief 测试 15：大小写不敏感验证
 */
static void test15_case_insensitive() {
	const char* src = R"(
RULE FILTER GLOBAL:
	SELF.CONF > 0.5
	SELF.W > 10
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["X"].push_back(Instance::Create("X", 0, 0, 20, 20, 0.9));
	scene["X"].push_back(Instance::Create("X", 0, 0, 5, 5, 0.9));
	scene["X"].push_back(Instance::Create("X", 0, 0, 20, 20, 0.3));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = check_count(res, "X", 1);
	report("大小写不敏感 (大写 SELF.CONF > 0.5)", ok);
}

/**
 * @brief 测试 16：GLOBAL 属性算子
 */
static void test16_attr_global() {
	const char* src = R"(
RULE ATTR GLOBAL:
	area_calc = self.w * self.h
RULEEND
)";
	PostAnvilCompiler compiler;
	CompiledProgram program = compiler.compile(src);

	Scene scene;
	scene["CAT"].push_back(Instance::Create("CAT", 0, 0, 10, 20));
	scene["DOG"].push_back(Instance::Create("DOG", 0, 0, 30, 40));

	Image img{200, 200};

	EvalResult res = program.evaluate(scene, img);

	bool ok = true;
	auto it_cat = res.kept.find("CAT");
	auto it_dog = res.kept.find("DOG");
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
 * @brief PostAnvil ANTLR4 迁移测试入口。
 * @return 0 表示全部通过，1 表示存在失败。
 */
int main() {
	std::cout << "========================================" << std::endl;
	std::cout << "  PostAnvil ANTLR4 迁移 —— 编译型规则编译器测试" << std::endl;
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
	} catch (const std::exception& e) {
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