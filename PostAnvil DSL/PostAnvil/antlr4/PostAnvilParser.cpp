
// Generated from PostAnvil.g4 by ANTLR 4.13.2


#include "PostAnvilListener.h"

#include "PostAnvilParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PostAnvilParserStaticData final {
  PostAnvilParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PostAnvilParserStaticData(const PostAnvilParserStaticData&) = delete;
  PostAnvilParserStaticData(PostAnvilParserStaticData&&) = delete;
  PostAnvilParserStaticData& operator=(const PostAnvilParserStaticData&) = delete;
  PostAnvilParserStaticData& operator=(PostAnvilParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag postanvilParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PostAnvilParserStaticData> postanvilParserStaticData = nullptr;

void postanvilParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (postanvilParserStaticData != nullptr) {
    return;
  }
#else
  assert(postanvilParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PostAnvilParserStaticData>(
    std::vector<std::string>{
      "program", "ruledef", "statement", "attr_assign", "expr", "or_expr", 
      "and_expr", "not_expr", "cmp_expr", "add_expr", "mul_expr", "unary_expr", 
      "primary", "attribute", "comp_op", "add_op", "mul_op"
    },
    std::vector<std::string>{
      "", "':'", "'RULE'", "'RULEEND'", "'FILTER'", "'ATTR'", "'AND'", "'OR'", 
      "'NOT'", "'SELF'", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'<='", 
      "'>='", "'=='", "'!='", "'.'", "'('", "')'", "'='"
    },
    std::vector<std::string>{
      "", "", "RULE", "RULEEND", "FILTER", "ATTR", "AND", "OR", "NOT", "SELF", 
      "PLUS", "MINUS", "STAR", "SLASH", "LT", "GT", "LE", "GE", "EQ", "NE", 
      "DOT", "LPAREN", "RPAREN", "ASSIGN", "NUMBER", "IDENTIFIER", "WS", 
      "NEWLINE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,28,141,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,5,0,37,8,0,10,0,12,0,40,9,0,1,0,1,0,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,52,8,1,10,1,12,1,55,9,1,1,1,1,1,1,2,
  	1,2,3,2,61,8,2,1,3,1,3,1,3,1,3,1,4,1,4,1,5,1,5,1,5,5,5,72,8,5,10,5,12,
  	5,75,9,5,1,6,1,6,1,6,5,6,80,8,6,10,6,12,6,83,9,6,1,7,1,7,1,7,3,7,88,8,
  	7,1,8,1,8,1,8,1,8,3,8,94,8,8,1,9,1,9,1,9,1,9,5,9,100,8,9,10,9,12,9,103,
  	9,9,1,10,1,10,1,10,1,10,5,10,109,8,10,10,10,12,10,112,9,10,1,11,1,11,
  	1,11,3,11,117,8,11,1,12,1,12,1,12,1,12,1,12,1,12,3,12,125,8,12,1,13,1,
  	13,1,13,5,13,130,8,13,10,13,12,13,133,9,13,1,14,1,14,1,15,1,15,1,16,1,
  	16,1,16,0,0,17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,5,1,0,
  	4,5,2,0,9,9,25,25,1,0,14,19,1,0,10,11,1,0,12,13,137,0,38,1,0,0,0,2,43,
  	1,0,0,0,4,60,1,0,0,0,6,62,1,0,0,0,8,66,1,0,0,0,10,68,1,0,0,0,12,76,1,
  	0,0,0,14,87,1,0,0,0,16,89,1,0,0,0,18,95,1,0,0,0,20,104,1,0,0,0,22,116,
  	1,0,0,0,24,124,1,0,0,0,26,126,1,0,0,0,28,134,1,0,0,0,30,136,1,0,0,0,32,
  	138,1,0,0,0,34,37,3,2,1,0,35,37,5,27,0,0,36,34,1,0,0,0,36,35,1,0,0,0,
  	37,40,1,0,0,0,38,36,1,0,0,0,38,39,1,0,0,0,39,41,1,0,0,0,40,38,1,0,0,0,
  	41,42,5,0,0,1,42,1,1,0,0,0,43,44,5,2,0,0,44,45,7,0,0,0,45,46,5,25,0,0,
  	46,47,5,1,0,0,47,53,5,27,0,0,48,49,3,4,2,0,49,50,5,27,0,0,50,52,1,0,0,
  	0,51,48,1,0,0,0,52,55,1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,56,1,0,0,
  	0,55,53,1,0,0,0,56,57,5,3,0,0,57,3,1,0,0,0,58,61,3,8,4,0,59,61,3,6,3,
  	0,60,58,1,0,0,0,60,59,1,0,0,0,61,5,1,0,0,0,62,63,5,25,0,0,63,64,5,23,
  	0,0,64,65,3,8,4,0,65,7,1,0,0,0,66,67,3,10,5,0,67,9,1,0,0,0,68,73,3,12,
  	6,0,69,70,5,7,0,0,70,72,3,12,6,0,71,69,1,0,0,0,72,75,1,0,0,0,73,71,1,
  	0,0,0,73,74,1,0,0,0,74,11,1,0,0,0,75,73,1,0,0,0,76,81,3,14,7,0,77,78,
  	5,6,0,0,78,80,3,14,7,0,79,77,1,0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,
  	1,0,0,0,82,13,1,0,0,0,83,81,1,0,0,0,84,85,5,8,0,0,85,88,3,14,7,0,86,88,
  	3,16,8,0,87,84,1,0,0,0,87,86,1,0,0,0,88,15,1,0,0,0,89,93,3,18,9,0,90,
  	91,3,28,14,0,91,92,3,18,9,0,92,94,1,0,0,0,93,90,1,0,0,0,93,94,1,0,0,0,
  	94,17,1,0,0,0,95,101,3,20,10,0,96,97,3,30,15,0,97,98,3,20,10,0,98,100,
  	1,0,0,0,99,96,1,0,0,0,100,103,1,0,0,0,101,99,1,0,0,0,101,102,1,0,0,0,
  	102,19,1,0,0,0,103,101,1,0,0,0,104,110,3,22,11,0,105,106,3,32,16,0,106,
  	107,3,22,11,0,107,109,1,0,0,0,108,105,1,0,0,0,109,112,1,0,0,0,110,108,
  	1,0,0,0,110,111,1,0,0,0,111,21,1,0,0,0,112,110,1,0,0,0,113,114,5,11,0,
  	0,114,117,3,22,11,0,115,117,3,24,12,0,116,113,1,0,0,0,116,115,1,0,0,0,
  	117,23,1,0,0,0,118,125,5,24,0,0,119,125,3,26,13,0,120,121,5,21,0,0,121,
  	122,3,8,4,0,122,123,5,22,0,0,123,125,1,0,0,0,124,118,1,0,0,0,124,119,
  	1,0,0,0,124,120,1,0,0,0,125,25,1,0,0,0,126,131,7,1,0,0,127,128,5,20,0,
  	0,128,130,5,25,0,0,129,127,1,0,0,0,130,133,1,0,0,0,131,129,1,0,0,0,131,
  	132,1,0,0,0,132,27,1,0,0,0,133,131,1,0,0,0,134,135,7,2,0,0,135,29,1,0,
  	0,0,136,137,7,3,0,0,137,31,1,0,0,0,138,139,7,4,0,0,139,33,1,0,0,0,13,
  	36,38,53,60,73,81,87,93,101,110,116,124,131
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  postanvilParserStaticData = std::move(staticData);
}

}

PostAnvilParser::PostAnvilParser(TokenStream *input) : PostAnvilParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PostAnvilParser::PostAnvilParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  PostAnvilParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *postanvilParserStaticData->atn, postanvilParserStaticData->decisionToDFA, postanvilParserStaticData->sharedContextCache, options);
}

