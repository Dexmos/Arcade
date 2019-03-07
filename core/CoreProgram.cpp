/*
** CoreProgram.cpp for cpp_arcade in
**
** Made by salome.marye@epitech.eu
** Login   <salome.marye@epitech.eu>
**
** Started on  lun. mars 12:07 2017 marye_s
** Last update lun. mars 12:07 2017 florian
*/
#include "CoreProgram.hh"

arcade::CoreProgram::CoreProgram(std::string to_load)
{
  DIR *directory;

  auto lambda = [this, to_load](DIR *directory, int i) {
    dirent *dir;

    while ((dir = readdir(directory)) != nullptr)
      {
	std::string curr_name(dir->d_name);
	std::size_t found = curr_name.find(".so");

	if (found != std::string::npos && found == curr_name.size() - 3)
	  {
	    curr_name = (i == 1) ? "./games/" + curr_name : "./lib/" + curr_name;
	    if (i == 1)
	      {
		this->game_libs.push_back(curr_name);
	      }
	    else
	      {
		this->graphic_libs.push_back(curr_name);
		if (curr_name == to_load || curr_name == "./" + to_load)
		  this->graphic_index = this->graphic_libs.size() - 1;
	      }
	  }
      }
  };

  if ((directory = opendir("./games/")) == nullptr)
    throw arcade::Errors("Could not open the ./games/ directory\n");
  lambda(directory, 1);
  closedir(directory);

  if ((directory = opendir("./lib/")) == nullptr)
    throw arcade::Errors("Could not open the ./lib/ directory\n");
  lambda(directory, 2);
  closedir(directory);

  if (this->graphic_libs.size() == 0 || this->game_libs.size() == 0)
    throw arcade::Errors("Arcade cannot run without at least a graphic and a game library\n");

  this->score = new arcade::Score();
  this->cursor = 0;
  this->curr_column = RIGHT;
  this->game_index = 0;
  this->current_key.first = false;
  this->current_key.second = arcade::Keys::NONE;
  this->tmp_player_name = "AAA";
  this->game_loader = nullptr;
  this->player_name = nullptr;
  this->graph = nullptr;
  this->game = nullptr;
}

arcade::CoreProgram::~CoreProgram()
{
  if (this->graphic_loader)
    delete (graphic_loader);
  if (this->game_loader)
    delete (this->game_loader);
  if (this->player_name)
    delete(this->player_name);
  if (this->score)
    delete(this->score);
}

void arcade::CoreProgram::HandleGraphicLib()
{
  delete (this->graph);
  this->graph = nullptr;
  this->graph = this->ChangeGraphicLib();

  if (this->game)
    {
      this->game->setGraphics(this->graph);
      this->graph->openWindow(this->game->getWidth(), this->game->getHeight());
    }
  else
    this->graph->openWindow(900, 900);
}

void arcade::CoreProgram::HandleGameLib()
{
  if (this->game->getScore() > this->score->highscore)
    {
      this->score->score = this->game->getScore();
      this->score->updateHighscore();
    }
  delete (this->game);
  this->game = nullptr;
  this->game = this->ChangeGameLib();

  delete (this->graph);
  this->graph = nullptr;
  this->graph = this->graphic_loader->getInstance();

  this->score->getHighscoreFromFile(this->game->getGameName());
  this->game->setHighScore(this->score->highscore);
  this->game->setGraphics(this->graph);
  this->graph->openWindow(this->game->getWidth(), this->game->getHeight());
}

void arcade::CoreProgram::HandleMenu()
{
  if (this->player_name == nullptr)
    this->InsertName();
  else
    this->Selection();
}

void arcade::CoreProgram::HandleGame()
{
  this->game->UpdateGame();
  if (this->current_key.second == arcade::Keys::BACK_MENU)
    {
      if (this->game->getScore() > this->score->highscore)
	{
	  this->score->score = this->game->getScore();
	  this->score->updateHighscore();
	}
      delete (this->game);
      this->game = nullptr;
      delete (this->game_loader);
      this->game_loader = nullptr;
      delete (this->graph);
      this->graph = nullptr;
      this->graph = this->graphic_loader->getInstance();
      this->graph->openWindow(900, 900);
    }
  if (this->game)
    this->game->KeyAction(this->current_key.second);
}

void arcade::CoreProgram::RestartGame()
{
  if (this->game->getScore() > this->score->highscore)
    {
      this->score->score = this->game->getScore();
      this->score->updateHighscore();
    }
  delete (this->game);
  this->game = nullptr;
  this->game = this->game_loader->getInstance();
  this->score->getHighscoreFromFile(this->game->getGameName());
  this->game->setHighScore(this->score->highscore);

  this->game->setGraphics(this->graph);
}

