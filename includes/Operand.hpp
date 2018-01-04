#include <sstream>
#include <iostream>

#ifndef OPERAND_HPP
# define OPERAND_HPP

//https://cpp.developpez.com/faq/cpp/?page=Les-templates
//https://www.cprogramming.com/tutorial/templates.html

template<typename T>
class Operand : public IOperand
{
  public:
    Operand(void) {}

    Operand(const Operand & model) {}

    ~Operand(void) {}

    int                 getPrecision( void );
    eOperandType        getType( void );

    std::string const & Operand::toString() const {
      std::ostringstream stream;
      std::string *str;
      std::string tmp;

      stream << *this;
      tmp = stream.str();
      str = &tmp;

      return *str;
    }

    IOperand const *    operator+( IOperand const & rhs ) {

    }

    IOperand const *    operator-( IOperand const & rhs ) {

    }

    IOperand const *    operator*( IOperand const & rhs ) {

    }

    IOperand const *    operator/( IOperand const & rhs ) {

    }

    IOperand const *    operator%( IOperand const & rhs ){

    }

  private:

};

#endif