/*
** Solarfox.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#include "Ennemy.hh"
#include "Solarfox.hh"

arcade::games::Solarfox::Solarfox() : AGame(50, 50), _victim(), gameName("solar_fox")
{
  this->speed = 0.1;
  this->shooted = nullptr;
  this->go_up = true;
  this->next_key = arcade::Keys::NONE;
  this->last_key = arcade::Keys::GO_UP;
  this->death = false;
  this->win = false;
  this->coord = {25.0, 25.0};
  this->score = 0;
  this->chrono = std::chrono::system_clock::now();

  this->enemie = {
	  new Ennemy({1, 47}, 1),
	  new Ennemy({48, 2}, 2),
	  new Ennemy({47, 48}, 3),
	  new Ennemy({2, 1}, 4)
  };
}

arcade::games::Solarfox::~Solarfox()
{
  for (auto e : this->enemie)
    delete e;
}

void arcade::games::Solarfox::KeyAction(arcade::Keys key)
{
  switch (key)
    {
      case arcade::Keys::GO_LEFT:
	{
	  if (this->last_key != arcade::Keys::GO_RIGHT)
	    this->next_key = key;
	  break;
	}
      case arcade::Keys::GO_RIGHT:
	{
	  if (this->last_key != arcade::Keys::GO_LEFT)
	    this->next_key = key;
	  break;
	}
      case arcade::Keys::GO_DOWN:
	{
	  if (this->last_key != arcade::Keys::GO_UP)
	    this->next_key = key;
	  break;
	}
      case arcade::Keys::GO_UP:
	{
	  if (this->last_key != arcade::Keys::GO_DOWN)
	    this->next_key = key;
	  break;
	}
      case arcade::Keys::SHOOT :
	{
	  if (!this->death)
	    {
	      if (this->shooted)
		break;
	      this->shooted = new arcade::games::Shoot(40, 0.15, this->coord, this->last_key);
	      break;
	    }
	  else
	    {
	      this->score = 0;
	      this->speed = 0.1;
	      this->shooted = nullptr;
	      this->go_up = true;
	      this->next_key = arcade::Keys::NONE;
	      this->last_key = arcade::Keys::GO_UP;
	      this->death = false;
	      this->win = false;
	      this->coord = {25.0, 25.0};
	      this->chrono = std::chrono::system_clock::now();
	      this->_victim = Block();

	      for (auto e : this->enemie)
		delete e;

	      this->enemie = {
		      new Ennemy({1, 47}, 1),
		      new Ennemy({48, 2}, 2),
		      new Ennemy({47, 48}, 3),
		      new Ennemy({2, 1}, 4)
	      };

	      break;
	    }
	}
      default:
	break;
    }
}

void arcade::games::Solarfox::UpdateGame()
{
  if (!this->graphic)
    return;

  Vector2<> pos(0, 0);

  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->chrono);

  while (pos.y < 50)
    {
      pos.x = 0;
      while (pos.x < 50)
	{
	  if (pos.y == 0 || pos.y == 49 || pos.x == 0 || pos.x == 49)
	    this->graphic->drawBlock(pos, arcade::Colors::WHITE);
	  pos.x += 1;
	}
      pos.y += 1;
    }

  if (elapsed.count() >= 4)
    {
      if (this->coord.x - (int) this->coord.x == 0 && this->coord.y - (int) this->coord.y == 0)
	this->last_key = this->next_key;

      if (!this->death && !this->win)
	{
	  switch (this->last_key)
	    {
	      case Keys::GO_LEFT :
		{
		  if (this->coord.x - (int) this->coord.x == 0 && this->coord.y - (int) this->coord.y == 0 &&
		      this->coord.x == 3)
		    this->death = true;
		  else
		    this->coord.x = round((this->coord.x - speed) * 10000) / 10000;
		  break;
		}
	      case Keys::GO_RIGHT :
		{
		  if (this->coord.x - (int) this->coord.x == 0 && this->coord.y - (int) this->coord.y == 0 &&
		      this->coord.x == 46)
		    this->death = true;
		  else
		    this->coord.x = round((this->coord.x + speed) * 10000) / 10000;
		  break;
		}
	      case Keys::GO_DOWN :
		{
		  if (this->coord.x - (int) this->coord.x == 0 && this->coord.y - (int) this->coord.y == 0 &&
		      this->coord.y == 46)
		    this->death = true;
		  else
		    this->coord.y = round((this->coord.y + speed) * 10000) / 10000;
		  break;
		}
	      case Keys::GO_UP :
		{
		  if (this->coord.x - (int) this->coord.x == 0 && this->coord.y - (int) this->coord.y == 0 &&
		      this->coord.y == 3)
		    this->death = true;
		  else
		    this->coord.y = round((this->coord.y - speed) * 10000) / 10000;
		  break;
		}
	      default:
		break;
	    }
	  for (auto e : this->enemie)
	    {
	      e->updateEnemy();
	      if (e->checkShoot(this->coord))
		{
		  this->death = true;
		  break;
		}
	    }
	}
      this->chrono = std::chrono::system_clock::now();
    }
  if (this->shooted)
    {
      this->shooted->updateshoot();
      this->shooted->drawshoot(this->graphic, Colors::CYAN);

      std::vector<Vector2<float>> &vic = this->_victim.getPos();

      for (auto it = vic.begin(); it != vic.end(); ++it)
	{
	  if (*it == this->shooted->getPos())
	    {
	      vic.erase(it);
	      this->score += 100;
	      if (static_cast<unsigned int>(this->score) > this->_highscore)
		this->setHighScore(this->score);
	      if (static_cast<unsigned int>(this->score) > this->max_score)
		this->max_score = this->score;
	      if (this->max_score > this->_highscore)
		this->setHighScore(this->max_score);
	      break;
	    }
	}
    }
  this->graphic->drawText({0, 810}, "Score :", 24, arcade::Colors::GREEN);
  this->graphic->drawText({10, 870}, std::to_string(this->score), 24, arcade::Colors::GREEN);

  this->graphic->drawText({200, 810}, "HighScore :", 24, arcade::Colors::GREEN);
  this->graphic->drawText({200, 870}, std::to_string(this->_highscore), 24, arcade::Colors::GREEN);

  auto elapsed_shoot = std::chrono::duration_cast<std::chrono::milliseconds>(this->chrono - now);

  if (this->shooted && this->shooted->_range <= 0)
    {
      delete(this->shooted);
      this->shooted = nullptr;
      this->chrono = std::chrono::system_clock::now();
    }
  for (auto it : this->_victim.getPos())
    this->graphic->drawBlock(it, arcade::Colors::WHITE);

  if (this->death)
    {
      this->graphic->drawText({170, 250}, "GAME", 80, arcade::Colors::MAGENTA);
      this->graphic->drawText({170, 331}, " OVER", 80, arcade::Colors::MAGENTA);
      this->graphic->drawText({130, 450}, "Press SPACE to restart", 20, arcade::Colors::CYAN);
    }
  else if (this->win)
    {
      this->graphic->drawText({60, 450}, "WELL", 60, arcade::Colors::MAGENTA);
      this->graphic->drawText({60, 531}, "PLAYED", 60, arcade::Colors::MAGENTA);
      this->graphic->drawText({30, 850}, "You're fat nerd", 20, arcade::Colors::CYAN);
    }
  else
    {
      for (auto it : this->enemie)
	it->drawEnemy(this->graphic);
    }

  this->graphic->drawBlock(this->coord, arcade::Colors::BLUE);

}

unsigned int arcade::games::Solarfox::getHeight() const
{
  return (900);
}

unsigned int arcade::games::Solarfox::getWidth() const
{
  return (800);
}

const std::string &arcade::games::Solarfox::getGameName() const
{
  return this->gameName;
}

extern "C" arcade::games::IGame *entry_point(void)
{
  return new arcade::games::Solarfox();
}