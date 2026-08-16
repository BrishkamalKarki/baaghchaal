#include "ui_manager.hpp"
#include <iostream>  

void UIManager::initScene()
{
  if (pair_scene.empty()) {
      pair_scene.push_back(ScenceOrd::INITIAL_SCENE);
      startup_scene = std::make_unique<StartupScene>(this);
      startup_scene->onPlayBot = [this]() {
          pair_scene.push_back(ScenceOrd::CONFIGURE_SCENE);
          initScene();
          state_changed = true; 
      };
      startup_scene->onExit = []() {
          SDL_Event quit_event;
          quit_event.type = SDL_EVENT_QUIT;
          SDL_PushEvent(&quit_event);
      };
      startup_scene->onInfo = []() {};
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
      board_scene->buildUI();
  } 
  else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
      if (!result_scene) {
          result_scene = std::make_unique<ResultScene>(this);
          result_scene->onPlayAgain = [this]() {
              game_state->resetGameState();
              deferred_actions.push_back([this]() {
                  // *game_state = GameState();
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
                  *game_state = GameState();
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
      result_scene->buildUI();
  }
} 

void UIManager::renderLayer()
{
  if (pair_scene.empty()) return;

  if (pair_scene.back() == ScenceOrd::INITIAL_SCENE) {
    if (startup_scene) startup_scene->render();
  } 
  else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
    if (config_scene) config_scene->render();
  } 
  else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
    bool is_bot_mode = (game_state->game_mode == "B V P");

      if (is_bot_mode){ // SYNCHRONOUS BOT MOVE 
        if (game_state->turn == game_state->bot_taken){
          engine->performBotMove();
          state_changed = true;
        }
      }

    // SDL_Log("===== GAME STATE DEBUG =====");
    // SDL_Log("turn: %s", game_state->turn.c_str());
    // SDL_Log("game_won: %s", game_state->game_won.c_str());
    // SDL_Log("bot_taken: %s", game_state->bot_taken.c_str());
    // SDL_Log("human_taken: %s", game_state->human_taken.c_str());
    // SDL_Log("game_mode: %s", game_state->game_mode.c_str());
    // SDL_Log("player1: %s", game_state->player1.c_str());
    // SDL_Log("player2: %s", game_state->player2.c_str());
    // SDL_Log("bot_diff_level: %s", game_state->bot_diff_level.c_str());
    // SDL_Log("timer_mode: %s", game_state->timer_mode ? "true" : "false");
    // SDL_Log("sec_p_move: %d", game_state->sec_p_move);
    // SDL_Log("move: %d", game_state->move);
    // SDL_Log("goats_in_hand: %d", game_state->goats_in_hand);
    // SDL_Log("goats_killed: %d", game_state->goats_killed);
    // SDL_Log("baagh_trapped: %d", game_state->baagh_trapped);
    // SDL_Log("goats_finished: %s", game_state->goats_finished ? "true" : "false");


      if (game_state->timer_mode && game_state->sec_p_move > 0){ 
        Uint64 elapsed_ms = SDL_GetTicks() - engine->turn_start_ticks;
        int current_sec = static_cast<int>(elapsed_ms / 1000);
        if (current_sec != last_timer_sec){
            last_timer_sec = current_sec;
            state_changed = true;
          }

          // SDL_Log("sec = %d", current_sec);
          // if (current_sec <= 0){
          //   std::string winner = game_state->turn == "baagh" ? "goat" : "baagh";
          //     game_state->game_won = winner;
          //     game_state->move = 0;
          //     game_state->turn = "goat";
          //     pair_scene.push_back(ScenceOrd::RESULT_SCREEN);
          //     initScene();
          //     state_changed = true;
          // }
      }
      if (state_changed){
        board_scene->buildUI();
        state_changed = false;
      }
      if (board_scene) board_scene->render();
  } 
  else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
    if (result_scene) result_scene->render();
  }
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
  for (auto& action : deferred_actions) {
      action();
  }
  deferred_actions.clear();
}

UIManager::UIManager(Config* conf, SDL_Window* win, SDL_Renderer* rend, Engine* engine, void* game_state): 
gameConf(conf), window(win), renderer(rend), texture(rend), engine(engine), game_state(static_cast<GameState*>(game_state)){
  texture.loadTexture();
}
