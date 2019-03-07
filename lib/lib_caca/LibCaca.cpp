/*
** LibCaca.cpp for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  ven. avr. 15:08 2017 marye_s
** Last update ven. avr. 15:08 2017 marye_s
*/
#include "LibCaca.hh"

static std::unordered_map<arcade::Colors, caca_color, arcade::EnumClassHash> match_color = {
	{arcade::Colors::BLACK,   caca_color::CACA_BLACK},
	{arcade::Colors::BLUE,    caca_color::CACA_BLUE},
	{arcade::Colors::CYAN,    caca_color::CACA_CYAN},
	{arcade::Colors::GREEN,   caca_color::CACA_GREEN},
	{arcade::Colors::MAGENTA, caca_color::CACA_MAGENTA},
	{arcade::Colors::RED,     caca_color::CACA_RED},
	{arcade::Colors::WHITE,   caca_color::CACA_WHITE},
	{arcade::Colors::YELLOW,  caca_color::CACA_YELLOW},
};

static std::unordered_map<arcade::graphics::LibCaca::Caca_keys, arcade::Keys, arcade::EnumClassHash> match_key = {
	{arcade::graphics::LibCaca::Caca_keys::CACA_GO_UP,          arcade::Keys::GO_UP},
	{arcade::graphics::LibCaca::Caca_keys::CACA_GO_DOWN,        arcade::Keys::GO_DOWN},
	{arcade::graphics::LibCaca::Caca_keys::CACA_GO_LEFT,        arcade::Keys::GO_LEFT},
	{arcade::graphics::LibCaca::Caca_keys::CACA_GO_RIGHT,       arcade::Keys::GO_RIGHT},
	{arcade::graphics::LibCaca::Caca_keys::CACA_SHOOT,          arcade::Keys::SHOOT},
	{arcade::graphics::LibCaca::Caca_keys::CACA_PREV_GRAPH_LIB, arcade::Keys::PREV_GRAPH_LIB},
	{arcade::graphics::LibCaca::Caca_keys::CACA_NEXT_GRAPH_LIB, arcade::Keys::NEXT_GRAPH_LIB},
	{arcade::graphics::LibCaca::Caca_keys::CACA_PREV_GAME,      arcade::Keys::PREV_GAME},
	{arcade::graphics::LibCaca::Caca_keys::CACA_NEXT_GAME,      arcade::Keys::NEXT_GAME},
	{arcade::graphics::LibCaca::Caca_keys::CACA_RESTART,        arcade::Keys::RESTART},
	{arcade::graphics::LibCaca::Caca_keys::CACA_BACK_MENU,      arcade::Keys::BACK_MENU},
	{arcade::graphics::LibCaca::Caca_keys::CACA_EXIT,           arcade::Keys::EXIT},
};

arcade::graphics::LibCaca::LibCaca()
{
  this->_height = 0;
  this->_width = 0;
}

arcade::graphics::LibCaca::~LibCaca()
{
  caca_free_display(this->display);
  caca_free_canvas(this->cv);
}


void arcade::graphics::LibCaca::openWindow(const unsigned int &winWidth, const unsigned int &winHeight)
{
  this->cv = caca_create_canvas(winWidth * 0.125, winHeight * (0.125 / 2));

  this->display = caca_create_display(this->cv);
}

arcade::Keys arcade::graphics::LibCaca::getKeys()
{
  if (caca_get_event(this->display, CACA_EVENT_KEY_PRESS, &this->ev, 0) == 0)
    return (arcade::Keys::NONE);

  int keys = caca_get_event_key_ch(&this->ev);
  auto check = match_key.find(static_cast<arcade::graphics::LibCaca::Caca_keys>(keys));
  if (check == match_key.end())
    return (arcade::Keys::NONE);
  else
    return (check->second);
}


void arcade::graphics::LibCaca::clearWindow()
{
  caca_clear_canvas(this->cv);
}

void arcade::graphics::LibCaca::updateWindow()
{
  caca_refresh_display(this->display);
}


