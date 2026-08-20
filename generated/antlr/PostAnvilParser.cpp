
// Generated from grammar/PostAnvil.g4 by ANTLR 4.13.2


#include "PostAnvilListener.h"
#include "PostAnvilVisitor.h"

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
      "program", "newlines", "declaration", "importDef", "importItem", "exportDef", 
      "exportItem", "globalDef", "type", "condition_block", "attr_block", 
      "sort_block", "stmt_block", "rule_", "filter_rule", "attr_rule", "group_rule", 
      "append_rule", "sort_rule", "func_rule", "attr_def", "attr_lvalue", 
      "typed_params", "typed_param", "statement", "ifStmt", "ifBranch", 
      "elifBranch", "elseBranch", "forStmt", "sort_key", "direction", "class_expr", 
      "class_selector", "class_group", "for_source", "bool_expr", "expr", 
      "or_expr", "and_expr", "not_expr", "cmp_expr", "add_expr", "mul_expr", 
      "unary_expr", "primary", "func_call", "attribute", "comp_op", "add_op", 
      "mul_op"
    },
    std::vector<std::string>{
      "", "':'", "'RULE'", "'FILTER'", "'ATTR'", "'FUNC'", "'SORT'", "'GROUP'", 
      "'APPEND'", "'FROM'", "'IMPORT'", "'EXPORT'", "'AS'", "'AND'", "'OR'", 
      "'NOT'", "", "'SELF'", "'NUM'", "'STR'", "'BOOL'", "'INST'", "'ANY'", 
      "'ALL_INST'", "'RETURN'", "'IF'", "'ELIF'", "'ELSE'", "'FOR'", "'IN'", 
      "'ASC'", "'DESC'", "'{'", "'}'", "'->'", "'+'", "'-'", "'*'", "'/'", 
      "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'.'", "'('", "')'", 
      "','", "'='", "'@'"
    },
    std::vector<std::string>{
      "", "", "RULE", "FILTER", "ATTR", "FUNC", "SORT", "GROUP", "APPEND", 
      "FROM", "IMPORT", "EXPORT", "AS", "AND", "OR", "NOT", "BOOL_LIT", 
      "SELF", "NUM", "STR", "BOOL", "INST", "ANY", "ALL_INST", "RETURN", 
      "IF", "ELIF", "ELSE", "FOR", "IN", "ASC", "DESC", "LCURLY", "RCURLY", 
      "ARROW", "PLUS", "MINUS", "STAR", "SLASH", "LT", "GT", "LE", "GE", 
      "EQ", "NE", "DOT", "LPAREN", "RPAREN", "COMMA", "ASSIGN", "AT", "NUMBER", 
      "STRING", "IDENTIFIER", "WS", "LINE_CONTINUATION", "NEWLINE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,57,551,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,1,0,5,0,104,8,0,10,0,12,0,107,9,0,1,0,1,0,3,0,111,8,0,1,
  	0,4,0,114,8,0,11,0,12,0,115,5,0,118,8,0,10,0,12,0,121,9,0,1,0,1,0,3,0,
  	125,8,0,1,0,1,0,1,1,4,1,130,8,1,11,1,12,1,131,1,2,1,2,1,2,3,2,137,8,2,
  	1,3,1,3,1,3,1,3,5,3,143,8,3,10,3,12,3,146,9,3,1,4,1,4,1,4,1,4,3,4,152,
  	8,4,1,5,1,5,1,5,1,5,5,5,158,8,5,10,5,12,5,161,9,5,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,175,8,7,1,8,1,8,1,9,1,9,3,9,181,8,9,1,
  	9,1,9,1,9,1,9,5,9,187,8,9,10,9,12,9,190,9,9,1,9,3,9,193,8,9,3,9,195,8,
  	9,1,9,1,9,1,10,1,10,3,10,201,8,10,1,10,1,10,1,10,1,10,5,10,207,8,10,10,
  	10,12,10,210,9,10,1,10,3,10,213,8,10,3,10,215,8,10,1,10,1,10,1,11,1,11,
  	3,11,221,8,11,1,11,1,11,1,11,1,11,5,11,227,8,11,10,11,12,11,230,9,11,
  	1,11,3,11,233,8,11,1,11,1,11,1,12,1,12,3,12,239,8,12,1,12,1,12,1,12,1,
  	12,5,12,245,8,12,10,12,12,12,248,9,12,1,12,3,12,251,8,12,3,12,253,8,12,
  	1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,3,13,263,8,13,1,14,1,14,1,14,
  	1,14,3,14,269,8,14,1,14,1,14,1,15,1,15,1,15,1,15,3,15,277,8,15,1,15,1,
  	15,1,16,1,16,1,16,1,16,1,16,1,16,3,16,287,8,16,1,16,1,16,1,17,1,17,1,
  	17,1,17,1,17,1,17,3,17,297,8,17,1,17,1,17,1,18,1,18,1,18,1,18,3,18,305,
  	8,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,3,19,314,8,19,1,19,1,19,1,19,
  	3,19,319,8,19,1,19,3,19,322,8,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,
  	21,1,21,1,21,1,21,1,21,3,21,336,8,21,1,22,1,22,1,22,5,22,341,8,22,10,
  	22,12,22,344,9,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,1,24,1,24,3,24,363,8,24,1,25,1,25,3,25,367,8,25,
  	1,25,5,25,370,8,25,10,25,12,25,373,9,25,1,25,3,25,376,8,25,1,25,3,25,
  	379,8,25,1,26,1,26,1,26,3,26,384,8,26,1,26,1,26,1,27,1,27,1,27,3,27,391,
  	8,27,1,27,1,27,1,28,1,28,3,28,397,8,28,1,28,1,28,1,29,1,29,1,29,1,29,
  	1,29,3,29,406,8,29,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,32,1,32,1,33,
  	1,33,1,33,5,33,420,8,33,10,33,12,33,423,9,33,1,33,3,33,426,8,33,1,34,
  	1,34,1,34,1,35,1,35,3,35,433,8,35,1,36,1,36,1,37,1,37,1,38,1,38,1,38,
  	5,38,442,8,38,10,38,12,38,445,9,38,1,39,1,39,1,39,5,39,450,8,39,10,39,
  	12,39,453,9,39,1,40,1,40,1,40,3,40,458,8,40,1,41,1,41,1,41,1,41,3,41,
  	464,8,41,1,42,1,42,1,42,1,42,5,42,470,8,42,10,42,12,42,473,9,42,1,43,
  	1,43,1,43,1,43,5,43,479,8,43,10,43,12,43,482,9,43,1,44,1,44,1,44,3,44,
  	487,8,44,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,1,45,3,45,
  	500,8,45,1,46,1,46,1,46,1,46,1,46,5,46,507,8,46,10,46,12,46,510,9,46,
  	3,46,512,8,46,1,46,1,46,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,
  	1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,1,47,
  	1,47,1,47,1,47,1,47,3,47,543,8,47,1,48,1,48,1,49,1,49,1,50,1,50,1,50,
  	0,0,51,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,
  	92,94,96,98,100,0,6,1,0,18,22,1,0,30,31,2,0,23,23,52,53,1,0,39,44,1,0,
  	35,36,1,0,37,38,579,0,105,1,0,0,0,2,129,1,0,0,0,4,136,1,0,0,0,6,138,1,
  	0,0,0,8,147,1,0,0,0,10,153,1,0,0,0,12,162,1,0,0,0,14,174,1,0,0,0,16,176,
  	1,0,0,0,18,178,1,0,0,0,20,198,1,0,0,0,22,218,1,0,0,0,24,236,1,0,0,0,26,
  	262,1,0,0,0,28,264,1,0,0,0,30,272,1,0,0,0,32,280,1,0,0,0,34,290,1,0,0,
  	0,36,300,1,0,0,0,38,308,1,0,0,0,40,325,1,0,0,0,42,335,1,0,0,0,44,337,
  	1,0,0,0,46,345,1,0,0,0,48,362,1,0,0,0,50,364,1,0,0,0,52,380,1,0,0,0,54,
  	387,1,0,0,0,56,394,1,0,0,0,58,400,1,0,0,0,60,409,1,0,0,0,62,412,1,0,0,
  	0,64,414,1,0,0,0,66,425,1,0,0,0,68,427,1,0,0,0,70,432,1,0,0,0,72,434,
  	1,0,0,0,74,436,1,0,0,0,76,438,1,0,0,0,78,446,1,0,0,0,80,457,1,0,0,0,82,
  	459,1,0,0,0,84,465,1,0,0,0,86,474,1,0,0,0,88,486,1,0,0,0,90,499,1,0,0,
  	0,92,501,1,0,0,0,94,542,1,0,0,0,96,544,1,0,0,0,98,546,1,0,0,0,100,548,
  	1,0,0,0,102,104,3,2,1,0,103,102,1,0,0,0,104,107,1,0,0,0,105,103,1,0,0,
  	0,105,106,1,0,0,0,106,119,1,0,0,0,107,105,1,0,0,0,108,111,3,4,2,0,109,
  	111,3,26,13,0,110,108,1,0,0,0,110,109,1,0,0,0,111,113,1,0,0,0,112,114,
  	3,2,1,0,113,112,1,0,0,0,114,115,1,0,0,0,115,113,1,0,0,0,115,116,1,0,0,
  	0,116,118,1,0,0,0,117,110,1,0,0,0,118,121,1,0,0,0,119,117,1,0,0,0,119,
  	120,1,0,0,0,120,124,1,0,0,0,121,119,1,0,0,0,122,125,3,4,2,0,123,125,3,
  	26,13,0,124,122,1,0,0,0,124,123,1,0,0,0,124,125,1,0,0,0,125,126,1,0,0,
  	0,126,127,5,0,0,1,127,1,1,0,0,0,128,130,5,56,0,0,129,128,1,0,0,0,130,
  	131,1,0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,3,1,0,0,0,133,137,3,6,
  	3,0,134,137,3,10,5,0,135,137,3,14,7,0,136,133,1,0,0,0,136,134,1,0,0,0,
  	136,135,1,0,0,0,137,5,1,0,0,0,138,139,5,10,0,0,139,144,3,8,4,0,140,141,
  	5,48,0,0,141,143,3,8,4,0,142,140,1,0,0,0,143,146,1,0,0,0,144,142,1,0,
  	0,0,144,145,1,0,0,0,145,7,1,0,0,0,146,144,1,0,0,0,147,148,3,16,8,0,148,
  	151,5,53,0,0,149,150,5,12,0,0,150,152,5,53,0,0,151,149,1,0,0,0,151,152,
  	1,0,0,0,152,9,1,0,0,0,153,154,5,11,0,0,154,159,3,12,6,0,155,156,5,48,
  	0,0,156,158,3,12,6,0,157,155,1,0,0,0,158,161,1,0,0,0,159,157,1,0,0,0,
  	159,160,1,0,0,0,160,11,1,0,0,0,161,159,1,0,0,0,162,163,3,74,37,0,163,
  	164,5,12,0,0,164,165,5,53,0,0,165,13,1,0,0,0,166,167,3,16,8,0,167,168,
  	5,53,0,0,168,169,5,49,0,0,169,170,3,74,37,0,170,175,1,0,0,0,171,172,5,
  	53,0,0,172,173,5,49,0,0,173,175,3,74,37,0,174,166,1,0,0,0,174,171,1,0,
  	0,0,175,15,1,0,0,0,176,177,7,0,0,0,177,17,1,0,0,0,178,180,5,32,0,0,179,
  	181,3,2,1,0,180,179,1,0,0,0,180,181,1,0,0,0,181,194,1,0,0,0,182,188,3,
  	72,36,0,183,184,3,2,1,0,184,185,3,72,36,0,185,187,1,0,0,0,186,183,1,0,
  	0,0,187,190,1,0,0,0,188,186,1,0,0,0,188,189,1,0,0,0,189,192,1,0,0,0,190,
  	188,1,0,0,0,191,193,3,2,1,0,192,191,1,0,0,0,192,193,1,0,0,0,193,195,1,
  	0,0,0,194,182,1,0,0,0,194,195,1,0,0,0,195,196,1,0,0,0,196,197,5,33,0,
  	0,197,19,1,0,0,0,198,200,5,32,0,0,199,201,3,2,1,0,200,199,1,0,0,0,200,
  	201,1,0,0,0,201,214,1,0,0,0,202,208,3,40,20,0,203,204,3,2,1,0,204,205,
  	3,40,20,0,205,207,1,0,0,0,206,203,1,0,0,0,207,210,1,0,0,0,208,206,1,0,
  	0,0,208,209,1,0,0,0,209,212,1,0,0,0,210,208,1,0,0,0,211,213,3,2,1,0,212,
  	211,1,0,0,0,212,213,1,0,0,0,213,215,1,0,0,0,214,202,1,0,0,0,214,215,1,
  	0,0,0,215,216,1,0,0,0,216,217,5,33,0,0,217,21,1,0,0,0,218,220,5,32,0,
  	0,219,221,3,2,1,0,220,219,1,0,0,0,220,221,1,0,0,0,221,222,1,0,0,0,222,
  	228,3,60,30,0,223,224,3,2,1,0,224,225,3,60,30,0,225,227,1,0,0,0,226,223,
  	1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,1,0,0,0,229,232,1,0,0,
  	0,230,228,1,0,0,0,231,233,3,2,1,0,232,231,1,0,0,0,232,233,1,0,0,0,233,
  	234,1,0,0,0,234,235,5,33,0,0,235,23,1,0,0,0,236,238,5,32,0,0,237,239,
  	3,2,1,0,238,237,1,0,0,0,238,239,1,0,0,0,239,252,1,0,0,0,240,246,3,48,
  	24,0,241,242,3,2,1,0,242,243,3,48,24,0,243,245,1,0,0,0,244,241,1,0,0,
  	0,245,248,1,0,0,0,246,244,1,0,0,0,246,247,1,0,0,0,247,250,1,0,0,0,248,
  	246,1,0,0,0,249,251,3,2,1,0,250,249,1,0,0,0,250,251,1,0,0,0,251,253,1,
  	0,0,0,252,240,1,0,0,0,252,253,1,0,0,0,253,254,1,0,0,0,254,255,5,33,0,
  	0,255,25,1,0,0,0,256,263,3,28,14,0,257,263,3,30,15,0,258,263,3,32,16,
  	0,259,263,3,34,17,0,260,263,3,36,18,0,261,263,3,38,19,0,262,256,1,0,0,
  	0,262,257,1,0,0,0,262,258,1,0,0,0,262,259,1,0,0,0,262,260,1,0,0,0,262,
  	261,1,0,0,0,263,27,1,0,0,0,264,265,5,2,0,0,265,266,5,3,0,0,266,268,3,
  	66,33,0,267,269,3,2,1,0,268,267,1,0,0,0,268,269,1,0,0,0,269,270,1,0,0,
  	0,270,271,3,18,9,0,271,29,1,0,0,0,272,273,5,2,0,0,273,274,5,4,0,0,274,
  	276,3,66,33,0,275,277,3,2,1,0,276,275,1,0,0,0,276,277,1,0,0,0,277,278,
  	1,0,0,0,278,279,3,20,10,0,279,31,1,0,0,0,280,281,5,2,0,0,281,282,5,7,
  	0,0,282,283,3,64,32,0,283,284,5,9,0,0,284,286,3,66,33,0,285,287,3,2,1,
  	0,286,285,1,0,0,0,286,287,1,0,0,0,287,288,1,0,0,0,288,289,3,18,9,0,289,
  	33,1,0,0,0,290,291,5,2,0,0,291,292,5,8,0,0,292,293,3,64,32,0,293,294,
  	5,9,0,0,294,296,3,66,33,0,295,297,3,2,1,0,296,295,1,0,0,0,296,297,1,0,
  	0,0,297,298,1,0,0,0,298,299,3,18,9,0,299,35,1,0,0,0,300,301,5,2,0,0,301,
  	302,5,6,0,0,302,304,3,66,33,0,303,305,3,2,1,0,304,303,1,0,0,0,304,305,
  	1,0,0,0,305,306,1,0,0,0,306,307,3,22,11,0,307,37,1,0,0,0,308,309,5,2,
  	0,0,309,310,5,5,0,0,310,311,5,53,0,0,311,313,5,46,0,0,312,314,3,44,22,
  	0,313,312,1,0,0,0,313,314,1,0,0,0,314,315,1,0,0,0,315,318,5,47,0,0,316,
  	317,5,34,0,0,317,319,3,16,8,0,318,316,1,0,0,0,318,319,1,0,0,0,319,321,
  	1,0,0,0,320,322,3,2,1,0,321,320,1,0,0,0,321,322,1,0,0,0,322,323,1,0,0,
  	0,323,324,3,24,12,0,324,39,1,0,0,0,325,326,3,42,21,0,326,327,5,49,0,0,
  	327,328,3,74,37,0,328,41,1,0,0,0,329,330,5,17,0,0,330,331,5,45,0,0,331,
  	336,5,53,0,0,332,333,5,52,0,0,333,334,5,45,0,0,334,336,5,53,0,0,335,329,
  	1,0,0,0,335,332,1,0,0,0,336,43,1,0,0,0,337,342,3,46,23,0,338,339,5,48,
  	0,0,339,341,3,46,23,0,340,338,1,0,0,0,341,344,1,0,0,0,342,340,1,0,0,0,
  	342,343,1,0,0,0,343,45,1,0,0,0,344,342,1,0,0,0,345,346,5,53,0,0,346,347,
  	5,1,0,0,347,348,3,16,8,0,348,47,1,0,0,0,349,350,3,16,8,0,350,351,5,53,
  	0,0,351,352,5,49,0,0,352,353,3,74,37,0,353,363,1,0,0,0,354,355,5,53,0,
  	0,355,356,5,49,0,0,356,363,3,74,37,0,357,363,3,50,25,0,358,363,3,58,29,
  	0,359,363,3,74,37,0,360,361,5,24,0,0,361,363,3,74,37,0,362,349,1,0,0,
  	0,362,354,1,0,0,0,362,357,1,0,0,0,362,358,1,0,0,0,362,359,1,0,0,0,362,
  	360,1,0,0,0,363,49,1,0,0,0,364,371,3,52,26,0,365,367,3,2,1,0,366,365,
  	1,0,0,0,366,367,1,0,0,0,367,368,1,0,0,0,368,370,3,54,27,0,369,366,1,0,
  	0,0,370,373,1,0,0,0,371,369,1,0,0,0,371,372,1,0,0,0,372,378,1,0,0,0,373,
  	371,1,0,0,0,374,376,3,2,1,0,375,374,1,0,0,0,375,376,1,0,0,0,376,377,1,
  	0,0,0,377,379,3,56,28,0,378,375,1,0,0,0,378,379,1,0,0,0,379,51,1,0,0,
  	0,380,381,5,25,0,0,381,383,3,74,37,0,382,384,3,2,1,0,383,382,1,0,0,0,
  	383,384,1,0,0,0,384,385,1,0,0,0,385,386,3,24,12,0,386,53,1,0,0,0,387,
  	388,5,26,0,0,388,390,3,74,37,0,389,391,3,2,1,0,390,389,1,0,0,0,390,391,
  	1,0,0,0,391,392,1,0,0,0,392,393,3,24,12,0,393,55,1,0,0,0,394,396,5,27,
  	0,0,395,397,3,2,1,0,396,395,1,0,0,0,396,397,1,0,0,0,397,398,1,0,0,0,398,
  	399,3,24,12,0,399,57,1,0,0,0,400,401,5,28,0,0,401,402,5,53,0,0,402,403,
  	5,29,0,0,403,405,3,70,35,0,404,406,3,2,1,0,405,404,1,0,0,0,405,406,1,
  	0,0,0,406,407,1,0,0,0,407,408,3,24,12,0,408,59,1,0,0,0,409,410,3,74,37,
  	0,410,411,3,62,31,0,411,61,1,0,0,0,412,413,7,1,0,0,413,63,1,0,0,0,414,
  	415,7,2,0,0,415,65,1,0,0,0,416,421,3,64,32,0,417,418,5,48,0,0,418,420,
  	3,64,32,0,419,417,1,0,0,0,420,423,1,0,0,0,421,419,1,0,0,0,421,422,1,0,
  	0,0,422,426,1,0,0,0,423,421,1,0,0,0,424,426,3,68,34,0,425,416,1,0,0,0,
  	425,424,1,0,0,0,426,67,1,0,0,0,427,428,5,50,0,0,428,429,5,53,0,0,429,
  	69,1,0,0,0,430,433,3,64,32,0,431,433,3,68,34,0,432,430,1,0,0,0,432,431,
  	1,0,0,0,433,71,1,0,0,0,434,435,3,76,38,0,435,73,1,0,0,0,436,437,3,76,
  	38,0,437,75,1,0,0,0,438,443,3,78,39,0,439,440,5,14,0,0,440,442,3,78,39,
  	0,441,439,1,0,0,0,442,445,1,0,0,0,443,441,1,0,0,0,443,444,1,0,0,0,444,
  	77,1,0,0,0,445,443,1,0,0,0,446,451,3,80,40,0,447,448,5,13,0,0,448,450,
  	3,80,40,0,449,447,1,0,0,0,450,453,1,0,0,0,451,449,1,0,0,0,451,452,1,0,
  	0,0,452,79,1,0,0,0,453,451,1,0,0,0,454,455,5,15,0,0,455,458,3,80,40,0,
  	456,458,3,82,41,0,457,454,1,0,0,0,457,456,1,0,0,0,458,81,1,0,0,0,459,
  	463,3,84,42,0,460,461,3,96,48,0,461,462,3,84,42,0,462,464,1,0,0,0,463,
  	460,1,0,0,0,463,464,1,0,0,0,464,83,1,0,0,0,465,471,3,86,43,0,466,467,
  	3,98,49,0,467,468,3,86,43,0,468,470,1,0,0,0,469,466,1,0,0,0,470,473,1,
  	0,0,0,471,469,1,0,0,0,471,472,1,0,0,0,472,85,1,0,0,0,473,471,1,0,0,0,
  	474,480,3,88,44,0,475,476,3,100,50,0,476,477,3,88,44,0,477,479,1,0,0,
  	0,478,475,1,0,0,0,479,482,1,0,0,0,480,478,1,0,0,0,480,481,1,0,0,0,481,
  	87,1,0,0,0,482,480,1,0,0,0,483,484,5,36,0,0,484,487,3,88,44,0,485,487,
  	3,90,45,0,486,483,1,0,0,0,486,485,1,0,0,0,487,89,1,0,0,0,488,500,5,51,
  	0,0,489,500,5,52,0,0,490,500,5,16,0,0,491,500,5,17,0,0,492,500,3,92,46,
  	0,493,500,3,94,47,0,494,495,5,46,0,0,495,496,3,74,37,0,496,497,5,47,0,
  	0,497,500,1,0,0,0,498,500,5,53,0,0,499,488,1,0,0,0,499,489,1,0,0,0,499,
  	490,1,0,0,0,499,491,1,0,0,0,499,492,1,0,0,0,499,493,1,0,0,0,499,494,1,
  	0,0,0,499,498,1,0,0,0,500,91,1,0,0,0,501,502,5,53,0,0,502,511,5,46,0,
  	0,503,508,3,74,37,0,504,505,5,48,0,0,505,507,3,74,37,0,506,504,1,0,0,
  	0,507,510,1,0,0,0,508,506,1,0,0,0,508,509,1,0,0,0,509,512,1,0,0,0,510,
  	508,1,0,0,0,511,503,1,0,0,0,511,512,1,0,0,0,512,513,1,0,0,0,513,514,5,
  	47,0,0,514,93,1,0,0,0,515,516,5,17,0,0,516,517,5,45,0,0,517,543,5,53,
  	0,0,518,519,5,52,0,0,519,520,5,45,0,0,520,543,5,53,0,0,521,522,5,53,0,
  	0,522,523,5,45,0,0,523,543,5,53,0,0,524,525,5,17,0,0,525,526,5,45,0,0,
  	526,527,5,46,0,0,527,528,3,74,37,0,528,529,5,47,0,0,529,543,1,0,0,0,530,
  	531,5,52,0,0,531,532,5,45,0,0,532,533,5,46,0,0,533,534,3,74,37,0,534,
  	535,5,47,0,0,535,543,1,0,0,0,536,537,5,53,0,0,537,538,5,45,0,0,538,539,
  	5,46,0,0,539,540,3,74,37,0,540,541,5,47,0,0,541,543,1,0,0,0,542,515,1,
  	0,0,0,542,518,1,0,0,0,542,521,1,0,0,0,542,524,1,0,0,0,542,530,1,0,0,0,
  	542,536,1,0,0,0,543,95,1,0,0,0,544,545,7,3,0,0,545,97,1,0,0,0,546,547,
  	7,4,0,0,547,99,1,0,0,0,548,549,7,5,0,0,549,101,1,0,0,0,60,105,110,115,
  	119,124,131,136,144,151,159,174,180,188,192,194,200,208,212,214,220,228,
  	232,238,246,250,252,262,268,276,286,296,304,313,318,321,335,342,362,366,
  	371,375,378,383,390,396,405,421,425,432,443,451,457,463,471,480,486,499,
  	508,511,542
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

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::ProgramContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ProgramContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::DeclarationContext *> PostAnvilParser::ProgramContext::declaration() {
  return getRuleContexts<PostAnvilParser::DeclarationContext>();
}

PostAnvilParser::DeclarationContext* PostAnvilParser::ProgramContext::declaration(size_t i) {
  return getRuleContext<PostAnvilParser::DeclarationContext>(i);
}

std::vector<PostAnvilParser::Rule_Context *> PostAnvilParser::ProgramContext::rule_() {
  return getRuleContexts<PostAnvilParser::Rule_Context>();
}

PostAnvilParser::Rule_Context* PostAnvilParser::ProgramContext::rule_(size_t i) {
  return getRuleContext<PostAnvilParser::Rule_Context>(i);
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


std::any PostAnvilParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::NEWLINE) {
      setState(102);
      newlines();
      setState(107);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(119);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(110);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PostAnvilParser::IMPORT:
          case PostAnvilParser::EXPORT:
          case PostAnvilParser::NUM:
          case PostAnvilParser::STR:
          case PostAnvilParser::BOOL:
          case PostAnvilParser::INST:
          case PostAnvilParser::ANY:
          case PostAnvilParser::IDENTIFIER: {
            setState(108);
            declaration();
            break;
          }

          case PostAnvilParser::RULE: {
            setState(109);
            rule_();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(113); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(112);
          newlines();
          setState(115); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == PostAnvilParser::NEWLINE); 
      }
      setState(121);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
    setState(124);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::IMPORT:
      case PostAnvilParser::EXPORT:
      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::INST:
      case PostAnvilParser::ANY:
      case PostAnvilParser::IDENTIFIER: {
        setState(122);
        declaration();
        break;
      }

      case PostAnvilParser::RULE: {
        setState(123);
        rule_();
        break;
      }

      case PostAnvilParser::EOF: {
        break;
      }

    default:
      break;
    }
    setState(126);
    match(PostAnvilParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NewlinesContext ------------------------------------------------------------------

PostAnvilParser::NewlinesContext::NewlinesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> PostAnvilParser::NewlinesContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::NewlinesContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
}


