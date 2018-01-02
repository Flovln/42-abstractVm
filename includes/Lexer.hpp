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

#ifndef LEXER_HPP
# define LEXER_HPP

//http://www.cse.chalmers.se/edu/year/2015/course/DAT150/lectures/proglang-04.html
#define INSTRUCTION "Instruction"
#define LEXICAL_ERROR "LexicalError"
#define UNKNOWN_INSTRUCTION "UnknownInstruction"
#define INT8 "Int8"
#define INT16 "Int16"
#define INT32 "Int32"
#define FLOAT "Float"
#define DOUBLE "Double"

class Lexer {
  public:

    Lexer(void);
    Lexer(Lexer const &obj);
    ~Lexer(void);

    Lexer &operator=(Lexer const &rhs);

    std::vector<Token>  lexicalAnalysis(std::vector<std::string> buff, int source);
    void  getChunks(std::string str);
    void  tokenizeChunks(void);

    void  parseTokens(void);

    /* Dev utilities */
    void  displayVectorContent(std::vector<std::string> buff);
    void  displayTokensList(void);

    std::vector<Token> tokens;

  private:
    std::vector<std::string> _chunks;

};

std::ostream & operator<<(std::ostream & o, Lexer const &obj);

#endif

