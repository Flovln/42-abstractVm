#include <iostream>

#ifndef OPERAND_HPP
# define OPERAND_HPP

//https://cpp.developpez.com/faq/cpp/?page=Les-templates
//https://www.cprogramming.com/tutorial/templates.html

template<typename T>
class Operand : public IOperand
{
  public:
    Operand<T>(void) {

    }

    Operan<T>(const Operand<T> & model) {

    }

    ~Operand<T>(void) {

    }

    <T>int getPrecision( void );
    <T>eOperandType getType( void );

    <T>const * operator+( T const & rhs );
    <T>const * operator-( T const & rhs );
    <T>const * operator*( T const & rhs );
    <T>const * operator/( T const & rhs );
    <T>const * operator%( T const & rhs );

    std::string const & toString( void );
}

#endif