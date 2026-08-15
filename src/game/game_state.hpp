#pragma once
#include <string>
#include <vector>

class GameState{
public:
  std::string turn;
  std::string game_won;
  std::vector<std::pair<int, char>> board_state;
  std::vector<int> baagh_trapped_at_pos;
  std::string bot_taken;
  std::string human_taken;
  std::string game_mode;

  std::string player1, player2;

  bool timer_mode;
  int sec_p_move;
  std::string bot_diff_level;

  int goats_in_hand;
  int goats_killed;
  int baagh_trapped;
  bool goats_finished;
  GameState();
};