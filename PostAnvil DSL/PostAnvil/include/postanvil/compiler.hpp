/**
 * @file   compiler.hpp
 * @brief  PostAnvil DSL 编译器 —— 基于 ANTLR4 ParseTree 的规则编译
 * @detail 本文件实现了 PostAnvil 的编译型评估架构，核心设计为"算子管道"模式：
 *
 * 编译流程（基于 ANTLR4 Listener）：
 *         PostAnvilCompiler 使用 ANTLR4 生成的 Lexer/Parser 将 DSL 源文本解析为
 *         ParseTree，然后通过 Listener 模式遍历 ParseTree，直接编译为算子管道。
 *         表达式部分使用 TreeExprCompiler 递归遍历 ParseTree 节点，生成闭包。
 *
 * 执行流程（Evaluate）：
 *         CompiledProgram 持有算子序列，对输入场景依次执行每个算子的 apply()，
 *         最终输出 EvalResult
 *
 * 算子类型（Operator）：
 *         1. OP_FILTER：按条件过滤实例，保留满足条件的实例
 *         2. OP_ATTRIBUTE：为类别每个实例添加计算属性
 *
 * 支持的表达式类型：
 * - 数值常量、属性访问（self.* / image.*）
 * - 比较运算（< > <= >= == !=）
 * - 算术运算（+ - * /）
 * - 逻辑运算（AND / OR / NOT）
 *
 * 注意：ANTLR4 语法使用 caseInsensitive = true 选项，标识符的原始大小写保留在
 * token 文本中。编译器在内部统一转换为大写进行比较。
 *
 * @author RedFeather-Zhao
 * @date   June 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once
#include "postanvil/program.hpp"
#include "postanvil/expr_compiler.hpp"
#include "antlr4-runtime.h"
#include "PostAnvilLexer.h"
#include "PostAnvilParser.h"
#include "PostAnvilBaseListener.h"
#include <memory>
#include <string>

namespace postanvil {

// ====================== ANTLR4 Error Listener ======================

/**
 * @brief 自定义 ANTLR4 错误监听器，收集语法错误信息
 */
struct PostAnvilErrorListener : public antlr4::BaseErrorListener {
	struct Error {
		int line;
		int col;
		std::string message;
	};

	std::vector<Error> errors;

	void syntaxError(antlr4::Recognizer* /*recognizer*/, antlr4::Token* /*offendingSymbol*/,
	                 size_t line, size_t charPositionInLine,
	                 const std::string& msg, std::exception_ptr /*e*/) override {
		errors.emplace_back(static_cast<int>(line), static_cast<int>(charPositionInLine), msg);
	}

	bool hasErrors() const { return !errors.empty(); }
};

// ====================== PostAnvilCompiler =========================

/**
 * @brief PostAnvil DSL 编译器 —— 基于 ANTLR4 Listener
 *
 * PostAnvilCompiler 是 PostAnvil 的主编译器。它使用 ANTLR4 生成的
 * Lexer/Parser 将 DSL 源文本解析为 ParseTree，然后通过 Listener 模式
 * 遍历 ParseTree，直接编译为 CompiledProgram（算子管道）。
 *
 * 架构设计：
 * - 顶层结构（program/ruledef/statement）→ 使用 Listener 回调处理
 * - 表达式编译 → 使用 TreeExprCompiler 递归遍历 ParseTree
 *
 * 使用方式：
 * @code
 *   PostAnvilCompiler compiler;
 *   CompiledProgram program = compiler.compile(source);
 *   EvalResult result = program.evaluate(scene, image);
 * @endcode
 */
class PostAnvilCompiler : public ::PostAnvilBaseListener {
public:
	PostAnvilCompiler() = default;

