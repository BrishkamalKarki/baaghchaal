#pragma once
#include <string>
#include <vector>

class GameState{
public:
  std::string turn;
  std::string game_won;
  std::vector<std::pair<int, char>> board_state;

  GameState();
};