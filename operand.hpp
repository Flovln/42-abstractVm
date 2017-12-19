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
    enum eOperandType
    {
      Int8,
      Int16,
      Int32,
      Float,
      Double
    }

    Operand<T>(void) {

    }

    Operand<T>(const Operand<T> & model) {

    }

    ~Operand<T>(void) {

    }

    int                 getPrecision( void );
    eOperandType        getType( void );
    std::string const & toString( void ) const;

    /* Factory method (Fabrique) */
    IOperand const *    createOperand( eOperandType type, std::string const & value ) const;

    IOperand const *    operator+( IOperand const & rhs );
    IOperand const *    operator-( IOperand const & rhs );
    IOperand const *    operator*( IOperand const & rhs );
    IOperand const *    operator/( IOperand const & rhs );
    IOperand const *    operator%( IOperand const & rhs );

  private:

};

std::ostream & operator<<(std::ostream & o, Operand const & obj);

#endif