PostAnvilParser::~PostAnvilParser() {
  delete _interpreter;
}

const atn::ATN& PostAnvilParser::getATN() const {
  return *postanvilParserStaticData->atn;
}

std::string PostAnvilParser::getGrammarFileName() const {
  return "PostAnvil.g4";
}

const std::vector<std::string>& PostAnvilParser::getRuleNames() const {
  return postanvilParserStaticData->ruleNames;
}

const dfa::Vocabulary& PostAnvilParser::getVocabulary() const {
  return postanvilParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PostAnvilParser::getSerializedATN() const {
  return postanvilParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

PostAnvilParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ProgramContext::EOF() {
  return getToken(PostAnvilParser::EOF, 0);
}

std::vector<PostAnvilParser::RuledefContext *> PostAnvilParser::ProgramContext::ruledef() {
  return getRuleContexts<PostAnvilParser::RuledefContext>();
}

PostAnvilParser::RuledefContext* PostAnvilParser::ProgramContext::ruledef(size_t i) {
  return getRuleContext<PostAnvilParser::RuledefContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::ProgramContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::ProgramContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
}


size_t PostAnvilParser::ProgramContext::getRuleIndex() const {
  return PostAnvilParser::RuleProgram;
}

void PostAnvilParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void PostAnvilParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}

PostAnvilParser::ProgramContext* PostAnvilParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, PostAnvilParser::RuleProgram);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::RULE

    || _la == PostAnvilParser::NEWLINE) {
      setState(36);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PostAnvilParser::RULE: {
          setState(34);
          ruledef();
          break;
        }

        case PostAnvilParser::NEWLINE: {
          setState(35);
          match(PostAnvilParser::NEWLINE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(40);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(41);
    match(PostAnvilParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RuledefContext ------------------------------------------------------------------

PostAnvilParser::RuledefContext::RuledefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::RuledefContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

std::vector<tree::TerminalNode *> PostAnvilParser::RuledefContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::RuledefContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
}

tree::TerminalNode* PostAnvilParser::RuledefContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

tree::TerminalNode* PostAnvilParser::RuledefContext::FILTER() {
  return getToken(PostAnvilParser::FILTER, 0);
}

tree::TerminalNode* PostAnvilParser::RuledefContext::ATTR() {
  return getToken(PostAnvilParser::ATTR, 0);
}

tree::TerminalNode* PostAnvilParser::RuledefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

std::vector<PostAnvilParser::StatementContext *> PostAnvilParser::RuledefContext::statement() {
  return getRuleContexts<PostAnvilParser::StatementContext>();
}

PostAnvilParser::StatementContext* PostAnvilParser::RuledefContext::statement(size_t i) {
  return getRuleContext<PostAnvilParser::StatementContext>(i);
}


size_t PostAnvilParser::RuledefContext::getRuleIndex() const {
  return PostAnvilParser::RuleRuledef;
}

void PostAnvilParser::RuledefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRuledef(this);
}

void PostAnvilParser::RuledefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRuledef(this);
}

PostAnvilParser::RuledefContext* PostAnvilParser::ruledef() {
  RuledefContext *_localctx = _tracker.createInstance<RuledefContext>(_ctx, getState());
  enterRule(_localctx, 2, PostAnvilParser::RuleRuledef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    match(PostAnvilParser::RULE);
    setState(44);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::FILTER

    || _la == PostAnvilParser::ATTR)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(45);
    antlrcpp::downCast<RuledefContext *>(_localctx)->target = match(PostAnvilParser::IDENTIFIER);
    setState(46);
    match(PostAnvilParser::T__0);
    setState(47);
    match(PostAnvilParser::NEWLINE);
    setState(53);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52431616) != 0)) {
      setState(48);
      statement();
      setState(49);
      match(PostAnvilParser::NEWLINE);
      setState(55);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(56);
    match(PostAnvilParser::RULEEND);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

PostAnvilParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PostAnvilParser::StatementContext::getRuleIndex() const {
  return PostAnvilParser::RuleStatement;
}

void PostAnvilParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprStmtContext ------------------------------------------------------------------

PostAnvilParser::ExprContext* PostAnvilParser::ExprStmtContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::ExprStmtContext::ExprStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::ExprStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprStmt(this);
}
void PostAnvilParser::ExprStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprStmt(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

PostAnvilParser::Attr_assignContext* PostAnvilParser::AssignStmtContext::attr_assign() {
  return getRuleContext<PostAnvilParser::Attr_assignContext>(0);
}

PostAnvilParser::AssignStmtContext::AssignStmtContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::AssignStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignStmt(this);
}
void PostAnvilParser::AssignStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignStmt(this);
}
PostAnvilParser::StatementContext* PostAnvilParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, PostAnvilParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(60);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(58);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(59);
      attr_assign();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_assignContext ------------------------------------------------------------------

