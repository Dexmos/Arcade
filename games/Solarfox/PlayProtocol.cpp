/*
** PlayProtocol.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  jeu. avr. 17:23 2017 florian
// Last update Sun Apr  9 17:46:16 2017 Florian Marie
*/

#include "PlayProtocol.hh"

static arcade::CommandType key = arcade::CommandType::GO_RIGHT;

arcade::game::Protocol::Protocol()
{
  this->pos = {
    {10, 10},
  };
  this->last_key = arcade::CommandType::GO_RIGHT;

  for (int i = 0; i < 20 * 20 ; i++)
    this->map.push_back(0);
}

arcade::game::Protocol::~Protocol()
{}

void arcade::game::Protocol::maped()
{
  size_t size;
  GetMap *tmp;
  
  size = sizeof(arcade::GetMap);
  size += 20 * 20 * sizeof(arcade::TileType);
  tmp = reinterpret_cast<GetMap *>(new char[size]);

  tmp->type = CommandType::GET_MAP;
  tmp->width = 20;
  tmp->height = 20;
  for (auto i = 0; i < 20 * 20; i++)
    tmp->tile[i] = static_cast<arcade::TileType> (this->map[i]);
  std::cout.write(reinterpret_cast<char *>(tmp), size);
  delete[] tmp;
}

void arcade::game::Protocol::where()
{
  size_t size;
  WhereAmI *tmp;
  
  size = sizeof(arcade::WhereAmI);
  size += this->pos.size() * sizeof(arcade::Position);
  tmp = reinterpret_cast<WhereAmI *>(new char[size]);

  tmp->type = arcade::CommandType::WHERE_AM_I;
  tmp->lenght = this->pos.size();
  for (int i = 0 ; i < tmp->lenght ; i++)
    tmp->position[i] = this->pos[i];
  std::cout.write(reinterpret_cast<char *>(tmp), size);
  delete[] tmp;
}

void arcade::game::Protocol::down()
{
  this->pos[0].y += 1;
  key = arcade::CommandType::GO_DOWN;
}

void arcade::game::Protocol::go_down()
{
  key = arcade::CommandType::GO_DOWN;
}

void arcade::game::Protocol::up()
{
  this->pos[0].y -= 1;
  key = arcade::CommandType::GO_UP;
}

void arcade::game::Protocol::go_up()
{
  key = arcade::CommandType::GO_UP;
}

void arcade::game::Protocol::left()
{
  this->pos[0].x -= 1;
  key = arcade::CommandType::GO_LEFT;
}

void arcade::game::Protocol::go_left()
{
  key = arcade::CommandType::GO_LEFT;
}

void arcade::game::Protocol::right()
{
  this->pos[0].x += 1;
  key = arcade::CommandType::GO_RIGHT;
}

void arcade::game::Protocol::go_right()
{
  key = arcade::CommandType::GO_RIGHT;
}

void arcade::game::Protocol::shoot()
{
  switch (key)
    {
      case arcade::CommandType::GO_LEFT :
	{
	  this->map[this->pos[0].y * 20 + (this->pos[0].x - 1)] = 5;
	  break;
	}
      case arcade::CommandType::GO_RIGHT :
	{
	  this->map[this->pos[0].y * 20 + (this->pos[0].x + 1)] = 5;
	  break;
	}
      case arcade::CommandType::GO_UP :
	{
	  this->map[(this->pos[0].y - 1) * 20 + this->pos[0].x] = 5;
	  break;
	}
      case arcade::CommandType::GO_DOWN :
	{
	  this->map[(this->pos[0].y + 1) * 20 + this->pos[0].x] = 5;
	  break;
	}
      default:
	break;
    }
}

void arcade::game::Protocol::playround()
{
  switch (key)
    {
      case arcade::CommandType::GO_DOWN:
	{
	  this->down();
	  break;
	}
      case arcade::CommandType::GO_UP:
	{
	  this->up();
	  break;
	}
      case arcade::CommandType::GO_RIGHT:
	{
	  this->right();
	  break;
	}
      case arcade::CommandType::GO_LEFT:
	{
	  this->left();
	  break;
	}
      default:
	break;
    }
}

void arcade::game::Protocol::forward()
{
  this->playround();
}

extern "C" void Play(void)
{
  arcade::game::Protocol play;
  char c;

  while (std::cin.read(&c, sizeof(arcade::CommandType)))
    {
      arcade::CommandType comm = static_cast<arcade::CommandType> (c);

      switch (comm)
	{
	  case arcade::CommandType::WHERE_AM_I:
	    {
	      play.where();
	      break;
	    }
	  case arcade::CommandType::GET_MAP:
	    {
	      play.maped();
	      break;
	    }
	  case arcade::CommandType::GO_DOWN:
	    {
	      play.go_down();
	      break;
	    }
	  case arcade::CommandType::GO_UP:
	    {
	      play.go_up();
	      break;
	    }
	  case arcade::CommandType::GO_RIGHT:
	    {
	      play.go_right();
	      break;
	    }
	  case arcade::CommandType::GO_LEFT:
	    {
	      play.go_left();
	      break;
	    }
	  case arcade::CommandType::PLAY:
	    {
	      play.playround();
	      break;
	    }
	  case arcade::CommandType::GO_FORWARD:
	    {
	      play.forward();
	      break;
	    }
	  case arcade::CommandType::SHOOT :
	    {
	      play.shoot();
	      break;
	    }
	  default :
	    break;
	}
    }
}
