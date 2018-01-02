#include "./includes/Vm.hpp"

void  Vm::readFromFile(char *file) {
  std::string   line;
  std::ifstream ifs(file);

  if (ifs.is_open())
  {
    while (std::getline(ifs, line, '\n'))
      this->_buff.push_back(line);

    ifs.close();
  }
  this->_source = 0;
}

void  Vm::readFromStdin(void) {
  std::string line;

  while (line != ";;")
  {
    std::cin >> line;
    this->_buff.push_back(line);
  }
  this->_source = 1;
}

void  Vm::analysis(void) {
  Lexer lexer;

  lexer.lexicalAnalysis(this->_buff);
}

void  Vm::execute(void) {
//  this->displayBufferContent();
}

int  Vm::getSource(void) {
  return this->_source;
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
    if ((eOperantType)i == type)
      return (this->*handler[i])(message);
  }
}*/

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
