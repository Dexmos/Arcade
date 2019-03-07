/*
** Block.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#ifndef CPP_ARCADE_BLOCK_HH
#define CPP_ARCADE_BLOCK_HH

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include "../game/AGames.hh"

namespace arcade
{
  namespace games
  {
    class Block
    {
      std::vector<Vector2<float>> _coord;

     public:
      Block();
      ~Block();

      void setPos();
      void isDead();
      std::vector<Vector2<float>> &getPos();
    };
  }
}

#endif //CPP_ARCADE_BLOCK_HH
