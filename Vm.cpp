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

void  Vm::pop(std::string const &instruction)
{
  std::cout << "Pop instruction: " << instruction << std::endl;
}

void  Vm::dump(std::string const &instruction)
{
  std::cout << "Dump instruction: " << instruction << std::endl;
}

void  Vm::add(std::string const &instruction)
{
  std::cout << "Add instruction: " << instruction << std::endl;
}

void  Vm::sub(std::string const &instruction)
{
  std::cout << "Sub instruction: " << instruction << std::endl;
}

void  Vm::mul(std::string const &instruction)
{
  std::cout << "Mul instruction: " << instruction << std::endl;
}

void  Vm::div(std::string const &instruction)
{
  std::cout << "Div instruction: " << instruction << std::endl;  
}

void  Vm::mod(std::string const &instruction)
{
  std::cout << "Mod instruction: " << instruction << std::endl;  
}

void  Vm::print(std::string const &instruction)
{
  std::cout << "Print instruction: " << instruction << std::endl; 
}

void  Vm::manageSimple(std::string instruction)
{
  std::string keys[] = { "pop", "dump", "add", "sub", "mul", "div", "mod", "print" };
  void (Vm::*handler[8])(std::string const &) = {
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
      (this->*handler[i])(instruction);
  }
}

void  Vm::manageComplex(std::string operand, std::string value)
{
  std::string operands[] = { "int8", "int16", "int32", "float", "double" };

  for (int i = 0; i < 5; ++i)
  {
    //std::cout << "Operand: " << operand << std::endl;
    //std::cout << "Value: " << value << std::endl;
    if (operands[i] == operand)
      switch(i)
      {
        case(0):
          this->createOperand(eOperandType::Int8, value);
          break;
        case(1):
          this->createOperand(eOperandType::Int16, value);
          break;
        case(2):
          this->createOperand(eOperandType::Int32, value);
          break;
        case(3):
          this->createOperand(eOperandType::Float, value);
          break;
        case(4):
          this->createOperand(eOperandType::Double, value);
          break;

        default:
          break;
      }
  }
}

void  Vm::handleInstructions()
{
  for (auto &iter : this->_instructions)
  {
    std::cout << "Node: " << "{ " << iter.type << ", " << iter.value  << " }" << std::endl;
/*
    if (iter.value == "push" || iter.value == "assert")
    {
      auto next = std::next(&iter, 1);
      //std::cout << "Node next: " << " | " << next->type << " | " << next->value << std::endl;

      this->manageComplex(next->type, next->value);
    }
    else
      this->manageSimple(iter.value);*/
  }
}

void  Vm::createOperand(eOperandType type, std::string const & value)
{
  std::cout << "Type: " << type << " | Value: " << value << std::endl;
}

/*
IOperand const *    Vm::createOperand( eOperandType type, std::string const & value ) const {
  //use array of pointers on member functions with enum values as index
  IOperand *(Vm::*handler[5])(std::string const &) = {
    &Vm::createInt8,
    &Vm::createInt16,
    &Vm::createInt32,
    &Vm::createFloat,
    &Vm::createDouble
  };

  for (int i = 0; i < 5; i++) {
    if ((eOperandType)i == type)
      return (this->*handler[i])(message);
  }
}
*/
/* Operands handling functions */
/* 
IOperand const * Vm::createInt8( std::string const & value ) const {

}

IOperand const * Vm::createInt16( std::string const & value ) const {

}

IOperand const * Vm::createInt32( std::string const & value ) const {

}

IOperand const * Vm::createFloat( std::string const & value ) const {

}

IOperand const * Vm::createDouble( std::string const & value ) const {

}*/

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