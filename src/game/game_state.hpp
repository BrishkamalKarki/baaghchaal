#pragma once
#include <string>
#include <vector>

class GameState{
public:
  std::string turn;
  std::string game_won;
  std::vector<std::pair<int, char>> board_state; // 1 - indexed 
  std::vector<int> baagh_trapped_at_pos;
  std::string bot_taken;
  std::string human_taken;
  std::string game_mode;

  std::string player1, player2;

  bool timer_mode;
  int sec_p_move;
  std::string bot_diff_level;
  int move; // CONTINOUSLY COUNT EACH NO OF MOVE
  bool won_by_time_out;

  int goats_in_hand;
  int goats_killed;
  int baagh_trapped;
  bool goats_finished;
  bool clicked_tobe_reloaded = false;
  bool game_paused;
  bool bot_thinking;
  bool audio_loaded;
  bool move_played;

  std::string copied_state;
  std::string copied_bot_taken;
  std::string copied_human_taken;
  std::string copied_player1;
  std::string copied_player2;
  std::string copied_game_mode;
  bool copied_timer_mode;
  int copied_sec_per_move;
  std::string copied_bot_diff_level;




  void resetGameState();
  void saveGameState();
  GameState();
};