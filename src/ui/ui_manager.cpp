#include "ui_manager.hpp"
#include "game_scene/board_scene.hpp"
#include <iostream>  

void UIManager::initScene()
{
  if (pair_scene.empty()) {
      pair_scene.push_back(ScenceOrd::INITIAL_SCENE);
      startup_scene = std::make_unique<StartupScene>(this);
      startup_scene->onPlayBot = [this]() {
          pair_scene.push_back(ScenceOrd::CONFIGURE_SCENE);
          initScene();
          MIX_PlayAudio(sound.mixer, sound.button_clicked);
          state_changed = true; 
      };
      startup_scene->onExit = [this]() {
          MIX_PlayAudio(sound.mixer, sound.button_clicked);
          SDL_Event quit_event;
          quit_event.type = SDL_EVENT_QUIT;
          SDL_PushEvent(&quit_event);
      };
      startup_scene->onInfo = [this]() {
        MIX_PlayAudio(sound.mixer, sound.button_clicked);
      };
      startup_scene->buildUI();
  }
  else if (pair_scene.back() == ScenceOrd::INITIAL_SCENE) {
      if (!startup_scene) {
          startup_scene = std::make_unique<StartupScene>(this);                 
          startup_scene->onPlayBot = [this]() {
                deferred_actions.push_back([this]() {
                pair_scene.push_back(ScenceOrd::CONFIGURE_SCENE);
                initScene();
                state_changed = true;
              });
          };
          startup_scene->onExit = []() {
              SDL_Event quit_event;
              quit_event.type = SDL_EVENT_QUIT;
              SDL_PushEvent(&quit_event);
          };
          startup_scene->onInfo = []() {};
      }
      startup_scene->buildUI();
  } 
  else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
      if (!config_scene) {
          config_scene = std::make_unique<GameConfigerScene>(this);
      }
      config_scene->buildUI();
  } 
  else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
      if (!board_scene) {
        board_scene = std::make_unique<BoardScene>(this);
      }
      MIX_PlayAudio(sound.mixer, sound.game_start);
      game_state->audio_loaded = false;
      board_scene->buildUI();
  } 
  else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
      if (!result_scene) {
          result_scene = std::make_unique<ResultScene>(this);
          result_scene->onPlayAgain = [this]() {
            deferred_actions.push_back([this]() {
              engine->resetEngineState(); // JOINS ANY RUNNING BOT SEARCH
              game_state->resetGameState();
              engine->resetHistory(); // SEED THE FRESH BOARD AS UNDO BASE
              board_scene.reset();
              result_scene.reset();
              pair_scene.clear();
              pair_scene.push_back(ScenceOrd::BOARD_SCENE);
              initScene();
              state_changed = true;
            });
          };
          result_scene->onMainMenu = [this]() {
            deferred_actions.push_back([this]() {
              engine->resetEngineState(); // JOINS ANY RUNNING BOT SEARCH
              *game_state = GameState();
              game_state->resetGameState(); 
              engine->resetHistory();
              board_scene.reset();
              result_scene.reset();
              config_scene.reset();
              startup_scene.reset();
              pair_scene.clear();
              pair_scene.push_back(ScenceOrd::INITIAL_SCENE);
              initScene();
              state_changed = true;
            });
          };
        }
      MIX_PlayAudio(sound.mixer, sound.game_end);
      result_scene->buildUI();
  }
} 

