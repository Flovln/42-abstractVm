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