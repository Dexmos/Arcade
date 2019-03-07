/*
** Apple.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:50 2017 florian
** Last update Sat Apr  8 17:02:43 2017 Florian
*/

#include "Apple.hh"

arcade::games::Apple::Apple(std::vector<Vector2<>> &coord) : _coord(coord)
{}

arcade::games::Apple::~Apple()
{}

void arcade::games::Apple::setPos(Vector2<> pos)
{
  this->pos = pos;
}

Vector2<> arcade::games::Apple::getPos() const
{
  return (this->pos);
}

void arcade::games::Apple::getRandPos()
{
  bool isdif = false;

  std::srand(std::time(0));
  while (!isdif)
    {
      this->setPos({rand() % 28 + 1, rand() % 28 + 1});
      for (auto it : this->_coord)
	{
	  if (it == this->pos)
	    {
	      isdif = false;
	      break;
	    }
	  else
	    isdif = true;
	}
    }
};
