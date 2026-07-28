
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
      "func_statement", "ifStmt", "elifBranch", "elseBranch", "forStmt", 
      "group_rule", "append_rule", "sort_rule", "sort_key", "direction", 
      "class_expr", "bool_expr", "expr", "or_expr", "and_expr", "not_expr", 
      "cmp_expr", "add_expr", "mul_expr", "unary_expr", "primary", "func_call", 
      "attribute", "comp_op", "add_op", "mul_op"
    },
    std::vector<std::string>{
      "", "':'", "'RULE'", "'RULEEND'", "'FILTER'", "'ATTR'", "'FUNC'", 
      "'GROUP'", "'APPEND'", "'FROM'", "'AND'", "'OR'", "'NOT'", "'SELF'", 
      "'NUM'", "'STR'", "'BOOL'", "'INST'", "'ANY'", "'RETURN'", "'IMPORT'", 
      "'EXPORT'", "'AS'", "'IF'", "'ELIF'", "'ELSE'", "'ENDIF'", "'FOR'", 
      "'IN'", "'ENDFOR'", "'SORT'", "'ASC'", "'DESC'", "", "'->'", "'+'", 
      "'-'", "'*'", "'/'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", 
      "'.'", "'('", "')'", "','", "'='"
    },
    std::vector<std::string>{
      "", "", "RULE", "RULEEND", "FILTER", "ATTR", "FUNC", "GROUP", "APPEND", 
      "FROM", "AND", "OR", "NOT", "SELF", "NUM", "STR", "BOOL", "INST", 
      "ANY", "RETURN", "IMPORT", "EXPORT", "AS", "IF", "ELIF", "ELSE", "ENDIF", 
      "FOR", "IN", "ENDFOR", "SORT", "ASC", "DESC", "BOOL_LIT", "ARROW", 
      "PLUS", "MINUS", "STAR", "SLASH", "LT", "GT", "LE", "GE", "EQ", "NE", 
      "DOT", "LPAREN", "RPAREN", "COMMA", "ASSIGN", "NUMBER", "STRING", 
      "IDENTIFIER", "WS", "NEWLINE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,55,483,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,1,0,1,0,1,0,5,0,90,8,0,10,0,12,0,93,9,0,1,0,1,0,1,1,4,1,98,8,1,11,
  	1,12,1,99,1,2,1,2,1,2,3,2,105,8,2,1,3,1,3,1,3,1,3,5,3,111,8,3,10,3,12,
  	3,114,9,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,122,8,4,1,5,1,5,1,5,1,5,5,5,128,
  	8,5,10,5,12,5,131,9,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,3,7,150,8,7,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,3,9,160,
  	8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,5,10,170,8,10,10,10,12,10,
  	173,9,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,185,8,
  	11,10,11,12,11,188,9,11,1,11,1,11,1,12,1,12,1,12,1,12,1,13,1,13,1,13,
  	1,13,1,13,1,13,3,13,202,8,13,1,14,1,14,1,14,1,14,1,14,3,14,209,8,14,1,
  	14,1,14,1,14,3,14,214,8,14,1,14,1,14,1,14,1,14,1,14,4,14,221,8,14,11,
  	14,12,14,222,1,14,1,14,1,15,1,15,1,15,5,15,230,8,15,10,15,12,15,233,9,
  	15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,
  	17,1,17,1,17,1,17,3,17,252,8,17,1,18,1,18,1,18,1,18,1,18,1,18,5,18,260,
  	8,18,10,18,12,18,263,9,18,1,18,5,18,266,8,18,10,18,12,18,269,9,18,1,18,
  	3,18,272,8,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,5,19,282,8,19,10,
  	19,12,19,285,9,19,1,20,1,20,1,20,1,20,1,20,5,20,292,8,20,10,20,12,20,
  	295,9,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,305,8,21,10,21,
  	12,21,308,9,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,5,22,322,8,22,10,22,12,22,325,9,22,1,22,1,22,1,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,5,23,339,8,23,10,23,12,23,342,9,23,1,23,
  	1,23,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,4,24,354,8,24,11,24,12,24,
  	355,1,24,1,24,1,25,1,25,1,25,1,26,1,26,1,27,1,27,1,28,1,28,1,29,1,29,
  	1,30,1,30,1,30,5,30,374,8,30,10,30,12,30,377,9,30,1,31,1,31,1,31,5,31,
  	382,8,31,10,31,12,31,385,9,31,1,32,1,32,1,32,3,32,390,8,32,1,33,1,33,
  	1,33,1,33,3,33,396,8,33,1,34,1,34,1,34,1,34,5,34,402,8,34,10,34,12,34,
  	405,9,34,1,35,1,35,1,35,1,35,5,35,411,8,35,10,35,12,35,414,9,35,1,36,
  	1,36,1,36,3,36,419,8,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,
  	1,37,1,37,3,37,432,8,37,1,38,1,38,1,38,1,38,1,38,5,38,439,8,38,10,38,
  	12,38,442,9,38,3,38,444,8,38,1,38,1,38,1,39,1,39,1,39,1,39,1,39,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,1,39,
  	1,39,1,39,1,39,1,39,1,39,1,39,1,39,3,39,475,8,39,1,40,1,40,1,41,1,41,
  	1,42,1,42,1,42,0,0,43,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
  	36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,
  	82,84,0,6,1,0,14,18,1,0,31,32,1,0,51,52,1,0,39,44,1,0,35,36,1,0,37,38,
  	496,0,91,1,0,0,0,2,97,1,0,0,0,4,104,1,0,0,0,6,106,1,0,0,0,8,117,1,0,0,
  	0,10,123,1,0,0,0,12,134,1,0,0,0,14,149,1,0,0,0,16,151,1,0,0,0,18,159,
  	1,0,0,0,20,161,1,0,0,0,22,176,1,0,0,0,24,191,1,0,0,0,26,201,1,0,0,0,28,
  	203,1,0,0,0,30,226,1,0,0,0,32,234,1,0,0,0,34,251,1,0,0,0,36,253,1,0,0,
  	0,38,275,1,0,0,0,40,286,1,0,0,0,42,296,1,0,0,0,44,311,1,0,0,0,46,328,
  	1,0,0,0,48,345,1,0,0,0,50,359,1,0,0,0,52,362,1,0,0,0,54,364,1,0,0,0,56,
  	366,1,0,0,0,58,368,1,0,0,0,60,370,1,0,0,0,62,378,1,0,0,0,64,389,1,0,0,
  	0,66,391,1,0,0,0,68,397,1,0,0,0,70,406,1,0,0,0,72,418,1,0,0,0,74,431,
  	1,0,0,0,76,433,1,0,0,0,78,474,1,0,0,0,80,476,1,0,0,0,82,478,1,0,0,0,84,
  	480,1,0,0,0,86,90,3,4,2,0,87,90,3,18,9,0,88,90,3,2,1,0,89,86,1,0,0,0,
  	89,87,1,0,0,0,89,88,1,0,0,0,90,93,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,
  	92,94,1,0,0,0,93,91,1,0,0,0,94,95,5,0,0,1,95,1,1,0,0,0,96,98,5,54,0,0,
  	97,96,1,0,0,0,98,99,1,0,0,0,99,97,1,0,0,0,99,100,1,0,0,0,100,3,1,0,0,
  	0,101,105,3,6,3,0,102,105,3,10,5,0,103,105,3,14,7,0,104,101,1,0,0,0,104,
  	102,1,0,0,0,104,103,1,0,0,0,105,5,1,0,0,0,106,107,5,20,0,0,107,112,3,
  	8,4,0,108,109,5,48,0,0,109,111,3,8,4,0,110,108,1,0,0,0,111,114,1,0,0,
  	0,112,110,1,0,0,0,112,113,1,0,0,0,113,115,1,0,0,0,114,112,1,0,0,0,115,
  	116,3,2,1,0,116,7,1,0,0,0,117,118,3,16,8,0,118,121,5,52,0,0,119,120,5,
  	22,0,0,120,122,5,52,0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,9,1,0,0,0,
  	123,124,5,21,0,0,124,129,3,12,6,0,125,126,5,48,0,0,126,128,3,12,6,0,127,
  	125,1,0,0,0,128,131,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,132,1,
  	0,0,0,131,129,1,0,0,0,132,133,3,2,1,0,133,11,1,0,0,0,134,135,3,58,29,
  	0,135,136,5,22,0,0,136,137,5,52,0,0,137,13,1,0,0,0,138,139,3,16,8,0,139,
  	140,5,52,0,0,140,141,5,49,0,0,141,142,3,58,29,0,142,143,3,2,1,0,143,150,
  	1,0,0,0,144,145,5,52,0,0,145,146,5,49,0,0,146,147,3,58,29,0,147,148,3,
  	2,1,0,148,150,1,0,0,0,149,138,1,0,0,0,149,144,1,0,0,0,150,15,1,0,0,0,
  	151,152,7,0,0,0,152,17,1,0,0,0,153,160,3,20,10,0,154,160,3,22,11,0,155,
  	160,3,44,22,0,156,160,3,46,23,0,157,160,3,48,24,0,158,160,3,28,14,0,159,
  	153,1,0,0,0,159,154,1,0,0,0,159,155,1,0,0,0,159,156,1,0,0,0,159,157,1,
  	0,0,0,159,158,1,0,0,0,160,19,1,0,0,0,161,162,5,2,0,0,162,163,5,4,0,0,
  	163,164,3,54,27,0,164,165,5,1,0,0,165,171,3,2,1,0,166,167,3,56,28,0,167,
  	168,3,2,1,0,168,170,1,0,0,0,169,166,1,0,0,0,170,173,1,0,0,0,171,169,1,
  	0,0,0,171,172,1,0,0,0,172,174,1,0,0,0,173,171,1,0,0,0,174,175,5,3,0,0,
  	175,21,1,0,0,0,176,177,5,2,0,0,177,178,5,5,0,0,178,179,3,54,27,0,179,
  	180,5,1,0,0,180,186,3,2,1,0,181,182,3,24,12,0,182,183,3,2,1,0,183,185,
  	1,0,0,0,184,181,1,0,0,0,185,188,1,0,0,0,186,184,1,0,0,0,186,187,1,0,0,
  	0,187,189,1,0,0,0,188,186,1,0,0,0,189,190,5,3,0,0,190,23,1,0,0,0,191,
  	192,3,26,13,0,192,193,5,49,0,0,193,194,3,58,29,0,194,25,1,0,0,0,195,196,
  	5,13,0,0,196,197,5,45,0,0,197,202,5,52,0,0,198,199,5,51,0,0,199,200,5,
  	45,0,0,200,202,5,52,0,0,201,195,1,0,0,0,201,198,1,0,0,0,202,27,1,0,0,
  	0,203,204,5,2,0,0,204,205,5,6,0,0,205,206,5,52,0,0,206,208,5,46,0,0,207,
  	209,3,30,15,0,208,207,1,0,0,0,208,209,1,0,0,0,209,210,1,0,0,0,210,213,
  	5,47,0,0,211,212,5,34,0,0,212,214,3,16,8,0,213,211,1,0,0,0,213,214,1,
  	0,0,0,214,215,1,0,0,0,215,216,5,1,0,0,216,220,3,2,1,0,217,218,3,34,17,
  	0,218,219,3,2,1,0,219,221,1,0,0,0,220,217,1,0,0,0,221,222,1,0,0,0,222,
  	220,1,0,0,0,222,223,1,0,0,0,223,224,1,0,0,0,224,225,5,3,0,0,225,29,1,
  	0,0,0,226,231,3,32,16,0,227,228,5,48,0,0,228,230,3,32,16,0,229,227,1,
  	0,0,0,230,233,1,0,0,0,231,229,1,0,0,0,231,232,1,0,0,0,232,31,1,0,0,0,
  	233,231,1,0,0,0,234,235,5,52,0,0,235,236,5,1,0,0,236,237,3,16,8,0,237,
  	33,1,0,0,0,238,239,3,16,8,0,239,240,5,52,0,0,240,241,5,49,0,0,241,242,
  	3,58,29,0,242,252,1,0,0,0,243,244,5,52,0,0,244,245,5,49,0,0,245,252,3,
  	58,29,0,246,252,3,36,18,0,247,252,3,42,21,0,248,252,3,58,29,0,249,250,
  	5,19,0,0,250,252,3,58,29,0,251,238,1,0,0,0,251,243,1,0,0,0,251,246,1,
  	0,0,0,251,247,1,0,0,0,251,248,1,0,0,0,251,249,1,0,0,0,252,35,1,0,0,0,
  	253,254,5,23,0,0,254,255,3,58,29,0,255,261,3,2,1,0,256,257,3,34,17,0,
  	257,258,3,2,1,0,258,260,1,0,0,0,259,256,1,0,0,0,260,263,1,0,0,0,261,259,
  	1,0,0,0,261,262,1,0,0,0,262,267,1,0,0,0,263,261,1,0,0,0,264,266,3,38,
  	19,0,265,264,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,
  	268,271,1,0,0,0,269,267,1,0,0,0,270,272,3,40,20,0,271,270,1,0,0,0,271,
  	272,1,0,0,0,272,273,1,0,0,0,273,274,5,26,0,0,274,37,1,0,0,0,275,276,5,
  	24,0,0,276,277,3,58,29,0,277,283,3,2,1,0,278,279,3,34,17,0,279,280,3,
  	2,1,0,280,282,1,0,0,0,281,278,1,0,0,0,282,285,1,0,0,0,283,281,1,0,0,0,
  	283,284,1,0,0,0,284,39,1,0,0,0,285,283,1,0,0,0,286,287,5,25,0,0,287,293,
  	3,2,1,0,288,289,3,34,17,0,289,290,3,2,1,0,290,292,1,0,0,0,291,288,1,0,
  	0,0,292,295,1,0,0,0,293,291,1,0,0,0,293,294,1,0,0,0,294,41,1,0,0,0,295,
  	293,1,0,0,0,296,297,5,27,0,0,297,298,5,52,0,0,298,299,5,28,0,0,299,300,
  	3,54,27,0,300,306,3,2,1,0,301,302,3,34,17,0,302,303,3,2,1,0,303,305,1,
  	0,0,0,304,301,1,0,0,0,305,308,1,0,0,0,306,304,1,0,0,0,306,307,1,0,0,0,
  	307,309,1,0,0,0,308,306,1,0,0,0,309,310,5,29,0,0,310,43,1,0,0,0,311,312,
  	5,2,0,0,312,313,5,7,0,0,313,314,3,54,27,0,314,315,5,9,0,0,315,316,3,54,
  	27,0,316,317,5,1,0,0,317,323,3,2,1,0,318,319,3,56,28,0,319,320,3,2,1,
  	0,320,322,1,0,0,0,321,318,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,
  	324,1,0,0,0,324,326,1,0,0,0,325,323,1,0,0,0,326,327,5,3,0,0,327,45,1,
  	0,0,0,328,329,5,2,0,0,329,330,5,8,0,0,330,331,3,54,27,0,331,332,5,9,0,
  	0,332,333,3,54,27,0,333,334,5,1,0,0,334,340,3,2,1,0,335,336,3,56,28,0,
  	336,337,3,2,1,0,337,339,1,0,0,0,338,335,1,0,0,0,339,342,1,0,0,0,340,338,
  	1,0,0,0,340,341,1,0,0,0,341,343,1,0,0,0,342,340,1,0,0,0,343,344,5,3,0,
  	0,344,47,1,0,0,0,345,346,5,2,0,0,346,347,5,30,0,0,347,348,3,54,27,0,348,
  	349,5,1,0,0,349,353,3,2,1,0,350,351,3,50,25,0,351,352,3,2,1,0,352,354,
  	1,0,0,0,353,350,1,0,0,0,354,355,1,0,0,0,355,353,1,0,0,0,355,356,1,0,0,
  	0,356,357,1,0,0,0,357,358,5,3,0,0,358,49,1,0,0,0,359,360,3,58,29,0,360,
  	361,3,52,26,0,361,51,1,0,0,0,362,363,7,1,0,0,363,53,1,0,0,0,364,365,7,
  	2,0,0,365,55,1,0,0,0,366,367,3,60,30,0,367,57,1,0,0,0,368,369,3,60,30,
  	0,369,59,1,0,0,0,370,375,3,62,31,0,371,372,5,11,0,0,372,374,3,62,31,0,
  	373,371,1,0,0,0,374,377,1,0,0,0,375,373,1,0,0,0,375,376,1,0,0,0,376,61,
  	1,0,0,0,377,375,1,0,0,0,378,383,3,64,32,0,379,380,5,10,0,0,380,382,3,
  	64,32,0,381,379,1,0,0,0,382,385,1,0,0,0,383,381,1,0,0,0,383,384,1,0,0,
  	0,384,63,1,0,0,0,385,383,1,0,0,0,386,387,5,12,0,0,387,390,3,64,32,0,388,
  	390,3,66,33,0,389,386,1,0,0,0,389,388,1,0,0,0,390,65,1,0,0,0,391,395,
  	3,68,34,0,392,393,3,80,40,0,393,394,3,68,34,0,394,396,1,0,0,0,395,392,
  	1,0,0,0,395,396,1,0,0,0,396,67,1,0,0,0,397,403,3,70,35,0,398,399,3,82,
  	41,0,399,400,3,70,35,0,400,402,1,0,0,0,401,398,1,0,0,0,402,405,1,0,0,
  	0,403,401,1,0,0,0,403,404,1,0,0,0,404,69,1,0,0,0,405,403,1,0,0,0,406,
  	412,3,72,36,0,407,408,3,84,42,0,408,409,3,72,36,0,409,411,1,0,0,0,410,
  	407,1,0,0,0,411,414,1,0,0,0,412,410,1,0,0,0,412,413,1,0,0,0,413,71,1,
  	0,0,0,414,412,1,0,0,0,415,416,5,36,0,0,416,419,3,72,36,0,417,419,3,74,
  	37,0,418,415,1,0,0,0,418,417,1,0,0,0,419,73,1,0,0,0,420,432,5,50,0,0,
  	421,432,5,51,0,0,422,432,5,33,0,0,423,432,5,13,0,0,424,432,3,76,38,0,
  	425,432,3,78,39,0,426,427,5,46,0,0,427,428,3,58,29,0,428,429,5,47,0,0,
  	429,432,1,0,0,0,430,432,5,52,0,0,431,420,1,0,0,0,431,421,1,0,0,0,431,
  	422,1,0,0,0,431,423,1,0,0,0,431,424,1,0,0,0,431,425,1,0,0,0,431,426,1,
  	0,0,0,431,430,1,0,0,0,432,75,1,0,0,0,433,434,5,52,0,0,434,443,5,46,0,
  	0,435,440,3,58,29,0,436,437,5,48,0,0,437,439,3,58,29,0,438,436,1,0,0,
  	0,439,442,1,0,0,0,440,438,1,0,0,0,440,441,1,0,0,0,441,444,1,0,0,0,442,
  	440,1,0,0,0,443,435,1,0,0,0,443,444,1,0,0,0,444,445,1,0,0,0,445,446,5,
  	47,0,0,446,77,1,0,0,0,447,448,5,13,0,0,448,449,5,45,0,0,449,475,5,52,
  	0,0,450,451,5,51,0,0,451,452,5,45,0,0,452,475,5,52,0,0,453,454,5,52,0,
  	0,454,455,5,45,0,0,455,475,5,52,0,0,456,457,5,13,0,0,457,458,5,45,0,0,
  	458,459,5,46,0,0,459,460,3,58,29,0,460,461,5,47,0,0,461,475,1,0,0,0,462,
  	463,5,51,0,0,463,464,5,45,0,0,464,465,5,46,0,0,465,466,3,58,29,0,466,
  	467,5,47,0,0,467,475,1,0,0,0,468,469,5,52,0,0,469,470,5,45,0,0,470,471,
  	5,46,0,0,471,472,3,58,29,0,472,473,5,47,0,0,473,475,1,0,0,0,474,447,1,
  	0,0,0,474,450,1,0,0,0,474,453,1,0,0,0,474,456,1,0,0,0,474,462,1,0,0,0,
  	474,468,1,0,0,0,475,79,1,0,0,0,476,477,7,3,0,0,477,81,1,0,0,0,478,479,
  	7,4,0,0,479,83,1,0,0,0,480,481,7,5,0,0,481,85,1,0,0,0,37,89,91,99,104,
  	112,121,129,149,159,171,186,201,208,213,222,231,251,261,267,271,283,293,
  	306,323,340,355,375,383,389,395,403,412,418,431,440,443,474
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
    setState(91);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 22517998140506116) != 0)) {
      setState(89);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PostAnvilParser::NUM:
        case PostAnvilParser::STR:
        case PostAnvilParser::BOOL:
        case PostAnvilParser::INST:
        case PostAnvilParser::ANY:
        case PostAnvilParser::IMPORT:
        case PostAnvilParser::EXPORT:
        case PostAnvilParser::IDENTIFIER: {
          setState(86);
          declaration();
          break;
        }

        case PostAnvilParser::RULE: {
          setState(87);
          rule_();
          break;
        }

        case PostAnvilParser::NEWLINE: {
          setState(88);
          newlines();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(93);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(94);
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
    setState(97); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(96);
              match(PostAnvilParser::NEWLINE);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(99); 
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
    setState(104);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::IMPORT: {
        enterOuterAlt(_localctx, 1);
        setState(101);
        importDef();
        break;
      }

      case PostAnvilParser::EXPORT: {
        enterOuterAlt(_localctx, 2);
        setState(102);
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
        setState(103);
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
    setState(106);
    match(PostAnvilParser::IMPORT);
    setState(107);
    importItem();
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(108);
      match(PostAnvilParser::COMMA);
      setState(109);
      importItem();
      setState(114);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(115);
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
    setState(117);
    type();
    setState(118);
    antlrcpp::downCast<ImportItemContext *>(_localctx)->host = match(PostAnvilParser::IDENTIFIER);
    setState(121);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::AS) {
      setState(119);
      match(PostAnvilParser::AS);
      setState(120);
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
    setState(123);
    match(PostAnvilParser::EXPORT);
    setState(124);
    exportItem();
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(125);
      match(PostAnvilParser::COMMA);
      setState(126);
      exportItem();
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(132);
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
    setState(134);
    expr();
    setState(135);
    match(PostAnvilParser::AS);
    setState(136);
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
    setState(149);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NUM:
      case PostAnvilParser::STR:
      case PostAnvilParser::BOOL:
      case PostAnvilParser::INST:
      case PostAnvilParser::ANY: {
        enterOuterAlt(_localctx, 1);
        setState(138);
        type();
        setState(139);
        match(PostAnvilParser::IDENTIFIER);
        setState(140);
        match(PostAnvilParser::ASSIGN);
        setState(141);
        expr();
        setState(142);
        newlines();
        break;
      }

      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(144);
        match(PostAnvilParser::IDENTIFIER);
        setState(145);
        match(PostAnvilParser::ASSIGN);
        setState(146);
        expr();
        setState(147);
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
    setState(151);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 507904) != 0))) {
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
    setState(159);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(153);
      filter_rule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(154);
      attr_rule();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(155);
      group_rule();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(156);
      append_rule();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(157);
      sort_rule();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(158);
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
    setState(161);
    match(PostAnvilParser::RULE);
    setState(162);
    match(PostAnvilParser::FILTER);
    setState(163);
    class_expr();
    setState(164);
    match(PostAnvilParser::T__0);
    setState(165);
    newlines();
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745401499648) != 0)) {
      setState(166);
      bool_expr();
      setState(167);
      newlines();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
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
    setState(176);
    match(PostAnvilParser::RULE);
    setState(177);
    match(PostAnvilParser::ATTR);
    setState(178);
    class_expr();
    setState(179);
    match(PostAnvilParser::T__0);
    setState(180);
    newlines();
    setState(186);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::SELF

    || _la == PostAnvilParser::STRING) {
      setState(181);
      attr_def();
      setState(182);
      newlines();
      setState(188);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(189);
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
    setState(191);
    attr_lvalue();
    setState(192);
    match(PostAnvilParser::ASSIGN);
    setState(193);
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
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::SELF: {
        _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(195);
        match(PostAnvilParser::SELF);
        setState(196);
        match(PostAnvilParser::DOT);
        setState(197);
        match(PostAnvilParser::IDENTIFIER);
        break;
      }

      case PostAnvilParser::STRING: {
        _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrDefContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(198);
        match(PostAnvilParser::STRING);
        setState(199);
        match(PostAnvilParser::DOT);
        setState(200);
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
    setState(203);
    match(PostAnvilParser::RULE);
    setState(204);
    match(PostAnvilParser::FUNC);
    setState(205);
    antlrcpp::downCast<Func_ruleContext *>(_localctx)->name = match(PostAnvilParser::IDENTIFIER);
    setState(206);
    match(PostAnvilParser::LPAREN);
    setState(208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::IDENTIFIER) {
      setState(207);
      typed_params();
    }
    setState(210);
    match(PostAnvilParser::RPAREN);
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ARROW) {
      setState(211);
      match(PostAnvilParser::ARROW);
      setState(212);
      antlrcpp::downCast<Func_ruleContext *>(_localctx)->return_type = type();
    }
    setState(215);
    match(PostAnvilParser::T__0);
    setState(216);
    newlines();
    setState(220); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(217);
      func_statement();
      setState(218);
      newlines();
      setState(222); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745545138176) != 0));
    setState(224);
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
    setState(226);
    typed_param();
    setState(231);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::COMMA) {
      setState(227);
      match(PostAnvilParser::COMMA);
      setState(228);
      typed_param();
      setState(233);
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
    setState(234);
    antlrcpp::downCast<Typed_paramContext *>(_localctx)->param_name = match(PostAnvilParser::IDENTIFIER);
    setState(235);
    match(PostAnvilParser::T__0);
    setState(236);
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
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncVarDefContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(238);
      type();
      setState(239);
      match(PostAnvilParser::IDENTIFIER);
      setState(240);
      match(PostAnvilParser::ASSIGN);
      setState(241);
      expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncAssignContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(243);
      match(PostAnvilParser::IDENTIFIER);
      setState(244);
      match(PostAnvilParser::ASSIGN);
      setState(245);
      expr();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncIfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(246);
      ifStmt();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncForStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(247);
      forStmt();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(248);
      expr();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::FuncReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(249);
      match(PostAnvilParser::RETURN);
      setState(250);
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

std::vector<PostAnvilParser::ElifBranchContext *> PostAnvilParser::IfStmtContext::elifBranch() {
  return getRuleContexts<PostAnvilParser::ElifBranchContext>();
}

PostAnvilParser::ElifBranchContext* PostAnvilParser::IfStmtContext::elifBranch(size_t i) {
  return getRuleContext<PostAnvilParser::ElifBranchContext>(i);
}

PostAnvilParser::ElseBranchContext* PostAnvilParser::IfStmtContext::elseBranch() {
  return getRuleContext<PostAnvilParser::ElseBranchContext>(0);
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
    setState(253);
    match(PostAnvilParser::IF);
    setState(254);
    expr();
    setState(255);
    newlines();
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745545138176) != 0)) {
      setState(256);
      func_statement();
      setState(257);
      newlines();
      setState(263);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(267);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::ELIF) {
      setState(264);
      elifBranch();
      setState(269);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(271);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PostAnvilParser::ELSE) {
      setState(270);
      elseBranch();
    }
    setState(273);
    match(PostAnvilParser::ENDIF);
   
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

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::ElifBranchContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ElifBranchContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::Func_statementContext *> PostAnvilParser::ElifBranchContext::func_statement() {
  return getRuleContexts<PostAnvilParser::Func_statementContext>();
}

