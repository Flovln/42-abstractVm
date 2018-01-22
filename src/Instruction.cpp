#include "../includes/Instruction.hpp"
#include "../includes/Vm.hpp"

Instruction::Instruction(void) {}

Instruction::Instruction(Instruction const &obj) {
  *this = obj;
}

Instruction::~Instruction(void) {}

Instruction & Instruction::operator=(Instruction const &rhs) {
  if (this != &rhs) {
    this->_line = rhs.getLine();
    this->_errors = rhs.getErrors();
    this->_chunks = rhs.getChunks();
    this->_tokens = rhs.getTokens();
    this->_instructions = rhs.getInstructions();
    this->_markedAsComment = rhs.getMarkedAsComment();
    this->_markAsLexicalError = rhs.getMarkAsLexicalError();
    this->_markAsUnknownInstruction = rhs.getMarkedAsUnknownInstruction();
  }

  return (*this);
}

int                      Instruction::getLine(void) const {
  return this->_line;
}

std::vector<std::string> Instruction::getErrors(void) const {
  return this->_errors;
}

std::vector<std::string> Instruction::getChunks(void) const {
  return this->_chunks;
}

std::vector<Token>       Instruction::getTokens(void) const {
  return this->_tokens;
}

std::vector<Content>     Instruction::getInstructions(void) const {
  return this->_instructions;
}

bool                     Instruction::getMarkedAsComment(void) const {
  return this->_markedAsComment;
}

bool                     Instruction::getMarkAsLexicalError(void) const {
  return this->_markAsLexicalError;
}

bool                     Instruction::getMarkedAsUnknownInstruction(void) const {
  return this->_markAsUnknownInstruction;
}

void  Instruction::setLine(int nb) {
  this->_line = nb;
}

/*************** LEXER **************/

void  Instruction::createChunks(std::string str) {
  /* split line on whitespaces to only keep strings and chars */
  std::stringstream lineStream(str);
  std::string       chunk;

  while (lineStream >> chunk)
    this->_chunks.push_back(chunk) ;
}

