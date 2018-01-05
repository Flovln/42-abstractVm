#include "./includes/Vm.hpp"

Vm::Vm(void) {
//  std::string keys[] = { "pop", "dump", "add", "sub", "mul", "div", "mod", "print" };
//   std::string operands[] = { "int8", "int16", "int32", "float", "double" };
}

Vm::Vm(Vm const &model) {
  *this = model;
}

Vm::~Vm(void) {
  //delete instances
}

Vm & Vm::operator=(Vm const &rhs)
{
  if (this != &rhs)
  {
      //this->name = rhs.name;
      //...
  }
  return (*this);
}

int  Vm::getSource(void) {
  return this->_source;
}

void  Vm::readFromFile(char *file) {
  std::string   line;
  std::ifstream ifs(file);

  if (ifs.is_open())
  {
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

  while (line != ";;")
  {
    std::getline(std::cin, line);
    this->_buff.push_back(line);
  }
  this->_source = 1;
}

void  Vm::run(void) {
  this->_instruction.lexer(this->_buff, this->_source);
  this->_instructions = this->_instruction.parser();  
  this->handleInstructions();
}

void  Vm::pop(void)
{
  std::cout << "Pop instruction: " << std::endl;
  if (this->_stack.empty())
    throw Vm::ExecutionException("empty stack.");
  //delete *(this->_stack.front());
  this->_stack.pop_front();
}

void  Vm::dump(void)
{
  std::list<IOperand const *>::reverse_iterator start = this->_stack.rend();

  for (std::list<IOperand const *>::reverse_iterator iter = this->_stack.rbegin(); iter != start; iter++)
    std::cout << (*iter)->toString() << std::endl;
}

void  Vm::add(void)
{
  std::cout << "Add instruction: " << std::endl;
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");
}

void  Vm::sub(void)
{
  std::cout << "Sub instruction: " << std::endl;
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");
}

void  Vm::mul(void)
{
  std::cout << "Mul instruction: " << std::endl;
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");
}

void  Vm::div(void)
{
  std::cout << "Div instruction: " << std::endl;  
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");
}

void  Vm::mod(void)
{
  std::cout << "Mod instruction: " << std::endl;  
  if (this->_stack.size() < 2)
    throw Vm::ExecutionException("less than 2 values in the stack.");
}

void  Vm::print(void)
{
  if (this->_stack.front()->getType() == eOperandType::Int8)
    std::cout << this->_stack.front()->toString() << std::endl;
  else
    throw Vm::ExecutionException("value is not an 8 bit integer.");
}

void  Vm::manageOperand(std::string operand, std::string value)
{
  std::string operands[] = { "int8", "int16", "int32", "float", "double" };

  //std::cout << "{ " << operand << ", " << value << " }" << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    if (operands[i] == operand)
      switch(i)
      {
        case(0):
          this->_stack.push_back(this->createOperand(eOperandType::Int8, value));
          break;
        case(1):
          this->_stack.push_back(this->createOperand(eOperandType::Int16, value));
          break;
        case(2):
          this->_stack.push_back(this->createOperand(eOperandType::Int32, value));
          break;
        case(3):
          this->_stack.push_back(this->createOperand(eOperandType::Float, value));
          break;
        case(4):
          this->_stack.push_back(this->createOperand(eOperandType::Double, value));
          break;

        default:
          break;
      }
  }
}

void  Vm::push(std::string operand, std::string value)
{
  std::cout << "Push instruction" << std::endl; 
  this->manageOperand(operand, value);
}

void  Vm::assert(std::string operand, std::string value)
{
  std::cout << "Assert instruction" << std::endl; 
  this->manageOperand(operand, value);
}

void  Vm::manageSimple(std::string instruction)
{
  std::string keys[] = { "pop", "dump", "add", "sub", "mul", "div", "mod", "print" };
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

  for (int i = 0; i < 8; i++)
  {
    if (keys[i] == instruction)
      (this->*handler[i])();
  }
}

void  Vm::handleInstructions()
{
  for (auto &iter : this->_instructions)
  {
    //std::cout << "Node: " << "{ " << iter.type << ", " << iter.value  << " }" << std::endl;
    auto next = std::next(&iter, 1);
    
    if (iter.value == "push")
      this->push(next->type, next->value);
    else if (iter.value == "assert")
      this->assert(next->type, next->value);
    else
      this->manageSimple(iter.value);
  }
}

/* Operands handling functions */
IOperand const * Vm::_createInt8( std::string const & value ) const {
  return new Operand<int8_t>(eOperandType::Int8, value);
}

IOperand const * Vm::_createInt16( std::string const & value ) const {
  return new Operand<int16_t>(eOperandType::Int16, value);
}

IOperand const * Vm::_createInt32( std::string const & value ) const {
  return new Operand<int32_t>(eOperandType::Int32, value);
}

IOperand const * Vm::_createFloat( std::string const & value ) const {
  return new Operand<float>(eOperandType::Float, value);
}

IOperand const * Vm::_createDouble( std::string const & value ) const {
  return new Operand<double>(eOperandType::Double, value);
}

IOperand const *    Vm::createOperand( eOperandType type, std::string const & value ) const
{
//  std::cout << "--- Create new operand ---" << std::endl;
//  std::cout << "{ " << type << ", " << value << " }"<< std::endl;

  IOperand const *(Vm::*handler[5])(std::string const &) const = {
    &Vm::_createInt8,
    &Vm::_createInt16,
    &Vm::_createInt32,
    &Vm::_createFloat,
    &Vm::_createDouble
  };

  return (this->*(handler[type]))(value);
}

/* Development tools */

void  Vm::displayListContent(void) {
  std::cout << "--- List content ---" << std::endl;
  for (auto &iter : this->_instructions)
  {
    std::cout << "Node: " << "{ " << iter.type << ", " << iter.value << " }" << std::endl;
  }
}

void  Vm::displayBufferContent(void) {
  std::cout << "--- Buffer(vector) content ---" << std::endl;
  std::cout << "Source: " << this->getSource() << std::endl;

  std::vector<std::string>::iterator iter = this->_buff.begin();
  std::vector<std::string>::iterator end = this->_buff.end();

  while (iter != end)
  {
    std::cout << (*iter) << std::endl;
    ++iter;
  }

  std::cout << "---------" << std::endl;
}