
// Generated from grammar/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PostAnvilParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by PostAnvilParser.
 */
class  PostAnvilListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(PostAnvilParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(PostAnvilParser::ProgramContext *ctx) = 0;

  virtual void enterNewlines(PostAnvilParser::NewlinesContext *ctx) = 0;
  virtual void exitNewlines(PostAnvilParser::NewlinesContext *ctx) = 0;

  virtual void enterDeclaration(PostAnvilParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(PostAnvilParser::DeclarationContext *ctx) = 0;

  virtual void enterImportDef(PostAnvilParser::ImportDefContext *ctx) = 0;
  virtual void exitImportDef(PostAnvilParser::ImportDefContext *ctx) = 0;

  virtual void enterImportItem(PostAnvilParser::ImportItemContext *ctx) = 0;
  virtual void exitImportItem(PostAnvilParser::ImportItemContext *ctx) = 0;

  virtual void enterExportDef(PostAnvilParser::ExportDefContext *ctx) = 0;
  virtual void exitExportDef(PostAnvilParser::ExportDefContext *ctx) = 0;

  virtual void enterExportItem(PostAnvilParser::ExportItemContext *ctx) = 0;
  virtual void exitExportItem(PostAnvilParser::ExportItemContext *ctx) = 0;

  virtual void enterGlobalDef(PostAnvilParser::GlobalDefContext *ctx) = 0;
  virtual void exitGlobalDef(PostAnvilParser::GlobalDefContext *ctx) = 0;

  virtual void enterType(PostAnvilParser::TypeContext *ctx) = 0;
  virtual void exitType(PostAnvilParser::TypeContext *ctx) = 0;

  virtual void enterCondition_block(PostAnvilParser::Condition_blockContext *ctx) = 0;
  virtual void exitCondition_block(PostAnvilParser::Condition_blockContext *ctx) = 0;

  virtual void enterAttr_block(PostAnvilParser::Attr_blockContext *ctx) = 0;
  virtual void exitAttr_block(PostAnvilParser::Attr_blockContext *ctx) = 0;

  virtual void enterSort_block(PostAnvilParser::Sort_blockContext *ctx) = 0;
  virtual void exitSort_block(PostAnvilParser::Sort_blockContext *ctx) = 0;

  virtual void enterStmt_block(PostAnvilParser::Stmt_blockContext *ctx) = 0;
  virtual void exitStmt_block(PostAnvilParser::Stmt_blockContext *ctx) = 0;

  virtual void enterRule_(PostAnvilParser::Rule_Context *ctx) = 0;
  virtual void exitRule_(PostAnvilParser::Rule_Context *ctx) = 0;

  virtual void enterFilter_rule(PostAnvilParser::Filter_ruleContext *ctx) = 0;
  virtual void exitFilter_rule(PostAnvilParser::Filter_ruleContext *ctx) = 0;

  virtual void enterAttr_rule(PostAnvilParser::Attr_ruleContext *ctx) = 0;
  virtual void exitAttr_rule(PostAnvilParser::Attr_ruleContext *ctx) = 0;

  virtual void enterGroup_rule(PostAnvilParser::Group_ruleContext *ctx) = 0;
  virtual void exitGroup_rule(PostAnvilParser::Group_ruleContext *ctx) = 0;

  virtual void enterAppend_rule(PostAnvilParser::Append_ruleContext *ctx) = 0;
  virtual void exitAppend_rule(PostAnvilParser::Append_ruleContext *ctx) = 0;

  virtual void enterSort_rule(PostAnvilParser::Sort_ruleContext *ctx) = 0;
  virtual void exitSort_rule(PostAnvilParser::Sort_ruleContext *ctx) = 0;

  virtual void enterFunc_rule(PostAnvilParser::Func_ruleContext *ctx) = 0;
  virtual void exitFunc_rule(PostAnvilParser::Func_ruleContext *ctx) = 0;

  virtual void enterAttr_def(PostAnvilParser::Attr_defContext *ctx) = 0;
  virtual void exitAttr_def(PostAnvilParser::Attr_defContext *ctx) = 0;

  virtual void enterInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext *ctx) = 0;
  virtual void exitInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext *ctx) = 0;

  virtual void enterClassAttrDef(PostAnvilParser::ClassAttrDefContext *ctx) = 0;
  virtual void exitClassAttrDef(PostAnvilParser::ClassAttrDefContext *ctx) = 0;

  virtual void enterTyped_params(PostAnvilParser::Typed_paramsContext *ctx) = 0;
  virtual void exitTyped_params(PostAnvilParser::Typed_paramsContext *ctx) = 0;

  virtual void enterTyped_param(PostAnvilParser::Typed_paramContext *ctx) = 0;
  virtual void exitTyped_param(PostAnvilParser::Typed_paramContext *ctx) = 0;

  virtual void enterStmtVarDef(PostAnvilParser::StmtVarDefContext *ctx) = 0;
  virtual void exitStmtVarDef(PostAnvilParser::StmtVarDefContext *ctx) = 0;

  virtual void enterStmtAssign(PostAnvilParser::StmtAssignContext *ctx) = 0;
  virtual void exitStmtAssign(PostAnvilParser::StmtAssignContext *ctx) = 0;

  virtual void enterStmtIf(PostAnvilParser::StmtIfContext *ctx) = 0;
  virtual void exitStmtIf(PostAnvilParser::StmtIfContext *ctx) = 0;

  virtual void enterStmtFor(PostAnvilParser::StmtForContext *ctx) = 0;
  virtual void exitStmtFor(PostAnvilParser::StmtForContext *ctx) = 0;

  virtual void enterStmtExpr(PostAnvilParser::StmtExprContext *ctx) = 0;
  virtual void exitStmtExpr(PostAnvilParser::StmtExprContext *ctx) = 0;

  virtual void enterStmtReturn(PostAnvilParser::StmtReturnContext *ctx) = 0;
  virtual void exitStmtReturn(PostAnvilParser::StmtReturnContext *ctx) = 0;

  virtual void enterIfStmt(PostAnvilParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(PostAnvilParser::IfStmtContext *ctx) = 0;

  virtual void enterIfBranch(PostAnvilParser::IfBranchContext *ctx) = 0;
  virtual void exitIfBranch(PostAnvilParser::IfBranchContext *ctx) = 0;

  virtual void enterElifBranch(PostAnvilParser::ElifBranchContext *ctx) = 0;
  virtual void exitElifBranch(PostAnvilParser::ElifBranchContext *ctx) = 0;

  virtual void enterElseBranch(PostAnvilParser::ElseBranchContext *ctx) = 0;
  virtual void exitElseBranch(PostAnvilParser::ElseBranchContext *ctx) = 0;

  virtual void enterForStmt(PostAnvilParser::ForStmtContext *ctx) = 0;
  virtual void exitForStmt(PostAnvilParser::ForStmtContext *ctx) = 0;

  virtual void enterSort_key(PostAnvilParser::Sort_keyContext *ctx) = 0;
  virtual void exitSort_key(PostAnvilParser::Sort_keyContext *ctx) = 0;

  virtual void enterDirection(PostAnvilParser::DirectionContext *ctx) = 0;
  virtual void exitDirection(PostAnvilParser::DirectionContext *ctx) = 0;

  virtual void enterClass_expr(PostAnvilParser::Class_exprContext *ctx) = 0;
  virtual void exitClass_expr(PostAnvilParser::Class_exprContext *ctx) = 0;

  virtual void enterClass_selector(PostAnvilParser::Class_selectorContext *ctx) = 0;
  virtual void exitClass_selector(PostAnvilParser::Class_selectorContext *ctx) = 0;

  virtual void enterClass_group(PostAnvilParser::Class_groupContext *ctx) = 0;
  virtual void exitClass_group(PostAnvilParser::Class_groupContext *ctx) = 0;

  virtual void enterFor_source(PostAnvilParser::For_sourceContext *ctx) = 0;
  virtual void exitFor_source(PostAnvilParser::For_sourceContext *ctx) = 0;

  virtual void enterBool_expr(PostAnvilParser::Bool_exprContext *ctx) = 0;
  virtual void exitBool_expr(PostAnvilParser::Bool_exprContext *ctx) = 0;

  virtual void enterExpr(PostAnvilParser::ExprContext *ctx) = 0;
  virtual void exitExpr(PostAnvilParser::ExprContext *ctx) = 0;

  virtual void enterOr_expr(PostAnvilParser::Or_exprContext *ctx) = 0;
  virtual void exitOr_expr(PostAnvilParser::Or_exprContext *ctx) = 0;

  virtual void enterAnd_expr(PostAnvilParser::And_exprContext *ctx) = 0;
  virtual void exitAnd_expr(PostAnvilParser::And_exprContext *ctx) = 0;

  virtual void enterNot_expr(PostAnvilParser::Not_exprContext *ctx) = 0;
  virtual void exitNot_expr(PostAnvilParser::Not_exprContext *ctx) = 0;

  virtual void enterCmp_expr(PostAnvilParser::Cmp_exprContext *ctx) = 0;
  virtual void exitCmp_expr(PostAnvilParser::Cmp_exprContext *ctx) = 0;

  virtual void enterAdd_expr(PostAnvilParser::Add_exprContext *ctx) = 0;
  virtual void exitAdd_expr(PostAnvilParser::Add_exprContext *ctx) = 0;

  virtual void enterMul_expr(PostAnvilParser::Mul_exprContext *ctx) = 0;
  virtual void exitMul_expr(PostAnvilParser::Mul_exprContext *ctx) = 0;

  virtual void enterUnary_expr(PostAnvilParser::Unary_exprContext *ctx) = 0;
  virtual void exitUnary_expr(PostAnvilParser::Unary_exprContext *ctx) = 0;

  virtual void enterPrimary(PostAnvilParser::PrimaryContext *ctx) = 0;
  virtual void exitPrimary(PostAnvilParser::PrimaryContext *ctx) = 0;

  virtual void enterFunc_call(PostAnvilParser::Func_callContext *ctx) = 0;
  virtual void exitFunc_call(PostAnvilParser::Func_callContext *ctx) = 0;

  virtual void enterInstanceAttr(PostAnvilParser::InstanceAttrContext *ctx) = 0;
  virtual void exitInstanceAttr(PostAnvilParser::InstanceAttrContext *ctx) = 0;

  virtual void enterClassAttr(PostAnvilParser::ClassAttrContext *ctx) = 0;
  virtual void exitClassAttr(PostAnvilParser::ClassAttrContext *ctx) = 0;

  virtual void enterVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext *ctx) = 0;
  virtual void exitVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext *ctx) = 0;

  virtual void enterDynamicInstanceAttr(PostAnvilParser::DynamicInstanceAttrContext *ctx) = 0;
  virtual void exitDynamicInstanceAttr(PostAnvilParser::DynamicInstanceAttrContext *ctx) = 0;

  virtual void enterDynamicClassAttr(PostAnvilParser::DynamicClassAttrContext *ctx) = 0;
  virtual void exitDynamicClassAttr(PostAnvilParser::DynamicClassAttrContext *ctx) = 0;

  virtual void enterDynamicVarAttr(PostAnvilParser::DynamicVarAttrContext *ctx) = 0;
  virtual void exitDynamicVarAttr(PostAnvilParser::DynamicVarAttrContext *ctx) = 0;

  virtual void enterComp_op(PostAnvilParser::Comp_opContext *ctx) = 0;
  virtual void exitComp_op(PostAnvilParser::Comp_opContext *ctx) = 0;

  virtual void enterAdd_op(PostAnvilParser::Add_opContext *ctx) = 0;
  virtual void exitAdd_op(PostAnvilParser::Add_opContext *ctx) = 0;

  virtual void enterMul_op(PostAnvilParser::Mul_opContext *ctx) = 0;
  virtual void exitMul_op(PostAnvilParser::Mul_opContext *ctx) = 0;


};

