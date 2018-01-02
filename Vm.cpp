#include "../includes/Vm.hpp"

IOperand const *    Vm::createOperand( eOperandType type, std::string const & value ) const {
  //use array of pointers on member functions with enum values as index
  IOperand *(Vm::*handler[5])(std::string const &) = {
    &Vm::createInt8,
    &Vm::createInt16,
    &Vm::createInt32,
    &Vm::createFloat,
    &Vm::createDouble
  }

  for (int i = 0; i < 5; i++) {
    if ((eOperantType)i == type)
      return (this->*handler[i])(message);
  }
}

/* Operands handling functions */
IOperand const * Vm::createInt8( std::string const & value ) const {

}

IOperand const * Vm::createInt16( std::string const & value ) const {

}

IOperand const * Vm::createInt32( std::string const & value ) const {

}

IOperand const * Vm::createFloat( std::string const & value ) const {

}

IOperand const * Vm::createDouble( std::string const & value ) const {

}