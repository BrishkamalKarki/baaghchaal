#pragma once
#include <string>
#include <vector>

class GameState{
public:
  std::string turn;
  std::string game_won;
  std::vector<std::pair<int, char>> board_state;
  std::vector<int> baagh_trapped_at_pos;

  int goats_in_hand;
  int goats_killed;
  int baagh_trapped;
  bool goats_finished;
  GameState();
};