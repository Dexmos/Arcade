/*
** Shoots.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#ifndef CPP_ARCADE_SHOOTS_HH
#define CPP_ARCADE_SHOOTS_HH

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include "../game/AGames.hh"
#include "../../Interfaces/Vector2.hpp"

namespace arcade
{
  namespace games
  {
    class Shoot
    {
      float _speed;
      arcade::Keys _where;
      Vector2<float> pos;

     public:
      int _range;

      Shoot(int range, float speed, const Vector2<float> &coord, arcade::Keys where);
      ~Shoot();

      void updateshoot();
      void drawshoot(graphics::IGraphic *graphic, const Colors &color);

      const Vector2<float> &getPos() const;
    };
  }
}
#endif //CPP_ARCADE_SHOOTS_HH
