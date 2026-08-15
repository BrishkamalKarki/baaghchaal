#include "board_evaluator.hpp" 
#include "engine.hpp" 

BoardEvaluator::BoardEvaluator(Engine* eng) : engine(eng){}

int BoardEvaluator::getValidMovesAt(int pos, std::string where){
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

        bool is_diagonal_point = (pos % 2 == 0);

        if (where != "none"){
            if (where == "UP" && has_up){
                if (engine->game_state->board_state[pos - 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 5});
                    return engine->game_state->board_state[pos - 5].first;
                }
            }
            else if (where == "DOWN" && has_down){
                if (engine->game_state->board_state[pos + 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 5});
                    return engine->game_state->board_state[pos + 5].first;
                }
            }
            else if (where == "LEFT" && has_left){
                if (engine->game_state->board_state[pos - 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 1});
                    return engine->game_state->board_state[pos - 1].first;
                }
            }
            else if (where == "RIGHT" && has_right){
                if (engine->game_state->board_state[pos + 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 1});
                    return engine->game_state->board_state[pos + 1].first;
                }
            }
            else if (where == "UP-LEFT" && is_diagonal_point && has_up && has_left){
                if (engine->game_state->board_state[pos - 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 6});
                    return engine->game_state->board_state[pos - 6].first;
                }
            }
            else if (where == "UP-RIGHT" && is_diagonal_point && has_up && has_right){
                if (engine->game_state->board_state[pos - 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 4});
                    return engine->game_state->board_state[pos - 4].first;
                }
            }
            else if (where == "DOWN-LEFT" && is_diagonal_point && has_down && has_left){
                if (engine->game_state->board_state[pos + 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 4});
                    return engine->game_state->board_state[pos + 4].first;
                }
            }
            else if (where == "DOWN_RIGHT" && is_diagonal_point && has_down && has_right){
                if (engine->game_state->board_state[pos + 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 6});
                    return engine->game_state->board_state[pos + 6].first;
                }
            }
            return -99;
        }


        if (is_diagonal_point){
            if (has_up && has_left){
                if (engine->game_state->board_state[pos - 6].second == ' ')
                    valid_moves.push_back(engine->game_state->board_state[pos - 6].first); // UP-LEFT
                else if(engine->game_state->board_state[pos - 6].second == 'G' && engine->game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos - 6, "UP-LEFT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }   
            }
        }
                
        if (has_left){
            if (engine->game_state->board_state[pos - 1].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos - 1].first); // LEFT
            }
            else if(engine->game_state->board_state[pos - 1].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 1, "LEFT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
                
        if (is_diagonal_point && has_down && has_left){
            if (engine->game_state->board_state[pos + 4].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos + 4].first); // DOWN-LEFT
            }
            else if(engine->game_state->board_state[pos + 4].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 4, "DOWN-LEFT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (has_up){
            if (engine->game_state->board_state[pos - 5].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos - 5].first); // UP
            }
            else if(engine->game_state->board_state[pos - 5].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 5, "UP");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (has_down){
            if (engine->game_state->board_state[pos + 5].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos + 5].first); // DOWN
            }
            else if(engine->game_state->board_state[pos + 5].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 5, "DOWN");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }   
        }
        
        if (is_diagonal_point && has_up && has_right){
            if (engine->game_state->board_state[pos - 4].second == ' ')
                valid_moves.push_back(engine->game_state->board_state[pos - 4].first); // UP-RIGHT
            else if(engine->game_state->board_state[pos - 4].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 4, "UP-RIGHT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }  
        }
        
        if (has_right){
            if (engine->game_state->board_state[pos + 1].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos + 1].first); // RIGHT
            }
            else if(engine->game_state->board_state[pos + 1].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 1, "RIGHT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }  

        }
                
        if (is_diagonal_point && has_down && has_right){
            if (engine->game_state->board_state[pos + 6].second == ' '){
                valid_moves.push_back(engine->game_state->board_state[pos + 6].first); // DOWN-RIGHT
            }
            else if(engine->game_state->board_state[pos + 6].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 6, "DOWN_RIGHT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }  
        }
        }
      g_pos++;
    }
  }
  bgh_valid_moves = valid_moves;
  return 0;
}

int BoardEvaluator::checkBaaghTrapped(){
    engine->game_state->baagh_trapped = 0;
    engine->game_state->baagh_trapped_at_pos.clear();

    temp_valid_moves = valid_moves;
    temp_edible_valid_moves = edible_valid_moves;
    std::string saved_turn = engine->game_state->turn;


    engine->game_state->turn = "baagh";

    for (const auto& [id, tp] : engine->game_state->board_state){
        if (tp == 'T'){
            valid_moves.clear();
            edible_valid_moves.clear();
            bgh_valid_moves.clear();

            getValidMovesAt(id - 1);

            if (bgh_valid_moves.empty()){
                engine->game_state->baagh_trapped_at_pos.push_back(id - 1);
                engine->game_state->baagh_trapped++;
            }
        }
    }

    valid_moves = temp_valid_moves;
    edible_valid_moves = temp_edible_valid_moves;
    engine->game_state->turn = saved_turn;

    // if (engine->game_state->baagh_trapped > 0)
        return engine->game_state->baagh_trapped;
    // else 
    //     return 0;
}

std::string BoardEvaluator::checkWinner(){
    checkBaaghTrapped();
    if (engine->game_state->baagh_trapped == 4){
        SDL_Log("GAME ENDED! GOAT WON!");
        return "goat";
    }

    if (engine->game_state->goats_killed == 5){
        SDL_Log("GAME ENDED! TIGER WON!");
        return "baagh";
    }

    return " ";
}