	/**
	 * @brief 编译 DSL 源文本，返回可复用的 CompiledProgram
	 *
	 * 编译流程：
	 * 1. 创建 ANTLR4 输入流、词法分析器、token 流、语法分析器
	 * 2. 安装自定义错误监听器
	 * 3. 解析为 ParseTree
	 * 4. 使用 Listener 遍历 ParseTree，构建算子管道
	 * 5. 返回 CompiledProgram
	 *
	 * @param source - DSL 源文本
	 * @return CompiledProgram - 编译后的算子管道
	 * @throws CompileError - 语法错误或编译错误时抛出
	 */
	CompiledProgram compile(const std::string& source) {
		// 重置状态
		m_program = CompiledProgram();
		m_current_filter.reset();
		m_current_attr.reset();
		m_current_kind = RuleKind::FILTER;

		// 创建 ANTLR4 组件
		antlr4::ANTLRInputStream input(source);
		::PostAnvilLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		::PostAnvilParser parser(&tokens);

		// 安装自定义错误监听器
		lexer.removeErrorListeners();
		parser.removeErrorListeners();

		PostAnvilErrorListener error_listener;
		lexer.addErrorListener(&error_listener);
		parser.addErrorListener(&error_listener);

		// 解析
		::PostAnvilParser::ProgramContext* tree = parser.program();

		// 检查语法错误
		if (error_listener.hasErrors()) {
			const auto& err = error_listener.errors[0];
			throw CompileError(err.message, err.line, err.col);
		}

		// 使用 Listener 遍历 ParseTree，构建算子管道
		antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, tree);

		return std::move(m_program);
	}

	// ======================== Listener 回调 ============================

	/**
	 * @brief 进入规则节点：识别规则类型（FILTER/ATTR）和目标，创建对应算子
	 */
	void enterRuledef(::PostAnvilParser::RuledefContext* ctx) override {
		// 获取目标类别名
		m_current_target = ctx->target->getText();
		to_upper_inplace(m_current_target);

		if (ctx->FILTER()) {
			m_current_kind = RuleKind::FILTER;
			m_current_filter = std::make_unique<FilterOperator>();
			m_current_filter->target = m_current_target;
		} else if (ctx->ATTR()) {
			m_current_kind = RuleKind::ATTR;
			m_current_attr = std::make_unique<AttributeOperator>();
			m_current_attr->target = m_current_target;
		}
	}

	/**
	 * @brief 退出规则节点：将当前算子加入 CompiledProgram
	 */
	void exitRuledef(::PostAnvilParser::RuledefContext* /*ctx*/) override {
		if (m_current_kind == RuleKind::FILTER && m_current_filter) {
			m_program.operators.push_back(std::move(m_current_filter));
		} else if (m_current_kind == RuleKind::ATTR && m_current_attr) {
			m_program.operators.push_back(std::move(m_current_attr));
		}
	}

	/**
	 * @brief 进入表达式语句：编译过滤条件表达式，添加到 FilterOperator
	 */
	void enterExprStmt(::PostAnvilParser::ExprStmtContext* ctx) override {
		if (!m_current_filter) return;

		auto numFunc = m_expr_compiler.compile(ctx->expr());
		m_current_filter->conditions.emplace_back(
			[numFunc](const Instance& self, const Scene& scene, const Image& img) {
				return numFunc(self, scene, img) != 0.0;
			}
		);
	}

	/**
	 * @brief 进入赋值语句：编译属性赋值表达式，添加到 AttributeOperator
	 */
	void enterAssignStmt(::PostAnvilParser::AssignStmtContext* ctx) override {
		if (!m_current_attr) return;

		auto* attr_assign = ctx->attr_assign();
		if (!attr_assign) return;

		// 获取属性名并转大写
		std::string attr_name = attr_assign->attr_name->getText();
		to_upper_inplace(attr_name);

		// 编译属性值表达式
		auto numFunc = m_expr_compiler.compile(attr_assign->expr());

		m_current_attr->attr_defs.emplace_back(
			std::move(attr_name),
			std::move(numFunc)
		);
	}

private:
	CompiledProgram m_program;							//< 编译结果
	std::unique_ptr<FilterOperator> m_current_filter;	//< 当前正在编译的 FILTER 算子
	std::unique_ptr<AttributeOperator> m_current_attr;	//< 当前正在编译的 ATTR 算子
	std::string m_current_target;						//< 当前规则目标类别名
	RuleKind m_current_kind = RuleKind::FILTER;			//< 当前规则类型
	TreeExprCompiler m_expr_compiler;					//< 表达式编译器
};

} // namespace postanvil