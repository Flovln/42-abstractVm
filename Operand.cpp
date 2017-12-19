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
  //use array of pointers on member functions with enum values as index
  IOperand *(Operand::*handler[5])(std::string const &) = {
    &Operand::createInt8,
    &Operand::createInt16,
    &Operand::createInt32,
    &Operand::createFloat,
    &Operand::createDouble
  }

  for (int i = 0; i < 5; i++) {
    if ((eOperantType)i == type)
      return (this->*handler[i])(message);
  }
}

/* Operators functions */
IOperand const * createInt8( std::string const & value ) const {

}

IOperand const * createInt16( std::string const & value ) const {

}

IOperand const * createInt32( std::string const & value ) const {

}

IOperand const * createFloat( std::string const & value ) const {

}

IOperand const * createDouble( std::string const & value ) const {

}

/* Overload operators */
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