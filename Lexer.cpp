#include "Lexer.hpp"

Lexer::Lexer(void) {}

Lexer::Lexer(Lexer const &obj) {
  *this = obj;
}

Lexer::~Lexer(void) {}

Lexer & Lexer::operator=(Lexer const &rhs) {
  if (this != &rhs) {
    //this->name = rhs.name;
    //...
  }

  return (*this)
}

/* Non member function */

std::ostream & operator<<(std::ostream & o, Lexer const &obj )
{
  o << "operator overload" << std::endl;
  return o;
}