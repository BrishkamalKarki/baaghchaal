#include "minimax.hpp"

#include <SDL3/SDL.h>

#include <limits>
#include <cmath>
#include <algorithm>

#include "engine/engine.hpp"


static const int WIN_SCORE = 10000000;

MiniMax::MiniMax(Engine* eng)
{
    engine = eng;
    eval_board = &engine->board_eval;

    bot_piece = ' ';
    opp_piece = ' ';
    from = -1;
    to = -1;
    depth_lim = 8;
}

void MiniMax::findBestMove(){

    bot_piece = (engine->game_state->bot_taken == "goat") ? 'G' : 'T';
    opp_piece = (bot_piece == 'G') ? 'T' : 'G';

    // SAVING THE CURRENT STATES TO UNDO LATER
    std::vector<std::pair<int, char>> saved_board_state = engine->game_state->board_state;
    std::string saved_turn = engine->game_state->turn;
    int saved_goats_in_hand = engine->game_state->goats_in_hand;
    int saved_goats_killed = engine->game_state->goats_killed;

    // Set the turn to the bot's turn before searching
    engine->game_state->turn = (bot_piece == 'T') ? "baagh" : "goat";

    int bestScore = minimax(0, true, -WIN_SCORE, WIN_SCORE);

    // RESTORE THE BOARD AND THE SAVED STATES
    engine->game_state->board_state = saved_board_state;
    engine->game_state->turn = saved_turn;
    engine->game_state->goats_in_hand = saved_goats_in_hand;
    engine->game_state->goats_killed = saved_goats_killed;
}

int MiniMax::minimax(int depth, bool maximizing, int alpha, int beta){

    std::string winner = eval_board->checkWinner();

    if (winner == "goat"){
        if (bot_piece == 'G')
            return WIN_SCORE + depth;

        return -(WIN_SCORE + depth);
    }

    if (winner == "baagh"){
        if (bot_piece == 'T')
            return WIN_SCORE + depth;

        return -(WIN_SCORE + depth);
    }

    if (depth >= depth_lim) return evaluate_score();

    char curr_piece = (engine->game_state->turn == "baagh") ? 'T' : 'G';
    engine->game_state->turn = (curr_piece == 'T') ? "baagh" : "goat";

    int bestScore = maximizing ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();
    bool found_move = false;

    if (curr_piece == 'G' && engine->game_state->goats_in_hand > 0){
        for (int id = 1; id <= 25; id++){
            if ( engine->game_state->board_state[id].second != ' '){
                continue;
            }

            found_move = true;

            // SAVING THE EACH BOARD STATES FOR LATER RESTORING AT THIS NODE
            std::vector<std::pair<int, char>> saved_board_state = engine->game_state->board_state;
            std::string saved_turn = engine->game_state->turn;
            int saved_goats_in_hand = engine->game_state->goats_in_hand;
            int saved_goats_killed = engine->game_state->goats_killed;

            engine->game_state->board_state[id].second = 'G';
            engine->game_state->goats_in_hand--;

            // REPLACING THE TURN
            engine->game_state->turn = "baagh";

            int score = minimax(depth + 1, !maximizing, alpha, beta);

            // RESTORING THE SAVED
            engine->game_state->board_state = saved_board_state;
            engine->game_state->turn = saved_turn;
            engine->game_state->goats_in_hand = saved_goats_in_hand;
            engine->game_state->goats_killed = saved_goats_killed;

            if (depth == 0 && score > bestScore){
                bestScore = score;
                from = -1;
                to = id;
            }

            if (maximizing){
                if (score > bestScore)
                    bestScore = score;

                if (bestScore > alpha)
                    alpha = bestScore;
            }
            else{
                if (score < bestScore)
                    bestScore = score;

                if (bestScore < beta)   
                    beta = bestScore;
            }

            if (beta <= alpha) break;
        }
    }
    else
    {
        for (int id = 1; id <= 25; id++)
        {
            if (engine->game_state->board_state[id].second!= curr_piece) continue;
            
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();

            engine->game_state->turn = (curr_piece == 'T') ? "baagh" : "goat";
            eval_board->getValidMovesAt(id);

            std::vector<int> node_valid_moves = eval_board->valid_moves; // VALID MOVES FOR THIS NODE
            std::vector<std::pair<int, int>> node_edible_valid_moves = eval_board->edible_valid_moves; // MOVES THAT THE TIGER CAN EAT
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();

            for (int destination : node_valid_moves){
                found_move = true;
                bool is_capture = false; // INITIALLY IF THE BAAGH HAVE 0 EADIBLE MOVES
                int capture_pos = -1;

                if (curr_piece == 'T'){
                    for (const auto& [goat_pos, landing_pos] : node_edible_valid_moves){
                        if (landing_pos == destination){
                            is_capture = true;
                            capture_pos = goat_pos;
                            break;
                        }
                    }
                }

                std::vector<std::pair<int, char>>  saved_board_state = engine->game_state->board_state;
                std::string saved_turn = engine->game_state->turn;
                int saved_goats_in_hand = engine->game_state->goats_in_hand;
                int saved_goats_killed = engine->game_state->goats_killed;

                // MAKING THE MOVE                
                engine->game_state->board_state[id].second = ' ';
                engine->game_state->board_state[destination].second = curr_piece;

                // IF THE TIGER IS CAPTURING THE GOAT
                if (curr_piece == 'T' && is_capture){
                    engine->game_state->board_state[capture_pos].second = ' ';
                    engine->game_state->goats_killed++;
                }

                engine->game_state->turn == "baagh" ? "goat" : "baagh";

                int score = minimax(depth + 1, !maximizing, alpha, beta);

                // RESTORING THE BOARD
                engine->game_state->board_state = saved_board_state;
                engine->game_state->turn = saved_turn;
                engine->game_state->goats_in_hand = saved_goats_in_hand;
                engine->game_state->goats_killed = saved_goats_killed;

                if (depth == 0 && score > bestScore){
                    bestScore = score;
                    from = id;
                    to = destination;
                }

                if (maximizing){
                    if (score > bestScore)
                        bestScore = score;

                    if (bestScore > alpha)
                        alpha = bestScore;
                }
                else{
                    if (score < bestScore)
                        bestScore = score;

                    if (bestScore < beta)
                        beta = bestScore;
                }   

                if (beta <= alpha)
                    break;
            }

            if (beta <= alpha)
                break;
        }
    }

    if (!found_move){
        return evaluate_score();
    }

    return bestScore;
}

