
// Generated from PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, RULE = 2, RULEEND = 3, FILTER = 4, ATTR = 5, FUNC = 6, GROUP = 7, 
    APPEND = 8, FROM = 9, AND = 10, OR = 11, NOT = 12, SELF = 13, NUM = 14, 
    STR = 15, BOOL = 16, INST = 17, ANY = 18, RETURN = 19, IMPORT = 20, 
    EXPORT = 21, AS = 22, IF = 23, ELIF = 24, ELSE = 25, IFEND = 26, FOR = 27, 
    IN = 28, FOREND = 29, SORT = 30, ASC = 31, DESC = 32, BOOL_LIT = 33, 
    ARROW = 34, PLUS = 35, MINUS = 36, STAR = 37, SLASH = 38, LT = 39, GT = 40, 
    LE = 41, GE = 42, EQ = 43, NE = 44, DOT = 45, LPAREN = 46, RPAREN = 47, 
    COMMA = 48, ASSIGN = 49, NUMBER = 50, STRING = 51, IDENTIFIER = 52, 
    WS = 53, NEWLINE = 54, COMMENT = 55
  };

  enum {
    RuleProgram = 0, RuleNewlines = 1, RuleDeclaration = 2, RuleImportDef = 3, 
    RuleImportItem = 4, RuleExportDef = 5, RuleExportItem = 6, RuleGlobalDef = 7, 
    RuleType = 8, RuleRule_ = 9, RuleFilter_rule = 10, RuleAttr_rule = 11, 
    RuleAttr_def = 12, RuleAttr_lvalue = 13, RuleFunc_rule = 14, RuleTyped_params = 15, 
    RuleTyped_param = 16, RuleFunc_statement = 17, RuleIfStmt = 18, RuleElifBranch = 19, 
    RuleElseBranch = 20, RuleForStmt = 21, RuleGroup_rule = 22, RuleAppend_rule = 23, 
    RuleSort_rule = 24, RuleSort_key = 25, RuleDirection = 26, RuleClass_expr = 27, 
    RuleBool_expr = 28, RuleExpr = 29, RuleOr_expr = 30, RuleAnd_expr = 31, 
    RuleNot_expr = 32, RuleCmp_expr = 33, RuleAdd_expr = 34, RuleMul_expr = 35, 
    RuleUnary_expr = 36, RulePrimary = 37, RuleFunc_call = 38, RuleAttribute = 39, 
    RuleComp_op = 40, RuleAdd_op = 41, RuleMul_op = 42
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
  class NewlinesContext;
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
  class ElifBranchContext;
  class ElseBranchContext;
  class ForStmtContext;
  class Group_ruleContext;
  class Append_ruleContext;
  class Sort_ruleContext;
  class Sort_keyContext;
  class DirectionContext;
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  NewlinesContext : public antlr4::ParserRuleContext {
  public:
    NewlinesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NEWLINE();
    antlr4::tree::TerminalNode* NEWLINE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NewlinesContext* newlines();

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
    NewlinesContext *newlines();
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
    NewlinesContext *newlines();
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
    NewlinesContext *newlines();

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
    antlr4::tree::TerminalNode *INST();
    antlr4::tree::TerminalNode *ANY();

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
    Group_ruleContext *group_rule();
    Append_ruleContext *append_rule();
    Sort_ruleContext *sort_rule();
    Func_ruleContext *func_rule();

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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    antlr4::tree::TerminalNode *IFEND();
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);
    std::vector<ElifBranchContext *> elifBranch();
    ElifBranchContext* elifBranch(size_t i);
    ElseBranchContext *elseBranch();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IfStmtContext* ifStmt();

  class  ElifBranchContext : public antlr4::ParserRuleContext {
  public:
    ElifBranchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELIF();
    ExprContext *expr();
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElifBranchContext* elifBranch();

  class  ElseBranchContext : public antlr4::ParserRuleContext {
  public:
    ElseBranchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ELSE();
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    std::vector<Func_statementContext *> func_statement();
    Func_statementContext* func_statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ElseBranchContext* elseBranch();

  class  ForStmtContext : public antlr4::ParserRuleContext {
  public:
    ForStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *IN();
    Class_exprContext *class_expr();
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    antlr4::tree::TerminalNode *FOREND();
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
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
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Bool_exprContext *> bool_expr();
    Bool_exprContext* bool_expr(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Append_ruleContext* append_rule();

  class  Sort_ruleContext : public antlr4::ParserRuleContext {
  public:
    Sort_ruleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *SORT();
    Class_exprContext *class_expr();
    std::vector<NewlinesContext *> newlines();
    NewlinesContext* newlines(size_t i);
    antlr4::tree::TerminalNode *RULEEND();
    std::vector<Sort_keyContext *> sort_key();
    Sort_keyContext* sort_key(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sort_ruleContext* sort_rule();

  class  Sort_keyContext : public antlr4::ParserRuleContext {
  public:
    Sort_keyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    DirectionContext *direction();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Sort_keyContext* sort_key();

  class  DirectionContext : public antlr4::ParserRuleContext {
  public:
    DirectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DirectionContext* direction();

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
    antlr4::tree::TerminalNode *SELF();
    Func_callContext *func_call();
    AttributeContext *attribute();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
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

  class  AttributeContext : public antlr4::ParserRuleContext {
  public:
    AttributeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AttributeContext() = default;
    void copyFrom(AttributeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DynamicInstanceAttrContext : public AttributeContext {
  public:
    DynamicInstanceAttrContext(AttributeContext *ctx);

    antlr4::tree::TerminalNode *SELF();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  DynamicClassAttrContext : public AttributeContext {
  public:
    DynamicClassAttrContext(AttributeContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
  };

  class  DynamicVarAttrContext : public AttributeContext {
  public:
    DynamicVarAttrContext(AttributeContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
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

