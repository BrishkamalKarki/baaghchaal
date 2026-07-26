#include "engine.hpp" 
#include <cmath>
#include <algorithm>

Engine::Engine(void* game_st, BoardConfig* b_conf) : b_conf(b_conf){
  turn = "GOAT";
  game_state = static_cast<GameState*>(game_st);
  b_conf->makePoints();
}

void Engine::routeToEngine(int pos, char type){
    for (const auto& [id, tp] : game_state->board_state){
        if (id - 1 == pos && (tp == 'G' || tp == 'T')){
            from_to.first = pos;
            getValidMovesAt(pos);
            SDL_Log("%d | %d %d", from_to.first, from_to.second, id);
            return;
        }
    }
    if (std::find(valid_moves.begin(), valid_moves.end(), pos + 1) != valid_moves.end()){
        from_to.second = pos;
        changePosBaagh();
    }
    
    else{ 
        SDL_Log("NOT A VALID MOVE");
        return;
    } 
    SDL_Log("%d | %d ", from_to.first, from_to.second);
};

void Engine::getValidMovesAt(int pos){
  int g_pos = 1;
  for (int row = 1; row <= 5; row++){
    for (int col = 1; col <= 5; col++){

      if (g_pos-1 == pos){
        valid_moves.clear();
        valid_moves.reserve(8);
        // if (row != 1 && row != 5 && col != 1 && col!= 5){

        int row_of_pos = pos % 5;      // 0-indexed row
        int col_of_pos = pos / 5;      // 0-indexed col

        bool has_up    = row_of_pos > 0;
        bool has_down  = row_of_pos < 4;
        bool has_left  = col_of_pos > 0;
        bool has_right = col_of_pos < 4;

         if (has_up && has_left && game_state->board_state[pos - 6].second == ' ')
            valid_moves.push_back(game_state->board_state[pos - 6].first); // UP-LEFT

        if (has_left && game_state->board_state[pos - 5].second == ' ')
            valid_moves.push_back(game_state->board_state[pos - 5].first); // LEFT

        if (has_down && has_left && game_state->board_state[pos - 4].second == ' ')
            valid_moves.push_back(game_state->board_state[pos - 4].first); // DOWN-LEFT

        if (has_up && game_state->board_state[pos - 1].second == ' ')
            valid_moves.push_back(game_state->board_state[pos - 1].first); // UP

        if (has_down && game_state->board_state[pos + 1].second == ' ')
            valid_moves.push_back(game_state->board_state[pos + 1].first); // DOWN

        if (has_up && has_right && game_state->board_state[pos + 4].second == ' ')
            valid_moves.push_back(game_state->board_state[pos + 4].first); // UP-RIGHT

        if (has_right && game_state->board_state[pos + 5].second == ' ')
            valid_moves.push_back(game_state->board_state[pos + 5].first); // RIGHT

        if (has_down && has_right && game_state->board_state[pos + 6].second == ' ')
            valid_moves.push_back(game_state->board_state[pos + 6].first); // DOWN-RIGHT
      }
      g_pos++;

    }
  }
}

void Engine::changePosBaagh(){
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'T';
}