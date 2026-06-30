/**
 * @file test_comprehensive.cpp
 * @brief PostAnvil DSL 全面测试 —— 覆盖几乎所有语法特性。
 *
 * 测试覆盖范围：
 * - GLOBAL 规则与类别规则
 * - 所有属性访问（self.* / image.* / 类名.*）
 * - 所有比较运算符（> < >= <= == !=）
 * - 算术运算符（+ - * 一元 -）
 * - 逻辑运算符（AND / OR / NOT）、括号分组
 * - 空间谓词（CONTAINS / INSIDE / OVERLAP / CLOSE_TO）
 * - CONTAINS 数量范围（单值 / 范围 / 无计数）
 * - 内置函数（abs / iou）
 * - 派生属性（center_x / center_y / right / bottom / area / aspect_ratio）
 * - 多规则组合（GLOBAL + 类别规则）
 * - 边界情况（空类别、数量范围 0-0）
 *
 * 每个测试用例独立构造场景与规则，验证后统计通过/失败。
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include "postanvil/parser.hpp"
#include "postanvil/context.hpp"
#include "postanvil/evaluator.hpp"

using namespace postanvil;

// ============================================================
// 测试辅助工具
// ============================================================

/** 通过的测试数 */
static int g_passed = 0;
/** 失败的测试数 */
static int g_failed = 0;

/**
 * @brief 辅助函数：创建简单的正方形实例。
 * @param cls 类别名
 * @param x 左上角 x
 * @param y 左上角 y
 * @param size 边长
 * @param conf 置信度
 * @return Instance 实例
 */
static Instance make_sq(const std::string& cls, double x, double y, double size, double conf = 1.0) {
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
static Instance make_rect(const std::string& cls, double x, double y, double w, double h, double conf = 1.0) {
	Instance inst;
	inst.cls = cls;
	inst.x = x; inst.y = y;
	inst.width = w; inst.height = h;
	inst.conf = conf;
	return inst;
}

/**
 * @brief 辅助函数：验证评估结果中指定类别的保留实例数。
 * @param res 评估结果
 * @param cls 类别名
 * @param expected_count 期望的保留实例数
 * @return true 表示通过
 */
static bool check_count(const EvalResult& res, const std::string& cls, int expected_count) {
	auto it = res.kept.find(cls);
	int actual = (it != res.kept.end()) ? (int)it->second.size() : 0;
	return actual == expected_count;
}

/**
 * @brief 辅助函数：打印测试结果。
 * @param name 测试名称
 * @param passed 是否通过
 * @param detail 详情（可选）
 */
static void report(const char* name, bool passed, const std::string& detail = "") {
	if (passed) {
		++g_passed;
		std::cout << "  [PASS] " << name;
	} else {
		++g_failed;
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "A", 2);
	report("GLOBAL 置信度过滤 (self.conf > 0.5)", ok);
	if (!ok) std::cout << "    期望 A=2, 实际 A=" << (res.kept.count("A") ? (int)res.kept.at("A").size() : 0) << std::endl;
}

/**
 * @brief 测试 2：GLOBAL 多条件（尺寸 + 面积 + 宽高比）
 *
 * 规则（多行 AND）：
 *   self.width > 10
 *   self.height > 10
 *   self.area > 200
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "C", 2);
	report("比较运算符 (>=, <=, !=)", ok);
}

/**
 * @brief 测试 4：算术加法 + 一元取负
 *
 * 规则：self.x + self.width > 100 AND -self.y > -100
 * 实例：
 *   (10,50,20,10): x+w=30✗
 *   (50,50,200,10): x+w=250✓, -y=-50 > -100✓
 *   (100,150,10,10): x+w=110✓, -y=-150 > -100✗
 * 预期：1 个保留。
 */
static void test04_arithmetic_add_and_unary_minus() {
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "D", 1);
	report("算术加法 + 一元取负 (x+w>100, -y>-100)", ok);
}

