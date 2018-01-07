#include "./includes/Instruction.hpp"
#include "./includes/Vm.hpp"

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

void  Instruction::setLine(int nb)
{
  this->_line = nb;
}

void  Instruction::createChunks(std::string str)
{
  /* split line on whitespaces to only keep strings and chars */
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
    this->_chunks.push_back(chunk) ;
}

void  Instruction::lexer(std::vector<std::string> buff, int source) {
  std::string lastElement =  buff.back();

  switch(source)
  {
    case(0):
      if (lastElement != "exit")
        this->_errors.push_back("No instruction ending the program found.");
      break;
    case(1):
      if (lastElement != ";;")
        this->_errors.push_back("No instruction ending the program found.");
      break;

    default:
      break;
  }

  /* Remove last element from vector aka exit command or ";;" */
  buff.pop_back();

  int lineNb;
  lineNb = 0;

  /* Go through file content line by line to remove comments and tonekize chunks */
  for (auto &iter : buff)
  {
    this->setLine(lineNb);
    lineNb++;

    if (!this->_chunks.empty())
      this->_chunks.clear();
    
    this->createChunks(iter);
    
    if (!this->_commentsRemoved.empty())
      this->_commentsRemoved.clear();
    
    this->removeComments();
    this->tokenizer();
  }
 
}

void  Instruction::removeComments(void)
{
  this->_markedAsComment = false;

  for (auto &iter: this->_chunks)
  {
    for (size_t i = 0; i < iter.length(); ++i)
    {
      if (iter[i] == ';')
      {
        if (i > 0)
          this->_commentsRemoved.push_back(iter.substr(0, i));
        this->_markedAsComment = true;
        break;
      }
    }

    if (this->_markedAsComment != true)
      this->_commentsRemoved.push_back(iter);
  }
}

void  Instruction::tokenizeSimple(std::string chunk)
{
  std::regex instructions("push|assert|pop|dump|add|sub|mul|div|mod|print");

  if (std::regex_match(chunk, instructions) == true)
  {
    if (chunk != "push" && chunk != "assert")
      this->_markAsUnknownInstruction = true;
    this->_tokens.push_back({this->_line, Token::Instruction, "", chunk});
  }
  else if (this->_markAsUnknownInstruction == false)
    this->_tokens.push_back({this->_line, Token::UnknownInstruction, "", chunk});
    //this->_markAsUnknownInstruction = true; ??? Use for multi instructions after parenthesis or with no operand or after unknown commands ex: (412) pop mul ... || asds mul pop ...
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
      this->_tokens.push_back({this->_line, Token::Operand, chunk.substr(0, i), chunk.substr(i + 1, count - 1)});

      if (closed == false)
        this->_tokens.push_back({this->_line, Token::LexicalError, "", "Missing closing parenthesis"});

      if (i + count + 1 < chunk.length())
      {
        this->_tokens.push_back({this->_line, Token::LexicalError, "", chunk.substr(i + count + 1, chunk.length())});
        this->_markAsLexicalError = true;
      }
  
      this->_markAsUnknownInstruction = true;
    }
  }
}

void  Instruction::tokenizer(void)
{
  this->_markAsLexicalError = false;
  this->_markAsUnknownInstruction = false;

  for (auto &iter : this->_commentsRemoved)
  {
    if (this->_markAsUnknownInstruction == true)
      this->_tokens.push_back({this->_line, Token::LexicalError, "", iter});
    else if (this->_markAsLexicalError == false)
    {
      this->tokenizeComplex(iter);
      this->tokenizeSimple(iter);
    }
    else
      this->_tokens.push_back({this->_line, Token::LexicalError, "", iter});
  }
}

void                  Instruction::checkInstructions(Token instruction, Token *next, int line)
{
  if (next->type == Token::Operand)
    this->_instructions.push_back({"Instruction", instruction.value});
  else
    this->_errors.push_back("Line: " + std::to_string(line) + ": error with instruction " + instruction.value);
}

void                  Instruction::checkOperands(Token operand, int line)
{
  std::regex operands("int8|int16|int32|float|double");

  if (std::regex_match(operand.valueType, operands) == true)
  {
    if (operand.value == "")
      this->_errors.push_back("Line: " + std::to_string(operand.line) + ": operand missing value.");
    else
      this->_instructions.push_back({operand.valueType, operand.value});      
  }
  else
    this->_errors.push_back("Line: " + std::to_string(line) + ": unvalid operand: " + operand.valueType);
}

std::vector<Content>  Instruction::parser(void)
{
  for (auto &iter : this->_tokens)
  {
    Token::Type type = iter.type;

    switch(type)
    {
      case Token::Instruction:
        if (iter.value == "push" || iter.value == "assert")
        {
          if (&iter != &this->_tokens.back())
          {
            auto next = std::next(&iter, 1);
            this->checkInstructions(iter, next, iter.line);
          }
          else
            this->_errors.push_back("Line: " + std::to_string(iter.line) + ": no operand passed after " + iter.value);
        }
        else
          this->_instructions.push_back({"Instruction", iter.value});
        break;
      case Token::Operand:
        this->checkOperands(iter, iter.line);
        break;
      case Token::LexicalError:
        this->_errors.push_back("Line: " + std::to_string(iter.line) + ": lexical error: " + iter.value);
        break;
      case Token::UnknownInstruction:
        this->_errors.push_back("Line: " + std::to_string(iter.line) + ": unknown instruction: " + iter.value);
        break;

      default:
        break;
    }
  }
  if (!this->_errors.empty())
    throw Vm::SyntaxException(this->_errors);

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
    std::cout << "Token: " << "{ " << iter[0].type << ", " << iter[0].valueType << ", " << iter[0].value << " }" << std::endl;
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