size_t PostAnvilParser::NewlinesContext::getRuleIndex() const {
  return PostAnvilParser::RuleNewlines;
}

void PostAnvilParser::NewlinesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNewlines(this);
}

void PostAnvilParser::NewlinesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNewlines(this);
}


std::any PostAnvilParser::NewlinesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitNewlines(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::newlines() {
  NewlinesContext *_localctx = _tracker.createInstance<NewlinesContext>(_ctx, getState());
  enterRule(_localctx, 2, PostAnvilParser::RuleNewlines);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(128);
              match(PostAnvilParser::NEWLINE);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(131); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

PostAnvilParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::ImportDefContext* PostAnvilParser::DeclarationContext::importDef() {
  return getRuleContext<PostAnvilParser::ImportDefContext>(0);
}

PostAnvilParser::ExportDefContext* PostAnvilParser::DeclarationContext::exportDef() {
  return getRuleContext<PostAnvilParser::ExportDefContext>(0);
}

PostAnvilParser::GlobalDefContext* PostAnvilParser::DeclarationContext::globalDef() {
  return getRuleContext<PostAnvilParser::GlobalDefContext>(0);
}


size_t PostAnvilParser::DeclarationContext::getRuleIndex() const {
  return PostAnvilParser::RuleDeclaration;
}

void PostAnvilParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void PostAnvilParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any PostAnvilParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::DeclarationContext* PostAnvilParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, PostAnvilParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(133);
        importDef();
        break;
      }

      case PostAnvilParser::EXPORT: {
        enterOuterAlt(_localctx, 2);
        setState(134);
        exportDef();
        break;
      }

      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::INST:
      case PostAnvilParser::ANY:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(135);
        globalDef();
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

//----------------- ImportDefContext ------------------------------------------------------------------

PostAnvilParser::ImportDefContext::ImportDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ImportDefContext::IMPORT() {
  return getToken(PostAnvilParser::IMPORT, 0);
}

std::vector<PostAnvilParser::ImportItemContext *> PostAnvilParser::ImportDefContext::importItem() {
  return getRuleContexts<PostAnvilParser::ImportItemContext>();
}

PostAnvilParser::ImportItemContext* PostAnvilParser::ImportDefContext::importItem(size_t i) {
  return getRuleContext<PostAnvilParser::ImportItemContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::ImportDefContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::ImportDefContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}


size_t PostAnvilParser::ImportDefContext::getRuleIndex() const {
  return PostAnvilParser::RuleImportDef;
}

void PostAnvilParser::ImportDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportDef(this);
}

