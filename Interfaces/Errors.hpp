/*
** Errors.hpp for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  dim. avr. 14:48 2017 marye_s
** Last update dim. avr. 14:48 2017 marye_s
*/
#ifndef CPP_ARCADE_ERRORS_HPP
#define CPP_ARCADE_ERRORS_HPP

#include <string>
#include <exception>

namespace arcade
{
  class Errors : public std::exception
  {
    std::string		err_message;

   public:
    Errors(std::string _err_message) : err_message(_err_message) {}

    virtual ~Errors() throw() {}

    const char *what() const throw()
    {
      return(this->err_message.c_str());
    }
  };
}

#endif //CPP_ARCADE_ERRORS_HPP
