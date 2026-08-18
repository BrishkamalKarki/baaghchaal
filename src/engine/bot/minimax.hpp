#pragma once

#include <vector>
#include <string>

#include <SDL3/SDL.h>
#include "engine/rules.hpp"
#include<atomic>

class Engine;
class BoardEvaluator;

class MiniMax {
public:
    Engine* engine = nullptr;
    BoardEvaluator* eval_board = nullptr;

    char bot_piece;
    char opp_piece;

    int from;
    int to;

    int depth_lim;

    struct TigerScoreFactors {
        int ttl_mobility = 0;
        int ttl_capture = 0;
        int esc_score = 0;
        int restriction = 0;
        int danger = 0;
        int center_control = 0;
        int trapped_count = 0;
        int edge_score = 0;
        std::vector<int> vulnerable_goat_pos;
    };

    MiniMax(Engine* eng);
    std::atomic<bool> stop_requested{false};  

    void findBestMove();
    Uint64 think_time;

private:
    static const int ABORT_SCORE = -2000000000;

    // ITERATIVE DEEPENING STATE
    int current_depth = 1;
    bool aborted = false;
    Uint64 search_start = 0;
    int time_budget_ms = 0;

    // STATIC PER-MOVE DATA
    std::vector<bool> danger_map;
    std::vector<int> place_order;
    std::vector<int> center_dist;

    void buildDangerMap();
    void buildPlacementOrder();
    int countGoatNeighbours(int id);
    void fallbackMove();

    int minimax(int depth, bool maximizingPlayer, int alpha, int beta);
    int evaluate_score();

    int countGoats();
    int goatClusters();
    int goatBlockingScore();

    TigerScoreFactors getScoreTiger();
};
