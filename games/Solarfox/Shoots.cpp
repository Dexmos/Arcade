/*
** Shoots.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#include "Shoots.hh"


arcade::games::Shoot::Shoot(int range, float speed, const Vector2<float> &coord, arcade::Keys where)
{
  this->_range = range;
  this->_speed = speed;
  this->_where = where;
  this->pos = coord;
}

arcade::games::Shoot::~Shoot()
{}

void arcade::games::Shoot::updateshoot()
{
  switch (this->_where)
    {
      case arcade::Keys::GO_DOWN :
	{
	  this->pos.y = round((this->pos.y + _speed) * 10000) / 10000;
	  break;
	}
      case arcade::Keys::GO_UP :
	{
	  this->pos.y = round((this->pos.y - _speed) * 10000) / 10000;
	  break;
	}
      case arcade::Keys::GO_LEFT :
	{
	  this->pos.x = round((this->pos.x - _speed) * 10000) / 10000;
	  break;
	}
      case arcade::Keys::GO_RIGHT :
	{
	  this->pos.x = round((this->pos.x + _speed) * 10000) / 10000;
	  break;
	}
      default:
	break;
    }
  this->_range -= 1;
}

void arcade::games::Shoot::drawshoot(graphics::IGraphic *graphic, const Colors &color)
{
  graphic->drawBlock(this->pos, color);
}

const Vector2<float>& arcade::games::Shoot::getPos() const
{
  return this->pos;
}