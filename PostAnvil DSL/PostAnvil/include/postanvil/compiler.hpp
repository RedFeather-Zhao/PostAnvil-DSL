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
 *         2. OP_ATTRIBUTE：为类别每个实例添加计算属性（支持实例/类级别）
 *         3. OP_GROUP：从源类别创建新类别
 *         4. OP_APPEND：向目标类别追加实例
 *         5. OP_FUNC：自定义函数
 *
 * 支持的表达式类型：
 * - 数值常量、属性访问（self.* / img.* / "class".*）
 * - 比较运算（< > <= >= == !=）
 * - 算术运算（+ - * /）
 * - 逻辑运算（AND / OR / NOT）
 * - 布尔字面量（TRUE / FALSE）
 * - 函数调用、SORT 排序原语
 *
 * 注意：ANTLR4 语法使用 caseInsensitive = true 选项，标识符的原始大小写保留在
 * token 文本中。编译器在内部统一转换为大写进行比较。
 *
 * @author RedFeather-Zhao
 * @date   July 2026
 * @copyright Copyright (c) 2026 RedFeather-Zhao, All Rights Reserved.
 */

#pragma once

#include <memory>
#include <format>

#include "antlr4-runtime.h"
#include "PostAnvilLexer.h"
#include "PostAnvilParser.h"
#include "PostAnvilBaseListener.h"

