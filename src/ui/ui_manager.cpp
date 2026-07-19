#include "ui_manager.hpp"
#include <iostream>   // add if not present


void UIManager::initScene()
{
  board_scene = std::make_unique <BoardScene>(this);
  pair_scene.push_back(ScenceOrd::BOARD_SCENE);
  pair_scene.push_back(ScenceOrd::BOARD_SCENE);
  board_scene->setFont(font);
  board_scene->buildUI();
} 

void UIManager::renderLayer()
{
  // board_scene->buildUI();
  board_scene->render();
}

UIManager::UIManager(Config* conf, SDL_Window* win, SDL_Renderer* rend): 
gameConf(conf), window(win), renderer(rend), texture(rend){
  texture.loadTexture();
} 
