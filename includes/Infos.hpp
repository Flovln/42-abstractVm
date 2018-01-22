#include <iostream>

#ifndef INFOS_HPP
# define INFOS_HPP

enum eOperandType
{
  Int8,
  Int16,
  Int32,
  Float,
  Double
};

// Use for instructions vector - to replace by std::pair
struct Content {
  std::string   type;
  std::string   value;
};

#endif