#include "engine.hpp" 
#include <cmath>
#include <algorithm>

Engine::Engine(void* game_st, BoardConfig* b_conf) : b_conf(b_conf){
  turn = "GOAT";
  game_state = static_cast<GameState*>(game_st);
  b_conf->makePoints();
}

void Engine::routeToEngine(int pos, char type){
    selectPos(pos);
};

void Engine::checkBaaghTrapped(){
    game_state->baagh_trapped = 0;
    game_state->baagh_trapped_at_pos.clear();
    temp_valid_moves = valid_moves;
    temp_edible_valid_moves = edible_valid_moves;
    for (const auto& [id, tp] : game_state->board_state){
        bgh_valid_moves.clear();
        if (tp == 'T'){
            check_trapped = true;
            getValidMovesAt(id - 1);
            check_trapped = false;
            if (bgh_valid_moves.empty()){
                game_state->baagh_trapped_at_pos.push_back(id - 1);
                game_state->baagh_trapped++;
            }
        }
    }
    valid_moves = temp_valid_moves;
    edible_valid_moves = temp_edible_valid_moves;
}

void Engine::selectPos(int pos){
    checkBaaghTrapped();
    if (game_state->baagh_trapped == 4){
        SDL_Log("GAME ENDED! TIGER WON!");
        return;
    }
    if (game_state->goats_killed == 5){
        SDL_Log("GAME ENDED! TIGER WON!");
    }
    
    for (const auto& [id, tp] : game_state->board_state){
        if (game_state->turn == "baagh"){
            if (id - 1 == pos && tp == 'T'){ // SELECTING THE BAAGH TO MOVE
                
                from_to.first = pos;
                valid_moves.clear();
                valid_moves.reserve(24);
                getValidMovesAt(pos); // GETTING THE VALID MOVES FOR THE BAAGH TO MOVE AROUND IT
                SDL_Log("%d | %d %d", from_to.first, from_to.second, id);
                return;
            }
        }
        else if (game_state->turn == "goat"){
            if (id - 1 == pos){ // CHOOSING THE OPEN POSITION FOR THE GOAT TO PUT IN THERE

                if (tp == ' ' && game_state->goats_in_hand > 0){
                    game_state->board_state[pos].second = 'G';
                    game_state->goats_in_hand--;
                    game_state->turn = "baagh";
                    return;
                }
                else if (tp == 'G' && game_state->goats_in_hand == 0){
                    from_to.first = pos;
                    valid_moves.clear();
                    valid_moves.reserve(24);
                    getValidMovesAt(pos); // GETTING THE VALID MOVES FOR THE GOAT (AFTER 20 DEPLOYED GOAT) TO MOVE AROUND IT
                    SDL_Log("%d | %d %d", from_to.first, from_to.second, id);
                    return;
                }
            }
        }
    }

    if (std::find(valid_moves.begin(), valid_moves.end(), pos + 1) != valid_moves.end()){ // CHOOSING THE VALID POSITION FOR BAAGH GOAT TO MOVE 
        from_to.second = pos;
        if (game_state->turn == "baagh"){
            for (auto& [goat, vacant] : edible_valid_moves){
                if (pos == vacant){
                    game_state->board_state[goat].second = ' ';
                }
            }
            changePosBaagh();
            game_state->turn = "goat";
            edible_valid_moves.clear();
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

int Engine::getValidMovesAt(int pos, std::string where){
  int g_pos = 1;

  for (int row = 1; row <= 5; row++){
    for (int col = 1; col <= 5; col++){

      if (g_pos-1 == pos){

        int row_of_pos = pos / 5; 
        int col_of_pos = pos % 5; 

        bool has_up    = row_of_pos > 0;
        bool has_down  = row_of_pos < 4;
        bool has_left  = col_of_pos > 0;
        bool has_right = col_of_pos < 4;

        if (where != "none"){
            if (where == "UP" && has_up){
                if (game_state->board_state[pos - 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 5});
                    return game_state->board_state[pos - 5].first;
                }
            }
            else if (where == "DOWN" && has_down){
                if (game_state->board_state[pos + 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 5});
                    return game_state->board_state[pos + 5].first;
                }
            }
            else if (where == "LEFT" && has_left){
                if (game_state->board_state[pos - 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 1});
                    return game_state->board_state[pos - 1].first;
                }
            }
            else if (where == "RIGHT" && has_right){
                if (game_state->board_state[pos + 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 1});
                    return game_state->board_state[pos + 1].first;
                }
            }
            else if (where == "UP-LEFT" && has_down && has_up){
                if (game_state->board_state[pos - 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 6});
                    return game_state->board_state[pos - 6].first;
                }
            }
            else if (where == "UP-RIGHT" && has_up && has_right){
                if (game_state->board_state[pos - 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 4});
                    return game_state->board_state[pos - 4].first;
                }
            }
            else if (where == "DOWN-LEFT" && has_down && has_left){
                if (game_state->board_state[pos + 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 4});
                    return game_state->board_state[pos + 4].first;
                }
            }
            else if (where == "DOWN_RIGHT" && has_down && has_right){
                if (game_state->board_state[pos + 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 6});
                    return game_state->board_state[pos + 6].first;
                }
            }
            return 99;
        }


        if (row == col){
            if (has_up && has_left){
                if (game_state->board_state[pos - 6].second == ' ')
                    valid_moves.push_back(game_state->board_state[pos - 6].first); // UP-LEFT
                else if(game_state->board_state[pos - 6].second == 'G'){
                    int edible_valid = getValidMovesAt(pos - 6, "UP-LEFT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }   
            }
        }
                
        if (has_left){
            if (game_state->board_state[pos - 1].second == ' '){
                valid_moves.push_back(game_state->board_state[pos - 1].first); // LEFT
            }
            else if(game_state->board_state[pos - 1].second == 'G' && game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 1, "LEFT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
                
                
        if (row + col == 6){
            if (has_down && has_left && game_state->board_state[pos + 4].second == ' '){
                valid_moves.push_back(game_state->board_state[pos + 4].first); // DOWN-LEFT
            }
            else if(game_state->board_state[pos + 4].second == 'G' && game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 4, "DOWN-LEFT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (has_up){
            if (game_state->board_state[pos - 5].second == ' '){
                valid_moves.push_back(game_state->board_state[pos - 5].first); // UP
            }
            else if(game_state->board_state[pos - 5].second == 'G' && game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 5, "UP");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (has_down){
            if (game_state->board_state[pos + 5].second == ' '){
                valid_moves.push_back(game_state->board_state[pos + 5].first); // DOWN
            }
            else if(game_state->board_state[pos + 5].second == 'G' && game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 5, "DOWN");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (row + col == 6){
            if (has_up && has_right){
                if (game_state->board_state[pos - 4].second == ' ')
                    valid_moves.push_back(game_state->board_state[pos - 4].first); // UP-RIGHT
                else if(game_state->board_state[pos - 4].second == 'G' && game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos - 4, "UP-RIGHT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }  
            }
        }
        
        if (has_right){
            if (game_state->board_state[pos + 1].second == ' '){
                valid_moves.push_back(game_state->board_state[pos + 1].first); // RIGHT
            }
            else if(game_state->board_state[pos + 1].second == 'G' && game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 1, "RIGHT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }  

        }
                
        if (row == col){
            if (has_down && has_right){
                if (game_state->board_state[pos + 6].second == ' '){
                    valid_moves.push_back(game_state->board_state[pos + 6].first); // DOWN-RIGHT
                }
                else if(game_state->board_state[pos + 6].second == 'G' && game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos + 6, "DOWN_RIGHT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }  
            }
        }
        }
      g_pos++;
    }
  }
  bgh_valid_moves = valid_moves;
  return 0;
}

void Engine::changePosBaagh(){
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'T';
}

void Engine::changePosGoat(){
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'G';
}