void PostAnvilParser::ImportDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportDef(this);
}


std::any PostAnvilParser::ImportDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitImportDef(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ImportDefContext* PostAnvilParser::importDef() {
  ImportDefContext *_localctx = _tracker.createInstance<ImportDefContext>(_ctx, getState());
  enterRule(_localctx, 6, PostAnvilParser::RuleImportDef);
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
    match(PostAnvilParser::IMPORT);
    setState(139);
    importItem();
    setState(144);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(140);
      match(PostAnvilParser::COMMA);
      setState(141);
      importItem();
      setState(146);
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

//----------------- ImportItemContext ------------------------------------------------------------------

PostAnvilParser::ImportItemContext::ImportItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::TypeContext* PostAnvilParser::ImportItemContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> PostAnvilParser::ImportItemContext::IDENTIFIER() {
  return getTokens(PostAnvilParser::IDENTIFIER);
}

tree::TerminalNode* PostAnvilParser::ImportItemContext::IDENTIFIER(size_t i) {
  return getToken(PostAnvilParser::IDENTIFIER, i);
}

tree::TerminalNode* PostAnvilParser::ImportItemContext::AS() {
  return getToken(PostAnvilParser::AS, 0);
}


size_t PostAnvilParser::ImportItemContext::getRuleIndex() const {
  return PostAnvilParser::RuleImportItem;
}

void PostAnvilParser::ImportItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportItem(this);
}

void PostAnvilParser::ImportItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportItem(this);
}


std::any PostAnvilParser::ImportItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitImportItem(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ImportItemContext* PostAnvilParser::importItem() {
  ImportItemContext *_localctx = _tracker.createInstance<ImportItemContext>(_ctx, getState());
  enterRule(_localctx, 8, PostAnvilParser::RuleImportItem);
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
    setState(147);
    type();
    setState(148);
    antlrcpp::downCast<ImportItemContext *>(_localctx)->host = match(PostAnvilParser::IDENTIFIER);
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::AS) {
      setState(149);
      match(PostAnvilParser::AS);
      setState(150);
      antlrcpp::downCast<ImportItemContext *>(_localctx)->local = match(PostAnvilParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExportDefContext ------------------------------------------------------------------

PostAnvilParser::ExportDefContext::ExportDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ExportDefContext::EXPORT() {
  return getToken(PostAnvilParser::EXPORT, 0);
}

std::vector<PostAnvilParser::ExportItemContext *> PostAnvilParser::ExportDefContext::exportItem() {
  return getRuleContexts<PostAnvilParser::ExportItemContext>();
}

PostAnvilParser::ExportItemContext* PostAnvilParser::ExportDefContext::exportItem(size_t i) {
  return getRuleContext<PostAnvilParser::ExportItemContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::ExportDefContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::ExportDefContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}


size_t PostAnvilParser::ExportDefContext::getRuleIndex() const {
  return PostAnvilParser::RuleExportDef;
}

void PostAnvilParser::ExportDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportDef(this);
}

void PostAnvilParser::ExportDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportDef(this);
}


std::any PostAnvilParser::ExportDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitExportDef(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ExportDefContext* PostAnvilParser::exportDef() {
  ExportDefContext *_localctx = _tracker.createInstance<ExportDefContext>(_ctx, getState());
  enterRule(_localctx, 10, PostAnvilParser::RuleExportDef);
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
    setState(153);
    match(PostAnvilParser::EXPORT);
    setState(154);
    exportItem();
    setState(159);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(155);
      match(PostAnvilParser::COMMA);
      setState(156);
      exportItem();
      setState(161);
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

//----------------- ExportItemContext ------------------------------------------------------------------

PostAnvilParser::ExportItemContext::ExportItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::ExprContext* PostAnvilParser::ExportItemContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::ExportItemContext::AS() {
  return getToken(PostAnvilParser::AS, 0);
}

tree::TerminalNode* PostAnvilParser::ExportItemContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}


size_t PostAnvilParser::ExportItemContext::getRuleIndex() const {
  return PostAnvilParser::RuleExportItem;
}

void PostAnvilParser::ExportItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExportItem(this);
}

void PostAnvilParser::ExportItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExportItem(this);
}


