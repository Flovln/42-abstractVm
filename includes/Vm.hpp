#include <iostream>
#include <list>
#include <exception>
#include <cmath>

#include "Instruction.hpp"
#include "Infos.hpp"
#include "Factory.hpp"

#ifndef VM_HPP
# define VM_HPP

class Vm {
  public:

    Vm(void);
    Vm(Vm const &model);
    ~Vm(void);

    Vm &operator=(Vm const &rhs);

    Instruction                 getInstruction(void) const;
    Factory                     getFactory(void) const;
    int                         getSource(void) const;
    std::vector<std::string>    getBuff(void) const ;
    std::vector<Content>        getInstructions(void) const;
    std::list<IOperand const *> getStack(void) const;

    void                        readFromFile(char *file);
    void                        readFromStdin(void);
    void                        run(void);
    void                        handleInstructions(void);
    void                        manageSingleInstruction(std::string instruction);

    void                        push(std::string operand, std::string value);
    void                        assert(std::string operand, std::string value);
    void                        pop(void);
    void                        dump(void);
    void                        add(void);
    void                        sub(void);
    void                        mul(void);
    void                        div(void);
    void                        mod(void);
    void                        print(void);

    class ExecutionException : public std::exception {
      public:
        ExecutionException(std::string str) : message(str){}

        virtual const char * what(void) const throw ()
        {
          return message.c_str();
        }

        std::string message;
    };

    class SyntaxException : public std::exception {
      public:
        SyntaxException(std::vector<std::string> errors) {
            for (auto &m : errors)
              this->messages.push_back(m);
        }

        virtual void displayErrors(void) const throw () {
          
          for (auto &iter : this->messages) {
            std::cout << "\033[1;33m" << "Syntax error - " << "\033[0m" << iter << std::endl;
          }
        }

        std::vector<std::string> messages;
    };

  private:
    Instruction                 _instruction;
    Factory                     _factory;

    int                         _source; // 0 = file | 1 = stdin
    std::vector<std::string>    _buff;
    std::vector<Content>        _instructions;
    std::list<IOperand const *> _stack;

    std::string                 _operands[5];
    std::string                 _keys[8];
};

#endif