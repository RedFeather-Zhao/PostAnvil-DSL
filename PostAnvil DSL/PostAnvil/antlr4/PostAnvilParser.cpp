
// Generated from D:/UserProject/vsstudio/PostAnvil DSL/PostAnvil DSL/docs/PostAnvil.g4 by ANTLR 4.13.2


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
      "program", "declaration", "importDef", "importItem", "exportDef", 
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
      "'NUM'", "'STR'", "'BOOL'", "'RETURN'", "'IMPORT'", "'EXPORT'", "'AS'", 
      "'IF'", "'ELSE'", "'ENDIF'", "'FOR'", "'IN'", "'ENDFOR'", "'SORT'", 
      "", "'->'", "'+'", "'-'", "'*'", "'/'", "'<'", "'>'", "'<='", "'>='", 
      "'=='", "'!='", "'.'", "'('", "')'", "','", "'='"
    },
    std::vector<std::string>{
      "", "", "RULE", "RULEEND", "FILTER", "ATTR", "FUNC", "GROUP", "APPEND", 
      "FROM", "AND", "OR", "NOT", "SELF", "NUM", "STR", "BOOL", "RETURN", 
      "IMPORT", "EXPORT", "AS", "IF", "ELSE", "ENDIF", "FOR", "IN", "ENDFOR", 
      "SORT", "BOOL_LIT", "ARROW", "PLUS", "MINUS", "STAR", "SLASH", "LT", 
      "GT", "LE", "GE", "EQ", "NE", "DOT", "LPAREN", "RPAREN", "COMMA", 
      "ASSIGN", "NUMBER", "STRING", "IDENTIFIER", "WS", "NEWLINE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,50,419,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,1,0,1,0,5,0,79,8,0,10,0,12,0,82,9,0,1,0,1,0,5,
  	0,86,8,0,10,0,12,0,89,9,0,1,0,1,0,1,1,1,1,1,1,3,1,96,8,1,1,2,1,2,1,2,
  	1,2,5,2,102,8,2,10,2,12,2,105,9,2,1,2,1,2,1,3,1,3,1,3,1,3,3,3,113,8,3,
  	1,4,1,4,1,4,1,4,5,4,119,8,4,10,4,12,4,122,9,4,1,4,1,4,1,5,1,5,1,5,1,5,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,8,3,8,143,8,8,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,153,8,9,10,9,12,9,156,9,9,1,9,1,9,1,10,
  	1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,168,8,10,10,10,12,10,171,9,10,
  	1,10,1,10,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,3,12,185,
  	8,12,1,13,1,13,1,13,1,13,1,13,3,13,192,8,13,1,13,1,13,1,13,3,13,197,8,
  	13,1,13,1,13,1,13,1,13,1,13,4,13,204,8,13,11,13,12,13,205,1,13,1,13,1,
  	14,1,14,1,14,5,14,213,8,14,10,14,12,14,216,9,14,1,15,1,15,1,15,1,15,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,235,
  	8,16,1,17,1,17,1,17,1,17,1,17,1,17,5,17,243,8,17,10,17,12,17,246,9,17,
  	1,17,1,17,1,17,1,17,1,17,5,17,253,8,17,10,17,12,17,256,9,17,3,17,258,
  	8,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,5,18,270,8,18,
  	10,18,12,18,273,9,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,
  	1,19,1,19,5,19,287,8,19,10,19,12,19,290,9,19,1,19,1,19,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,5,20,304,8,20,10,20,12,20,307,9,20,
  	1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,24,5,24,320,8,24,
  	10,24,12,24,323,9,24,1,25,1,25,1,25,5,25,328,8,25,10,25,12,25,331,9,25,
  	1,26,1,26,1,26,3,26,336,8,26,1,27,1,27,1,27,1,27,3,27,342,8,27,1,28,1,
  	28,1,28,1,28,5,28,348,8,28,10,28,12,28,351,9,28,1,29,1,29,1,29,1,29,5,
  	29,357,8,29,10,29,12,29,360,9,29,1,30,1,30,1,30,3,30,365,8,30,1,31,1,
  	31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,3,31,377,8,31,1,32,1,32,1,
  	32,1,32,1,32,5,32,384,8,32,10,32,12,32,387,9,32,3,32,389,8,32,1,32,1,
  	32,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,
  	34,1,34,1,34,1,34,1,34,3,34,411,8,34,1,35,1,35,1,36,1,36,1,37,1,37,1,
  	37,0,0,38,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,0,5,1,0,14,16,1,0,46,
  	47,1,0,34,39,1,0,30,31,1,0,32,33,428,0,80,1,0,0,0,2,95,1,0,0,0,4,97,1,
  	0,0,0,6,108,1,0,0,0,8,114,1,0,0,0,10,125,1,0,0,0,12,129,1,0,0,0,14,135,
  	1,0,0,0,16,142,1,0,0,0,18,144,1,0,0,0,20,159,1,0,0,0,22,174,1,0,0,0,24,
  	184,1,0,0,0,26,186,1,0,0,0,28,209,1,0,0,0,30,217,1,0,0,0,32,234,1,0,0,
  	0,34,236,1,0,0,0,36,261,1,0,0,0,38,276,1,0,0,0,40,293,1,0,0,0,42,310,
  	1,0,0,0,44,312,1,0,0,0,46,314,1,0,0,0,48,316,1,0,0,0,50,324,1,0,0,0,52,
  	335,1,0,0,0,54,337,1,0,0,0,56,343,1,0,0,0,58,352,1,0,0,0,60,364,1,0,0,
  	0,62,376,1,0,0,0,64,378,1,0,0,0,66,392,1,0,0,0,68,410,1,0,0,0,70,412,
  	1,0,0,0,72,414,1,0,0,0,74,416,1,0,0,0,76,79,3,2,1,0,77,79,5,49,0,0,78,
  	76,1,0,0,0,78,77,1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,81,1,0,0,0,81,
  	87,1,0,0,0,82,80,1,0,0,0,83,86,3,16,8,0,84,86,5,49,0,0,85,83,1,0,0,0,
  	85,84,1,0,0,0,86,89,1,0,0,0,87,85,1,0,0,0,87,88,1,0,0,0,88,90,1,0,0,0,
  	89,87,1,0,0,0,90,91,5,0,0,1,91,1,1,0,0,0,92,96,3,4,2,0,93,96,3,8,4,0,
  	94,96,3,12,6,0,95,92,1,0,0,0,95,93,1,0,0,0,95,94,1,0,0,0,96,3,1,0,0,0,
  	97,98,5,18,0,0,98,103,3,6,3,0,99,100,5,43,0,0,100,102,3,6,3,0,101,99,
  	1,0,0,0,102,105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,
  	0,105,103,1,0,0,0,106,107,5,49,0,0,107,5,1,0,0,0,108,109,3,14,7,0,109,
  	112,5,47,0,0,110,111,5,20,0,0,111,113,5,47,0,0,112,110,1,0,0,0,112,113,
  	1,0,0,0,113,7,1,0,0,0,114,115,5,19,0,0,115,120,3,10,5,0,116,117,5,43,
  	0,0,117,119,3,10,5,0,118,116,1,0,0,0,119,122,1,0,0,0,120,118,1,0,0,0,
  	120,121,1,0,0,0,121,123,1,0,0,0,122,120,1,0,0,0,123,124,5,49,0,0,124,
  	9,1,0,0,0,125,126,3,46,23,0,126,127,5,20,0,0,127,128,5,47,0,0,128,11,
  	1,0,0,0,129,130,3,14,7,0,130,131,5,47,0,0,131,132,5,44,0,0,132,133,3,
  	46,23,0,133,134,5,49,0,0,134,13,1,0,0,0,135,136,7,0,0,0,136,15,1,0,0,
  	0,137,143,3,18,9,0,138,143,3,20,10,0,139,143,3,26,13,0,140,143,3,38,19,
  	0,141,143,3,40,20,0,142,137,1,0,0,0,142,138,1,0,0,0,142,139,1,0,0,0,142,
  	140,1,0,0,0,142,141,1,0,0,0,143,17,1,0,0,0,144,145,5,2,0,0,145,146,5,
  	4,0,0,146,147,3,42,21,0,147,148,5,1,0,0,148,154,5,49,0,0,149,150,3,44,
  	22,0,150,151,5,49,0,0,151,153,1,0,0,0,152,149,1,0,0,0,153,156,1,0,0,0,
  	154,152,1,0,0,0,154,155,1,0,0,0,155,157,1,0,0,0,156,154,1,0,0,0,157,158,
  	5,3,0,0,158,19,1,0,0,0,159,160,5,2,0,0,160,161,5,5,0,0,161,162,3,42,21,
  	0,162,163,5,1,0,0,163,169,5,49,0,0,164,165,3,22,11,0,165,166,5,49,0,0,
  	166,168,1,0,0,0,167,164,1,0,0,0,168,171,1,0,0,0,169,167,1,0,0,0,169,170,
  	1,0,0,0,170,172,1,0,0,0,171,169,1,0,0,0,172,173,5,3,0,0,173,21,1,0,0,
  	0,174,175,3,24,12,0,175,176,5,44,0,0,176,177,3,46,23,0,177,23,1,0,0,0,
  	178,179,5,13,0,0,179,180,5,40,0,0,180,185,5,47,0,0,181,182,5,46,0,0,182,
  	183,5,40,0,0,183,185,5,47,0,0,184,178,1,0,0,0,184,181,1,0,0,0,185,25,
  	1,0,0,0,186,187,5,2,0,0,187,188,5,6,0,0,188,189,5,47,0,0,189,191,5,41,
  	0,0,190,192,3,28,14,0,191,190,1,0,0,0,191,192,1,0,0,0,192,193,1,0,0,0,
  	193,196,5,42,0,0,194,195,5,29,0,0,195,197,3,14,7,0,196,194,1,0,0,0,196,
  	197,1,0,0,0,197,198,1,0,0,0,198,199,5,1,0,0,199,203,5,49,0,0,200,201,
  	3,32,16,0,201,202,5,49,0,0,202,204,1,0,0,0,203,200,1,0,0,0,204,205,1,
  	0,0,0,205,203,1,0,0,0,205,206,1,0,0,0,206,207,1,0,0,0,207,208,5,3,0,0,
  	208,27,1,0,0,0,209,214,3,30,15,0,210,211,5,43,0,0,211,213,3,30,15,0,212,
  	210,1,0,0,0,213,216,1,0,0,0,214,212,1,0,0,0,214,215,1,0,0,0,215,29,1,
  	0,0,0,216,214,1,0,0,0,217,218,5,47,0,0,218,219,5,1,0,0,219,220,3,14,7,
  	0,220,31,1,0,0,0,221,222,3,14,7,0,222,223,5,47,0,0,223,224,5,44,0,0,224,
  	225,3,46,23,0,225,235,1,0,0,0,226,227,5,47,0,0,227,228,5,44,0,0,228,235,
  	3,46,23,0,229,235,3,34,17,0,230,235,3,36,18,0,231,235,3,46,23,0,232,233,
  	5,17,0,0,233,235,3,46,23,0,234,221,1,0,0,0,234,226,1,0,0,0,234,229,1,
  	0,0,0,234,230,1,0,0,0,234,231,1,0,0,0,234,232,1,0,0,0,235,33,1,0,0,0,
  	236,237,5,21,0,0,237,238,3,46,23,0,238,244,5,49,0,0,239,240,3,32,16,0,
  	240,241,5,49,0,0,241,243,1,0,0,0,242,239,1,0,0,0,243,246,1,0,0,0,244,
  	242,1,0,0,0,244,245,1,0,0,0,245,257,1,0,0,0,246,244,1,0,0,0,247,248,5,
  	22,0,0,248,254,5,49,0,0,249,250,3,32,16,0,250,251,5,49,0,0,251,253,1,
  	0,0,0,252,249,1,0,0,0,253,256,1,0,0,0,254,252,1,0,0,0,254,255,1,0,0,0,
  	255,258,1,0,0,0,256,254,1,0,0,0,257,247,1,0,0,0,257,258,1,0,0,0,258,259,
  	1,0,0,0,259,260,5,23,0,0,260,35,1,0,0,0,261,262,5,24,0,0,262,263,5,47,
  	0,0,263,264,5,25,0,0,264,265,3,42,21,0,265,271,5,49,0,0,266,267,3,32,
  	16,0,267,268,5,49,0,0,268,270,1,0,0,0,269,266,1,0,0,0,270,273,1,0,0,0,
  	271,269,1,0,0,0,271,272,1,0,0,0,272,274,1,0,0,0,273,271,1,0,0,0,274,275,
  	5,26,0,0,275,37,1,0,0,0,276,277,5,2,0,0,277,278,5,7,0,0,278,279,5,46,
  	0,0,279,280,5,9,0,0,280,281,3,42,21,0,281,282,5,1,0,0,282,288,5,49,0,
  	0,283,284,3,44,22,0,284,285,5,49,0,0,285,287,1,0,0,0,286,283,1,0,0,0,
  	287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,0,0,0,289,291,1,0,0,0,290,288,
  	1,0,0,0,291,292,5,3,0,0,292,39,1,0,0,0,293,294,5,2,0,0,294,295,5,8,0,
  	0,295,296,3,42,21,0,296,297,5,9,0,0,297,298,3,42,21,0,298,299,5,1,0,0,
  	299,305,5,49,0,0,300,301,3,44,22,0,301,302,5,49,0,0,302,304,1,0,0,0,303,
  	300,1,0,0,0,304,307,1,0,0,0,305,303,1,0,0,0,305,306,1,0,0,0,306,308,1,
  	0,0,0,307,305,1,0,0,0,308,309,5,3,0,0,309,41,1,0,0,0,310,311,7,1,0,0,
  	311,43,1,0,0,0,312,313,3,48,24,0,313,45,1,0,0,0,314,315,3,48,24,0,315,
  	47,1,0,0,0,316,321,3,50,25,0,317,318,5,11,0,0,318,320,3,50,25,0,319,317,
  	1,0,0,0,320,323,1,0,0,0,321,319,1,0,0,0,321,322,1,0,0,0,322,49,1,0,0,
  	0,323,321,1,0,0,0,324,329,3,52,26,0,325,326,5,10,0,0,326,328,3,52,26,
  	0,327,325,1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,
  	51,1,0,0,0,331,329,1,0,0,0,332,333,5,12,0,0,333,336,3,52,26,0,334,336,
  	3,54,27,0,335,332,1,0,0,0,335,334,1,0,0,0,336,53,1,0,0,0,337,341,3,56,
  	28,0,338,339,3,70,35,0,339,340,3,56,28,0,340,342,1,0,0,0,341,338,1,0,
  	0,0,341,342,1,0,0,0,342,55,1,0,0,0,343,349,3,58,29,0,344,345,3,72,36,
  	0,345,346,3,58,29,0,346,348,1,0,0,0,347,344,1,0,0,0,348,351,1,0,0,0,349,
  	347,1,0,0,0,349,350,1,0,0,0,350,57,1,0,0,0,351,349,1,0,0,0,352,358,3,
  	60,30,0,353,354,3,74,37,0,354,355,3,60,30,0,355,357,1,0,0,0,356,353,1,
  	0,0,0,357,360,1,0,0,0,358,356,1,0,0,0,358,359,1,0,0,0,359,59,1,0,0,0,
  	360,358,1,0,0,0,361,362,5,31,0,0,362,365,3,60,30,0,363,365,3,62,31,0,
  	364,361,1,0,0,0,364,363,1,0,0,0,365,61,1,0,0,0,366,377,5,45,0,0,367,377,
  	5,46,0,0,368,377,5,28,0,0,369,377,3,64,32,0,370,377,3,68,34,0,371,372,
  	5,41,0,0,372,373,3,46,23,0,373,374,5,42,0,0,374,377,1,0,0,0,375,377,3,
  	66,33,0,376,366,1,0,0,0,376,367,1,0,0,0,376,368,1,0,0,0,376,369,1,0,0,
  	0,376,370,1,0,0,0,376,371,1,0,0,0,376,375,1,0,0,0,377,63,1,0,0,0,378,
  	379,5,47,0,0,379,388,5,41,0,0,380,385,3,46,23,0,381,382,5,43,0,0,382,
  	384,3,46,23,0,383,381,1,0,0,0,384,387,1,0,0,0,385,383,1,0,0,0,385,386,
  	1,0,0,0,386,389,1,0,0,0,387,385,1,0,0,0,388,380,1,0,0,0,388,389,1,0,0,
  	0,389,390,1,0,0,0,390,391,5,42,0,0,391,65,1,0,0,0,392,393,5,27,0,0,393,
  	394,5,41,0,0,394,395,3,42,21,0,395,396,5,43,0,0,396,397,3,46,23,0,397,
  	398,5,43,0,0,398,399,3,46,23,0,399,400,5,42,0,0,400,67,1,0,0,0,401,402,
  	5,13,0,0,402,403,5,40,0,0,403,411,5,47,0,0,404,405,5,46,0,0,405,406,5,
  	40,0,0,406,411,5,47,0,0,407,408,5,47,0,0,408,409,5,40,0,0,409,411,5,47,
  	0,0,410,401,1,0,0,0,410,404,1,0,0,0,410,407,1,0,0,0,411,69,1,0,0,0,412,
  	413,7,2,0,0,413,71,1,0,0,0,414,415,7,3,0,0,415,73,1,0,0,0,416,417,7,4,
  	0,0,417,75,1,0,0,0,34,78,80,85,87,95,103,112,120,142,154,169,184,191,
  	196,205,214,234,244,254,257,271,288,305,321,329,335,341,349,358,364,376,
  	385,388,410
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

std::vector<tree::TerminalNode *> PostAnvilParser::ProgramContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::ProgramContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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
    setState(80);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(78);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PostAnvilParser::NUM:
          case PostAnvilParser::STR:
          case PostAnvilParser::BOOL:
          case PostAnvilParser::IMPORT:
          case PostAnvilParser::EXPORT: {
            setState(76);
            declaration();
            break;
          }

          case PostAnvilParser::NEWLINE: {
            setState(77);
            match(PostAnvilParser::NEWLINE);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(82);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::RULE

    || _la == PostAnvilParser::NEWLINE) {
      setState(85);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PostAnvilParser::RULE: {
          setState(83);
          rule_();
          break;
        }

        case PostAnvilParser::NEWLINE: {
          setState(84);
          match(PostAnvilParser::NEWLINE);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(90);
    match(PostAnvilParser::EOF);
   
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
  enterRule(_localctx, 2, PostAnvilParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(95);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(92);
        importDef();
        break;
      }

      case PostAnvilParser::EXPORT: {
        enterOuterAlt(_localctx, 2);
        setState(93);
        exportDef();
        break;
      }

      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL: {
        enterOuterAlt(_localctx, 3);
        setState(94);
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

tree::TerminalNode* PostAnvilParser::ImportDefContext::NEWLINE() {
  return getToken(PostAnvilParser::NEWLINE, 0);
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
  enterRule(_localctx, 4, PostAnvilParser::RuleImportDef);
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
    setState(97);
    match(PostAnvilParser::IMPORT);
    setState(98);
    importItem();
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(99);
      match(PostAnvilParser::COMMA);
      setState(100);
      importItem();
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    match(PostAnvilParser::NEWLINE);
   
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
  enterRule(_localctx, 6, PostAnvilParser::RuleImportItem);
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
    setState(108);
    type();
    setState(109);
    antlrcpp::downCast<ImportItemContext *>(_localctx)->host = match(PostAnvilParser::IDENTIFIER);
    setState(112);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::AS) {
      setState(110);
      match(PostAnvilParser::AS);
      setState(111);
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

tree::TerminalNode* PostAnvilParser::ExportDefContext::NEWLINE() {
  return getToken(PostAnvilParser::NEWLINE, 0);
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
  enterRule(_localctx, 8, PostAnvilParser::RuleExportDef);
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
    setState(114);
    match(PostAnvilParser::EXPORT);
    setState(115);
    exportItem();
    setState(120);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(116);
      match(PostAnvilParser::COMMA);
      setState(117);
      exportItem();
      setState(122);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(123);
    match(PostAnvilParser::NEWLINE);
   
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
  enterRule(_localctx, 10, PostAnvilParser::RuleExportItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    expr();
    setState(126);
    match(PostAnvilParser::AS);
    setState(127);
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

tree::TerminalNode* PostAnvilParser::GlobalDefContext::NEWLINE() {
  return getToken(PostAnvilParser::NEWLINE, 0);
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
  enterRule(_localctx, 12, PostAnvilParser::RuleGlobalDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(129);
    type();
    setState(130);
    match(PostAnvilParser::IDENTIFIER);
    setState(131);
    match(PostAnvilParser::ASSIGN);
    setState(132);
    expr();
    setState(133);
    match(PostAnvilParser::NEWLINE);
   
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
  enterRule(_localctx, 14, PostAnvilParser::RuleType);
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
    setState(135);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 114688) != 0))) {
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

PostAnvilParser::Func_ruleContext* PostAnvilParser::Rule_Context::func_rule() {
  return getRuleContext<PostAnvilParser::Func_ruleContext>(0);
}

PostAnvilParser::Group_ruleContext* PostAnvilParser::Rule_Context::group_rule() {
  return getRuleContext<PostAnvilParser::Group_ruleContext>(0);
}

PostAnvilParser::Append_ruleContext* PostAnvilParser::Rule_Context::append_rule() {
  return getRuleContext<PostAnvilParser::Append_ruleContext>(0);
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
  enterRule(_localctx, 16, PostAnvilParser::RuleRule_);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(137);
      filter_rule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(138);
      attr_rule();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(139);
      func_rule();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(140);
      group_rule();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(141);
      append_rule();
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

std::vector<tree::TerminalNode *> PostAnvilParser::Filter_ruleContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::Filter_ruleContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::Filter_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFilter_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Filter_ruleContext* PostAnvilParser::filter_rule() {
  Filter_ruleContext *_localctx = _tracker.createInstance<Filter_ruleContext>(_ctx, getState());
  enterRule(_localctx, 18, PostAnvilParser::RuleFilter_rule);
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
    setState(144);
    match(PostAnvilParser::RULE);
    setState(145);
    match(PostAnvilParser::FILTER);
    setState(146);
    class_expr();
    setState(147);
    match(PostAnvilParser::T__0);
    setState(148);
    match(PostAnvilParser::NEWLINE);
    setState(154);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492178026496) != 0)) {
      setState(149);
      bool_expr();
      setState(150);
      match(PostAnvilParser::NEWLINE);
      setState(156);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(157);
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

std::vector<tree::TerminalNode *> PostAnvilParser::Attr_ruleContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::Attr_ruleContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::Attr_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAttr_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Attr_ruleContext* PostAnvilParser::attr_rule() {
  Attr_ruleContext *_localctx = _tracker.createInstance<Attr_ruleContext>(_ctx, getState());
  enterRule(_localctx, 20, PostAnvilParser::RuleAttr_rule);
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
    setState(159);
    match(PostAnvilParser::RULE);
    setState(160);
    match(PostAnvilParser::ATTR);
    setState(161);
    class_expr();
    setState(162);
    match(PostAnvilParser::T__0);
    setState(163);
    match(PostAnvilParser::NEWLINE);
    setState(169);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::SELF

    || _la == PostAnvilParser::STRING) {
      setState(164);
      attr_def();
      setState(165);
      match(PostAnvilParser::NEWLINE);
      setState(171);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(172);
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


std::any PostAnvilParser::Attr_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAttr_def(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Attr_defContext* PostAnvilParser::attr_def() {
  Attr_defContext *_localctx = _tracker.createInstance<Attr_defContext>(_ctx, getState());
  enterRule(_localctx, 22, PostAnvilParser::RuleAttr_def);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(174);
    attr_lvalue();
    setState(175);
    match(PostAnvilParser::ASSIGN);
    setState(176);
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
  enterRule(_localctx, 24, PostAnvilParser::RuleAttr_lvalue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(178);
        match(PostAnvilParser::SELF);
        setState(179);
        match(PostAnvilParser::DOT);
        setState(180);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(181);
        match(PostAnvilParser::STRING);
        setState(182);
        match(PostAnvilParser::DOT);
        setState(183);
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

std::vector<tree::TerminalNode *> PostAnvilParser::Func_ruleContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::Func_ruleContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::Func_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFunc_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Func_ruleContext* PostAnvilParser::func_rule() {
  Func_ruleContext *_localctx = _tracker.createInstance<Func_ruleContext>(_ctx, getState());
  enterRule(_localctx, 26, PostAnvilParser::RuleFunc_rule);
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
    setState(186);
    match(PostAnvilParser::RULE);
    setState(187);
    match(PostAnvilParser::FUNC);
    setState(188);
    antlrcpp::downCast<Func_ruleContext *>(_localctx)->name = match(PostAnvilParser::IDENTIFIER);
    setState(189);
    match(PostAnvilParser::LPAREN);
    setState(191);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::IDENTIFIER) {
      setState(190);
      typed_params();
    }
    setState(193);
    match(PostAnvilParser::RPAREN);
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ARROW) {
      setState(194);
      match(PostAnvilParser::ARROW);
      setState(195);
      antlrcpp::downCast<Func_ruleContext *>(_localctx)->return_type = type();
    }
    setState(198);
    match(PostAnvilParser::T__0);
    setState(199);
    match(PostAnvilParser::NEWLINE);
    setState(203); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(200);
      func_statement();
      setState(201);
      match(PostAnvilParser::NEWLINE);
      setState(205); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492197146624) != 0));
    setState(207);
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


std::any PostAnvilParser::Typed_paramsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitTyped_params(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Typed_paramsContext* PostAnvilParser::typed_params() {
  Typed_paramsContext *_localctx = _tracker.createInstance<Typed_paramsContext>(_ctx, getState());
  enterRule(_localctx, 28, PostAnvilParser::RuleTyped_params);
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
    setState(209);
    typed_param();
    setState(214);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(210);
      match(PostAnvilParser::COMMA);
      setState(211);
      typed_param();
      setState(216);
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
  enterRule(_localctx, 30, PostAnvilParser::RuleTyped_param);

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
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_name = match(PostAnvilParser::IDENTIFIER);
    setState(218);
    match(PostAnvilParser::T__0);
    setState(219);
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

std::any PostAnvilParser::FuncVarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncVarDef(this);
  else
    return visitor->visitChildren(this);
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

std::any PostAnvilParser::FuncIfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncIfStmt(this);
  else
    return visitor->visitChildren(this);
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

std::any PostAnvilParser::FuncAssignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncAssign(this);
  else
    return visitor->visitChildren(this);
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

std::any PostAnvilParser::FuncExprStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncExprStmt(this);
  else
    return visitor->visitChildren(this);
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

std::any PostAnvilParser::FuncForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncForStmt(this);
  else
    return visitor->visitChildren(this);
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

std::any PostAnvilParser::FuncReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitFuncReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
PostAnvilParser::Func_statementContext* PostAnvilParser::func_statement() {
  Func_statementContext *_localctx = _tracker.createInstance<Func_statementContext>(_ctx, getState());
  enterRule(_localctx, 32, PostAnvilParser::RuleFunc_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(234);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(221);
      type();
      setState(222);
      match(PostAnvilParser::IDENTIFIER);
      setState(223);
      match(PostAnvilParser::ASSIGN);
      setState(224);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncAssignContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(226);
      match(PostAnvilParser::IDENTIFIER);
      setState(227);
      match(PostAnvilParser::ASSIGN);
      setState(228);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncIfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(229);
      ifStmt();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncForStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(230);
      forStmt();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(231);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(232);
      match(PostAnvilParser::RETURN);
      setState(233);
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

std::vector<tree::TerminalNode *> PostAnvilParser::IfStmtContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::IfStmtContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::IfStmtContext* PostAnvilParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 34, PostAnvilParser::RuleIfStmt);
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
    setState(236);
    match(PostAnvilParser::IF);
    setState(237);
    expr();
    setState(238);
    match(PostAnvilParser::NEWLINE);
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492197146624) != 0)) {
      setState(239);
      func_statement();
      setState(240);
      match(PostAnvilParser::NEWLINE);
      setState(246);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ELSE) {
      setState(247);
      match(PostAnvilParser::ELSE);
      setState(248);
      match(PostAnvilParser::NEWLINE);
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 248492197146624) != 0)) {
        setState(249);
        func_statement();
        setState(250);
        match(PostAnvilParser::NEWLINE);
        setState(256);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(259);
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

std::vector<tree::TerminalNode *> PostAnvilParser::ForStmtContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::ForStmtContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::ForStmtContext* PostAnvilParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 36, PostAnvilParser::RuleForStmt);
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
    setState(261);
    match(PostAnvilParser::FOR);
    setState(262);
    match(PostAnvilParser::IDENTIFIER);
    setState(263);
    match(PostAnvilParser::IN);
    setState(264);
    class_expr();
    setState(265);
    match(PostAnvilParser::NEWLINE);
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492197146624) != 0)) {
      setState(266);
      func_statement();
      setState(267);
      match(PostAnvilParser::NEWLINE);
      setState(273);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(274);
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

tree::TerminalNode* PostAnvilParser::Group_ruleContext::FROM() {
  return getToken(PostAnvilParser::FROM, 0);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::Group_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<tree::TerminalNode *> PostAnvilParser::Group_ruleContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

tree::TerminalNode* PostAnvilParser::Group_ruleContext::STRING() {
  return getToken(PostAnvilParser::STRING, 0);
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


std::any PostAnvilParser::Group_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitGroup_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Group_ruleContext* PostAnvilParser::group_rule() {
  Group_ruleContext *_localctx = _tracker.createInstance<Group_ruleContext>(_ctx, getState());
  enterRule(_localctx, 38, PostAnvilParser::RuleGroup_rule);
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
    setState(276);
    match(PostAnvilParser::RULE);
    setState(277);
    match(PostAnvilParser::GROUP);
    setState(278);
    antlrcpp::downCast<Group_ruleContext *>(_localctx)->new_class = match(PostAnvilParser::STRING);
    setState(279);
    match(PostAnvilParser::FROM);
    setState(280);
    class_expr();
    setState(281);
    match(PostAnvilParser::T__0);
    setState(282);
    match(PostAnvilParser::NEWLINE);
    setState(288);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492178026496) != 0)) {
      setState(283);
      bool_expr();
      setState(284);
      match(PostAnvilParser::NEWLINE);
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(291);
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

std::vector<tree::TerminalNode *> PostAnvilParser::Append_ruleContext::NEWLINE() {
  return getTokens(PostAnvilParser::NEWLINE);
}

tree::TerminalNode* PostAnvilParser::Append_ruleContext::NEWLINE(size_t i) {
  return getToken(PostAnvilParser::NEWLINE, i);
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


std::any PostAnvilParser::Append_ruleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitAppend_rule(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Append_ruleContext* PostAnvilParser::append_rule() {
  Append_ruleContext *_localctx = _tracker.createInstance<Append_ruleContext>(_ctx, getState());
  enterRule(_localctx, 40, PostAnvilParser::RuleAppend_rule);
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
    setState(293);
    match(PostAnvilParser::RULE);
    setState(294);
    match(PostAnvilParser::APPEND);
    setState(295);
    class_expr();
    setState(296);
    match(PostAnvilParser::FROM);
    setState(297);
    class_expr();
    setState(298);
    match(PostAnvilParser::T__0);
    setState(299);
    match(PostAnvilParser::NEWLINE);
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492178026496) != 0)) {
      setState(300);
      bool_expr();
      setState(301);
      match(PostAnvilParser::NEWLINE);
      setState(307);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(308);
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


std::any PostAnvilParser::Class_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitClass_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Class_exprContext* PostAnvilParser::class_expr() {
  Class_exprContext *_localctx = _tracker.createInstance<Class_exprContext>(_ctx, getState());
  enterRule(_localctx, 42, PostAnvilParser::RuleClass_expr);
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
    setState(310);
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


std::any PostAnvilParser::Bool_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitBool_expr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Bool_exprContext* PostAnvilParser::bool_expr() {
  Bool_exprContext *_localctx = _tracker.createInstance<Bool_exprContext>(_ctx, getState());
  enterRule(_localctx, 44, PostAnvilParser::RuleBool_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
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
  enterRule(_localctx, 46, PostAnvilParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
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
  enterRule(_localctx, 48, PostAnvilParser::RuleOr_expr);
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
    setState(316);
    and_expr();
    setState(321);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::OR) {
      setState(317);
      match(PostAnvilParser::OR);
      setState(318);
      and_expr();
      setState(323);
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
  enterRule(_localctx, 50, PostAnvilParser::RuleAnd_expr);
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
    not_expr();
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::AND) {
      setState(325);
      match(PostAnvilParser::AND);
      setState(326);
      not_expr();
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
  enterRule(_localctx, 52, PostAnvilParser::RuleNot_expr);

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
      case PostAnvilParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(332);
        match(PostAnvilParser::NOT);
        setState(333);
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
        setState(334);
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
  enterRule(_localctx, 54, PostAnvilParser::RuleCmp_expr);
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
    add_expr();
    setState(341);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1082331758592) != 0)) {
      setState(338);
      comp_op();
      setState(339);
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
  enterRule(_localctx, 56, PostAnvilParser::RuleAdd_expr);
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
    setState(343);
    mul_expr();
    setState(349);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS) {
      setState(344);
      add_op();
      setState(345);
      mul_expr();
      setState(351);
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
  enterRule(_localctx, 58, PostAnvilParser::RuleMul_expr);
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
    setState(352);
    unary_expr();
    setState(358);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH) {
      setState(353);
      mul_op();
      setState(354);
      unary_expr();
      setState(360);
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
  enterRule(_localctx, 60, PostAnvilParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(361);
        match(PostAnvilParser::MINUS);
        setState(362);
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
        setState(363);
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
  enterRule(_localctx, 62, PostAnvilParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(376);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(366);
      match(PostAnvilParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(367);
      match(PostAnvilParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(368);
      match(PostAnvilParser::BOOL_LIT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(369);
      func_call();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(370);
      attribute();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(371);
      match(PostAnvilParser::LPAREN);
      setState(372);
      expr();
      setState(373);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(375);
      sortExpr();
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
  enterRule(_localctx, 64, PostAnvilParser::RuleFunc_call);
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
    setState(378);
    match(PostAnvilParser::IDENTIFIER);
    setState(379);
    match(PostAnvilParser::LPAREN);
    setState(388);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 248492178026496) != 0)) {
      setState(380);
      expr();
      setState(385);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PostAnvilParser::COMMA) {
        setState(381);
        match(PostAnvilParser::COMMA);
        setState(382);
        expr();
        setState(387);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(390);
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


std::any PostAnvilParser::SortExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitSortExpr(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::SortExprContext* PostAnvilParser::sortExpr() {
  SortExprContext *_localctx = _tracker.createInstance<SortExprContext>(_ctx, getState());
  enterRule(_localctx, 66, PostAnvilParser::RuleSortExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(392);
    match(PostAnvilParser::SORT);
    setState(393);
    match(PostAnvilParser::LPAREN);
    setState(394);
    class_expr();
    setState(395);
    match(PostAnvilParser::COMMA);
    setState(396);
    expr();
    setState(397);
    match(PostAnvilParser::COMMA);
    setState(398);
    expr();
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
  enterRule(_localctx, 68, PostAnvilParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(410);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(401);
        match(PostAnvilParser::SELF);
        setState(402);
        match(PostAnvilParser::DOT);
        setState(403);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(404);
        match(PostAnvilParser::STRING);
        setState(405);
        match(PostAnvilParser::DOT);
        setState(406);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<PostAnvilParser::VarInstanceAttrContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(407);
        match(PostAnvilParser::IDENTIFIER);
        setState(408);
        match(PostAnvilParser::DOT);
        setState(409);
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


std::any PostAnvilParser::Comp_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<PostAnvilVisitor*>(visitor))
    return parserVisitor->visitComp_op(this);
  else
    return visitor->visitChildren(this);
}

PostAnvilParser::Comp_opContext* PostAnvilParser::comp_op() {
  Comp_opContext *_localctx = _tracker.createInstance<Comp_opContext>(_ctx, getState());
  enterRule(_localctx, 70, PostAnvilParser::RuleComp_op);
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
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1082331758592) != 0))) {
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
  enterRule(_localctx, 72, PostAnvilParser::RuleAdd_op);
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
  enterRule(_localctx, 74, PostAnvilParser::RuleMul_op);
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
    setState(416);
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
