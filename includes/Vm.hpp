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
    void  manageOperand(std::string operand, std::string value);

    void  push(std::string operand, std::string value);
    void  assert(std::string operand, std::string value);
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

    IOperand const *            _createInt8( std::string const & value ) const;
    IOperand const *            _createInt16( std::string const & value ) const;
    IOperand const *            _createInt32( std::string const & value ) const;
    IOperand const *            _createFloat( std::string const & value ) const;
    IOperand const *            _createDouble( std::string const & value ) const;

    int                         _source; // 0 = file | 1 = stdin
    std::vector<std::string>    _buff;
    std::vector<Content>        _instructions;
    std::list<IOperand const *> _stack;
};

#endif