void UIManager::renderLayer()
{
  if (pair_scene.empty()) return;

  game_state->audio_loaded = MIX_TrackPlaying(sound.track) ? false : true;

  if (pair_scene.back() == ScenceOrd::INITIAL_SCENE) {
    if (startup_scene) startup_scene->render();
  } 
  else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
    if (config_scene) config_scene->render();
  } 
  else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
    bool is_bot_mode = (game_state->game_mode == "B V P");

    
    if (is_bot_mode && !game_state->clicked_tobe_reloaded){ // ASYNC BOT MOVE
      if (engine->bot_result_pending){
        engine->performBotMove();
        state_changed = true;
      }
      else if (!engine->bot_busy &&game_state->turn == game_state->bot_taken){
        engine->startBotThink();
      }
    }
    
    if (game_state->timer_mode && game_state->sec_p_move > 0){ 
      Uint64 elapsed_ms = SDL_GetTicks() - engine->turn_start_ticks;
      int current_sec = static_cast<int>(elapsed_ms / 1000);
      if (current_sec != last_timer_sec){
        last_timer_sec = current_sec;
        state_changed = true;
      }
    }
    
    if (game_state->move_played){
      MIX_PlayAudio(sound.mixer, sound.moved);
      game_state->move_played = false;
    }
    
    if (state_changed && !engine->bot_busy){
      board_scene->buildUI();
      state_changed = false;
    }
    
    if (board_scene) board_scene->render();
    if (game_state->timer_mode && game_state->sec_p_move > 0){
      Uint64 now = SDL_GetTicks();
      Uint64 elapsed_ms = 0;
      if (!game_state->game_paused){
        if (engine->bot_busy)
          elapsed_ms = now - engine->bot.think_time;
        else
          elapsed_ms = now - engine->turn_start_ticks;
        int elapsed_sec = static_cast<int>(elapsed_ms / 1000);
        int remaining = game_state->sec_p_move - elapsed_sec;
        if (remaining < 0) remaining = 0;
        time_paused = 0;
        time_resumed = 0;
        if (remaining <= 0){
          std::string winner = game_state->turn == "baagh" ? "goat" : "baagh";
          game_state->game_won = winner;
          game_state->won_by_time_out = true;
        }
        saved_time_string = "TIME LEFT   " + std::to_string(remaining) + "S";
      }
      if (!saved_time_string.empty()){
        SDL_Surface* surface = TTF_RenderText_Blended(font.font_regular_bold, saved_time_string.c_str(), saved_time_string.length(), {255, 255, 255, 255});
        if (surface){
          SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
          SDL_DestroySurface(surface);
          if (texture){
            SDL_FRect rect = {1400.f - 80.f, 700.f - 125.f + 20.f, static_cast<float>(texture->w), static_cast<float>(texture->h)};
            SDL_RenderTexture(renderer, texture, NULL, &rect);
            SDL_DestroyTexture(texture);
          }
        }
      }
    }

    if (engine->just_trapped_tiger){
      MIX_PlayAudio(sound.mixer, sound.tiger_trapped);
      engine->just_trapped_tiger = false;
    }     
    if (engine->just_killed_goat){
      MIX_PlayAudio(sound.mixer, sound.goat_killed);
      engine->just_killed_goat = false;
    }  
  } 
  else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
    if (result_scene) result_scene->render();
  }

  game_state->audio_loaded = MIX_TrackPlaying(sound.track) ? false : true;
}

void UIManager::handleEvents(const SDL_Event& event) {
  if (pair_scene.empty()) return;
  
  if (pair_scene.back() == ScenceOrd::INITIAL_SCENE) {
    if (startup_scene) startup_scene->handleEvent(event);
  } else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
    if (config_scene) config_scene->handleEvents(event);
  } else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
      if (board_scene) board_scene->handleEvent(event);
  } else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
    if (result_scene) result_scene->handleEvent(event);
    
  }

  // EXECUTING ANY SCENECE TRANSITIONS OR RESETS THAT WERE QUEEUED 
  if (game_state->audio_loaded){
    for (auto& action : deferred_actions) {
      action();
    }
    deferred_actions.clear();
  }
}

UIManager::UIManager(Config* conf, SDL_Window* win, SDL_Renderer* rend, Engine* engine, void* game_state): 
gameConf(conf), window(win), renderer(rend), texture(rend), engine(engine), game_state(static_cast<GameState*>(game_state)){
  texture.loadTexture();
}
