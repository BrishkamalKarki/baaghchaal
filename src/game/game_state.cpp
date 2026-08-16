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
  game_mode = "";
  bot_diff_level = "HARD";

  won_by_time_out = false;

  player1 = "baagh";
  player2 = "goat";
  bot_thinking = false;
  game_paused = false;

  timer_mode = true;
  sec_p_move = 45;
  move = 1;
  saveGameState();
}

void GameState::resetGameState(){
  board_state.clear();
  std::unordered_set<int> baagh_pos = {1, 5, 21, 25};  
  for (int pos = 1; pos <= 25; pos++){
    if (baagh_pos.find(pos) != baagh_pos.end()) board_state.push_back({pos, 'T'});
    else board_state.push_back({pos, ' '});
  }
  move = 1;
  turn = "goat";
    baagh_trapped = 0;
  goats_in_hand = 20;
  goats_killed = 0;
  goats_finished = false;
  bot_taken = "goat";
  human_taken = "baagh";
  game_mode = "";
  bot_diff_level = "HARD";

  won_by_time_out = false;

  player1 = "baagh";
  player2 = "goat";
  bot_thinking = false;
  game_paused = false;

  timer_mode = true;
  sec_p_move = copied_sec_per_move;

  bot_taken = copied_bot_taken;
  human_taken = copied_human_taken;
  player1 = copied_player1;
  player2 = copied_player2;
  game_mode = copied_game_mode;
  timer_mode = copied_timer_mode;
  sec_p_move = copied_sec_per_move;
  bot_diff_level = copied_bot_diff_level;
}

void GameState::saveGameState(){
  copied_bot_taken = bot_taken;
  copied_human_taken = human_taken;
  copied_player1 = player1;
  copied_player2 = player2;
  copied_game_mode = game_mode;
  copied_timer_mode = timer_mode;
  copied_sec_per_move = sec_p_move;
  copied_bot_diff_level = bot_diff_level;
}