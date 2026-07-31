
// Generated from D:/UserProject/vsstudio/PostAnvil DSL/PostAnvil DSL/docs/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PostAnvilVisitor.h"


/**
 * This class provides an empty implementation of PostAnvilVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  PostAnvilBaseVisitor : public PostAnvilVisitor {
public:

  virtual std::any visitProgram(PostAnvilParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(PostAnvilParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportDef(PostAnvilParser::ImportDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportItem(PostAnvilParser::ImportItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportDef(PostAnvilParser::ExportDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExportItem(PostAnvilParser::ExportItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGlobalDef(PostAnvilParser::GlobalDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(PostAnvilParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRule_(PostAnvilParser::Rule_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter_rule(PostAnvilParser::Filter_ruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttr_rule(PostAnvilParser::Attr_ruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAttr_def(PostAnvilParser::Attr_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassAttrDef(PostAnvilParser::ClassAttrDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_rule(PostAnvilParser::Func_ruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTyped_params(PostAnvilParser::Typed_paramsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTyped_param(PostAnvilParser::Typed_paramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncVarDef(PostAnvilParser::FuncVarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncAssign(PostAnvilParser::FuncAssignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncIfStmt(PostAnvilParser::FuncIfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncForStmt(PostAnvilParser::FuncForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncExprStmt(PostAnvilParser::FuncExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncReturnStmt(PostAnvilParser::FuncReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(PostAnvilParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStmt(PostAnvilParser::ForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroup_rule(PostAnvilParser::Group_ruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAppend_rule(PostAnvilParser::Append_ruleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClass_expr(PostAnvilParser::Class_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBool_expr(PostAnvilParser::Bool_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(PostAnvilParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOr_expr(PostAnvilParser::Or_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnd_expr(PostAnvilParser::And_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot_expr(PostAnvilParser::Not_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCmp_expr(PostAnvilParser::Cmp_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdd_expr(PostAnvilParser::Add_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMul_expr(PostAnvilParser::Mul_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnary_expr(PostAnvilParser::Unary_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimary(PostAnvilParser::PrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc_call(PostAnvilParser::Func_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSortExpr(PostAnvilParser::SortExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInstanceAttr(PostAnvilParser::InstanceAttrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClassAttr(PostAnvilParser::ClassAttrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComp_op(PostAnvilParser::Comp_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdd_op(PostAnvilParser::Add_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMul_op(PostAnvilParser::Mul_opContext *ctx) override {
    return visitChildren(ctx);
  }


};