void  Instruction::removeComments(void) {
  this->_markedAsComment = false;

  for (auto &iter: this->_chunks) {
    for (size_t i = 0; i < iter.length(); ++i) {
      if (iter[i] == ';') {
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

void  Instruction::tokenizeSimple(std::string chunk) {
  std::regex instructions("push|assert|pop|dump|add|sub|mul|div|mod|print|exit");

  if (std::regex_match(chunk, instructions) == true) {
    if (chunk != "push" && chunk != "assert")
      this->_markAsUnknownInstruction = true;
    this->_tokens.push_back({this->_line, Token::Instruction, "", chunk});
  }
  else if (this->_markAsUnknownInstruction == false)
    this->_tokens.push_back({this->_line, Token::UnknownInstruction, "", chunk});
}

void  Instruction::tokenizeComplex(std::string chunk) {
  for (size_t i = 0; i < chunk.length(); ++i) {
    if (chunk[i] == '(' && i > 0) {
      int   count;
      bool  closed;

      count = 0;
      closed = false;
      for (int j = i; chunk[j] != '\0'; j++) {
        if (chunk[j] == ')') {
          closed = true;
          break;
        }
        count++;
      }

      /* Get content before and between parenthesis */
      this->_tokens.push_back({this->_line, Token::Operand, chunk.substr(0, i), chunk.substr(i + 1, count - 1)});

      if (closed == false)
        this->_tokens.push_back({this->_line, Token::LexicalError, "", "Missing closing parenthesis"});

      if (i + count + 1 < chunk.length()) {
        this->_tokens.push_back({this->_line, Token::LexicalError, "", chunk.substr(i + count + 1, chunk.length())});
        this->_markAsLexicalError = true;
      }
  
      this->_markAsUnknownInstruction = true;
    }
  }
}

void  Instruction::tokenizer(void) {
  this->_markAsLexicalError = false;
  this->_markAsUnknownInstruction = false;

  for (auto &iter : this->_commentsRemoved) {
    if (this->_markAsUnknownInstruction == true)
      this->_tokens.push_back({this->_line, Token::LexicalError, "", iter});
    else if (this->_markAsLexicalError == false) {
      this->tokenizeComplex(iter);
      this->tokenizeSimple(iter);
    }
    else
      this->_tokens.push_back({this->_line, Token::LexicalError, "", iter});
  }
}

void  Instruction::lexer(std::vector<std::string> buff) {
  int lineNb;
  lineNb = 0;

  /* Go through file content line by line to remove comments and tonekize chunks */
  for (auto &iter : buff) {
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

/*************** PARSER **************/

void                  Instruction::checkInstructions(Token instruction, Token *next, int line) {
  if (next->type == Token::Operand)
    this->_instructions.push_back({"Instruction", instruction.value});
  else
    this->_errors.push_back("Line: " + std::to_string(line + 1) + ": error with instruction " + instruction.value);
}

void                  Instruction::checkOperands(Token operand, int line) {
  std::regex operands("int8|int16|int32|float|double");

  if (std::regex_match(operand.valueType, operands) == true) {
    if (operand.value == "")
      this->_errors.push_back("Line: " + std::to_string(operand.line) + ": operand missing value.");
    else {
      bool error = false;
      size_t countNeg = std::count(operand.value.begin(), operand.value.end(), '-');
      size_t countComa = std::count(operand.value.begin(), operand.value.end(), '.');

      if ((operand.value.find("-") != std::string::npos && operand.value.find("-") != 0) || countNeg > 1)
        error = true;

      if (operand.valueType == "float" || operand.valueType == "double") {
        if (operand.value.find(".") == std::string::npos || countComa > 1)
          error = true;
        else if (operand.value.find(".") != std::string::npos && operand.value.find(".") == 0)
          error = true;
      }
      else {
        if (operand.value.find(".") != std::string::npos)
          error = true;
      }

      for (size_t i = 0; i < operand.value.length(); ++i) {
        char c = operand.value[i];

        if (!isdigit(c) && c != '.' && c != '-')
          error = true;
      }

      if (error)
        this->_errors.push_back("Line: " + std::to_string(operand.line + 1) + ": unvalid operand value.");
      else
        this->_instructions.push_back({operand.valueType, operand.value});      
    }
  }
  else
    this->_errors.push_back("Line: " + std::to_string(line + 1) + ": unvalid operand: " + operand.valueType);
}

std::vector<Content>  Instruction::parser(void) {
  bool exit = false;

  for (auto &iter : this->_tokens) {
    Token::Type type = iter.type;

    if (iter.value == "exit") {
      exit = true;
      break;
    }

    switch(type) {
      case Token::Instruction:
        if (iter.value == "push" || iter.value == "assert") {
          if (&iter != &this->_tokens.back()) {
            auto next = std::next(&iter, 1);
            this->checkInstructions(iter, next, iter.line);
          }
          else
            this->_errors.push_back("Line: " + std::to_string(iter.line + 1) + ": no operand passed after " + iter.value);
        }
        else
          this->_instructions.push_back({"Instruction", iter.value});
        break;
      case Token::Operand:
        this->checkOperands(iter, iter.line);
        break;
      case Token::LexicalError:
        this->_errors.push_back("Line: " + std::to_string(iter.line + 1) + ": lexical error: " + iter.value);
        break;
      case Token::UnknownInstruction:
        this->_errors.push_back("Line: " + std::to_string(iter.line + 1) + ": unknown instruction: " + iter.value);
        break;

      default:
        break;
    }
  }

  if (!exit)
    this->_errors.push_back("Program ended with no 'exit' command");

  if (!this->_errors.empty())
    throw Vm::SyntaxException(this->_errors);

  return this->_instructions;  
}

/* Non member function */
std::ostream & operator<<(std::ostream & o, Instruction const &obj ) {
  (void)obj;
  o << "operator overload" << std::endl;
  return o;
}