PostAnvilParser::Attr_assignContext::Attr_assignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Attr_assignContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::Attr_assignContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::Attr_assignContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}


size_t PostAnvilParser::Attr_assignContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttr_assign;
}

void PostAnvilParser::Attr_assignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_assign(this);
}

void PostAnvilParser::Attr_assignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_assign(this);
}

PostAnvilParser::Attr_assignContext* PostAnvilParser::attr_assign() {
  Attr_assignContext *_localctx = _tracker.createInstance<Attr_assignContext>(_ctx, getState());
  enterRule(_localctx, 6, PostAnvilParser::RuleAttr_assign);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62);
    antlrcpp::downCast<Attr_assignContext *>(_localctx)->attr_name = match(PostAnvilParser::IDENTIFIER);
    setState(63);
    match(PostAnvilParser::ASSIGN);
    setState(64);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

PostAnvilParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::Or_exprContext* PostAnvilParser::ExprContext::or_expr() {
  return getRuleContext<PostAnvilParser::Or_exprContext>(0);
}


size_t PostAnvilParser::ExprContext::getRuleIndex() const {
  return PostAnvilParser::RuleExpr;
}

void PostAnvilParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void PostAnvilParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

PostAnvilParser::ExprContext* PostAnvilParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 8, PostAnvilParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    or_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Or_exprContext ------------------------------------------------------------------

