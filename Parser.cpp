#include "Parser.hpp"

Parser::Parser(void) {}

Parser::Parser(Parser const &obj) {
  *this = obj;
}

Parser::~Parser(void) {}

Parser & Parser::operator=(Parser const &rhs) {
  if (this != &rhs) {
    //this->name = rhs.name;
    //...
  }

  return (*this);
}
/*
void  Parser::test(void)
{
  std::vector<Lexer::token>::iterator iter = Lexer::tokens.begin();
  std::vector<Lexer::token>::iterator end = Lexer::tokens.end();

  std::cout << "--- Tokens list ---" << std::endl;
  while (iter != end)
  {
    std::cout << "Token: " << "{ " << iter[0].type << ", " << iter[0].value << " }" << std::endl;
    ++iter;
  }
  std::cout << "--- --- ---" << std::endl;  
}*/