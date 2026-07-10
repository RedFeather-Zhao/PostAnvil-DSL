/**
 * @file   compiler.hpp
 * @brief  PostAnvil DSL 编译器，基于 ANTLR4 ParseTree 将 DSL 源文本编译为可执行的算子管道
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
 * @brief 自定义 ANTLR4 错误监听器，用于收集语法分析过程中的错误信息
 */
struct PostAnvilErrorListener : public antlr4::BaseErrorListener {
	struct Error {
		int line;          // 错误所在行号
		int col;           // 错误所在列号
		std::string message; // 错误描述
	};

	std::vector<Error> errors;  // 收集到的所有错误

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
 * @brief PostAnvil DSL 编译器
 * @details 基于 ANTLR4 Listener 模式遍历 ParseTree，将 DSL 源文本编译为 CompiledProgram
 *
 * 编译流程：
 * 1. ANTLR4 词法/语法分析生成 ParseTree
 * 2. Listener 遍历 ParseTree，处理各类规则
 * 3. 表达式部分由 TreeExprCompiler 递归编译生成闭包
 * 4. 最终产出包含算子列表和函数注册表的 CompiledProgram
 *
 * 算子类型对应五种 DSL 规则：
 * - FILTER：条件过滤
 * - ATTR：属性计算
 * - GROUP：创建新类别
 * - APPEND：追加实例
 * - FUNC：自定义函数
 *
 * 类型系统：
 * - 编译期使用 Type 枚举推导表达式类型
 * - 运行时使用 Val 多态值传递数据
 */
class PostAnvilCompiler : public ::PostAnvilBaseListener {
public:
	PostAnvilCompiler() = default;

	/**
	 * @brief 编译 DSL 源文本
	 * @param source DSL 源代码
	 * @return CompiledProgram 编译结果，包含算子管道和函数表
	 * @throws CompileError 语法错误或编译错误时抛出
	 */
	CompiledProgram compile(const std::string& source) {
		// 重置编译状态
		m_program = CompiledProgram();
		m_current_filter.reset();
		m_current_attr.reset();
		m_current_group.reset();
		m_current_append.reset();
		m_current_vardef.reset();
		m_current_kind = RuleKind::FILTER;
		m_global_types.clear();

		// 初始化 ANTLR4 组件
		antlr4::ANTLRInputStream input(source);
		::PostAnvilLexer lexer(&input);
		antlr4::CommonTokenStream tokens(&lexer);
		::PostAnvilParser parser(&tokens);

		lexer.removeErrorListeners();
		parser.removeErrorListeners();

		PostAnvilErrorListener error_listener;
		lexer.addErrorListener(&error_listener);
		parser.addErrorListener(&error_listener);

		::PostAnvilParser::ProgramContext* tree = parser.program();

		if (error_listener.hasErrors()) {
			std::string err_msg;
			for (const auto& err : error_listener.errors) {
				err_msg += std::format("line {} col {}: {}\n", err.line, err.col, err.message);
			}
			throw CompileError(err_msg);
		}

		// 遍历 ParseTree 构建算子管道
		m_expr_compiler.functions = &m_program.functions;
		m_expr_compiler.global_types = &m_global_types;
		antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, tree);

		return std::move(m_program);
	}

private: // Listener 回调实现

	// =========================== IMPORT ===========================

	void enterImportDef(::PostAnvilParser::ImportDefContext* ctx) override {
		for (auto* item : ctx->importItem()) {
			std::string hostName = item->host->getText();
			std::string localName = item->local
				? item->local->getText()
				: hostName;
			utils::to_upper_inplace(localName);
			Type type = parseType(item->type());

			m_global_types[localName] = type;

			auto op = std::make_unique<ImportOperator>();
			op->host_name = hostName;
			op->local_name = localName;
			op->var_type = type;
			m_program.operators.emplace_back(std::move(op));
		}
	}

	// =========================== EXPORT ===========================

	void enterExportDef(::PostAnvilParser::ExportDefContext* ctx) override {
		for (auto* item : ctx->exportItem()) {
			std::string hostName = item->host->getText();
			auto typed = m_expr_compiler.compile(item->expr());

			auto op = std::make_unique<ExportOperator>();
			op->host_name = hostName;
			op->expression = std::move(typed.func);
			m_program.operators.emplace_back(std::move(op));
		}
	}

	// =========================== GlobalDef ===========================

