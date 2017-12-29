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

void  Lexer::getChunks(std::string str)
{
  // split line on whitespaces
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
    this->_chunks.push_back(chunk) ;
}

void  Lexer::tokenizeChunks(void)
{
  std::vector<std::string>::iterator chunkIter = this->_chunks.begin();
  std::vector<std::string>::iterator chunkEnd = this->_chunks.end();
  std::regex regexInstructions("push|pop|dump|assert|add|sub|mul|div|mod|print|exit");
  bool markAllAsComment = false;

  while (chunkIter != chunkEnd)
  {
    std::cout << "Chunk: " << *chunkIter << std::endl;

    // Tokenize every type of chunks but comments
    if (markAllAsComment == false)
    {
      bool unvalidInstruction = true;
  
      // Tokenize simple instructions
      if (std::regex_match(*chunkIter, regexInstructions) == true)
      {
        this->_tokens.push_back(*chunkIter);
        unvalidInstruction = false;
      }
      else
      {
        // Tokenize instructions before comments or operands and values
        for (size_t i = 0; i < (*chunkIter).length(); i++)
        {
          if ((*chunkIter)[i] == ';' && (*chunkIter)[i + 1] != ';')
          {
            // tag instructions before comment
            if (i > 0)
              this->_tokens.push_back((*chunkIter).substr(0, i));          
            
            // from here until last chunk (from ";" to "\n") all content is a comment
            markAllAsComment = true;
            unvalidInstruction = false;
            break;
          }
          else if ((*chunkIter)[i] == '(')
          {
            int j;
            int count;

            // tokenize operand before opening parenthesis
            this->_tokens.push_back((*chunkIter).substr(0, i));

            j = i;
            count = 0;
            while ((*chunkIter)[j] != '\0')
            {
              if ((*chunkIter)[j] == ')')
                break;
              count++;
              j++;
            }

            unvalidInstruction = false;
            // tokenize value contain between parenthesis
            this->_tokens.push_back((*chunkIter).substr(i + 1, count - 1));
          }
        }
      }

      // tokenize unknown instructions
      if (unvalidInstruction == true)
        this->_tokens.push_back(*chunkIter);
    }

    ++chunkIter;
  }
}

void  Lexer::analysis(void) {
  std::vector<std::string>::iterator iter = this->_buff.begin();
  std::vector<std::string>::iterator end = this->_buff.end();  

  while (iter != end)
  {
    this->_chunks.clear();
    this->getChunks(*iter);
    this->tokenizeChunks();
    ++iter;
  }

  this->displayTokensList(); //tool
}

/* Development tools */

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

void  Lexer::displayTokensList(void)
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

/* Non member function */

std::ostream & operator<<(std::ostream & o, Lexer const &obj )
{
  (void)obj;
  o << "operator overload" << std::endl;
  return o;
}