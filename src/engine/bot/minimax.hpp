#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>
#include <chrono>
#include <game/game_state.hpp>
#include "engine/board_evaluator.hpp"
#include "engine/rules.hpp"

class Engine;

enum class TTFlag { EXACT, LOWER, UPPER };

struct TTEntry {
    uint64_t key = 0;
    int depth = -1;
    int score = 0;
    TTFlag flag = TTFlag::EXACT;
    int bestFrom = -2;
    int bestTo = -1;
};

class MiniMax{
  public:
    MiniMax(Engine* eng);

    Engine* engine = nullptr;
    BoardEvaluator* eval_board = nullptr;

    void findBestMove();

    int from;
    int to;
    char bot_piece;
    char opp_piece;
    char turn;

    static const int MAX_PLY = 64;

  private:
    int depth_lim;
    std::chrono::steady_clock::time_point search_start;
    long long time_budget_ms;
    bool time_up;
    long long node_count;

    int negamax(int depth, int alpha, int beta);
    int quiescence(int alpha, int beta, int qdepth);
    bool timeCheck();

    struct SearchMove {
        int from;
        int to;
        int score;
    };

    std::vector<SearchMove> generateMoves();
    void scoreMoves(std::vector<SearchMove>& moves, int depth, int ttFrom, int ttTo);

    void applyMove(const SearchMove& move,
                    std::vector<std::pair<int,char>>& savedBoard,
                    std::string& savedGameTurn,
                    int& savedGoatsInHand,
                    int& savedGoatsKilled,
                    char& savedTurn,
                    bool& wasCapture);

    void undoMove(const std::vector<std::pair<int,char>>& savedBoard,
                  const std::string& savedGameTurn,
                  int savedGoatsInHand,
                  int savedGoatsKilled,
                  char savedTurn);

    int killerFrom[MAX_PLY][2];
    int killerTo[MAX_PLY][2];

    int history[2][25][25];

    static const size_t TT_SIZE = 1 << 20;
    std::vector<TTEntry> tt;
    uint64_t computeHash();

    int evaluate_score();

    struct TigerScan {
        int totalMobility = 0;
        int totalCaptures = 0;
        std::vector<int> vulnerableGoatPositions;
        int escapeScore = 0;
        int restriction = 0;
        int danger = 0;
        int centerControl = 0;
        int edgeScore = 0;
    };

    struct PlacementSafety {
        int safe = 0;
        int dangerous = 0;
    };

    int countTigers();
    int countGoats();
    int goatMobility();
    int goatClusters();
    int goatAdvancedPositions();
    int goatBlockingScore();
    TigerScan scanTigers();
    PlacementSafety computePlacementSafety();
};