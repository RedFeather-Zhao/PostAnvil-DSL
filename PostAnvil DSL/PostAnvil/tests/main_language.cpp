#include "test_common.hpp"

namespace {
void append_tests(std::vector<TestCase>& target, std::vector<TestCase> source)
{
	target.insert(target.end(),
		std::make_move_iterator(source.begin()),
		std::make_move_iterator(source.end()));
}
}

int main()
{
	std::vector<TestCase> tests;
	append_tests(tests, get_bool_sort_func_tests());
	append_tests(tests, get_new_features_tests());
	append_tests(tests, get_control_flow_tests());
	return run_test_suite("语言特性测试", tests);
}
