#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <list>

#ifndef LEXER_HPP
# define LEXER_HPP

class Lexer {
  public:
    enum TokenType
    {
      Instruction, // push | pop | dump | assert | add | sub | mul | div | mod | print | exit
//      Operand, // int8(N) | int16(N) | int32(N) | float(Z) | double(Z)
      Int8, // + value
      Int16, // + value 
      Int32, // + value
      Float, // + value
      Double // + value
    };

    Lexer(void);
    Lexer(Lexer const &obj);
    ~Lexer(void);

    Lexer &operator=(Lexer const &rhs);

    void  readFromFile(char *file);
    void  readFromStdin(std::string line);
    void  analysis(void);

    /* Utilities */
    void  displayVectorContent(void);

  private:
    std::vector<std::string> _buff;

};

std::ostream & operator<<(std::ostream & o, Lexer const &obj);

#endif