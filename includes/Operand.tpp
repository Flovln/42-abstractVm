#include <sstream>
#include <iostream>
#include <string>
#include <math.h>

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
    Operand(eOperandType type, std::string value) : _type(type), _valueStr(value)
    {
      // do checking on value overflow, etc ..
      std::cout << "||||| CONSTRUCTOR ||||||" << std::endl;
      std::cout << "value: " << this->toString() << ", type: " << this->getType() << std::endl;
      std::cout << "||||||||||||||||||||||||" << std::endl;

      if (this->_value >= eOperandType::Float)
        this->_value = std::stod(this->_valueStr);
      else
        this->_value = round(std::stod(this->_valueStr));
/*
      if (type == eOperandType::Int8 && (this->_valueStr < 0 || this->_valueStr > 255))
        throw Operand::Execution("");
      else if (type == eOperandType::Int16)
      else if (type == eOperandType::Int32)
      else if (type == eOperandType::Float)
      else if (type == eOperandType::Double)*/
    }

    Operand(const Operand & model) { *this = model; }
    ~Operand(void) {}

    int            getPrecision( void ) const { return this->_type; }
    eOperandType   getType( void ) const { return this->_type; }
    double         getValue( void ) { return this->_value; }

    std::string const & toString( void ) const {
      return this->_valueStr;
    }

    IOperand const *    operator+( IOperand const & rhs ) const {
      std::cout << "ADD" << std::endl;
      //double res = this->getValue() + rhs.getValue();
      double v2;

      if (rhs.getType() >= eOperandType::Float)
        v2 = std::stod(rhs.toString());
      else
        v2 = round(std::stod(rhs.toString()));

      double res = this->_value + v2;

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
/*
      int v1 = std::stoi(this->toString());
      int v2 = std::stoi(rhs.toString());
      int res = v1 + v2;

      std::stringstream ss;
      ss << res;
      std::string value = ss.str();

      return this->_factory.createOperand(this->getType(), value);*/
    }

    IOperand const *    operator-( IOperand const & rhs ) const {
      std::cout << "SUB" << std::endl;
      //double res = this->getValue() - rhs.getValue();
      double v2;

      if (rhs.getType() >= eOperandType::Float)
        v2 = std::stod(rhs.toString());
      else
        v2 = round(std::stod(rhs.toString()));

      double res = this->_value - v2;

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
    }

    IOperand const *    operator*( IOperand const & rhs ) const {
      std::cout << "MUL" << std::endl;
      //double res = this->getValue() * rhs.getValue();
      double v2;

      if (rhs.getType() >= eOperandType::Float)
        v2 = std::stod(rhs.toString());
      else
        v2 = round(std::stod(rhs.toString()));

      double res = this->_value * v2;

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
    }

    IOperand const *    operator/( IOperand const & rhs ) const {
      std::cout << "DIV" << std::endl;
      //double res = this->getValue() / rhs.getValue();
      double v2;

      if (rhs.getType() >= eOperandType::Float)
        v2 = std::stod(rhs.toString());
      else
        v2 = round(std::stod(rhs.toString()));

      double res = this->_value / v2;

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
    }

    IOperand const *    operator%( IOperand const & rhs ) const {
      //double res = this->getValue() % rhs.getValue();
      if (this->getType() >= eOperandType::Float || rhs.getType() >= eOperandType::Float)
        std::cout << "Throw error!" << std::endl;

      int v2;
      
      if (rhs.getType() >= eOperandType::Float)
        v2 = std::stoi(rhs.toString());
      else
        v2 = std::stoi(rhs.toString());

      int res = std::stoi(this->toString()) % v2;

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
    }

  private:
    Factory      _factory;
    eOperandType _type;
    std::string  _valueStr;
    double       _value;
};

#endif