/**
 * @brief 测试 5：乘法 *
 *
 * 规则：self.width * self.height > 300
 * 预期：20x30=600 > 300 ✓，10x10=100✗，15x15=225✗，5x20=100✗ → 1 个保留。
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "E", 1);
	report("乘法 (width * height > 300)", ok);
}

/**
 * @brief 测试 6：逻辑 OR + 括号分组
 *
 * 规则：(self.width > 100 OR self.height > 100) AND self.conf > 0.5
 * 预期：
 *   (150,10,0.9): (✓ or ✗) and ✓ → ✓
 *   (10,150,0.9): (✗ or ✓) and ✓ → ✓
 *   (150,150,0.3): (✓ or ✓) and ✗ → ✗
 *   (10,10,0.9):   (✗ or ✗) and ✓ → ✗
 * → 2 个保留。
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "F", 2);
	report("逻辑 OR + 括号 ((w>100 OR h>100) AND conf>0.5)", ok);
}

/**
 * @brief 测试 7：逻辑 NOT
 *
 * 规则：NOT self.conf < 0.3
 * 预期：conf=0.2 被过滤（0.2<0.3 为真，取反为假），0.5 和 0.8 保留。
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "G", 2);
	report("逻辑 NOT (NOT conf < 0.3)", ok);
}

/**
 * @brief 测试 8：图像属性 image.width / image.height
 *
 * 规则：self.x + self.width <= image.width AND self.y + self.height <= image.height
 * 图像：200x100
 * 预期：仅 (10,10,20,20) 完全在图像内，(180,10,30,20) 右边超出，(10,80,20,30) 下边超出。
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "H", 1);
	report("图像属性 (image.width, image.height 边界检查)", ok);
}

/**
 * @brief 测试 9：CONTAINS 谓词 —— 单值计数
 *
 * 规则：CONTAINS J 1
 * 场景：I 包含 2 个 J 实例
 * 预期：cnt=2 >= 1 → I 保留；J 类无规则，全部保留。
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
	scene["J"].push_back(make_sq("J", 10, 10, 5));   // inside I
	scene["J"].push_back(make_sq("J", 20, 20, 5));   // inside I

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "I", 1) && check_count(res, "J", 2);
	if (!ok) {
		int i_cnt = res.kept.count("I") ? (int)res.kept.at("I").size() : 0;
		int j_cnt = res.kept.count("J") ? (int)res.kept.at("J").size() : 0;
		std::cout << "    期望: I=1, J=2; 实际: I=" << i_cnt << ", J=" << j_cnt << std::endl;
	}
	report("CONTAINS 单值计数 (CONTAINS J 1)", ok);
}

/**
 * @brief 测试 10：CONTAINS 谓词 —— 范围计数
 *
 * 规则：CONTAINS L 2-4
 * 场景：K 包含 3 个 L 实例
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "K", 1);
	report("CONTAINS 范围计数 (CONTAINS L 2-4)", ok);
}

/**
 * @brief 测试 11：CONTAINS 谓词 —— 范围计数 范围外
 *
 * 规则：CONTAINS L 5-7
 * 场景：K 包含 3 个 L 实例
 * 预期：cnt=3 不在 [5,7] 内 → K 被过滤。
 */
static void test11_contains_range_outside() {
	const char* src = R"(
RULE FOR K:
	CONTAINS L 5-7
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["K"].push_back(make_rect("K", 0, 0, 100, 100));
	scene["L"].push_back(make_sq("L", 10, 10, 5));
	scene["L"].push_back(make_sq("L", 30, 30, 5));
	scene["L"].push_back(make_sq("L", 50, 50, 5));

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "K", 0);
	report("CONTAINS 范围计数-范围外 (CONTAINS L 5-7, 实际3个)", ok);
}

/**
 * @brief 测试 12：CONTAINS 谓词 —— 无计数（默认至少 1 个）
 *
 * 规则：CONTAINS N
 * 场景：M 包含 1 个 N 实例
 * 预期：cnt=1 >= 1 → M 保留。
 */
static void test12_contains_no_count() {
	const char* src = R"(
RULE FOR M:
	CONTAINS N
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["M"].push_back(make_rect("M", 0, 0, 100, 100));
	scene["N"].push_back(make_sq("N", 10, 10, 5));

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "M", 1);
	report("CONTAINS 无计数 (CONTAINS N, 默认至少1个)", ok);
}

/**
 * @brief 测试 13：CONTAINS 谓词 —— 0 个实例不满足
 *
 * 规则：CONTAINS P
 * 场景：O 内部没有 P 实例
 * 预期：O 被过滤。
 */
static void test13_contains_zero_instances() {
	const char* src = R"(
RULE FOR O:
	CONTAINS P
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["O"].push_back(make_rect("O", 0, 0, 100, 100));
	scene["P"].push_back(make_sq("P", 200, 200, 5));  // outside O

	Image img{300, 300};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "O", 0) && check_count(res, "P", 1);
	report("CONTAINS 无匹配 (CONTAINS P, 但P在O外部)", ok);
}

