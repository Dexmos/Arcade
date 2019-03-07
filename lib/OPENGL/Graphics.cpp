/*
** Graphics.cpp for cpp_arcade in
**
** Made by auguste.larrive-jahan@epitech.eu
** Login   <auguste.larrive-jahan@epitech.net>
**
** Started on  jeu. avr. 14:04 2017 each
** Last update jeu. avr. 14:04 2017 each
*/

#include "Graphics.hh"
#include "../../Interfaces/Protocol.hpp"

static std::unordered_map<SDLKey, arcade::Keys, arcade::EnumClassHash> match = {
	{SDLK_UP,         arcade::Keys::GO_UP},
	{SDLK_DOWN,       arcade::Keys::GO_DOWN},
	{SDLK_LEFT,       arcade::Keys::GO_LEFT},
	{SDLK_RIGHT,      arcade::Keys::GO_RIGHT},
	{SDLK_SPACE,      arcade::Keys::SHOOT},
	{SDLK_WORLD_73,   arcade::Keys::PREV_GRAPH_LIB},
	{SDLK_QUOTEDBL,   arcade::Keys::NEXT_GRAPH_LIB},
	{SDLK_QUOTE,      arcade::Keys::PREV_GAME},
	{SDLK_LEFTPAREN,  arcade::Keys::NEXT_GAME},
	{SDLK_UNDERSCORE, arcade::Keys::RESTART},
	{SDLK_WORLD_71,   arcade::Keys::BACK_MENU},
	{SDLK_ESCAPE,     arcade::Keys::EXIT}
};

static std::unordered_map<arcade::Colors, arcade::graphics::GraphicsOPENGL::OpenGLColor, arcade::EnumClassHash> colors = {
	{arcade::Colors::BLACK,   arcade::graphics::GraphicsOPENGL::OpenGLColor::BLACK},
	{arcade::Colors::WHITE,   arcade::graphics::GraphicsOPENGL::OpenGLColor::WHITE},
	{arcade::Colors::RED,     arcade::graphics::GraphicsOPENGL::OpenGLColor::RED},
	{arcade::Colors::BLUE,    arcade::graphics::GraphicsOPENGL::OpenGLColor::BLUE},
	{arcade::Colors::GREEN,   arcade::graphics::GraphicsOPENGL::OpenGLColor::GREEN},
	{arcade::Colors::YELLOW,  arcade::graphics::GraphicsOPENGL::OpenGLColor::YELLOW},
	{arcade::Colors::CYAN,    arcade::graphics::GraphicsOPENGL::OpenGLColor::CYAN},
	{arcade::Colors::MAGENTA, arcade::graphics::GraphicsOPENGL::OpenGLColor::MAGENTA}
};


arcade::graphics::GraphicsOPENGL::GraphicsOPENGL()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
}

arcade::graphics::GraphicsOPENGL::~GraphicsOPENGL()
{
  SDL_Quit();
}

void arcade::graphics::GraphicsOPENGL::openWindow(const unsigned int &winWidth, const unsigned int &winHeight)
{
  this->window_with = winWidth;
  this->window_height = winHeight;
  this->screen = SDL_SetVideoMode(winWidth, winHeight, 32, SDL_SWSURFACE | SDL_OPENGL);
  if (!this->screen)
    return;

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, winWidth, winHeight, 1.0, -1.0, 1.0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
}

void arcade::graphics::GraphicsOPENGL::clearWindow()
{
  if (this->screen)
    glClear(GL_COLOR_BUFFER_BIT);
}

void arcade::graphics::GraphicsOPENGL::updateWindow()
{
  SDL_GL_SwapBuffers();
  SDL_Delay(10);
}

bool arcade::graphics::GraphicsOPENGL::isWindowOpen() const
{
  if (this->screen)
    return true;
  return false;
}

arcade::Keys arcade::graphics::GraphicsOPENGL::getKeys()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	SDL_Quit();
      else if (event.type == SDL_KEYDOWN)
	{
	  auto it = match.find(event.key.keysym.sym);
	  if (it != match.end())
	    return it->second;
	}
    }
  return Keys::NONE;
}

/*
 * défini le nombre d'unités de blocks dans le jeu
 */

void arcade::graphics::GraphicsOPENGL::defineMapSize(const unsigned int &width, const unsigned int &height)
{
  this->width = width;
  this->height = height;
}