std::any PostAnvilParser::ExportItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitExportItem(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ExportItemContext* PostAnvilParser::exportItem() {
  ExportItemContext *_localctx = _tracker.createInstance<ExportItemContext>(_ctx, getState());
  enterRule(_localctx, 12, PostAnvilParser::RuleExportItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    expr();
    setState(163);
    match(PostAnvilParser::AS);
    setState(164);
    antlrcpp::downCast<ExportItemContext *>(_localctx)->host = match(PostAnvilParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalDefContext ------------------------------------------------------------------

PostAnvilParser::GlobalDefContext::GlobalDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::TypeContext* PostAnvilParser::GlobalDefContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}

tree::TerminalNode* PostAnvilParser::GlobalDefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::GlobalDefContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::GlobalDefContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}


size_t PostAnvilParser::GlobalDefContext::getRuleIndex() const {
  return PostAnvilParser::RuleGlobalDef;
}

void PostAnvilParser::GlobalDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGlobalDef(this);
}

void PostAnvilParser::GlobalDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGlobalDef(this);
}


std::any PostAnvilParser::GlobalDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitGlobalDef(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::GlobalDefContext* PostAnvilParser::globalDef() {
  GlobalDefContext *_localctx = _tracker.createInstance<GlobalDefContext>(_ctx, getState());
  enterRule(_localctx, 14, PostAnvilParser::RuleGlobalDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(174);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::INST:
      case PostAnvilParser::ANY: {
        enterOuterAlt(_localctx, 1);
        setState(166);
        type();
        setState(167);
        match(PostAnvilParser::IDENTIFIER);
        setState(168);
        match(PostAnvilParser::ASSIGN);
        setState(169);
        expr();
        break;
      }

      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(171);
        match(PostAnvilParser::IDENTIFIER);
        setState(172);
        match(PostAnvilParser::ASSIGN);
        setState(173);
        expr();
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

//----------------- TypeContext ------------------------------------------------------------------

PostAnvilParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::TypeContext::NUM() {
  return getToken(PostAnvilParser::NUM, 0);
}

tree::TerminalNode* PostAnvilParser::TypeContext::STR() {
  return getToken(PostAnvilParser::STR, 0);
}

tree::TerminalNode* PostAnvilParser::TypeContext::BOOL() {
  return getToken(PostAnvilParser::BOOL, 0);
}

tree::TerminalNode* PostAnvilParser::TypeContext::INST() {
  return getToken(PostAnvilParser::INST, 0);
}

tree::TerminalNode* PostAnvilParser::TypeContext::ANY() {
  return getToken(PostAnvilParser::ANY, 0);
}


size_t PostAnvilParser::TypeContext::getRuleIndex() const {
  return PostAnvilParser::RuleType;
}

void PostAnvilParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void PostAnvilParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}


std::any PostAnvilParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::TypeContext* PostAnvilParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 16, PostAnvilParser::RuleType);
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
    setState(176);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8126464) != 0))) {
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

//----------------- Condition_blockContext ------------------------------------------------------------------

PostAnvilParser::Condition_blockContext::Condition_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Condition_blockContext::LCURLY() {
  return getToken(PostAnvilParser::LCURLY, 0);
}

tree::TerminalNode* PostAnvilParser::Condition_blockContext::RCURLY() {
  return getToken(PostAnvilParser::RCURLY, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Condition_blockContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Condition_blockContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::Bool_exprContext *> PostAnvilParser::Condition_blockContext::bool_expr() {
  return getRuleContexts<PostAnvilParser::Bool_exprContext>();
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::Condition_blockContext::bool_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Bool_exprContext>(i);
}


size_t PostAnvilParser::Condition_blockContext::getRuleIndex() const {
  return PostAnvilParser::RuleCondition_block;
}

void PostAnvilParser::Condition_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition_block(this);
}

void PostAnvilParser::Condition_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition_block(this);
}


std::any PostAnvilParser::Condition_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitCondition_block(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Condition_blockContext* PostAnvilParser::condition_block() {
  Condition_blockContext *_localctx = _tracker.createInstance<Condition_blockContext>(_ctx, getState());
  enterRule(_localctx, 18, PostAnvilParser::RuleCondition_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(178);
    match(PostAnvilParser::LCURLY);
    setState(180);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(179);
      newlines();
    }
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15833036159680512) != 0)) {
      setState(182);
      bool_expr();
      setState(188);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(183);
          newlines();
          setState(184);
          bool_expr(); 
        }
        setState(190);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
      }
      setState(192);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PostAnvilParser::NEWLINE) {
        setState(191);
        newlines();
      }
    }
    setState(196);
    match(PostAnvilParser::RCURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_blockContext ------------------------------------------------------------------

PostAnvilParser::Attr_blockContext::Attr_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Attr_blockContext::LCURLY() {
  return getToken(PostAnvilParser::LCURLY, 0);
}

tree::TerminalNode* PostAnvilParser::Attr_blockContext::RCURLY() {
  return getToken(PostAnvilParser::RCURLY, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Attr_blockContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Attr_blockContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::Attr_defContext *> PostAnvilParser::Attr_blockContext::attr_def() {
  return getRuleContexts<PostAnvilParser::Attr_defContext>();
}

PostAnvilParser::Attr_defContext* PostAnvilParser::Attr_blockContext::attr_def(size_t i) {
  return getRuleContext<PostAnvilParser::Attr_defContext>(i);
}


size_t PostAnvilParser::Attr_blockContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttr_block;
}

void PostAnvilParser::Attr_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_block(this);
}

void PostAnvilParser::Attr_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_block(this);
}


std::any PostAnvilParser::Attr_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAttr_block(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Attr_blockContext* PostAnvilParser::attr_block() {
  Attr_blockContext *_localctx = _tracker.createInstance<Attr_blockContext>(_ctx, getState());
  enterRule(_localctx, 20, PostAnvilParser::RuleAttr_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(198);
    match(PostAnvilParser::LCURLY);
    setState(200);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(199);
      newlines();
    }
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::SELF

    || _la == PostAnvilParser::STRING) {
      setState(202);
      attr_def();
      setState(208);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(203);
          newlines();
          setState(204);
          attr_def(); 
        }
        setState(210);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
      }
      setState(212);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PostAnvilParser::NEWLINE) {
        setState(211);
        newlines();
      }
    }
    setState(216);
    match(PostAnvilParser::RCURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sort_blockContext ------------------------------------------------------------------

PostAnvilParser::Sort_blockContext::Sort_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Sort_blockContext::LCURLY() {
  return getToken(PostAnvilParser::LCURLY, 0);
}

std::vector<PostAnvilParser::Sort_keyContext *> PostAnvilParser::Sort_blockContext::sort_key() {
  return getRuleContexts<PostAnvilParser::Sort_keyContext>();
}

PostAnvilParser::Sort_keyContext* PostAnvilParser::Sort_blockContext::sort_key(size_t i) {
  return getRuleContext<PostAnvilParser::Sort_keyContext>(i);
}

tree::TerminalNode* PostAnvilParser::Sort_blockContext::RCURLY() {
  return getToken(PostAnvilParser::RCURLY, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Sort_blockContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Sort_blockContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}


size_t PostAnvilParser::Sort_blockContext::getRuleIndex() const {
  return PostAnvilParser::RuleSort_block;
}

void PostAnvilParser::Sort_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSort_block(this);
}

void PostAnvilParser::Sort_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSort_block(this);
}


std::any PostAnvilParser::Sort_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitSort_block(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Sort_blockContext* PostAnvilParser::sort_block() {
  Sort_blockContext *_localctx = _tracker.createInstance<Sort_blockContext>(_ctx, getState());
  enterRule(_localctx, 22, PostAnvilParser::RuleSort_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(218);
    match(PostAnvilParser::LCURLY);
    setState(220);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(219);
      newlines();
    }
    setState(222);
    sort_key();
    setState(228);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(223);
        newlines();
        setState(224);
        sort_key(); 
      }
      setState(230);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
    setState(232);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(231);
      newlines();
    }
    setState(234);
    match(PostAnvilParser::RCURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Stmt_blockContext ------------------------------------------------------------------

PostAnvilParser::Stmt_blockContext::Stmt_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Stmt_blockContext::LCURLY() {
  return getToken(PostAnvilParser::LCURLY, 0);
}

tree::TerminalNode* PostAnvilParser::Stmt_blockContext::RCURLY() {
  return getToken(PostAnvilParser::RCURLY, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Stmt_blockContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Stmt_blockContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::StatementContext *> PostAnvilParser::Stmt_blockContext::statement() {
  return getRuleContexts<PostAnvilParser::StatementContext>();
}

PostAnvilParser::StatementContext* PostAnvilParser::Stmt_blockContext::statement(size_t i) {
  return getRuleContext<PostAnvilParser::StatementContext>(i);
}


size_t PostAnvilParser::Stmt_blockContext::getRuleIndex() const {
  return PostAnvilParser::RuleStmt_block;
}

void PostAnvilParser::Stmt_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmt_block(this);
}

void PostAnvilParser::Stmt_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmt_block(this);
}


std::any PostAnvilParser::Stmt_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmt_block(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::stmt_block() {
  Stmt_blockContext *_localctx = _tracker.createInstance<Stmt_blockContext>(_ctx, getState());
  enterRule(_localctx, 24, PostAnvilParser::RuleStmt_block);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(236);
    match(PostAnvilParser::LCURLY);
    setState(238);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(237);
      newlines();
    }
    setState(252);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15833036486574080) != 0)) {
      setState(240);
      statement();
      setState(246);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(241);
          newlines();
          setState(242);
          statement(); 
        }
        setState(248);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
      }
      setState(250);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PostAnvilParser::NEWLINE) {
        setState(249);
        newlines();
      }
    }
    setState(254);
    match(PostAnvilParser::RCURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Rule_Context ------------------------------------------------------------------

PostAnvilParser::Rule_Context::Rule_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::Filter_ruleContext* PostAnvilParser::Rule_Context::filter_rule() {
  return getRuleContext<PostAnvilParser::Filter_ruleContext>(0);
}

PostAnvilParser::Attr_ruleContext* PostAnvilParser::Rule_Context::attr_rule() {
  return getRuleContext<PostAnvilParser::Attr_ruleContext>(0);
}

PostAnvilParser::Group_ruleContext* PostAnvilParser::Rule_Context::group_rule() {
  return getRuleContext<PostAnvilParser::Group_ruleContext>(0);
}

PostAnvilParser::Append_ruleContext* PostAnvilParser::Rule_Context::append_rule() {
  return getRuleContext<PostAnvilParser::Append_ruleContext>(0);
}

PostAnvilParser::Sort_ruleContext* PostAnvilParser::Rule_Context::sort_rule() {
  return getRuleContext<PostAnvilParser::Sort_ruleContext>(0);
}

PostAnvilParser::Func_ruleContext* PostAnvilParser::Rule_Context::func_rule() {
  return getRuleContext<PostAnvilParser::Func_ruleContext>(0);
}


size_t PostAnvilParser::Rule_Context::getRuleIndex() const {
  return PostAnvilParser::RuleRule_;
}

void PostAnvilParser::Rule_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRule_(this);
}

