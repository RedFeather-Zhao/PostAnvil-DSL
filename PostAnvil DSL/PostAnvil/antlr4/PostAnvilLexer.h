
// Generated from D:/UserProject/vsstudio/PostAnvil DSL/PostAnvil DSL/docs/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilLexer : public antlr4::Lexer {
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

