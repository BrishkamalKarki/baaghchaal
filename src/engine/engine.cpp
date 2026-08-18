#include "engine.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <SDL3/SDL.h>

Engine::Engine(void* game_st, BoardConfig* b_conf)
    : b_conf(b_conf), bot(this), board_eval(this)
{
    game_state = static_cast<GameState*>(game_st);
    b_conf->makePoints();

    // THE INITIAL POSITION SO UNDO ALWAYS HAS A STATE TO RESTORE
    resetHistory();
}

Engine::~Engine(){
    if (bot_thread.joinable()) bot_thread.join();
}

void Engine::startBotThink(){
    if (bot_busy || bot_result_pending) return;

    // NEVER REASSIGN OVER A STILL JOINABLE THREAD (WOULD CALL std::terminate)
    if (bot_thread.joinable()) bot_thread.join();

    bot_busy = true;
    bot_result_pending = false;
    game_state->bot_thinking = true;

    bot_thread = std::thread([this](){
        bot.findBestMove();
        bot_busy = false;
        bot_result_pending = true;
        game_state->bot_thinking = false;
    });
}

void Engine::resetEngineState(){
    // WAIT FOR ANY RUNNING SEARCH BEFORE TOUCHING SHARED STATE
    bot.stop_requested = true;
    if (bot_thread.joinable()) bot_thread.join();
    bot.stop_requested = false;

    bot_busy = false;
    bot_result_pending = false;
    game_state->bot_thinking = false;

    from_to = {-1, -1};
    turn_start_ticks = 0;
    last_processed_pos = -1;
    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();
    board_eval.bgh_valid_moves.clear();
    bot.from = -1;
    bot.to = -1;
    bot.bot_piece = ' ';
    bot.opp_piece = ' ';

    // THE CURRENT POSITION AS THE UNDO BASE STATE
    resetHistory();
}

int Engine::performBotMove(){
    // ONLY APPLY A MOVE AFTER THE BACKGROUND SEARCH HAS FINISHED
    if (bot_busy || !bot_result_pending) return -1;
    bot_result_pending = false;

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();
    
    if (bot.to == -1){
        game_state->turn = game_state->human_taken;
        turn_start_ticks = SDL_GetTicks();
        last_processed_pos = -1;
        return -1;
    }
    
    int baagh_trapped = board_eval.checkBaaghTrapped();
    if (bot.from == -1)
    {
        game_state->board_state[bot.to].second = 'G';
        game_state->goats_in_hand--;
        just_trapped_tiger = (board_eval.checkBaaghTrapped() - baagh_trapped) >= 1;
    }
    else
    {
        if (game_state->bot_taken == "baagh"){
            game_state->turn = "baagh";
            board_eval.getValidMovesAt(bot.from);

            for (const auto& [goat_pos, landing_pos] : board_eval.edible_valid_moves)
            {
                if (landing_pos == bot.to)
                {
                    game_state->board_state[goat_pos].second = ' ';
                    just_killed_goat = true;
                    game_state->goats_killed++;
                    break;
                }
            }
        }
        
        game_state->board_state[bot.from].second = ' ';
        game_state->board_state[bot.to].second = bot.bot_piece;
        just_trapped_tiger = (board_eval.checkBaaghTrapped() - baagh_trapped) >= 1;
    }

    game_state->move++;
    game_state->turn = game_state->human_taken;
    saveBoardState();
    game_state->move_played = true;
    game_state->clicked_tobe_reloaded = true;

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();

    board_eval.checkBaaghTrapped(true);

    turn_start_ticks = SDL_GetTicks();
    last_processed_pos = -1;

    return 0;
}

// ENTRY POINT TO THE ENGINE
void Engine::routeToEngine(int pos, char type){

    if (bot_busy && game_state->game_mode == "B V P"){
        return;
    }

    if (pos < 0 || pos > 24){
        return;
    }

    if (pos == last_processed_pos){
        return;
    }
    last_processed_pos = pos;

    bool is_bot_mode = (game_state->game_mode == "B V P");
    if (is_bot_mode){
        if (game_state->turn == game_state->bot_taken){
            return;
        }

        // HUMAN'S TURN
        selectPos(pos);

        // AFTER THE HUMAN MOVE, IF IT IS NOW THE BOT'S TURN, RESET THE TIMER
        if (game_state->turn == game_state->bot_taken){
            turn_start_ticks = SDL_GetTicks();
        }
    }
    else {
        selectPos(pos);
    }
}

