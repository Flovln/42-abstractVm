
#ifndef TOKEN_HPP
# define TOKEN_HPP

struct Token {
  
  enum Type {
    Instruction,
    Operand,
    /* Errors */
    LexicalError,
    UnknownInstruction
  };

  Type        type;
  std::string valueType;
  std::string value;
};

#endif