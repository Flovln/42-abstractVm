#include "Lexer.hpp"
#include <fstream>

int main(int ac, char **av)
{
  if (ac < 3)
  {
    if (ac == 2)
    {
      /* read from file */
      std::string              line;
      std::vector<std::string> buff;
      std::ifstream            file(av[1]);

      if (file.is_open())
      {
        while (std::getline(file, line, '\n'))
        {
          buff.push_back(line);
        }

        file.close();

        Lexer lexer;

        lexer.displayVectorContent(buff);
      }
    }
    else
    {
      /* read from stdin */
      std::string input;
    }
  }
  else
    std::cout << "AbstractVm runs programs from a file and from the standard input." << std::endl;

  return (0);
}