void PostAnvilParser::Rule_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRule_(this);
}


std::any PostAnvilParser::Rule_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitRule_(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Rule_Context* PostAnvilParser::rule_() {
  Rule_Context *_localctx = _tracker.createInstance<Rule_Context>(_ctx, getState());
  enterRule(_localctx, 26, PostAnvilParser::RuleRule_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(256);
      filter_rule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(257);
      attr_rule();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(258);
      group_rule();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(259);
      append_rule();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(260);
      sort_rule();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(261);
      func_rule();
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

//----------------- Filter_ruleContext ------------------------------------------------------------------

PostAnvilParser::Filter_ruleContext::Filter_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Filter_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Filter_ruleContext::FILTER() {
  return getToken(PostAnvilParser::FILTER, 0);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::Filter_ruleContext::class_selector() {
  return getRuleContext<PostAnvilParser::Class_selectorContext>(0);
}

PostAnvilParser::Condition_blockContext* PostAnvilParser::Filter_ruleContext::condition_block() {
  return getRuleContext<PostAnvilParser::Condition_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Filter_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::Filter_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleFilter_rule;
}

void PostAnvilParser::Filter_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilter_rule(this);
}

void PostAnvilParser::Filter_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilter_rule(this);
}


std::any PostAnvilParser::Filter_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFilter_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Filter_ruleContext* PostAnvilParser::filter_rule() {
  Filter_ruleContext *_localctx = _tracker.createInstance<Filter_ruleContext>(_ctx, getState());
  enterRule(_localctx, 28, PostAnvilParser::RuleFilter_rule);
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
    setState(264);
    match(PostAnvilParser::RULE);
    setState(265);
    match(PostAnvilParser::FILTER);
    setState(266);
    class_selector();
    setState(268);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(267);
      newlines();
    }
    setState(270);
    condition_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_ruleContext ------------------------------------------------------------------

PostAnvilParser::Attr_ruleContext::Attr_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Attr_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Attr_ruleContext::ATTR() {
  return getToken(PostAnvilParser::ATTR, 0);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::Attr_ruleContext::class_selector() {
  return getRuleContext<PostAnvilParser::Class_selectorContext>(0);
}

PostAnvilParser::Attr_blockContext* PostAnvilParser::Attr_ruleContext::attr_block() {
  return getRuleContext<PostAnvilParser::Attr_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Attr_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::Attr_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttr_rule;
}

void PostAnvilParser::Attr_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_rule(this);
}

void PostAnvilParser::Attr_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_rule(this);
}


std::any PostAnvilParser::Attr_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAttr_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Attr_ruleContext* PostAnvilParser::attr_rule() {
  Attr_ruleContext *_localctx = _tracker.createInstance<Attr_ruleContext>(_ctx, getState());
  enterRule(_localctx, 30, PostAnvilParser::RuleAttr_rule);
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
    setState(272);
    match(PostAnvilParser::RULE);
    setState(273);
    match(PostAnvilParser::ATTR);
    setState(274);
    class_selector();
    setState(276);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(275);
      newlines();
    }
    setState(278);
    attr_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Group_ruleContext ------------------------------------------------------------------

PostAnvilParser::Group_ruleContext::Group_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::GROUP() {
  return getToken(PostAnvilParser::GROUP, 0);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Group_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::FROM() {
  return getToken(PostAnvilParser::FROM, 0);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::Group_ruleContext::class_selector() {
  return getRuleContext<PostAnvilParser::Class_selectorContext>(0);
}

PostAnvilParser::Condition_blockContext* PostAnvilParser::Group_ruleContext::condition_block() {
  return getRuleContext<PostAnvilParser::Condition_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Group_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::Group_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleGroup_rule;
}

void PostAnvilParser::Group_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroup_rule(this);
}

void PostAnvilParser::Group_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroup_rule(this);
}


std::any PostAnvilParser::Group_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitGroup_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Group_ruleContext* PostAnvilParser::group_rule() {
  Group_ruleContext *_localctx = _tracker.createInstance<Group_ruleContext>(_ctx, getState());
  enterRule(_localctx, 32, PostAnvilParser::RuleGroup_rule);
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
    setState(280);
    match(PostAnvilParser::RULE);
    setState(281);
    match(PostAnvilParser::GROUP);
    setState(282);
    class_expr();
    setState(283);
    match(PostAnvilParser::FROM);
    setState(284);
    class_selector();
    setState(286);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(285);
      newlines();
    }
    setState(288);
    condition_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Append_ruleContext ------------------------------------------------------------------

PostAnvilParser::Append_ruleContext::Append_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::APPEND() {
  return getToken(PostAnvilParser::APPEND, 0);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Append_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::FROM() {
  return getToken(PostAnvilParser::FROM, 0);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::Append_ruleContext::class_selector() {
  return getRuleContext<PostAnvilParser::Class_selectorContext>(0);
}

PostAnvilParser::Condition_blockContext* PostAnvilParser::Append_ruleContext::condition_block() {
  return getRuleContext<PostAnvilParser::Condition_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Append_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::Append_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleAppend_rule;
}

void PostAnvilParser::Append_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAppend_rule(this);
}

void PostAnvilParser::Append_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAppend_rule(this);
}


std::any PostAnvilParser::Append_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAppend_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Append_ruleContext* PostAnvilParser::append_rule() {
  Append_ruleContext *_localctx = _tracker.createInstance<Append_ruleContext>(_ctx, getState());
  enterRule(_localctx, 34, PostAnvilParser::RuleAppend_rule);
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
    setState(290);
    match(PostAnvilParser::RULE);
    setState(291);
    match(PostAnvilParser::APPEND);
    setState(292);
    class_expr();
    setState(293);
    match(PostAnvilParser::FROM);
    setState(294);
    class_selector();
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(295);
      newlines();
    }
    setState(298);
    condition_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sort_ruleContext ------------------------------------------------------------------

PostAnvilParser::Sort_ruleContext::Sort_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Sort_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Sort_ruleContext::SORT() {
  return getToken(PostAnvilParser::SORT, 0);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::Sort_ruleContext::class_selector() {
  return getRuleContext<PostAnvilParser::Class_selectorContext>(0);
}

PostAnvilParser::Sort_blockContext* PostAnvilParser::Sort_ruleContext::sort_block() {
  return getRuleContext<PostAnvilParser::Sort_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Sort_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::Sort_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleSort_rule;
}

void PostAnvilParser::Sort_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSort_rule(this);
}

void PostAnvilParser::Sort_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSort_rule(this);
}


std::any PostAnvilParser::Sort_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitSort_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Sort_ruleContext* PostAnvilParser::sort_rule() {
  Sort_ruleContext *_localctx = _tracker.createInstance<Sort_ruleContext>(_ctx, getState());
  enterRule(_localctx, 36, PostAnvilParser::RuleSort_rule);
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
    setState(300);
    match(PostAnvilParser::RULE);
    setState(301);
    match(PostAnvilParser::SORT);
    setState(302);
    class_selector();
    setState(304);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(303);
      newlines();
    }
    setState(306);
    sort_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_ruleContext ------------------------------------------------------------------

PostAnvilParser::Func_ruleContext::Func_ruleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::RULE() {
  return getToken(PostAnvilParser::RULE, 0);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::FUNC() {
  return getToken(PostAnvilParser::FUNC, 0);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::Func_ruleContext::stmt_block() {
  return getRuleContext<PostAnvilParser::Stmt_blockContext>(0);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::Typed_paramsContext* PostAnvilParser::Func_ruleContext::typed_params() {
  return getRuleContext<PostAnvilParser::Typed_paramsContext>(0);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::ARROW() {
  return getToken(PostAnvilParser::ARROW, 0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Func_ruleContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}

PostAnvilParser::TypeContext* PostAnvilParser::Func_ruleContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}


size_t PostAnvilParser::Func_ruleContext::getRuleIndex() const {
  return PostAnvilParser::RuleFunc_rule;
}

void PostAnvilParser::Func_ruleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_rule(this);
}

void PostAnvilParser::Func_ruleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_rule(this);
}


std::any PostAnvilParser::Func_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFunc_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Func_ruleContext* PostAnvilParser::func_rule() {
  Func_ruleContext *_localctx = _tracker.createInstance<Func_ruleContext>(_ctx, getState());
  enterRule(_localctx, 38, PostAnvilParser::RuleFunc_rule);
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
    setState(308);
    match(PostAnvilParser::RULE);
    setState(309);
    match(PostAnvilParser::FUNC);
    setState(310);
    antlrcpp::downCast<Func_ruleContext *>(_localctx)->name = match(PostAnvilParser::IDENTIFIER);
    setState(311);
    match(PostAnvilParser::LPAREN);
    setState(313);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::IDENTIFIER) {
      setState(312);
      typed_params();
    }
    setState(315);
    match(PostAnvilParser::RPAREN);
    setState(318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ARROW) {
      setState(316);
      match(PostAnvilParser::ARROW);
      setState(317);
      antlrcpp::downCast<Func_ruleContext *>(_localctx)->return_type = type();
    }
    setState(321);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(320);
      newlines();
    }
    setState(323);
    stmt_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_defContext ------------------------------------------------------------------

PostAnvilParser::Attr_defContext::Attr_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::Attr_lvalueContext* PostAnvilParser::Attr_defContext::attr_lvalue() {
  return getRuleContext<PostAnvilParser::Attr_lvalueContext>(0);
}

tree::TerminalNode* PostAnvilParser::Attr_defContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::Attr_defContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}


size_t PostAnvilParser::Attr_defContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttr_def;
}

void PostAnvilParser::Attr_defContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAttr_def(this);
}

