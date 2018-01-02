#include "./includes/Lexer.hpp"

void  usage(char *execName)
{
  std::cout << "Usage: " << execName << " [file]" << std::endl;
  std::cout << "or" << std::endl;
  std::cout << "Usage: " << execName << std::endl;
}

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
  
      while (line != ";;")
      {
        std::cin >> line;
        lexer.readFromStdin(line);
      }
    }

    lexer.analysis();
  }
  else
    usage(av[0]);

  return (0);
}