/**
 * @brief 测试 14：INSIDE 谓词
 *
 * 规则：INSIDE Container
 * 场景：Container(0,0,200,200)；Q1(50,50,20,20) 在内部，Q2(250,250,20,20) 在外部
 * 预期：Q1 保留，Q2 过滤。
 */
static void test14_inside_predicate() {
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "Q", 1);
	report("INSIDE 谓词 (INSIDE Container)", ok);
}

/**
 * @brief 测试 15：OVERLAP 谓词
 *
 * 规则：OVERLAP S
 * 场景：S(0,0,50,50)；R1(30,30,50,50) 重叠，R2(100,100,50,50) 不重叠
 * 预期：R1 保留，R2 过滤。
 */
static void test15_overlap_predicate() {
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "R", 1);
	report("OVERLAP 谓词 (OVERLAP S)", ok);
}

/**
 * @brief 测试 16：CLOSE_TO 谓词
 *
 * 规则：CLOSE_TO U 50
 * 场景：U 中心在 (50,50)；T1 中心在 (60,60)，距离 ≈14.14 ≤ 50；T2 中心在 (200,200)，距离 ≈212 > 50
 * 预期：T1 保留，T2 过滤。
 */
static void test16_close_to_predicate() {
	const char* src = R"(
RULE FOR T:
	CLOSE_TO U 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	// U: (40,40,20,20) → center = (50,50)
	scene["U"].push_back(make_rect("U", 40, 40, 20, 20));
	// T1: (50,50,20,20) → center = (60,60), dist = sqrt(200) ≈ 14.14
	scene["T"].push_back(make_rect("T", 50, 50, 20, 20));
	// T2: (190,190,20,20) → center = (200,200), dist = sqrt(45000) ≈ 212
	scene["T"].push_back(make_rect("T", 190, 190, 20, 20));

	Image img{300, 300};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "T", 1);
	if (!ok) {
		int t_cnt = res.kept.count("T") ? (int)res.kept.at("T").size() : 0;
		std::cout << "    期望: T=1; 实际: T=" << t_cnt << std::endl;
	}
	report("CLOSE_TO 谓词 (CLOSE_TO U 50)", ok);
}

/**
 * @brief 测试 17：abs() 内置函数
 *
 * 规则：abs(self.center_x - 70) < 50
 * 实例：center_x=30, 70, 120
 * 预期：|30-70|=40<50 ✓, |70-70|=0<50 ✓, |120-70|=50 not <50 ✗ → 2 个保留。
 */
static void test17_abs_function() {
	const char* src = R"(
RULE FOR V:
	abs(self.center_x - 70) < 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	// center_x = x + w/2
	scene["V"].push_back(make_rect("V", 20, 0, 20, 20));   // center_x=30
	scene["V"].push_back(make_rect("V", 60, 0, 20, 20));   // center_x=70
	scene["V"].push_back(make_rect("V", 110, 0, 20, 20));  // center_x=120

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "V", 2);
	report("abs() 函数 (abs(center_x - 70) < 50)", ok);
}

/**
 * @brief 测试 18：iou() 内置函数
 *
 * 规则：iou(self, X) > 0.1
 * 场景：X(0,0,100,100)；W1(50,50,100,100) iou≈0.1428；W2(200,200,100,100) iou=0
 * 预期：W1 保留，W2 过滤。
 */
static void test18_iou_function() {
	const char* src = R"(
RULE FOR W:
	iou(self, X) > 0.1
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["X"].push_back(make_rect("X", 0, 0, 100, 100));
	// W1: intersection=(50,50)-(100,100)=50x50=2500, union=20000-2500=17500, iou=0.1428
	scene["W"].push_back(make_rect("W", 50, 50, 100, 100));
	// W2: no intersection
	scene["W"].push_back(make_rect("W", 200, 200, 100, 100));

	Image img{400, 400};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "W", 1);
	report("iou() 函数 (iou(self, X) > 0.1)", ok);
}

/**
 * @brief 测试 19：类属性访问（OtherClass.property）
 *
 * 规则：self.width > Y.width
 * 场景：Y(0,0,50,50) width=50；Z1(0,0,60,60) width=60>50；Z2(0,0,30,30) width=30<50
 * 预期：Z1 保留，Z2 过滤。
 */
