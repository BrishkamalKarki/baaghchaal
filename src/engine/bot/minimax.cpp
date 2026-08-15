#include "minimax.hpp"

#include <SDL3/SDL.h>
#include <limits>
#include <cmath>
#include <algorithm>
#include <cstring>

#include "engine/engine.hpp"

static const int WIN_SCORE = 10000000;

MiniMax::MiniMax(Engine* eng)
{
    engine = eng;
    eval_board = &engine->board_eval;

    bot_piece = ' ';
    opp_piece = ' ';
    turn = ' ';

    from = -1;
    to = -1;

    depth_lim = 4;
    time_budget_ms = 2000;
    time_up = false;
    node_count = 0;

    memset(killerFrom, 0, sizeof(killerFrom));
    memset(killerTo, 0, sizeof(killerTo));
    memset(history, 0, sizeof(history));

    tt.resize(TT_SIZE);
}



void MiniMax::findBestMove()
{
    SDL_Log("========== MINIMAX START ==========");

    std::vector<std::pair<int, char>> saved_board = engine->game_state->board_state;
    std::string saved_game_turn = engine->game_state->turn;
    int saved_goats_in_hand = engine->game_state->goats_in_hand;
    int saved_goats_killed  = engine->game_state->goats_killed;

    bot_piece = engine->game_state->bot_taken == "goat" ? 'G' : 'T';
    opp_piece = bot_piece == 'G' ? 'T' : 'G';

    memset(killerFrom, 0, sizeof(killerFrom));
    memset(killerTo, 0, sizeof(killerTo));
    for (int s = 0; s < 2; s++)
        for (int f = 0; f < 25; f++)
            for (int t = 0; t < 25; t++)
                history[s][f][t] /= 2; 

    search_start = std::chrono::steady_clock::now();
    node_count = 0;

    int best_from = -1, best_to = -1;

    for (int d = 2; d <= 16; d += 2){ 
        turn = bot_piece;
        from = -2;
        to = -1;
        time_up = false;
        depth_lim = d;

        int alpha = -WIN_SCORE - 1;
        int beta  =  WIN_SCORE + 1;

        int score = negamax(0, alpha, beta);

        engine->game_state->board_state = saved_board;
        engine->game_state->turn = saved_game_turn;
        engine->game_state->goats_in_hand = saved_goats_in_hand;
        engine->game_state->goats_killed  = saved_goats_killed;

        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - search_start).count();

        bool depthCompleted = (from != -2) && !time_up;

        if (depthCompleted){
            best_from = from;
            best_to = to;
            SDL_Log("Depth %d complete | score=%d | from=%d | to=%d | elapsed=%lldms | nodes=%lld",
                    d, score, best_from, best_to, (long long)elapsed, node_count);
        }
        else if (from != -2){
            best_from = from;
            best_to = to;
            SDL_Log("Depth %d partial (time up) | using from=%d | to=%d", d, best_from, best_to);
        }

        if (elapsed > time_budget_ms || time_up){
            SDL_Log("Time budget reached, stopping at depth %d", d);
            break;
        }
    }

    from = best_from;
    to = best_to;

    SDL_Log("MINIMAX RESULT | from=%d | to=%d", from, to);

    engine->game_state->board_state = saved_board;
    engine->game_state->turn = saved_game_turn;
    engine->game_state->goats_in_hand = saved_goats_in_hand;
    engine->game_state->goats_killed  = saved_goats_killed;

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();

    SDL_Log ("MINIMAX END" );
}


bool MiniMax::timeCheck()
{
    if ((++node_count & 1023) == 0){
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - search_start).count();
        if (elapsed >= time_budget_ms){
            time_up = true;
        }
    }
    return time_up;
}



uint64_t MiniMax::computeHash()
{
    uint64_t h = 1469598103934665603ULL; 
    for (auto& [id, piece] : engine->game_state->board_state){
        uint64_t v = (piece == 'T') ? 1 : (piece == 'G' ? 2 : 0);
        h ^= v;
        h *= 1099511628211ULL; 
    }
    h ^= (turn == 'T' ? 1ULL : 2ULL);
    h *= 1099511628211ULL;
    h ^= static_cast<uint64_t>(engine->game_state->goats_in_hand);
    h *= 1099511628211ULL;
    return h;
}


