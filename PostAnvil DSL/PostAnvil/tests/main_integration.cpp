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
	append_tests(tests, get_import_export_tests());
	append_tests(tests, get_end_to_end_tests());
	return run_test_suite("宿主集成测试", tests);
}
