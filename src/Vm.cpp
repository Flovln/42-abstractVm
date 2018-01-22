#include "../includes/Vm.hpp"

Vm::Vm(void) {
  std::string values[] = {"int8", "int16", "int32", "float", "double" };
  std::string keys[] = { "pop", "dump", "add", "sub", "mul", "div", "mod", "print" };

  for (int i = 0; i < 5; ++i) {
    this->_operands[i] = values[i];
  }

  for (int i = 0; i < 8; ++i) {
    this->_keys[i] = keys[i];
  }
}

Vm::Vm(Vm const &model) {
  *this = model;
}

Vm::~Vm(void) {
  for (auto &iter: this->_stack) {
    delete(iter);
  }
}

Vm & Vm::operator=(Vm const &rhs) {
  if (this != &rhs)
  {
      this->_instruction = rhs.getInstruction();
      this->_factory = rhs.getFactory();
      this->_source = rhs.getSource();
      this->_buff = rhs.getBuff();
      this->_instructions = rhs.getInstructions();
      //this->_stack = rhs.getStack();

      for (int i = 0; i < 5; ++i)
      {
        this->_operands[i] = rhs._operands[i];
        this->_keys[i] = rhs._operands[i];
      }

  }
  return (*this);
}

Instruction                 Vm::getInstruction(void) const {
  return this->_instruction;
}

Factory                     Vm::getFactory(void) const {
  return this->_factory;
}

int                         Vm::getSource(void) const {
  return this->_source;
}

std::vector<std::string>    Vm::getBuff(void) const {
  return this->_buff;
}

std::vector<Content>        Vm::getInstructions(void) const {
  return this->_instructions;
}

std::list<IOperand const *> Vm::getStack(void) const {
  return this->_stack;
}

void  Vm::readFromFile(char *file) {
  std::string   line;
  std::ifstream ifs(file);

  if (ifs.is_open()) {
    while (std::getline(ifs, line, '\n'))
      this->_buff.push_back(line);

    ifs.close();
  }
  else
    throw Vm::ExecutionException("File open error.");

  this->_source = 0;
}

void  Vm::readFromStdin(void) {
  std::string line;

  while (line != ";;") {
    std::getline(std::cin, line);
    this->_buff.push_back(line);
  }
  this->_source = 1;
}

/* INSTRUCTIONS */

void  Vm::run(void) {
  this->_instruction.lexer(this->_buff);
  this->_instructions = this->_instruction.parser();
  this->handleInstructions();
}

void  Vm::pop(void) {
  if (this->_stack.empty())
    throw Vm::ExecutionException("empty stack.");
  delete this->_stack.front();
  this->_stack.pop_front();
}

void  Vm::dump(void) {
  for (auto &iter: this->_stack)
  {
    if (iter->getType() >= eOperandType::Float)
      std::cout << std::stod(iter->toString()) << std::endl;
    else
      std::cout << std::stoi(iter->toString()) << std::endl;      
  }
}

void  Vm::add(void) {
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");

  IOperand const *v1 = this->_stack.front();
  IOperand const *v2 = *(std::next(this->_stack.begin()));
  IOperand const *res = *v2 + *v1;

  this->_stack.pop_front();
  this->_stack.pop_front();
  this->_stack.push_front(res);
}

void  Vm::sub(void) {
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");

  IOperand const *v1 = this->_stack.front();
  IOperand const *v2 = *(std::next(this->_stack.begin()));
  IOperand const *res = *v2 - *v1;

  this->_stack.pop_front();
  this->_stack.pop_front();
  this->_stack.push_front(res);
}

void  Vm::mul(void) {
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");

  IOperand const *v1 = this->_stack.front();
  IOperand const *v2 = *(std::next(this->_stack.begin()));
  IOperand const *res = *v2 * *v1;

  this->_stack.pop_front();
  this->_stack.pop_front();
  this->_stack.push_front(res);
}

void  Vm::div(void) {
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");

  IOperand const *v1 = this->_stack.front();
  IOperand const *v2 = *(std::next(this->_stack.begin()));

  if (v1->toString() == "0")
    throw Vm::ExecutionException("divisor is equal to 0.");

  IOperand const *res = *v2 / *v1;

  this->_stack.pop_front();
  this->_stack.pop_front();
  this->_stack.push_front(res);
}

void  Vm::mod(void) {
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");

  IOperand const *v1 = this->_stack.front();
  IOperand const *v2 = *(std::next(this->_stack.begin()));
  
  if (v1->getType() >= eOperandType::Float || v2->getType() >= eOperandType::Float)
    throw Vm::ExecutionException("modulo only works on integer types.");

  if (v1->toString() == "0")
    throw Vm::ExecutionException("value is equal to 0.");

  IOperand const *res = *v2 % *v1;

  this->_stack.pop_front();
  this->_stack.pop_front();
  this->_stack.push_front(res);
}

void  Vm::print(void) {
  if (this->_stack.front()->getType() == eOperandType::Int8) {
    std::string value = this->_stack.front()->toString();

    int ascii;
    std::stringstream ss;
    ss << value;
    ss >> ascii;

    std::cout << static_cast<char>(ascii);
  }
  else
    throw Vm::ExecutionException("value is not an 8 bit integer.");
}

void  Vm::push(std::string operand, std::string value) {
  for (int i = 0; i < 5; ++i) {
    if (this->_operands[i] == operand)
      switch(i) {
        case(0):
          this->_stack.push_front(this->_factory.createOperand(eOperandType::Int8, value));
          break;
        case(1):
          this->_stack.push_front(this->_factory.createOperand(eOperandType::Int16, value));
          break;
        case(2):
          this->_stack.push_front(this->_factory.createOperand(eOperandType::Int32, value));
          break;
        case(3):
          this->_stack.push_front(this->_factory.createOperand(eOperandType::Float, value));
          break;
        case(4):
          this->_stack.push_front(this->_factory.createOperand(eOperandType::Double, value));
          break;

        default:
          break;
      }
  }
}

void  Vm::assert(std::string operand, std::string value) {
  if (this->_stack.size() < 1)
    throw Vm::ExecutionException("not a single value in the stack.");

  IOperand const *tmp = this->_stack.front();

  for (int i = 0; i < 5; i++) {
    if (this->_operands[i] == operand) {
      double valueFirst = std::stod(tmp->toString());
      double valueToCompare = std::stod(value);

      if (tmp->getType() != i || valueFirst != valueToCompare)
        throw Vm::ExecutionException("values are not equal.");
    }
  }
}

/* INSTRUCTIONS MANAGER */

void  Vm::manageSingleInstruction(std::string instruction) {
  void (Vm::*handler[8])(void) = {
    &Vm::pop,
    &Vm::dump,
    &Vm::add,
    &Vm::sub,
    &Vm::mul,
    &Vm::div,
    &Vm::mod,
    &Vm::print
  };

  for (int i = 0; i < 8; i++) {
    if (this->_keys[i] == instruction)
      (this->*handler[i])();
  }
}

void  Vm::handleInstructions() {
  for (auto &iter : this->_instructions) {
    auto next = std::next(&iter, 1);
    
    if (iter.value == "push")
      this->push(next->type, next->value);
    else if (iter.value == "assert")
      this->assert(next->type, next->value);
    else
      this->manageSingleInstruction(iter.value);
  }
}