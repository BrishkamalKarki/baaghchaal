#include <iostream>
#include "board_scene.hpp"
#include "ui/ui_manager.hpp"
#include "ui_config.hpp"

void BoardScene::buildUI(){
  ui_manager->board_layer.rects.clear();
  ui_manager->board_layer.points.clear();

  int x, y;
  if (SDL_GetWindowSize(window, &x, &y)){
    SDL_Log("the width : %d, height: %d", x, y);
    w_w = x;
    w_h = y;
  }

  SDL_SetWindowAspectRatio(window, ui_manager->gameConf->max_aspect_ratio, ui_manager->gameConf->max_aspect_ratio); 
  SDL_SetRenderLogicalPresentation(renderer, 1920, 1080, SDL_LOGICAL_PRESENTATION_LETTERBOX); 

  // rect1 = {w_w*0.2f, w_h*0.4f, (static_cast<float>(w_w)/1920)*100.f, (static_cast<float>(w_h)/1011)*100.f};
  // SDL_RenderFillRect(renderer, &rect1);
  // ui_manager->board_layer.rects.push_back({&rect1, &theme.cyan});

  // rect2 = {w_w*0.3f, w_h*0.5f, (static_cast<float>(w_w)/1920)*10.f, (static_cast<float>(w_h)/1011)*100.f};
  // // SDL_RenderFillRect(renderer, &rect1);
  // ui_manager->board_layer.rects.push_back({&rect2, &theme.black});

  rrect = RoundedRect(300.f, 100.f);
  rrect.makeRoundRect(500.f, 500.f, 10.f, &theme.black);
  ui_manager->board_layer.rounded_rects.push_back(&rrect);

  rrect1 = RoundedRect(400.f, 20.f);
  rrect1.makeRoundRect(800.f, 200.f, 4.f, &theme.black);
  ui_manager->board_layer.rounded_rects.push_back(&rrect1);
//   rrect = RoundedRect(300.f, 100.f, 0.15f);   // width, height, corner radius %
// rrect.makeRoundRect(500.f, 500.f, &theme.black);  // x,y = center, not top-left
// ui_manager->board_layer.rounded_rects.push_back(&rrect);

  rect1 = {200.f, 400.f, 100.f, 100.f};
  // SDL_RenderFillRect(renderer, &rect1);
  ui_manager->board_layer.rects.push_back({&rect1, &theme.cyan});

  rect2 = {300.f, 500.f, 10.f, 100.f};
  // SDL_RenderFillRect(renderer, &rect1);
  ui_manager->board_layer.rects.push_back({&rect2, &theme.black});

  p11 = {120.f, 120.f};
  p55 = {800.f, 800.f};
  ui_manager->board_layer.points.push_back({{&p11, &p55}, &theme.black});
  // ui_manager->board_layer.points.push_back({&p55, &theme.background});
  
  goat_rect = {300.f, 600.f, 200.f, 200.f};
  ui_manager->board_layer.textures.push_back({ui_manager->texture.goat, &goat_rect});

  if (!font)
  {
    SDL_Log("ERROR: Font was not set!");
  }
  
  playButton = Button(
    {400.f, 300.f}, //TOP-LEFT POSITION COORDINATES
    {250.f, 80.f}, //SIZE (LENGTH, BREADTH)
    "Play", //TEXT ON BUTTON
    font, //FONT
    {200, 200, 200, 255} //COLOR
  );

  //ONCLICK FUNCTION
  playButton.onClick = []()
  {
    SDL_Log("Play button pressed!");
  };

  ui_manager->board_layer.buttons.push_back(&playButton);

  circButton = CircularButton(
    {800.f, 350.f}, //CENTER COORDINATES
    70.f, //RADIUS
    "Circ", //TEXT ON BUTTON
    font, //FONT
    {200, 200, 200, 255} //COLOR
  );
  
  // ONCLICK FUNCTION
  circButton.onClick = []()
  {
      SDL_Log("Circular Button clicked!");
  };

  ui_manager->board_layer.circular_buttons.push_back(&circButton);
} 

void BoardScene::render(){
  // SDL_SetRenderDrawColor(renderer, );
  // for (auto rectElm : ui_manager->board_layer.rects){
    // SDL_RenderFillRect(renderer, ui_manager->board_layer.rects[0]);

  // int x, y;
  // if (SDL_GetWindowSize(window, &x, &y)){
  //   // SDL_Log("the width : %d, height: %d", x, y);
  //   w_w = x;
  //   w_h = y;
  //   // if (static_cast<float>(w_w)/static_cast<float>(w_h) != ui_manager->gameConf->aspect_ratio){
  //   // SDL_SetWindowAspectRatio(window, ui_manager->gameConf->max_aspect_ratio, ui_manager->gameConf->max_aspect_ratio);
  //   // }
  // }

  for (const auto& [rect, col] : ui_manager->board_layer.rects){
    SDL_SetRenderDrawColor(renderer, col->r, col->g, col->b, col->a);
    SDL_RenderFillRect(renderer, rect);
  }

  for (const auto& [points, col] : ui_manager->board_layer.points){
    SDL_SetRenderDrawColor(renderer, col->r, col->g, col->b, col->a);
    SDL_RenderLine(renderer, points.first->x, points.first->y, points.second->x, points.second->y);
  }

  for (const auto& [tex, rect] : ui_manager->board_layer.textures){
    SDL_RenderTexture(renderer, ui_manager->texture.goat, NULL, rect);
  }

  // SDL_Log("this is the thing: %d", ui_manager->board_layer.rounded_rects[0]->vertx);
  // for (const auto& round_rect : ui_manager->board_layer.rounded_rects){
  //   SDL_RenderGeometry(renderer, NULL, round_rect->rounded_rect, round_rect->vertx*4, NULL, 0);
  // }
  for (const auto& round_rect : ui_manager->board_layer.rounded_rects){
  SDL_RenderGeometry(renderer, NULL, 
    round_rect->rounded_rect.data(), 
    static_cast<int>(round_rect->rounded_rect.size()), 
    round_rect->indices.data(), 
    round_rect->indices.size());
}
// for (const auto& round_rect : ui_manager->board_layer.rounded_rects){
//   SDL_RenderGeometry(renderer, NULL,
//                       round_rect->rounded_rect.data(),
//                       static_cast<int>(round_rect->rounded_rect.size()),
//                       round_rect->indices.data(),
//                       static_cast<int>(round_rect->indices.size()));
// }

  for (const auto& button : ui_manager->board_layer.buttons)
  {
    button->draw(renderer);
  }

  for (const auto& c_button : ui_manager->board_layer.circular_buttons)
  {
    c_button->draw(renderer);
  }
} 

BoardScene::BoardScene(UIManager* uim): ui_manager(uim)
{
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
}
