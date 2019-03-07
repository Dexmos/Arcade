/*
** Block.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.eu>
**
** Started on  sam. avr. 20:18 2017 florian
** Last update sam. avr. 20:18 2017 florian
*/

#include "Block.hh"

arcade::games::Block::Block()
{
  this->_coord = {
	  {20, 14}, {22, 14}, {24, 14}, {26, 14}, {28, 14},
	  {18, 16}, {20, 16}, {22, 16}, {24, 16}, {26, 16}, {28, 16}, {30, 16},
	  {16, 18}, {18, 18}, {20, 18}, {22, 18}, {24, 18}, {26, 18}, {28, 18}, {30, 18}, {32, 18},
	  {14, 20}, {16, 20}, {18, 20},                                                   {30, 20}, {32, 20}, {34, 20},
	  {14, 22}, {16, 22},                                                                       {32, 22}, {34, 22},
	  {14, 24}, {16, 24},                                                                       {32, 24}, {34, 24},
	  {14, 26}, {16, 26},                                                                       {32, 26}, {34, 26},
	  {14, 28}, {16, 28}, {18, 28},                                                   {30, 28}, {32, 28}, {34, 28},
	  {16, 30}, {18, 30}, {20, 30}, {22, 30}, {24, 30}, {26, 30}, {28, 30}, {30, 30}, {32, 30},
	  {18, 32}, {20, 32}, {22, 32}, {24, 32}, {26, 32}, {28, 32}, {30, 32},
	  {20, 34}, {22, 34}, {24, 34}, {26, 34}, {28, 34},

  };
}

arcade::games::Block::~Block()
{}

void arcade::games::Block::setPos()
{}

void arcade::games::Block::isDead()
{}

std::vector<Vector2<float>> &arcade::games::Block::getPos()
{
  return (this->_coord);
}