void PostAnvilParser::Attr_defContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAttr_def(this);
}


std::any PostAnvilParser::Attr_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAttr_def(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Attr_defContext* PostAnvilParser::attr_def() {
  Attr_defContext *_localctx = _tracker.createInstance<Attr_defContext>(_ctx, getState());
  enterRule(_localctx, 40, PostAnvilParser::RuleAttr_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    attr_lvalue();
    setState(326);
    match(PostAnvilParser::ASSIGN);
    setState(327);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Attr_lvalueContext ------------------------------------------------------------------

PostAnvilParser::Attr_lvalueContext::Attr_lvalueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PostAnvilParser::Attr_lvalueContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttr_lvalue;
}

void PostAnvilParser::Attr_lvalueContext::copyFrom(Attr_lvalueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- InstanceAttrDefContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::InstanceAttrDefContext::SELF() {
  return getToken(PostAnvilParser::SELF, 0);
}

tree::TerminalNode* PostAnvilParser::InstanceAttrDefContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::InstanceAttrDefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::InstanceAttrDefContext::InstanceAttrDefContext(Attr_lvalueContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::InstanceAttrDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstanceAttrDef(this);
}
void PostAnvilParser::InstanceAttrDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstanceAttrDef(this);
}

std::any PostAnvilParser::InstanceAttrDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitInstanceAttrDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassAttrDefContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::ClassAttrDefContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
}

tree::TerminalNode* PostAnvilParser::ClassAttrDefContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::ClassAttrDefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::ClassAttrDefContext::ClassAttrDefContext(Attr_lvalueContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::ClassAttrDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassAttrDef(this);
}
void PostAnvilParser::ClassAttrDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassAttrDef(this);
}

std::any PostAnvilParser::ClassAttrDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClassAttrDef(this);
  else
    return visitor->visitChildren(this);
}
PostAnvilParser::Attr_lvalueContext* PostAnvilParser::attr_lvalue() {
  Attr_lvalueContext *_localctx = _tracker.createInstance<Attr_lvalueContext>(_ctx, getState());
  enterRule(_localctx, 42, PostAnvilParser::RuleAttr_lvalue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(335);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(329);
        match(PostAnvilParser::SELF);
        setState(330);
        match(PostAnvilParser::DOT);
        setState(331);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(332);
        match(PostAnvilParser::STRING);
        setState(333);
        match(PostAnvilParser::DOT);
        setState(334);
        match(PostAnvilParser::IDENTIFIER);
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

//----------------- Typed_paramsContext ------------------------------------------------------------------

PostAnvilParser::Typed_paramsContext::Typed_paramsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Typed_paramContext *> PostAnvilParser::Typed_paramsContext::typed_param() {
  return getRuleContexts<PostAnvilParser::Typed_paramContext>();
}

PostAnvilParser::Typed_paramContext* PostAnvilParser::Typed_paramsContext::typed_param(size_t i) {
  return getRuleContext<PostAnvilParser::Typed_paramContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::Typed_paramsContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::Typed_paramsContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}


size_t PostAnvilParser::Typed_paramsContext::getRuleIndex() const {
  return PostAnvilParser::RuleTyped_params;
}

void PostAnvilParser::Typed_paramsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTyped_params(this);
}

void PostAnvilParser::Typed_paramsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTyped_params(this);
}


std::any PostAnvilParser::Typed_paramsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitTyped_params(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Typed_paramsContext* PostAnvilParser::typed_params() {
  Typed_paramsContext *_localctx = _tracker.createInstance<Typed_paramsContext>(_ctx, getState());
  enterRule(_localctx, 44, PostAnvilParser::RuleTyped_params);
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
    setState(337);
    typed_param();
    setState(342);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(338);
      match(PostAnvilParser::COMMA);
      setState(339);
      typed_param();
      setState(344);
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

//----------------- Typed_paramContext ------------------------------------------------------------------

PostAnvilParser::Typed_paramContext::Typed_paramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Typed_paramContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::TypeContext* PostAnvilParser::Typed_paramContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}


size_t PostAnvilParser::Typed_paramContext::getRuleIndex() const {
  return PostAnvilParser::RuleTyped_param;
}

void PostAnvilParser::Typed_paramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTyped_param(this);
}

void PostAnvilParser::Typed_paramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTyped_param(this);
}


std::any PostAnvilParser::Typed_paramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitTyped_param(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Typed_paramContext* PostAnvilParser::typed_param() {
  Typed_paramContext *_localctx = _tracker.createInstance<Typed_paramContext>(_ctx, getState());
  enterRule(_localctx, 46, PostAnvilParser::RuleTyped_param);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_name = match(PostAnvilParser::IDENTIFIER);
    setState(346);
    match(PostAnvilParser::T__0);
    setState(347);
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_type = type();
   
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

//----------------- StmtReturnContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::StmtReturnContext::RETURN() {
  return getToken(PostAnvilParser::RETURN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::StmtReturnContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::StmtReturnContext::StmtReturnContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtReturn(this);
}
void PostAnvilParser::StmtReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtReturn(this);
}

std::any PostAnvilParser::StmtReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtReturn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtExprContext ------------------------------------------------------------------

PostAnvilParser::ExprContext* PostAnvilParser::StmtExprContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::StmtExprContext::StmtExprContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtExpr(this);
}
void PostAnvilParser::StmtExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtExpr(this);
}

std::any PostAnvilParser::StmtExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtVarDefContext ------------------------------------------------------------------

PostAnvilParser::TypeContext* PostAnvilParser::StmtVarDefContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}

tree::TerminalNode* PostAnvilParser::StmtVarDefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::StmtVarDefContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::StmtVarDefContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::StmtVarDefContext::StmtVarDefContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtVarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtVarDef(this);
}
void PostAnvilParser::StmtVarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtVarDef(this);
}

std::any PostAnvilParser::StmtVarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtVarDef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtForContext ------------------------------------------------------------------

PostAnvilParser::ForStmtContext* PostAnvilParser::StmtForContext::forStmt() {
  return getRuleContext<PostAnvilParser::ForStmtContext>(0);
}

PostAnvilParser::StmtForContext::StmtForContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtForContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtFor(this);
}
void PostAnvilParser::StmtForContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtFor(this);
}

std::any PostAnvilParser::StmtForContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtFor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtAssignContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::StmtAssignContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::StmtAssignContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::StmtAssignContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::StmtAssignContext::StmtAssignContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtAssign(this);
}
void PostAnvilParser::StmtAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtAssign(this);
}

std::any PostAnvilParser::StmtAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtAssign(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StmtIfContext ------------------------------------------------------------------

PostAnvilParser::IfStmtContext* PostAnvilParser::StmtIfContext::ifStmt() {
  return getRuleContext<PostAnvilParser::IfStmtContext>(0);
}

PostAnvilParser::StmtIfContext::StmtIfContext(StatementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::StmtIfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStmtIf(this);
}
void PostAnvilParser::StmtIfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStmtIf(this);
}

std::any PostAnvilParser::StmtIfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitStmtIf(this);
  else
    return visitor->visitChildren(this);
}
PostAnvilParser::StatementContext* PostAnvilParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 48, PostAnvilParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(362);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(349);
      type();
      setState(350);
      match(PostAnvilParser::IDENTIFIER);
      setState(351);
      match(PostAnvilParser::ASSIGN);
      setState(352);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtAssignContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(354);
      match(PostAnvilParser::IDENTIFIER);
      setState(355);
      match(PostAnvilParser::ASSIGN);
      setState(356);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtIfContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(357);
      ifStmt();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtForContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(358);
      forStmt();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtExprContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(359);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::StmtReturnContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(360);
      match(PostAnvilParser::RETURN);
      setState(361);
      expr();
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

//----------------- IfStmtContext ------------------------------------------------------------------

PostAnvilParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::IfBranchContext* PostAnvilParser::IfStmtContext::ifBranch() {
  return getRuleContext<PostAnvilParser::IfBranchContext>(0);
}

std::vector<PostAnvilParser::ElifBranchContext *> PostAnvilParser::IfStmtContext::elifBranch() {
  return getRuleContexts<PostAnvilParser::ElifBranchContext>();
}

PostAnvilParser::ElifBranchContext* PostAnvilParser::IfStmtContext::elifBranch(size_t i) {
  return getRuleContext<PostAnvilParser::ElifBranchContext>(i);
}

PostAnvilParser::ElseBranchContext* PostAnvilParser::IfStmtContext::elseBranch() {
  return getRuleContext<PostAnvilParser::ElseBranchContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::IfStmtContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::IfStmtContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}


size_t PostAnvilParser::IfStmtContext::getRuleIndex() const {
  return PostAnvilParser::RuleIfStmt;
}

void PostAnvilParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}

void PostAnvilParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}


std::any PostAnvilParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::IfStmtContext* PostAnvilParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 50, PostAnvilParser::RuleIfStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(364);
    ifBranch();
    setState(371);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(366);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PostAnvilParser::NEWLINE) {
          setState(365);
          newlines();
        }
        setState(368);
        elifBranch(); 
      }
      setState(373);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
    setState(378);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(375);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PostAnvilParser::NEWLINE) {
        setState(374);
        newlines();
      }
      setState(377);
      elseBranch();
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

//----------------- IfBranchContext ------------------------------------------------------------------

