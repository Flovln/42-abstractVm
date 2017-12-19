#include "Operand.hpp"

std::string const & Operad::toString() const {
  std::ostringstream stream;
  std::string *str;
  std::string tmp;

  stream << *this;
  tmp = stream.str();
  str = &tmp;

  return *str;
}

std::ostream & operator<<(std::ostream & o, Operand const & obj) {
//  o << obj.getType() << std::endl
  return o;
}