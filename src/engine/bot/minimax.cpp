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

    danger_map.assign(25, false);
    center_dist.resize(25);
    for (int id = 0; id < 25; id++){
        center_dist[id] = std::abs(id / 5 - 2) + std::abs(id % 5 - 2);
    }
}

void MiniMax::findBestMove(){
    think_time = SDL_GetTicks();

    bot_piece = (engine->game_state->bot_taken == "goat") ? 'G' : 'T';
    opp_piece = (bot_piece == 'G') ? 'T' : 'G';

    // DIFFICULTY CONTROLS REAL SEARCH DEPTH + TIME BUDGET.
    // THE SEARCH RUNS ON A BACKGROUND THREAD, SO THESE BUDGETS ARE JUST
    // A RESPONSIVENESS CEILING - THE ENGINE NEVER FREEZES ON THEM.
    const std::string& diff = engine->game_state->bot_diff_level;
    if (diff == "EASY"){
        depth_lim = 5;
        time_budget_ms = 400;
    }
    else if (diff == "MEDIUM"){
        depth_lim = 7;
        time_budget_ms = 1200;
    }
    else{
        depth_lim = 10;
        time_budget_ms = 4000;
    }
    time_budget_ms = std::clamp(time_budget_ms, 100, 4000); // SETTING THE RANGE

    // NEVER REUSE A STALE MOVE FROM A PREVIOUS SEARCH
    from = -1;
    to = -1;

    // SAVE THE CURRENT BOARD SO WE CAN RESTORE IT AFTER SEARCH
    std::vector<std::pair<int, char>> saved_board_state = engine->game_state->board_state;
    std::string saved_turn = engine->game_state->turn;
    int saved_goats_in_hand = engine->game_state->goats_in_hand;
    int saved_goats_killed = engine->game_state->goats_killed;

    engine->game_state->turn = (bot_piece == 'T') ? "baagh" : "goat";

    // STATIC FOR MOVE ORDERING, ONCE PER MOVE
    buildDangerMap();
    buildPlacementOrder();

    // IMPLEMENTING THE ITERATIVE DEEPNING
    search_start = SDL_GetTicks();
    aborted = false;
    stop_requested = false;

    int best_from = -1;
    int best_to = -1;

    for (int d = 1; d <= depth_lim; d++){
        current_depth = d;
        aborted = false;

        minimax(0, true, -WIN_SCORE, WIN_SCORE);

        if (aborted) break;
        if (stop_requested) break;
        best_from = from;
        best_to = to;

        if (SDL_GetTicks() - search_start >= time_budget_ms) break;
    }

    from = best_from;
    to = best_to;

    if (to == -1){
        fallbackMove(); // IN ANY CASE - PREVENTION
    }

    // RESTORE EVERYTHING AFTER SEARCH IS DONE
    engine->game_state->board_state = saved_board_state;
    engine->game_state->turn = saved_turn;
    engine->game_state->goats_in_hand = saved_goats_in_hand;
    engine->game_state->goats_killed = saved_goats_killed;
}

