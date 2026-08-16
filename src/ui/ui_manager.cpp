#include "ui_manager.hpp"
#include <iostream>  

void UIManager::initScene()
{
  board_scene = std::make_unique <BoardScene>(this);
  pair_scene.push_back(ScenceOrd::BOARD_SCENE);
  pair_scene.push_back(ScenceOrd::BOARD_SCENE);
  board_scene->buildUI();
} 

void UIManager::renderLayer()
{
  bool is_bot_mode = (game_state->game_mode == "B V P");

  if (is_bot_mode){ // SYNCHRONOUS BOT MOVE (no threading = no data races)
    if (game_state->turn == game_state->bot_taken){
      engine->performBotMove();
      state_changed = true;
    }
  }

  
  if (game_state->timer_mode && game_state->sec_p_move > 0){ // MAKGING THE TIMER SYNCHROUNOUS
    Uint64 elapsed_ms = SDL_GetTicks() - engine->turn_start_ticks;
    int current_sec = static_cast<int>(elapsed_ms / 1000);
    if (current_sec != last_timer_sec){
        last_timer_sec = current_sec;
        state_changed = true;
    }
  }

  if (state_changed){
    board_scene->buildUI();
    state_changed = false;
  }

  board_scene->render();
}

UIManager::UIManager(Config* conf, SDL_Window* win, SDL_Renderer* rend, Engine* engine, void* game_state): 
gameConf(conf), window(win), renderer(rend), texture(rend), engine(engine), game_state(static_cast<GameState*>(game_state)){
  texture.loadTexture();
} 