#include "program.hpp"
#include "expr_compiler.hpp"

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
	                 const std::string& msg, std::exception_ptr /*e*/) override
	{
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
 * - 顶层结构（program/declaration/rule_）→ 使用 Listener 回调处理
 * - 表达式编译 → 使用 TreeExprCompiler 递归遍历 ParseTree
 *
 * 使用方式：
 * @code
 *   PostAnvilCompiler compiler;
 *   CompiledProgram program = compiler.compile(source);
 *   EvalResult result = program.evaluate(scene);
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
		m_current_group.reset();
		m_current_append.reset();
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
			std::string err_msg;
			for (const auto& err : error_listener.errors) {
				err_msg += std::format("line {} col {}: {}\n", err.line, err.col, err.message);
			}
			throw CompileError(err_msg);
		}

		// 使用 Listener 遍历 ParseTree，构建算子管道
		// 设置表达式编译器的函数注册表指针
		m_expr_compiler.functions = &m_program.functions;
		antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, tree);

		return std::move(m_program);
	}

	// ======================== Listener 回调 ============================

	// ---------- FILTER 规则 ----------

	/**
	 * @brief 进入 FILTER 规则：创建 FilterOperator
	 */
	void enterFilter_rule(::PostAnvilParser::Filter_ruleContext* ctx) override {
		m_current_kind = RuleKind::FILTER;
		m_current_target = resolve_class_expr(ctx->class_expr());
		m_current_filter = std::make_unique<FilterOperator>();
		m_current_filter->target = m_current_target;
	}

	/**
	 * @brief 退出 FILTER 规则：将 FilterOperator 加入管道
	 */
	void exitFilter_rule(::PostAnvilParser::Filter_ruleContext* /*ctx*/) override {
		if (m_current_filter) {
			m_program.operators.push_back(std::move(m_current_filter));
		}
	}

	// ---------- ATTR 规则 ----------

	/**
	 * @brief 进入 ATTR 规则：创建 AttributeOperator
	 */
	void enterAttr_rule(::PostAnvilParser::Attr_ruleContext* ctx) override {
		m_current_kind = RuleKind::ATTR;
		m_current_target = resolve_class_expr(ctx->class_expr());
		m_current_attr = std::make_unique<AttributeOperator>();
		m_current_attr->target = m_current_target;
	}

	/**
	 * @brief 退出 ATTR 规则：将 AttributeOperator 加入管道
	 */
	void exitAttr_rule(::PostAnvilParser::Attr_ruleContext* /*ctx*/) override {
		if (m_current_attr) {
			m_program.operators.push_back(std::move(m_current_attr));
		}
	}

	/**
	 * @brief 进入属性定义：编译 self.xxx = expr 或 "class".xxx = expr
	 */
	void enterAttr_def(::PostAnvilParser::Attr_defContext* ctx) override {
		if (!m_current_attr) return;

		auto* lvalue = ctx->attr_lvalue();
		if (!lvalue) return;

		std::string attr_name;
		bool is_class_attr = false;
		std::string cls_name;

		// 区分 InstanceAttrDef 和 ClassAttrDef
		if (auto* inst_def = dynamic_cast<::PostAnvilParser::InstanceAttrDefContext*>(lvalue)) {
			// self.xxx = expr
			attr_name = inst_def->IDENTIFIER()->getText();
		} else if (auto* cls_def = dynamic_cast<::PostAnvilParser::ClassAttrDefContext*>(lvalue)) {
			// "class".xxx = expr
			attr_name = cls_def->IDENTIFIER()->getText();
			is_class_attr = true;
			cls_name = utils::strip_quotes(cls_def->STRING()->getText());
			utils::to_upper_inplace(cls_name);
		} else {
			return; // 未知类型
		}

		utils::to_upper_inplace(attr_name);

		// 编译属性值表达式
		auto numFunc = m_expr_compiler.compile(ctx->expr());

		// 如果是类级别属性，记录到当前算子
		if (is_class_attr) {
			m_current_attr->is_class_attr = true;
			m_current_attr->class_name = cls_name;
		}

		m_current_attr->attr_defs.emplace_back(
			std::move(attr_name),
			std::move(numFunc)
		);
	}

	// ---------- 布尔表达式（FILTER/GROUP/APPEND 共用） ----------

	/**
	 * @brief 进入布尔表达式：编译条件并添加到当前算子
	 */
	void enterBool_expr(::PostAnvilParser::Bool_exprContext* ctx) override {
		auto numFunc = m_expr_compiler.compile(ctx->or_expr());
		auto filterFunc = [numFunc](const Instance& self, const Scene& scene) {
			return numFunc(self, scene) != 0.0;
		};

		if (m_current_filter) {
			m_current_filter->conditions.push_back(filterFunc);
		} else if (m_current_group) {
			m_current_group->conditions.push_back(filterFunc);
		} else if (m_current_append) {
			m_current_append->conditions.push_back(filterFunc);
		}
	}

	// ---------- GROUP 规则 ----------

	void enterGroup_rule(::PostAnvilParser::Group_ruleContext* ctx) override {
		m_current_kind = RuleKind::GROUP;
		m_current_group = std::make_unique<GroupOperator>();

		// new_class 是 STRING 字面量
		std::string new_cls = utils::strip_quotes(ctx->STRING()->getText());
		utils::to_upper_inplace(new_cls);
		m_current_group->new_class = new_cls;
		m_current_group->source_class = resolve_class_expr(ctx->class_expr());
	}

	void exitGroup_rule(::PostAnvilParser::Group_ruleContext* /*ctx*/) override {
		if (m_current_group) {
			m_program.operators.push_back(std::move(m_current_group));
		}
	}

	// ---------- APPEND 规则 ----------

	void enterAppend_rule(::PostAnvilParser::Append_ruleContext* ctx) override {
		m_current_kind = RuleKind::APPEND;
		m_current_append = std::make_unique<AppendOperator>();

		// class_expr(0) = 目标类别, class_expr(1) = 源类别
		auto class_exprs = ctx->class_expr();
		if (class_exprs.size() >= 2) {
			m_current_append->dest_class = resolve_class_expr(class_exprs[0]);
			m_current_append->source_class = resolve_class_expr(class_exprs[1]);
		}
	}

	void exitAppend_rule(::PostAnvilParser::Append_ruleContext* /*ctx*/) override {
		if (m_current_append) {
			m_program.operators.push_back(std::move(m_current_append));
		}
	}

	// ---------- FUNC 规则 ----------

	// TODO 完全错误
	void enterFunc_rule(::PostAnvilParser::Func_ruleContext* ctx) override {
		m_current_kind = RuleKind::FUNC;
		m_current_func = std::make_unique<FuncOperator>();

		// 函数名
		m_current_func->name = ctx->name->getText();
		utils::to_upper_inplace(m_current_func->name);

		// 解析参数列表
		if (ctx->typed_params()) {
			for (auto* param : ctx->typed_params()->typed_param()) {
				std::string pname = param->param_name->getText();
				utils::to_upper_inplace(pname);
				m_current_func->param_names.push_back(pname);
			}
		}

		// 编译函数体：将所有 func_statement 编译为一个返回最后值的闭包
		auto statements = ctx->func_statement();
		if (statements.empty()) {
				throw CompileError("FUNC rule '" + m_current_func->name + "' has no body statements");
			}
			if (!statements.empty()) {
			// 编译最后一条语句的值作为返回值
			auto* last_stmt = statements[statements.size() - 1];

			// 检查是否为 RETURN 语句
			if (auto* ret_stmt = dynamic_cast<::PostAnvilParser::FuncReturnStmtContext*>(last_stmt)) {
				auto ret_expr = m_expr_compiler.compile(ret_stmt->expr());
				m_current_func->body = [ret_expr](const std::vector<double>& /*args*/, EvaluationContext& /*ctx*/) -> double {
					// 简化版：使用虚拟实例执行返回表达式
					Instance dummy("__dummy", 0, 0, 0, 0, 0);
					Scene empty_scene({0, 0});
					return ret_expr(dummy, empty_scene);
				};
			} else if (auto* expr_stmt = dynamic_cast<::PostAnvilParser::FuncExprStmtContext*>(last_stmt)) {
				auto ret_expr = m_expr_compiler.compile(expr_stmt->expr());
				m_current_func->body = [ret_expr](const std::vector<double>& /*args*/, EvaluationContext& /*ctx*/) -> double {
					Instance dummy("__dummy", 0, 0, 0, 0, 0);
					Scene empty_scene({0, 0});
					return ret_expr(dummy, empty_scene);
				};
			} else {
				// 默认返回 0.0
				m_current_func->body = [](const std::vector<double>&, EvaluationContext&) -> double {
					return 0.0;
				};
			}
		}
	}

	void exitFunc_rule(::PostAnvilParser::Func_ruleContext* /*ctx*/) override {
		if (m_current_func) {
			// 将函数注册到 CompiledProgram 的函数注册表
			m_program.functions[m_current_func->name] = m_current_func->body;
			m_program.operators.push_back(std::move(m_current_func));
		}
	}

