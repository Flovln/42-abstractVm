#include <iostream>
#include <list>
#include <exception>

#include "Instruction.hpp"
#include "IOperand.hpp"

#ifndef VM_HPP
# define VM_HPP

enum eOperandType
{
  Int8,
  Int16,
  Int32,
  Float,
  Double
};

class Vm {
  public:

    Vm(void);
    Vm(Vm const &model);
    ~Vm(void);

    void  readFromFile(char *file);
    void  readFromStdin(void);
    void  run(void);
    void  handleInstructions(void);
    void  manageSimple(std::string instruction);
    void  manageComplex(std::string operand, std::string value);
    void  pop(std::string const &instruction);
    void  dump(std::string const &instruction);
    void  add(std::string const &instruction);
    void  sub(std::string const &instruction);
    void  mul(std::string const &instruction);
    void  div(std::string const &instruction);
    void  mod(std::string const &instruction);
    void  print(std::string const &instruction);

    /* Factory method (Fabrique) */
    IOperand const *  createOperand( eOperandType type, std::string const & value ) const;    
    void createOperand( eOperandType type, std::string const & value ); //test

    std::vector<Token> tokens;

    class ExecutionException : public std::exception
    {
      public:
        ExecutionException(std::string str) : message(str){}

        virtual const char * what(void) const throw ()
        {
          return message.c_str();
        }

        std::string message;
    };

    class SyntaxException : public std::exception
    {
      public:
        SyntaxException(std::string str) : message(str){}

        virtual const char * what(void) const throw ()
        {
          return message.c_str();
        }

        std::string message;
    };

    /* Development tools */
    void  displayListContent(void);
    void  displayBufferContent(void);
    void  displayTokens(void);
    int   getSource(void);

  private:
    IOperand const *  createInt8( std::string const & value ) const;
    IOperand const *  createInt16( std::string const & value ) const;
    IOperand const *  createInt32( std::string const & value ) const;
    IOperand const *  createFloat( std::string const & value ) const;
    IOperand const *  createDouble( std::string const & value ) const;

    Instruction              _instruction;

    int                         _source; // 0 = file | 1 = stdin
    std::vector<std::string>    _buff;
    std::vector<Content>          _instructions;
    std::list<IOperand const *> _stack;
};

#endif