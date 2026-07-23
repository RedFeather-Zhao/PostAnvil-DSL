#include "test_common.hpp"
#include <iostream>

int main() {
	std::cout << "========================================" << std::endl;
	std::cout << "  PostAnvil v0.3 数据驱动测试框架" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;

	PostAnvilCompiler compiler;
	std::vector<TestCase> all_tests;

	// 合并所有模块的测试用例
	auto append = [&](const std::vector<TestCase>& module_tests) {
		all_tests.insert(all_tests.end(), module_tests.begin(), module_tests.end());
	};

	 //append(get_basic_tests());
	 // append(get_attr_tests());
	 //append(get_group_append_tests());
	 //append(get_bool_sort_func_tests());
	 // append(get_new_features_tests());
	 append(get_control_flow_tests());
	 //append(get_import_export_tests());
	 //append(get_end_to_end_tests());

	int passed = 0;
	int failed = 0;
	for (const auto& tc : all_tests) {
		if (run_test_case(tc, compiler))
			++passed;
		else
			++failed;
	}

	std::cout << "\n========================================" << std::endl;
	std::cout << "  测试结果统计" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "  通过: " << passed << std::endl;
	std::cout << "  失败: " << failed << std::endl;
	std::cout << "  总计: " << (passed + failed) << std::endl;
	std::cout << "  通过率: " << (passed + failed > 0 ? 100.0 * passed / (passed + failed) : 0.0) << "%" << std::endl;
	std::cout << "========================================" << std::endl;

	return failed > 0 ? 1 : 0;
}