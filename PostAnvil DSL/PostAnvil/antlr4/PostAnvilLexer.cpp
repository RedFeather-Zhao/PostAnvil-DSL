
// Generated from PostAnvil.g4 by ANTLR 4.13.2


#include "PostAnvilLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct PostAnvilLexerStaticData final {
  PostAnvilLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PostAnvilLexerStaticData(const PostAnvilLexerStaticData&) = delete;
  PostAnvilLexerStaticData(PostAnvilLexerStaticData&&) = delete;
  PostAnvilLexerStaticData& operator=(const PostAnvilLexerStaticData&) = delete;
  PostAnvilLexerStaticData& operator=(PostAnvilLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag postanvillexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<PostAnvilLexerStaticData> postanvillexerLexerStaticData = nullptr;

void postanvillexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (postanvillexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(postanvillexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PostAnvilLexerStaticData>(
    std::vector<std::string>{
      "T__0", "RULE", "RULEEND", "FILTER", "ATTR", "AND", "OR", "NOT", "SELF", 
      "PLUS", "MINUS", "STAR", "SLASH", "LT", "GT", "LE", "GE", "EQ", "NE", 
      "DOT", "LPAREN", "RPAREN", "ASSIGN", "NUMBER", "IDENTIFIER", "WS", 
      "NEWLINE", "COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,28,186,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,1,0,
  	1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,7,1,7,
  	1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,
  	1,13,1,14,1,14,1,15,1,15,1,15,1,16,1,16,1,16,1,17,1,17,1,17,1,18,1,18,
  	1,18,1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,4,23,134,8,23,11,23,
  	12,23,135,1,23,1,23,5,23,140,8,23,10,23,12,23,143,9,23,3,23,145,8,23,
  	1,23,1,23,4,23,149,8,23,11,23,12,23,150,3,23,153,8,23,1,24,1,24,5,24,
  	157,8,24,10,24,12,24,160,9,24,1,25,4,25,163,8,25,11,25,12,25,164,1,25,
  	1,25,1,26,3,26,170,8,26,1,26,1,26,1,27,1,27,1,27,3,27,177,8,27,1,27,5,
  	27,180,8,27,10,27,12,27,183,9,27,1,27,1,27,0,0,28,1,1,3,2,5,3,7,4,9,5,
  	11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,
  	18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,1,0,17,
  	2,0,82,82,114,114,2,0,85,85,117,117,2,0,76,76,108,108,2,0,69,69,101,101,
  	2,0,78,78,110,110,2,0,68,68,100,100,2,0,70,70,102,102,2,0,73,73,105,105,
  	2,0,84,84,116,116,2,0,65,65,97,97,2,0,79,79,111,111,2,0,83,83,115,115,
  	1,0,48,57,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,2,0,9,9,
  	32,32,2,0,10,10,13,13,195,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,1,57,1,0,0,0,3,59,1,0,0,0,5,64,1,
  	0,0,0,7,72,1,0,0,0,9,79,1,0,0,0,11,84,1,0,0,0,13,88,1,0,0,0,15,91,1,0,
  	0,0,17,95,1,0,0,0,19,100,1,0,0,0,21,102,1,0,0,0,23,104,1,0,0,0,25,106,
  	1,0,0,0,27,108,1,0,0,0,29,110,1,0,0,0,31,112,1,0,0,0,33,115,1,0,0,0,35,
  	118,1,0,0,0,37,121,1,0,0,0,39,124,1,0,0,0,41,126,1,0,0,0,43,128,1,0,0,
  	0,45,130,1,0,0,0,47,152,1,0,0,0,49,154,1,0,0,0,51,162,1,0,0,0,53,169,
  	1,0,0,0,55,176,1,0,0,0,57,58,5,58,0,0,58,2,1,0,0,0,59,60,7,0,0,0,60,61,
  	7,1,0,0,61,62,7,2,0,0,62,63,7,3,0,0,63,4,1,0,0,0,64,65,7,0,0,0,65,66,
  	7,1,0,0,66,67,7,2,0,0,67,68,7,3,0,0,68,69,7,3,0,0,69,70,7,4,0,0,70,71,
  	7,5,0,0,71,6,1,0,0,0,72,73,7,6,0,0,73,74,7,7,0,0,74,75,7,2,0,0,75,76,
  	7,8,0,0,76,77,7,3,0,0,77,78,7,0,0,0,78,8,1,0,0,0,79,80,7,9,0,0,80,81,
  	7,8,0,0,81,82,7,8,0,0,82,83,7,0,0,0,83,10,1,0,0,0,84,85,7,9,0,0,85,86,
  	7,4,0,0,86,87,7,5,0,0,87,12,1,0,0,0,88,89,7,10,0,0,89,90,7,0,0,0,90,14,
  	1,0,0,0,91,92,7,4,0,0,92,93,7,10,0,0,93,94,7,8,0,0,94,16,1,0,0,0,95,96,
  	7,11,0,0,96,97,7,3,0,0,97,98,7,2,0,0,98,99,7,6,0,0,99,18,1,0,0,0,100,
  	101,5,43,0,0,101,20,1,0,0,0,102,103,5,45,0,0,103,22,1,0,0,0,104,105,5,
  	42,0,0,105,24,1,0,0,0,106,107,5,47,0,0,107,26,1,0,0,0,108,109,5,60,0,
  	0,109,28,1,0,0,0,110,111,5,62,0,0,111,30,1,0,0,0,112,113,5,60,0,0,113,
  	114,5,61,0,0,114,32,1,0,0,0,115,116,5,62,0,0,116,117,5,61,0,0,117,34,
  	1,0,0,0,118,119,5,61,0,0,119,120,5,61,0,0,120,36,1,0,0,0,121,122,5,33,
  	0,0,122,123,5,61,0,0,123,38,1,0,0,0,124,125,5,46,0,0,125,40,1,0,0,0,126,
  	127,5,40,0,0,127,42,1,0,0,0,128,129,5,41,0,0,129,44,1,0,0,0,130,131,5,
  	61,0,0,131,46,1,0,0,0,132,134,7,12,0,0,133,132,1,0,0,0,134,135,1,0,0,
  	0,135,133,1,0,0,0,135,136,1,0,0,0,136,144,1,0,0,0,137,141,5,46,0,0,138,
  	140,7,12,0,0,139,138,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,
  	1,0,0,0,142,145,1,0,0,0,143,141,1,0,0,0,144,137,1,0,0,0,144,145,1,0,0,
  	0,145,153,1,0,0,0,146,148,5,46,0,0,147,149,7,12,0,0,148,147,1,0,0,0,149,
  	150,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,153,1,0,0,0,152,133,1,
  	0,0,0,152,146,1,0,0,0,153,48,1,0,0,0,154,158,7,13,0,0,155,157,7,14,0,
  	0,156,155,1,0,0,0,157,160,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,
  	50,1,0,0,0,160,158,1,0,0,0,161,163,7,15,0,0,162,161,1,0,0,0,163,164,1,
  	0,0,0,164,162,1,0,0,0,164,165,1,0,0,0,165,166,1,0,0,0,166,167,6,25,0,
  	0,167,52,1,0,0,0,168,170,5,13,0,0,169,168,1,0,0,0,169,170,1,0,0,0,170,
  	171,1,0,0,0,171,172,5,10,0,0,172,54,1,0,0,0,173,177,5,35,0,0,174,175,
  	5,47,0,0,175,177,5,47,0,0,176,173,1,0,0,0,176,174,1,0,0,0,177,181,1,0,
  	0,0,178,180,8,16,0,0,179,178,1,0,0,0,180,183,1,0,0,0,181,179,1,0,0,0,
  	181,182,1,0,0,0,182,184,1,0,0,0,183,181,1,0,0,0,184,185,6,27,0,0,185,
  	56,1,0,0,0,11,0,135,141,144,150,152,158,164,169,176,181,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  postanvillexerLexerStaticData = std::move(staticData);
}

}

PostAnvilLexer::PostAnvilLexer(CharStream *input) : Lexer(input) {
  PostAnvilLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *postanvillexerLexerStaticData->atn, postanvillexerLexerStaticData->decisionToDFA, postanvillexerLexerStaticData->sharedContextCache);
}

PostAnvilLexer::~PostAnvilLexer() {
  delete _interpreter;
}

std::string PostAnvilLexer::getGrammarFileName() const {
  return "PostAnvil.g4";
}

const std::vector<std::string>& PostAnvilLexer::getRuleNames() const {
  return postanvillexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& PostAnvilLexer::getChannelNames() const {
  return postanvillexerLexerStaticData->channelNames;
}

const std::vector<std::string>& PostAnvilLexer::getModeNames() const {
  return postanvillexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& PostAnvilLexer::getVocabulary() const {
  return postanvillexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PostAnvilLexer::getSerializedATN() const {
  return postanvillexerLexerStaticData->serializedATN;
}

const atn::ATN& PostAnvilLexer::getATN() const {
  return *postanvillexerLexerStaticData->atn;
}




void PostAnvilLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  postanvillexerLexerInitialize();
#else
  ::antlr4::internal::call_once(postanvillexerLexerOnceFlag, postanvillexerLexerInitialize);
#endif
}
