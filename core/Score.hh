/*
** Score.hh for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  sam. avr. 18:43 2017 marye_s
** Last update sam. avr. 18:43 2017 marye_s
*/
#ifndef CPP_ARCADE_SCORE_HH
#define CPP_ARCADE_SCORE_HH

#include "../Interfaces/Errors.hpp"
namespace arcade
{
  class Score
  {
   public:

    unsigned int score;
    unsigned int highscore;
    std::string scorefile;

    Score();
    ~Score();

    void	updateHighscore();
    void	getHighscoreFromFile(const std::string &game);
    void	setScore(const unsigned int _score);
  };
}


#endif //CPP_ARCADE_SCORE_HH
