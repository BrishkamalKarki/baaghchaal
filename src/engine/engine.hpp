#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <vector>

#include "game_config/board_config/board_config.hpp"
#include "game/game_state.hpp"
#include "game_config/board_config/board_config.hpp"
#include "bot/minimax.hpp"
#include "board_evaluator.hpp"

class Engine{
  public:
    GameState* game_state = nullptr;
    BoardConfig* b_conf = nullptr;
    BoardEvaluator board_eval;

    int pos_tiger_etn;
    bool check_trapped;
    std::string turn;

    std::pair<int, int> from_to = {-1, -1}; // STORES THE BOARD POSTION - FROM POSITION TO WHERE THE BAAGH OR BAAKHRA SHOULD MOVE
    Engine(void* game_st, BoardConfig* b_conf);
    MiniMax bot;

    void routeToEngine(int pos, char type = ' '); // KEEPING THE ENGINE IN FLOW
    inline void changePosBaagh();
    inline void changePosGoat();
    inline void selectPos(int pos);
};