void arcade::CoreProgram::GeneralLoop(std::string lib_name)
{
  this->graphic_loader = new DLLoader<arcade::graphics::IGraphic>(lib_name);

  this->graph = this->graphic_loader->getInstance();
  this->game = nullptr;

  this->graph->openWindow(900, 900);
  while ((this->current_key.second = this->graph->getKeys()) != arcade::Keys::EXIT
	 && this->graph->isWindowOpen())
    {
      this->current_key.first = false;

      this->graph->clearWindow();
      if (this->current_key.first == false
	  && (this->current_key.second == arcade::Keys::NEXT_GRAPH_LIB
	      || this->current_key.second == arcade::Keys::PREV_GRAPH_LIB))
	this->HandleGraphicLib();
      if (this->current_key.first == false
	  && (this->current_key.second == arcade::Keys::NEXT_GAME
	      || this->current_key.second == arcade::Keys::PREV_GAME))
	this->HandleGameLib();
      if (this->current_key.first == false
	  && this->current_key.second == arcade::Keys::RESTART)
	this->RestartGame();
      if (this->game_loader == nullptr && this->current_key.first == false)
	this->HandleMenu();
      if (this->current_key.first == false && game == nullptr)
	{
	  this->graph = this->graphic_loader->getInstance();
	  this->game = this->game_loader->getInstance();
	  this->score->getHighscoreFromFile(this->game->getGameName());
	  this->game->setHighScore(this->score->highscore);
	}
      else if (this->current_key.first == false)
	this->HandleGame();
      this->graph->updateWindow();
    }
}

arcade::graphics::IGraphic* arcade::CoreProgram::ChangeGraphicLib()
{
  if (this->current_key.second == arcade::Keys::NEXT_GRAPH_LIB)
    {
      if (this->graphic_index < this->graphic_libs.size() - 1)
	this->graphic_index += 1;
      else
	this->graphic_index = 0;
    }
  else
    {
      if (this->graphic_index > 0)
	this->graphic_index -= 1;
      else
	this->graphic_index = this->graphic_libs.size() - 1;
    }
  delete(this->graphic_loader);
  this->graphic_loader = nullptr;
  this->graphic_loader = new DLLoader<arcade::graphics::IGraphic>(this->graphic_libs[this->graphic_index]);
  this->current_key.first = true;
  return (this->graphic_loader->getInstance());
}

arcade::games::IGame* arcade::CoreProgram::ChangeGameLib()
{
  if (this->current_key.second == arcade::Keys::NEXT_GAME)
    {
      if (this->game_index < this->game_libs.size() - 1)
	this->game_index += 1;
      else
	this->game_index= 0;
    }
  else
    {
      if (this->game_index > 0)
	this->game_index -= 1;
      else
	this->game_index = this->game_libs.size() - 1;
    }
  delete(this->game_loader);
  this->game_loader = nullptr;
  this->game_loader = new DLLoader<arcade::games::IGame>(this->game_libs[this->game_index]);
  this->current_key.first = true;
  return (this->game_loader->getInstance());
}

void arcade::CoreProgram::SelectionDisplay()
{
  this->graph->drawText(Vector2<>(90, 10), *this->player_name + " CHOSE YOUR GRAPHIC AND GAME", 25, arcade::Colors::CYAN);
  this->graph->drawText(Vector2<>(100, 70), "GRAPHICS", 25, arcade::Colors::CYAN);
  this->graph->drawText(Vector2<>(550, 70), "GAMES", 25, arcade::Colors::CYAN);
  this->graph->drawLine(Vector2<>(450, 70), Vector2<>(450, 900), arcade::Colors::CYAN);
  size_t	i = 50;

  for (size_t to_turn = 0 ; to_turn <= this->graphic_libs.size() - 1; to_turn += 1)
    {
      std::string to_display = this->graphic_libs[to_turn].substr(6, this->graphic_libs[to_turn].size() - 9);
      if (to_turn != this->graphic_index)
	this->graph->drawText(Vector2<>(10, i + 100), to_display, 18, arcade::Colors::CYAN);
      else
	this->graph->drawText(Vector2<>(10, i + 100), to_display, 18, arcade::Colors::BLUE);
      i += 40;
    }
  i = 50;
  if (game_libs.size() != 0)
    {
      for (size_t to_turn = 0; to_turn <= this->game_libs.size() - 1; to_turn += 1)
	{
	  std::string to_display2 = this->game_libs[to_turn].substr(8, this->game_libs[to_turn].size() - 11);
	  if (to_turn != this->game_index)
	    this->graph->drawText(Vector2<>(480, i + 100), to_display2, 18, arcade::Colors::CYAN);
	  else
	    this->graph->drawText(Vector2<>(480, i + 100), to_display2, 18, arcade::Colors::BLUE);
	  i += 40;
	}
    }
}

