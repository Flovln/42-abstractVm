#include <iostream>
#include <list>

#include "Lexer.hpp"

#ifndef VM_HPP
# define VM_HPP

class Vm
{
  public:
    enum eOperandType
    {
      Int8,
      Int16,
      Int32,
      Float,
      Double
    };

    /* Factory method (Fabrique) */
    IOperand const *  createOperand( eOperandType type, std::string const & value ) const;    

  private:
    IOperand const *  createInt8( std::string const & value ) const;
    IOperand const *  createInt16( std::string const & value ) const;
    IOperand const *  createInt32( std::string const & value ) const;
    IOperand const *  createFloat( std::string const & value ) const;
    IOperand const *  createDouble( std::string const & value ) const;    
};

#endif