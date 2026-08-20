
// Generated from grammar/PostAnvil.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  PostAnvilLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, RULE = 2, FILTER = 3, ATTR = 4, FUNC = 5, SORT = 6, GROUP = 7, 
    APPEND = 8, FROM = 9, IMPORT = 10, EXPORT = 11, AS = 12, AND = 13, OR = 14, 
    NOT = 15, BOOL_LIT = 16, SELF = 17, NUM = 18, STR = 19, BOOL = 20, INST = 21, 
    ANY = 22, ALL_INST = 23, RETURN = 24, IF = 25, ELIF = 26, ELSE = 27, 
    FOR = 28, IN = 29, ASC = 30, DESC = 31, LCURLY = 32, RCURLY = 33, ARROW = 34, 
    PLUS = 35, MINUS = 36, STAR = 37, SLASH = 38, LT = 39, GT = 40, LE = 41, 
    GE = 42, EQ = 43, NE = 44, DOT = 45, LPAREN = 46, RPAREN = 47, COMMA = 48, 
    ASSIGN = 49, AT = 50, NUMBER = 51, STRING = 52, IDENTIFIER = 53, WS = 54, 
    LINE_CONTINUATION = 55, NEWLINE = 56, COMMENT = 57
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

