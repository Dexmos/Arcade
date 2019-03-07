#include <iostream>
#include "CoreProgram.hh"

int main(int ac, char **av)
{

if (ac != 2)
  {
    std::cerr << "Usage : ./arcade [graphic_library]" << std::endl;
    return (0);
  }

  std::string	to_load = av[1];
  arcade::CoreProgram *coreProgram = new arcade::CoreProgram(to_load);

  coreProgram->GeneralLoop(to_load);
  return 0;
}