#include "engine.hpp" 

Engine::Engine(void* game_st){
  turn = "GOAT";
  game_state = static_cast<GameState*>(game_st);
}

void Engine::getValidMovesAt(int pos){
  int g_pos = 1;
  for (int row = 1; row <= 5; row++){
    for (int col = 1; col <= 5; col++){
      
      if (g_pos == pos){
        SDL_Log("%d %d", g_pos, pos);
        if (row != 1 && row != 5 && col != 1 && col!= 5){
          if (game_state->board_state[g_pos - 6].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 6].second);
          if (game_state->board_state[g_pos - 5].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 5].second);
          if (game_state->board_state[g_pos - 4].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 4].second);
          if (game_state->board_state[g_pos - 1].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 1].second);
          if (game_state->board_state[g_pos + 1].second == ' ') valid_moves.push_back(game_state->board_state[g_pos + 1].second);
          if (game_state->board_state[g_pos + 4].second == ' ') valid_moves.push_back(game_state->board_state[g_pos + 4].second);
          if (game_state->board_state[g_pos + 5].second == ' ') valid_moves.push_back(game_state->board_state[g_pos + 5].second);
          if (game_state->board_state[g_pos + 6].second == ' ') valid_moves.push_back(game_state->board_state[g_pos + 6].second);
        }


        // if (row != 1){
        //   if (game_state->board_state[g_pos - 5].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 5].second);
        //   if (col != 1)
        //     if (game_state->board_state[g_pos - 6].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 6].second);
        //   if (col + 1 < )
        //     if (game_state->board_state[g_pos - 6].second == ' ') valid_moves.push_back(game_state->board_state[g_pos - 6].second);

        // }
      }
      g_pos++;










    //   if (g_pos == pos){

    //     if (row == 1){
    //       valid_moves.push_back(pos + 1);
    //       if (col != 1 && col != 5){
    //         valid_moves.push_back(pos - 4);
    //         valid_moves.push_back(pos - 5);
    //         valid_moves.push_back(pos + 5);
    //         valid_moves.push_back(pos + 6);
    //       }
    //       if (col == 1){
    //         valid_moves.push_back(pos + 5);
    //         valid_moves.push_back(pos + 6);
    //       }
    //       if (col == 5){
    //         valid_moves.push_back(pos - 4);
    //         valid_moves.push_back(pos - 5);
    //       }
    //     }
    //     if (row == 5){

    //     }



    //   }

    }
  }
}