PostAnvilParser::IfBranchContext::IfBranchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::IfBranchContext::IF() {
  return getToken(PostAnvilParser::IF, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::IfBranchContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::IfBranchContext::stmt_block() {
  return getRuleContext<PostAnvilParser::Stmt_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::IfBranchContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::IfBranchContext::getRuleIndex() const {
  return PostAnvilParser::RuleIfBranch;
}

void PostAnvilParser::IfBranchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfBranch(this);
}

void PostAnvilParser::IfBranchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfBranch(this);
}


std::any PostAnvilParser::IfBranchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitIfBranch(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::IfBranchContext* PostAnvilParser::ifBranch() {
  IfBranchContext *_localctx = _tracker.createInstance<IfBranchContext>(_ctx, getState());
  enterRule(_localctx, 52, PostAnvilParser::RuleIfBranch);
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
    setState(380);
    match(PostAnvilParser::IF);
    setState(381);
    expr();
    setState(383);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(382);
      newlines();
    }
    setState(385);
    stmt_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElifBranchContext ------------------------------------------------------------------

PostAnvilParser::ElifBranchContext::ElifBranchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ElifBranchContext::ELIF() {
  return getToken(PostAnvilParser::ELIF, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::ElifBranchContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::ElifBranchContext::stmt_block() {
  return getRuleContext<PostAnvilParser::Stmt_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ElifBranchContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::ElifBranchContext::getRuleIndex() const {
  return PostAnvilParser::RuleElifBranch;
}

void PostAnvilParser::ElifBranchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElifBranch(this);
}

void PostAnvilParser::ElifBranchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElifBranch(this);
}


std::any PostAnvilParser::ElifBranchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitElifBranch(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ElifBranchContext* PostAnvilParser::elifBranch() {
  ElifBranchContext *_localctx = _tracker.createInstance<ElifBranchContext>(_ctx, getState());
  enterRule(_localctx, 54, PostAnvilParser::RuleElifBranch);
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
    setState(387);
    match(PostAnvilParser::ELIF);
    setState(388);
    expr();
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(389);
      newlines();
    }
    setState(392);
    stmt_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseBranchContext ------------------------------------------------------------------

PostAnvilParser::ElseBranchContext::ElseBranchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ElseBranchContext::ELSE() {
  return getToken(PostAnvilParser::ELSE, 0);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::ElseBranchContext::stmt_block() {
  return getRuleContext<PostAnvilParser::Stmt_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ElseBranchContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::ElseBranchContext::getRuleIndex() const {
  return PostAnvilParser::RuleElseBranch;
}

void PostAnvilParser::ElseBranchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElseBranch(this);
}

void PostAnvilParser::ElseBranchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElseBranch(this);
}


std::any PostAnvilParser::ElseBranchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitElseBranch(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ElseBranchContext* PostAnvilParser::elseBranch() {
  ElseBranchContext *_localctx = _tracker.createInstance<ElseBranchContext>(_ctx, getState());
  enterRule(_localctx, 56, PostAnvilParser::RuleElseBranch);
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
    setState(394);
    match(PostAnvilParser::ELSE);
    setState(396);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(395);
      newlines();
    }
    setState(398);
    stmt_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStmtContext ------------------------------------------------------------------

PostAnvilParser::ForStmtContext::ForStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ForStmtContext::FOR() {
  return getToken(PostAnvilParser::FOR, 0);
}

tree::TerminalNode* PostAnvilParser::ForStmtContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::ForStmtContext::IN() {
  return getToken(PostAnvilParser::IN, 0);
}

PostAnvilParser::For_sourceContext* PostAnvilParser::ForStmtContext::for_source() {
  return getRuleContext<PostAnvilParser::For_sourceContext>(0);
}

PostAnvilParser::Stmt_blockContext* PostAnvilParser::ForStmtContext::stmt_block() {
  return getRuleContext<PostAnvilParser::Stmt_blockContext>(0);
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ForStmtContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
}


size_t PostAnvilParser::ForStmtContext::getRuleIndex() const {
  return PostAnvilParser::RuleForStmt;
}

void PostAnvilParser::ForStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStmt(this);
}

void PostAnvilParser::ForStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStmt(this);
}


std::any PostAnvilParser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ForStmtContext* PostAnvilParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 58, PostAnvilParser::RuleForStmt);
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
    setState(400);
    match(PostAnvilParser::FOR);
    setState(401);
    match(PostAnvilParser::IDENTIFIER);
    setState(402);
    match(PostAnvilParser::IN);
    setState(403);
    for_source();
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::NEWLINE) {
      setState(404);
      newlines();
    }
    setState(407);
    stmt_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sort_keyContext ------------------------------------------------------------------

PostAnvilParser::Sort_keyContext::Sort_keyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::ExprContext* PostAnvilParser::Sort_keyContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::DirectionContext* PostAnvilParser::Sort_keyContext::direction() {
  return getRuleContext<PostAnvilParser::DirectionContext>(0);
}


size_t PostAnvilParser::Sort_keyContext::getRuleIndex() const {
  return PostAnvilParser::RuleSort_key;
}

void PostAnvilParser::Sort_keyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSort_key(this);
}

void PostAnvilParser::Sort_keyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSort_key(this);
}


std::any PostAnvilParser::Sort_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitSort_key(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Sort_keyContext* PostAnvilParser::sort_key() {
  Sort_keyContext *_localctx = _tracker.createInstance<Sort_keyContext>(_ctx, getState());
  enterRule(_localctx, 60, PostAnvilParser::RuleSort_key);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(409);
    expr();
    setState(410);
    direction();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DirectionContext ------------------------------------------------------------------

PostAnvilParser::DirectionContext::DirectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::DirectionContext::ASC() {
  return getToken(PostAnvilParser::ASC, 0);
}

tree::TerminalNode* PostAnvilParser::DirectionContext::DESC() {
  return getToken(PostAnvilParser::DESC, 0);
}


size_t PostAnvilParser::DirectionContext::getRuleIndex() const {
  return PostAnvilParser::RuleDirection;
}

void PostAnvilParser::DirectionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDirection(this);
}

void PostAnvilParser::DirectionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDirection(this);
}


std::any PostAnvilParser::DirectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitDirection(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::DirectionContext* PostAnvilParser::direction() {
  DirectionContext *_localctx = _tracker.createInstance<DirectionContext>(_ctx, getState());
  enterRule(_localctx, 62, PostAnvilParser::RuleDirection);
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
    setState(412);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::ASC

    || _la == PostAnvilParser::DESC)) {
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

//----------------- Class_exprContext ------------------------------------------------------------------

PostAnvilParser::Class_exprContext::Class_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Class_exprContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
}

tree::TerminalNode* PostAnvilParser::Class_exprContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::Class_exprContext::ALL_INST() {
  return getToken(PostAnvilParser::ALL_INST, 0);
}


size_t PostAnvilParser::Class_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleClass_expr;
}

void PostAnvilParser::Class_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClass_expr(this);
}

void PostAnvilParser::Class_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClass_expr(this);
}


std::any PostAnvilParser::Class_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClass_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::class_expr() {
  Class_exprContext *_localctx = _tracker.createInstance<Class_exprContext>(_ctx, getState());
  enterRule(_localctx, 64, PostAnvilParser::RuleClass_expr);
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
    setState(414);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 13510798890500096) != 0))) {
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

//----------------- Class_selectorContext ------------------------------------------------------------------

PostAnvilParser::Class_selectorContext::Class_selectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<PostAnvilParser::Class_exprContext *> PostAnvilParser::Class_selectorContext::class_expr() {
  return getRuleContexts<PostAnvilParser::Class_exprContext>();
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Class_selectorContext::class_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Class_exprContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::Class_selectorContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::Class_selectorContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}

PostAnvilParser::Class_groupContext* PostAnvilParser::Class_selectorContext::class_group() {
  return getRuleContext<PostAnvilParser::Class_groupContext>(0);
}


size_t PostAnvilParser::Class_selectorContext::getRuleIndex() const {
  return PostAnvilParser::RuleClass_selector;
}

void PostAnvilParser::Class_selectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClass_selector(this);
}

void PostAnvilParser::Class_selectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClass_selector(this);
}


std::any PostAnvilParser::Class_selectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClass_selector(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Class_selectorContext* PostAnvilParser::class_selector() {
  Class_selectorContext *_localctx = _tracker.createInstance<Class_selectorContext>(_ctx, getState());
  enterRule(_localctx, 66, PostAnvilParser::RuleClass_selector);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(425);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::ALL_INST:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(416);
        class_expr();
        setState(421);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PostAnvilParser::COMMA) {
          setState(417);
          match(PostAnvilParser::COMMA);
          setState(418);
          class_expr();
          setState(423);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case PostAnvilParser::AT: {
        enterOuterAlt(_localctx, 2);
        setState(424);
        class_group();
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

//----------------- Class_groupContext ------------------------------------------------------------------

PostAnvilParser::Class_groupContext::Class_groupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Class_groupContext::AT() {
  return getToken(PostAnvilParser::AT, 0);
}

tree::TerminalNode* PostAnvilParser::Class_groupContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}


size_t PostAnvilParser::Class_groupContext::getRuleIndex() const {
  return PostAnvilParser::RuleClass_group;
}

void PostAnvilParser::Class_groupContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClass_group(this);
}

void PostAnvilParser::Class_groupContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClass_group(this);
}


