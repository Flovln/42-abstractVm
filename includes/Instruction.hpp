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

#include "Token.hpp"

#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

class Instruction {

  public:

    Instruction(void);
    Instruction(Instruction const &obj);
    ~Instruction(void);

    Instruction &operator=(Instruction const &rhs);

    /* LEXER */
    void  lexicalAnalysis(std::vector<std::string> buff, int source);
    void  createChunks(std::string str);
    void  removeComments(void);
    void  tokenizer(void);
    void  tokenizeSimple(std::string chunk);
    void  tokenizeComplex(std::string chunk);

    /* PARSER */
    std::vector<Content>  parser(void);

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

    Token _next;
};

std::ostream & operator<<(std::ostream & o, Instruction const &obj);

#endif

