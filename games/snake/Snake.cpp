/*
** Snake.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:49 2017 florian
** Last update mer. avr. 19:49 2017 florian
*/

#include "Apple.hh"
#include "Snake.hh"


arcade::games::Snake::Snake() : AGame(30, 30), iphone(this->coord)
{
  this->win = false;
  this->score = 0;
  this->_highscore = 0;
  this->name = "snake";
  this->next_key = arcade::Keys::NONE;
  this->last_key = arcade::Keys::GO_RIGHT;
  this->death = false;
  this->rand_msg = 0;
  this->score = 0;
  this->size_snake = 4;
  this->coord = {
	  {23, 20},
	  {22, 20},
	  {21, 20},
	  {20, 20}
  };
  this->iphone.getRandPos();

  this->chrono = std::chrono::system_clock::now();
}


arcade::games::Snake::~Snake()
{}

void arcade::games::Snake::KeyAction(arcade::Keys key)
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
      case arcade::Keys::SHOOT:
	{
	  {
	    this->next_key = arcade::Keys::NONE;
	    this->last_key = arcade::Keys::GO_RIGHT;
	    this->death = false;
	    this->win = false;
	    this->size_snake = 4;
	    this->score = 0;
	    this->rand_msg = 0;
	    this->coord = {
		    {23, 20},
		    {22, 20},
		    {21, 20},
		    {20, 20}
	    };
	    this->iphone.getRandPos();
	    this->chrono = std::chrono::system_clock::now();
	  }
	  break;
	}
      default:
	break;
    }
}

