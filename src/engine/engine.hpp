#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <utility>

#include "game_config/board_config/board_config.hpp"
#include "game/game_state.hpp"
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

    std::pair<int, int> from_to = {-1, -1};

    explicit Engine(void* game_st, BoardConfig* b_conf);
    MiniMax bot;

    void routeToEngine(int pos, char type = ' ');
    void changePosBaagh();
    void changePosGoat();
    void selectPos(int pos);

    int performBotMove();

    uint32_t bit_board_tigers[10];
    uint32_t bit_board_goats[10];
    int saved = -1;
    std::vector<std::pair<int, char>> board_state; 

    // AFTER THE GOAT OR BAAGH IS MOVED OR PLACED
    Uint64 turn_start_ticks = 0;

    int last_processed_pos = -1;

    void saveBoardState();
    void undoMove();
};