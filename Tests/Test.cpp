#include "Test.hpp"

Test::Test(void) {
  std::cout << "Hi i am default constructor" << std::endl;
}

Test::Test(std::string name) : _name(name) {
  std::cout << "Constructor says your name is " << this->_name << std::endl;
}

Test::Test(Test const & rhs) {
  *this = rhs;
  std::cout << "Hi i am copy constructor" << std::endl;
}

Test::~Test(void) {
  std::cout << "Destructor called" << std::endl;
}

std::string  Test::getName() const {
  return this->_name;
}

std::string const & Test::toString() const {
  std::ostringstream stream;
  std::string *str;
  std::string tmp;

  stream << *this;
  tmp = stream.str();
  str = &tmp;

  return *str;
}

void  Test::createOperand( eOperandType type, std::string const & value ) /*const*/{
  void (Test::*handler[5])(std::string const &) = {
    &Test::createInt8,
    &Test::createInt16,
    &Test::createInt32,
    &Test::createFloat,
    &Test::createDouble
  };

  for (int i = 0; i < 5; i++)
  {
    if ((eOperandType)i == type)
      (this->*handler[i])(value);
  }
}

void Test::createInt8( std::string const & value ) /*const*/{
  std::cout << "create Int8 value: " << value << std::endl;
}

void Test::createInt16( std::string const & value ) /*const*/{
  std::cout << "create Int1 value: " << value << std::endl;
}

void Test::createInt32( std::string const & value ) /*const*/{
  std::cout << "create Int3 value: " << value << std::endl;
}

void Test::createFloat( std::string const & value ) /*const*/{
  std::cout << "create Float value: " << value << std::endl;
}

void Test::createDouble( std::string const & value ) /*const*/{
  std::cout << "create Double value: " << value << std::endl;
}

/* Non member */

std::ostream & operator<<(std::ostream & o, Test const & obj) {
  o << "Name : " << obj.getName() << std::endl;
  return o;
}