PostAnvilParser::Or_exprContext::Or_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::And_exprContext *> PostAnvilParser::Or_exprContext::and_expr() {
  return getRuleContexts<PostAnvilParser::And_exprContext>();
}

PostAnvilParser::And_exprContext* PostAnvilParser::Or_exprContext::and_expr(size_t i) {
  return getRuleContext<PostAnvilParser::And_exprContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::Or_exprContext::OR() {
  return getTokens(PostAnvilParser::OR);
}

tree::TerminalNode* PostAnvilParser::Or_exprContext::OR(size_t i) {
  return getToken(PostAnvilParser::OR, i);
}


size_t PostAnvilParser::Or_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleOr_expr;
}

void PostAnvilParser::Or_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOr_expr(this);
}

void PostAnvilParser::Or_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOr_expr(this);
}

PostAnvilParser::Or_exprContext* PostAnvilParser::or_expr() {
  Or_exprContext *_localctx = _tracker.createInstance<Or_exprContext>(_ctx, getState());
  enterRule(_localctx, 10, PostAnvilParser::RuleOr_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    and_expr();
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::OR) {
      setState(69);
      match(PostAnvilParser::OR);
      setState(70);
      and_expr();
      setState(75);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- And_exprContext ------------------------------------------------------------------

PostAnvilParser::And_exprContext::And_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Not_exprContext *> PostAnvilParser::And_exprContext::not_expr() {
  return getRuleContexts<PostAnvilParser::Not_exprContext>();
}

PostAnvilParser::Not_exprContext* PostAnvilParser::And_exprContext::not_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Not_exprContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::And_exprContext::AND() {
  return getTokens(PostAnvilParser::AND);
}

tree::TerminalNode* PostAnvilParser::And_exprContext::AND(size_t i) {
  return getToken(PostAnvilParser::AND, i);
}


size_t PostAnvilParser::And_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleAnd_expr;
}

void PostAnvilParser::And_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnd_expr(this);
}

void PostAnvilParser::And_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnd_expr(this);
}

