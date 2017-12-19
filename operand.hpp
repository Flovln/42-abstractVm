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

    Operand<T>(const Operand<T> & model) {

    }

    ~Operand<T>(void) {

    }

    int              getPrecision( void );
    eOperandType     getType( void );

    IOperand const * createOperand( eOperandType type, std::string const & value ) const;

    IOperand const * operator+( IOperand const & rhs );
    IOperand const * operator-( IOperand const & rhs );
    IOperand const * operator*( IOperand const & rhs );
    IOperand const * operator/( IOperand const & rhs );
    IOperand const * operator%( IOperand const & rhs );

    std::string const & toString( void );
};

std::ostream & operator<<(std::ostream & o, Operand const & obj);

#endif