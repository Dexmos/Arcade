/*
** enums.hh for cpp_arcade in
**
** Made by julien1.benoit@epitech.eu
** Login   <julien1.benoit@epitech.net>
**
** Started on  ven. mars 11:12 2017 benoit_g
** Last update ven. mars 11:12 2017 benoit_g
*/

#ifndef CPP_ARCADE_ENUMS_HH
#define CPP_ARCADE_ENUMS_HH

#include <utility>
#include <vector>
#include <functional>
#include <cstdint>
#include <cstdarg>

#include "Vector2.hpp"
#include "Errors.hpp"

namespace arcade
{
  enum class Colors : uint32_t
  {
    BLACK = 0,
    WHITE,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    CYAN,
    MAGENTA
  };

  enum class Keys : uint32_t
  {
    GO_UP = 0,
    GO_DOWN,
    GO_LEFT,
    GO_RIGHT,
    SHOOT,
    GO_FAST,
    PREV_GRAPH_LIB,
    NEXT_GRAPH_LIB,
    PREV_GAME,
    NEXT_GAME,
    RESTART,
    BACK_MENU,
    EXIT,
    NONE
  };

  struct EnumClassHash
  {
    template<typename T>
    std::size_t operator()(T t) const
    {
      return static_cast<std::size_t>(t);
    }
  };
}

#endif //CPP_ARCADE_ENUMS_HH
