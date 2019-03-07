/*
** Apple.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:49 2017 florian
** Last update mer. avr. 19:49 2017 florian
*/

#ifndef CPP_ARCADE_APPLE_HH
#define CPP_ARCADE_APPLE_HH

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include "../game/AGames.hh"

namespace arcade
{
  namespace games
  {
    class Apple
    {
      Vector2<>			pos;
      std::vector<Vector2<>> 	&_coord;

     public:
      Apple(std::vector<Vector2<>> &coord);
      ~Apple();

      Vector2<>		getPos() const ;
      void		getRandPos();

     private:
      void		setPos(Vector2<> pos);
    };
  }
}

#endif //CPP_ARCADE_APPLE_HH
