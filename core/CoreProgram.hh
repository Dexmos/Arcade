/*
** CoreProgram.hh for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  lun. mars 12:07 2017 marye_s
** Last update lun. mars 12:07 2017 florian
*/
#ifndef CPP_ARCADE_COREPROGRAM_HH
#define CPP_ARCADE_COREPROGRAM_HH

#include <vector>
#include <string>
#include <dirent.h>
#include "DLLoader.hpp"
#include "../Interfaces/IGraphics.hh"
#include "../Interfaces/IGames.hh"
#include "Score.hh"

namespace arcade
{
  enum column
  {
    LEFT,
    RIGHT
  };

  class CoreProgram
  {
    std::vector<std::string>	game_libs;
    std::vector<std::string>	graphic_libs;
    size_t 			game_index;
    size_t 			graphic_index;

    DLLoader<arcade::graphics::IGraphic>	*graphic_loader;
    DLLoader<arcade::games::IGame>		*game_loader;

    std::string			*player_name;
    std::string			tmp_player_name;
    size_t 			cursor;

    std::pair<bool, Keys> 	current_key;
    column			curr_column;

    graphics::IGraphic		*graph;
    games::IGame		*game;
    arcade::Score		*score;

   public:
    CoreProgram(std::string to_load);
    ~CoreProgram();
    void	GeneralLoop(std::string lib_name);

   private:
    void	InsertName();
    void	Selection();
    void	HandleGraphicLib();
    void	HandleGameLib();
    void	HandleMenu();
    void	HandleGame();
    void 	RestartGame();
    void	SelectionDisplay();
    void	Selected_Graphic_n_Game();
    arcade::graphics::IGraphic	*ChangeGraphicLib();
    arcade::games::IGame	*ChangeGameLib();
  };
}


#endif //CPP_ARCADE_COREPROGRAM_HH
