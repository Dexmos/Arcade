/*
** Enemy.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#include "Ennemy.hh"
#include "Block.hh"

arcade::games::Ennemy::Ennemy(Vector2<float> pos, const int &nbr) : value(nbr)
{
  this->_coord = pos;
  this->dir = false;
  this->shooted = nullptr;

  switch (this->value)
    {
      case 1:
	{
	  this->_listCoord.push_back({0, 0});
	  this->_listCoord.push_back({0, 1});
	  this->_listCoord.push_back({0, -1});
	  this->_listCoord.push_back({1, 0});
	  break;
	}
      case 2:
	{
	  this->_listCoord.push_back({0, 0});
	  this->_listCoord.push_back({0, -1});
	  this->_listCoord.push_back({0, 1});
	  this->_listCoord.push_back({-1, 0});
	  break;
	}
      case 3:
	{
	  this->_listCoord.push_back({0, 0});
	  this->_listCoord.push_back({1, 0});
	  this->_listCoord.push_back({-1, 0});
	  this->_listCoord.push_back({0, -1});
	  break;
	}
      case 4:
	{
	  this->_listCoord.push_back({0, 0});
	  this->_listCoord.push_back({-1, 0});
	  this->_listCoord.push_back({1, 0});
	  this->_listCoord.push_back({0, 1});
	  break;
	}
      default:
	break;
    }
}

arcade::games::Ennemy::~Ennemy()
{
  delete this->shooted;
}

void arcade::games::Ennemy::drawEnemy(graphics::IGraphic *graphic)
{
  if (this->shooted)
    this->shooted->drawshoot(graphic, Colors::GREEN);

  graphic->drawBlock(this->_coord + this->_listCoord[0], Colors::MAGENTA);
  graphic->drawBlock(this->_coord + this->_listCoord[1], Colors::MAGENTA);
  graphic->drawBlock(this->_coord + this->_listCoord[2], Colors::MAGENTA);
  graphic->drawBlock(this->_coord + this->_listCoord[3], Colors::MAGENTA);
}

void arcade::games::Ennemy::updateEnemy()
{
  switch (this->value)
    {
      case 1:
	{
	  if (this->dir)
	    this->_coord.y = round((this->_coord.y + 0.1f) * 10000) / 10000;
	  else
	    this->_coord.y = round((this->_coord.y - 0.1f) * 10000) / 10000;
	  break;
	}
      case 2:
	{
	  if (this->dir)
	    this->_coord.y = round((this->_coord.y - 0.1f) * 10000) / 10000;
	  else
	    this->_coord.y = round((this->_coord.y + 0.1f) * 10000) / 10000;
	  break;
	}
      case 3:
	{
	  if (this->dir)
	    this->_coord.x = round((this->_coord.x + 0.1f) * 10000) / 10000;
	  else
	    this->_coord.x = round((this->_coord.x - 0.1f) * 10000) / 10000;
	  break;
	}
      case 4:
	{
	  if (this->dir)
	    this->_coord.x = round((this->_coord.x - 0.1f) * 10000) / 10000;
	  else
	    this->_coord.x = round((this->_coord.x + 0.1f) * 10000) / 10000;
	  break;
	}
    }

  if (this->_coord.x - (int)this->_coord.x == 0 && this->_coord.y - (int)this->_coord.y == 0)
    {
      if (!this->shooted && rand() % 25 == 0)
	{
	  Vector2<float> pos = this->_coord + this->_listCoord[3];
	  Keys key;

	  switch (this->value)
	    {
	      case 1:
		{
		  key = Keys::GO_RIGHT;
		  break;
		}
	      case 2:
		{
		  key = Keys::GO_LEFT;
		  break;
		}
	      case 3:
		{
		  key = Keys::GO_UP;
		  break;
		}
	      case 4:
		{
		  key = Keys::GO_DOWN;
		  break;
		}
	    }
	  this->shooted = new Shoot(150, 0.2, pos, key);
	}

      switch (this->value)
	{
	  case 1:
	    {
	      if (this->dir && this->_coord.y == 47)
		this->dir = false;
	      else if (this->_coord.y == 2)
		this->dir = true;
	      break;
	    }
	  case 2:
	    {
	      if (this->dir && this->_coord.y == 2)
		this->dir = false;
	      else if (this->_coord.y == 47)
		this->dir = true;
	      break;
	    }
	  case 3:
	    {
	      if (this->dir && this->_coord.x == 47)
		this->dir = false;
	      else if (this->_coord.x == 2)
		this->dir = true;
	      break;
	    }
	  case 4:
	    {
	      if (this->dir && this->_coord.x == 2)
		this->dir = false;
	      else if (this->_coord.x == 47)
		this->dir = true;
	      break;
	    }
	}
    }

  if (this->shooted)
    {
      this->shooted->updateshoot();
      if (this->shooted->_range <= 0)
	{
	  delete this->shooted;
	  this->shooted = nullptr;
	}
    }
}

bool arcade::games::Ennemy::checkShoot(const Vector2<float> &pos) const
{
  if (!this->shooted)
    return false;
  const Vector2<float> &shootPos = this->shooted->getPos();

  if (shootPos.x - pos.x < 1
      && shootPos.x - pos.x > -1
      && shootPos.y - pos.y < 1
      && shootPos.y - pos.y > -1)
    return true;
  return false;
}