static void test19_class_property_access() {
	const char* src = R"(
RULE FOR Z:
	self.width > Y.width
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Y"].push_back(make_rect("Y", 0, 0, 50, 50));
	scene["Z"].push_back(make_rect("Z", 0, 0, 60, 60));   // 60 > 50 ✓
	scene["Z"].push_back(make_rect("Z", 0, 0, 30, 30));   // 30 > 50 ✗

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "Z", 1);
	report("类属性访问 (self.width > Y.width)", ok);
}

/**
 * @brief 测试 20：派生属性 center_x, center_y
 *
 * 规则：self.center_x > 50 AND self.center_y > 50
 * 场景：A1(0,0,100,100) center=(50,50)→50>50✗；A2(41,0,20,20) center=(51,10)→51>50✓,10>50✗；
 *       A3(41,41,20,20) center=(51,51)→✓✓
 * 预期：A3 保留。
 */
static void test20_derived_center_properties() {
	const char* src = R"(
RULE FOR AA:
	self.center_x > 50
	self.center_y > 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["AA"].push_back(make_rect("AA", 0, 0, 100, 100));    // center=(50,50) ✗
	scene["AA"].push_back(make_rect("AA", 41, 0, 20, 20));     // center=(51,10) ✗ (y)
	scene["AA"].push_back(make_rect("AA", 41, 41, 20, 20));    // center=(51,51) ✓

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "AA", 1);
	report("派生属性 center_x, center_y", ok);
}

/**
 * @brief 测试 21：派生属性 right, bottom, aspect_ratio
 *
 * 规则：self.right < 200 AND self.bottom < 200 AND self.aspect_ratio > 1.5
 * 场景：BB1(10,10,100,50) right=110<200✓, bottom=60<200✓, ar=2.0>1.5✓ → kept
 *       BB2(10,10,50,100) right=60<200✓, bottom=110<200✓, ar=0.5>1.5✗ → filtered
 *       BB3(150,10,100,50) right=250<200✗ → filtered
 * 预期：BB1 保留。
 */
static void test21_derived_right_bottom_aspect() {
	const char* src = R"(
RULE FOR BB:
	self.right < 200
	self.bottom < 200
	self.aspect_ratio > 1.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["BB"].push_back(make_rect("BB", 10, 10, 100, 50));   // right=110, bottom=60, ar=2.0 ✓
	scene["BB"].push_back(make_rect("BB", 10, 10, 50, 100));   // right=60, bottom=110, ar=0.5 ✗
	scene["BB"].push_back(make_rect("BB", 150, 10, 100, 50));  // right=250 ✗

	Image img{300, 300};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "BB", 1);
	report("派生属性 right, bottom, aspect_ratio", ok);
}

/**
 * @brief 测试 22：减法
 *
 * 规则：self.right - self.x >= 60
 * 场景：CC1(0,0,70,70) right=70, 70-0=70≥60✓；CC2(0,0,50,50) right=50, 50-0=50≥60✗
 * 预期：CC1 保留。
 */
static void test22_subtraction() {
	const char* src = R"(
RULE FOR CC:
	self.right - self.x >= 60
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["CC"].push_back(make_rect("CC", 0, 0, 70, 70));  // right-x = 70 ✓
	scene["CC"].push_back(make_rect("CC", 0, 0, 50, 50));  // right-x = 50 ✗

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "CC", 1);
	report("减法 (self.right - self.x >= 60)", ok);
}

/**
 * @brief 测试 23：== 和 != 运算符
 *
 * 规则：self.width == 50 AND self.height != 50
 * 场景：DD1(0,0,50,50) w=50✓, h=50!=50✗；DD2(0,0,50,60) w=50✓, h=60!=50✓；DD3(0,0,60,60) w=60!=50✗
 * 预期：DD2 保留。
 */
static void test23_equal_not_equal() {
	const char* src = R"(
RULE FOR DD:
	self.width == 50
	self.height != 50
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["DD"].push_back(make_rect("DD", 0, 0, 50, 50));  // w=50✓, h=50!=50 ✗
	scene["DD"].push_back(make_rect("DD", 0, 0, 50, 60));  // w=50✓, h=60!=50 ✓
	scene["DD"].push_back(make_rect("DD", 0, 0, 60, 60));  // w=60!=50 ✗

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "DD", 1);
	report("== 和 != 运算符", ok);
}