PostAnvilParser::Func_statementContext* PostAnvilParser::ElifBranchContext::func_statement(size_t i) {
  return getRuleContext<PostAnvilParser::Func_statementContext>(i);
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

PostAnvilParser::ElifBranchContext* PostAnvilParser::elifBranch() {
  ElifBranchContext *_localctx = _tracker.createInstance<ElifBranchContext>(_ctx, getState());
  enterRule(_localctx, 38, PostAnvilParser::RuleElifBranch);
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
    setState(275);
    match(PostAnvilParser::ELIF);
    setState(276);
    expr();
    setState(277);
    newlines();
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745545138176) != 0)) {
      setState(278);
      func_statement();
      setState(279);
      newlines();
      setState(285);
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

//----------------- ElseBranchContext ------------------------------------------------------------------

PostAnvilParser::ElseBranchContext::ElseBranchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* PostAnvilParser::ElseBranchContext::ELSE() {
  return getToken(PostAnvilParser::ELSE, 0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::ElseBranchContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::ElseBranchContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

std::vector<PostAnvilParser::Func_statementContext *> PostAnvilParser::ElseBranchContext::func_statement() {
  return getRuleContexts<PostAnvilParser::Func_statementContext>();
}

PostAnvilParser::Func_statementContext* PostAnvilParser::ElseBranchContext::func_statement(size_t i) {
  return getRuleContext<PostAnvilParser::Func_statementContext>(i);
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

PostAnvilParser::ElseBranchContext* PostAnvilParser::elseBranch() {
  ElseBranchContext *_localctx = _tracker.createInstance<ElseBranchContext>(_ctx, getState());
  enterRule(_localctx, 40, PostAnvilParser::RuleElseBranch);
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
    setState(286);
    match(PostAnvilParser::ELSE);
    setState(287);
    newlines();
    setState(293);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745545138176) != 0)) {
      setState(288);
      func_statement();
      setState(289);
      newlines();
      setState(295);
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
  enterRule(_localctx, 42, PostAnvilParser::RuleForStmt);
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
    setState(296);
    match(PostAnvilParser::FOR);
    setState(297);
    match(PostAnvilParser::IDENTIFIER);
    setState(298);
    match(PostAnvilParser::IN);
    setState(299);
    class_expr();
    setState(300);
    newlines();
    setState(306);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745545138176) != 0)) {
      setState(301);
      func_statement();
      setState(302);
      newlines();
      setState(308);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(309);
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
  enterRule(_localctx, 44, PostAnvilParser::RuleGroup_rule);
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
    setState(311);
    match(PostAnvilParser::RULE);
    setState(312);
    match(PostAnvilParser::GROUP);
    setState(313);
    class_expr();
    setState(314);
    match(PostAnvilParser::FROM);
    setState(315);
    class_expr();
    setState(316);
    match(PostAnvilParser::T__0);
    setState(317);
    newlines();
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745401499648) != 0)) {
      setState(318);
      bool_expr();
      setState(319);
      newlines();
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(326);
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
  enterRule(_localctx, 46, PostAnvilParser::RuleAppend_rule);
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
    setState(328);
    match(PostAnvilParser::RULE);
    setState(329);
    match(PostAnvilParser::APPEND);
    setState(330);
    class_expr();
    setState(331);
    match(PostAnvilParser::FROM);
    setState(332);
    class_expr();
    setState(333);
    match(PostAnvilParser::T__0);
    setState(334);
    newlines();
    setState(340);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745401499648) != 0)) {
      setState(335);
      bool_expr();
      setState(336);
      newlines();
      setState(342);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(343);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Class_exprContext* PostAnvilParser::Sort_ruleContext::class_expr() {
  return getRuleContext<PostAnvilParser::Class_exprContext>(0);
}

std::vector<PostAnvilParser::NewlinesContext *> PostAnvilParser::Sort_ruleContext::newlines() {
  return getRuleContexts<PostAnvilParser::NewlinesContext>();
}

PostAnvilParser::NewlinesContext* PostAnvilParser::Sort_ruleContext::newlines(size_t i) {
  return getRuleContext<PostAnvilParser::NewlinesContext>(i);
}

tree::TerminalNode* PostAnvilParser::Sort_ruleContext::RULEEND() {
  return getToken(PostAnvilParser::RULEEND, 0);
}

std::vector<PostAnvilParser::Sort_keyContext *> PostAnvilParser::Sort_ruleContext::sort_key() {
  return getRuleContexts<PostAnvilParser::Sort_keyContext>();
}

PostAnvilParser::Sort_keyContext* PostAnvilParser::Sort_ruleContext::sort_key(size_t i) {
  return getRuleContext<PostAnvilParser::Sort_keyContext>(i);
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

PostAnvilParser::Sort_ruleContext* PostAnvilParser::sort_rule() {
  Sort_ruleContext *_localctx = _tracker.createInstance<Sort_ruleContext>(_ctx, getState());
  enterRule(_localctx, 48, PostAnvilParser::RuleSort_rule);
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
    match(PostAnvilParser::RULE);
    setState(346);
    match(PostAnvilParser::SORT);
    setState(347);
    class_expr();
    setState(348);
    match(PostAnvilParser::T__0);
    setState(349);
    newlines();
    setState(353); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(350);
      sort_key();
      setState(351);
      newlines();
      setState(355); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745401499648) != 0));
    setState(357);
    match(PostAnvilParser::RULEEND);
   
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

