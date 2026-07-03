
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

  virtual void enterRuledef(PostAnvilParser::RuledefContext * /*ctx*/) override { }
  virtual void exitRuledef(PostAnvilParser::RuledefContext * /*ctx*/) override { }

  virtual void enterExprStmt(PostAnvilParser::ExprStmtContext * /*ctx*/) override { }
  virtual void exitExprStmt(PostAnvilParser::ExprStmtContext * /*ctx*/) override { }

  virtual void enterAssignStmt(PostAnvilParser::AssignStmtContext * /*ctx*/) override { }
  virtual void exitAssignStmt(PostAnvilParser::AssignStmtContext * /*ctx*/) override { }

  virtual void enterAttr_assign(PostAnvilParser::Attr_assignContext * /*ctx*/) override { }
  virtual void exitAttr_assign(PostAnvilParser::Attr_assignContext * /*ctx*/) override { }

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

  virtual void enterAttribute(PostAnvilParser::AttributeContext * /*ctx*/) override { }
  virtual void exitAttribute(PostAnvilParser::AttributeContext * /*ctx*/) override { }

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

