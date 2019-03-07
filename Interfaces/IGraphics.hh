/*
** IGraphic.hh for cpp_arcade in
**
** Made by julien1.benoit@epitech.eu
** Login   <julien1.benoit@epitech.net>
**
** Started on  ven. mars 11:03 2017 benoit_g
** Last update ven. mars 11:03 2017 florian
*/

#ifndef CPP_ARCADE_IGRAPHIC_HH
#define CPP_ARCADE_IGRAPHIC_HH

#include <iostream>
#include "enums.hh"
#include "Vector2.hpp"


namespace arcade
{
  namespace graphics
  {
    class IGraphic
    {
     public:
      virtual ~IGraphic() {};

      virtual void openWindow(const unsigned int &winWidth, const unsigned int &winHeight) = 0;
      virtual void clearWindow() = 0;
      virtual void updateWindow() = 0;

      virtual bool isWindowOpen() const = 0;
      virtual Keys getKeys() = 0;

      virtual void defineMapSize(const unsigned int &width, const unsigned int &height) = 0;
      virtual void drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color) = 0;
      virtual void drawCircle(const Vector2<> &pos, const float &size, const Colors &color) = 0;
      virtual void drawCircleOnBlock(const Vector2<> &pos, const int &inPos, const float &size, const Colors &color) = 0;
      virtual void drawBlock(const Vector2<> &pos, const Colors &color) = 0;
      virtual void drawBlock(const Vector2<float> &pos, const Colors &color) = 0;
      virtual void drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color) = 0;
      virtual void drawSquareOnBlock(const Vector2<> &pos, const int &inPos, const Vector2<> &size, const Colors &color) = 0;
      virtual void drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size, const Colors &color) = 0;
    };
  }

  //extern "C" arcade::IGraphic *entry_point(void);  function entry point
}

#endif //CPP_ARCADE_IGRAPHIC_HH
