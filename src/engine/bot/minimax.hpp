#pragma once

#include <vector>
#include <string>

#include "engine/rules.hpp"

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

    struct PlacementSafety {
        int safe      = 0;
        int dangerous = 0;
    };

    explicit MiniMax(Engine* eng);

    void findBestMove();

private:


    int minimax(int depth, bool maximizingPlayer, int alpha, int beta);
    int evaluate_score();

    int countTigers();
    int countGoats();

    int goatClusters();
    int goatBlockingScore();

    TigerScoreFactors getScoreTiger();

    PlacementSafety computePlacementSafety();
};