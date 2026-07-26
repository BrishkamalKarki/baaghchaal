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