int MiniMax::evaluate_score(){

    const int goats_killed = engine->game_state->goats_killed;
    const int tigers = 4 - eval_board->checkBaaghTrapped();
    const int goats = countGoats();

    // 
    const TigerScoreFactors tsf = getScoreTiger();

    const int t_mob = tsf.ttl_mobility;
    const int captures = tsf.ttl_capture; 
    const int vulnerable = static_cast<int>(tsf.vulnerable_goat_pos.size());
    const int center = tsf.center_control;
    const int escape = tsf.esc_score;
    const int restriction = tsf.restriction;
    const int edge = tsf.edge_score;
    const int immobale_danger = tsf.danger;
    const int trapped = tsf.trapped_count;
    const int clusters = goatClusters();
    const int blocking = goatBlockingScore();

    const PlacementSafety placement = computePlacementSafety();
    const int safe_placement = placement.safe;

    const int danger_placement = placement.dangerous;

    int score = 0;

    score += goats_killed * Scores::GOATS_KILLED;
    score += t_mob * Scores::TIGERS_MOBILITY;
    score += captures * Scores::TIGER_CAPTURE; // HOW MANY TOTAL CAPTURES ARE POSSIBLE
    score -= trapped * Scores::TIGER_TRAPPED; 
    score += center * Scores::TIGER_CENTER; // CENTER COVERAGE ADVANTAGE
    score += escape * Scores::TIGER_ESCAPE; // COMPACTED FOR MOBILITY AND CAPTURE COUNT




    // score += edge * Scores::TIGER_EDGE; // TIGER AT EDGE DISADVANTAGE



    score += vulnerable * Scores::GOAT_VULNERABLE;
    score += restriction * Scores::GOAT_RESTRICT; // FOR TIGER, NEGATIVE ADVANTAGE
    score -= clusters * Scores::GOAT_CLUSTER;
    score -= blocking * ExtraScores::GOAT_BLOCKING; // HOW MANY OF THE GOATS/EDGES ARE BLOCING A GOAT TO EAT

    // IF THE GOAT IS STILL TO BE PLACED
    if (engine->game_state->goats_in_hand > 0){
        // score += restriction * 20; 
        // score += vulnerable * 40;
        score += danger_placement * ExtraScores::GOAT_DANGER_PLACEMENT;
        score -= safe_placement * ExtraScores::GOAT_SAFE_PLACEMENT;
        score += t_mob * 4;
    }
    else{
        // score -= trapped * 150;
        // score += captures * 35;
        // score += immobale_danger * 100;
        // score -= g_mob * 4;
    }

    score += tigers * ExtraScores::TIGER_COUNT_BONUS;
    score -= goats * ExtraScores::GOAT_COUNT_PENALTY;
    if (bot_piece == 'T')
        return score;

    return -score;
}

