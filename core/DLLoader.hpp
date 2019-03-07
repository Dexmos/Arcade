/*
** DLLoader.hpp for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  mar. mars 15:51 2017 marye_s
** Last update mar. mars 15:51 2017 marye_s
*/

#ifndef CPP_ARCADE_DLLOADER_HPP
#define CPP_ARCADE_DLLOADER_HPP
#include <iostream>
#include <dlfcn.h>
#include "../Interfaces/Errors.hpp"

template <typename T>
class DLLoader
{
  std::string           name;
  void                  *handler;
  T                     *(*ptr)();

 public:
  DLLoader(std::string _name) : name(_name)
  {
    if (!(this->handler = dlopen(this->name.c_str(), RTLD_LAZY)))
      {
	std::cerr << dlerror() << std::endl;
	throw arcade::Errors("Could not open the given library\n");
      }
    else if (!(this->ptr = (T *(*)()) dlsym(this->handler, "entry_point")))
      {
	std::cerr << dlerror() << std::endl;
	throw arcade::Errors("Could not find the symbol used to create an instance of the library\n");
      }
  }

  ~DLLoader()
  {
    dlclose(this->handler);
  }

  T *getInstance()
  {
    return (this->ptr());
  }
};

#endif //CPP_ARCADE_DLLOADER_HPP
