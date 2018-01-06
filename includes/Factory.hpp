#include "IOperand.hpp"
#include "Token.hpp"

#include <iostream>

#ifndef FACTORY_HPP
# define FACTORY_HPP

class Factory {

  public:
    Factory(void);
    Factory(Factory &model);
    ~Factory(void);

    Factory &operator=(Factory const &rhs);

    /* Factory method (Fabrique) */
    IOperand const *  createOperand( eOperandType type, std::string const & value ) const;    

  private:
    IOperand const *  _createInt8( std::string const & value ) const;
    IOperand const *  _createInt16( std::string const & value ) const;
    IOperand const *  _createInt32( std::string const & value ) const;
    IOperand const *  _createFloat( std::string const & value ) const;
    IOperand const *  _createDouble( std::string const & value ) const;
};

#endif