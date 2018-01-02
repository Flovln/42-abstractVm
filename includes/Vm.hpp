#include <iostream>
#include <list>

#include "Lexer.hpp"
#include "IOperand.hpp"

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

    void  readFromFile(char *file);
    void  readFromStdin(void);
    void  analysis(void);
    void  execute(void);

    /* Factory method (Fabrique) */
    IOperand const *  createOperand( eOperandType type, std::string const & value ) const;    

    /* Development tools */
    void  displayBufferContent(void);
    void  displayTokens(void);
    int   getSource(void);

    std::vector<Token> tokens;

  private:
    IOperand const *  createInt8( std::string const & value ) const;
    IOperand const *  createInt16( std::string const & value ) const;
    IOperand const *  createInt32( std::string const & value ) const;
    IOperand const *  createFloat( std::string const & value ) const;
    IOperand const *  createDouble( std::string const & value ) const;

    Lexer _lexer;

    int   _source; // 0 = file | 1 = stdin
    std::vector<std::string> _buff;
    std::list<Token> _instructions; 
};

#endif