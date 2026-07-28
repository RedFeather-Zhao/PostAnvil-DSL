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
	append_tests(tests, get_basic_tests());
	append_tests(tests, get_attr_tests());
	append_tests(tests, get_group_append_tests());
	return run_test_suite("基础规则测试", tests);
}
