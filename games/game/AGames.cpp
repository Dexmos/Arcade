/*
** AGames.cpp for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  mer. avr. 19:49 2017 florian
** Last update mer. avr. 19:49 2017 florian
*/

#include "AGames.hh"

arcade::games::AGame::AGame(const unsigned int width, const unsigned int height) : _width(width), _height(height)
{
  this->graphic = nullptr;
  this->max_score = 0;
  this->_highscore = 0;
}

arcade::games::AGame::~AGame()
{}

void arcade::games::AGame::setGraphics(graphics::IGraphic *graph)
{
  this->graphic = graph;
  this->graphic->defineMapSize(this->_width, this->_height);
}

unsigned int arcade::games::AGame::getScore() const
{
  return (this->max_score);
}

void arcade::games::AGame::setHighScore(const unsigned int &highScore)
{
  this->_highscore = highScore;
}