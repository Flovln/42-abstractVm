#include <iostream>
#include <list>
#include <exception>

#include "Instruction.hpp"
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

    int   getSource(void);
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

  private:
    Instruction                 _instruction;
    /* Factory method class */
    Factory                     _factory;

    int                         _source; // 0 = file | 1 = stdin
    std::vector<std::string>    _buff;
    std::vector<Content>        _instructions;
    std::list<IOperand const *> _stack;

    std::string                 _operands[5];
    std::string                 _keys[8];
};

#endif