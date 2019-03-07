/*
** PlayProtocol.hh for cpp_arcade in
**
** Made by florian.marie@epitech.eu
** Login   <florian.marie@epitech.net>
**
** Started on  jeu. avr. 17:23 2017 florian
// Last update Sun Apr  9 16:42:23 2017 Florian Marie
*/

#ifndef CPP_ARCADE_PLAYPROTOCOL_HH
#define CPP_ARCADE_PLAYPROTOCOL_HH

#include <chrono>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include "../../Interfaces/Protocol.hpp"


namespace arcade
{
  namespace game
  {
    class Protocol
    {
      arcade::CommandType	last_key;
      std::vector<Position> pos;
      
     public:
      Protocol();
      ~Protocol();

      void	where();
      void	maped();
      void 	up();
      void	go_up();
      void	down();
      void	go_down();
      void	left();
      void 	go_left();
      void	right();
      void 	go_right();
      void	playround();
      void	forward();
    };
  }
}

#endif //CPP_ARCADE_PLAYPROTOCOL_HH
