#pragma once

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

namespace postanvil::test::framework {

inline bool no_color_requested() noexcept {
#ifdef _WIN32
	char* value = nullptr;
	std::size_t size = 0;
	const auto error = _dupenv_s(&value, &size, "NO_COLOR");
	const auto requested = error == 0 && value && value[0] != '\0';
	std::free(value);
	return requested;
#else
	const auto* value = std::getenv("NO_COLOR");
	return value && value[0] != '\0';
#endif
}

inline bool should_use_color() {
	static const bool use = !no_color_requested() && isatty(fileno(stdout)) != 0;
	return use;
}

inline std::string_view color_reset() {
	static const std::string reset = should_use_color() ? "\033[0m" : "";
	return reset;
}

inline std::string_view color_green() {
	static const std::string green = should_use_color() ? "\033[32m" : "";
	return green;
}

inline std::string_view color_red() {
	static const std::string red = should_use_color() ? "\033[31m" : "";
	return red;
}

inline std::string_view color_bold() {
	static const std::string bold = should_use_color() ? "\033[1m" : "";
	return bold;
}

using TestFunction = void (*)();

struct TestCase {
	std::string name;
	TestFunction function;
};

inline std::vector<TestCase>& registry()
{
	static std::vector<TestCase> tests;
	return tests;
}

class Registrar {
public:
	Registrar(std::string name, TestFunction function)
	{
		registry().push_back({ std::move(name), function });
	}
};

inline std::string narrow_message(const wchar_t* message)
{
	if (message == nullptr) return {};
	std::string result;
	while (*message != L'\0') {
		const wchar_t ch = *message++;
		result.push_back(ch >= 0 && ch <= 0x7f ? static_cast<char>(ch) : '?');
	}
	return result;
}

[[noreturn]] inline void fail(const char* assertion, const wchar_t* message)
{
	std::string text = assertion;
	const auto suffix = narrow_message(message);
	if (!suffix.empty()) text += ": " + suffix;
	throw std::runtime_error(text);
}

class Assert {
public:
	static void IsTrue(bool condition, const wchar_t* message = nullptr)
	{
		if (!condition) fail("Assert::IsTrue failed", message);
	}

	template<class Expected, class Actual>
	static void AreEqual(
		const Expected& expected,
		const Actual& actual,
		const wchar_t* message = nullptr)
	{
		if (!(expected == actual)) fail("Assert::AreEqual failed", message);
	}

	template<class Expected, class Actual, class Tolerance>
	static void AreEqual(
		const Expected& expected,
		const Actual& actual,
		const Tolerance& tolerance,
		const wchar_t* message = nullptr)
	{
		const auto difference = std::abs(
			static_cast<double>(expected) - static_cast<double>(actual));
		if (difference > static_cast<double>(tolerance)) {
			fail("Assert::AreEqual failed (outside tolerance)", message);
		}
	}
};

inline int run_all_tests() {
	std::size_t passed = 0;
	for (const auto& test : registry()) {
		try {
			test.function();
			++passed;
			std::cout << color_green() << "[PASS] " << color_reset() << test.name << '\n';
		}
		catch (const std::exception& error) {
			std::cerr << color_red() << "[FAIL] " << color_reset() << test.name
				<< ": " << error.what() << '\n';
		}
		catch (...) {
			std::cerr << color_red() << "[FAIL] " << color_reset() << test.name
				<< ": unknown exception\n";
		}
	}

	const auto total = registry().size();
	const auto failed = total - passed;
	std::cout << "\nPostAnvil tests: "
		<< color_green() << passed << color_reset() << " passed, "
		<< color_red() << failed << color_reset() << " failed, "
		<< total << " total\n";
	return failed == 0 ? 0 : 1;
}

} // namespace postanvil::test::framework

// 保留原测试中的 Assert 名称，测试体无需堆砌平台适配代码。
namespace Microsoft::VisualStudio::CppUnitTestFramework {
using Assert = ::postanvil::test::framework::Assert;
}

#define POSTANVIL_TEST_JOIN_IMPL(lhs, rhs) lhs##rhs
#define POSTANVIL_TEST_JOIN(lhs, rhs) POSTANVIL_TEST_JOIN_IMPL(lhs, rhs)
#define PA_TEST(name)                                                        \
	static void name();                                                      \
	static const ::postanvil::test::framework::Registrar                     \
		POSTANVIL_TEST_JOIN(postanvil_test_registrar_, __LINE__)(#name, &name); \
	static void name()
