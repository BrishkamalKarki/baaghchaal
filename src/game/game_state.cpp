#include <unordered_set>
#include "game_state.hpp"

GameState::GameState(){
  std::unordered_set<int> baagh_pos = {1, 5, 21, 25};  
  for (int pos = 1; pos <= 25; pos++){
    if (baagh_pos.find(pos) != baagh_pos.end()) board_state.push_back({pos, 'T'});
    else board_state.push_back({pos, ' '});
  }
  turn = "goat";
  baagh_trapped = 0;
  goats_in_hand = 20;
  goats_killed = 0;
  goats_finished = false;
  bot_taken = "goat";
  human_taken = "baagh";
  game_mode = "B V P";
  bot_diff_level = "HARD";

  player1 = "baagh";
  player2 = "goat";

  timer_mode = true;
  sec_p_move = 45;
  int move = 1;
}