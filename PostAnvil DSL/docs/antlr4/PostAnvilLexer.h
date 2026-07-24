
// Generated from PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, RULE = 2, RULEEND = 3, FILTER = 4, ATTR = 5, FUNC = 6, GROUP = 7, 
    APPEND = 8, FROM = 9, AND = 10, OR = 11, NOT = 12, SELF = 13, NUM = 14, 
    STR = 15, BOOL = 16, INST = 17, ANY = 18, RETURN = 19, IMPORT = 20, 
    EXPORT = 21, AS = 22, IF = 23, ELIF = 24, ELSE = 25, ENDIF = 26, FOR = 27, 
    IN = 28, ENDFOR = 29, SORT = 30, BOOL_LIT = 31, ARROW = 32, PLUS = 33, 
    MINUS = 34, STAR = 35, SLASH = 36, LT = 37, GT = 38, LE = 39, GE = 40, 
    EQ = 41, NE = 42, DOT = 43, LPAREN = 44, RPAREN = 45, COMMA = 46, ASSIGN = 47, 
    NUMBER = 48, STRING = 49, IDENTIFIER = 50, WS = 51, NEWLINE = 52, COMMENT = 53
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