PostAnvilParser::And_exprContext* PostAnvilParser::and_expr() {
  And_exprContext *_localctx = _tracker.createInstance<And_exprContext>(_ctx, getState());
  enterRule(_localctx, 12, PostAnvilParser::RuleAnd_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    not_expr();
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::AND) {
      setState(77);
      match(PostAnvilParser::AND);
      setState(78);
      not_expr();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Not_exprContext ------------------------------------------------------------------

PostAnvilParser::Not_exprContext::Not_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Not_exprContext::NOT() {
  return getToken(PostAnvilParser::NOT, 0);
}

PostAnvilParser::Not_exprContext* PostAnvilParser::Not_exprContext::not_expr() {
  return getRuleContext<PostAnvilParser::Not_exprContext>(0);
}

PostAnvilParser::Cmp_exprContext* PostAnvilParser::Not_exprContext::cmp_expr() {
  return getRuleContext<PostAnvilParser::Cmp_exprContext>(0);
}


size_t PostAnvilParser::Not_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleNot_expr;
}

void PostAnvilParser::Not_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNot_expr(this);
}

void PostAnvilParser::Not_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNot_expr(this);
}

PostAnvilParser::Not_exprContext* PostAnvilParser::not_expr() {
  Not_exprContext *_localctx = _tracker.createInstance<Not_exprContext>(_ctx, getState());
  enterRule(_localctx, 14, PostAnvilParser::RuleNot_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(87);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(84);
        match(PostAnvilParser::NOT);
        setState(85);
        not_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::MINUS:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(86);
        cmp_expr();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cmp_exprContext ------------------------------------------------------------------

PostAnvilParser::Cmp_exprContext::Cmp_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Add_exprContext *> PostAnvilParser::Cmp_exprContext::add_expr() {
  return getRuleContexts<PostAnvilParser::Add_exprContext>();
}

PostAnvilParser::Add_exprContext* PostAnvilParser::Cmp_exprContext::add_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Add_exprContext>(i);
}

PostAnvilParser::Comp_opContext* PostAnvilParser::Cmp_exprContext::comp_op() {
  return getRuleContext<PostAnvilParser::Comp_opContext>(0);
}


size_t PostAnvilParser::Cmp_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleCmp_expr;
}

void PostAnvilParser::Cmp_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCmp_expr(this);
}

void PostAnvilParser::Cmp_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCmp_expr(this);
}

PostAnvilParser::Cmp_exprContext* PostAnvilParser::cmp_expr() {
  Cmp_exprContext *_localctx = _tracker.createInstance<Cmp_exprContext>(_ctx, getState());
  enterRule(_localctx, 16, PostAnvilParser::RuleCmp_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    add_expr();
    setState(93);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1032192) != 0)) {
      setState(90);
      comp_op();
      setState(91);
      add_expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Add_exprContext ------------------------------------------------------------------

PostAnvilParser::Add_exprContext::Add_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Mul_exprContext *> PostAnvilParser::Add_exprContext::mul_expr() {
  return getRuleContexts<PostAnvilParser::Mul_exprContext>();
}

PostAnvilParser::Mul_exprContext* PostAnvilParser::Add_exprContext::mul_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Mul_exprContext>(i);
}

std::vector<PostAnvilParser::Add_opContext *> PostAnvilParser::Add_exprContext::add_op() {
  return getRuleContexts<PostAnvilParser::Add_opContext>();
}

PostAnvilParser::Add_opContext* PostAnvilParser::Add_exprContext::add_op(size_t i) {
  return getRuleContext<PostAnvilParser::Add_opContext>(i);
}


size_t PostAnvilParser::Add_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleAdd_expr;
}

void PostAnvilParser::Add_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_expr(this);
}

void PostAnvilParser::Add_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_expr(this);
}

