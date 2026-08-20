#include "pch.h"

using namespace postanvil;

namespace UnitTest1Basic {

namespace {

PACompileError compile_error_from(std::string_view source)
{
	try {
		(void)Compiler{}.compile(source);
	}
	catch (const PACompileError& error) {
		return error;
	}
	throw std::runtime_error("Expected Compiler::compile to throw PACompileError");
}

bool contains(std::string_view text, std::string_view expected)
{
	return text.find(expected) != std::string_view::npos;
}

} // namespace

PA_TEST(SyntaxDiagnosticShowsSourceCaretAndFriendlyHint)
{
	const auto error = compile_error_from(
		"RULE FILTER \"person\" {\n"
		"    self.conf >= 0.5\n"
		"    OR self.area > 10\n"
		"}\n");

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		error.kind() == PACompileError::Kind::Syntax);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(3, error.line());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(5, error.column());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(
		std::string("    OR self.area > 10"), error.source_line());

	const std::string rendered = error.what();
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "3 |     OR self.area > 10"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "|     ^"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "cannot start a new statement"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "help:"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		!contains(rendered, "expecting {"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		!error.raw_message().empty());
}

PA_TEST(SemanticDiagnosticIsEnrichedWithSourceContext)
{
	const auto error = compile_error_from("NUM threshold = missing\n");

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		error.kind() == PACompileError::Kind::Semantic);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(1, error.line());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(17, error.column());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(
		std::string("NUM threshold = missing"), error.source_line());

	const std::string rendered = error.what();
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "PostAnvil semantic error at line 1, column 17"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "Undefined variable: MISSING"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(rendered, "|                 ^"));
}

PA_TEST(FilterTypeDiagnosticPointsAtInvalidExpression)
{
	const auto error = compile_error_from(
		"RULE FILTER \"person\" {\n"
		"    1\n"
		"}\n");

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		error.kind() == PACompileError::Kind::Semantic);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(2, error.line());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(5, error.column());
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(error.what(), "must be BOOL"));
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(error.what(), "2 |     1"));
}

PA_TEST(UnescapedPhysicalNewlineCannotAppearInsideString)
{
	const auto error = compile_error_from(
		"STR value = \"first\n"
		"second\"\n");

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		error.kind() == PACompileError::Kind::Syntax);
}

PA_TEST(UnknownBuiltInGroupIsRejected)
{
	const auto error = compile_error_from(
		"RULE FILTER @UNKNOWN {\n"
		"    TRUE\n"
		"}\n");

	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		error.kind() == PACompileError::Kind::Semantic);
	Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsTrue(
		contains(error.what(), "@UNKNOWN"));
}

} // namespace UnitTest1Basic
