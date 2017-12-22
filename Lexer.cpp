#include "Lexer.hpp"

Lexer::Lexer(void) {}

Lexer::Lexer(Lexer const &obj) {
  *this = obj;
}

Lexer::~Lexer(void) {}

Lexer & Lexer::operator=(Lexer const &rhs) {
  if (this != &rhs) {
    //this->name = rhs.name;
    //...
  }

  return (*this);
}

void  Lexer::readFromFile(char *file) {
  std::string   line;
  std::ifstream ifs(file);

  if (ifs.is_open())
  {
    while (std::getline(ifs, line, '\n'))
      this->_buff.push_back(line);

    ifs.close();
  }
}

void  Lexer::readFromStdin(std::string line) {
  this->_buff.push_back(line);
}

//http://www.cplusplus.com/reference/map/multimap/insert/
//http://www.cse.chalmers.se/edu/year/2015/course/DAT150/lectures/proglang-04.html

void  Lexer::analysis(void) {
  std::cout << "Analysis " << std::endl;
  std::vector<std::string>::iterator iter = this->_buff.begin();
  std::vector<std::string>::iterator end = this->_buff.end();

  while (iter != end)
  {
    std::cout << (*iter) << std::endl;
    ++iter;
  }

  // split the bare characters list into tokens
  // recognizing those tokens (identifying keywords, parenthesis) (regex)
  // verifying a general grammar structure
}

void  Lexer::displayVectorContent(void) {
  std::cout << "--- Vector content ---" << std::endl;

  std::vector<std::string>::iterator iter = this->_buff.begin();
  std::vector<std::string>::iterator end = this->_buff.end();

  while (iter != end)
  {
    std::cout << (*iter) << std::endl;
    ++iter;
  }

  std::cout << "---------" << std::endl;
}

/* Non member function */

std::ostream & operator<<(std::ostream & o, Lexer const &obj )
{
  (void)obj;
  o << "operator overload" << std::endl;
  return o;
}