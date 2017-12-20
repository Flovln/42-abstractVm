#include "Lexer.hpp"

int main(int ac, char **av)
{
  if (ac < 3)
  {
    std::string line;
    Lexer       lexer;

    if (ac == 2)
      lexer.readFromFile(av[1]);
    else
    {
      while (1)
      {
        std::cin >> line;
        lexer.readFromStdin(line);
        
        if (line == ";;")
          break;
      }
    }

    lexer.displayVectorContent();
    // call parser
    // call factory method
  }
  else
    std::cout << "AbstractVm runs programs from a file and from the standard input." << std::endl;

  return (0);
}