#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>

#include "game_config/board_config/board_config.hpp"
#include "game/game_state.hpp"
#include "game_config/board_config/board_config.hpp"

class Engine{
public:
  GameState* game_state = nullptr;
  BoardConfig* b_conf = nullptr;

  int pos_tiger_etn;
  bool check_trapped;
  std::string turn;
  std::vector<int> valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
  std::vector<int> bgh_valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
  std::vector<int> temp_valid_moves; // STORES THE VALID MOVE WHEN CLICKED 
  std::vector<std::pair<int, int>> temp_edible_valid_moves; // STORES THE VALID TO EAT A GOAT

  std::vector<std::pair<int, int>> edible_valid_moves; // STORES THE VALID TO EAT A GOAT

  std::pair<int, int> from_to = {-1, -1}; // STORES THE BOARD POSTION - FROM POSITION TO WHERE THE BAAGH OR BAAKHRA SHOULD MOVE
  Engine(void* game_st, BoardConfig* b_conf);
  void routeToEngine(int pos, char type = ' '); // KEEPING THE ENGINE IN FLOW
  int getValidMovesAt(int pos, std::string where = "none"); // GIVES THE VALID MOVES TO MOVE AROUND A POSITION
  inline void changePosBaagh();
  inline void changePosGoat();
  inline void selectPos(int pos);
  inline void checkBaaghTrapped();
};