#include "board_evaluator.hpp"
#include "engine.hpp"
#include <SDL3/SDL.h>

BoardEvaluator::BoardEvaluator(Engine* eng) : engine(eng){}

int BoardEvaluator::getValidMovesAt(int pos, std::string where){
  int g_pos = 1;

  for (int row = 1; row <= 5; row++){
    for (int col = 1; col <= 5; col++){

      if (g_pos - 1 == pos){

        int row_of_pos = pos / 5;
        int col_of_pos = pos % 5;

        bool has_up    = row_of_pos > 0;
        bool has_down  = row_of_pos < 4;
        bool has_left  = col_of_pos > 0;
        bool has_right = col_of_pos < 4;

        bool is_main_diag = (row_of_pos == col_of_pos);
        bool is_anti_diag = (row_of_pos + col_of_pos == 4);

        if (where != "none"){
            if (where == "UP" && has_up){
                if (engine->game_state->board_state[pos - 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 5});
                    return pos - 5;
                }
            }
            else if (where == "DOWN" && has_down){
                if (engine->game_state->board_state[pos + 5].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 5});
                    return pos + 5;
                }
            }
            else if (where == "LEFT" && has_left){
                if (engine->game_state->board_state[pos - 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 1});
                    return pos - 1;
                }
            }
            else if (where == "RIGHT" && has_right){
                if (engine->game_state->board_state[pos + 1].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 1});
                    return pos + 1;
                }
            }
            else if (where == "UP-LEFT" && is_main_diag && has_up && has_left){
                if (engine->game_state->board_state[pos - 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 6});
                    return pos - 6;
                }
            }
            else if (where == "DOWN-RIGHT" && is_main_diag && has_down && has_right){
                if (engine->game_state->board_state[pos + 6].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 6});
                    return pos + 6;
                }
            }
            else if (where == "UP-RIGHT" && is_anti_diag && has_up && has_right){
                if (engine->game_state->board_state[pos - 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos - 4});
                    return pos - 4;
                }
            }
            else if (where == "DOWN-LEFT" && is_anti_diag && has_down && has_left){
                if (engine->game_state->board_state[pos + 4].second == ' '){
                    edible_valid_moves.push_back({pos, pos + 4});
                    return pos + 4;
                }
            }
            return -99;
        }


        if (is_main_diag){
            if (has_up && has_left){
                if (engine->game_state->board_state[pos - 6].second == ' ')
                    valid_moves.push_back(pos - 6); // UP-LEFT
                else if (engine->game_state->board_state[pos - 6].second == 'G' && engine->game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos - 6, "UP-LEFT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }
            }
            if (has_down && has_right){
                if (engine->game_state->board_state[pos + 6].second == ' '){
                    valid_moves.push_back(pos + 6); // DOWN-RIGHT
                }
                else if (engine->game_state->board_state[pos + 6].second == 'G' && engine->game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos + 6, "DOWN-RIGHT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }
            }
        }

        if (has_left){
            if (engine->game_state->board_state[pos - 1].second == ' '){
                valid_moves.push_back(pos - 1); // LEFT
            }
            else if (engine->game_state->board_state[pos - 1].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 1, "LEFT");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }
        }

        if (is_anti_diag){
            if (has_down && has_left){
                if (engine->game_state->board_state[pos + 4].second == ' '){
                    valid_moves.push_back(pos + 4); // DOWN-LEFT
                }
                else if (engine->game_state->board_state[pos + 4].second == 'G' && engine->game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos + 4, "DOWN-LEFT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }
            }
            if (has_up && has_right){
                if (engine->game_state->board_state[pos - 4].second == ' ')
                    valid_moves.push_back(pos - 4); // UP-RIGHT
                else if (engine->game_state->board_state[pos - 4].second == 'G' && engine->game_state->turn == "baagh"){
                    int edible_valid = getValidMovesAt(pos - 4, "UP-RIGHT");
                    if (edible_valid >= 0)
                        valid_moves.push_back(edible_valid);
                }
            }
        }

        if (has_up){
            if (engine->game_state->board_state[pos - 5].second == ' '){
                valid_moves.push_back(pos - 5); // UP
            }
            else if (engine->game_state->board_state[pos - 5].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos - 5, "UP");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }
        }

        if (has_down){
            if (engine->game_state->board_state[pos + 5].second == ' '){
                valid_moves.push_back(pos + 5); // DOWN
            }
            else if (engine->game_state->board_state[pos + 5].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 5, "DOWN");
                if (edible_valid >= 0)
                    valid_moves.push_back(edible_valid);
            }
        }

        if (has_right){
            if (engine->game_state->board_state[pos + 1].second == ' '){
                valid_moves.push_back(pos + 1); // RIGHT
            }
            else if (engine->game_state->board_state[pos + 1].second == 'G' && engine->game_state->turn == "baagh"){
                int edible_valid = getValidMovesAt(pos + 1, "RIGHT");
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

int BoardEvaluator::checkBaaghTrapped(bool update_real_state){
    int local_trapped = 0;
    std::vector<int> local_trapped_pos;
    std::vector<int> saved_valid_moves = valid_moves;
    std::vector<std::pair<int,int>> saved_edible = edible_valid_moves;
    std::string saved_turn = engine->game_state->turn;

    engine->game_state->turn = "baagh";

    for (const auto& [id, tp] : engine->game_state->board_state){
        if (tp == 'T'){
            valid_moves.clear();
            edible_valid_moves.clear();
            bgh_valid_moves.clear();

            getValidMovesAt(id - 1);

            if (bgh_valid_moves.empty()){
                local_trapped_pos.push_back(id - 1);
                local_trapped++;
            }
        }
    }

    valid_moves = saved_valid_moves;
    edible_valid_moves = saved_edible;
    engine->game_state->turn = saved_turn;

    if (update_real_state){
        engine->game_state->baagh_trapped = local_trapped;
        engine->game_state->baagh_trapped_at_pos = local_trapped_pos;
    }
    return local_trapped;
}

std::string BoardEvaluator::checkWinner(){
    int trapped = checkBaaghTrapped(false);

    if (trapped == 4){
        // SDL_Log("GAME ENDED! GOAT WON!");
        return "goat";
    }

    if (engine->game_state->goats_killed == 5){
        // SDL_Log("GAME ENDED! TIGER WON!");
        return "baagh";
    }

    return " ";
}