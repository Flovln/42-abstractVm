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
    Operand<T>(void) {}

    Operand<T>(const Operand<T> & model) {}

    ~Operand<T>(void) {}

    int                 getPrecision( void );
    eOperandType        getType( void );
    std::string const & toString( void ) const;

    IOperand const *    operator+( IOperand const & rhs );
    IOperand const *    operator-( IOperand const & rhs );
    IOperand const *    operator*( IOperand const & rhs );
    IOperand const *    operator/( IOperand const & rhs );
    IOperand const *    operator%( IOperand const & rhs );

  private:

};

std::ostream & operator<<(std::ostream & o, Operand const & obj);

#endif