#include <sstream>
#include <iostream>
#include <string>

#include "IOperand.hpp"
#include "Token.hpp"

#ifndef OPERAND_HPP
# define OPERAND_HPP

template<typename T>
class Operand : public IOperand
{
  public:
    Operand(void) {}
    Operand(eOperandType type, std::string value) : _type(type), _value(value)
    {
      // do checking on value overflow, etc ..
      std::cout << "||||| CONSTRUCTOR ||||||" << std::endl;
      std::cout << "value: " << this->getValue() << ", type: " << this->getType() << std::endl;
      std::cout << "||||||||||||||||||||||||" << std::endl;

      
    }

    Operand(const Operand & model) { *this = model; }
    ~Operand(void) {}

    int                 getPrecision( void ) const { return this->_type; }
    eOperandType        getType( void ) const { return this->_type; }
    std::string         getValue( void ) { return this->_value; }

    std::string const & toString( void ) const {
/*      std::ostringstream stream;
      std::string *str;
      std::string tmp;

      stream << *this;
      tmp = stream.str();
      str = &tmp;

      return *str;*/
      return this->_value;
    }

    IOperand const *    operator+( IOperand const & rhs ) const {
      std::cout << "ADD" << std::endl;
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 + v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return &rhs;//this->createOperand(this->getType(), value);
    }

    IOperand const *    operator-( IOperand const & rhs ) const {
      std::cout << "SUB" << std::endl;
//      std::cout << "v1: " << v1 << ", " << "v2: " << v2 << std::endl;
//      std::cout << "value: " << value << std::endl;
      return &rhs;
    }

    IOperand const *    operator*( IOperand const & rhs ) const {
      std::cout << "MUL" << std::endl;
      return &rhs;
    }

    IOperand const *    operator/( IOperand const & rhs ) const {
      std::cout << "DIV" << std::endl;
      return &rhs;
    }

    IOperand const *    operator%( IOperand const & rhs ) const {
      std::cout << "MOD" << std::endl;
      return &rhs;
    }

  private:
    eOperandType _type;
    std::string  _value;
};

#endif