#include "Lexer.hpp"

int main(int ac, char **av)
{
  if (ac < 3)
  {
    Lexer lexer;

    if (ac == 2)
      lexer.readFromFile(av[1]);
    else
    {
      std::string line;
  
      while (1)
      {
        std::cin >> line;
        lexer.readFromStdin(line);
        
        if (line == ";;")
          break;
      }
    }

    lexer.displayVectorContent();
    // lexical analysis | convert vector to list or deque or stack
    lexer.analysis();
    // parse and validate all elements from lexical data structure
    // call factory method
  }
  else
    std::cout << "AbstractVm runs programs from a file and from the standard input." << std::endl;

  return (0);
}