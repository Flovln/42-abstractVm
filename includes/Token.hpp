#include <iostream>

#ifndef TOKEN_HPP
# define TOKEN_HPP

enum eOperandType
{
  Int8,
  Int16,
  Int32,
  Float,
  Double
};

// replace by std::pair
struct Content {
  std::string   type;
  std::string   value;
};

#endif