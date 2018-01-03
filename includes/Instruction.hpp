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

#define INSTRUCTION "Instruction" // to rename
#define LEXICAL_ERROR "LexicalError"
#define UNKNOWN_INSTRUCTION "UnknownInstruction"
#define INT8 "Int8"
#define INT16 "Int16"
#define INT32 "Int32"
#define FLOAT "Float"
#define DOUBLE "Double"

class Instruction {
  public:

    Instruction(void);
    Instruction(Instruction const &obj);
    ~Instruction(void);

    Instruction &operator=(Instruction const &rhs);

    void  lexicalAnalysis(std::vector<std::string> buff, int source);
    void  createChunks(std::string str);
    void  removeComments(void);
    void  tokenizer(void);
    void  tokenizeSimple(std::string chunk);
    void  tokenizeComplex(std::string chunk);
    std::list<Token>  parseTokens(void);

    /* Dev utilities */
    void  displayVectorContent(std::vector<std::string> buff);
    void  displayTokensList(void);
    void  displayTokensListWithoutComments(void);

  private:
    std::vector<std::string> _chunks;
    std::vector<std::string> _commentsRemoved;
    std::vector<Token>       _tokens;
    std::list<Token>         _instructions;
    bool                     _markedAsComment;
    bool                     _markAsLexicalError;
    bool                     _markAsUnknownInstruction;

};

std::ostream & operator<<(std::ostream & o, Instruction const &obj);

#endif

