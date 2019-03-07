/*
** Graphics.hh for cpp_arcade in
**
** Made by auguste.larrive-jahan@epitech.eu
** Login   <auguste.larrive-jahan@epitech.net>
**
** Started on  mar. mars 18:21 2017 each
** Last update mar. mars 18:21 2017 each
*/

#ifndef CPP_ARCADE_GRAPHICS_HH
#define CPP_ARCADE_GRAPHICS_HH

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../../Interfaces/IGraphics.hh"

namespace arcade
{
  namespace graphics
  {
    class GraphicSFML : public IGraphic
    {
      sf::RenderWindow *window;
      sf::Keyboard::Key	key;
      sf::Font		font;
      unsigned int	width;
      unsigned int	height;

     public:
      GraphicSFML();
      virtual ~GraphicSFML();

      virtual void openWindow(const unsigned int &winWidth, const unsigned int &winHeight);
      virtual void clearWindow();
      virtual void updateWindow();

      virtual bool isWindowOpen() const;
      virtual Keys getKeys();

      virtual void defineMapSize(const unsigned int &width, const unsigned int &height);
      virtual void drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color);
      virtual void drawCircle(const Vector2<> &pos, const float &size, const Colors &color);
      virtual void drawCircleOnBlock(const Vector2<> &pos, const int &inPos, const float &size, const Colors &color);
      virtual void drawBlock(const Vector2<> &pos, const Colors &color);
      virtual void drawBlock(const Vector2<float> &pos, const Colors &color);
      virtual void drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color);
      virtual void drawSquareOnBlock(const Vector2<> &pos, const int &inPos, const Vector2<> &size, const Colors &color);
      virtual void drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size, const Colors &color);
    };
  }
}


#endif //CPP_ARCADE_GRAPHICS_HH