PostAnvilParser::Add_exprContext* PostAnvilParser::add_expr() {
  Add_exprContext *_localctx = _tracker.createInstance<Add_exprContext>(_ctx, getState());
  enterRule(_localctx, 18, PostAnvilParser::RuleAdd_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(95);
    mul_expr();
    setState(101);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS) {
      setState(96);
      add_op();
      setState(97);
      mul_expr();
      setState(103);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mul_exprContext ------------------------------------------------------------------

PostAnvilParser::Mul_exprContext::Mul_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Unary_exprContext *> PostAnvilParser::Mul_exprContext::unary_expr() {
  return getRuleContexts<PostAnvilParser::Unary_exprContext>();
}

PostAnvilParser::Unary_exprContext* PostAnvilParser::Mul_exprContext::unary_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Unary_exprContext>(i);
}

std::vector<PostAnvilParser::Mul_opContext *> PostAnvilParser::Mul_exprContext::mul_op() {
  return getRuleContexts<PostAnvilParser::Mul_opContext>();
}

PostAnvilParser::Mul_opContext* PostAnvilParser::Mul_exprContext::mul_op(size_t i) {
  return getRuleContext<PostAnvilParser::Mul_opContext>(i);
}


size_t PostAnvilParser::Mul_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleMul_expr;
}

void PostAnvilParser::Mul_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMul_expr(this);
}

void PostAnvilParser::Mul_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMul_expr(this);
}

PostAnvilParser::Mul_exprContext* PostAnvilParser::mul_expr() {
  Mul_exprContext *_localctx = _tracker.createInstance<Mul_exprContext>(_ctx, getState());
  enterRule(_localctx, 20, PostAnvilParser::RuleMul_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    unary_expr();
    setState(110);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH) {
      setState(105);
      mul_op();
      setState(106);
      unary_expr();
      setState(112);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Unary_exprContext ------------------------------------------------------------------

PostAnvilParser::Unary_exprContext::Unary_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Unary_exprContext::MINUS() {
  return getToken(PostAnvilParser::MINUS, 0);
}

PostAnvilParser::Unary_exprContext* PostAnvilParser::Unary_exprContext::unary_expr() {
  return getRuleContext<PostAnvilParser::Unary_exprContext>(0);
}

PostAnvilParser::PrimaryContext* PostAnvilParser::Unary_exprContext::primary() {
  return getRuleContext<PostAnvilParser::PrimaryContext>(0);
}


size_t PostAnvilParser::Unary_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleUnary_expr;
}

void PostAnvilParser::Unary_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnary_expr(this);
}

void PostAnvilParser::Unary_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnary_expr(this);
}

PostAnvilParser::Unary_exprContext* PostAnvilParser::unary_expr() {
  Unary_exprContext *_localctx = _tracker.createInstance<Unary_exprContext>(_ctx, getState());
  enterRule(_localctx, 22, PostAnvilParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(116);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(113);
        match(PostAnvilParser::MINUS);
        setState(114);
        unary_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(115);
        primary();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

PostAnvilParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::PrimaryContext::NUMBER() {
  return getToken(PostAnvilParser::NUMBER, 0);
}

PostAnvilParser::AttributeContext* PostAnvilParser::PrimaryContext::attribute() {
  return getRuleContext<PostAnvilParser::AttributeContext>(0);
}

tree::TerminalNode* PostAnvilParser::PrimaryContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::PrimaryContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::PrimaryContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}


size_t PostAnvilParser::PrimaryContext::getRuleIndex() const {
  return PostAnvilParser::RulePrimary;
}

void PostAnvilParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void PostAnvilParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}

