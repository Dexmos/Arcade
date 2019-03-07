/*
** Graphics.cpp for cpp_arcade in
**
** Made by auguste.larrive-jahan@epitech.eu
** Login   <auguste.larrive-jahan@epitech.net>
**
** Started on  mar. mars 18:26 2017 each
** Last update mar. mars 18:26 2017 each
*/

#include "Graphics.hh"

static std::unordered_map<sf::Keyboard::Key, arcade::Keys, arcade::EnumClassHash> match = {
	{sf::Keyboard::Up,     arcade::Keys::GO_UP},
	{sf::Keyboard::Down,   arcade::Keys::GO_DOWN},
	{sf::Keyboard::Left,   arcade::Keys::GO_LEFT},
	{sf::Keyboard::Right,  arcade::Keys::GO_RIGHT},
	{sf::Keyboard::Space,  arcade::Keys::SHOOT},
	{sf::Keyboard::Num2,   arcade::Keys::PREV_GRAPH_LIB},
	{sf::Keyboard::Num3,   arcade::Keys::NEXT_GRAPH_LIB},
	{sf::Keyboard::Num4,   arcade::Keys::PREV_GAME},
	{sf::Keyboard::Num5,   arcade::Keys::NEXT_GAME},
	{sf::Keyboard::Num8,   arcade::Keys::RESTART},
	{sf::Keyboard::Num9,   arcade::Keys::BACK_MENU},
	{sf::Keyboard::Escape, arcade::Keys::EXIT}
};

static std::unordered_map<arcade::Colors, sf::Color, arcade::EnumClassHash> colors = {
	{arcade::Colors::BLACK,		sf::Color::Black},
	//{arcade::Colors::GREY,	sf::Color::Color(0x888888ff)},
	{arcade::Colors::WHITE,		sf::Color::White},
	{arcade::Colors::RED,		sf::Color::Red},
	{arcade::Colors::BLUE,		sf::Color::Blue},
	{arcade::Colors::GREEN,		sf::Color::Green},
	{arcade::Colors::YELLOW,	sf::Color::Yellow},
	{arcade::Colors::CYAN,		sf::Color::Cyan},
	{arcade::Colors::MAGENTA,	sf::Color::Magenta}
};

arcade::graphics::GraphicSFML::GraphicSFML()
{
  if (!this->font.loadFromFile("assets/SolomonS.ttf"))
    {
	throw arcade::Errors("Could not load the font from it's file\n");
    }
}

arcade::graphics::GraphicSFML::~GraphicSFML()
{
  this->window->close();
  delete this->window;
}

void arcade::graphics::GraphicSFML::openWindow(const unsigned int &winWidth, const unsigned int &winHeight)
{
  this->window = new sf::RenderWindow(sf::VideoMode(winWidth, winHeight), "Arcade");
}

void arcade::graphics::GraphicSFML::clearWindow()
{
  if (isWindowOpen())
    this->window->clear();
}

void arcade::graphics::GraphicSFML::updateWindow()
{
  if (isWindowOpen())
    this->window->display();
}

bool arcade::graphics::GraphicSFML::isWindowOpen() const
{
  return this->window->isOpen();
}

arcade::Keys arcade::graphics::GraphicSFML::getKeys()
{
  sf::Event event;
  while (this->window->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	this->window->close();
      else if (event.type == sf::Event::KeyPressed)
	{
	  auto it = match.find(event.key.code);

	  if (it != match.end())
	    return it->second;
	}
    }
  return Keys::NONE;
}

void arcade::graphics::GraphicSFML::defineMapSize(const unsigned int &width, const unsigned int &height)
{
  this->width = width;
  this->height = height;
}

void arcade::graphics::GraphicSFML::drawLine(const Vector2<> &pos1, const Vector2<> &pos2, const Colors &color)
{
  double size;
  double angle;
  sf::RectangleShape line;

  size = sqrt(pow(((double) pos2.x - (double) pos1.x), 2) + pow(((double) pos2.y - (double) pos1.y), 2));
  if (((double) pos2.y - (double) pos1.y) == 0)
    {
      if((double)pos2.y - (double)pos1.y < 0)
	angle = - M_PI / 2;
      else
	angle = M_PI / 2;
    }
  else
    angle = atan((((double) pos2.y - (double) pos1.y)) / (((double) pos2.x - (double) pos1.x)));
  if ((double)pos2.x - (double)pos1.x < 0)
    angle += M_PI;
  line.setSize((sf::Vector2f((float) size, 1)));
  line.rotate((float) (angle) * (float) (180 / M_PI));
  auto it = colors.find(color);
  if (it != colors.end())
    line.setFillColor(it->second);
  line.setPosition((sf::Vector2f(pos1.x, pos1.y)));
  this->window->draw(line);
}

