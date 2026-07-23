
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
      "program", "newlines", "declaration", "importDef", "importItem", "exportDef", 
      "exportItem", "globalDef", "type", "rule_", "filter_rule", "attr_rule", 
      "attr_def", "attr_lvalue", "func_rule", "typed_params", "typed_param", 
      "func_statement", "ifStmt", "forStmt", "group_rule", "append_rule", 
      "class_expr", "bool_expr", "expr", "or_expr", "and_expr", "not_expr", 
      "cmp_expr", "add_expr", "mul_expr", "unary_expr", "primary", "func_call", 
      "sortExpr", "attribute", "comp_op", "add_op", "mul_op"
    },
    std::vector<std::string>{
      "", "':'", "'RULE'", "'RULEEND'", "'FILTER'", "'ATTR'", "'FUNC'", 
      "'GROUP'", "'APPEND'", "'FROM'", "'AND'", "'OR'", "'NOT'", "'SELF'", 
      "'NUM'", "'STR'", "'BOOL'", "'ANY'", "'RETURN'", "'IMPORT'", "'EXPORT'", 
      "'AS'", "'IF'", "'ELSE'", "'ENDIF'", "'FOR'", "'IN'", "'ENDFOR'", 
      "'SORT'", "", "'->'", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'<='", 
      "'>='", "'=='", "'!='", "'.'", "'('", "')'", "','", "'='"
    },
    std::vector<std::string>{
      "", "", "RULE", "RULEEND", "FILTER", "ATTR", "FUNC", "GROUP", "APPEND", 
      "FROM", "AND", "OR", "NOT", "SELF", "NUM", "STR", "BOOL", "ANY", "RETURN", 
      "IMPORT", "EXPORT", "AS", "IF", "ELSE", "ENDIF", "FOR", "IN", "ENDFOR", 
      "SORT", "BOOL_LIT", "ARROW", "PLUS", "MINUS", "STAR", "SLASH", "LT", 
      "GT", "LE", "GE", "EQ", "NE", "DOT", "LPAREN", "RPAREN", "COMMA", 
      "ASSIGN", "NUMBER", "STRING", "IDENTIFIER", "WS", "NEWLINE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,428,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,1,0,1,0,1,0,5,0,82,8,0,10,0,12,0,85,
  	9,0,1,0,1,0,1,1,4,1,90,8,1,11,1,12,1,91,1,2,1,2,1,2,3,2,97,8,2,1,3,1,
  	3,1,3,1,3,5,3,103,8,3,10,3,12,3,106,9,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,114,
  	8,4,1,5,1,5,1,5,1,5,5,5,120,8,5,10,5,12,5,123,9,5,1,5,1,5,1,6,1,6,1,6,
  	1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,142,8,7,1,8,1,8,1,
  	9,1,9,1,9,1,9,1,9,3,9,151,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	5,10,161,8,10,10,10,12,10,164,9,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,5,11,176,8,11,10,11,12,11,179,9,11,1,11,1,11,1,12,1,12,
  	1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,3,13,193,8,13,1,14,1,14,1,14,
  	1,14,1,14,3,14,200,8,14,1,14,1,14,1,14,3,14,205,8,14,1,14,1,14,1,14,1,
  	14,1,14,4,14,212,8,14,11,14,12,14,213,1,14,1,14,1,15,1,15,1,15,5,15,221,
  	8,15,10,15,12,15,224,9,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,243,8,17,1,18,1,18,1,18,
  	1,18,1,18,1,18,5,18,251,8,18,10,18,12,18,254,9,18,1,18,1,18,1,18,1,18,
  	1,18,5,18,261,8,18,10,18,12,18,264,9,18,3,18,266,8,18,1,18,1,18,1,19,
  	1,19,1,19,1,19,1,19,1,19,1,19,1,19,5,19,278,8,19,10,19,12,19,281,9,19,
  	1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,5,20,295,
  	8,20,10,20,12,20,298,9,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,
  	1,21,1,21,1,21,5,21,312,8,21,10,21,12,21,315,9,21,1,21,1,21,1,22,1,22,
  	1,23,1,23,1,24,1,24,1,25,1,25,1,25,5,25,328,8,25,10,25,12,25,331,9,25,
  	1,26,1,26,1,26,5,26,336,8,26,10,26,12,26,339,9,26,1,27,1,27,1,27,3,27,
  	344,8,27,1,28,1,28,1,28,1,28,3,28,350,8,28,1,29,1,29,1,29,1,29,5,29,356,
  	8,29,10,29,12,29,359,9,29,1,30,1,30,1,30,1,30,5,30,365,8,30,10,30,12,
  	30,368,9,30,1,31,1,31,1,31,3,31,373,8,31,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,3,32,386,8,32,1,33,1,33,1,33,1,33,1,33,5,33,
  	393,8,33,10,33,12,33,396,9,33,3,33,398,8,33,1,33,1,33,1,34,1,34,1,34,
  	1,34,1,34,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,
  	1,35,3,35,420,8,35,1,36,1,36,1,37,1,37,1,38,1,38,1,38,0,0,39,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,64,66,68,70,72,74,76,0,5,1,0,14,17,1,0,47,48,1,0,35,40,1,
  	0,31,32,1,0,33,34,438,0,83,1,0,0,0,2,89,1,0,0,0,4,96,1,0,0,0,6,98,1,0,
  	0,0,8,109,1,0,0,0,10,115,1,0,0,0,12,126,1,0,0,0,14,141,1,0,0,0,16,143,
  	1,0,0,0,18,150,1,0,0,0,20,152,1,0,0,0,22,167,1,0,0,0,24,182,1,0,0,0,26,
  	192,1,0,0,0,28,194,1,0,0,0,30,217,1,0,0,0,32,225,1,0,0,0,34,242,1,0,0,
  	0,36,244,1,0,0,0,38,269,1,0,0,0,40,284,1,0,0,0,42,301,1,0,0,0,44,318,
  	1,0,0,0,46,320,1,0,0,0,48,322,1,0,0,0,50,324,1,0,0,0,52,332,1,0,0,0,54,
  	343,1,0,0,0,56,345,1,0,0,0,58,351,1,0,0,0,60,360,1,0,0,0,62,372,1,0,0,
  	0,64,385,1,0,0,0,66,387,1,0,0,0,68,401,1,0,0,0,70,419,1,0,0,0,72,421,
  	1,0,0,0,74,423,1,0,0,0,76,425,1,0,0,0,78,82,3,4,2,0,79,82,3,18,9,0,80,
  	82,3,2,1,0,81,78,1,0,0,0,81,79,1,0,0,0,81,80,1,0,0,0,82,85,1,0,0,0,83,
  	81,1,0,0,0,83,84,1,0,0,0,84,86,1,0,0,0,85,83,1,0,0,0,86,87,5,0,0,1,87,
  	1,1,0,0,0,88,90,5,50,0,0,89,88,1,0,0,0,90,91,1,0,0,0,91,89,1,0,0,0,91,
  	92,1,0,0,0,92,3,1,0,0,0,93,97,3,6,3,0,94,97,3,10,5,0,95,97,3,14,7,0,96,
  	93,1,0,0,0,96,94,1,0,0,0,96,95,1,0,0,0,97,5,1,0,0,0,98,99,5,19,0,0,99,
  	104,3,8,4,0,100,101,5,44,0,0,101,103,3,8,4,0,102,100,1,0,0,0,103,106,
  	1,0,0,0,104,102,1,0,0,0,104,105,1,0,0,0,105,107,1,0,0,0,106,104,1,0,0,
  	0,107,108,3,2,1,0,108,7,1,0,0,0,109,110,3,16,8,0,110,113,5,48,0,0,111,
  	112,5,21,0,0,112,114,5,48,0,0,113,111,1,0,0,0,113,114,1,0,0,0,114,9,1,
  	0,0,0,115,116,5,20,0,0,116,121,3,12,6,0,117,118,5,44,0,0,118,120,3,12,
  	6,0,119,117,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,
  	124,1,0,0,0,123,121,1,0,0,0,124,125,3,2,1,0,125,11,1,0,0,0,126,127,3,
  	48,24,0,127,128,5,21,0,0,128,129,5,48,0,0,129,13,1,0,0,0,130,131,3,16,
  	8,0,131,132,5,48,0,0,132,133,5,45,0,0,133,134,3,48,24,0,134,135,3,2,1,
  	0,135,142,1,0,0,0,136,137,5,48,0,0,137,138,5,45,0,0,138,139,3,48,24,0,
  	139,140,3,2,1,0,140,142,1,0,0,0,141,130,1,0,0,0,141,136,1,0,0,0,142,15,
  	1,0,0,0,143,144,7,0,0,0,144,17,1,0,0,0,145,151,3,20,10,0,146,151,3,22,
  	11,0,147,151,3,40,20,0,148,151,3,42,21,0,149,151,3,28,14,0,150,145,1,
  	0,0,0,150,146,1,0,0,0,150,147,1,0,0,0,150,148,1,0,0,0,150,149,1,0,0,0,
  	151,19,1,0,0,0,152,153,5,2,0,0,153,154,5,4,0,0,154,155,3,44,22,0,155,
  	156,5,1,0,0,156,162,3,2,1,0,157,158,3,46,23,0,158,159,3,2,1,0,159,161,
  	1,0,0,0,160,157,1,0,0,0,161,164,1,0,0,0,162,160,1,0,0,0,162,163,1,0,0,
  	0,163,165,1,0,0,0,164,162,1,0,0,0,165,166,5,3,0,0,166,21,1,0,0,0,167,
  	168,5,2,0,0,168,169,5,5,0,0,169,170,3,44,22,0,170,171,5,1,0,0,171,177,
  	3,2,1,0,172,173,3,24,12,0,173,174,3,2,1,0,174,176,1,0,0,0,175,172,1,0,
  	0,0,176,179,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,180,1,0,0,0,179,
  	177,1,0,0,0,180,181,5,3,0,0,181,23,1,0,0,0,182,183,3,26,13,0,183,184,
  	5,45,0,0,184,185,3,48,24,0,185,25,1,0,0,0,186,187,5,13,0,0,187,188,5,
  	41,0,0,188,193,5,48,0,0,189,190,5,47,0,0,190,191,5,41,0,0,191,193,5,48,
  	0,0,192,186,1,0,0,0,192,189,1,0,0,0,193,27,1,0,0,0,194,195,5,2,0,0,195,
  	196,5,6,0,0,196,197,5,48,0,0,197,199,5,42,0,0,198,200,3,30,15,0,199,198,
  	1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,204,5,43,0,0,202,203,5,30,
  	0,0,203,205,3,16,8,0,204,202,1,0,0,0,204,205,1,0,0,0,205,206,1,0,0,0,
  	206,207,5,1,0,0,207,211,3,2,1,0,208,209,3,34,17,0,209,210,3,2,1,0,210,
  	212,1,0,0,0,211,208,1,0,0,0,212,213,1,0,0,0,213,211,1,0,0,0,213,214,1,
  	0,0,0,214,215,1,0,0,0,215,216,5,3,0,0,216,29,1,0,0,0,217,222,3,32,16,
  	0,218,219,5,44,0,0,219,221,3,32,16,0,220,218,1,0,0,0,221,224,1,0,0,0,
  	222,220,1,0,0,0,222,223,1,0,0,0,223,31,1,0,0,0,224,222,1,0,0,0,225,226,
  	5,48,0,0,226,227,5,1,0,0,227,228,3,16,8,0,228,33,1,0,0,0,229,230,3,16,
  	8,0,230,231,5,48,0,0,231,232,5,45,0,0,232,233,3,48,24,0,233,243,1,0,0,
  	0,234,235,5,48,0,0,235,236,5,45,0,0,236,243,3,48,24,0,237,243,3,36,18,
  	0,238,243,3,38,19,0,239,243,3,48,24,0,240,241,5,18,0,0,241,243,3,48,24,
  	0,242,229,1,0,0,0,242,234,1,0,0,0,242,237,1,0,0,0,242,238,1,0,0,0,242,
  	239,1,0,0,0,242,240,1,0,0,0,243,35,1,0,0,0,244,245,5,22,0,0,245,246,3,
  	48,24,0,246,252,3,2,1,0,247,248,3,34,17,0,248,249,3,2,1,0,249,251,1,0,
  	0,0,250,247,1,0,0,0,251,254,1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,
  	265,1,0,0,0,254,252,1,0,0,0,255,256,5,23,0,0,256,262,3,2,1,0,257,258,
  	3,34,17,0,258,259,3,2,1,0,259,261,1,0,0,0,260,257,1,0,0,0,261,264,1,0,
  	0,0,262,260,1,0,0,0,262,263,1,0,0,0,263,266,1,0,0,0,264,262,1,0,0,0,265,
  	255,1,0,0,0,265,266,1,0,0,0,266,267,1,0,0,0,267,268,5,24,0,0,268,37,1,
  	0,0,0,269,270,5,25,0,0,270,271,5,48,0,0,271,272,5,26,0,0,272,273,3,44,
  	22,0,273,279,3,2,1,0,274,275,3,34,17,0,275,276,3,2,1,0,276,278,1,0,0,
  	0,277,274,1,0,0,0,278,281,1,0,0,0,279,277,1,0,0,0,279,280,1,0,0,0,280,
  	282,1,0,0,0,281,279,1,0,0,0,282,283,5,27,0,0,283,39,1,0,0,0,284,285,5,
  	2,0,0,285,286,5,7,0,0,286,287,3,44,22,0,287,288,5,9,0,0,288,289,3,44,
  	22,0,289,290,5,1,0,0,290,296,3,2,1,0,291,292,3,46,23,0,292,293,3,2,1,
  	0,293,295,1,0,0,0,294,291,1,0,0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,
  	297,1,0,0,0,297,299,1,0,0,0,298,296,1,0,0,0,299,300,5,3,0,0,300,41,1,
  	0,0,0,301,302,5,2,0,0,302,303,5,8,0,0,303,304,3,44,22,0,304,305,5,9,0,
  	0,305,306,3,44,22,0,306,307,5,1,0,0,307,313,3,2,1,0,308,309,3,46,23,0,
  	309,310,3,2,1,0,310,312,1,0,0,0,311,308,1,0,0,0,312,315,1,0,0,0,313,311,
  	1,0,0,0,313,314,1,0,0,0,314,316,1,0,0,0,315,313,1,0,0,0,316,317,5,3,0,
  	0,317,43,1,0,0,0,318,319,7,1,0,0,319,45,1,0,0,0,320,321,3,50,25,0,321,
  	47,1,0,0,0,322,323,3,50,25,0,323,49,1,0,0,0,324,329,3,52,26,0,325,326,
  	5,11,0,0,326,328,3,52,26,0,327,325,1,0,0,0,328,331,1,0,0,0,329,327,1,
  	0,0,0,329,330,1,0,0,0,330,51,1,0,0,0,331,329,1,0,0,0,332,337,3,54,27,
  	0,333,334,5,10,0,0,334,336,3,54,27,0,335,333,1,0,0,0,336,339,1,0,0,0,
  	337,335,1,0,0,0,337,338,1,0,0,0,338,53,1,0,0,0,339,337,1,0,0,0,340,341,
  	5,12,0,0,341,344,3,54,27,0,342,344,3,56,28,0,343,340,1,0,0,0,343,342,
  	1,0,0,0,344,55,1,0,0,0,345,349,3,58,29,0,346,347,3,72,36,0,347,348,3,
  	58,29,0,348,350,1,0,0,0,349,346,1,0,0,0,349,350,1,0,0,0,350,57,1,0,0,
  	0,351,357,3,60,30,0,352,353,3,74,37,0,353,354,3,60,30,0,354,356,1,0,0,
  	0,355,352,1,0,0,0,356,359,1,0,0,0,357,355,1,0,0,0,357,358,1,0,0,0,358,
  	59,1,0,0,0,359,357,1,0,0,0,360,366,3,62,31,0,361,362,3,76,38,0,362,363,
  	3,62,31,0,363,365,1,0,0,0,364,361,1,0,0,0,365,368,1,0,0,0,366,364,1,0,
  	0,0,366,367,1,0,0,0,367,61,1,0,0,0,368,366,1,0,0,0,369,370,5,32,0,0,370,
  	373,3,62,31,0,371,373,3,64,32,0,372,369,1,0,0,0,372,371,1,0,0,0,373,63,
  	1,0,0,0,374,386,5,46,0,0,375,386,5,47,0,0,376,386,5,29,0,0,377,386,3,
  	66,33,0,378,386,3,70,35,0,379,380,5,42,0,0,380,381,3,48,24,0,381,382,
  	5,43,0,0,382,386,1,0,0,0,383,386,3,68,34,0,384,386,5,48,0,0,385,374,1,
  	0,0,0,385,375,1,0,0,0,385,376,1,0,0,0,385,377,1,0,0,0,385,378,1,0,0,0,
  	385,379,1,0,0,0,385,383,1,0,0,0,385,384,1,0,0,0,386,65,1,0,0,0,387,388,
  	5,48,0,0,388,397,5,42,0,0,389,394,3,48,24,0,390,391,5,44,0,0,391,393,
  	3,48,24,0,392,390,1,0,0,0,393,396,1,0,0,0,394,392,1,0,0,0,394,395,1,0,
  	0,0,395,398,1,0,0,0,396,394,1,0,0,0,397,389,1,0,0,0,397,398,1,0,0,0,398,
  	399,1,0,0,0,399,400,5,43,0,0,400,67,1,0,0,0,401,402,5,28,0,0,402,403,
  	5,42,0,0,403,404,3,44,22,0,404,405,5,44,0,0,405,406,3,48,24,0,406,407,
  	5,44,0,0,407,408,3,48,24,0,408,409,5,43,0,0,409,69,1,0,0,0,410,411,5,
  	13,0,0,411,412,5,41,0,0,412,420,5,48,0,0,413,414,5,47,0,0,414,415,5,41,
  	0,0,415,420,5,48,0,0,416,417,5,48,0,0,417,418,5,41,0,0,418,420,5,48,0,
  	0,419,410,1,0,0,0,419,413,1,0,0,0,419,416,1,0,0,0,420,71,1,0,0,0,421,
  	422,7,2,0,0,422,73,1,0,0,0,423,424,7,3,0,0,424,75,1,0,0,0,425,426,7,4,
  	0,0,426,77,1,0,0,0,34,81,83,91,96,104,113,121,141,150,162,177,192,199,
  	204,213,222,242,252,262,265,279,296,313,329,337,343,349,357,366,372,385,
  	394,397,419
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

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::ProgramContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ProgramContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
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
    setState(83);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1407374885371908) != 0)) {
      setState(81);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PostAnvilParser::NUM:
        case PostAnvilParser::STR:
        case PostAnvilParser::BOOL:
        case PostAnvilParser::ANY:
        case PostAnvilParser::IMPORT:
        case PostAnvilParser::EXPORT:
        case PostAnvilParser::IDENTIFIER: {
          setState(78);
          declaration();
          break;
        }

        case PostAnvilParser::RULE: {
          setState(79);
          rule_();
          break;
        }

        case PostAnvilParser::NEWLINE: {
          setState(80);
          newlines();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(85);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(86);
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
    setState(89); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(88);
              match(PostAnvilParser::NEWLINE);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(91); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
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
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(93);
        importDef();
        break;
      }

      case PostAnvilParser::EXPORT: {
        enterOuterAlt(_localctx, 2);
        setState(94);
        exportDef();
        break;
      }

      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::ANY:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(95);
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

PostAnvilParser::NewlinesContext* PostAnvilParser::ImportDefContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
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
    setState(98);
    match(PostAnvilParser::IMPORT);
    setState(99);
    importItem();
    setState(104);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(100);
      match(PostAnvilParser::COMMA);
      setState(101);
      importItem();
      setState(106);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(107);
    newlines();
   
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
    setState(109);
    type();
    setState(110);
    antlrcpp::downCast<ImportItemContext *>(_localctx)->host = match(PostAnvilParser::IDENTIFIER);
    setState(113);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::AS) {
      setState(111);
      match(PostAnvilParser::AS);
      setState(112);
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

PostAnvilParser::NewlinesContext* PostAnvilParser::ExportDefContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
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
    setState(115);
    match(PostAnvilParser::EXPORT);
    setState(116);
    exportItem();
    setState(121);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(117);
      match(PostAnvilParser::COMMA);
      setState(118);
      exportItem();
      setState(123);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(124);
    newlines();
   
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
    setState(126);
    expr();
    setState(127);
    match(PostAnvilParser::AS);
    setState(128);
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

PostAnvilParser::NewlinesContext* PostAnvilParser::GlobalDefContext::newlines() {
  return getRuleContext<PostAnvilParser::NewlinesContext>(0);
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
    setState(141);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::ANY: {
        enterOuterAlt(_localctx, 1);
        setState(130);
        type();
        setState(131);
        match(PostAnvilParser::IDENTIFIER);
        setState(132);
        match(PostAnvilParser::ASSIGN);
        setState(133);
        expr();
        setState(134);
        newlines();
        break;
      }

      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(136);
        match(PostAnvilParser::IDENTIFIER);
        setState(137);
        match(PostAnvilParser::ASSIGN);
        setState(138);
        expr();
        setState(139);
        newlines();
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
    setState(143);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 245760) != 0))) {
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

PostAnvilParser::Rule_Context* PostAnvilParser::rule_() {
  Rule_Context *_localctx = _tracker.createInstance<Rule_Context>(_ctx, getState());
  enterRule(_localctx, 18, PostAnvilParser::RuleRule_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(145);
      filter_rule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(146);
      attr_rule();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(147);
      group_rule();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(148);
      append_rule();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(149);
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

PostAnvilParser::Class_exprContext* PostAnvilParser::Filter_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Filter_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Filter_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Filter_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

std::vector<PostAnvilParser::Bool_exprContext *> PostAnvilParser::Filter_ruleContext::bool_expr() {
  return getRuleContexts<PostAnvilParser::Bool_exprContext>();
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::Filter_ruleContext::bool_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Bool_exprContext>(i);
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

PostAnvilParser::Filter_ruleContext* PostAnvilParser::filter_rule() {
  Filter_ruleContext *_localctx = _tracker.createInstance<Filter_ruleContext>(_ctx, getState());
  enterRule(_localctx, 20, PostAnvilParser::RuleFilter_rule);
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
    setState(152);
    match(PostAnvilParser::RULE);
    setState(153);
    match(PostAnvilParser::FILTER);
    setState(154);
    class_expr();
    setState(155);
    match(PostAnvilParser::T__0);
    setState(156);
    newlines();
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984356040704) != 0)) {
      setState(157);
      bool_expr();
      setState(158);
      newlines();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(165);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Class_exprContext* PostAnvilParser::Attr_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Attr_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Attr_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Attr_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

std::vector<PostAnvilParser::Attr_defContext *> PostAnvilParser::Attr_ruleContext::attr_def() {
  return getRuleContexts<PostAnvilParser::Attr_defContext>();
}

PostAnvilParser::Attr_defContext* PostAnvilParser::Attr_ruleContext::attr_def(size_t i) {
  return getRuleContext<PostAnvilParser::Attr_defContext>(i);
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

PostAnvilParser::Attr_ruleContext* PostAnvilParser::attr_rule() {
  Attr_ruleContext *_localctx = _tracker.createInstance<Attr_ruleContext>(_ctx, getState());
  enterRule(_localctx, 22, PostAnvilParser::RuleAttr_rule);
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
    setState(167);
    match(PostAnvilParser::RULE);
    setState(168);
    match(PostAnvilParser::ATTR);
    setState(169);
    class_expr();
    setState(170);
    match(PostAnvilParser::T__0);
    setState(171);
    newlines();
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::SELF

    || _la == PostAnvilParser::STRING) {
      setState(172);
      attr_def();
      setState(173);
      newlines();
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(180);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Attr_defContext* PostAnvilParser::attr_def() {
  Attr_defContext *_localctx = _tracker.createInstance<Attr_defContext>(_ctx, getState());
  enterRule(_localctx, 24, PostAnvilParser::RuleAttr_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    attr_lvalue();
    setState(183);
    match(PostAnvilParser::ASSIGN);
    setState(184);
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
PostAnvilParser::Attr_lvalueContext* PostAnvilParser::attr_lvalue() {
  Attr_lvalueContext *_localctx = _tracker.createInstance<Attr_lvalueContext>(_ctx, getState());
  enterRule(_localctx, 26, PostAnvilParser::RuleAttr_lvalue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(192);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(186);
        match(PostAnvilParser::SELF);
        setState(187);
        match(PostAnvilParser::DOT);
        setState(188);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(189);
        match(PostAnvilParser::STRING);
        setState(190);
        match(PostAnvilParser::DOT);
        setState(191);
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

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Func_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Func_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
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

std::vector<PostAnvilParser::Func_statementContext *> PostAnvilParser::Func_ruleContext::func_statement() {
  return getRuleContexts<PostAnvilParser::Func_statementContext>();
}

PostAnvilParser::Func_statementContext* PostAnvilParser::Func_ruleContext::func_statement(size_t i) {
  return getRuleContext<PostAnvilParser::Func_statementContext>(i);
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

PostAnvilParser::Func_ruleContext* PostAnvilParser::func_rule() {
  Func_ruleContext *_localctx = _tracker.createInstance<Func_ruleContext>(_ctx, getState());
  enterRule(_localctx, 28, PostAnvilParser::RuleFunc_rule);
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
    setState(194);
    match(PostAnvilParser::RULE);
    setState(195);
    match(PostAnvilParser::FUNC);
    setState(196);
    antlrcpp::downCast<Func_ruleContext *>(_localctx)->name = match(PostAnvilParser::IDENTIFIER);
    setState(197);
    match(PostAnvilParser::LPAREN);
    setState(199);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::IDENTIFIER) {
      setState(198);
      typed_params();
    }
    setState(201);
    match(PostAnvilParser::RPAREN);
    setState(204);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ARROW) {
      setState(202);
      match(PostAnvilParser::ARROW);
      setState(203);
      antlrcpp::downCast<Func_ruleContext *>(_localctx)->return_type = type();
    }
    setState(206);
    match(PostAnvilParser::T__0);
    setState(207);
    newlines();
    setState(211); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(208);
      func_statement();
      setState(209);
      newlines();
      setState(213); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984394297344) != 0));
    setState(215);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Typed_paramsContext* PostAnvilParser::typed_params() {
  Typed_paramsContext *_localctx = _tracker.createInstance<Typed_paramsContext>(_ctx, getState());
  enterRule(_localctx, 30, PostAnvilParser::RuleTyped_params);
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
    setState(217);
    typed_param();
    setState(222);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(218);
      match(PostAnvilParser::COMMA);
      setState(219);
      typed_param();
      setState(224);
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

PostAnvilParser::Typed_paramContext* PostAnvilParser::typed_param() {
  Typed_paramContext *_localctx = _tracker.createInstance<Typed_paramContext>(_ctx, getState());
  enterRule(_localctx, 32, PostAnvilParser::RuleTyped_param);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_name = match(PostAnvilParser::IDENTIFIER);
    setState(226);
    match(PostAnvilParser::T__0);
    setState(227);
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_type = type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Func_statementContext ------------------------------------------------------------------

PostAnvilParser::Func_statementContext::Func_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t PostAnvilParser::Func_statementContext::getRuleIndex() const {
  return PostAnvilParser::RuleFunc_statement;
}

void PostAnvilParser::Func_statementContext::copyFrom(Func_statementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FuncVarDefContext ------------------------------------------------------------------

PostAnvilParser::TypeContext* PostAnvilParser::FuncVarDefContext::type() {
  return getRuleContext<PostAnvilParser::TypeContext>(0);
}

tree::TerminalNode* PostAnvilParser::FuncVarDefContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::FuncVarDefContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::FuncVarDefContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::FuncVarDefContext::FuncVarDefContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncVarDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncVarDef(this);
}
void PostAnvilParser::FuncVarDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncVarDef(this);
}
//----------------- FuncIfStmtContext ------------------------------------------------------------------

PostAnvilParser::IfStmtContext* PostAnvilParser::FuncIfStmtContext::ifStmt() {
  return getRuleContext<PostAnvilParser::IfStmtContext>(0);
}

PostAnvilParser::FuncIfStmtContext::FuncIfStmtContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncIfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncIfStmt(this);
}
void PostAnvilParser::FuncIfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncIfStmt(this);
}
//----------------- FuncAssignContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::FuncAssignContext::IDENTIFIER() {
  return getToken(PostAnvilParser::IDENTIFIER, 0);
}

tree::TerminalNode* PostAnvilParser::FuncAssignContext::ASSIGN() {
  return getToken(PostAnvilParser::ASSIGN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::FuncAssignContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::FuncAssignContext::FuncAssignContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncAssign(this);
}
void PostAnvilParser::FuncAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncAssign(this);
}
//----------------- FuncExprStmtContext ------------------------------------------------------------------

PostAnvilParser::ExprContext* PostAnvilParser::FuncExprStmtContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::FuncExprStmtContext::FuncExprStmtContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncExprStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncExprStmt(this);
}
void PostAnvilParser::FuncExprStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncExprStmt(this);
}
//----------------- FuncForStmtContext ------------------------------------------------------------------

PostAnvilParser::ForStmtContext* PostAnvilParser::FuncForStmtContext::forStmt() {
  return getRuleContext<PostAnvilParser::ForStmtContext>(0);
}

PostAnvilParser::FuncForStmtContext::FuncForStmtContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncForStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncForStmt(this);
}
void PostAnvilParser::FuncForStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncForStmt(this);
}
//----------------- FuncReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* PostAnvilParser::FuncReturnStmtContext::RETURN() {
  return getToken(PostAnvilParser::RETURN, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::FuncReturnStmtContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

PostAnvilParser::FuncReturnStmtContext::FuncReturnStmtContext(Func_statementContext *ctx) { copyFrom(ctx); }

void PostAnvilParser::FuncReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncReturnStmt(this);
}
void PostAnvilParser::FuncReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncReturnStmt(this);
}
PostAnvilParser::Func_statementContext* PostAnvilParser::func_statement() {
  Func_statementContext *_localctx = _tracker.createInstance<Func_statementContext>(_ctx, getState());
  enterRule(_localctx, 34, PostAnvilParser::RuleFunc_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(229);
      type();
      setState(230);
      match(PostAnvilParser::IDENTIFIER);
      setState(231);
      match(PostAnvilParser::ASSIGN);
      setState(232);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncAssignContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(234);
      match(PostAnvilParser::IDENTIFIER);
      setState(235);
      match(PostAnvilParser::ASSIGN);
      setState(236);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncIfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(237);
      ifStmt();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncForStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(238);
      forStmt();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(239);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(240);
      match(PostAnvilParser::RETURN);
      setState(241);
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

tree::TerminalNode* PostAnvilParser::IfStmtContext::IF() {
  return getToken(PostAnvilParser::IF, 0);
}

PostAnvilParser::ExprContext* PostAnvilParser::IfStmtContext::expr() {
  return getRuleContext<PostAnvilParser::ExprContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::IfStmtContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::IfStmtContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::IfStmtContext::ENDIF() {
  return getToken(PostAnvilParser::ENDIF, 0);
}

std::vector<PostAnvilParser::Func_statementContext *> PostAnvilParser::IfStmtContext::func_statement() {
  return getRuleContexts<PostAnvilParser::Func_statementContext>();
}

PostAnvilParser::Func_statementContext* PostAnvilParser::IfStmtContext::func_statement(size_t i) {
  return getRuleContext<PostAnvilParser::Func_statementContext>(i);
}

tree::TerminalNode* PostAnvilParser::IfStmtContext::ELSE() {
  return getToken(PostAnvilParser::ELSE, 0);
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

PostAnvilParser::IfStmtContext* PostAnvilParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 36, PostAnvilParser::RuleIfStmt);
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
    setState(244);
    match(PostAnvilParser::IF);
    setState(245);
    expr();
    setState(246);
    newlines();
    setState(252);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984394297344) != 0)) {
      setState(247);
      func_statement();
      setState(248);
      newlines();
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ELSE) {
      setState(255);
      match(PostAnvilParser::ELSE);
      setState(256);
      newlines();
      setState(262);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 496984394297344) != 0)) {
        setState(257);
        func_statement();
        setState(258);
        newlines();
        setState(264);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(267);
    match(PostAnvilParser::ENDIF);
   
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

PostAnvilParser::Class_exprContext* PostAnvilParser::ForStmtContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::ForStmtContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ForStmtContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::ForStmtContext::ENDFOR() {
  return getToken(PostAnvilParser::ENDFOR, 0);
}

std::vector<PostAnvilParser::Func_statementContext *> PostAnvilParser::ForStmtContext::func_statement() {
  return getRuleContexts<PostAnvilParser::Func_statementContext>();
}

PostAnvilParser::Func_statementContext* PostAnvilParser::ForStmtContext::func_statement(size_t i) {
  return getRuleContext<PostAnvilParser::Func_statementContext>(i);
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

PostAnvilParser::ForStmtContext* PostAnvilParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 38, PostAnvilParser::RuleForStmt);
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
    setState(269);
    match(PostAnvilParser::FOR);
    setState(270);
    match(PostAnvilParser::IDENTIFIER);
    setState(271);
    match(PostAnvilParser::IN);
    setState(272);
    class_expr();
    setState(273);
    newlines();
    setState(279);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984394297344) != 0)) {
      setState(274);
      func_statement();
      setState(275);
      newlines();
      setState(281);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(282);
    match(PostAnvilParser::ENDFOR);
   
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

std::vector<PostAnvilParser::Class_exprContext *> PostAnvilParser::Group_ruleContext::class_expr() {
  return getRuleContexts<PostAnvilParser::Class_exprContext>();
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Group_ruleContext::class_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Class_exprContext>(i);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::FROM() {
  return getToken(PostAnvilParser::FROM, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Group_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Group_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

std::vector<PostAnvilParser::Bool_exprContext *> PostAnvilParser::Group_ruleContext::bool_expr() {
  return getRuleContexts<PostAnvilParser::Bool_exprContext>();
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::Group_ruleContext::bool_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Bool_exprContext>(i);
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

PostAnvilParser::Group_ruleContext* PostAnvilParser::group_rule() {
  Group_ruleContext *_localctx = _tracker.createInstance<Group_ruleContext>(_ctx, getState());
  enterRule(_localctx, 40, PostAnvilParser::RuleGroup_rule);
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
    setState(284);
    match(PostAnvilParser::RULE);
    setState(285);
    match(PostAnvilParser::GROUP);
    setState(286);
    class_expr();
    setState(287);
    match(PostAnvilParser::FROM);
    setState(288);
    class_expr();
    setState(289);
    match(PostAnvilParser::T__0);
    setState(290);
    newlines();
    setState(296);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984356040704) != 0)) {
      setState(291);
      bool_expr();
      setState(292);
      newlines();
      setState(298);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(299);
    match(PostAnvilParser::RULEEND);
   
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

std::vector<PostAnvilParser::Class_exprContext *> PostAnvilParser::Append_ruleContext::class_expr() {
  return getRuleContexts<PostAnvilParser::Class_exprContext>();
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Append_ruleContext::class_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Class_exprContext>(i);
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::FROM() {
  return getToken(PostAnvilParser::FROM, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Append_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Append_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

std::vector<PostAnvilParser::Bool_exprContext *> PostAnvilParser::Append_ruleContext::bool_expr() {
  return getRuleContexts<PostAnvilParser::Bool_exprContext>();
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::Append_ruleContext::bool_expr(size_t i) {
  return getRuleContext<PostAnvilParser::Bool_exprContext>(i);
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

PostAnvilParser::Append_ruleContext* PostAnvilParser::append_rule() {
  Append_ruleContext *_localctx = _tracker.createInstance<Append_ruleContext>(_ctx, getState());
  enterRule(_localctx, 42, PostAnvilParser::RuleAppend_rule);
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
    setState(301);
    match(PostAnvilParser::RULE);
    setState(302);
    match(PostAnvilParser::APPEND);
    setState(303);
    class_expr();
    setState(304);
    match(PostAnvilParser::FROM);
    setState(305);
    class_expr();
    setState(306);
    match(PostAnvilParser::T__0);
    setState(307);
    newlines();
    setState(313);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984356040704) != 0)) {
      setState(308);
      bool_expr();
      setState(309);
      newlines();
      setState(315);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(316);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Class_exprContext* PostAnvilParser::class_expr() {
  Class_exprContext *_localctx = _tracker.createInstance<Class_exprContext>(_ctx, getState());
  enterRule(_localctx, 44, PostAnvilParser::RuleClass_expr);
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
    setState(318);
    _la = _input->LA(1);
    if (!(_la == PostAnvilParser::STRING

    || _la == PostAnvilParser::IDENTIFIER)) {
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

PostAnvilParser::Bool_exprContext* PostAnvilParser::bool_expr() {
  Bool_exprContext *_localctx = _tracker.createInstance<Bool_exprContext>(_ctx, getState());
  enterRule(_localctx, 46, PostAnvilParser::RuleBool_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(320);
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

PostAnvilParser::ExprContext* PostAnvilParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 48, PostAnvilParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(322);
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
  enterRule(_localctx, 50, PostAnvilParser::RuleOr_expr);
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
    setState(324);
    and_expr();
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::OR) {
      setState(325);
      match(PostAnvilParser::OR);
      setState(326);
      and_expr();
      setState(331);
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
  enterRule(_localctx, 52, PostAnvilParser::RuleAnd_expr);
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
    setState(332);
    not_expr();
    setState(337);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::AND) {
      setState(333);
      match(PostAnvilParser::AND);
      setState(334);
      not_expr();
      setState(339);
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
  enterRule(_localctx, 54, PostAnvilParser::RuleNot_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(343);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(340);
        match(PostAnvilParser::NOT);
        setState(341);
        not_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::SORT:
      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::MINUS:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(342);
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
  enterRule(_localctx, 56, PostAnvilParser::RuleCmp_expr);
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
    setState(345);
    add_expr();
    setState(349);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2164663517184) != 0)) {
      setState(346);
      comp_op();
      setState(347);
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
  enterRule(_localctx, 58, PostAnvilParser::RuleAdd_expr);
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
    setState(351);
    mul_expr();
    setState(357);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS) {
      setState(352);
      add_op();
      setState(353);
      mul_expr();
      setState(359);
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
  enterRule(_localctx, 60, PostAnvilParser::RuleMul_expr);
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
    setState(360);
    unary_expr();
    setState(366);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH) {
      setState(361);
      mul_op();
      setState(362);
      unary_expr();
      setState(368);
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
  enterRule(_localctx, 62, PostAnvilParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(369);
        match(PostAnvilParser::MINUS);
        setState(370);
        unary_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::SORT:
      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(371);
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

PostAnvilParser::SortExprContext* PostAnvilParser::PrimaryContext::sortExpr() {
  return getRuleContext<PostAnvilParser::SortExprContext>(0);
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

PostAnvilParser::PrimaryContext* PostAnvilParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 64, PostAnvilParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(385);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(374);
      match(PostAnvilParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(375);
      match(PostAnvilParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(376);
      match(PostAnvilParser::BOOL_LIT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(377);
      func_call();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(378);
      attribute();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(379);
      match(PostAnvilParser::LPAREN);
      setState(380);
      expr();
      setState(381);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(383);
      sortExpr();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(384);
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

PostAnvilParser::Func_callContext* PostAnvilParser::func_call() {
  Func_callContext *_localctx = _tracker.createInstance<Func_callContext>(_ctx, getState());
  enterRule(_localctx, 66, PostAnvilParser::RuleFunc_call);
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
    match(PostAnvilParser::IDENTIFIER);
    setState(388);
    match(PostAnvilParser::LPAREN);
    setState(397);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 496984356040704) != 0)) {
      setState(389);
      expr();
      setState(394);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PostAnvilParser::COMMA) {
        setState(390);
        match(PostAnvilParser::COMMA);
        setState(391);
        expr();
        setState(396);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(399);
    match(PostAnvilParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SortExprContext ------------------------------------------------------------------

PostAnvilParser::SortExprContext::SortExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::SortExprContext::SORT() {
  return getToken(PostAnvilParser::SORT, 0);
}

tree::TerminalNode* PostAnvilParser::SortExprContext::LPAREN() {
  return getToken(PostAnvilParser::LPAREN, 0);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::SortExprContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<tree::TerminalNode *> PostAnvilParser::SortExprContext::COMMA() {
  return getTokens(PostAnvilParser::COMMA);
}

tree::TerminalNode* PostAnvilParser::SortExprContext::COMMA(size_t i) {
  return getToken(PostAnvilParser::COMMA, i);
}

std::vector<PostAnvilParser::ExprContext *> PostAnvilParser::SortExprContext::expr() {
  return getRuleContexts<PostAnvilParser::ExprContext>();
}

PostAnvilParser::ExprContext* PostAnvilParser::SortExprContext::expr(size_t i) {
  return getRuleContext<PostAnvilParser::ExprContext>(i);
}

tree::TerminalNode* PostAnvilParser::SortExprContext::RPAREN() {
  return getToken(PostAnvilParser::RPAREN, 0);
}


size_t PostAnvilParser::SortExprContext::getRuleIndex() const {
  return PostAnvilParser::RuleSortExpr;
}

void PostAnvilParser::SortExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSortExpr(this);
}

void PostAnvilParser::SortExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<PostAnvilListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSortExpr(this);
}

PostAnvilParser::SortExprContext* PostAnvilParser::sortExpr() {
  SortExprContext *_localctx = _tracker.createInstance<SortExprContext>(_ctx, getState());
  enterRule(_localctx, 68, PostAnvilParser::RuleSortExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(401);
    match(PostAnvilParser::SORT);
    setState(402);
    match(PostAnvilParser::LPAREN);
    setState(403);
    class_expr();
    setState(404);
    match(PostAnvilParser::COMMA);
    setState(405);
    expr();
    setState(406);
    match(PostAnvilParser::COMMA);
    setState(407);
    expr();
    setState(408);
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
PostAnvilParser::AttributeContext* PostAnvilParser::attribute() {
  AttributeContext *_localctx = _tracker.createInstance<AttributeContext>(_ctx, getState());
  enterRule(_localctx, 70, PostAnvilParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(419);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(410);
        match(PostAnvilParser::SELF);
        setState(411);
        match(PostAnvilParser::DOT);
        setState(412);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(413);
        match(PostAnvilParser::STRING);
        setState(414);
        match(PostAnvilParser::DOT);
        setState(415);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<PostAnvilParser::VarInstanceAttrContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(416);
        match(PostAnvilParser::IDENTIFIER);
        setState(417);
        match(PostAnvilParser::DOT);
        setState(418);
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
  enterRule(_localctx, 72, PostAnvilParser::RuleComp_op);
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
    setState(421);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2164663517184) != 0))) {
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
  enterRule(_localctx, 74, PostAnvilParser::RuleAdd_op);
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
    setState(423);
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
  enterRule(_localctx, 76, PostAnvilParser::RuleMul_op);
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
    setState(425);
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