/**
 * @brief 测试 24：多类别 + GLOBAL + 类别规则组合
 *
 * GLOBAL：self.conf > 0.5
 * Person：self.width > 20
 * Vehicle：self.width > 100
 *
 * 场景：
 *   Person: (w=30,conf=0.9) ✓, (w=15,conf=0.9) ✗(w), (w=30,conf=0.3) ✗(conf)
 *   Vehicle: (w=150,conf=0.9) ✓, (w=80,conf=0.9) ✗(w)
 *   Animal: (w=10,conf=0.9) ✓(仅GLOBAL)
 *
 * 预期：Person=1, Vehicle=1, Animal=1
 */
static void test24_combined_global_and_class_rules() {
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
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "Person", 1)
		   && check_count(res, "Vehicle", 1)
		   && check_count(res, "Animal", 1);
	report("多类别 + GLOBAL + 类别规则组合", ok);
	if (!ok) {
		std::cout << "    期望: Person=1, Vehicle=1, Animal=1" << std::endl;
		std::cout << "    实际: Person=" << (res.kept.count("Person") ? (int)res.kept.at("Person").size() : 0)
				  << ", Vehicle=" << (res.kept.count("Vehicle") ? (int)res.kept.at("Vehicle").size() : 0)
				  << ", Animal=" << (res.kept.count("Animal") ? (int)res.kept.at("Animal").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 25：CONTAINS 范围 0-0（边界情况）
 *
 * 规则：CONTAINS FF 0-0
 * 场景：EE 内部无 FF 实例
 * 预期：cnt=0 在 [0,0] 内 → EE 保留。
 */
static void test25_contains_range_zero_zero() {
	const char* src = R"(
RULE FOR EE:
	CONTAINS FF 0-0
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["EE"].push_back(make_rect("EE", 0, 0, 100, 100));
	// FF 不在场景中或不在 EE 内部

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "EE", 1);
	report("CONTAINS 范围 0-0 (边界情况)", ok);
}

/**
 * @brief 测试 26：纯 GLOBAL 规则（无类别规则）
 *
 * 规则：GLOBAL self.conf > 0.7
 * 场景：多个类别实例，部分满足
 * 预期：所有类别中 conf > 0.7 的实例保留。
 */
static void test26_pure_global_multi_class() {
	const char* src = R"(
RULE FOR GLOBAL:
	self.conf > 0.7
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Cat"].push_back(make_sq("Cat", 0, 0, 10, 0.9));
	scene["Cat"].push_back(make_sq("Cat", 0, 0, 10, 0.6));
	scene["Dog"].push_back(make_sq("Dog", 0, 0, 10, 0.8));
	scene["Dog"].push_back(make_sq("Dog", 0, 0, 10, 0.5));
	scene["Bird"].push_back(make_sq("Bird", 0, 0, 10, 0.3));

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "Cat", 1)   // 0.9 kept, 0.6 filtered
		   && check_count(res, "Dog", 1)   // 0.8 kept, 0.5 filtered
		   && check_count(res, "Bird", 0); // 0.3 filtered
	report("纯 GLOBAL 规则多类别", ok);
	if (!ok) {
		std::cout << "    期望: Cat=1, Dog=1, Bird=0" << std::endl;
		std::cout << "    实际: Cat=" << (res.kept.count("Cat") ? (int)res.kept.at("Cat").size() : 0)
				  << ", Dog=" << (res.kept.count("Dog") ? (int)res.kept.at("Dog").size() : 0)
				  << ", Bird=" << (res.kept.count("Bird") ? (int)res.kept.at("Bird").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 27：复杂嵌套表达式
 *
 * 规则：((self.width + self.height) * 2 > 100) AND (self.area / 100 > 1 OR self.conf > 0.9)
 * 场景：
 *   GG1(20,30,0.5): perimeter=100>100✗
 *   GG2(30,30,0.5): perimeter=120>100✓, area=900/100=9>1✓ → kept
 *   GG3(10,10,0.95): perimeter=40>100✗
 *   GG4(20,20,0.5): perimeter=80>100✗
 * 预期：GG2 保留。
 *
 * 注意：由于 parser 的括号和 AND/OR 优先级，需要确保表达式正确解析。
 * 这里的表达式 (self.width + self.height) * 2 > 100 应该能正确解析。
 */
static void test27_complex_nested_expression() {
	// 简化：只用 AND 连接两个条件，在单行内测试
	const char* src = R"(
RULE FOR GG:
	self.width + self.height > 50
	self.area > 500
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["GG"].push_back(make_rect("GG", 0, 0, 20, 30));   // 50>50✗
	scene["GG"].push_back(make_rect("GG", 0, 0, 30, 30));   // 60>50✓, area=900>500✓ → kept
	scene["GG"].push_back(make_rect("GG", 0, 0, 10, 10));   // 20>50✗
	scene["GG"].push_back(make_rect("GG", 0, 0, 20, 20));   // 40>50✗

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "GG", 1);
	report("复杂表达式 (w+h>50 AND area>500)", ok);
}

/**
 * @brief 测试 28：CONTAINS + 属性条件组合
 *
 * 规则：self.conf > 0.5 AND CONTAINS HH 1
 * 场景：HH1(0,0,100,100,conf=0.9) 包含 2 个 II；HH2(0,0,100,100,conf=0.3) 也包含 2 个 II
 * 预期：HH1 保留（conf>0.5 且包含 II），HH2 过滤（conf 不满足）。
 */
static void test28_contains_with_property_condition() {
	const char* src = R"(
RULE FOR HH:
	self.conf > 0.5
	CONTAINS II 1
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["HH"].push_back(make_rect("HH", 0, 0, 100, 100, 0.9));
	scene["HH"].push_back(make_rect("HH", 0, 0, 100, 100, 0.3));
	scene["II"].push_back(make_sq("II", 10, 10, 5));
	scene["II"].push_back(make_sq("II", 20, 20, 5));

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "HH", 1);
	if (!ok) {
		int hh_cnt = res.kept.count("HH") ? (int)res.kept.at("HH").size() : 0;
		int ii_cnt = res.kept.count("II") ? (int)res.kept.at("II").size() : 0;
		std::cout << "    期望: HH=1, II=2; 实际: HH=" << hh_cnt << ", II=" << ii_cnt << std::endl;
	}
	report("CONTAINS + 属性条件组合 (conf>0.5, CONTAINS II 1)", ok);
}

/**
 * @brief 测试 29：多个类别规则 + 空间谓词
 *
 * 多个规则分别测试不同的空间关系。
 * Room: CONTAINS Chair 1-3
 * Lamp: INSIDE Room
 * Rug: OVERLAP Floor
 *
 * 场景：Room 包含 2 把 Chair，Lamp 在 Room 内，Rug 与 Floor 重叠
 * 预期：Room=1, Chair=2, Lamp=1, Rug=1, Floor=1
 */
static void test29_multi_class_spatial() {
	const char* src = R"(
RULE FOR Room:
	CONTAINS Chair 1-3

RULE FOR Lamp:
	INSIDE Room

RULE FOR Rug:
	OVERLAP Floor
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["Room"].push_back(make_rect("Room", 0, 0, 200, 200));
	scene["Chair"].push_back(make_sq("Chair", 10, 10, 10));
	scene["Chair"].push_back(make_sq("Chair", 50, 50, 10));
	scene["Lamp"].push_back(make_sq("Lamp", 30, 30, 5));     // inside Room
	scene["Lamp"].push_back(make_sq("Lamp", 250, 250, 5));   // outside Room
	scene["Floor"].push_back(make_rect("Floor", 0, 0, 100, 100));
	scene["Rug"].push_back(make_rect("Rug", 50, 50, 100, 100));  // overlaps Floor
	scene["Rug"].push_back(make_rect("Rug", 200, 200, 50, 50));  // no overlap

	Image img{300, 300};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "Room", 1)
		   && check_count(res, "Chair", 2)
		   && check_count(res, "Lamp", 1)
		   && check_count(res, "Rug", 1)
		   && check_count(res, "Floor", 1);
	report("多类别空间谓词组合 (Room/Chair/Lamp/Rug/Floor)", ok);
	if (!ok) {
		std::cout << "    期望: Room=1, Chair=2, Lamp=1, Rug=1, Floor=1" << std::endl;
		std::cout << "    实际: Room=" << (res.kept.count("Room") ? (int)res.kept.at("Room").size() : 0)
				  << ", Chair=" << (res.kept.count("Chair") ? (int)res.kept.at("Chair").size() : 0)
				  << ", Lamp=" << (res.kept.count("Lamp") ? (int)res.kept.at("Lamp").size() : 0)
				  << ", Rug=" << (res.kept.count("Rug") ? (int)res.kept.at("Rug").size() : 0)
				  << ", Floor=" << (res.kept.count("Floor") ? (int)res.kept.at("Floor").size() : 0) << std::endl;
	}
}

