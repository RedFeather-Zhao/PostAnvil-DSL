#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include "PostAnvil.h"

using namespace postanvil;

struct TestCase {
	std::string name;
	std::string source;
	std::function<Scene()> buildScene;
	std::function<bool(const Scene&, std::string&)> verify;
};

// 辅助验证函数
bool check_count(
	const Scene& res,
	const std::string& cls,
	int expected_count);

bool check_prop(const Scene& res,
	const std::string& cls,
	int idx,
	const std::string& prop,
	const Val& expected);

bool check_class_prop(
	const Scene& res,
	const std::string& cls,
	const std::string& prop,
	const Val& expected);

// 测试运行器
bool run_test_case(
	const TestCase& tc,
	PostAnvilCompiler& compiler
);

// 各模块测试生成函数

std::vector<TestCase> get_basic_tests();

std::vector<TestCase> get_attr_tests();

std::vector<TestCase> get_group_append_tests();

std::vector<TestCase> get_bool_sort_func_tests();

std::vector<TestCase> get_new_features_tests();

std::vector<TestCase> get_control_flow_tests();

std::vector<TestCase> get_import_export_tests();

std::vector<TestCase> get_end_to_end_tests();

