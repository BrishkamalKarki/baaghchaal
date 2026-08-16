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
    turn_start_ticks = SDL_GetTicks();
}

int Engine::performBotMove(){
    bot.findBestMove();

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();

    if (bot.from == -1)
    {
        game_state->board_state[bot.to].second = 'G';
        game_state->goats_in_hand--;
    }
    else
    {
        if (game_state->bot_taken == "baagh")
        {
            game_state->turn = "baagh";
            board_eval.getValidMovesAt(bot.from);

            for (const auto& [goat_pos, landing_pos] : board_eval.edible_valid_moves)
            {
                if (landing_pos == bot.to)
                {
                    game_state->board_state[goat_pos].second = ' ';
                    game_state->goats_killed++;
                    break;
                }
            }
        }

        game_state->board_state[bot.from].second = ' ';
        game_state->board_state[bot.to].second = bot.bot_piece;
    }

    game_state->move++;
    saveBoardState();
    game_state->clicked_tobe_reloaded = true;
    
    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();

    board_eval.checkBaaghTrapped(true);

    game_state->turn = game_state->human_taken;
    turn_start_ticks = SDL_GetTicks();
    last_processed_pos = -1;

    return 0;
}

// ENTRY POINT TO THE ENGINE
void Engine::routeToEngine(int pos, char type){
    if (pos < 0 || pos > 24){
        return;
    }

    if (pos == last_processed_pos){
        return;
    }
    last_processed_pos = pos;

    SDL_Log("routeToEngine: pos=%d, turn=%s, bot_taken=%s, game_mode=%s",
            pos, game_state->turn.c_str(), game_state->bot_taken.c_str(),
            game_state->game_mode.c_str());

    bool is_bot_mode = (game_state->game_mode == "B V P");

    if (is_bot_mode){
        if (game_state->turn == game_state->bot_taken){
            SDL_Log("routeToEngine: Human's turn, calling selectPos(%d)", pos);
            selectPos(pos);
            performBotMove();

            turn_start_ticks = SDL_GetTicks();
            SDL_Log("routeToEngine: Turn passed to bot.");
        }
    }else {
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
        else if (game_state->turn == "goat" && game_state->bot_taken != "goat"){
            if (id == pos){
                turn_start_ticks = SDL_GetTicks();
                if (tp == ' ' && game_state->goats_in_hand > 0){ // PLACING THE NEW GOAT

                    game_state->move++;
                    game_state->board_state[pos].second = 'G';
                    game_state->goats_in_hand--;
                    game_state->turn = "baagh";
                    saveBoardState();
                    game_state->clicked_tobe_reloaded = true;
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
        from_to.second = pos; // SAVING THE POSITION TO GO TO

        if (game_state->turn == "baagh"){
            for (auto& [goat, vacant] : board_eval.edible_valid_moves){
                if (pos == vacant){
                    SDL_Log("CAPTURED THE GOAT BY BAAGH AT %d", goat);
                    game_state->board_state[goat].second = ' ';
                    game_state->goats_killed++;
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
        saveBoardState();

        game_state->clicked_tobe_reloaded = true;
        turn_start_ticks = SDL_GetTicks();
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

// SAVING THE CURRENT BOARD IN THE BIT BOARD
void Engine::saveBoardState(){
    if (saved == 9){
        for (int i = 0; i < 9; i++){
            bit_board_goats[i] = bit_board_goats[i + 1];
            bit_board_tigers[i] = bit_board_tigers[i + 1];
        }
        bit_board_goats[9] = 0;
        bit_board_tigers[9] = 0;
    } else {
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
}

// 10 UNDOS AT MAX
void Engine::undoMove(){
    if (saved < 0){
        SDL_Log("NO MOVES TO UNDO");
        return;
    }

    bit_board_goats[saved] = 0;
    bit_board_tigers[saved] = 0;
    saved--;

    if (saved >= 0){
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
    }
}