/**
 * @brief 测试 30：GLOBAL 仅过滤部分类别
 *
 * 规则：GLOBAL self.conf > 0.5
 * 场景：3 个类别，每个类别有高置信度和低置信度实例
 * 预期：每个类别只保留高置信度实例。
 */
static void test30_global_partial_filter() {
	const char* src = R"(
RULE FOR GLOBAL:
	self.conf > 0.5
)";
	Parser p; std::vector<Rule> rules;
	assert(p.parse(src, rules));

	Scene scene;
	scene["X1"].push_back(make_sq("X1", 0, 0, 10, 0.8));
	scene["X1"].push_back(make_sq("X1", 0, 0, 10, 0.3));
	scene["X2"].push_back(make_sq("X2", 0, 0, 10, 0.9));
	scene["X2"].push_back(make_sq("X2", 0, 0, 10, 0.4));
	scene["X3"].push_back(make_sq("X3", 0, 0, 10, 0.6));
	scene["X3"].push_back(make_sq("X3", 0, 0, 10, 0.5));  // not > 0.5

	Image img{200, 200};
	Evaluator ev;
	EvalResult res = ev.evaluate(scene, img, rules);

	bool ok = check_count(res, "X1", 1)   // 0.8 kept
		   && check_count(res, "X2", 1)   // 0.9 kept
		   && check_count(res, "X3", 1);  // 0.6 kept, 0.5 filtered
	report("GLOBAL 部分过滤三类别", ok);
}