PostAnvilParser::Sort_keyContext* PostAnvilParser::sort_key() {
  Sort_keyContext *_localctx = _tracker.createInstance<Sort_keyContext>(_ctx, getState());
  enterRule(_localctx, 50, PostAnvilParser::RuleSort_key);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(359);
    expr();
    setState(360);
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

PostAnvilParser::DirectionContext* PostAnvilParser::direction() {
  DirectionContext *_localctx = _tracker.createInstance<DirectionContext>(_ctx, getState());
  enterRule(_localctx, 52, PostAnvilParser::RuleDirection);
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
    setState(362);
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
  enterRule(_localctx, 54, PostAnvilParser::RuleClass_expr);
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
    setState(364);
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
  enterRule(_localctx, 56, PostAnvilParser::RuleBool_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
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
  enterRule(_localctx, 58, PostAnvilParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
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
  enterRule(_localctx, 60, PostAnvilParser::RuleOr_expr);
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
    setState(370);
    and_expr();
    setState(375);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::OR) {
      setState(371);
      match(PostAnvilParser::OR);
      setState(372);
      and_expr();
      setState(377);
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
  enterRule(_localctx, 62, PostAnvilParser::RuleAnd_expr);
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
    not_expr();
    setState(383);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::AND) {
      setState(379);
      match(PostAnvilParser::AND);
      setState(380);
      not_expr();
      setState(385);
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
  enterRule(_localctx, 64, PostAnvilParser::RuleNot_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(389);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::NOT: {
        enterOuterAlt(_localctx, 1);
        setState(386);
        match(PostAnvilParser::NOT);
        setState(387);
        not_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::MINUS:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(388);
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
  enterRule(_localctx, 66, PostAnvilParser::RuleCmp_expr);
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
    setState(391);
    add_expr();
    setState(395);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 34634616274944) != 0)) {
      setState(392);
      comp_op();
      setState(393);
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
  enterRule(_localctx, 68, PostAnvilParser::RuleAdd_expr);
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
    setState(397);
    mul_expr();
    setState(403);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::PLUS

    || _la == PostAnvilParser::MINUS) {
      setState(398);
      add_op();
      setState(399);
      mul_expr();
      setState(405);
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
  enterRule(_localctx, 70, PostAnvilParser::RuleMul_expr);
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
    setState(406);
    unary_expr();
    setState(412);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PostAnvilParser::STAR

    || _la == PostAnvilParser::SLASH) {
      setState(407);
      mul_op();
      setState(408);
      unary_expr();
      setState(414);
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
  enterRule(_localctx, 72, PostAnvilParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(418);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PostAnvilParser::MINUS: {
        enterOuterAlt(_localctx, 1);
        setState(415);
        match(PostAnvilParser::MINUS);
        setState(416);
        unary_expr();
        break;
      }

      case PostAnvilParser::SELF:
      case PostAnvilParser::BOOL_LIT:
      case PostAnvilParser::LPAREN:
      case PostAnvilParser::NUMBER:
      case PostAnvilParser::STRING:
      case PostAnvilParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(417);
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

PostAnvilParser::PrimaryContext* PostAnvilParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 74, PostAnvilParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(431);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(420);
      match(PostAnvilParser::NUMBER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(421);
      match(PostAnvilParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(422);
      match(PostAnvilParser::BOOL_LIT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(423);
      match(PostAnvilParser::SELF);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(424);
      func_call();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(425);
      attribute();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(426);
      match(PostAnvilParser::LPAREN);
      setState(427);
      expr();
      setState(428);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(430);
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
  enterRule(_localctx, 76, PostAnvilParser::RuleFunc_call);
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
    setState(433);
    match(PostAnvilParser::IDENTIFIER);
    setState(434);
    match(PostAnvilParser::LPAREN);
    setState(443);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7951745401499648) != 0)) {
      setState(435);
      expr();
      setState(440);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PostAnvilParser::COMMA) {
        setState(436);
        match(PostAnvilParser::COMMA);
        setState(437);
        expr();
        setState(442);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(445);
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
  enterRule(_localctx, 78, PostAnvilParser::RuleAttribute);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(474);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<PostAnvilParser::InstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(447);
      match(PostAnvilParser::SELF);
      setState(448);
      match(PostAnvilParser::DOT);
      setState(449);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<PostAnvilParser::ClassAttrContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(450);
      match(PostAnvilParser::STRING);
      setState(451);
      match(PostAnvilParser::DOT);
      setState(452);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<PostAnvilParser::VarInstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(453);
      match(PostAnvilParser::IDENTIFIER);
      setState(454);
      match(PostAnvilParser::DOT);
      setState(455);
      match(PostAnvilParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicInstanceAttrContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(456);
      match(PostAnvilParser::SELF);
      setState(457);
      match(PostAnvilParser::DOT);
      setState(458);
      match(PostAnvilParser::LPAREN);
      setState(459);
      expr();
      setState(460);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicClassAttrContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(462);
      match(PostAnvilParser::STRING);
      setState(463);
      match(PostAnvilParser::DOT);
      setState(464);
      match(PostAnvilParser::LPAREN);
      setState(465);
      expr();
      setState(466);
      match(PostAnvilParser::RPAREN);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<PostAnvilParser::DynamicVarAttrContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(468);
      match(PostAnvilParser::IDENTIFIER);
      setState(469);
      match(PostAnvilParser::DOT);
      setState(470);
      match(PostAnvilParser::LPAREN);
      setState(471);
      expr();
      setState(472);
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

PostAnvilParser::Comp_opContext* PostAnvilParser::comp_op() {
  Comp_opContext *_localctx = _tracker.createInstance<Comp_opContext>(_ctx, getState());
  enterRule(_localctx, 80, PostAnvilParser::RuleComp_op);
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
    setState(476);
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

PostAnvilParser::Add_opContext* PostAnvilParser::add_op() {
  Add_opContext *_localctx = _tracker.createInstance<Add_opContext>(_ctx, getState());
  enterRule(_localctx, 82, PostAnvilParser::RuleAdd_op);
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
    setState(478);
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
  enterRule(_localctx, 84, PostAnvilParser::RuleMul_op);
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
    setState(480);
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
