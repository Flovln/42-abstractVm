#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>

#ifndef LEXER_HPP
# define LEXER_HPP

class Lexer {
  public:
    enum TokenType
    {
      Instruction, // push | pop | dump | assert | add | sub | mul | div | mod | print | exit
      Separator, // \n
      Value, // int8(N) | int16(N) | int32(N) | float(Z) | double(Z)
      Eof, // ;;
    };

    enum ValueType
    {
      Int8,
      Int16,
      Int32,
      Float,
      Double
    };

    Lexer(void);
    Lexer(Lexer const &obj);
    ~Lexer(void);

    Lexer &operator=(Lexer const &rhs);

    std::vector<std::string>  *readFromFile(char *file);
    std::vector<std::string>  *readFromStdin(std::string line);

    /* Utilities */
    void                      displayVectorContent(void);

  private:
    std::vector<std::string> _buff;

};

std::ostream & operator<<(std::ostream & o, Lexer const &obj);

#endif