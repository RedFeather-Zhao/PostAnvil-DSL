
// Generated from PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "PostAnvilListener.h"


/**
 * This class provides an empty implementation of PostAnvilListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  PostAnvilBaseListener : public PostAnvilListener {
public:

  virtual void enterProgram(PostAnvilParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(PostAnvilParser::ProgramContext * /*ctx*/) override { }

  virtual void enterNewlines(PostAnvilParser::NewlinesContext * /*ctx*/) override { }
  virtual void exitNewlines(PostAnvilParser::NewlinesContext * /*ctx*/) override { }

  virtual void enterDeclaration(PostAnvilParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(PostAnvilParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterImportDef(PostAnvilParser::ImportDefContext * /*ctx*/) override { }
  virtual void exitImportDef(PostAnvilParser::ImportDefContext * /*ctx*/) override { }

  virtual void enterImportItem(PostAnvilParser::ImportItemContext * /*ctx*/) override { }
  virtual void exitImportItem(PostAnvilParser::ImportItemContext * /*ctx*/) override { }

  virtual void enterExportDef(PostAnvilParser::ExportDefContext * /*ctx*/) override { }
  virtual void exitExportDef(PostAnvilParser::ExportDefContext * /*ctx*/) override { }

  virtual void enterExportItem(PostAnvilParser::ExportItemContext * /*ctx*/) override { }
  virtual void exitExportItem(PostAnvilParser::ExportItemContext * /*ctx*/) override { }

  virtual void enterGlobalDef(PostAnvilParser::GlobalDefContext * /*ctx*/) override { }
  virtual void exitGlobalDef(PostAnvilParser::GlobalDefContext * /*ctx*/) override { }

  virtual void enterType(PostAnvilParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(PostAnvilParser::TypeContext * /*ctx*/) override { }

  virtual void enterRule_(PostAnvilParser::Rule_Context * /*ctx*/) override { }
  virtual void exitRule_(PostAnvilParser::Rule_Context * /*ctx*/) override { }

  virtual void enterFilter_rule(PostAnvilParser::Filter_ruleContext * /*ctx*/) override { }
  virtual void exitFilter_rule(PostAnvilParser::Filter_ruleContext * /*ctx*/) override { }

  virtual void enterAttr_rule(PostAnvilParser::Attr_ruleContext * /*ctx*/) override { }
  virtual void exitAttr_rule(PostAnvilParser::Attr_ruleContext * /*ctx*/) override { }

  virtual void enterAttr_def(PostAnvilParser::Attr_defContext * /*ctx*/) override { }
  virtual void exitAttr_def(PostAnvilParser::Attr_defContext * /*ctx*/) override { }

  virtual void enterInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext * /*ctx*/) override { }
  virtual void exitInstanceAttrDef(PostAnvilParser::InstanceAttrDefContext * /*ctx*/) override { }

  virtual void enterClassAttrDef(PostAnvilParser::ClassAttrDefContext * /*ctx*/) override { }
  virtual void exitClassAttrDef(PostAnvilParser::ClassAttrDefContext * /*ctx*/) override { }

  virtual void enterFunc_rule(PostAnvilParser::Func_ruleContext * /*ctx*/) override { }
  virtual void exitFunc_rule(PostAnvilParser::Func_ruleContext * /*ctx*/) override { }

  virtual void enterTyped_params(PostAnvilParser::Typed_paramsContext * /*ctx*/) override { }
  virtual void exitTyped_params(PostAnvilParser::Typed_paramsContext * /*ctx*/) override { }

  virtual void enterTyped_param(PostAnvilParser::Typed_paramContext * /*ctx*/) override { }
  virtual void exitTyped_param(PostAnvilParser::Typed_paramContext * /*ctx*/) override { }

  virtual void enterFuncVarDef(PostAnvilParser::FuncVarDefContext * /*ctx*/) override { }
  virtual void exitFuncVarDef(PostAnvilParser::FuncVarDefContext * /*ctx*/) override { }

  virtual void enterFuncAssign(PostAnvilParser::FuncAssignContext * /*ctx*/) override { }
  virtual void exitFuncAssign(PostAnvilParser::FuncAssignContext * /*ctx*/) override { }

  virtual void enterFuncIfStmt(PostAnvilParser::FuncIfStmtContext * /*ctx*/) override { }
  virtual void exitFuncIfStmt(PostAnvilParser::FuncIfStmtContext * /*ctx*/) override { }

  virtual void enterFuncForStmt(PostAnvilParser::FuncForStmtContext * /*ctx*/) override { }
  virtual void exitFuncForStmt(PostAnvilParser::FuncForStmtContext * /*ctx*/) override { }

  virtual void enterFuncExprStmt(PostAnvilParser::FuncExprStmtContext * /*ctx*/) override { }
  virtual void exitFuncExprStmt(PostAnvilParser::FuncExprStmtContext * /*ctx*/) override { }

  virtual void enterFuncReturnStmt(PostAnvilParser::FuncReturnStmtContext * /*ctx*/) override { }
  virtual void exitFuncReturnStmt(PostAnvilParser::FuncReturnStmtContext * /*ctx*/) override { }

  virtual void enterIfStmt(PostAnvilParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(PostAnvilParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterElifBranch(PostAnvilParser::ElifBranchContext * /*ctx*/) override { }
  virtual void exitElifBranch(PostAnvilParser::ElifBranchContext * /*ctx*/) override { }

  virtual void enterElseBranch(PostAnvilParser::ElseBranchContext * /*ctx*/) override { }
  virtual void exitElseBranch(PostAnvilParser::ElseBranchContext * /*ctx*/) override { }

  virtual void enterForStmt(PostAnvilParser::ForStmtContext * /*ctx*/) override { }
  virtual void exitForStmt(PostAnvilParser::ForStmtContext * /*ctx*/) override { }

  virtual void enterGroup_rule(PostAnvilParser::Group_ruleContext * /*ctx*/) override { }
  virtual void exitGroup_rule(PostAnvilParser::Group_ruleContext * /*ctx*/) override { }

  virtual void enterAppend_rule(PostAnvilParser::Append_ruleContext * /*ctx*/) override { }
  virtual void exitAppend_rule(PostAnvilParser::Append_ruleContext * /*ctx*/) override { }

  virtual void enterSort_rule(PostAnvilParser::Sort_ruleContext * /*ctx*/) override { }
  virtual void exitSort_rule(PostAnvilParser::Sort_ruleContext * /*ctx*/) override { }

  virtual void enterSort_key(PostAnvilParser::Sort_keyContext * /*ctx*/) override { }
  virtual void exitSort_key(PostAnvilParser::Sort_keyContext * /*ctx*/) override { }

  virtual void enterDirection(PostAnvilParser::DirectionContext * /*ctx*/) override { }
  virtual void exitDirection(PostAnvilParser::DirectionContext * /*ctx*/) override { }

  virtual void enterClass_expr(PostAnvilParser::Class_exprContext * /*ctx*/) override { }
  virtual void exitClass_expr(PostAnvilParser::Class_exprContext * /*ctx*/) override { }

  virtual void enterBool_expr(PostAnvilParser::Bool_exprContext * /*ctx*/) override { }
  virtual void exitBool_expr(PostAnvilParser::Bool_exprContext * /*ctx*/) override { }

  virtual void enterExpr(PostAnvilParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(PostAnvilParser::ExprContext * /*ctx*/) override { }

  virtual void enterOr_expr(PostAnvilParser::Or_exprContext * /*ctx*/) override { }
  virtual void exitOr_expr(PostAnvilParser::Or_exprContext * /*ctx*/) override { }

  virtual void enterAnd_expr(PostAnvilParser::And_exprContext * /*ctx*/) override { }
  virtual void exitAnd_expr(PostAnvilParser::And_exprContext * /*ctx*/) override { }

  virtual void enterNot_expr(PostAnvilParser::Not_exprContext * /*ctx*/) override { }
  virtual void exitNot_expr(PostAnvilParser::Not_exprContext * /*ctx*/) override { }

  virtual void enterCmp_expr(PostAnvilParser::Cmp_exprContext * /*ctx*/) override { }
  virtual void exitCmp_expr(PostAnvilParser::Cmp_exprContext * /*ctx*/) override { }

  virtual void enterAdd_expr(PostAnvilParser::Add_exprContext * /*ctx*/) override { }
  virtual void exitAdd_expr(PostAnvilParser::Add_exprContext * /*ctx*/) override { }

  virtual void enterMul_expr(PostAnvilParser::Mul_exprContext * /*ctx*/) override { }
  virtual void exitMul_expr(PostAnvilParser::Mul_exprContext * /*ctx*/) override { }

  virtual void enterUnary_expr(PostAnvilParser::Unary_exprContext * /*ctx*/) override { }
  virtual void exitUnary_expr(PostAnvilParser::Unary_exprContext * /*ctx*/) override { }

  virtual void enterPrimary(PostAnvilParser::PrimaryContext * /*ctx*/) override { }
  virtual void exitPrimary(PostAnvilParser::PrimaryContext * /*ctx*/) override { }

  virtual void enterFunc_call(PostAnvilParser::Func_callContext * /*ctx*/) override { }
  virtual void exitFunc_call(PostAnvilParser::Func_callContext * /*ctx*/) override { }

  virtual void enterInstanceAttr(PostAnvilParser::InstanceAttrContext * /*ctx*/) override { }
  virtual void exitInstanceAttr(PostAnvilParser::InstanceAttrContext * /*ctx*/) override { }

  virtual void enterClassAttr(PostAnvilParser::ClassAttrContext * /*ctx*/) override { }
  virtual void exitClassAttr(PostAnvilParser::ClassAttrContext * /*ctx*/) override { }

  virtual void enterVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext * /*ctx*/) override { }
  virtual void exitVarInstanceAttr(PostAnvilParser::VarInstanceAttrContext * /*ctx*/) override { }

  virtual void enterDynamicInstanceAttr(PostAnvilParser::DynamicInstanceAttrContext * /*ctx*/) override { }
  virtual void exitDynamicInstanceAttr(PostAnvilParser::DynamicInstanceAttrContext * /*ctx*/) override { }

  virtual void enterDynamicClassAttr(PostAnvilParser::DynamicClassAttrContext * /*ctx*/) override { }
  virtual void exitDynamicClassAttr(PostAnvilParser::DynamicClassAttrContext * /*ctx*/) override { }

  virtual void enterDynamicVarAttr(PostAnvilParser::DynamicVarAttrContext * /*ctx*/) override { }
  virtual void exitDynamicVarAttr(PostAnvilParser::DynamicVarAttrContext * /*ctx*/) override { }

  virtual void enterComp_op(PostAnvilParser::Comp_opContext * /*ctx*/) override { }
  virtual void exitComp_op(PostAnvilParser::Comp_opContext * /*ctx*/) override { }

  virtual void enterAdd_op(PostAnvilParser::Add_opContext * /*ctx*/) override { }
  virtual void exitAdd_op(PostAnvilParser::Add_opContext * /*ctx*/) override { }

  virtual void enterMul_op(PostAnvilParser::Mul_opContext * /*ctx*/) override { }
  virtual void exitMul_op(PostAnvilParser::Mul_opContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