void arcade::graphics::GraphicSFML::drawCircle(const Vector2<> &pos, const float &size, const Colors &color)
{
  sf::CircleShape Circle;

  Circle.setRadius(size);
  Circle.setPosition(sf::Vector2f(pos.x, pos.y));
  auto it = colors.find(color);
  if (it != colors.end())
    Circle.setFillColor(it->second);
  this->window->draw(Circle);
}


void arcade::graphics::GraphicSFML::drawCircleOnBlock(const Vector2<> &pos, const int &inPos, const float &size,
						      const Colors &color)
{
  int size_block;

  auto win = this->window->getSize();
  if (win.x < win.y)
    size_block = win.x / this->width;
  else
    size_block = win.y / this->height;

  drawCircle({pos.x * size_block + inPos, pos.y * size_block + inPos}, size, color);
}


void arcade::graphics::GraphicSFML::drawBlock(const Vector2<> &pos, const Colors &color)
{
  sf::RectangleShape block;
  unsigned int size_block;

  auto size = this->window->getSize();
  if (size.x < size.y)
    size_block = size.x / this->width;
  else
    size_block = size.y / this->height;
  block.setSize(sf::Vector2f(size_block, size_block));
  block.setPosition(sf::Vector2f(pos.x * size_block, pos.y * size_block));
  auto it = colors.find(color);
  if (it != colors.end())
    block.setFillColor(it->second);
  this->window->draw(block);
}

void arcade::graphics::GraphicSFML::drawBlock(const Vector2<float> &pos, const Colors &color)
{
  sf::RectangleShape block;
  unsigned int size_block;

  auto size = this->window->getSize();
  if (size.x < size.y)
    size_block = size.x / this->width;
  else
    size_block = size.y / this->height;
  block.setSize(sf::Vector2f(size_block, size_block));
  block.setPosition(sf::Vector2f(pos.x * size_block, pos.y * size_block));
  auto it = colors.find(color);
  if (it != colors.end())
    block.setFillColor(it->second);
  this->window->draw(block);
}

void arcade::graphics::GraphicSFML::drawSquare(const Vector2<> &pos, const Vector2<> &size, const Colors &color)
{
  sf::RectangleShape block;

  block.setSize(sf::Vector2f(size.x, size.y));
  block.setPosition(sf::Vector2f(pos.x, pos.y));

  auto it = colors.find(color);
  if (it != colors.end())
    block.setFillColor(it->second);
  this->window->draw(block);
}

void arcade::graphics::GraphicSFML::drawSquareOnBlock(const Vector2<> &pos, const int &inPos, const Vector2<> &size,
						      const Colors &color)
{
  sf::RectangleShape block;
  unsigned int size_block;

  auto win = this->window->getSize();
  if (win.x < win.y)
    size_block = win.x / this->width;
  else
    size_block = win.y / this->height;
  block.setSize(sf::Vector2f(size.x, size.y));
  block.setPosition(sf::Vector2f(pos.x * size_block + inPos, pos.y * size_block + inPos));
  auto it = colors.find(color);
  if (it != colors.end())
    block.setFillColor(it->second);
  this->window->draw(block);
}

void arcade::graphics::GraphicSFML::drawText(const Vector2<> &pos, const std::string &text, const unsigned int &size,
					     const Colors &color)
{
  sf::Text my_text;
  my_text.setFont(this->font);
  my_text.setString(text);
  my_text.setCharacterSize(size);
  my_text.setFillColor(colors[color]);
  my_text.setPosition(pos.x, pos.y);
  this->window->draw(my_text);
}

extern "C" arcade::graphics::IGraphic *entry_point()
{
  return new arcade::graphics::GraphicSFML();
}