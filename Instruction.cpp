#include "./includes/Instruction.hpp"

Instruction::Instruction(void) {}

Instruction::Instruction(Instruction const &obj) {
  *this = obj;
}

Instruction::~Instruction(void) {}

Instruction & Instruction::operator=(Instruction const &rhs) {
  if (this != &rhs) {
    //this->name = rhs.name;
    //...
  }

  return (*this);
}

void  Instruction::createChunks(std::string str)
{
  /* split line on whitespaces to only keep strings and chars */
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
    this->_chunks.push_back(chunk) ;
}

void  Instruction::lexicalAnalysis(std::vector<std::string> buff, int source) {
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

  /* Remove last element from vector aka exit command or ";;" */
  buff.pop_back();

  std::vector<std::string>::iterator iter = buff.begin();
  std::vector<std::string>::iterator end = buff.end();  

  /* Go through file content line by line to remove comments and tonekize chunks */
  while (iter != end)
  {
    if (!this->_chunks.empty())
      this->_chunks.clear();
    this->createChunks(*iter);
    if (!this->_commentsRemoved.empty())
      this->_commentsRemoved.clear();
    this->removeComments();
    this->tokenizer();
    ++iter;
  }
 
}

void  Instruction::removeComments(void)
{
  std::vector<std::string>::iterator iter = this->_chunks.begin();
  std::vector<std::string>::iterator end = this->_chunks.end();

  this->_markedAsComment = false;

  while (iter != end)
  {
    for (size_t i = 0; i < (*iter).length(); ++i)
    {
      if ((*iter)[i] == ';')
      {
        if (i > 0)
          this->_commentsRemoved.push_back((*iter).substr(0, i));
        this->_markedAsComment = true;
        break;
      }
    }

    if (this->_markedAsComment != true)
      this->_commentsRemoved.push_back(*iter);

    ++iter;
  }
}

void  Instruction::tokenizeSimple(std::string chunk)
{
  std::regex simpleInstructions("pop|dump|add|sub|mul|div|mod|print");
  std::regex complexInstructions("push|assert");

  if (std::regex_match(chunk, simpleInstructions) == true)
  {
    this->_markAsUnknownInstruction = true;
    this->_tokens.push_back({INSTRUCTION, chunk});
  }
  else if (std::regex_match(chunk, complexInstructions) == true)
    this->_tokens.push_back({INSTRUCTION, chunk});
  else if (this->_markAsUnknownInstruction == false)
  {
    this->_markAsUnknownInstruction = true;
    this->_tokens.push_back({UNKNOWN_INSTRUCTION, chunk});
  }
}

void  Instruction::tokenizeComplex(std::string chunk)
{
  for (size_t i = 0; i < chunk.length(); ++i)
  {
    if (chunk[i] == '(' && i > 0)
    {
      int   count;
      bool  closed;

      count = 0;
      closed = false;
      for (int j = i; chunk[j] != '\0'; j++)
      {
        if (chunk[j] == ')')
        {
          closed = true;
          break;
        }
        count++;
      }

      /* Get content before and between parenthesis */
      this->_tokens.push_back({chunk.substr(0, i), chunk.substr(i + 1, count - 1)});

      if (closed == false)
        this->_tokens.push_back({LEXICAL_ERROR, "Missing closing parenthesis"});

      if (i + count + 1 < chunk.length())
      {
        this->_tokens.push_back({LEXICAL_ERROR, chunk.substr(i + count + 1, chunk.length())});
        this->_markAsLexicalError = true;
      }
  
      this->_markAsUnknownInstruction = true;
    }
  }
}

void  Instruction::tokenizer(void)
{
  std::vector<std::string>::iterator iter = this->_commentsRemoved.begin();
  std::vector<std::string>::iterator end = this->_commentsRemoved.end();
  this->_markAsLexicalError = false;
  this->_markAsUnknownInstruction = false;

  while (iter != end)
  {
    if (this->_markAsUnknownInstruction == true)
      this->_tokens.push_back({LEXICAL_ERROR, *iter});
    else if (this->_markAsLexicalError == false)
    {
      this->tokenizeComplex(*iter);
      this->tokenizeSimple(*iter);
    }
    else
      this->_tokens.push_back({LEXICAL_ERROR, *iter});

    ++iter;
  }
}

std::list<Token>  Instruction::parseTokens(void)
{
  this->displayTokensList();
  
  return this->_instructions;
}

/* Development tools */

void  Instruction::displayVectorContent(std::vector<std::string> buff) {
  std::cout << "--- Vector content in Instruction ---" << std::endl;

  std::vector<std::string>::iterator iter = buff.begin();
  std::vector<std::string>::iterator end = buff.end();

  while (iter != end)
  {
    std::cout << (*iter) << std::endl;
    ++iter;
  }

  std::cout << "---------" << std::endl;
}

void  Instruction::displayTokensListWithoutComments(void)
{
  std::vector<std::string>::iterator iter = this->_commentsRemoved.begin();
  std::vector<std::string>::iterator end = this->_commentsRemoved.end();

  std::cout << "--- Tokens list without comments ---" << std::endl;
  while (iter != end)
  {
    std::cout << "Token: " << *iter << std::endl;
    ++iter;
  }
  std::cout << "--- --- ---" << std::endl;
}

void  Instruction::displayTokensList(void)
{
  std::vector<Token>::iterator iter = this->_tokens.begin();
  std::vector<Token>::iterator end = this->_tokens.end();

  std::cout << "--- Tokens list Instruction ---" << std::endl;
  while (iter != end)
  {
    std::cout << "Token: " << "{ " << iter[0].type << ", " << iter[0].value << " }" << std::endl;
    ++iter;
  }
  std::cout << "--- --- ---" << std::endl;
}

/* Non member function */

std::ostream & operator<<(std::ostream & o, Instruction const &obj )
{
  (void)obj;
  o << "operator overload" << std::endl;
  return o;
}

/*
void  Instruction::tokenizerOld(void)
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
      this->_tokens.push_back({LEXICAL_ERROR, *chunkIter});

    // Tokenize every type of chunks but comments
    if (markAllAsComment == false && markAllAsError == false)
    {
  
      // Tokenize simple instructions
      if (std::regex_match(*chunkIter, regexInstructions) == true && markAfterParenthesis == false)
      {
        this->_tokens.push_back({INSTRUCTION, *chunkIter});
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
              this->_tokens.push_back({INSTRUCTION, (*chunkIter).substr(0, i)});
            else if (i > 0 && (*chunkIter)[i - 1] != ')' && markAfterParenthesis == true)
              this->_tokens.push_back({LEXICAL_ERROR, (*chunkIter).substr(0, i)});

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
            this->_tokens.push_back({(*chunkIter).substr(0, i), (*chunkIter).substr(i + 1, count - 1)});

            if (i + count + 1 < (*chunkIter).length())
            {
              if ((*chunkIter)[i + count] == ')' && (*chunkIter)[i + count + 1] != ';')
              {
                markAllAsError = true;
                this->_tokens.push_back({LEXICAL_ERROR, (*chunkIter).substr(i + count + 1, (*chunkIter).length())});
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
        this->_tokens.push_back({UNKNOWN_INSTRUCTION, *chunkIter});
//        this->tokens.push_back(token("UnknownInstruction", *chunkIter));
    }

    ++chunkIter;
  }
}*/