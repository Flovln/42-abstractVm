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

#ifndef LEXER_HPP
# define LEXER_HPP

class Lexer {
  public:
    enum TokenType
    {
      Instruction, // push | pop | dump | assert | add | sub | mul | div | mod | print | exit
//      Operand, // int8(N) | int16(N) | int32(N) | float(Z) | double(Z)
      Comment,
      Int8, // + value
      Int16, // + value 
      Int32, // + value
      Float, // + value
      Double // + value
    };

    enum InstructionType
    {
      push,
      pop,
      dump,
      assert,
      add,
      sub,
      mul,
      div,
      mod,
      print,
      exit
    };

    Lexer(void);
    Lexer(Lexer const &obj);
    ~Lexer(void);

    Lexer &operator=(Lexer const &rhs);

    void  readFromFile(char *file);
    void  readFromStdin(std::string line);
    void  analysis(void);
    bool  checkIfComment(std::string str);
    void  getChunks(std::string str);
    void  tokenizeChunks(void);

    /* Utilities */
    void  displayVectorContent(void);
    void  printTokens(void);

  private:
    std::vector<std::string> _buff;
    std::vector<std::string> _chunks;
    std::vector<std::string> _tokens;

    std::vector<std::string> _instructionType;
};

std::ostream & operator<<(std::ostream & o, Lexer const &obj);

#endif