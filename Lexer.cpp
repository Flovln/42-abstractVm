#include "Lexer.hpp"

Lexer::Lexer(void) {
//  this->_instructionType = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};

  this->_instructionType.push_back("push");
  this->_instructionType.push_back("pop");
  this->_instructionType.push_back("dump");
  this->_instructionType.push_back("assert");
  this->_instructionType.push_back("add");
  this->_instructionType.push_back("sub");
  this->_instructionType.push_back("mul");
  this->_instructionType.push_back("div");
  this->_instructionType.push_back("mod");
  this->_instructionType.push_back("print");
  this->_instructionType.push_back("exit");
}

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

void  Lexer::printTokens(void)
{
  std::vector<std::string>::iterator iter = this->_tokens.begin();
  std::vector<std::string>::iterator end = this->_tokens.end();

  std::cout << "--- Tokens list ---" << std::endl;
  while (iter != end)
  {
    std::cout << "Token: " << *iter << std::endl;
    ++iter;
  }
  std::cout << "--- --- ---" << std::endl;
}

void  Lexer::tokenizeChunks(void)
{
  std::vector<std::string>::iterator chunkIter = this->_chunks.begin();
  std::vector<std::string>::iterator chunkEnd = this->_chunks.end();
  std::vector<std::string>::iterator iterInstruc = this->_instructionType.begin();
  std::vector<std::string>::iterator endInstruc = this->_instructionType.end();

  std::string delimiters[3] = {";", "(", ")"};
  std::string token;

  while (chunkIter != chunkEnd)
  {
    std::cout << "Chunk: " << *chunkIter << std::endl;

    // Tag simple chunks as tokens if possible
    while (iterInstruc != endInstruc)
    {
      if (*chunkIter == *iterInstruc)
        this->_tokens.push_back(*chunkIter);
      ++iterInstruc;
    }

    // Tag more complex chunks as comments + parenthesis
    for (size_t i = 0; i < (*chunkIter).length(); i++)
    {
      //std::cout << (*iter)[i] << std::endl;
      if ((*iter)[i] == ";" && (*iter)[i] != ";")
      {
        if (i > 1)
          //get and save as token all content before ";"
        else
        {
          //from here until last chunk all content is a comment
          
        }
        break;
      }
    }
    ++chunkIter;
  }
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
  this->printTokens(); //tool
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