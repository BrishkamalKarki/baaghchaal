#include <iostream>
#include "board_scene.hpp"
#include "ui/ui_manager.hpp"

void BoardScene::buildUI(){
  ui_manager->board_layer.Rectangles.clear();
  rect1 = {w_w*0.2f, w_h*0.4f, 100.f, 100.f};
  SDL_RenderFillRect(renderer, &rect1);
  ui_manager->board_layer.Rectangles.push_back(&rect1);

  rect2 = {w_w*0.7f, w_h*0.2f, 10.f, 400.f};
  SDL_RenderFillRect(renderer, &rect1);
  ui_manager->board_layer.Rectangles.push_back(&rect2);
} 

void BoardScene::render(){
  SDL_SetRenderDrawColor(renderer, 11, 10, 6, 77);
  // for (auto rectElm : ui_manager->board_layer.Rectangles){
    SDL_RenderFillRect(renderer, ui_manager->board_layer.Rectangles[0]);
  // }
  SDL_SetRenderDrawColor(renderer, 111, 222, 6, 27);
  SDL_RenderFillRect(renderer, ui_manager->board_layer.Rectangles[1]);

}

BoardScene::BoardScene(UIManager* uim): ui_manager(uim)
{
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
}
