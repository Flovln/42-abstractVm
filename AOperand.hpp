#ifndef AOPERAND_HPP
# define AOPERAND_HPP

class AOperand : public IOperand
{
  public:
    AOperand();
    virtual ~AOperand();

    virtual int getPrecision( void ) const = 0;
    virtual eOperandType getType( void ) const = 0;

    virtual const * operator+( IOperand const & rhs ) = 0;
    virtual const * operator-( IOperand const & rhs ) = 0;
    virtual const * operator*( IOperand const & rhs ) = 0;
    virtual const * operator/( IOperand const & rhs ) = 0;
    virtual const * operator%( IOperand const & rhs ) = 0;

    virtual std::string const & toString( void ) const = 0;    
}

#endif