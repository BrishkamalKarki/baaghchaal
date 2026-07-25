#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>

#include "game_config/board_config/board_config.hpp"
#include "game/game_state.hpp"

class Engine{
public:
  GameState* game_state = nullptr;
  std::string turn;
  std::vector<int> valid_moves;
  Engine(void* game_st);
  void getValidMovesAt(int pos);
};