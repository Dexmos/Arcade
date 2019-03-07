/*
** Graphics.hh for cpp_arcade in
**
** Made by auguste.larrive-jahan@epitech.eu
** Login   <auguste.larrive-jahan@epitech.net>
**
** Started on  mer. avr. 15:37 2017 each
** Last update mer. avr. 15:37 2017 each
*/

#ifndef CPP_ARCADE_GRAPHICS_HH
# define CPP_ARCADE_GRAPHICS_HH

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unordered_map>
#include "../../Interfaces/IGraphics.hh"

namespace arcade
{
  namespace graphics
  {
    class GraphicsOPENGL : public IGraphic
    {
     public:
      enum class OpenGLColor : uint32_t
      {
	RED = 0xFF0000FF,
	GREEN = 0x00FF00FF,
	BLUE = 0x0000FFFF,
	YELLOW = 0xFFFF00FF,
	BLACK = 0x000000FF,
	WHITE = 0xFFFFFFFF,
	CYAN = 0x00FFFFFF,
	MAGENTA = 0xFF00FFFF
      };

     private:
      unsigned int window_with;
      unsigned int window_height;
      unsigned int width;
      unsigned int height;
      TTF_Font *font;
      SDL_Surface *screen;

     public:
      GraphicsOPENGL();
      virtual ~GraphicsOPENGL();

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
