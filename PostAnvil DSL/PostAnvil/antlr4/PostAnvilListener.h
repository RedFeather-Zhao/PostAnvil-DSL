
// Generated from PostAnvil.g4 by ANTLR 4.13.2

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

  virtual void enterRuledef(PostAnvilParser::RuledefContext *ctx) = 0;
  virtual void exitRuledef(PostAnvilParser::RuledefContext *ctx) = 0;

  virtual void enterExprStmt(PostAnvilParser::ExprStmtContext *ctx) = 0;
  virtual void exitExprStmt(PostAnvilParser::ExprStmtContext *ctx) = 0;

  virtual void enterAssignStmt(PostAnvilParser::AssignStmtContext *ctx) = 0;
  virtual void exitAssignStmt(PostAnvilParser::AssignStmtContext *ctx) = 0;

  virtual void enterAttr_assign(PostAnvilParser::Attr_assignContext *ctx) = 0;
  virtual void exitAttr_assign(PostAnvilParser::Attr_assignContext *ctx) = 0;

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

  virtual void enterAttribute(PostAnvilParser::AttributeContext *ctx) = 0;
  virtual void exitAttribute(PostAnvilParser::AttributeContext *ctx) = 0;

  virtual void enterComp_op(PostAnvilParser::Comp_opContext *ctx) = 0;
  virtual void exitComp_op(PostAnvilParser::Comp_opContext *ctx) = 0;

  virtual void enterAdd_op(PostAnvilParser::Add_opContext *ctx) = 0;
  virtual void exitAdd_op(PostAnvilParser::Add_opContext *ctx) = 0;

  virtual void enterMul_op(PostAnvilParser::Mul_opContext *ctx) = 0;
  virtual void exitMul_op(PostAnvilParser::Mul_opContext *ctx) = 0;


};