private:
	/**
	 * @brief 解析 class_expr（STRING 或 IDENTIFIER），返回大写类别名
	 */
	std::string resolve_class_expr(::PostAnvilParser::Class_exprContext* ctx) {
		if (!ctx) return "";
		if (ctx->STRING()) {
			std::string s = utils::strip_quotes(ctx->STRING()->getText());
			utils::to_upper_inplace(s);
			return s;
		}
		if (ctx->IDENTIFIER()) {
			std::string s = ctx->IDENTIFIER()->getText();
			utils::to_upper_inplace(s);
			return s;
		}
		return "";
	}

	CompiledProgram m_program;							//< 编译结果
	std::unique_ptr<FilterOperator> m_current_filter;	//< 当前正在编译的 FILTER 算子
	std::unique_ptr<AttributeOperator> m_current_attr;	//< 当前正在编译的 ATTR 算子
	std::unique_ptr<GroupOperator> m_current_group;		//< 当前正在编译的 GROUP 算子
	std::unique_ptr<AppendOperator> m_current_append;	//< 当前正在编译的 APPEND 算子
	std::unique_ptr<FuncOperator> m_current_func;		//< 当前正在编译的 FUNC 算子
	std::string m_current_target;						//< 当前规则目标类别名
	RuleKind m_current_kind = RuleKind::FILTER;			//< 当前规则类型
	TreeExprCompiler m_expr_compiler;					//< 表达式编译器
};

} // namespace postanvil