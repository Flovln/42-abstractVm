#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

int main(int ac, char **av)
{
  if (ac < 3)
  {
    if (ac == 2)
    {
      /* read from file */
      std::string  line;
      std::vector<std::string> buff;
      std::ifstream file(av[1]);

      if (file.is_open())
      {
        while (std::getline(file, line, '\n'))
        {
          std::cout << "Line: " << line << std::endl;
          buff.push_back(line);
        }
        file.close();

        std::cout << "--- Content ---" << std::endl;
        std::vector<std::string>::iterator iter = buff.begin();
        std::vector<std::string>::iterator end = buff.end();
        while (iter != end)
        {
          std::cout << (*iter) << std::endl;
          ++iter;
        }
        std::cout << "---------" << std::endl;
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