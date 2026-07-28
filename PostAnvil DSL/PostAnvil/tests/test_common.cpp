#include "test_common.hpp"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

bool check_count(
	const Scene& res,
	const std::string& cls,
	int expected_count)
{
	auto it = res.objects.find(cls);
	int actual = 0;
	if (it != res.objects.end()) {
		actual = static_cast<int>(it->second.size());
	}
	return actual == expected_count;
}

bool check_prop(
	const Scene& res,
	const std::string& cls,
	int idx,
	const std::string& prop,
	const Val& expected)
{
	auto it = res.objects.find(cls);
	if (it == res.objects.end() || idx >= static_cast<int>(it->second.size())) {
		return false;
	}

	Val actual = it->second[idx].get_prop(prop);
	if (!type_strict_equal(actual.type(), expected.type())) {
		return false;
	}
	return actual == expected;
}

bool check_class_prop(
	const Scene& res,
	const std::string& cls,
	const std::string& prop,
	const Val& expected)
{
	auto it = res.class_props.find(cls);
	if (it == res.class_props.end()) {
		return false;
	}

	auto pit = it->second.find(prop);
	if (pit == it->second.end()) {
		return false;
	}
	return pit->second == expected;
}

bool run_test_case(
	const TestCase& tc,
	PostAnvilCompiler& compiler)
{
	try {
		CompiledProgram prog = compiler.compile(tc.source);
		Scene scene = tc.buildScene();
		Scene res = prog.evaluate(scene);

		std::string err_msg;
		bool ok = tc.verify(res, err_msg);

		if (ok) {
			std::cout << "  [PASS] " << tc.name;
		}
		else {
			std::cout << "  [FAIL] " << tc.name;
		}

		if (!ok && !err_msg.empty()) {
			std::cout << "  (" << err_msg << ")";
		}
		std::cout << std::endl;
		return ok;
	}
	catch (const std::exception& e) {
		std::cout << "  [FAIL] " << tc.name << "  (exception: " << e.what() << ")" << std::endl;
		return false;
	}
}

int run_test_suite(
	const std::string& suite_name,
	const std::vector<TestCase>& tests)
{
#ifdef _WIN32
	// 测试源码使用 UTF-8 执行字符集，同步 Windows 控制台以避免中文乱码。
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	std::cout << "========================================\n";
	std::cout << "  PostAnvil " << suite_name << "\n";
	std::cout << "========================================\n\n";

	PostAnvilCompiler compiler;
	int passed = 0;
	int failed = 0;
	for (const auto& test : tests) {
		if (run_test_case(test, compiler)) ++passed;
		else ++failed;
	}

	std::cout << "\n========================================\n";
	std::cout << "  测试结果统计\n";
	std::cout << "========================================\n";
	std::cout << "  通过: " << passed << '\n';
	std::cout << "  失败: " << failed << '\n';
	std::cout << "  总计: " << tests.size() << '\n';
	std::cout << "  通过率: "
		<< (tests.empty() ? 0.0 : 100.0 * passed / tests.size()) << "%\n";
	std::cout << "========================================\n";
	return failed == 0 ? 0 : 1;
}