void arcade::CoreProgram::Selected_Graphic_n_Game()
{
  delete this->graph;
  delete this->graphic_loader;

  this->graphic_loader = nullptr;

  this->graphic_loader = new DLLoader<arcade::graphics::IGraphic>(this->graphic_libs[this->graphic_index]);
  this->graph = this->graphic_loader->getInstance();

  this->game_loader = new DLLoader<arcade::games::IGame>(this->game_libs[this->game_index]);
  this->game = this->game_loader->getInstance();
  this->score->getHighscoreFromFile(this->game->getGameName());
  this->game->setHighScore(this->score->highscore);
  this->game->setGraphics(this->graph);

  this->graph->openWindow(this->game->getWidth(), this->game->getHeight());
}

void arcade::CoreProgram::Selection()
{
  auto incr_indexes = [this](int i)
  {
    if (i == 1)
      {
	if (this->game_index < this->game_libs.size() - 1)
	  this->game_index += 1;
	else
	  this->game_index = 0;
      }
    else
      {
	if (this->graphic_index < this->graphic_libs.size() - 1)
	  this->graphic_index += 1;
	else
	  this->graphic_index = 0;
      }
  };

  auto desc_indexes = [this](int i)
  {
    if (i == 1)
      {
	if (this->game_index > 0)
	  this->game_index -= 1;
	else
	  this->game_index = this->game_libs.size() - 1;
      }
    else
      {
	if (this->graphic_index > 0)
	  this->graphic_index -= 1;
	else
	  this->graphic_index = this->graphic_libs.size() - 1;
      }
  };

  switch (this->current_key.second)
    {
      case arcade::Keys::GO_DOWN :
	{
	  if (this->curr_column == RIGHT)
	    incr_indexes(1);
	  else
	    incr_indexes(2);

	  break;
	}
      case arcade::Keys::GO_UP :
	{
	  if (this->curr_column == RIGHT)
	    desc_indexes(1);
	  else
	    desc_indexes(2);
	  break;
	}
      case arcade::Keys::GO_LEFT:
	{
	  this->curr_column = LEFT;
	  break;
	}
      case arcade::Keys::GO_RIGHT:
	{
	  this->curr_column = RIGHT;
	  break;
	}
      case arcade::Keys::SHOOT:
	{
	  this->Selected_Graphic_n_Game();
	  break;
	}
      default:
	break;
    }

  this->SelectionDisplay();
  this->current_key.first = true;
}

void arcade::CoreProgram::InsertName()
{
  this->graph->drawText(Vector2<>(300, 0), "ARCADE", 50, arcade::Colors::CYAN);
  this->graph->drawText(Vector2<>(130, 80), "PLEASE ENTER YOUR NAME", 30, arcade::Colors::CYAN);
  this->graph->drawText(Vector2<>(350, 400), tmp_player_name, 70, arcade::Colors::CYAN);
  switch (this->current_key.second)
    {
      case arcade::Keys::SHOOT :
	{
	  this->player_name = new std::string(this->tmp_player_name);
	  break;
	}
      case arcade::Keys::GO_RIGHT :
	{
	  if (this->cursor + 1 < this->tmp_player_name.size())
	    this->cursor += 1;
	  break;
	}
      case arcade::Keys::GO_LEFT :
	{
	  if (this->cursor - 1 < static_cast<unsigned int>(-1))
	    this->cursor -= 1;
	  break;
	}
      case arcade::Keys::GO_DOWN :
	{
	  if (this->tmp_player_name[this->cursor] == 'Z')
	    this->tmp_player_name[this->cursor] = 'A';
	  else
	    this->tmp_player_name[this->cursor] = this->tmp_player_name[this->cursor] + 1;
	  break;
	}
      case arcade::Keys::GO_UP :
	{
	  if (this->tmp_player_name[this->cursor] == 'A')
	    this->tmp_player_name[this->cursor] = 'Z';
	  else
	    this->tmp_player_name[this->cursor] = this->tmp_player_name[this->cursor] - 1;
	  break;
	}
      default:
	break;
    }
  this->current_key.first = true;
  return;
}