bool arcade::graphics::LibCaca::isWindowOpen() const
{
  return (caca_get_event(this->display, CACA_EVENT_QUIT, nullptr, 0) == 0);
}


void arcade::graphics::LibCaca::defineMapSize(const unsigned int &width, const unsigned int &height)
{
  this->_width = width;
  this->_height = height;
}

void arcade::graphics::LibCaca::drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color)
{
  caca_set_color_ansi(this->cv, match_color[color], CACA_BLACK);
  caca_draw_thin_line(this->cv, pos1.x * 0.125, pos1.y * (0.125 / 2), pos2.x * 0.125, pos2.y * (0.125 / 2));
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawCircle(const Vector2<> &pos, const float &size, const Colors &color)
{
  caca_set_color_ansi(this->cv, match_color[color], CACA_BLACK);
  caca_draw_circle(this->cv, pos.x * 0.125, pos.y * (0.125 / 2), size, '.');
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawCircleOnBlock(const Vector2<> &pos, const int &inPos,
						  const float &size, const Colors &color)
{
  (void)inPos;
  (void)size;
  caca_set_color_ansi(this->cv, match_color[color], match_color[color]);
  unsigned int size_block;

  int canvas_width = caca_get_canvas_width(this->cv);
  int canvas_height = caca_get_canvas_height(this->cv);

  if (canvas_width < canvas_height)
    size_block = canvas_width / this->_width;
  else
    size_block = canvas_height / this->_height;
  (void)size_block;
  caca_fill_box(this->cv, pos.x, pos.y, 1, 1, ' ');
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawBlock(const Vector2<> &pos, const Colors &color)
{
  caca_set_color_ansi(this->cv, match_color[color], match_color[color]);
  unsigned int size_block;

  int canvas_width = caca_get_canvas_width(this->cv);
  int canvas_height = caca_get_canvas_height(this->cv);

  if (canvas_width < canvas_height)
    size_block = canvas_width / this->_width;
  else
    size_block = canvas_height / this->_height;
  (void)size_block;
  caca_fill_box(this->cv, pos.x, pos.y, 1, 1, ' ');
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawBlock(const Vector2<float> &pos, const Colors &color)
{
  caca_set_color_ansi(this->cv, match_color[color], match_color[color]);
  unsigned int size_block;

  int canvas_width = caca_get_canvas_width(this->cv);
  int canvas_height = caca_get_canvas_height(this->cv);

  if (canvas_width < canvas_height)
    size_block = canvas_width / this->_width;
  else
    size_block = canvas_height / this->_height;
  (void)size_block;
  caca_fill_box(this->cv, round(pos.x), round(pos.y), 1, 1, ' ');
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color)
{
  caca_set_color_ansi(this->cv, match_color[color], CACA_BLACK);
  caca_draw_thin_box(this->cv, pos.x, pos.y, size.x, size.y);
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawSquareOnBlock(const Vector2<> &pos, const int &inPos,
						  const Vector2<> &size, const Colors &color)
{
  (void)inPos;
  (void)size;
  caca_set_color_ansi(this->cv, match_color[color], match_color[color]);
  unsigned int size_block;

  int canvas_width = caca_get_canvas_width(this->cv);
  int canvas_height = caca_get_canvas_height(this->cv);

  if (canvas_width < canvas_height)
    size_block = canvas_width / this->_width;
  else
    size_block = canvas_height / this->_height;
  (void)size_block;
  caca_fill_box(this->cv, pos.x, pos.y, 1, 1, ' ');
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

void arcade::graphics::LibCaca::drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size, const Colors &color)
{
  (void) size;
  caca_set_color_ansi(this->cv, match_color[color], CACA_BLACK);
  caca_put_str(this->cv, pos.x * 0.125, pos.y * (0.125 / 2), text.c_str());
  caca_set_color_ansi(this->cv, CACA_BLACK, CACA_BLACK);
}

extern "C" arcade::graphics::IGraphic *entry_point()
{
  return new arcade::graphics::LibCaca();
}