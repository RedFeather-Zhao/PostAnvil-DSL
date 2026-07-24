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
		m_type_scope.clear();
		m_expr_compiler.set_functions(&m_program.functions);
		m_expr_compiler.set_type_scope(&m_type_scope);

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

			m_type_scope.set_global(localName, type);

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
		Type type = Type::T_ANY;

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

			if (m_type_scope.checkup(varName)) {
				auto err = std::format("Global variable '{}' already declared, type = {}", varName);
				handle_compile_error(err, ctx);
			}
			m_type_scope.set_global(varName, type);
		}
		else {
			// 否则为赋值，应确保类型一致
			if (!m_type_scope.checkup(varName)) {
				auto err = std::format("Cannot assign to undeclared global variable '{}'", varName);
				handle_compile_error(err, ctx);
			}

			m_type_scope.lookup(varName, type);
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
		m_type_scope.push();
		m_current_func = std::make_unique<FuncOperator>();
		m_current_func->name = utils::get_upper_text(ctx->name);

		// 解析返回类型
		Type ret_type = Type::T_ANY;
		if (ctx->return_type) {
			ret_type = parseType(ctx->return_type);
		}
		auto& function_info = m_program.functions[m_current_func->name];
		function_info.ret_type = ret_type;
		function_info.param_types.clear();

		// 编译参数，视为导入的局部变量
		if (ctx->typed_params()) {
			for (auto const* param : ctx->typed_params()->typed_param()) {
				auto name = utils::get_upper_text(param->param_name);
				Type param_type = parseType(param->param_type);
				m_type_scope.set_local(name, param_type);
				m_current_func->param_names.emplace_back(name);
				function_info.param_types.emplace_back(param_type);
			}
		}

		// 编译函数体语句
		auto statements = ctx->func_statement();
		std::vector<StatementFunc> body_stmts;
		for (size_t i = 0; i < statements.size(); ++i) {
			body_stmts.emplace_back(compileFuncStatement(statements[i], i + 1 == statements.size()));
		}

		// 生成 CompiledFunc
		auto& param_names = m_current_func->param_names;
		m_current_func->body = [param_names, body_stmts]
		(const std::vector<Val>& args, const Instance& self, EvaluationContext& ctx) -> Val
		{
			ctx.push_scope();
			const Instance* previous_inst = ctx.curr_inst;
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

			ctx.curr_inst = previous_inst;
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
			m_program.functions[m_current_func->name].func = m_current_func->body;
			m_program.operators.emplace_back(std::move(m_current_func));
		}
		m_type_scope.pop();
	}

	/**
	 * @brief 编译函数体变量定义语句闭包
	 *
	 * @param ctx				- FuncVarDefContext 标签
	 * @return StatementFunc	- 语句闭包
	 */
	StatementFunc compileFuncVarDef(::PostAnvilParser::FuncVarDefContext* ctx) {
		std::string name = utils::get_upper_text(ctx->IDENTIFIER());
		auto typed = m_expr_compiler.compile(ctx->expr());
		Type declared = parseType(ctx->type());
		if (declared == Type::T_ANY) {
			declared = typed.type;
		}
		if (!type_compatible(declared, typed.type)) {
			auto err = std::format("Local variable '{}' declared as {} but initialized with {}",
				name, type_name(declared), type_name(typed.type));
			handle_compile_error(err, ctx);
		}
		m_type_scope.set_local(name, declared);

		return [name, func = std::move(typed.func)](EvaluationContext& ctx) {
			Val val = func(ctx.curr_inst ? *ctx.curr_inst : Scene::make_dummy(), ctx);
			ctx.set_var(name, val);
		};
	}

	/**
	 * @brief 编译函数体变量赋值语句闭包
	 *
	 * @param ctx				- FuncAssignContext 标签
	 * @return StatementFunc	- 语句闭包
	 */
	StatementFunc compileFuncAssign(::PostAnvilParser::FuncAssignContext* ctx) {
		std::string name = utils::get_upper_text(ctx->IDENTIFIER());
		auto typed = m_expr_compiler.compile(ctx->expr());
		
		Type existing;
		if (!m_type_scope.lookup(name, existing)) {
			handle_compile_error("Assignment to undeclared variable '" + name + "'", ctx);
		}
		if (!type_compatible(existing, typed.type)) {
			auto err = std::format("Type mismatch: variable '{}' is {}, assigned {}",
				name, type_name(existing), type_name(typed.type));
			handle_compile_error(err, ctx);
		}
		// 赋值并不改变变量类型

		return [name, func = std::move(typed.func)](EvaluationContext& ctx) {
			Val val = func(ctx.curr_inst ? *ctx.curr_inst : Scene::make_dummy(), ctx);
			ctx.set_var(name, val);
		};
	}

	/**
	 * @brief 编译函数体 if 控制语句闭包
	 *
	 * @param ctx				- IfStmtContext 标签
	 * @return StatementFunc	- 语句闭包
	 */
	StatementFunc compileIfStmt(::PostAnvilParser::IfStmtContext* ctx) {
		struct Branch {
			BoolFunc cond;
			std::vector<StatementFunc> stmts;
		};
		std::vector<Branch> branches;

		// IF
		m_type_scope.push();
		auto if_cond = m_expr_compiler.compileAsBool(ctx->expr()->or_expr());
		std::vector<StatementFunc> if_stmts;
		for (auto* stmt : ctx->func_statement()) {
			if_stmts.emplace_back(compileFuncStatement(stmt));
		}
		branches.emplace_back(std::move(if_cond), std::move(if_stmts));
		m_type_scope.pop();

		// ELIF
		for (auto* elif_ctx : ctx->elifBranch()) {
			m_type_scope.push();
			auto cond = m_expr_compiler.compileAsBool(elif_ctx->expr()->or_expr());
			std::vector<StatementFunc> stmts;
			for (auto* stmt : elif_ctx->func_statement()) {
				stmts.emplace_back(compileFuncStatement(stmt));
			}
			branches.emplace_back(std::move(cond), std::move(stmts));
			m_type_scope.pop();
		}

		// ELSE
		std::vector<StatementFunc> else_stmts;
		if (auto* else_ctx = ctx->elseBranch()) {
			m_type_scope.push();
			for (auto* stmt : else_ctx->func_statement()) {
				else_stmts.emplace_back(compileFuncStatement(stmt));
			}
			m_type_scope.pop();
		}
		branches.emplace_back([](const Instance&, EvaluationContext&) { return true; },
			std::move(else_stmts));

		// 生成闭包：依次判断 if -> elif -> else
		return [branches = std::move(branches)](EvaluationContext& ctx) {
			for (const auto& branch : branches) {
				if (!branch.cond(*ctx.curr_inst, ctx)) {
					continue;
				}
				ctx.push_scope();
				for (auto& stmt : branch.stmts) {
					if (ctx.is_returned) {
						break;
					}
					stmt(ctx);
				}
				ctx.pop_scope();
				return;  // 执行完当前分支后立即返回
			}
		};
	}

	/**
	 * @brief 编译函数体 for 循环语句闭包
	 *
	 * @param ctx				- ForStmtContext 标签
	 * @return StatementFunc	- 语句闭包
	 */
	StatementFunc compileForStmt(::PostAnvilParser::ForStmtContext* ctx) {
		m_type_scope.push();
		std::string loop_var = utils::get_upper_text(ctx->IDENTIFIER());
		auto class_expr = m_expr_compiler.compileClassExpr(ctx->class_expr());

		// "global" 遍历类别名；普通类别遍历 INST。动态类别表达式运行时决定。
		Type loop_type = Type::T_ANY;
		if (ctx->class_expr()->STRING()) {
			auto literal = utils::strip_quotes(utils::get_upper_text(ctx->class_expr()->STRING()));
			loop_type = literal == EvaluationContext::GLOBAL_TARGET ? Type::T_STR : Type::T_INST;
		}
		m_type_scope.set_local(loop_var, loop_type);

		std::vector<StatementFunc> body_stmts;
		for (auto* stmt : ctx->func_statement()) {
			body_stmts.emplace_back(compileFuncStatement(stmt));
		}
		m_type_scope.pop();

		return [loop_var, class_expr, body_stmts](EvaluationContext& ctx) {
			std::string cls_name = class_expr(Scene::make_dummy(), ctx);
			const Instance* previous_inst = ctx.curr_inst;

			// 特殊处理 "GLOBAL"：遍历所有类别
			if (cls_name == "GLOBAL") {
				// TODO: "GLOBAL"视为所有类别的分组，未来支持若干类合并为一组，同样支持循环
				for (const auto& [category, _] : ctx.scene.objects) {
					ctx.push_scope();
					ctx.set_var(loop_var, category);
					ctx.curr_inst = previous_inst;
					for (auto& stmt : body_stmts) {
						if (ctx.is_returned) {
							break;
						}
						stmt(ctx);
					}
					ctx.curr_inst = previous_inst;
					ctx.pop_scope();
					if (ctx.is_returned) {
						break;
					}
				}
				ctx.curr_inst = previous_inst;
				return;
			}

			// 普通类别
			auto it = ctx.scene.objects.find(cls_name);
			if (it == ctx.scene.objects.end()) {
				throw RuntimeError(std::format("Class {} is undefined!", cls_name));
			}

			for (const Instance& inst : it->second) {
				ctx.push_scope();
				ctx.set_var(loop_var, Val(inst));
				ctx.curr_inst = &inst;
				for (auto& stmt : body_stmts) {
					if (ctx.is_returned) {
						break;
					}
					stmt(ctx);
				}
				ctx.curr_inst = previous_inst;
				ctx.pop_scope();
				if (ctx.is_returned) {
					break;
				}
			}
			ctx.curr_inst = previous_inst;
		};
	}

	/**
	 * @brief 编译函数体表达式语句闭包，支持可能有副作用的语句
	 * 
	 * @param ctx				- FuncExprStmtContext 标签
	 * @return StatementFunc	- 语句闭包
	 */
	StatementFunc compileExprStmt(::PostAnvilParser::FuncExprStmtContext* ctx, bool implicit_return) {
		auto typed = m_expr_compiler.compile(ctx->expr());
		if (implicit_return) {
			if (auto it = m_program.functions.find(m_current_func->name); it != m_program.functions.end()) {
				Type declared = it->second.ret_type;
				if (!type_compatible(declared, typed.type)) {
					auto err = std::format("Return type mismatch: function declared {}, but returns {}",
						type_name(declared), type_name(typed.type));
					handle_compile_error(err, ctx);
				}
			}
			return [func = std::move(typed.func)](EvaluationContext& ctx) {
				Val val = func(ctx.curr_inst ? *ctx.curr_inst : Scene::make_dummy(), ctx);
				ctx.do_return(std::move(val));
			};
		}
		return [func = std::move(typed.func)](EvaluationContext& ctx) {
			(void)func(ctx.curr_inst ? *ctx.curr_inst : Scene::make_dummy(), ctx);
		};
	}

	/**
	 * @brief 编译返回语句闭包
	 * 
	 * @param ctx				- FuncReturnStmtContext 标签
	 * @return StatementFunc	- 状态闭包
	 */
	StatementFunc compileFuncReturn(::PostAnvilParser::FuncReturnStmtContext* ctx) {
		auto typed = m_expr_compiler.compile(ctx->expr());
		if (auto it = m_program.functions.find(m_current_func->name); it != m_program.functions.end()) {
			Type declared = it->second.ret_type;
			if (!type_compatible(declared, typed.type)) {
				auto err = std::format("Return type mismatch: function declared {}, but returns {}",
					type_name(declared), type_name(typed.type));
				handle_compile_error(err, ctx);
			}
		}

		return [func = std::move(typed.func)](EvaluationContext& ctx) {
			Val val = func(ctx.curr_inst ? *ctx.curr_inst : Scene::make_dummy(), ctx);
			ctx.do_return(std::move(val));
		};
	}

	// 编译单条语句
	StatementFunc compileFuncStatement(::PostAnvilParser::Func_statementContext* ctx, bool implicit_return = false) {
		if (auto* varDef = dynamic_cast<::PostAnvilParser::FuncVarDefContext*>(ctx)) {
			return compileFuncVarDef(varDef);
		}
		if (auto* assign = dynamic_cast<::PostAnvilParser::FuncAssignContext*>(ctx)) {
			return compileFuncAssign(assign);
		}
		if (auto* ifStmt = dynamic_cast<::PostAnvilParser::FuncIfStmtContext*>(ctx)) {
			return compileIfStmt(ifStmt->ifStmt());		// 编译通用if语句
		}
		if (auto* forStmt = dynamic_cast<::PostAnvilParser::FuncForStmtContext*>(ctx)) {
			return compileForStmt(forStmt->forStmt());	// 编译通用for语句
		}
		if (auto* exprStmt = dynamic_cast<::PostAnvilParser::FuncExprStmtContext*>(ctx)) {
			return compileExprStmt(exprStmt, implicit_return);
		}
		if (auto* retStmt = dynamic_cast<::PostAnvilParser::FuncReturnStmtContext*>(ctx)) {
			return compileFuncReturn(retStmt);
		}
		handle_compile_error("Unknown func_statement type", ctx);
	}

	// ======================== Helpers ============================


	/**
	 * @brief 解析类型节点为 Type 枚举
	 */
	static Type parseType(::PostAnvilParser::TypeContext* ctx) {
		using enum postanvil::Type;
		if (!ctx)			handle_compile_error("Nullptr: ctx", ctx);
		if (ctx->NUM())		return T_NUM;
		if (ctx->STR())		return T_STR;
		if (ctx->BOOL())	return T_BOOL;
		if (ctx->INST())	return T_INST;
		if (ctx->ANY())		return T_ANY;
		handle_compile_error("Error type", ctx);
	}

private:
	//====================== 编译算子 ======================//

	std::unique_ptr<FilterOperator>		m_current_filter;
	std::unique_ptr<AttributeOperator>	m_current_attr;
	std::unique_ptr<GroupOperator>		m_current_group;
	std::unique_ptr<AppendOperator>		m_current_append;
	std::unique_ptr<FuncOperator>		m_current_func;
	std::unique_ptr<VarDefOperator>		m_current_vardef;

	//====================== 编译上下文 ======================//

	detail::ScopeChain<Type>			m_type_scope;						// 变量类型作用域，局部变量、全局变量、函数参数
	RuleKind							m_current_kind = RuleKind::FILTER;	// 当前编译的规则类型
	CompiledProgram						m_program;							// 编译程序

	//====================== 子编译器 ======================//
	TreeExprCompiler					m_expr_compiler;
};

} // namespace postanvil