void arcade::graphics::GraphicsOPENGL::drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color)
{
  uint8_t r, g, b, a;


  glEnable(GL_LINE_SMOOTH);
  glBegin(GL_LINES);
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = (static_cast<uint32_t> (it->second) & 0x000000FF);
    }
  glColor4ub(r, g, b, a);
  glVertex2f(pos1.x, pos1.y);
  glVertex2f(pos2.x, pos2.y);
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawCircle(const Vector2<> &pos, const float &size, const Colors &color)
{
  uint8_t r, g, b, a;
  int i;

  glBegin(GL_TRIANGLES);
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);
  for (i = 0; i < 90; i++)
    {
      glVertex2f(pos.x, pos.y);
      glVertex2f((GLfloat) (pos.x + size * cos(i * (M_PI / 45))), (GLfloat) (pos.y + size * sin(i * (M_PI / 45))));
      glVertex2f((GLfloat) (pos.x + size * cos((i + 1) * (M_PI / 45))),
		 (GLfloat) (pos.y + size * sin((i + 1) * (M_PI / 45))));
    }
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawCircleOnBlock(const Vector2<> &pos, const int &inPos, const float &size,
							 const Colors &color)
{
  uint8_t r, g, b, a;
  int i;
  unsigned int size_block;

  glBegin(GL_TRIANGLES);
  if (this->window_height < this->window_with)
    size_block = this->window_height / this->height;
  else
    size_block = this->window_with / this->width;
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);

  int x = pos.x * size_block + inPos;
  int y = pos.y * size_block + inPos;
  for (i = 0; i < 90; i++)
    {
      glVertex2f(x, y);
      glVertex2f((GLfloat) (x + size * cos(i * (M_PI / 45))), (GLfloat) (y + size * sin(i * (M_PI / 45))));
      glVertex2f((GLfloat) (x + size * cos((i + 1) * (M_PI / 45))),
		 (GLfloat) (y + size * sin((i + 1) * (M_PI / 45))));
    }
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawBlock(const Vector2<> &pos, const Colors &color)
{
  unsigned int size_block;
  uint8_t r, g, b, a;

  glBegin(GL_QUADS);
  if (this->window_height < this->window_with)
    size_block = this->window_height / this->height;
  else
    size_block = this->window_with / this->width;
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);
  unsigned int x = pos.x * size_block;
  unsigned int y = pos.y * size_block;
  glVertex2f(x, y);
  glVertex2f(x + size_block, y);
  glVertex2f(x + size_block, y + size_block);
  glVertex2f(x, y + size_block);
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawBlock(const Vector2<float> &pos, const Colors &color)
{
  unsigned int size_block;
  uint8_t r, g, b, a;

  glBegin(GL_QUADS);
  if (this->window_height < this->window_with)
    size_block = this->window_height / this->height;
  else
    size_block = this->window_with / this->width;
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);
  unsigned int x = pos.x * size_block;
  unsigned int y = pos.y * size_block;
  glVertex2f(x, y);
  glVertex2f(x + size_block, y);
  glVertex2f(x + size_block, y + size_block);
  glVertex2f(x, y + size_block);
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color)
{
  uint8_t r, g, b, a;

  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);
  glVertex2f(pos.x, pos.y);
  glVertex2f(pos.x + size.x, pos.y);
  glVertex2f(pos.x + size.x, pos.y + size.y);
  glVertex2f(pos.x, pos.y + size.y);
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawSquareOnBlock(const Vector2<> &pos, const int &inPos, const Vector2<> &size,
							 const Colors &color)
{
  unsigned int size_block;
  uint8_t r, g, b, a;

  glBegin(GL_QUADS);
  if (this->window_height < this->window_with)
    size_block = this->window_height / this->height;
  else
    size_block = this->window_with / this->width;
  auto it = colors.find(color);
  if (it != colors.end())
    {
      r = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      b = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      a = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  glColor4ub(r, g, b, a);
  unsigned int x = pos.x * size_block + inPos;
  unsigned int y = pos.y * size_block + inPos;
  glVertex2f(x, y);
  glVertex2f(x + size.x, y);
  glVertex2f(x + size.x, y + size.y);
  glVertex2f(x, y + size.y);
  glEnd();
  glFlush();
}

void arcade::graphics::GraphicsOPENGL::drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size,
						const Colors &color)
{
  SDL_Color my_color;
  SDL_Surface *message;
  GLuint texture = 0;
  int width_texture, height_texture;
  float ratio_width, ratio_height;

  this->font = TTF_OpenFont("assets/SolomonS.ttf", size);
  auto it = colors.find(color);
  if (it != colors.end())
    {
      my_color.b = (static_cast<uint32_t> (it->second) & 0xFF000000) >> 24;
      my_color.g = (static_cast<uint32_t> (it->second) & 0x00FF0000) >> 16;
      my_color.r = (static_cast<uint32_t> (it->second) & 0x0000FF00) >> 8;
      my_color.unused = static_cast<uint32_t> (it->second) & 0x000000FF;
    }
  message = TTF_RenderText_Blended(this->font, text.c_str(), my_color);
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  width_texture = (int) (pow(2, ceil(log((float) message->w) / log(2.0))) + 0.5);
  height_texture = (int) (pow(2, ceil(log((float) message->h) / log(2.0))) + 0.5);
  ratio_width = (float) message->w / (float) width_texture;
  ratio_height = (float) message->h / (float) height_texture;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_texture, height_texture, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, message->w, message->h, GL_RGBA, GL_UNSIGNED_BYTE, message->pixels);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glColor4ub(255, 255, 255, 255);
  glVertex2d(pos.x, pos.y);
  glTexCoord2f(ratio_width, 0);
  glVertex2d(pos.x + message->w, pos.y);
  glTexCoord2f(ratio_width, ratio_height);
  glVertex2d(pos.x + message->w, pos.y + message->h);
  glTexCoord2f(0, ratio_height);
  glVertex2d(pos.x, pos.y + message->h);
  glEnd();

  glDeleteTextures(1, &texture);
  SDL_FreeSurface(message);
  TTF_CloseFont(this->font);
}

extern "C" arcade::graphics::IGraphic *entry_point()
{
  return new arcade::graphics::GraphicsOPENGL();
}