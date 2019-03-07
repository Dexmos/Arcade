/*
** Snake.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:49 2017 florian
** Last update mer. avr. 19:49 2017 florian
*/

#ifndef CPP_ARCADE_SNAKE_HH
#define CPP_ARCADE_SNAKE_HH

#include <chrono>
#include <vector>
#include <string>
#include <unordered_map>
#include "../game/AGames.hh"
#include "Apple.hh"

namespace arcade
{
  namespace games
  {
    class Snake : public AGame
    {
      arcade::Keys next_key;
      arcade::Keys last_key;
      std::vector<Vector2<>> coord;
      bool death;
      bool win;
      std::chrono::system_clock::time_point chrono;
      Apple iphone;
      int score;
      int rand_msg;
      int size_snake;
      std::string	name;

     public:
      Snake();
      virtual ~Snake();

      virtual void UpdateGame(); //mise à jour du jeu
      virtual unsigned int getWidth() const;
      virtual unsigned int getHeight() const;
      virtual void KeyAction(const arcade::Keys key);

      virtual const std::string &getGameName() const;
    };
  }
}


#endif //CPP_ARCADE_SNAKE_HH
