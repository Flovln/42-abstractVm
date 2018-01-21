#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <list>
#include <string>
#include <string.h>
#include <algorithm>
#include <iterator>

#include "Infos.hpp"

#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

struct Token {
  
  enum Type {
    Instruction,
    Operand,
    /* Errors */
    LexicalError,
    UnknownInstruction
  };

  int         line;
  Type        type;
  std::string valueType;
  std::string value;
};

class Instruction {

  public:

    Instruction(void);
    Instruction(Instruction const &obj);
    ~Instruction(void);

    Instruction &operator=(Instruction const &rhs);

    /* LEXER */
    void  lexer(std::vector<std::string> buff);
    void  createChunks(std::string str);
    void  removeComments(void);
    void  tokenizer(void);
    void  tokenizeSimple(std::string chunk);
    void  tokenizeComplex(std::string chunk);

    /* PARSER */
    std::vector<Content>  parser(void);
    void                  checkInstructions(Token iterator, Token *next, int line);
    void                  checkOperands(Token iterator, int line);


    void  setLine(int nb);
    
    /* Dev utilities */
    void  displayVectorContent(std::vector<std::string> buff);
    void  displayTokensList(void);
    void  displayTokensListWithoutComments(void);

  private:
    int                      _line;
    std::vector<std::string> _errors;
    std::vector<std::string> _chunks;
    std::vector<std::string> _commentsRemoved;
    std::vector<Token>       _tokens;
    std::vector<Content>     _instructions;
    bool                     _markedAsComment;
    bool                     _markAsLexicalError;
    bool                     _markAsUnknownInstruction;
};

std::ostream & operator<<(std::ostream & o, Instruction const &obj);

#endif

