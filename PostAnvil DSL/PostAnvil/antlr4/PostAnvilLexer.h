
// Generated from PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, RULE = 2, RULEEND = 3, FILTER = 4, ATTR = 5, FUNC = 6, GROUP = 7, 
    APPEND = 8, FROM = 9, AND = 10, OR = 11, NOT = 12, SELF = 13, NUM = 14, 
    STR = 15, BOOL = 16, ANY = 17, RETURN = 18, IMPORT = 19, EXPORT = 20, 
    AS = 21, IF = 22, ELSE = 23, ENDIF = 24, FOR = 25, IN = 26, ENDFOR = 27, 
    SORT = 28, BOOL_LIT = 29, ARROW = 30, PLUS = 31, MINUS = 32, STAR = 33, 
    SLASH = 34, LT = 35, GT = 36, LE = 37, GE = 38, EQ = 39, NE = 40, DOT = 41, 
    LPAREN = 42, RPAREN = 43, COMMA = 44, ASSIGN = 45, NUMBER = 46, STRING = 47, 
    IDENTIFIER = 48, WS = 49, NEWLINE = 50, COMMENT = 51
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

