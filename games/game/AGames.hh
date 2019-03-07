/*
** AGames.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:49 2017 florian
** Last update mer. avr. 19:49 2017 florian
*/

#ifndef CPP_ARCADE_AGAMES_HH
# define CPP_ARCADE_AGAMES_HH

# include "../../Interfaces/IGames.hh"
#include "../../core/DLLoader.hpp"
#include "../../Interfaces/IGraphics.hh"
# include <vector>

namespace arcade
{
  namespace games
  {
    class AGame : public IGame
    {
     protected:
      graphics::IGraphic *graphic;
      unsigned int	max_score;
      unsigned int	_highscore;

      const unsigned int _width;
      const unsigned int _height;

     public:
      AGame(const unsigned int width, const unsigned int height);
      virtual ~AGame();

      virtual void UpdateGame() = 0; //mise à jour du jeu
      virtual void setGraphics(graphics::IGraphic *graph); //setGraphics
      virtual unsigned int getWidth() const = 0;
      virtual unsigned int getHeight() const = 0;
      virtual void KeyAction(const arcade::Keys key) = 0;
      virtual void setHighScore(const unsigned int &highScore);
      virtual unsigned int getScore() const;
      virtual const std::string &getGameName() const = 0;
    };
  }
}

#endif //CPP_ARCADE_AGAMES_HH
