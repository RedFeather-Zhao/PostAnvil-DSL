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
		m_expr_compiler.set_functions(&m_program.functions);
		m_expr_compiler.set_global_types(&m_global_types);

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
			handle_compile_error(err_msg);
		}

		// 遍历 ParseTree 构建算子管道
		antlr4::tree::ParseTreeWalker::DEFAULT.walk(this, tree);

		return std::move(m_program);
	}

private: // Listener 回调实现

	// =========================== IMPORT ===========================

	void enterImportDef(::PostAnvilParser::ImportDefContext* ctx) override {
		for (auto* item : ctx->importItem()) {
			std::string hostName = utils::get_upper_text(item->host);
			std::string localName = item->local
				? utils::get_upper_text(item->local)
				: hostName;
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

	/**
	 * @brief 全局变量定义/赋值语句
	 *		globalDef
	 *			: type IDENTIFIER '=' expr NEWLINE
	 *			| IDENTIFIER '=' expr NEWLINE
	 *			;
	 * 
	 * @param ctx
	 */
	void enterGlobalDef(::PostAnvilParser::GlobalDefContext* ctx) override {
		auto varName = utils::get_upper_text(ctx->IDENTIFIER());
		auto initExpr = m_expr_compiler.compile(ctx->expr());
		Type type;

		if (ctx->type()) {
			// 若带类型，则为变量声明
			type = parseType(ctx->type());
			if (type == Type::T_ANY) {
				type = initExpr.type;
			}

			if (initExpr.type != type && initExpr.type != Type::T_ANY) {
				auto err = std::format("Global variable '{}' declared as {} but initialized with {}",
					varName, type_name(type), type_name(initExpr.type));
				handle_compile_error(err, ctx);
			}

			if (m_global_types.contains(varName)) {
				auto err = std::format("Global variable '{}' already declared", varName);
				handle_compile_error(err, ctx);
			}
			m_global_types[varName] = type;
		}
		else {
			// 否则为赋值，应确保类型一致
			if (!m_global_types.contains(varName)) {
				auto err = std::format("Cannot assign to undeclared global variable '{}'", varName);
				handle_compile_error(err, ctx);
			}

			type = m_global_types[varName];
			if (initExpr.type != type && initExpr.type != Type::T_ANY) {
				auto err = std::format("Global variable '{}' declared as {} but assigned with {}",
					varName, type_name(type), type_name(initExpr.type));
				handle_compile_error(err, ctx);
			}
		}

		m_current_vardef = std::make_unique<VarDefOperator>();
		m_current_vardef->var_name = varName;
		m_current_vardef->var_type = type;
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
			attr_name = utils::get_upper_text(inst_def->IDENTIFIER());
		}
		else if (auto* cls_def = dynamic_cast<::PostAnvilParser::ClassAttrDefContext*>(lvalue)) {
			attr_name = utils::get_upper_text(cls_def->IDENTIFIER());
			is_class_attr = true;
			cls_name = utils::strip_quotes(utils::get_upper_text(cls_def->STRING()));
		}
		else {
			handle_compile_error("Unknown attribute definition type", ctx);
		}

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
		m_current_func = std::make_unique<FuncOperator>();
		m_current_func->name = utils::get_upper_text(ctx->name);

		// 收集参数名 TODO: 此处应该对参数类型做记录
		if (ctx->typed_params()) {
			for (auto const* param : ctx->typed_params()->typed_param()) {
				m_current_func->param_names.emplace_back(
					utils::get_upper_text(param->param_name)
				);
			}
		}

		// 编译函数体语句
		auto statements = ctx->func_statement();
		std::vector<StatementFunc> body_stmts;
		for (auto* stmt : statements) {
			body_stmts.push_back(compileFuncStatement(stmt));
		}

		// 生成 CompiledFunc
		auto param_names = m_current_func->param_names;
		m_current_func->body = [param_names, body_stmts]
		(const std::vector<Val>& args, const Instance& self, EvaluationContext& ctx) -> Val
		{
			ctx.push_scope();
			ctx.curr_inst = &self;

			// 导入参数并执行
			size_t arg_count = std::min(args.size(), param_names.size());
			for (size_t i = 0; i < arg_count; ++i) {
				ctx.set_var(param_names[i], args[i]);
			}
			for (auto& stmt : body_stmts) {
				if (ctx.is_returned) {
					break;
				}
				stmt(ctx);
			}

			ctx.curr_inst = nullptr;
			ctx.pop_scope();

			// 返回计算值
			if (!ctx.is_returned) {
				throw RuntimeError("Function current branch no return!");
			}
			ctx.is_returned = false;
			return ctx.return_value;
		};
	}

	void exitFunc_rule(::PostAnvilParser::Func_ruleContext* /*ctx*/) override {
		if (m_current_func) {
			m_program.functions[m_current_func->name] = m_current_func->body;
			m_program.operators.emplace_back(std::move(m_current_func));
		}
	}

	StatementFunc compileFuncVarDef(::PostAnvilParser::FuncVarDefContext* ctx) {
		std::string name = utils::get_upper_text(ctx->IDENTIFIER());
		auto typed = m_expr_compiler.compile(ctx->expr());

		return [name, func = std::move(typed.func)](EvaluationContext& ctx) {
			Val val = func(Scene::make_dummy(), ctx);
			ctx.set_var(name, val);
		};
	}

	StatementFunc compileFuncAssign(::PostAnvilParser::FuncAssignContext* ctx) {
		std::string name = utils::get_upper_text(ctx->IDENTIFIER());
		auto typed = m_expr_compiler.compile(ctx->expr());

		return [name, func = std::move(typed.func)](EvaluationContext& ctx) {
			// 注意：赋值在函数内默认操作局部变量（如果已存在则更新，否则在当前作用域创建）
			// 如果想支持修改全局变量，可以在未找到局部变量时 fallback 到全局
			Val val = func(Scene::make_dummy(), ctx);
			ctx.set_var(name, val);
			};
	}

	// 编译 forStmt
	StatementFunc compileForStmt(::PostAnvilParser::ForStmtContext* ctx) {
		std::string loop_var = utils::get_upper_text(ctx->IDENTIFIER());
		auto class_expr = m_expr_compiler.compileClassExpr(ctx->class_expr());

		std::vector<StatementFunc> body_stmts;
		for (auto* stmt : ctx->func_statement()) {
			body_stmts.push_back(compileFuncStatement(stmt));
		}

		return [loop_var, class_expr, body_stmts](EvaluationContext& ctx) {
			std::string cls_name = class_expr(Scene::make_dummy(), ctx);

			// 特殊处理 "GLOBAL"：遍历所有类别
			if (cls_name == "GLOBAL") {
				for (auto& pair : ctx.scene.objects) {
					const std::string& category = pair.first;
					// 用类别名字符串作为循环变量值
					ctx.push_scope();
					ctx.set_var(loop_var, Val(category));
					ctx.curr_inst = nullptr;
					for (auto& stmt : body_stmts) {
						if (ctx.is_returned) break;
						stmt(ctx);
					}
					ctx.curr_inst = nullptr;
					ctx.pop_scope();
					if (ctx.is_returned) break;
				}
				return;
			}

			// 普通类别
			auto it = ctx.scene.objects.find(cls_name);
			if (it == ctx.scene.objects.end()) {
				// 类别不存在，跳过循环
				return;
			}

			for (const Instance& inst : it->second) {
				ctx.push_scope();
				ctx.loop_vars[loop_var] = &inst;
				ctx.curr_inst = &inst;
				for (auto& stmt : body_stmts) {
					if (ctx.is_returned) break;
					stmt(ctx);
				}
				ctx.loop_vars.erase(loop_var);
				ctx.curr_inst = nullptr;
				ctx.pop_scope();
				if (ctx.is_returned) break;
			}
			};
	}

	// 编译 ifStmt
	StatementFunc compileIfStmt(::PostAnvilParser::IfStmtContext* ctx) {
		auto cond = m_expr_compiler.compileAsBool(ctx->expr()->or_expr());
		// 获取所有 func_statement 节点
		auto all_stmts = ctx->func_statement();
		std::vector<::PostAnvilParser::Func_statementContext*> then_stmts;
		std::vector<::PostAnvilParser::Func_statementContext*> else_stmts;

		// 查找 ELSE token 的位置（如果有）
		if (auto else_token = ctx->ELSE()) {
			size_t else_pos = else_token->getSymbol()->getTokenIndex();
			for (auto* stmt : all_stmts) {
				// 获取该语句的第一个 token 位置
				size_t stmt_start = stmt->getStart()->getTokenIndex();
				if (stmt_start < else_pos) {
					then_stmts.push_back(stmt);
				}
				else {
					else_stmts.push_back(stmt);
				}
			}
		}
		else {
			then_stmts = all_stmts;
		}

		// 编译 THEN 分支
		std::vector<StatementFunc> then_bodies;
		for (auto* stmt : then_stmts) {
			then_bodies.push_back(compileFuncStatement(stmt));
		}

		std::vector<StatementFunc> else_bodies;
		for (auto* stmt : else_stmts) {
			else_bodies.push_back(compileFuncStatement(stmt));
		}

		return [cond, then_bodies, else_bodies](EvaluationContext& ctx) {
			bool condition = cond(*ctx.curr_inst, ctx);
			if (condition) {
				for (auto& stmt : then_bodies) {
					if (ctx.is_returned) break;
					stmt(ctx);
				}
			}
			else {
				for (auto& stmt : else_bodies) {
					if (ctx.is_returned) break;
					stmt(ctx);
				}
			}
			};
	}

	// 编译返回语句
	StatementFunc compileFuncReturn(::PostAnvilParser::FuncReturnStmtContext* ctx) {
		auto typed = m_expr_compiler.compile(ctx->expr());
		return [func = std::move(typed.func)](EvaluationContext& ctx) {
			Val val = func(*ctx.curr_inst, ctx);
			ctx.do_return(std::move(val));
		};
	}

	// 编译单条语句
	StatementFunc compileFuncStatement(::PostAnvilParser::Func_statementContext* ctx) {
		if (auto* varDef = dynamic_cast<::PostAnvilParser::FuncVarDefContext*>(ctx)) {
			return compileFuncVarDef(varDef);
		}
		if (auto* assign = dynamic_cast<::PostAnvilParser::FuncAssignContext*>(ctx)) {
			return compileFuncAssign(assign);
		}
		if (auto* ifStmt = dynamic_cast<::PostAnvilParser::FuncIfStmtContext*>(ctx)) {
			return compileIfStmt(ifStmt->ifStmt());
		}
		if (auto* forStmt = dynamic_cast<::PostAnvilParser::FuncForStmtContext*>(ctx)) {
			return compileForStmt(forStmt->forStmt());
		}
		if (auto* exprStmt = dynamic_cast<::PostAnvilParser::FuncExprStmtContext*>(ctx)) {
			auto typed = m_expr_compiler.compile(exprStmt->expr());
			return [func = std::move(typed.func)](EvaluationContext& ctx) {
				// 表达式语句仅求值，丢弃结果
				func(*ctx.curr_inst, ctx);
			};
		}
		if (auto* retStmt = dynamic_cast<::PostAnvilParser::FuncReturnStmtContext*>(ctx)) {
			return compileFuncReturn(retStmt);
		}

		// 未知类型
		handle_compile_error("Unknown func_statement type", ctx);
	}

	// ======================== Helpers ============================


	/**
	 * @brief 解析类型节点为 Type 枚举
	 */
	static Type parseType(::PostAnvilParser::TypeContext* ctx) {
		using enum postanvil::Type;
		if (!ctx)			return T_ERROR;
		if (ctx->NUM())		return T_NUM;
		if (ctx->STR())		return T_STR;
		if (ctx->BOOL())	return T_BOOL;
		if (ctx->ANY())		return T_ANY;
		return T_ERROR;
	}

private:

	std::unique_ptr<FilterOperator>		m_current_filter;
	std::unique_ptr<AttributeOperator>	m_current_attr;
	std::unique_ptr<GroupOperator>		m_current_group;
	std::unique_ptr<AppendOperator>		m_current_append;
	std::unique_ptr<FuncOperator>		m_current_func;
	std::unique_ptr<VarDefOperator>		m_current_vardef;

	detail::str_map<Type>				m_global_types;


	RuleKind							m_current_kind = RuleKind::FILTER;
	TreeExprCompiler					m_expr_compiler;
	CompiledProgram						m_program;
};

} // namespace postanvil