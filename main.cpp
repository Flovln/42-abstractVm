#include <sstream>
#include "Test.hpp"

int main(int ac, char **av)
{
  (void)ac;
  (void)av;
  Test person1("Florent"); // with parameter
  Test person2("Jose"); // with parameter
  Test person3; // no parameter = default constructor
  Test person4(person1); // constructor by copy

  std::cout << person1; // operator overload

  return (0);
}