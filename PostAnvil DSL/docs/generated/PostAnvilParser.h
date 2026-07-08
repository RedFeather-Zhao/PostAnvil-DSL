
// Generated from PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, RULE = 2, RULEEND = 3, FILTER = 4, ATTR = 5, FUNC = 6, GROUP = 7, 
    APPEND = 8, FROM = 9, AND = 10, OR = 11, NOT = 12, SELF = 13, NUM = 14, 
    STR = 15, BOOL = 16, RETURN = 17, IMPORT = 18, EXPORT = 19, AS = 20, 
    IF = 21, ELSE = 22, ENDIF = 23, FOR = 24, IN = 25, ENDFOR = 26, SORT = 27, 
    BOOL_LIT = 28, ARROW = 29, PLUS = 30, MINUS = 31, STAR = 32, SLASH = 33, 
    LT = 34, GT = 35, LE = 36, GE = 37, EQ = 38, NE = 39, DOT = 40, LPAREN = 41, 
    RPAREN = 42, COMMA = 43, ASSIGN = 44, NUMBER = 45, STRING = 46, IDENTIFIER = 47, 
    WS = 48, NEWLINE = 49, COMMENT = 50
  };

  enum {
    RuleProgram = 0, RuleDeclaration = 1, RuleImportDef = 2, RuleImportItem = 3, 
    RuleExportDef = 4, RuleExportItem = 5, RuleGlobalDef = 6, RuleType = 7, 
    RuleRule_ = 8, RuleFilter_rule = 9, RuleAttr_rule = 10, RuleAttr_def = 11, 
    RuleAttr_lvalue = 12, RuleFunc_rule = 13, RuleTyped_params = 14, RuleTyped_param = 15, 
    RuleFunc_statement = 16, RuleIfStmt = 17, RuleForStmt = 18, RuleGroup_rule = 19, 
    RuleAppend_rule = 20, RuleClass_expr = 21, RuleBool_expr = 22, RuleExpr = 23, 
    RuleOr_expr = 24, RuleAnd_expr = 25, RuleNot_expr = 26, RuleCmp_expr = 27, 
    RuleAdd_expr = 28, RuleMul_expr = 29, RuleUnary_expr = 30, RulePrimary = 31, 
    RuleFunc_call = 32, RuleSortExpr = 33, RuleAttribute = 34, RuleComp_op = 35, 
    RuleAdd_op = 36, RuleMul_op = 37
  };

  explicit PostAnvilParser(antlr4::TokenStream *input);

  PostAnvilParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~PostAnvilParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class DeclarationContext;
  class ImportDefContext;
  class ImportItemContext;
  class ExportDefContext;
  class ExportItemContext;
  class GlobalDefContext;
  class TypeContext;
  class Rule_Context;
  class Filter_ruleContext;
  class Attr_ruleContext;
  class Attr_defContext;
  class Attr_lvalueContext;
  class Func_ruleContext;
  class Typed_paramsContext;
  class Typed_paramContext;
  class Func_statementContext;
  class IfStmtContext;
  class ForStmtContext;
  class Group_ruleContext;
  class Append_ruleContext;
  class Class_exprContext;
  class Bool_exprContext;
  class ExprContext;
  class Or_exprContext;
  class And_exprContext;
  class Not_exprContext;
  class Cmp_exprContext;
  class Add_exprContext;
  class Mul_exprContext;
  class Unary_exprContext;
  class PrimaryContext;
  class Func_callContext;
  class SortExprContext;
  class AttributeContext;
  class Comp_opContext;
  class Add_opContext;
  class Mul_opContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<Rule_Context *> rule_();
    Rule_Context* rule_(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportDefContext *importDef();
    ExportDefContext *exportDef();
    GlobalDefContext *globalDef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationContext* declaration();

  class  ImportDefContext : public antlr4::ParserRuleContext {
  public:
    ImportDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    std::vector<ImportItemContext *> importItem();
    ImportItemContext* importItem(size_t i);
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportDefContext* importDef();

  class  ImportItemContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *host = nullptr;
    antlr4::Token *local = nullptr;
    ImportItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ImportItemContext* importItem();

  class  ExportDefContext : public antlr4::ParserRuleContext {
  public:
    ExportDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXPORT();
    std::vector<ExportItemContext *> exportItem();
    ExportItemContext* exportItem(size_t i);
    antlr4::tree::TerminalNode *NEWLINE();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportDefContext* exportDef();

  class  ExportItemContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *host = nullptr;
    ExportItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExportItemContext* exportItem();

  class  GlobalDefContext : public antlr4::ParserRuleContext {
  public:
    GlobalDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GlobalDefContext* globalDef();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUM();
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *BOOL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TypeContext* type();

  class  Rule_Context : public antlr4::ParserRuleContext {
  public:
    Rule_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Filter_ruleContext *filter_rule();
    Attr_ruleContext *attr_rule();
    Func_ruleContext *func_rule();
    Group_ruleContext *group_rule();
    Append_ruleContext *append_rule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Rule_Context* rule_();

  class  Filter_ruleContext : public antlr4::ParserRuleContext {
  public:
    Filter_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *FILTER();
    Class_exprContext *class_expr();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Bool_exprContext *> bool_expr();
    Bool_exprContext* bool_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Filter_ruleContext* filter_rule();

  class  Attr_ruleContext : public antlr4::ParserRuleContext {
  public:
    Attr_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *ATTR();
    Class_exprContext *class_expr();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Attr_defContext *> attr_def();
    Attr_defContext* attr_def(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Attr_ruleContext* attr_rule();

  class  Attr_defContext : public antlr4::ParserRuleContext {
  public:
    Attr_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Attr_lvalueContext *attr_lvalue();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Attr_defContext* attr_def();

  class  Attr_lvalueContext : public antlr4::ParserRuleContext {
  public:
    Attr_lvalueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Attr_lvalueContext() = default;
    void copyFrom(Attr_lvalueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InstanceAttrDefContext : public Attr_lvalueContext {
  public:
    InstanceAttrDefContext(Attr_lvalueContext *ctx);

    antlr4::tree::TerminalNode *SELF();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ClassAttrDefContext : public Attr_lvalueContext {
  public:
    ClassAttrDefContext(Attr_lvalueContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  Attr_lvalueContext* attr_lvalue();

  class  Func_ruleContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *name = nullptr;
    PostAnvilParser::TypeContext *return_type = nullptr;
    Func_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *FUNC();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    antlr4::tree::TerminalNode *IDENTIFIER();
    Typed_paramsContext *typed_params();
    antlr4::tree::TerminalNode *ARROW();
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Func_ruleContext* func_rule();

  class  Typed_paramsContext : public antlr4::ParserRuleContext {
  public:
    Typed_paramsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Typed_paramContext *> typed_param();
    Typed_paramContext* typed_param(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Typed_paramsContext* typed_params();

  class  Typed_paramContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *param_name = nullptr;
    PostAnvilParser::TypeContext *param_type = nullptr;
    Typed_paramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Typed_paramContext* typed_param();

  class  Func_statementContext : public antlr4::ParserRuleContext {
  public:
    Func_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Func_statementContext() = default;
    void copyFrom(Func_statementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FuncVarDefContext : public Func_statementContext {
  public:
    FuncVarDefContext(Func_statementContext *ctx);

    TypeContext *type();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FuncIfStmtContext : public Func_statementContext {
  public:
    FuncIfStmtContext(Func_statementContext *ctx);

    IfStmtContext *ifStmt();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FuncAssignContext : public Func_statementContext {
  public:
    FuncAssignContext(Func_statementContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FuncExprStmtContext : public Func_statementContext {
  public:
    FuncExprStmtContext(Func_statementContext *ctx);

    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FuncForStmtContext : public Func_statementContext {
  public:
    FuncForStmtContext(Func_statementContext *ctx);

    ForStmtContext *forStmt();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  FuncReturnStmtContext : public Func_statementContext {
  public:
    FuncReturnStmtContext(Func_statementContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  Func_statementContext* func_statement();

  class  IfStmtContext : public antlr4::ParserRuleContext {
  public:
    IfStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *ENDIF();
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStmtContext* ifStmt();

  class  ForStmtContext : public antlr4::ParserRuleContext {
  public:
    ForStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN();
    Class_exprContext *class_expr();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *ENDFOR();
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ForStmtContext* forStmt();

  class  Group_ruleContext : public antlr4::ParserRuleContext {
  public:
    Group_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *GROUP();
    std::vector<Class_exprContext *> class_expr();
    Class_exprContext* class_expr(size_t i);
    antlr4::tree::TerminalNode *FROM();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Bool_exprContext *> bool_expr();
    Bool_exprContext* bool_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Group_ruleContext* group_rule();

  class  Append_ruleContext : public antlr4::ParserRuleContext {
  public:
    Append_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *APPEND();
    std::vector<Class_exprContext *> class_expr();
    Class_exprContext* class_expr(size_t i);
    antlr4::tree::TerminalNode *FROM();
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Bool_exprContext *> bool_expr();
    Bool_exprContext* bool_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Append_ruleContext* append_rule();

  class  Class_exprContext : public antlr4::ParserRuleContext {
  public:
    Class_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Class_exprContext* class_expr();

  class  Bool_exprContext : public antlr4::ParserRuleContext {
  public:
    Bool_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Or_exprContext *or_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bool_exprContext* bool_expr();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Or_exprContext *or_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();

  class  Or_exprContext : public antlr4::ParserRuleContext {
  public:
    Or_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<And_exprContext *> and_expr();
    And_exprContext* and_expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Or_exprContext* or_expr();

  class  And_exprContext : public antlr4::ParserRuleContext {
  public:
    And_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Not_exprContext *> not_expr();
    Not_exprContext* not_expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  And_exprContext* and_expr();

  class  Not_exprContext : public antlr4::ParserRuleContext {
  public:
    Not_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    Not_exprContext *not_expr();
    Cmp_exprContext *cmp_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Not_exprContext* not_expr();

  class  Cmp_exprContext : public antlr4::ParserRuleContext {
  public:
    Cmp_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Add_exprContext *> add_expr();
    Add_exprContext* add_expr(size_t i);
    Comp_opContext *comp_op();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Cmp_exprContext* cmp_expr();

  class  Add_exprContext : public antlr4::ParserRuleContext {
  public:
    Add_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mul_exprContext *> mul_expr();
    Mul_exprContext* mul_expr(size_t i);
    std::vector<Add_opContext *> add_op();
    Add_opContext* add_op(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Add_exprContext* add_expr();

  class  Mul_exprContext : public antlr4::ParserRuleContext {
  public:
    Mul_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Unary_exprContext *> unary_expr();
    Unary_exprContext* unary_expr(size_t i);
    std::vector<Mul_opContext *> mul_op();
    Mul_opContext* mul_op(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Mul_exprContext* mul_expr();

  class  Unary_exprContext : public antlr4::ParserRuleContext {
  public:
    Unary_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MINUS();
    Unary_exprContext *unary_expr();
    PrimaryContext *primary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Unary_exprContext* unary_expr();

  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NUMBER();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *BOOL_LIT();
    Func_callContext *func_call();
    AttributeContext *attribute();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    SortExprContext *sortExpr();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryContext* primary();

  class  Func_callContext : public antlr4::ParserRuleContext {
  public:
    Func_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Func_callContext* func_call();

  class  SortExprContext : public antlr4::ParserRuleContext {
  public:
    SortExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SORT();
    antlr4::tree::TerminalNode *LPAREN();
    Class_exprContext *class_expr();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SortExprContext* sortExpr();

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AttributeContext() = default;
    void copyFrom(AttributeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  InstanceAttrContext : public AttributeContext {
  public:
    InstanceAttrContext(AttributeContext *ctx);

    antlr4::tree::TerminalNode *SELF();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  ClassAttrContext : public AttributeContext {
  public:
    ClassAttrContext(AttributeContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *IDENTIFIER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  VarInstanceAttrContext : public AttributeContext {
  public:
    VarInstanceAttrContext(AttributeContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *DOT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  AttributeContext* attribute();

  class  Comp_opContext : public antlr4::ParserRuleContext {
  public:
    Comp_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Comp_opContext* comp_op();

  class  Add_opContext : public antlr4::ParserRuleContext {
  public:
    Add_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Add_opContext* add_op();

  class  Mul_opContext : public antlr4::ParserRuleContext {
  public:
    Mul_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Mul_opContext* mul_op();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

