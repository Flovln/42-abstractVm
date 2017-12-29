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