PostAnvilParser::PrimaryContext* PostAnvilParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 24, PostAnvilParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(124);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NUMBER: {
        enterOuterAlt(_localctx, 1);
        setState(118);
        match(PostAnvilParser::NUMBER);
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(119);
        attribute();
        break;
      }

      case PostAnvilParser::LPAREN: {
        enterOuterAlt(_localctx, 3);
        setState(120);
        match(PostAnvilParser::LPAREN);
        setState(121);
        expr();
        setState(122);
        match(PostAnvilParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AttributeContext ------------------------------------------------------------------

PostAnvilParser::AttributeContext::AttributeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::AttributeContext::SELF() {
  return getToken(PostAnvilParser::SELF, 0);
}

std::vector<tree::TerminalNode *> PostAnvilParser::AttributeContext::IDENTIFIER() {
  return getTokens(PostAnvilParser::IDENTIFIER);
}

tree::TerminalNode* PostAnvilParser::AttributeContext::IDENTIFIER(size_t i) {
  return getToken(PostAnvilParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::AttributeContext::DOT() {
  return getTokens(PostAnvilParser::DOT);
}

tree::TerminalNode* PostAnvilParser::AttributeContext::DOT(size_t i) {
  return getToken(PostAnvilParser::DOT, i);
}


size_t PostAnvilParser::AttributeContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttribute;
}

void PostAnvilParser::AttributeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttribute(this);
}

void PostAnvilParser::AttributeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttribute(this);
}

PostAnvilParser::AttributeContext* PostAnvilParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 26, PostAnvilParser::RuleAttribute);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::SELF

    || _la == PostAnvilParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::DOT) {
      setState(127);
      match(PostAnvilParser::DOT);
      setState(128);
      match(PostAnvilParser::IDENTIFIER);
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Comp_opContext ------------------------------------------------------------------

PostAnvilParser::Comp_opContext::Comp_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::GT() {
  return getToken(PostAnvilParser::GT, 0);
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::LT() {
  return getToken(PostAnvilParser::LT, 0);
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::GE() {
  return getToken(PostAnvilParser::GE, 0);
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::LE() {
  return getToken(PostAnvilParser::LE, 0);
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::EQ() {
  return getToken(PostAnvilParser::EQ, 0);
}

tree::TerminalNode* PostAnvilParser::Comp_opContext::NE() {
  return getToken(PostAnvilParser::NE, 0);
}


size_t PostAnvilParser::Comp_opContext::getRuleIndex() const {
  return PostAnvilParser::RuleComp_op;
}

void PostAnvilParser::Comp_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComp_op(this);
}

void PostAnvilParser::Comp_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComp_op(this);
}

PostAnvilParser::Comp_opContext* PostAnvilParser::comp_op() {
  Comp_opContext *_localctx = _tracker.createInstance<Comp_opContext>(_ctx, getState());
  enterRule(_localctx, 28, PostAnvilParser::RuleComp_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(134);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1032192) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Add_opContext ------------------------------------------------------------------

PostAnvilParser::Add_opContext::Add_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Add_opContext::PLUS() {
  return getToken(PostAnvilParser::PLUS, 0);
}

tree::TerminalNode* PostAnvilParser::Add_opContext::MINUS() {
  return getToken(PostAnvilParser::MINUS, 0);
}


size_t PostAnvilParser::Add_opContext::getRuleIndex() const {
  return PostAnvilParser::RuleAdd_op;
}

void PostAnvilParser::Add_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_op(this);
}

void PostAnvilParser::Add_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_op(this);
}

PostAnvilParser::Add_opContext* PostAnvilParser::add_op() {
  Add_opContext *_localctx = _tracker.createInstance<Add_opContext>(_ctx, getState());
  enterRule(_localctx, 30, PostAnvilParser::RuleAdd_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(136);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mul_opContext ------------------------------------------------------------------

PostAnvilParser::Mul_opContext::Mul_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Mul_opContext::STAR() {
  return getToken(PostAnvilParser::STAR, 0);
}

tree::TerminalNode* PostAnvilParser::Mul_opContext::SLASH() {
  return getToken(PostAnvilParser::SLASH, 0);
}


size_t PostAnvilParser::Mul_opContext::getRuleIndex() const {
  return PostAnvilParser::RuleMul_op;
}

void PostAnvilParser::Mul_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMul_op(this);
}

void PostAnvilParser::Mul_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMul_op(this);
}

PostAnvilParser::Mul_opContext* PostAnvilParser::mul_op() {
  Mul_opContext *_localctx = _tracker.createInstance<Mul_opContext>(_ctx, getState());
  enterRule(_localctx, 32, PostAnvilParser::RuleMul_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void PostAnvilParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  postanvilParserInitialize();
#else
  ::antlr4::internal::call_once(postanvilParserOnceFlag, postanvilParserInitialize);
#endif
}
