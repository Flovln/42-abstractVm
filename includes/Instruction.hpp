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

//http://www.cse.chalmers.se/edu/year/2015/course/DAT150/lectures/proglang-04.html
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
    void  tokenizer(void);
    void  tokenizerOld(void);

    std::list<Token>  parseTokens(void);

    /* Dev utilities */
    void  displayVectorContent(std::vector<std::string> buff);
    void  displayTokensList(void);

  private:
    std::vector<Token>       _tokens;
    std::vector<std::string> _chunks;
    std::list<Token>         _instructions;

};

std::ostream & operator<<(std::ostream & o, Instruction const &obj);

#endif

