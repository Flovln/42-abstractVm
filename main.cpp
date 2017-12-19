#include "Test.hpp"

int main(int ac, char **av)
{
  (void)ac;
  (void)av;
  std::string obj;

  Test person1("Florent"); // with parameter
  Test person2("Jose"); // with parameter
  Test person3; // no parameter = default constructor
  Test person4(person1); // constructor by copy

//  std::cout << person1; // operator overload
  obj = person2.toString();
  std::cout << obj;

  person1.createOperand((Test::eOperandType)4, "test");
  return (0);
}