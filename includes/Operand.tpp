#include <sstream>
#include <iostream>

#include "IOperand.hpp"
#include "Token.hpp"

#ifndef OPERAND_HPP
# define OPERAND_HPP

//https://cpp.developpez.com/faq/cpp/?page=Les-templates
//https://www.cprogramming.com/tutorial/templates.html

template<typename T>
class Operand : public IOperand
{
  public:
    Operand(void) {}
    Operand(eOperandType type, std::string value) : _type(type), _value(value) {}

    Operand(const Operand & model) { *this = model; }
    ~Operand(void) {}

    int                 getPrecision( void ) const { return this->_type; }
    eOperandType        getType( void ) const { return this->_type; }
    std::string         getValue( void ) { return this->_value; }

    std::string const & toString( void ) const {
      std::ostringstream stream;
      std::string *str;
      std::string tmp;

      stream << *this;
      tmp = stream.str();
      str = &tmp;

      return *str;
    }

    IOperand const *    operator+( IOperand const & rhs ) const {
      std::cout << "YO" << std::endl;
      return &rhs;
    }

    IOperand const *    operator-( IOperand const & rhs ) const {
      std::cout << "YO" << std::endl;
      return &rhs;
    }

    IOperand const *    operator*( IOperand const & rhs ) const {
      std::cout << "YO" << std::endl;
      return &rhs;
    }

    IOperand const *    operator/( IOperand const & rhs ) const {
      std::cout << "YO" << std::endl;
      return &rhs;
    }

    IOperand const *    operator%( IOperand const & rhs ) const {
      std::cout << "YO" << std::endl;
      return &rhs;
    }

    void  test(void){
      std::cout << "Value: " << this->getValue << std::endl;
    }

  private:
    eOperandType _type;
    std::string  _value;
};

#endif