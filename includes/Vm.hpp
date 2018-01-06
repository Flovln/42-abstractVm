#include <iostream>
#include <list>
#include <exception>

#include "Instruction.hpp"
//#include "Operand.tpp"
#include "Token.hpp"
#include "Factory.hpp"

#ifndef VM_HPP
# define VM_HPP

class Vm {
  public:

    Vm(void);
    Vm(Vm const &model);
    ~Vm(void);

    Vm &operator=(Vm const &rhs);

    void  readFromFile(char *file);
    void  readFromStdin(void);
    void  run(void);
    void  handleInstructions(void);
    void  manageSingleInstruction(std::string instruction);

    void  push(std::string operand, std::string value);
    void  assert(std::string operand, std::string value);
    void  pop(void);
    void  dump(void);
    void  add(void);
    void  sub(void);
    void  mul(void);
    void  div(void);
    void  mod(void);
    void  print(void);

    /* Factory method (Fabrique) */
    //IOperand const *  createOperand( eOperandType type, std::string const & value ) const;    

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
        SyntaxException(std::vector<std::string> errors) {
            for (auto &m : errors)
              this->messages.push_back(m);
        }

        virtual void displayErrors(void) const throw ()
        {
          for (auto &iter : this->messages)
          {
            std::cout << iter << std::endl;
          }
        }

        std::vector<std::string> messages;
    };

    /* Development tools */
    void  displayListContent(void);
    void  displayBufferContent(void);
    void  displayTokens(void);
    int   getSource(void);

  private:
    Instruction                 _instruction;
    Factory                     _factory;
/*
    IOperand const *            _createInt8( std::string const & value ) const;
    IOperand const *            _createInt16( std::string const & value ) const;
    IOperand const *            _createInt32( std::string const & value ) const;
    IOperand const *            _createFloat( std::string const & value ) const;
    IOperand const *            _createDouble( std::string const & value ) const;
*/
    int                         _source; // 0 = file | 1 = stdin
    std::vector<std::string>    _buff;
    std::vector<Content>        _instructions;
    std::list<IOperand const *> _stack;

    std::string                 _operands[5];
};

#endif