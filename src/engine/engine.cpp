#include "engine.hpp" 
#include <cmath>
#include <algorithm>
#include <random>

Engine::Engine(void* game_st, BoardConfig* b_conf) : b_conf(b_conf), bot(this), board_eval(this){
  game_state = static_cast<GameState*>(game_st);
  b_conf->makePoints();
}

void Engine::routeToEngine(int pos, char type){
    if (game_state->game_mode == "bot_vs_human"){
        if (game_state->turn == game_state->bot_taken){
            bot.findBestMove();
            board_eval.valid_moves.clear();
            board_eval.edible_valid_moves.clear();

            if (bot.from == -1){
                game_state->board_state[bot.to].second = 'G';
                game_state->goats_in_hand--;
            }
            else{
                if (game_state->bot_taken == "baagh")
                {
                    game_state->turn = "baagh";

                    board_eval.getValidMovesAt(bot.from);

                    for (const auto& [goat_pos, landing_pos] :
                        board_eval.edible_valid_moves)
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

            board_eval.valid_moves.clear();
            board_eval.edible_valid_moves.clear();

            game_state->turn = game_state->human_taken;
        }
        else{
            selectPos(pos);
        }
    }
    else{
        selectPos(pos);
    }
};

void Engine::selectPos(int pos){
    board_eval.checkBaaghTrapped();
    
    for (const auto& [id, tp] : game_state->board_state){
        if (game_state->turn == "baagh" && game_state->bot_taken != "baagh"){
                if (id - 1 == pos && tp == 'T'){
                    from_to.first = pos;
                    board_eval.valid_moves.clear();
                    board_eval.valid_moves.reserve(24);
                    board_eval.getValidMovesAt(pos);
                    SDL_Log("%d | %d %d", from_to.first, from_to.second, id);
                    return;
                }
        }
        else if (game_state->turn == "goat" && game_state->bot_taken != "goat"){
                if (id - 1 == pos){
                    if (tp == ' ' && game_state->goats_in_hand > 0){
                        game_state->board_state[pos].second = 'G';
                        game_state->goats_in_hand--;
                        game_state->turn = "baagh";
                        return;
                    }
                    else if (tp == 'G' && game_state->goats_in_hand == 0){
                        from_to.first = pos;
                        board_eval.valid_moves.clear();
                        board_eval.valid_moves.reserve(24);
                        board_eval.getValidMovesAt(pos);
                        SDL_Log("%d | %d %d", from_to.first, from_to.second, id);
                        return;
                    }
            }
        }
    }

    if (std::find(board_eval.valid_moves.begin(), board_eval.valid_moves.end(), pos + 1) != board_eval.valid_moves.end()){
        from_to.second = pos;
        if (game_state->turn == "baagh"){
            for (auto& [goat, vacant] : board_eval.edible_valid_moves){
                if (pos == vacant){
                    game_state->board_state[goat].second = ' ';
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
    }
    else{ 
        SDL_Log("NOT A VALID MOVE");
        return;
    } 
    SDL_Log("%d | %d ", from_to.first, from_to.second);
}

void Engine::changePosBaagh(){
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'T';
}

void Engine::changePosGoat(){
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'G';
}