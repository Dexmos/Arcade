/*
** IGame.hh for cpp_arcade in
**
** Made by julien1.benoit@epitech.eu
** Login   <julien1.benoit@epitech.net>
**
** Started on  ven. mars 11:02 2017 benoit_g
** Last update Tue Mar 28 15:04:36 2017 florian
*/

#ifndef CPP_ARCADE_IGAME_HH
#define CPP_ARCADE_IGAME_HH

#include "IGraphics.hh"
#include "Vector2.hpp"
#include "enums.hh"

namespace arcade
{
  namespace games
  {
    class IGame
    {
     public:
      virtual ~IGame() {};

      virtual void UpdateGame() = 0;
      virtual void setGraphics(graphics::IGraphic *graph) = 0;

      virtual unsigned int getWidth() const = 0;
      virtual unsigned int getHeight() const = 0;
      virtual void KeyAction(const arcade::Keys key) = 0;

      virtual void setHighScore(const unsigned int &highScore) = 0;
      virtual unsigned int getScore() const = 0;
      virtual const std::string &getGameName() const = 0;
    };
  }
}

#endif //CPP_ARCADE_IGAME_HH
