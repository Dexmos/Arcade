/*
** LibCaca.hh for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  ven. avr. 15:08 2017 marye_s
** Last update ven. avr. 15:08 2017 marye_s
*/
#ifndef CPP_ARCADE_LIBCACA_HH
#define CPP_ARCADE_LIBCACA_HH

#include "../../Interfaces/IGraphics.hh"
#include <unordered_map>
#include <caca.h>

namespace arcade
{
  namespace graphics
  {
    class LibCaca : public IGraphic
    {
     public:
      enum class Caca_keys : int
      {
	CACA_GO_UP = CACA_KEY_UP,
	CACA_GO_DOWN = CACA_KEY_DOWN,
	CACA_GO_LEFT = CACA_KEY_LEFT,
	CACA_GO_RIGHT = CACA_KEY_RIGHT,
	CACA_SHOOT = 32,
	CACA_PREV_GRAPH_LIB = 50,
	CACA_NEXT_GRAPH_LIB = 51,
	CACA_PREV_GAME = 52,
	CACA_NEXT_GAME = 53,
	CACA_RESTART = 56,
	CACA_BACK_MENU = 57,
	CACA_EXIT = CACA_KEY_ESCAPE,
      };

     private:
      caca_canvas_t	*cv;
      caca_display_t	*display;
      caca_event_t	ev;
      unsigned int	_height;
      unsigned int	_width;

     public:
      LibCaca(); //done
      virtual ~LibCaca(); //done

      virtual void openWindow(const unsigned int &winWidth, const unsigned int &winHeight); //done
      virtual void clearWindow(); //done
      virtual void updateWindow(); //done

      virtual bool isWindowOpen() const; //done
      virtual Keys getKeys();

      virtual void defineMapSize(const unsigned int &width, const unsigned int &height);
      virtual void drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color); //done
      virtual void drawCircle(const Vector2<> &pos, const float &size, const Colors &color); //done
      virtual void drawCircleOnBlock(const Vector2<> &pos, const int &inPos, const float &size, const Colors &color); //done
      virtual void drawBlock(const Vector2<> &pos, const Colors &color); //done
      virtual void drawBlock(const Vector2<float> &pos, const Colors &color); //done
      virtual void drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color); //done
      virtual void drawSquareOnBlock(const Vector2<> &pos, const int &inPos, const Vector2<> &size, const Colors &color); // done
      virtual void drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size, const Colors &color); //done
    };
  }
}


#endif //CPP_ARCADE_LIBCACA_HH
