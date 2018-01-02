
#ifndef TOKEN_HPP
# define TOKEN_HPP

struct Token {
  
  enum Type {
    Instruction, // push | pop | dump | assert | add | sub | mul | div | mod | print | exit
    /* Operands */
    Int8,
    Int16, 
    Int32,
    Float,
    Double,
    /* Errors */
    LexicalError,
    UnknownInstruction
  };

  std::string type;
  std::string value;
};

#endif