	void enterGlobalDef(::PostAnvilParser::GlobalDefContext* ctx) override {
		std::string varName = ctx->IDENTIFIER()->getText();
		utils::to_upper_inplace(varName);

		Type declaredType = parseType(ctx->type());
		auto initExpr = m_expr_compiler.compile(ctx->expr());

		if (initExpr.type != declaredType) {
			throw CompileError("Global variable '" + varName + "' declared as " +
				std::string(type_name(declaredType)) + " but initialized with " +
				std::string(type_name(initExpr.type)));
		}

		m_global_types[varName] = declaredType;

		m_current_vardef = std::make_unique<VarDefOperator>();
		m_current_vardef->var_name = varName;
		m_current_vardef->var_type = declaredType;
		m_current_vardef->initializer = std::move(initExpr.func);
	}

	void exitGlobalDef(::PostAnvilParser::GlobalDefContext* /*ctx*/) override {
		if (m_current_vardef) {
			m_program.operators.emplace_back(std::move(m_current_vardef));
		}
	}

	// =========================== FILTER ===========================

	void enterFilter_rule(::PostAnvilParser::Filter_ruleContext* ctx) override {
		m_current_kind = RuleKind::FILTER;
		m_current_filter = std::make_unique<FilterOperator>();
		m_current_filter->target = m_expr_compiler.compileClassExpr(ctx->class_expr());
	}

	void exitFilter_rule(::PostAnvilParser::Filter_ruleContext* /*ctx*/) override {
		if (m_current_filter) {
			m_program.operators.emplace_back(std::move(m_current_filter));
		}
	}

	// ============================ ATTR ============================

	void enterAttr_rule(::PostAnvilParser::Attr_ruleContext* ctx) override {
		m_current_kind = RuleKind::ATTR;
		m_current_attr = std::make_unique<AttributeOperator>();
		m_current_attr->target = m_expr_compiler.compileClassExpr(ctx->class_expr());
	}

	void exitAttr_rule(::PostAnvilParser::Attr_ruleContext* /*ctx*/) override {
		if (m_current_attr) {
			m_program.operators.emplace_back(std::move(m_current_attr));
		}
	}

	/**
	 * @brief 处理属性定义语句
	 * @details 区分实例属性 self.xxx 和类别属性 "cls".xxx
	 */
	void enterAttr_def(::PostAnvilParser::Attr_defContext* ctx) override {
		if (!m_current_attr) return;

		auto* lvalue = ctx->attr_lvalue();
		if (!lvalue) return;

		std::string attr_name;
		bool is_class_attr = false;
		std::string cls_name;

		if (auto* inst_def = dynamic_cast<::PostAnvilParser::InstanceAttrDefContext*>(lvalue)) {
			attr_name = inst_def->IDENTIFIER()->getText();
		}
		else if (auto* cls_def = dynamic_cast<::PostAnvilParser::ClassAttrDefContext*>(lvalue)) {
			attr_name = cls_def->IDENTIFIER()->getText();
			is_class_attr = true;
			cls_name = utils::strip_quotes(cls_def->STRING()->getText());
			utils::to_upper_inplace(cls_name);
		}
		else {
			throw CompileError("Unknown attribute definition type");
		}

		utils::to_upper_inplace(attr_name);

		auto typed = m_expr_compiler.compile(ctx->expr());

		m_current_attr->attr_defs.emplace_back(
			std::move(attr_name),
			std::move(typed.func),
			is_class_attr,
			cls_name
		);
	}

	/**
	 * @brief 处理布尔表达式，将其编译为过滤条件
	 * @details FILTER、GROUP、APPEND 规则中的条件行统一由此处处理
	 */
	void enterBool_expr(::PostAnvilParser::Bool_exprContext* ctx) override {
		auto filterFunc = m_expr_compiler.compileAsBool(ctx->or_expr());

		if (m_current_filter) {
			m_current_filter->conditions.emplace_back(filterFunc);
		}
		else if (m_current_group) {
			m_current_group->conditions.emplace_back(filterFunc);
		}
		else if (m_current_append) {
			m_current_append->conditions.emplace_back(filterFunc);
		}
	}

	// =========================== GROUP ===========================

	void enterGroup_rule(::PostAnvilParser::Group_ruleContext* ctx) override {
		m_current_kind = RuleKind::GROUP;
		m_current_group = std::make_unique<GroupOperator>();
		auto class_exprs = ctx->class_expr();
		if (class_exprs.size() >= 2) {
			m_current_group->new_class = m_expr_compiler.compileClassExpr(class_exprs[0]);
			m_current_group->source_class = m_expr_compiler.compileClassExpr(class_exprs[1]);
		}
	}