int MiniMax::countGoats()
{
    int count = 0;
    for (int id = 1; id <= 25; id++)
    {
        if (engine->game_state->board_state[id].second == 'G')
        {
            count++;
        }
    }
    return count;
}

// CHECKING THE GOAT CLUSTERS - ADJACENT GOATS ON THE BOARD
int MiniMax::goatClusters(){
    int clusters = 0;
    for (int pos = 0; pos < 25; pos++){
        if (engine->game_state->board_state[pos].second != 'G') continue;

        int row_of_pos = pos / 5;
        int col_of_pos = pos % 5;
        bool has_up = row_of_pos > 0;
        bool has_down = row_of_pos < 4;
        bool has_left = col_of_pos > 0;
        bool has_right = col_of_pos < 4;
        bool is_main_diag = (row_of_pos == col_of_pos);
        bool is_anti_diag = (row_of_pos + col_of_pos == 4);
        
        if (has_up){
            int neighbor = pos - 5;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // DOWN
        if (has_down){
            int neighbor = pos + 5;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // LEFT
        if (has_left){
            int neighbor = pos - 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // RIGHT
        if (has_right){
            int neighbor = pos + 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // UP-LEFT
        if (is_main_diag && has_up && has_left){
            int neighbor = pos - 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // DOWN-RIGHT
        if (is_main_diag && has_down && has_right){
            int neighbor = pos + 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // UP-RIGHT
        if (is_anti_diag && has_up && has_right){
            int neighbor = pos - 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        // DOWN-LEFT
        if (is_anti_diag && has_down && has_left){
            int neighbor = pos + 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
    }

    return clusters / 2;
}

// GETTING THE NUMBER OF GOATS THAT BLOCKS THE GOAT
int MiniMax::goatBlockingScore(){
    int goats_blocking_tiger = 0;

    for (int pos = 0; pos < 25; pos++){
        if (engine->game_state->board_state[pos].second != 'T') continue;

        int row_pos = pos / 5;
        int col_pos = pos % 5;
        bool has_up = row_pos > 0;
        bool has_down = row_pos < 4;
        bool has_left = col_pos > 0;
        bool has_right = col_pos < 4;
        bool is_main_diag = (row_pos == col_pos);
        bool is_anti_diag = (row_pos + col_pos == 4);

        if (has_up){
            int neighbor = pos - 5;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos - 2;
                if (jump_r < 0) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + col_pos;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (has_down){
            int neighbor = pos + 5;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos + 2;
                if (jump_r > 4) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + col_pos;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (has_left){
            int neighbor = pos - 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_c = col_pos - 2;
                if (jump_c < 0) goats_blocking_tiger++;
                else{
                    int jump_pos = row_pos * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (has_right){
            int neighbor = pos + 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_c = col_pos + 2;
                if (jump_c > 4) goats_blocking_tiger++;
                else{
                    int jump_pos = row_pos * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (is_main_diag && has_up && has_left){
            int neighbor = pos - 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos - 2;
                int jump_c = col_pos - 2;
                if (jump_r < 0 || jump_c < 0) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (is_main_diag && has_down && has_right){
            int neighbor = pos + 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos + 2;
                int jump_c = col_pos + 2;
                if (jump_r > 4 || jump_c > 4) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (is_anti_diag && has_up && has_right){
            int neighbor = pos - 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos - 2;
                int jump_c = col_pos + 2;
                if (jump_r < 0 || jump_c > 4) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }

        if (is_anti_diag && has_down && has_left){
            int neighbor = pos + 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                int jump_r = row_pos + 2;
                int jump_c = col_pos - 2;
                if (jump_r > 4 || jump_c < 0) goats_blocking_tiger++;
                else{
                    int jump_pos = jump_r * 5 + jump_c;
                    if (engine->game_state->board_state[jump_pos].second != ' ') goats_blocking_tiger++;
                }
            }
        }
    }
    return goats_blocking_tiger;
}

// GETTING THE INFO FOR THE SCORING FACTOR FOR THE TIGER
MiniMax::TigerScoreFactors MiniMax::getScoreTiger() {
    TigerScoreFactors tsf{};

    for (int id = 1; id <= 25; id++) {
        if (engine->game_state->board_state[id].second != 'T') continue;

        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        engine->game_state->turn = "baagh";
        eval_board->getValidMovesAt(id);

        std::vector<int> node_valid_moves = eval_board->valid_moves;
        std::vector<std::pair<int, int>> node_edible_valid_moves = eval_board->edible_valid_moves;
        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();

        int mobility = static_cast<int>(node_valid_moves.size());
        int capture_count = static_cast<int>(node_edible_valid_moves.size());
        int total_actions = mobility + capture_count;

        tsf.ttl_mobility += mobility;
        tsf.ttl_capture += capture_count;

        for (const auto& [goat_pos, landing_pos] : node_edible_valid_moves) {
            if (std::find(tsf.vulnerable_goat_pos.begin(), tsf.vulnerable_goat_pos.end(), goat_pos) == tsf.vulnerable_goat_pos.end()) {
                tsf.vulnerable_goat_pos.push_back(goat_pos);
            }
        }

        if (total_actions >= 5) { tsf.esc_score += 5; }
        else if (total_actions == 4) { tsf.esc_score += 4; }
        else if (total_actions == 3) { tsf.esc_score += 2; }
        else if (total_actions == 2) { tsf.esc_score -= 1; }
        else if (total_actions == 1) { tsf.esc_score -= 3; }
        else { tsf.esc_score -= 8; }

        if (total_actions == 0) {
            tsf.restriction -= 6;
            tsf.trapped_count++;
        } else if (total_actions == 1) {
            tsf.restriction -= 4;
        } else if (total_actions == 2) {
            tsf.restriction -= 2;
        } else if (total_actions == 3) {
            tsf.restriction -= 1;
        }

        tsf.danger += capture_count * 4;

        int idx = id - 1;
        int row = idx / 5;
        int col = idx % 5;
        int dist = std::abs(row - 2) + std::abs(col - 2);

        if (dist == 0) { tsf.center_control += 4; }
        else if (dist == 1) { tsf.center_control += 3; }
        else if (dist == 2) { tsf.center_control += 2; }

        if (row == 0 || row == 4 || col == 0 || col == 4) {
            tsf.edge_score -= 1;
        }
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();
    return tsf;
}

// IF ANY POS HAS THE PLACEMENT VULNERABLE THEN DANGERAOUS POSITIONS IS THAT
MiniMax::PlacementSafety MiniMax::computePlacementSafety(){
    PlacementSafety result;
    if (engine->game_state->goats_in_hand <= 0){
        return result;
    }

    for (int id = 1; id <= 25; id++){
        if (engine->game_state->board_state[id].second != ' ') continue;

        engine->game_state->board_state[id].second = 'G';
        bool vulnerable = false;

        for (int tid = 1; tid <= 25; tid++){
            if (engine->game_state->board_state[tid].second != 'T') continue;

            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            std::string saved_turn =  engine->game_state->turn;
            engine->game_state->turn = "baagh";
            eval_board->getValidMovesAt(tid);

            engine->game_state->turn = saved_turn;

            std::vector<std::pair<int, int>> node_edible_valid_moves = eval_board->edible_valid_moves;
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();

            for (const auto& [goat_pos, landing_pos] : node_edible_valid_moves){
                (void)landing_pos;
                if (goat_pos == id){
                    vulnerable = true;
                    break;
                }
            }

            if (vulnerable) break;
        }

        engine->game_state->board_state[id].second = ' ';

        if (vulnerable) result.dangerous++;
        else result.safe++;
    }

    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();
    return result;
}