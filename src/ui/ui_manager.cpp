#include "ui_manager.hpp"
#include <iostream>  

void UIManager::initScene()
{
  if (pair_scene.empty()) {
      pair_scene.push_back(ScenceOrd::INITIAL_SCENE);
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
      startup_scene->buildUI();
  } else if (pair_scene.back() == ScenceOrd::INITIAL_SCENE) {
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
  } else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
      if (!config_scene) {
          config_scene = std::make_unique<GameConfigerScene>(this);
      }
      config_scene->buildUI();
  } else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
      if (!board_scene) {
          board_scene = std::make_unique<BoardScene>(this);
      }
      board_scene->buildUI();
  } else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
      if (!result_scene) {
          result_scene = std::make_unique<ResultScene>(this);
          result_scene->onPlayAgain = [this]() {
              deferred_actions.push_back([this]() {
                  *game_state = GameState();
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
  } else if (pair_scene.back() == ScenceOrd::CONFIGURE_SCENE) {
      if (config_scene) config_scene->render();
  } else if (pair_scene.back() == ScenceOrd::BOARD_SCENE) {
      if (state_changed){
        board_scene->buildUI();
        state_changed = false;
      }
      if (board_scene) board_scene->render();
  } else if (pair_scene.back() == ScenceOrd::RESULT_SCREEN) {
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

  // Execute any scene transitions or resets that were queued during event handling
  for (auto& action : deferred_actions) {
      action();
  }
  deferred_actions.clear();
}

UIManager::UIManager(Config* conf, SDL_Window* win, SDL_Renderer* rend, Engine* engine, void* game_state): 
gameConf(conf), window(win), renderer(rend), texture(rend), engine(engine), game_state(static_cast<GameState*>(game_state)){
  texture.loadTexture();
}
