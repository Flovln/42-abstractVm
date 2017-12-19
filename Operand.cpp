#include "Operand.hpp"

std::string const & Operand::toString() const {
  std::ostringstream stream;
  std::string *str;
  std::string tmp;

  stream << *this;
  tmp = stream.str();
  str = &tmp;

  return *str;
}

IOperand const *    Operand::createOperand( eOperandType type, std::string const & value ) const {
  //use array of pointers on member functions with enum values as an array
}

IOperand const *    operator+( IOperand const & rhs ) {

}

IOperand const *    operator-( IOperand const & rhs ) {

}

IOperand const *    operator*( IOperand const & rhs ) {

}

IOperand const *    operator/( IOperand const & rhs ) {

}

IOperand const *    operator%( IOperand const & rhs ) {
  
}


std::ostream & operator<<(std::ostream & o, Operand const & obj) {
//  o << obj.getType() << std::endl
  return o;
}