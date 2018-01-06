#include "./includes/Factory.hpp"
#include "./includes/Operand.tpp"

Factory::Factory(void) {}
Factory::Factory(Factory &model) { *this = model; }
Factory::~Factory(void) {}

Factory &Factory::operator=(Factory const &rhs)
{
  if (this != &rhs)
  {
    //copy content
  }

  return (*this);
}

/* Operands handling functions */
IOperand const * Factory::_createInt8( std::string const & value ) const {
  return new Operand<int8_t>(eOperandType::Int8, value);
}

IOperand const * Factory::_createInt16( std::string const & value ) const {
  return new Operand<int16_t>(eOperandType::Int16, value);
}

IOperand const * Factory::_createInt32( std::string const & value ) const {
  return new Operand<int32_t>(eOperandType::Int32, value);
}

IOperand const * Factory::_createFloat( std::string const & value ) const {
  return new Operand<float>(eOperandType::Float, value);
}

IOperand const * Factory::_createDouble( std::string const & value ) const {
  return new Operand<double>(eOperandType::Double, value);
}

IOperand const *    Factory::createOperand( eOperandType type, std::string const & value ) const
{
  IOperand const *(Factory::*handler[5])(std::string const &) const = {
    &Factory::_createInt8,
    &Factory::_createInt16,
    &Factory::_createInt32,
    &Factory::_createFloat,
    &Factory::_createDouble
  };

  return (this->*(handler[type]))(value);
}