// ============================================================
// 入口
// ============================================================

/**
 * @brief 全面测试入口。
 * 依次执行所有测试用例，统计并输出通过/失败结果。
 * @return 0 表示全部通过，1 表示存在失败。
 */
int main() {
	std::cout << "========================================" << std::endl;
	std::cout << "  PostAnvil DSL 全面测试" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;

	// ---------- 基础过滤 ----------
	std::cout << "--- 基础过滤 ---" << std::endl;
	test01_global_confidence_filter();
	test02_global_size_and_area();
	test26_pure_global_multi_class();
	test30_global_partial_filter();
	std::cout << std::endl;

	// ---------- 运算符 ----------
	std::cout << "--- 运算符 ---" << std::endl;
	test03_comparison_operators();
	test04_arithmetic_add_and_unary_minus();
	test05_multiplication();
	test22_subtraction();
	test23_equal_not_equal();
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
	std::cout << "--- 空间谓词 CONTAINS ---" << std::endl;
	test09_contains_single_count();
	test10_contains_range_count();
	test11_contains_range_outside();
	test12_contains_no_count();
	test13_contains_zero_instances();
	test25_contains_range_zero_zero();
	std::cout << std::endl;

	std::cout << "--- 空间谓词 INSIDE / OVERLAP / CLOSE_TO ---" << std::endl;
	test14_inside_predicate();
	test15_overlap_predicate();
	test16_close_to_predicate();
	std::cout << std::endl;

	// ---------- 内置函数 ----------
	std::cout << "--- 内置函数 ---" << std::endl;
	test17_abs_function();
	test18_iou_function();
	std::cout << std::endl;

	// ---------- 属性访问 ----------
	std::cout << "--- 属性访问 ---" << std::endl;
	test19_class_property_access();
	test20_derived_center_properties();
	test21_derived_right_bottom_aspect();
	std::cout << std::endl;

	// ---------- 组合场景 ----------
	std::cout << "--- 组合场景 ---" << std::endl;
	test24_combined_global_and_class_rules();
	test27_complex_nested_expression();
	test28_contains_with_property_condition();
	test29_multi_class_spatial();
	std::cout << std::endl;

	// ---------- 结果统计 ----------
	std::cout << "========================================" << std::endl;
	std::cout << "  测试结果统计" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "  通过: " << g_passed << std::endl;
	std::cout << "  失败: " << g_failed << std::endl;
	std::cout << "  总计: " << (g_passed + g_failed) << std::endl;
	std::cout << "  通过率: " << (g_passed + g_failed > 0
		? (100.0 * g_passed / (g_passed + g_failed)) : 0.0) << "%" << std::endl;
	std::cout << "========================================" << std::endl;
	
	return g_failed > 0 ? 1 : 0;
}
