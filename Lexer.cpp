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

bool  Lexer::checkIfComment(std::string str)
{
  if (str[0] == ';' && str[1] != ';')
    return true;
  return false;
}

void  Lexer::getChunks(std::string str)
{
  // split line on whitespaces
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
  {
    this->_chunks.push_back(chunk) ;
  }
}

void  Lexer::tokenizeChunks(void)
{
  std::vector<std::string>::iterator iter = this->_chunks.begin();
  std::vector<std::string>::iterator end = this->_chunks.end();
  std::string delimiters[3] = {";", "(", ")"};
  std::string token;

  while (iter != end)
  {
    std::cout << "Chunk: " << *iter << std::endl;
    for (size_t i = 0; i < (*iter).length(); i++)
    {
      // save tokens + label them
      
    }
    ++iter;
  }
  return;
}

void  Lexer::analysis(void) {
  std::cout << "--- Analysis ----" << std::endl;
  std::vector<std::string>::iterator iter = this->_buff.begin();
  std::vector<std::string>::iterator end = this->_buff.end();  
//  std::list<std::tuple<std::string, int> > tokens;

  while (iter != end)
  {
    std::cout << "COMMAND: " << (*iter) << std::endl;
    std::cout << "------" << std::endl;
    bool              isComment;

    isComment = false;
    this->_chunks.clear();
    this->getChunks(*iter);
    this->tokenizeChunks();
    std::cout << "------" << std::endl;

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