std::any PostAnvilParser::Class_groupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClass_group(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Class_groupContext* PostAnvilParser::class_group() {
  Class_groupContext *_localctx = _tracker.createInstance<Class_groupContext>(_ctx, getState());
  enterRule(_localctx, 68, PostAnvilParser::RuleClass_group);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    match(PostAnvilParser::AT);
    setState(428);
    match(PostAnvilParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- For_sourceContext ------------------------------------------------------------------

PostAnvilParser::For_sourceContext::For_sourceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::Class_exprContext* PostAnvilParser::For_sourceContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

PostAnvilParser::Class_groupContext* PostAnvilParser::For_sourceContext::class_group() {
  return getRuleContext<PostAnvilParser::Class_groupContext>(0);
}


size_t PostAnvilParser::For_sourceContext::getRuleIndex() const {
  return PostAnvilParser::RuleFor_source;
}

void PostAnvilParser::For_sourceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFor_source(this);
}

void PostAnvilParser::For_sourceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFor_source(this);
}


std::any PostAnvilParser::For_sourceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFor_source(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::For_sourceContext* PostAnvilParser::for_source() {
  For_sourceContext *_localctx = _tracker.createInstance<For_sourceContext>(_ctx, getState());
  enterRule(_localctx, 70, PostAnvilParser::RuleFor_source);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(432);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::ALL_INST:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(430);
        class_expr();
        break;
      }

      case PostAnvilParser::AT: {
        enterOuterAlt(_localctx, 2);
        setState(431);
        class_group();
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

//----------------- Bool_exprContext ------------------------------------------------------------------

PostAnvilParser::Bool_exprContext::Bool_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

PostAnvilParser::Or_exprContext* PostAnvilParser::Bool_exprContext::or_expr() {
  return getRuleContext<PostAnvilParser::Or_exprContext>(0);
}


size_t PostAnvilParser::Bool_exprContext::getRuleIndex() const {
  return PostAnvilParser::RuleBool_expr;
}

void PostAnvilParser::Bool_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBool_expr(this);
}

void PostAnvilParser::Bool_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBool_expr(this);
}


std::any PostAnvilParser::Bool_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitBool_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::bool_expr() {
  Bool_exprContext *_localctx = _tracker.createInstance<Bool_exprContext>(_ctx, getState());
  enterRule(_localctx, 72, PostAnvilParser::RuleBool_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(434);
    or_expr();
   
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


std::any PostAnvilParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ExprContext* PostAnvilParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 74, PostAnvilParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
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


std::any PostAnvilParser::Or_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitOr_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Or_exprContext* PostAnvilParser::or_expr() {
  Or_exprContext *_localctx = _tracker.createInstance<Or_exprContext>(_ctx, getState());
  enterRule(_localctx, 76, PostAnvilParser::RuleOr_expr);
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
    setState(438);
    and_expr();
    setState(443);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::OR) {
      setState(439);
      match(PostAnvilParser::OR);
      setState(440);
      and_expr();
      setState(445);
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


std::any PostAnvilParser::And_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAnd_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::And_exprContext* PostAnvilParser::and_expr() {
  And_exprContext *_localctx = _tracker.createInstance<And_exprContext>(_ctx, getState());
  enterRule(_localctx, 78, PostAnvilParser::RuleAnd_expr);
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
    setState(446);
    not_expr();
    setState(451);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::AND) {
      setState(447);
      match(PostAnvilParser::AND);
      setState(448);
      not_expr();
      setState(453);
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


std::any PostAnvilParser::Not_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitNot_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Not_exprContext* PostAnvilParser::not_expr() {
  Not_exprContext *_localctx = _tracker.createInstance<Not_exprContext>(_ctx, getState());
  enterRule(_localctx, 80, PostAnvilParser::RuleNot_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(457);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(454);
        match(PostAnvilParser::NOT);
        setState(455);
        not_expr();
        break;
      }

      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::SELF:
      case PostAnvilParser::MINUS:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(456);
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


std::any PostAnvilParser::Cmp_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitCmp_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Cmp_exprContext* PostAnvilParser::cmp_expr() {
  Cmp_exprContext *_localctx = _tracker.createInstance<Cmp_exprContext>(_ctx, getState());
  enterRule(_localctx, 82, PostAnvilParser::RuleCmp_expr);
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
    setState(459);
    add_expr();
    setState(463);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34634616274944) != 0)) {
      setState(460);
      comp_op();
      setState(461);
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


std::any PostAnvilParser::Add_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAdd_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Add_exprContext* PostAnvilParser::add_expr() {
  Add_exprContext *_localctx = _tracker.createInstance<Add_exprContext>(_ctx, getState());
  enterRule(_localctx, 84, PostAnvilParser::RuleAdd_expr);
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
    setState(465);
    mul_expr();
    setState(471);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS) {
      setState(466);
      add_op();
      setState(467);
      mul_expr();
      setState(473);
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


std::any PostAnvilParser::Mul_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitMul_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Mul_exprContext* PostAnvilParser::mul_expr() {
  Mul_exprContext *_localctx = _tracker.createInstance<Mul_exprContext>(_ctx, getState());
  enterRule(_localctx, 86, PostAnvilParser::RuleMul_expr);
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
    setState(474);
    unary_expr();
    setState(480);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH) {
      setState(475);
      mul_op();
      setState(476);
      unary_expr();
      setState(482);
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


std::any PostAnvilParser::Unary_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitUnary_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Unary_exprContext* PostAnvilParser::unary_expr() {
  Unary_exprContext *_localctx = _tracker.createInstance<Unary_exprContext>(_ctx, getState());
  enterRule(_localctx, 88, PostAnvilParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(486);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(483);
        match(PostAnvilParser::MINUS);
        setState(484);
        unary_expr();
        break;
      }

      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::SELF:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(485);
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

tree::TerminalNode* PostAnvilParser::PrimaryContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
}

tree::TerminalNode* PostAnvilParser::PrimaryContext::BOOL_LIT() {
  return getToken(PostAnvilParser::BOOL_LIT, 0);
}

tree::TerminalNode* PostAnvilParser::PrimaryContext::SELF() {
  return getToken(PostAnvilParser::SELF, 0);
}

PostAnvilParser::Func_callContext* PostAnvilParser::PrimaryContext::func_call() {
  return getRuleContext<PostAnvilParser::Func_callContext>(0);
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

tree::TerminalNode* PostAnvilParser::PrimaryContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
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


std::any PostAnvilParser::PrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitPrimary(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::PrimaryContext* PostAnvilParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 90, PostAnvilParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(499);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(488);
      match(PostAnvilParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(489);
      match(PostAnvilParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(490);
      match(PostAnvilParser::BOOL_LIT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(491);
      match(PostAnvilParser::SELF);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(492);
      func_call();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(493);
      attribute();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(494);
      match(PostAnvilParser::LPAREN);
      setState(495);
      expr();
      setState(496);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(498);
      match(PostAnvilParser::IDENTIFIER);
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

//----------------- Func_callContext ------------------------------------------------------------------

PostAnvilParser::Func_callContext::Func_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::Func_callContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::Func_callContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

tree::TerminalNode* PostAnvilParser::Func_callContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}

std::vector<PostAnvilParser::ExprContext *> PostAnvilParser::Func_callContext::expr() {
  return getRuleContexts<PostAnvilParser::ExprContext>();
}

PostAnvilParser::ExprContext* PostAnvilParser::Func_callContext::expr(size_t i) {
  return getRuleContext<PostAnvilParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> PostAnvilParser::Func_callContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::Func_callContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}


size_t PostAnvilParser::Func_callContext::getRuleIndex() const {
  return PostAnvilParser::RuleFunc_call;
}

void PostAnvilParser::Func_callContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc_call(this);
}

void PostAnvilParser::Func_callContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc_call(this);
}


std::any PostAnvilParser::Func_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFunc_call(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Func_callContext* PostAnvilParser::func_call() {
  Func_callContext *_localctx = _tracker.createInstance<Func_callContext>(_ctx, getState());
  enterRule(_localctx, 92, PostAnvilParser::RuleFunc_call);
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
    setState(501);
    match(PostAnvilParser::IDENTIFIER);
    setState(502);
    match(PostAnvilParser::LPAREN);
    setState(511);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15833036159680512) != 0)) {
      setState(503);
      expr();
      setState(508);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PostAnvilParser::COMMA) {
        setState(504);
        match(PostAnvilParser::COMMA);
        setState(505);
        expr();
        setState(510);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(513);
    match(PostAnvilParser::RPAREN);
   
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


size_t PostAnvilParser::AttributeContext::getRuleIndex() const {
  return PostAnvilParser::RuleAttribute;
}

void PostAnvilParser::AttributeContext::copyFrom(AttributeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DynamicInstanceAttrContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::DynamicInstanceAttrContext::SELF() {
  return getToken(PostAnvilParser::SELF, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicInstanceAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicInstanceAttrContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::DynamicInstanceAttrContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::DynamicInstanceAttrContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}

PostAnvilParser::DynamicInstanceAttrContext::DynamicInstanceAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::DynamicInstanceAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDynamicInstanceAttr(this);
}
void PostAnvilParser::DynamicInstanceAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDynamicInstanceAttr(this);
}

std::any PostAnvilParser::DynamicInstanceAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitDynamicInstanceAttr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DynamicClassAttrContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::DynamicClassAttrContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicClassAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicClassAttrContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::DynamicClassAttrContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::DynamicClassAttrContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}

PostAnvilParser::DynamicClassAttrContext::DynamicClassAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::DynamicClassAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDynamicClassAttr(this);
}
void PostAnvilParser::DynamicClassAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDynamicClassAttr(this);
}

std::any PostAnvilParser::DynamicClassAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitDynamicClassAttr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DynamicVarAttrContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::DynamicVarAttrContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicVarAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::DynamicVarAttrContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::DynamicVarAttrContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

tree::TerminalNode* PostAnvilParser::DynamicVarAttrContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}

PostAnvilParser::DynamicVarAttrContext::DynamicVarAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::DynamicVarAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDynamicVarAttr(this);
}
void PostAnvilParser::DynamicVarAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDynamicVarAttr(this);
}

std::any PostAnvilParser::DynamicVarAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitDynamicVarAttr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InstanceAttrContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::InstanceAttrContext::SELF() {
  return getToken(PostAnvilParser::SELF, 0);
}

tree::TerminalNode* PostAnvilParser::InstanceAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::InstanceAttrContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::InstanceAttrContext::InstanceAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::InstanceAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInstanceAttr(this);
}
void PostAnvilParser::InstanceAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInstanceAttr(this);
}

std::any PostAnvilParser::InstanceAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitInstanceAttr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ClassAttrContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::ClassAttrContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
}

tree::TerminalNode* PostAnvilParser::ClassAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

tree::TerminalNode* PostAnvilParser::ClassAttrContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

PostAnvilParser::ClassAttrContext::ClassAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::ClassAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClassAttr(this);
}
void PostAnvilParser::ClassAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClassAttr(this);
}

std::any PostAnvilParser::ClassAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClassAttr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarInstanceAttrContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> PostAnvilParser::VarInstanceAttrContext::IDENTIFIER() {
  return getTokens(PostAnvilParser::IDENTIFIER);
}

tree::TerminalNode* PostAnvilParser::VarInstanceAttrContext::IDENTIFIER(size_t i) {
  return getToken(PostAnvilParser::IDENTIFIER, i);
}

tree::TerminalNode* PostAnvilParser::VarInstanceAttrContext::DOT() {
  return getToken(PostAnvilParser::DOT, 0);
}

PostAnvilParser::VarInstanceAttrContext::VarInstanceAttrContext(AttributeContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::VarInstanceAttrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarInstanceAttr(this);
}
void PostAnvilParser::VarInstanceAttrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarInstanceAttr(this);
}

std::any PostAnvilParser::VarInstanceAttrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitVarInstanceAttr(this);
  else
    return visitor->visitChildren(this);
}
PostAnvilParser::AttributeContext* PostAnvilParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 94, PostAnvilParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(542);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(515);
      match(PostAnvilParser::SELF);
      setState(516);
      match(PostAnvilParser::DOT);
      setState(517);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(518);
      match(PostAnvilParser::STRING);
      setState(519);
      match(PostAnvilParser::DOT);
      setState(520);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::VarInstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(521);
      match(PostAnvilParser::IDENTIFIER);
      setState(522);
      match(PostAnvilParser::DOT);
      setState(523);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicInstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(524);
      match(PostAnvilParser::SELF);
      setState(525);
      match(PostAnvilParser::DOT);
      setState(526);
      match(PostAnvilParser::LPAREN);
      setState(527);
      expr();
      setState(528);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicClassAttrContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(530);
      match(PostAnvilParser::STRING);
      setState(531);
      match(PostAnvilParser::DOT);
      setState(532);
      match(PostAnvilParser::LPAREN);
      setState(533);
      expr();
      setState(534);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicVarAttrContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(536);
      match(PostAnvilParser::IDENTIFIER);
      setState(537);
      match(PostAnvilParser::DOT);
      setState(538);
      match(PostAnvilParser::LPAREN);
      setState(539);
      expr();
      setState(540);
      match(PostAnvilParser::RPAREN);
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


std::any PostAnvilParser::Comp_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitComp_op(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Comp_opContext* PostAnvilParser::comp_op() {
  Comp_opContext *_localctx = _tracker.createInstance<Comp_opContext>(_ctx, getState());
  enterRule(_localctx, 96, PostAnvilParser::RuleComp_op);
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
    setState(544);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34634616274944) != 0))) {
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


std::any PostAnvilParser::Add_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAdd_op(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Add_opContext* PostAnvilParser::add_op() {
  Add_opContext *_localctx = _tracker.createInstance<Add_opContext>(_ctx, getState());
  enterRule(_localctx, 98, PostAnvilParser::RuleAdd_op);
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
    setState(546);
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


std::any PostAnvilParser::Mul_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitMul_op(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Mul_opContext* PostAnvilParser::mul_op() {
  Mul_opContext *_localctx = _tracker.createInstance<Mul_opContext>(_ctx, getState());
  enterRule(_localctx, 100, PostAnvilParser::RuleMul_op);
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
    setState(548);
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
