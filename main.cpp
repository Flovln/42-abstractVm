#include "Lexer.hpp"
#include <fstream>

int main(int ac, char **av)
{
  if (ac < 3)
  {
    std::string              line;
    std::ifstream            file(av[1]);
    std::vector<std::string> buff;
    Lexer                    lexer;

    if (ac == 2)
    {
      /* read from file */
      if (file.is_open())
      {
        while (std::getline(file, line, '\n'))
        {
          buff.push_back(line);
        }

        file.close();

        //lexer.readFromFile()
      }
    }
    else
    {
      /* read from stdin */

      //lexer.readFromStdin()
      while (1)
      {
        std::cin >> line;
        buff.push_back(line);
        
        if (line == "exit")
          break;
      }
    }

    lexer.displayVectorContent(buff);
  }
  else
    std::cout << "AbstractVm runs programs from a file and from the standard input." << std::endl;

  return (0);
}