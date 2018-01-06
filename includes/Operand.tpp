#include <sstream>
#include <iostream>
#include <string>

#include "Token.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"

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

      //if (type == eOperandType::Float)
    }

    Operand(const Operand & model) { *this = model; }
    ~Operand(void) {}

    int                 getPrecision( void ) const { return this->_type; }
    eOperandType        getType( void ) const { return this->_type; }
    std::string         getValue( void ) { return this->_value; }

    std::string const & toString( void ) const {
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

      return this->_factory.createOperand(this->getType(), value);
    }

    IOperand const *    operator-( IOperand const & rhs ) const {
      std::cout << "SUB" << std::endl;
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 - v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return this->_factory.createOperand(this->getType(), value);
    }

    IOperand const *    operator*( IOperand const & rhs ) const {
      std::cout << "MUL" << std::endl;
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 * v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return this->_factory.createOperand(this->getType(), value);
    }

    IOperand const *    operator/( IOperand const & rhs ) const {
      std::cout << "DIV" << std::endl;
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 / v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return this->_factory.createOperand(this->getType(), value);
    }

    IOperand const *    operator%( IOperand const & rhs ) const {
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 % v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return this->_factory.createOperand(this->getType(), value);
      return &rhs;
    }

  private:
    Factory      _factory;
    eOperandType _type;
    std::string  _value;
};

#endif