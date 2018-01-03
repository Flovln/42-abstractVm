#include "./includes/Vm.hpp"

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
    Vm vm;

    try {
      if (ac == 2)
        vm.readFromFile(av[1]);
      else
        vm.readFromStdin();

      vm.run();
    }

    catch (Vm::ExecutionException & e) { std::cout << "Execution error: " << e.what() << std::endl; }
    catch (Vm::SyntaxException & e) { std::cout << "Syntax error: " << e.what() << std::endl; }
  }
  else
    usage(av[0]);

  return (0);
}