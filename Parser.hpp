#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>
#include <list>
#include <string>
#include <string.h>
#include <algorithm>
#include <iterator>

#ifndef PARSER_HPP
# define PARSER_HPP

class Parser {
  Parser(void);

  Parser(Parser const &obj);
  ~Parser(void);

  Parser &operator=(Parser const &rhs);

};

#endif