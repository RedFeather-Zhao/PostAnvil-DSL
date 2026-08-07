
// Generated from D:/UserProject/vsstudio/PostAnvil DSL/grammar/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PostAnvilParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by PostAnvilParser.
 */
class  PostAnvilVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by PostAnvilParser.
   */
    virtual std::any visitProgram(PostAnvilParser::ProgramContext *context) = 0;

    virtual std::any visitNewlines(PostAnvilParser::NewlinesContext *context) = 0;

    virtual std::any visitDeclaration(PostAnvilParser::DeclarationContext *context) = 0;

    virtual std::any visitImportDef(PostAnvilParser::ImportDefContext *context) = 0;

    virtual std::any visitImportItem(PostAnvilParser::ImportItemContext *context) = 0;

    virtual std::any visitExportDef(PostAnvilParser::ExportDefContext *context) = 0;

    virtual std::any visitExportItem(PostAnvilParser::ExportItemContext *context) = 0;

    virtual std::any visitGlobalDef(PostAnvilParser::GlobalDefContext *context) = 0;

    virtual std::any visitType(PostAnvilParser::TypeContext *context) = 0;

    virtual std::any visitRule_(PostAnvilParser::Rule_Context *context) = 0;

    virtual std::any visitFilter_rule(PostAnvilParser::Filter_ruleContext *context) = 0;

    virtual std::any visitAttr_rule(PostAnvilParser::Attr_ruleContext *context) = 0;

    virtual std::any visitAttr_def(PostAnvilParser::Attr_defContext *context) = 0;

    virtual std::any visitInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext *context) = 0;

    virtual std::any visitClassAttrDef(PostAnvilParser::ClassAttrDefContext *context) = 0;

    virtual std::any visitFunc_rule(PostAnvilParser::Func_ruleContext *context) = 0;

    virtual std::any visitTyped_params(PostAnvilParser::Typed_paramsContext *context) = 0;

    virtual std::any visitTyped_param(PostAnvilParser::Typed_paramContext *context) = 0;

    virtual std::any visitFuncVarDef(PostAnvilParser::FuncVarDefContext *context) = 0;

    virtual std::any visitFuncAssign(PostAnvilParser::FuncAssignContext *context) = 0;

    virtual std::any visitFuncIfStmt(PostAnvilParser::FuncIfStmtContext *context) = 0;

    virtual std::any visitFuncForStmt(PostAnvilParser::FuncForStmtContext *context) = 0;

    virtual std::any visitFuncExprStmt(PostAnvilParser::FuncExprStmtContext *context) = 0;

    virtual std::any visitFuncReturnStmt(PostAnvilParser::FuncReturnStmtContext *context) = 0;

    virtual std::any visitIfStmt(PostAnvilParser::IfStmtContext *context) = 0;

    virtual std::any visitElifBranch(PostAnvilParser::ElifBranchContext *context) = 0;

    virtual std::any visitElseBranch(PostAnvilParser::ElseBranchContext *context) = 0;

    virtual std::any visitForStmt(PostAnvilParser::ForStmtContext *context) = 0;

    virtual std::any visitGroup_rule(PostAnvilParser::Group_ruleContext *context) = 0;

    virtual std::any visitAppend_rule(PostAnvilParser::Append_ruleContext *context) = 0;

    virtual std::any visitSort_rule(PostAnvilParser::Sort_ruleContext *context) = 0;

    virtual std::any visitSort_key(PostAnvilParser::Sort_keyContext *context) = 0;

    virtual std::any visitDirection(PostAnvilParser::DirectionContext *context) = 0;

    virtual std::any visitClass_expr(PostAnvilParser::Class_exprContext *context) = 0;

    virtual std::any visitBool_expr(PostAnvilParser::Bool_exprContext *context) = 0;

    virtual std::any visitExpr(PostAnvilParser::ExprContext *context) = 0;

    virtual std::any visitOr_expr(PostAnvilParser::Or_exprContext *context) = 0;

    virtual std::any visitAnd_expr(PostAnvilParser::And_exprContext *context) = 0;

    virtual std::any visitNot_expr(PostAnvilParser::Not_exprContext *context) = 0;

    virtual std::any visitCmp_expr(PostAnvilParser::Cmp_exprContext *context) = 0;

    virtual std::any visitAdd_expr(PostAnvilParser::Add_exprContext *context) = 0;

    virtual std::any visitMul_expr(PostAnvilParser::Mul_exprContext *context) = 0;

    virtual std::any visitUnary_expr(PostAnvilParser::Unary_exprContext *context) = 0;

    virtual std::any visitPrimary(PostAnvilParser::PrimaryContext *context) = 0;

    virtual std::any visitFunc_call(PostAnvilParser::Func_callContext *context) = 0;

    virtual std::any visitInstanceAttr(PostAnvilParser::InstanceAttrContext *context) = 0;

    virtual std::any visitClassAttr(PostAnvilParser::ClassAttrContext *context) = 0;

    virtual std::any visitVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext *context) = 0;

    virtual std::any visitDynamicInstanceAttr(PostAnvilParser::DynamicInstanceAttrContext *context) = 0;

    virtual std::any visitDynamicClassAttr(PostAnvilParser::DynamicClassAttrContext *context) = 0;

    virtual std::any visitDynamicVarAttr(PostAnvilParser::DynamicVarAttrContext *context) = 0;

    virtual std::any visitComp_op(PostAnvilParser::Comp_opContext *context) = 0;

    virtual std::any visitAdd_op(PostAnvilParser::Add_opContext *context) = 0;

    virtual std::any visitMul_op(PostAnvilParser::Mul_opContext *context) = 0;


};