void MiniMax::applyMove(const SearchMove& move,
                         std::vector<std::pair<int,char>>& savedBoard,
                         std::string& savedGameTurn,
                         int& savedGoatsInHand,
                         int& savedGoatsKilled,
                         char& savedTurn,
                         bool& wasCapture)
{
    savedBoard = engine->game_state->board_state;
    savedGameTurn = engine->game_state->turn;
    savedGoatsInHand = engine->game_state->goats_in_hand;
    savedGoatsKilled = engine->game_state->goats_killed;
    savedTurn = turn;
    wasCapture = false;

    engine->game_state->turn = (turn == 'T') ? "baagh" : "goat";

    if (turn == 'G' && move.from == -1)
    {
        engine->game_state->board_state[move.to].second = 'G';
        engine->game_state->goats_in_hand--;
        turn = 'T';
    }
    else
    {
        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        eval_board->getValidMovesAt(move.from);

        engine->game_state->board_state[move.from].second = ' ';
        engine->game_state->board_state[move.to].second = turn;

        if (turn == 'T'){
            for (const auto& [goat_pos, landing_pos] : eval_board->edible_valid_moves){
                if (landing_pos == move.to){
                    engine->game_state->board_state[goat_pos].second = ' ';
                    engine->game_state->goats_killed++;
                    wasCapture = true;
                    break;
                }
            }
        }

        turn = (turn == 'T') ? 'G' : 'T';
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();
}

void MiniMax::undoMove(const std::vector<std::pair<int,char>>& savedBoard,
                        const std::string& savedGameTurn,
                        int savedGoatsInHand,
                        int savedGoatsKilled,
                        char savedTurn)
{
    engine->game_state->board_state = savedBoard;
    engine->game_state->turn = savedGameTurn;
    engine->game_state->goats_in_hand = savedGoatsInHand;
    engine->game_state->goats_killed = savedGoatsKilled;
    turn = savedTurn;
}



std::vector<MiniMax::SearchMove> MiniMax::generateMoves()
{
    std::vector<SearchMove> moves;

    if (turn == 'G' && engine->game_state->goats_in_hand > 0)
    {
        for (auto& [id, piece] : engine->game_state->board_state){
            if (piece != ' ') continue;
            moves.push_back({ -1, id - 1, 0 });
        }
    }
    else
    {
        for (auto& [id, piece] : engine->game_state->board_state){
            if (piece != turn) continue;

            int start_pos = id - 1;

            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            engine->game_state->turn = (turn == 'T') ? "baagh" : "goat";
            eval_board->getValidMovesAt(start_pos);

            for (int destination : eval_board->valid_moves){
                moves.push_back({ start_pos, destination, 0 });
            }
        }
        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
    }

    return moves;
}



void MiniMax::scoreMoves(std::vector<SearchMove>& moves, int depth, int ttFrom, int ttTo)
{
    int sideIdx = (turn == 'T') ? 1 : 0;

    for (auto& move : moves){
        if (move.from == ttFrom && move.to == ttTo){
            move.score = 10000000;
            continue;
        }

        if (turn == 'T' && move.from != -1){
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            eval_board->getValidMovesAt(move.from);
            bool isCap = false;
            for (const auto& [goat_pos, landing_pos] : eval_board->edible_valid_moves){
                if (landing_pos == move.to){ isCap = true; break; }
            }
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            if (isCap){
                move.score = 1000000;
                continue;
            }
        }

        if (depth < MAX_PLY){
            if (move.from == killerFrom[depth][0] && move.to == killerTo[depth][0]){
                move.score = 900000;
                continue;
            }
            if (move.from == killerFrom[depth][1] && move.to == killerTo[depth][1]){
                move.score = 800000;
                continue;
            }
        }

        int f = (move.from == -1) ? move.to : move.from; 
        int t = move.to;
        move.score = history[sideIdx][f][t];
    }
}


int MiniMax::negamax(int depth, int alpha, int beta)
{
    if (timeCheck())
        return 0;

    engine->game_state->turn = (turn == 'T') ? "baagh" : "goat";

    std::string winner_string = eval_board->checkWinner();

    if (winner_string == "goat")
        return (turn == 'G') ? (WIN_SCORE - depth) : -(WIN_SCORE - depth);

    if (winner_string == "baagh")
        return (turn == 'T') ? (WIN_SCORE - depth) : -(WIN_SCORE - depth);

    if (depth >= depth_lim)
        return quiescence(alpha, beta, 4);

    uint64_t key = computeHash();
    size_t ttIdx = static_cast<size_t>(key) & (TT_SIZE - 1);
    TTEntry& entry = tt[ttIdx];
    int ttFrom = -2, ttTo = -1;

    int origAlpha = alpha, origBeta = beta;
    int remaining = depth_lim - depth;

    if (entry.key == key){
        ttFrom = entry.bestFrom;
        ttTo = entry.bestTo;

        if (entry.depth >= remaining){
            if (entry.flag == TTFlag::EXACT) return entry.score;
            if (entry.flag == TTFlag::LOWER) alpha = std::max(alpha, entry.score);
            if (entry.flag == TTFlag::UPPER) beta  = std::min(beta,  entry.score);
            if (alpha >= beta) return entry.score;
        }
    }

    std::vector<SearchMove> moves = generateMoves();

    if (moves.empty()){
        return -(WIN_SCORE - depth);
    }

    scoreMoves(moves, depth, ttFrom, ttTo);

    int bestScore = -WIN_SCORE - 1;
    int bestFrom = moves[0].from, bestTo = moves[0].to;
    TTFlag flag = TTFlag::UPPER;
    int movesSearched = 0;

    for (size_t i = 0; i < moves.size(); i++){
        size_t bestIdx = i;
        for (size_t j = i + 1; j < moves.size(); j++)
            if (moves[j].score > moves[bestIdx].score) bestIdx = j;
        if (bestIdx != i) std::swap(moves[i], moves[bestIdx]);

        const SearchMove& move = moves[i];

        std::vector<std::pair<int,char>> savedBoard;
        std::string savedGameTurn;
        int savedGoatsInHand, savedGoatsKilled;
        char savedTurn;
        bool wasCapture;

        applyMove(move, savedBoard, savedGameTurn, savedGoatsInHand, savedGoatsKilled, savedTurn, wasCapture);

        int val;
        int reduction = 0;

        if (movesSearched >= 4 && remaining >= 3 && !wasCapture){
            reduction = 1;
            if (movesSearched >= 10) reduction = 2;
        }

        if (movesSearched == 0){
            val = -negamax(depth + 1, -beta, -alpha);
        }
        else{
            val = -negamax(depth + 1 + reduction, -alpha - 1, -alpha);

            if (reduction > 0 && val > alpha && !time_up)
                val = -negamax(depth + 1, -alpha - 1, -alpha); 

            if (val > alpha && val < beta && !time_up)
                val = -negamax(depth + 1, -beta, -alpha);
        }

        undoMove(savedBoard, savedGameTurn, savedGoatsInHand, savedGoatsKilled, savedTurn);
        movesSearched++;

        if (time_up) return 0;

        if (val > bestScore){
            bestScore = val;
            bestFrom = move.from;
            bestTo = move.to;
        }

        if (val > alpha){
            alpha = val;
            flag = TTFlag::EXACT;
            if (depth == 0){
                from = move.from;
                to = move.to;
            }
        }

        if (alpha >= beta){
            flag = TTFlag::LOWER;
            if (!wasCapture && depth < MAX_PLY){
                killerFrom[depth][1] = killerFrom[depth][0];
                killerTo[depth][1] = killerTo[depth][0];
                killerFrom[depth][0] = move.from;
                killerTo[depth][0] = move.to;

                int sideIdx = (turn == 'T') ? 0 : 1; 
                int f = (move.from == -1) ? move.to : move.from;
                history[sideIdx][f][move.to] += remaining * remaining;
            }
            break;
        }
    }

    if (!time_up){
        entry.key = key;
        entry.score = bestScore;
        entry.bestFrom = bestFrom;
        entry.bestTo = bestTo;
        entry.depth = remaining;
        entry.flag = flag;
    }

    (void)origAlpha; (void)origBeta;
    return bestScore;
}

int MiniMax::quiescence(int alpha, int beta, int qdepth)
{
    if (timeCheck())
        return 0;

    int standPat = evaluate_score();

    if (standPat >= beta) return beta;
    if (standPat > alpha) alpha = standPat;

    if (turn != 'T' || qdepth <= 0)
        return alpha;

    for (auto& [id, piece] : engine->game_state->board_state){
        if (piece != 'T') continue;
        int start = id - 1;

        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        engine->game_state->turn = "baagh";
        eval_board->getValidMovesAt(start);

        std::vector<std::pair<int,int>> local_captures = eval_board->edible_valid_moves;

        for (auto& [goat_pos, landing_pos] : local_captures){
            std::vector<std::pair<int, char>> savedBoard = engine->game_state->board_state;
            int savedGoatsKilled = engine->game_state->goats_killed;
            char savedTurn = turn;

            engine->game_state->board_state[start].second = ' ';
            engine->game_state->board_state[landing_pos].second = 'T';
            engine->game_state->board_state[goat_pos].second = ' ';
            engine->game_state->goats_killed++;

            turn = 'G';
            int val = -quiescence(-beta, -alpha, qdepth - 1);
            turn = savedTurn;

            engine->game_state->board_state = savedBoard;
            engine->game_state->goats_killed = savedGoatsKilled;

            if (val >= beta){
                eval_board->valid_moves.clear();
                eval_board->edible_valid_moves.clear();
                return beta;
            }
            if (val > alpha) alpha = val;
        }
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();

    return alpha;
}


int MiniMax::evaluate_score()
{
    const int goats_killed = engine->game_state->goats_killed;
    const int tigers = countTigers();
    const int goats  = countGoats();

    const TigerScan scan = scanTigers();

    const int t_mob            = scan.totalMobility;
    const int captures         = scan.totalCaptures;
    const int vulnerable       = static_cast<int>(scan.vulnerableGoatPositions.size());
    const int center           = scan.centerControl;
    const int escape           = scan.escapeScore;
    const int restriction      = scan.restriction;
    const int edge             = scan.edgeScore;
    const int immediateDanger  = scan.danger;

    const int g_mob = goatMobility();
    const int trapped = engine->game_state->baagh_trapped;

    const int clusters = goatClusters();
    const int advanced = goatAdvancedPositions();
    const int blocking = goatBlockingScore();

    const PlacementSafety placement = computePlacementSafety();
    const int safePlacements       = placement.safe;
    const int dangerousPlacements  = placement.dangerous;

    const bool placementPhase = engine->game_state->goats_in_hand > 0;

    int score = 0; // positive = good for TIGER

    score += goats_killed * Scores::GOATS_KILLED;

    score += t_mob * Scores::TIGER_MOBILITY;
    score += captures * Scores::TIGER_CAPTURE;
    score -= trapped * Scores::TIGER_TRAPPED;
    score += center * Scores::TIGER_CENTER;
    score += escape * Scores::TIGER_ESCAPE;
    score += edge * Scores::TIGER_EDGE;

    score -= g_mob * Scores::GOAT_MOBILITY;
    score += vulnerable * Scores::GOAT_VULNERABLE;
    score += restriction * Scores::GOAT_RESTRICT;
    score -= clusters * Scores::GOAT_CLUSTER;
    score -= advanced * Scores::GOAT_ADVANCED;
    score -= blocking * Scores::GOAT_BLOCKING;

    if (placementPhase){
        score += restriction * 20;
        score += vulnerable * 40;
        score -= dangerousPlacements * Scores::GOAT_DANGER_PLACEMENT;
        score -= safePlacements * Scores::GOAT_SAFE_PLACEMENT;
        score += t_mob * 4;
    }
    else{
        score -= trapped * 150;
        score += captures * 35;
        score += immediateDanger * 100;
        score -= g_mob * 4;
    }

    score += tigers * 3;
    score -= goats * 1;

    return (turn == 'T') ? score : -score;
}



int MiniMax::countTigers()
{
    int count = 0;
    for (const auto& [id, type] : engine->game_state->board_state)
        if (type == 'T') count++;
    return count;
}

int MiniMax::countGoats()
{
    int count = 0;
    for (const auto& [id, type] : engine->game_state->board_state)
        if (type == 'G') count++;
    return count;
}

int MiniMax::goatMobility()
{
    if (engine->game_state->goats_in_hand > 0)
        return 0;

    int mobility = 0;

    for (const auto& [id, type] : engine->game_state->board_state){
        if (type != 'G') continue;

        int pos = id - 1;

        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        engine->game_state->turn = "goat";
        eval_board->getValidMovesAt(pos);

        mobility += static_cast<int>(eval_board->valid_moves.size());
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();

    return mobility;
}

int MiniMax::goatClusters()
{
    int clusters = 0;

    for (const auto& [id, type] : engine->game_state->board_state){
        if (type != 'G') continue;

        int pos = id - 1;
        int row = pos / 5;
        int col = pos % 5;

        for (const auto& [other_id, other_type] : engine->game_state->board_state){
            if (other_type != 'G') continue;
            if (other_id <= id) continue;

            int other_pos = other_id - 1;
            int other_row = other_pos / 5;
            int other_col = other_pos % 5;

            int dr = std::abs(row - other_row);
            int dc = std::abs(col - other_col);

            if ((dr == 1 && dc == 0) || (dr == 0 && dc == 1) || (dr == 1 && dc == 1))
                clusters++;
        }
    }

    return clusters;
}

int MiniMax::goatAdvancedPositions()
{
    int score = 0;

    for (const auto& [id, type] : engine->game_state->board_state){
        if (type != 'G') continue;

        int pos = id - 1;
        int row = pos / 5;

        if (row == 2) score += 3;
        else if (row == 1 || row == 3) score += 2;
        else score += 1;
    }

    return score;
}

int MiniMax::goatBlockingScore()
{
    int score = 0;

    for (const auto& [id, type] : engine->game_state->board_state){
        if (type != 'G') continue;

        int goat_pos = id - 1;

        for (const auto& [tiger_id, tiger_type] : engine->game_state->board_state){
            if (tiger_type != 'T') continue;

            int tiger_pos = tiger_id - 1;

            int tr = tiger_pos / 5;
            int tc = tiger_pos % 5;
            int gr = goat_pos / 5;
            int gc = goat_pos % 5;

            int dr = std::abs(tr - gr);
            int dc = std::abs(tc - gc);

            if ((dr == 1 && dc == 0) || (dr == 0 && dc == 1) || (dr == 1 && dc == 1))
                score++;
        }
    }

    return score;
}

MiniMax::TigerScan MiniMax::scanTigers()
{
    TigerScan scan;

    for (const auto& [id, type] : engine->game_state->board_state){
        if (type != 'T') continue;

        int pos = id - 1;

        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        engine->game_state->turn = "baagh";
        eval_board->getValidMovesAt(pos);

        int mobility = static_cast<int>(eval_board->valid_moves.size());
        int capture_count = static_cast<int>(eval_board->edible_valid_moves.size());

        scan.totalMobility += mobility;
        scan.totalCaptures += capture_count;

        for (const auto& [goat_pos, landing_pos] : eval_board->edible_valid_moves){
            (void)landing_pos;
            if (std::find(scan.vulnerableGoatPositions.begin(),
                           scan.vulnerableGoatPositions.end(),
                           goat_pos) == scan.vulnerableGoatPositions.end()){
                scan.vulnerableGoatPositions.push_back(goat_pos);
            }
        }

        int total = mobility + capture_count;

        if (total >= 5)      scan.escapeScore += 5;
        else if (total == 4) scan.escapeScore += 4;
        else if (total == 3) scan.escapeScore += 2;
        else if (total == 2) scan.escapeScore += 0;
        else if (total == 1) scan.escapeScore -= 3;
        else                  scan.escapeScore -= 8;

        if (mobility == 0)      scan.restriction += 6;
        else if (mobility == 1) scan.restriction += 4;
        else if (mobility == 2) scan.restriction += 2;
        else if (mobility == 3) scan.restriction += 1;

        if (capture_count >= 2)      scan.danger += 3;
        else if (capture_count == 1) scan.danger += 1;

        int row = pos / 5;
        int col = pos % 5;
        int center_distance = std::abs(row - 2) + std::abs(col - 2);

        if (center_distance == 0)      scan.centerControl += 4;
        else if (center_distance == 1) scan.centerControl += 3;
        else if (center_distance == 2) scan.centerControl += 1;

        if (row == 0 || row == 4 || col == 0 || col == 4)
            scan.edgeScore -= 1;
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();

    return scan;
}

MiniMax::PlacementSafety MiniMax::computePlacementSafety()
{
    PlacementSafety result;

    if (engine->game_state->goats_in_hand <= 0)
        return result;

    for (auto& [id, piece] : engine->game_state->board_state){
        if (piece != ' ') continue;

        int pos = id - 1;

        engine->game_state->board_state[pos].second = 'G';

        bool vulnerable = false;

        for (const auto& [tiger_id, tiger_type] : engine->game_state->board_state){
            if (tiger_type != 'T') continue;

            int tiger_pos = tiger_id - 1;

            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            engine->game_state->turn = "baagh";
            eval_board->getValidMovesAt(tiger_pos);

            for (const auto& [goat_pos, landing] : eval_board->edible_valid_moves){
                (void)landing;
                if (goat_pos == pos){ vulnerable = true; break; }
            }

            if (vulnerable) break;
        }

        engine->game_state->board_state[pos].second = ' ';

        if (vulnerable) result.dangerous++;
        else            result.safe++;
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();

    return result;
}