int MiniMax::minimax(int depth, bool maximizing, int alpha, int beta){

    // CHECKING FOR THE TIME
    // think_time = SDL_GetTicks();
    if (depth > 0 && time_budget_ms > 0 && SDL_GetTicks() - search_start >= time_budget_ms && stop_requested.load(std::memory_order_relaxed)){
        aborted = true;
        return ABORT_SCORE;
    }

    // CHECK IF SOMEONE ALREADY WON
    std::string winner = eval_board->checkWinner();

    if (winner == "goat"){
        if (bot_piece == 'G')
            return WIN_SCORE - depth; 

        return -(WIN_SCORE - depth); 
    }

    if (winner == "baagh"){
        if (bot_piece == 'T')
            return WIN_SCORE - depth;

        return -(WIN_SCORE - depth);
    }

    char curr_piece = (engine->game_state->turn == "baagh") ? 'T' : 'G';

    // FOR TIGER CHECK TO DEPTH + 1 TO CHECK IF EATABLE 
    bool capture_extend = false;
    if (depth >= current_depth){
        if (depth < current_depth + 2 && curr_piece == 'T'){
            capture_extend = true;
        }
        else{
            return evaluate_score();
        }
    }

    int best_score = maximizing ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();
    bool found_move = false;

    // PLACEMENT PHASE
    if (curr_piece == 'G' && engine->game_state->goats_in_hand > 0){
        for (int id : place_order){
            if (engine->game_state->board_state[id].second != ' '){
                continue;
            }

            found_move = true;

            // SAVE BOARD BEFORE TRYING THE MOVE
            std::vector<std::pair<int, char>> saved_board_state = engine->game_state->board_state;
            std::string saved_turn = engine->game_state->turn;
            int saved_goats_in_hand = engine->game_state->goats_in_hand;
            int saved_goats_killed = engine->game_state->goats_killed;

            engine->game_state->board_state[id].second = 'G';
            engine->game_state->goats_in_hand--;

            // AFTER GOAT IS PLACED IT IS TIGERS TURN
            engine->game_state->turn = "baagh";

            int score = minimax(depth + 1, !maximizing, alpha, beta);

            // PUT THE BOARD BACK
            engine->game_state->board_state = saved_board_state;
            engine->game_state->turn = saved_turn;
            engine->game_state->goats_in_hand = saved_goats_in_hand;
            engine->game_state->goats_killed = saved_goats_killed;

            if (score == ABORT_SCORE) return ABORT_SCORE;

            if (depth == 0 && score > best_score){
                best_score = score;
                from = -1;
                to = id;
            }

            if (maximizing){
                if (score > best_score)
                    best_score = score;

                if (best_score > alpha)
                    alpha = best_score;
            }
            else{
                if (score < best_score)
                    best_score = score;

                if (best_score < beta)
                    beta = best_score;
            }

            if (beta <= alpha) break;
        }
    }
    else
    {
        // MOVEMENT PHASE
        for (int id = 0; id < 25; id++)
        {
            if (engine->game_state->board_state[id].second != curr_piece) continue;

            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();

            engine->game_state->turn = (curr_piece == 'T') ? "baagh" : "goat";
            eval_board->getValidMovesAt(id);

            std::vector<int> node_valid_moves = eval_board->valid_moves;
            std::vector<std::pair<int, int>> node_edible_valid_moves = eval_board->edible_valid_moves;
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();

            // SORTING FOR BETTER, PUTTING THE CAPTURE FIRST
            if (curr_piece == 'T' && !node_edible_valid_moves.empty()){
                std::vector<int> capture_dests;
                std::vector<int> non_capture_dests;
                for (int dest : node_valid_moves){
                    bool is_capturable = false;
                    for (const auto& [gp, lp] : node_edible_valid_moves){
                        if (lp == dest){ is_capturable = true; break; }
                    }
                    if (is_capturable) capture_dests.push_back(dest);
                    else non_capture_dests.push_back(dest);
                }
                node_valid_moves.clear();
                for (int d : capture_dests) node_valid_moves.push_back(d);
                for (int d : non_capture_dests) node_valid_moves.push_back(d);
            }

            for (int destination : node_valid_moves){
                found_move = true;
                bool is_capture = false;
                int capture_pos = -1;

                // CHECK IF THIS MOVE CAPTURES A GOAT
                if (curr_piece == 'T'){
                    for (const auto& [goat_pos, landing_pos] : node_edible_valid_moves){
                        if (landing_pos == destination){
                            is_capture = true;
                            capture_pos = goat_pos;
                            break;
                        }
                    }
                }

                // CAPTURE EXTENSION
                if (capture_extend && !is_capture) continue;

                // SAVE THE BOARD BEFORE MAKING THE MOVE
                std::vector<std::pair<int, char>>  saved_board_state = engine->game_state->board_state;
                std::string saved_turn = engine->game_state->turn;
                int saved_goats_in_hand = engine->game_state->goats_in_hand;
                int saved_goats_killed = engine->game_state->goats_killed;

                // MAKE THE MOVE
                engine->game_state->board_state[id].second = ' ';
                engine->game_state->board_state[destination].second = curr_piece;

                // REMOVE CAPTURED GOAT
                if (curr_piece == 'T' && is_capture){
                    engine->game_state->board_state[capture_pos].second = ' ';
                    engine->game_state->goats_killed++;
                }

                // FLIP THE TURN AFTER MOVING
                engine->game_state->turn = (curr_piece == 'T') ? "goat" : "baagh";

                int score = minimax(depth + 1, !maximizing, alpha, beta);

                // PUT THE BOARD BACK
                engine->game_state->board_state = saved_board_state;
                engine->game_state->turn = saved_turn;
                engine->game_state->goats_in_hand = saved_goats_in_hand;
                engine->game_state->goats_killed = saved_goats_killed;

                if (score == ABORT_SCORE) return ABORT_SCORE;

                if (depth == 0 && score > best_score){
                    best_score = score;
                    from = id;
                    to = destination;
                }

                if (maximizing){
                    if (score > best_score)
                        best_score = score;

                    if (best_score > alpha)
                        alpha = best_score;
                }
                else{
                    if (score < best_score)
                        best_score = score;

                    if (best_score < beta)
                        beta = best_score;
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

    return best_score;
}

int MiniMax::evaluate_score(){

    const int goats_killed = engine->game_state->goats_killed;
    const int tigers = 4 - eval_board->checkBaaghTrapped();
    const int goats = countGoats();

    // GATHER TIGER POSITIONAL DATA
    const TigerScoreFactors tsf = getScoreTiger();

    const int t_mob = tsf.ttl_mobility;
    const int captures = tsf.ttl_capture;
    const int vulnerable = static_cast<int>(tsf.vulnerable_goat_pos.size());
    const int center = tsf.center_control;
    const int escape = tsf.esc_score;
    const int restriction = tsf.restriction;
    const int trapped = tsf.trapped_count;
    const int edge = tsf.edge_score;
    const int clusters = goatClusters();
    const int blocking = goatBlockingScore();

    int score = 0;

    // TIGER SCORING: MORE KILLS AND CAPTURES ARE GOOD FOR THE TIGER
    score += goats_killed * Scores::GOATS_KILLED;
    score += t_mob * Scores::TIGERS_MOBILITY;
    score += captures * Scores::TIGER_CAPTURE;
    score -= trapped * Scores::TIGER_TRAPPED;
    score += center * Scores::TIGER_CENTER;
    score += escape * Scores::TIGER_ESCAPE;
    // HERD TIGERS THERE, WHERE THEIR LEAP LINES ARE FEWEST
    score += edge * Scores::TIGER_EDGE;

    // GOAT SCORING
    score += vulnerable * Scores::GOAT_VULNERABLE;
    score += restriction * Scores::GOAT_RESTRICT;
    score -= clusters * Scores::GOAT_CLUSTER;
    score -= blocking * ExtraScores::GOAT_BLOCKING;

    // PLACEMENT PHASE
    if (engine->game_state->goats_in_hand > 0){
        int dangerous = 0;
        int safe = 0;
        for (int id = 0; id < 25; id++){
            if (engine->game_state->board_state[id].second == ' '){
                if (danger_map[id]) dangerous++;
                else safe++;
            }
        }
        score += dangerous * ExtraScores::GOAT_DANGER_PLACEMENT;
        score -= safe * ExtraScores::GOAT_SAFE_PLACEMENT;
    }

    // ACTIVE TIGERS ARE GOOD, FEWER GOATS MEANS TIGER IS WINNING
    score += tigers * ExtraScores::TIGER_COUNT_BONUS;
    score -= goats * ExtraScores::GOAT_COUNT_PENALTY;

    // RETURN SCORE FROM THE BOT'S PERSPECTIVE - FROM THE TIGER VIEWPOINT
    if (bot_piece == 'T')
        return score;

    return -score;
}

// MARK ALL EMPTY CELLS WHERE A NEWLY PLACED GOAT COULD BE CAPTURED FROM TIGER PERSPECTIVE
void MiniMax::buildDangerMap(){
    danger_map.assign(25, false);
    const auto& b = engine->game_state->board_state;

    for (int tid = 0; tid < 25; tid++){
        if (b[tid].second != 'T') continue;

        int row= tid / 5;
        int col = tid % 5;
        bool has_up = row > 0;
        bool has_down = row < 4;
        bool has_left = col > 0;
        bool has_right = col < 4;
        bool is_main_diag = (row == col);
        bool is_anti_diag = (row + col == 4);

        if (has_up && row >= 2){
            int mid = (row - 1) * 5 + col;
            int land = (row - 2) * 5 + col;
            if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
        }   
        if (has_down && row <= 2){
            int mid = (row + 1) * 5 + col;
            int land = (row + 2) * 5 + col;
            if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
        }
        if (has_left && col >= 2){
            int mid = row * 5 + (col - 1);
            int land = row * 5 + (col - 2);
            if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
        }
        if (has_right && col <= 2){
            int mid = row * 5 + (col + 1);
            int land = row * 5 + (col + 2);
            if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
        }

        // MAIN DIAGONAL CAPTURES
        if (is_main_diag){
            if (row >= 2 && col >= 2){
                int mid = (row - 1) * 5 + (col - 1);
                int land = (row - 2) * 5 + (col - 2);
                if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
            }
            if (row <= 2 && col <= 2){
                int mid = (row + 1) * 5 + (col + 1);
                int land = (row + 2) * 5 + (col + 2);
                if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
            }
        }

        // ANTI DIAGONAL CAPTURES
        if (is_anti_diag){
            if (row >= 2 && col <= 2){
                int mid = (row - 1) * 5 + (col + 1);
                int land = (row - 2) * 5 + (col + 2);
                if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
            }
            if (row <= 2 && col >= 2){
                int mid = (row + 1) * 5 + (col - 1);
                int land = (row + 2) * 5 + (col - 2);
                if (b[mid].second == ' ' && b[land].second == ' ') danger_map[mid] = true;
            }
        }
    }
}

// EXISTING GOATS (PAIRED GOATS PROTECT EACH OTHER), THEN CLOSER TO THE CENTER
void MiniMax::buildPlacementOrder(){
    place_order.clear();
    for (int id = 0; id < 25; id++){
        if (engine->game_state->board_state[id].second == ' '){
            place_order.push_back(id);
        }
    }
    std::sort(place_order.begin(), place_order.end(), [this](int a, int b){
        bool da = danger_map[a];
        bool db = danger_map[b];
        if (da != db) return !da;

        // COMPARING THE GOATS AROUND EACH
        int ga = countGoatNeighbours(a);
        int gb = countGoatNeighbours(b);
        if (ga != gb) return ga > gb;

        return center_dist[a] < center_dist[b];
    }); 
}

// HOW MANY GOATS ARE PRESENT ON THE EACH 8 PLACES AROUND
int MiniMax::countGoatNeighbours(int id){
    int row  = id / 5;
    int col = id % 5;
    int count = 0;

    for (int dr = -1; dr <= 1; dr++){
        for (int dc = -1; dc <= 1; dc++){
            if (dr == 0 && dc == 0) continue;
            int nr = row + dr;
            int nc = col + dc;
            if (nr < 0 || nr > 4 || nc < 0 || nc > 4) continue;
            if (engine->game_state->board_state[nr * 5 + nc].second == 'G') count++;
        }
    }
    return count;
}

// FOR THE SAFETY PRECAUTIONS
void MiniMax::fallbackMove(){
    char curr = (engine->game_state->turn == "baagh") ? 'T' : 'G';

    if (curr == 'G' && engine->game_state->goats_in_hand > 0){
        for (int id : place_order){
            if (engine->game_state->board_state[id].second == ' '){
                from = -1;
                to = id;
                return;
            }
        }
        return;
    }

    for (int id = 0; id < 25; id++){
        if (engine->game_state->board_state[id].second != curr) continue;

        eval_board->valid_moves.clear();
        eval_board->edible_valid_moves.clear();
        std::string local_saved_turn = engine->game_state->turn;
        engine->game_state->turn = (curr == 'T') ? "baagh" : "goat";
        eval_board->getValidMovesAt(id);
        engine->game_state->turn = local_saved_turn;

        if (!eval_board->valid_moves.empty()){
            from = id;
            to = eval_board->valid_moves.front();
            eval_board->valid_moves.clear();
            eval_board->edible_valid_moves.clear();
            return;
        }
    }
}

int MiniMax::countGoats()
{
    int count = 0;
    for (int id = 0; id < 25; id++)
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
        if (has_down){
            int neighbor = pos + 5;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (has_left){
            int neighbor = pos - 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (has_right){
            int neighbor = pos + 1;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (is_main_diag && has_up && has_left){
            int neighbor = pos - 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (is_main_diag && has_down && has_right){
            int neighbor = pos + 6;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (is_anti_diag && has_up && has_right){
            int neighbor = pos - 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
        if (is_anti_diag && has_down && has_left){
            int neighbor = pos + 4;
            if (engine->game_state->board_state[neighbor].second == 'G'){
                clusters++;
            }
        }
    }

    return clusters / 2;
}

// COUNT HOW MANY GOATS BLOCK A TIGER FROM CAPTURING
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

// GATHER SCORING FACTORS FOR ALL TIGERS ON THE BOARD
MiniMax::TigerScoreFactors MiniMax::getScoreTiger() {
    TigerScoreFactors tsf{};
    std::string saved_turn = engine->game_state->turn;

    for (int id = 0; id < 25; id++) {
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

        // TRACK UNIQUE GOATS THAT CAN BE CAPTURED
        for (const auto& [goat_pos, landing_pos] : node_edible_valid_moves) {
            if (std::find(tsf.vulnerable_goat_pos.begin(), tsf.vulnerable_goat_pos.end(), goat_pos) == tsf.vulnerable_goat_pos.end()) {
                tsf.vulnerable_goat_pos.push_back(goat_pos);
            }
        }

        // FREEDOM SCORE, MORE MOVES - TIGER IS FREE
        if (total_actions >= 5) { tsf.esc_score += 5; }
        else if (total_actions == 4) { tsf.esc_score += 4; }
        else if (total_actions == 3) { tsf.esc_score += 2; }
        else if (total_actions == 2) { tsf.esc_score -= 1; }
        else if (total_actions == 1) { tsf.esc_score -= 3; }
        else { tsf.esc_score -= 8; }

        // RESTRICTION
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

        // CENTER CONTROL
        int row = id / 5;
        int col = id % 5;
        int dist = std::abs(row - 2) + std::abs(col - 2);

        if (dist == 0) { tsf.center_control += 4; }
        else if (dist == 1) { tsf.center_control += 3; }
        else if (dist == 2) { tsf.center_control += 2; }

        if (row == 0 || row == 4 || col == 0 || col == 4) {
            tsf.edge_score -= 1;
        }
    }

    engine->game_state->turn = saved_turn;
    eval_board->valid_moves.clear();
    eval_board->edible_valid_moves.clear();
    return tsf;
}
