/*
** Enemy.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#ifndef CPP_ARCADE_ENEMY_HH
#define CPP_ARCADE_ENEMY_HH

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include "../game/AGames.hh"
#include "Shoots.hh"

namespace arcade
{
  namespace games
  {
    class Ennemy
    {
      Vector2<float> _coord; //coordonnées du milieu
      std::vector<Vector2<float>> _listCoord;

      Shoot *shooted;
      const int value;
      bool dir;

     public:
      Ennemy(Vector2<float> pos, const int &nbr);
      ~Ennemy();

      void drawEnemy(graphics::IGraphic *graphic);
      void updateEnemy(void);
      bool checkShoot(const Vector2<float> &pos) const;
    };
  }
}

#endif //CPP_ARCADE_ENEMY_HH