	void exitGroup_rule(::PostAnvilParser::Group_ruleContext* /*ctx*/) override {
		if (m_current_group) {
			m_program.operators.emplace_back(std::move(m_current_group));
		}
	}

	// =========================== APPEND ===========================

	void enterAppend_rule(::PostAnvilParser::Append_ruleContext* ctx) override {
		m_current_kind = RuleKind::APPEND;
		m_current_append = std::make_unique<AppendOperator>();
		auto class_exprs = ctx->class_expr();
		if (class_exprs.size() >= 2) {
			m_current_append->dest_class = m_expr_compiler.compileClassExpr(class_exprs[0]);
			m_current_append->source_class = m_expr_compiler.compileClassExpr(class_exprs[1]);
		}
	}

	void exitAppend_rule(::PostAnvilParser::Append_ruleContext* /*ctx*/) override {
		if (m_current_append) {
			m_program.operators.emplace_back(std::move(m_current_append));
		}
	}

	// =========================== FUNC ===========================

	void enterFunc_rule(::PostAnvilParser::Func_ruleContext* ctx) override {
		m_current_kind = RuleKind::FUNC;
		m_current_func = std::make_unique<FuncOperator>();

		m_current_func->name = ctx->name->getText();
		utils::to_upper_inplace(m_current_func->name);

		if (ctx->typed_params()) {
			for (auto const* param : ctx->typed_params()->typed_param()) {
				std::string pname = param->param_name->getText();
				utils::to_upper_inplace(pname);
				m_current_func->param_names.push_back(pname);
			}
		}

		auto statements = ctx->func_statement();
		if (statements.empty()) {
			throw CompileError("FUNC rule '" + m_current_func->name + "' has no body statements");
		}

		// 编译最后一条语句作为返回值
		// TODO: 当前实现未处理多条语句，需重构为完整语句块编译
		auto* last_stmt = statements[statements.size() - 1];

		if (auto* ret_stmt = dynamic_cast<::PostAnvilParser::FuncReturnStmtContext*>(last_stmt)) {
			auto ret_expr = m_expr_compiler.compile(ret_stmt->expr());
			m_current_func->body = [ret_expr](const std::vector<double>& /*args*/, EvaluationContext& /*ctx*/) -> double {
				Instance dummy("__dummy", 0, 0, 0, 0, 0);
				Scene empty_scene({ 0, 0 });
				return ret_expr.func(dummy, empty_scene).as_bool() ? 1.0 : 0.0;
				};
		}
		else if (auto* expr_stmt = dynamic_cast<::PostAnvilParser::FuncExprStmtContext*>(last_stmt)) {
			auto ret_expr = m_expr_compiler.compile(expr_stmt->expr());
			m_current_func->body = [ret_expr](const std::vector<double>& /*args*/, EvaluationContext& /*ctx*/) -> double {
				Instance dummy("__dummy", 0, 0, 0, 0, 0);
				Scene empty_scene({ 0, 0 });
				return ret_expr.func(dummy, empty_scene).as_bool() ? 1.0 : 0.0;
				};
		}
		else {
			m_current_func->body = [](const std::vector<double>&, EvaluationContext&) -> double {
				return 0.0;
				};
		}
	}

	void exitFunc_rule(::PostAnvilParser::Func_ruleContext* /*ctx*/) override {
		if (m_current_func) {
			m_program.functions[m_current_func->name] = m_current_func->body;
			m_program.operators.emplace_back(std::move(m_current_func));
		}
	}

	// ======================== Helpers ============================


	/**
	 * @brief 解析类型节点为 Type 枚举
	 */
	static Type parseType(::PostAnvilParser::TypeContext* ctx) {
		if (!ctx) return Type::T_NUM;
		if (ctx->NUM())  return Type::T_NUM;
		if (ctx->STR())  return Type::T_STR;
		if (ctx->BOOL()) return Type::T_BOOL;
		return Type::T_NUM;
	}

	// 当前正在构建的算子
	std::unique_ptr<FilterOperator>    m_current_filter;
	std::unique_ptr<AttributeOperator> m_current_attr;
	std::unique_ptr<GroupOperator>     m_current_group;
	std::unique_ptr<AppendOperator>    m_current_append;
	std::unique_ptr<FuncOperator>      m_current_func;
	std::unique_ptr<VarDefOperator>    m_current_vardef;

	RuleKind               m_current_kind = RuleKind::FILTER;
	TreeExprCompiler       m_expr_compiler;    // 表达式编译器
	CompiledProgram        m_program;          // 编译结果

	std::unordered_map<std::string, Type>        m_global_types;      // 全局变量类型表
};

} // namespace postanvil