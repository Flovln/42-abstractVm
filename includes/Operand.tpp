#include <sstream>
#include <iostream>
#include <string>
#include <math.h>
#include <climits>
#include <cfloat>

#include "Token.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"
#include "Vm.hpp"

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

      if (this->_type == eOperandType::Float)
        this->_value = std::stof(this->_valueStr);
      else if (this->_type == eOperandType::Double)
        this->_value = std::stod(this->_valueStr);
      else if (this->_type == eOperandType::Int8 || this->_type == eOperandType::Int16 || this->_type == eOperandType::Int32)
        this->_value = std::stoi(this->_valueStr);

      if (type == eOperandType::Int8 && (this->_value < SCHAR_MIN || this->_value > SCHAR_MAX))
        throw Vm::ExecutionException("Overflow or underflow on char.");
      else if (type == eOperandType::Int16 && (this->_value < SHRT_MIN || this->_value > SHRT_MAX))
        throw Vm::ExecutionException("Overflow or underflow on short.");
      else if (type == eOperandType::Int32 && (this->_value < INT_MIN || this->_value > INT_MAX))
        throw Vm::ExecutionException("Oveflow or underflow on int");
      else if (type == eOperandType::Float && (this->_value < FLT_MIN || this->_value > FLT_MAX))
        throw Vm::ExecutionException("Oveflow or underflow on float");
      else if (type == eOperandType::Double && (this->_value < DBL_MIN || this->_value > DBL_MAX))
        throw Vm::ExecutionException("Overflow or underflow on double");
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

      //check overflow and underflow on result

      if (this->getPrecision() > rhs.getPrecision())        
        return this->_factory.createOperand(this->getType(), std::to_string(res));
      else
        return this->_factory.createOperand(rhs.getType(), std::to_string(res));
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

      //std::cout << "res: " << res << std::endl;
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