void Engine::selectPos(int pos){
    if (pos < 0 || pos > 24) return;

    board_eval.checkBaaghTrapped(true);

    for (int id = 0; id < 25; id++){
        char tp = game_state->board_state[id].second;

        if (game_state->turn == "baagh"){
            if (id == pos && tp == 'T'){
                from_to.first = pos;
                board_eval.valid_moves.clear();
                board_eval.valid_moves.reserve(24);
                board_eval.getValidMovesAt(pos);
                SDL_Log("TIGER IS SELECTED AT %d", pos);
                return;
            }
        }
        else if (game_state->turn == "goat"){
            if (id == pos){
                int baagh_trapped = board_eval.checkBaaghTrapped();
                turn_start_ticks = SDL_GetTicks();
                if (tp == ' ' && game_state->goats_in_hand > 0){ // PLACING THE NEW GOAT
                    game_state->move++;
                    game_state->board_state[pos].second = 'G';
                    game_state->goats_in_hand--;
                    game_state->turn = "baagh";
                    saveBoardState();
                    just_trapped_tiger = (board_eval.checkBaaghTrapped() - baagh_trapped) >= 1;
                    game_state->clicked_tobe_reloaded = true;
                    game_state->move_played = true;
                    board_eval.checkBaaghTrapped(true); 
                    SDL_Log("GOAT IS PALCED AT %d", pos);
                    return;
                }
                else if (tp == 'G' && game_state->goats_in_hand == 0){
                    // SELECTING THE BAAKHRA PRESENT IN THE BOARD TO MOVE
                    from_to.first = pos;
                    board_eval.valid_moves.clear();
                    board_eval.valid_moves.reserve(24);
                    board_eval.getValidMovesAt(pos);
                    SDL_Log("GOAT IS SELECTED %d", pos);
                    return;
                }
            }
        }
    }

    // SECOND CLICK TO MOVE THE BAAGH OR BAAKHRA
    if (std::find(board_eval.valid_moves.begin(), board_eval.valid_moves.end(), pos) != board_eval.valid_moves.end()){
        int baagh_trapped = board_eval.checkBaaghTrapped();
        from_to.second = pos; // SAVING THE POSITION TO GO TO

        if (game_state->turn == "baagh"){
            for (auto& [goat, vacant] : board_eval.edible_valid_moves){
                if (pos == vacant){
                    SDL_Log("CAPTURED THE GOAT BY BAAGH AT %d", goat);
                    game_state->board_state[goat].second = ' ';
                    game_state->goats_killed++;
                    just_killed_goat = true;
                }
            }
            changePosBaagh();
            game_state->turn = "goat";
            board_eval.edible_valid_moves.clear();
        }
        else if (game_state->turn == "goat"){
            changePosGoat();
            game_state->turn = "baagh";
        }
        just_trapped_tiger = (board_eval.checkBaaghTrapped() - baagh_trapped) >= 1;
        saveBoardState();
        game_state->clicked_tobe_reloaded = true;
        game_state->move_played = true;
        game_state->clicked_tobe_reloaded = true;
        turn_start_ticks = SDL_GetTicks();
        board_eval.checkBaaghTrapped(true); 
        SDL_Log("BAAKHRA / BAAGH MOVED TO %d", pos);
        return;
    }

    SDL_Log("NOT A VALID MOVE at pos %d", pos);
}

// MAKING TEH MOVES
void Engine::changePosBaagh(){
    game_state->move++;
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'T';
}

void Engine::changePosGoat(){
    game_state->move++;
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'G';
}

// SAVING THE CURRENT BOARD AND ALL GAME COUNTERS IN THE HISTORY 
void Engine::saveBoardState(){
    if (saved == 9){
        for (int i = 0; i < 9; i++){
            bit_board_goats[i] = bit_board_goats[i + 1];
            bit_board_tigers[i] = bit_board_tigers[i + 1];
            saved_goats_in_hand[i] = saved_goats_in_hand[i + 1];
            saved_goats_killed[i] = saved_goats_killed[i + 1];
            saved_turn[i] = saved_turn[i + 1];
            saved_move[i] = saved_move[i + 1];
        }
        bit_board_goats[9] = 0;
        bit_board_tigers[9] = 0;
    }
    else {
        saved++;
    }

    bit_board_goats[saved] = 0;
    bit_board_tigers[saved] = 0;

    for (int id = 0; id < 25; id++){
        char type = game_state->board_state[id].second;
        if (type == 'G'){
            bit_board_goats[saved] |= (1u << id);
        } else if (type == 'T'){
            bit_board_tigers[saved] |= (1u << id);
        }
    }

    saved_goats_in_hand[saved] = game_state->goats_in_hand;
    saved_goats_killed[saved] = game_state->goats_killed;
    saved_turn[saved] = game_state->turn;
    saved_move[saved] = game_state->move;
}

// CLEARS THE HISTORY AND SEEDS THE CURRENT POSITION AS THE BASE STATE
void Engine::resetHistory(){
    for (int i = 0; i < 10; i++){
        bit_board_goats[i] = 0;
        bit_board_tigers[i] = 0;
        saved_goats_in_hand[i] = 0;
        saved_goats_killed[i] = 0;
        saved_turn[i] = "goat";
        saved_move[i] = 1;
    }
    saved = -1;
    saveBoardState();
}

// RESTORES THE PREVIOUS FULL STATE (BOARD, GOATS, TURN, MOVE COUNT)
void Engine::undoMove(){
    if (bot_busy){
        SDL_Log("UNDO: BOT IS THINKING, IGNORED");
        return;
    }

    if (saved <= 0){
        SDL_Log("NO MOVES TO UNDO");
        return;
    }

    saved--;

    for (int pos = 0; pos < 25; pos++){
        game_state->board_state[pos].second = ' ';
    }
    for (int pos = 0; pos < 25; pos++){ 
        uint32_t bit = (1u << pos);
        if (bit & bit_board_tigers[saved]){
            game_state->board_state[pos].second = 'T';
        } else if (bit & bit_board_goats[saved]){
            game_state->board_state[pos].second = 'G';
        }
    }

    game_state->goats_in_hand = saved_goats_in_hand[saved];
    game_state->goats_killed = saved_goats_killed[saved];
    game_state->turn = saved_turn[saved];
    game_state->move = saved_move[saved];

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();
    from_to = {-1, -1};
    last_processed_pos = -1;
    turn_start_ticks = SDL_GetTicks();

    board_eval.checkBaaghTrapped(true);
}