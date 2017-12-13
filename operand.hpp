#include <iostream>

#ifndef OPERAND_HPP
# define OPERAND_HPP

//https://cpp.developpez.com/faq/cpp/?page=Les-templates
//https://www.cprogramming.com/tutorial/templates.html

template<typename T> class Operand : public IOperand
{
  public:
    const * operator+( IOperand const & rhs );
    const * operator-( IOperand const & rhs );
    const * operator*( IOperand const & rhs );
    const * operator/( IOperand const & rhs );
    const * operator%( IOperand const & rhs );    
}

#endif