void arcade::games::Snake::UpdateGame()
{
  if (!this->graphic)
    return;

  Vector2<> pos(0, 0);

  auto now = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->chrono);

  while (pos.y < 30)
    {
      pos.x = 0;
      while (pos.x < 30)
	{
	  if (pos.y == 0 || pos.y == 29 || pos.x == 0 || pos.x == 29)
	    this->graphic->drawBlock(pos, arcade::Colors::WHITE);
	  pos.x += 1;
	}
      pos.y += 1;
    }

  if (elapsed.count() >= 200)
    {

      if (this->next_key == arcade::Keys::GO_RIGHT)
	this->last_key = arcade::Keys::GO_RIGHT;
      if (this->next_key == arcade::Keys::GO_LEFT)
	this->last_key = arcade::Keys::GO_LEFT;
      if (this->next_key == arcade::Keys::GO_UP)
	this->last_key = arcade::Keys::GO_UP;
      if (this->next_key == arcade::Keys::GO_DOWN)
	this->last_key = arcade::Keys::GO_DOWN;

      if (!this->death && !this->win)
	{
	  if (this->last_key == arcade::Keys::GO_LEFT)
	    {
	      if (this->coord[0].x == 1)
		this->death = true;
	      else
		{
		  for (int i = this->coord.size() - 1; i > 0; i--)
		    this->coord[i] = this->coord[i - 1];
		  this->coord[0].x -= 1;
		}
	    }
	  if (this->last_key == arcade::Keys::GO_RIGHT)
	    {
	      if (this->coord[0].x == 28)
		this->death = true;
	      else
		{
		  for (int i = this->coord.size() - 1; i > 0; i--)
		    this->coord[i] = this->coord[i - 1];
		  this->coord[0].x += 1;
		}
	    }
	  if (this->last_key == arcade::Keys::GO_DOWN)
	    {
	      if (this->coord[0].y == 28)
		this->death = true;
	      else
		{
		  for (int i = this->coord.size() - 1; i > 0; i--)
		    this->coord[i] = this->coord[i - 1];
		  this->coord[0].y += 1;
		}
	    }
	  if (this->last_key == arcade::Keys::GO_UP)
	    {
	      if (this->coord[0].y == 1)
		this->death = true;
	      else
		{
		  for (int i = this->coord.size() - 1; i > 0; i--)
		    this->coord[i] = this->coord[i - 1];
		  this->coord[0].y -= 1;
		}
	    }

	  for (int i = this->coord.size() - 1; i > 0; i--)
	    {
	      if (this->coord[0] == this->coord[i])
		this->death = true;
	    }
	}
      this->chrono = std::chrono::system_clock::now();
    }

  if (this->coord[0] == this->iphone.getPos())
    {
      this->size_snake += 1;
      std::srand(std::time(0));
      this->rand_msg = rand() % 10 + 1;
      this->score += 100;
      if (static_cast<unsigned int>(this->score) > this->_highscore)
	this->setHighScore(this->score);
      if (static_cast<unsigned int>(this->score) > this->max_score)
	this->max_score = this->score;
      if (this->max_score > this->_highscore)
	this->setHighScore(this->max_score);
      this->coord.push_back(this->iphone.getPos());
      this->iphone.getRandPos();

      if (this->size_snake == 784)
	this->win = true;
    }

  this->graphic->drawText({5, 480}, "Score :", 24, arcade::Colors::GREEN);
  this->graphic->drawText({5, 500}, std::to_string(this->score), 24, arcade::Colors::GREEN);

  this->graphic->drawText({5, 530}, "Highscore :", 24, arcade::Colors::GREEN);
  this->graphic->drawText({5, 555}, std::to_string(this->_highscore), 24, arcade::Colors::GREEN);


  switch (this->rand_msg)
    {
      case 1:
	{
	  this->graphic->drawText({250, 500}, "SICK MATE", 20, arcade::Colors::GREEN);
	  break;
	}
      case 2:
	{
	  this->graphic->drawText({250, 500}, "El famoso", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " 8h30", 20, arcade::Colors::GREEN);
	  break;
	}
      case 3:
	{
	  this->graphic->drawText({250, 500}, "Karim", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " approuved ;)", 20, arcade::Colors::GREEN);
	  break;
	}
      case 4:
	{
	  this->graphic->drawText({250, 500}, "ALEEEEEEED", 20, arcade::Colors::GREEN);
	  break;
	}
      case 5:
	{
	  this->graphic->drawText({250, 500}, "Auguste et", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " la Piscine", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 541}, "  de synthese", 20, arcade::Colors::GREEN);
	  break;
	}
      case 6:
	{
	  this->graphic->drawText({250, 500}, "1v1 Yasuo", 20, arcade::Colors::GREEN);
	  break;
	}
      case 7:
	{
	  this->graphic->drawText({250, 500}, "Salut le bro", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " c lrb", 20, arcade::Colors::GREEN);
	  break;
	}
      case 8:
	{
	  this->graphic->drawText({250, 500}, "Stop les", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " memes en", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 541}, "  pitch", 20, arcade::Colors::GREEN);
	  break;
	}
      case 9:
	{
	  this->graphic->drawText({250, 500}, "-84", 20, arcade::Colors::GREEN);
	  this->graphic->drawText({250, 521}, " les cheaters", 20, arcade::Colors::GREEN);
	  break;
	}
      case 10:
	{
	  this->graphic->drawText({250, 500}, "Bisous", 20, arcade::Colors::GREEN);
	  break;
	}
    }
  if (this->death)
    {
      if (static_cast<unsigned int>(this->score) > this->max_score)
	this->max_score = this->score;
      this->graphic->drawText({70, 150}, "GAME", 80, arcade::Colors::MAGENTA);
      this->graphic->drawText({70, 231}, " OVER", 80, arcade::Colors::MAGENTA);
      this->graphic->drawText({30, 350}, "Press SPACE to restart", 20, arcade::Colors::CYAN);
    }
  else if (this->win)
    {
      this->graphic->drawText({60, 150}, "WELL", 60, arcade::Colors::MAGENTA);
      this->graphic->drawText({60, 231}, "PLAYED", 60, arcade::Colors::MAGENTA);
      this->graphic->drawText({30, 350}, "gg ez", 20, arcade::Colors::CYAN);
    }
  else
    {
      this->graphic->drawBlock(this->iphone.getPos(), arcade::Colors::RED);
      for (auto it : this->coord)
	this->graphic->drawBlock(it, arcade::Colors::BLUE);
      this->graphic->drawBlock(this->coord[0], arcade::Colors::CYAN);
    }
}

unsigned int arcade::games::Snake::getHeight() const
{
  return (600);
}

unsigned int arcade::games::Snake::getWidth() const
{
  return (500);
}

const std::string& arcade::games::Snake::getGameName() const
{
  return (this->name);
}

extern "C" arcade::games::IGame *entry_point(void)
{
  return new arcade::games::Snake();
}