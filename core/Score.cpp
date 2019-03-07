/*
** Score.cpp for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  sam. avr. 18:43 2017 marye_s
** Last update sam. avr. 18:43 2017 marye_s
*/

#include <fstream>
#include <iostream>
#include "Score.hh"

arcade::Score::Score()
{
  this->score = 0;
  this->highscore = 0;
  this->scorefile = "";
}

arcade::Score::~Score()
{}

void arcade::Score::updateHighscore()
{
  std::fstream	score_file;

  score_file.open(this->scorefile, std::fstream::out | std::fstream::trunc);

  if (!score_file)
    throw arcade::Errors("Could not open the file containing the score\n");

  score_file << this->score << std::endl;
  score_file.close();
}

void	arcade::Score::getHighscoreFromFile(const std::string &game)
{
  std::fstream score_file;

  this->scorefile = "./assets/" + game + ".txt";

  score_file.open(this->scorefile, std::fstream::in | std::fstream::app);

  if (!score_file)
    {
      score_file.open(this->scorefile, std::fstream::out | std::fstream::trunc);

      if (!score_file)
	throw arcade::Errors("Could not create the file to save the highscore\n");
      score_file << "\n";
      score_file.close();
      this->highscore = 0;
      return ;
    }
  score_file >> this->highscore;
  score_file.close();
}

void arcade::Score::setScore(const unsigned int _score)
{
  this->score = _score;

  if (this->score > highscore)
    this->highscore = this->score;
}