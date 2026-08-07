
// Generated from D:/UserProject/vsstudio/PostAnvil DSL/grammar/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, RULE = 2, FILTER = 3, ATTR = 4, FUNC = 5, GROUP = 6, APPEND = 7, 
    FROM = 8, AND = 9, OR = 10, NOT = 11, SELF = 12, NUM = 13, STR = 14, 
    BOOL = 15, INST = 16, ANY = 17, RETURN = 18, IMPORT = 19, EXPORT = 20, 
    AS = 21, IF = 22, ELIF = 23, ELSE = 24, FOR = 25, IN = 26, SORT = 27, 
    ASC = 28, DESC = 29, LCURLY = 30, RCURLY = 31, BOOL_LIT = 32, ARROW = 33, 
    PLUS = 34, MINUS = 35, STAR = 36, SLASH = 37, LT = 38, GT = 39, LE = 40, 
    GE = 41, EQ = 42, NE = 43, DOT = 44, LPAREN = 45, RPAREN = 46, COMMA = 47, 
    ASSIGN = 48, NUMBER = 49, STRING = 50, IDENTIFIER = 51, WS = 52, LINE_CONTINUATION = 53, 
    NEWLINE = 54, COMMENT = 55
  };

  explicit PostAnvilLexer(antlr4::CharStream *input);

  ~PostAnvilLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

