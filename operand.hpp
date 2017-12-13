#include <iostream>

#ifndef OPERAND_HPP
# define OPERAND_HPP

//https://cpp.developpez.com/faq/cpp/?page=Les-templates
//https://www.cprogramming.com/tutorial/templates.html

template<typename T> class Operand : public AOperand
{
  public:
    template<typename T>int getPrecision( void ) const = 0;
    template<typename T>eOperandType getType( void ) const = 0;

    template<typename T>const * operator+( IOperand const & rhs );
    template<typename T>const * operator-( IOperand const & rhs );
    template<typename T>const * operator*( IOperand const & rhs );
    template<typename T>const * operator/( IOperand const & rhs );
    template<typename T>const * operator%( IOperand const & rhs );

    std::string const & toString( void ) const = 0;
}

#endif