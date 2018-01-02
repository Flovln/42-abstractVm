#include "./includes/Lexer.hpp"

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

std::vector<Token>  Lexer::lexicalAnalysis(std::vector<std::string> buff, int source) {
  std::string lastElement =  buff.back();

  if (source == 0)
  {
    if (lastElement != "exit")
      //throw exception
      std::cout << "Error" << std::endl;
  }
  else if (source == 1)
  {
    if (lastElement != ";;")
      //throw exception
      std::cout << "Error" << std::endl;
  }

  std::vector<std::string>::iterator iter = buff.begin();
  std::vector<std::string>::iterator end = buff.end();  

  while (iter != end)
  {
    this->_chunks.clear();
    this->getChunks(*iter);
    this->tokenizeChunks();
    ++iter;
  }

//  this->displayTokensList(); //tool

  return this->tokens;
}

void  Lexer::getChunks(std::string str)
{
  // split line on whitespaces
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
    this->_chunks.push_back(chunk) ;
}
//tokenize logic
/*
  1 - Get simple instruction if possible using regex
  2 - Get complex instruction (= operands + values + comments)
    Comments: (unique separateloop)
      1- If line starts with ";" until the end = comment = escape everything after
      2- If a ";" is encountered anywhere in the string, extract content before and escape everyhting after
    Parenthesis: (unique separate loop)
      1- If a "(" is encountered, extract content before
      2- From the "(" extract everything inside until the closing ")"
      3- If next char after ")" is ";" escape it as comment
      4- Everything after closing ")" minus comments is a lexical error
*/

void  Lexer::tokenizeChunks(void)
{
  std::vector<std::string>::iterator chunkIter = this->_chunks.begin();
  std::vector<std::string>::iterator chunkEnd = this->_chunks.end();
  std::regex regexInstructions("push|pop|dump|assert|add|sub|mul|div|mod|print|exit");
  bool markAllAsComment = false;
  bool markAllAsError = false;
  bool markAfterParenthesis = false;

  while (chunkIter != chunkEnd)
  {
    bool unvalidInstruction = true;

    // Tokenize as error all content contained after closed parenthesis minus comments
    if (markAllAsError == true)
      this->tokens.push_back({LEXICAL_ERROR, *chunkIter});

    // Tokenize every type of chunks but comments
    if (markAllAsComment == false && markAllAsError == false)
    {
  
      // Tokenize simple instructions
      if (std::regex_match(*chunkIter, regexInstructions) == true && markAfterParenthesis == false)
      {
        this->tokens.push_back({INSTRUCTION, *chunkIter});
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
            if (i > 0 && (*chunkIter)[i - 1] != ')' && markAfterParenthesis == false)
              this->tokens.push_back({INSTRUCTION, (*chunkIter).substr(0, i)});
            else if (i > 0 && (*chunkIter)[i - 1] != ')' && markAfterParenthesis == true)
              this->tokens.push_back({LEXICAL_ERROR, (*chunkIter).substr(0, i)});

            // from here until last chunk (from ";" to "\n") all content is a comment
            markAllAsComment = true;
            unvalidInstruction = false;
            break;
          }
          else if ((*chunkIter)[i] == '(' && markAllAsError == false)
          {
            int j;
            int count;

            j = i;
            count = 0;
            while ((*chunkIter)[j] != '\0')
            {
              if ((*chunkIter)[j] == ')')
                break;
              count++;
              j++;
            }

            // tokenize operand + value
            this->tokens.push_back({(*chunkIter).substr(0, i), (*chunkIter).substr(i + 1, count - 1)});

            if (i + count + 1 < (*chunkIter).length())
            {
              if ((*chunkIter)[i + count] == ')' && (*chunkIter)[i + count + 1] != ';')
              {
                markAllAsError = true;
                this->tokens.push_back({LEXICAL_ERROR, (*chunkIter).substr(i + count + 1, (*chunkIter).length())});
              }
              else if ((*chunkIter)[i + count] == ')' && (*chunkIter)[i + count + 1] == ';')
                markAllAsComment = true;
            }

            markAfterParenthesis = true;
            unvalidInstruction = false;
          }
        }
      }

      // tokenize unknown instructions = errors
      if (unvalidInstruction == true)
        this->tokens.push_back({UNKNOWN_INSTRUCTION, *chunkIter});
//        this->tokens.push_back(token("UnknownInstruction", *chunkIter));
    }

    ++chunkIter;
  }
}

/* Development tools */

void  Lexer::displayVectorContent(std::vector<std::string> buff) {
  std::cout << "--- Vector content in Lexer ---" << std::endl;

  std::vector<std::string>::iterator iter = buff.begin();
  std::vector<std::string>::iterator end = buff.end();

  while (iter != end)
  {
    std::cout << (*iter) << std::endl;
    ++iter;
  }

  std::cout << "---------" << std::endl;
}

void  Lexer::displayTokensList(void)
{
  std::vector<Token>::iterator iter = this->tokens.begin();
  std::vector<Token>::iterator end = this->tokens.end();

  std::cout << "--- Tokens list Lexer ---" << std::endl;
  while (iter != end)
  {
    std::cout << "Token: " << "{ " << iter[0].type << ", " << iter[0].value << " }" << std::endl;
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
