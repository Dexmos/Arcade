/*
** Solarfox.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#ifndef CPP_ARCADE_SOLARFOX_HH
#define CPP_ARCADE_SOLARFOX_HH

#include "Ennemy.hh"
#include <chrono>
#include <vector>
#include <string>
#include <unordered_map>
#include "../game/AGames.hh"
#include "../../Interfaces/Protocol.hpp"
#include "Block.hh"
#include "Shoots.hh"

namespace arcade
{
  namespace games
  {
    class Solarfox : public AGame
    {
      float speed;
      arcade::Keys next_key;
      arcade::Keys last_key;
      Vector2<float> coord;
      bool death;
      std::chrono::system_clock::time_point chrono;
      bool win;
      arcade::games::Block _victim;
      std::vector<arcade::games::Ennemy *> enemie;
      bool go_up;
      Shoot *shooted;
      unsigned int score;

      const std::string gameName;

     public:
      Solarfox();
      virtual ~Solarfox();

      virtual void UpdateGame(); //mise à jour du jeu
      virtual unsigned int getWidth() const;
      virtual unsigned int getHeight() const;
      virtual void KeyAction(const arcade::Keys key);

      virtual const std::string &getGameName() const;
    };
  }
}

#endif //CPP_ARCADE_SOLARFOX_HH
