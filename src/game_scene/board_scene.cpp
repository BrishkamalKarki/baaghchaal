#include <iostream>
#include "game_config/board_config/board_config.hpp"
#include "ui/ui_manager.hpp"
#include "game_config/theme_config.hpp"

void BoardScene::buildUI(){
  ui_manager->board_layer.rects.clear();
  ui_manager->board_layer.points.clear();

  int ww, wh;
  if (SDL_GetWindowSize(window, &ww, &wh)){
    SDL_Log("the width : %d, height: %d", ww, wh);
    w_w = ww;
    w_h = wh;
  }

  rrect = RoundedRect(500.f, 200.f);
  rrect.makeRoundRect(500.f, 500.f, 40.f, &theme.light_silver, 45.f);
  // ui_manager->board_layer.rounded_rects.push_back(&rrect);

  rrect1 = RoundedRect(400.f, 20.f);
  rrect1.makeRoundRect(800.f, 200.f, 4.f, &theme.light_silver);
  // ui_manager->board_layer.rounded_rects.push_back(&rrect1);

  rect1 = {200.f, 400.f, 100.f, 100.f};
  // ui_manager->board_layer.rects.push_back({&rect1, &theme.cyan});

  rect2 = {300.f, 500.f, 10.f, 100.f};
  // ui_manager->board_layer.rects.push_bac k({&rect2, &theme.light_silver});

  p11 = {120.f, 120.f};
  p55 = {800.f, 800.f};
  // ui_manager->board_layer.points.push_back({{&p11, &p55}, &theme.light_silver});
  







  // tada = {{200.f, 200.f}, 40.f, "", nullptr, theme.white};
  // tada.onClick = [](){
  //   SDL_Log("aksdjfa;lksdjf");
  // };
  // ui_manager->board_layer.circular_buttons.push_back(&tada);





  baagh_circ.clear();
  baagh_circ.resize(4);
  // MAKING THE BAAGH TEXTURES
  for (int baagh=0; baagh<4; baagh++){
    baagh_circ[baagh] = {{bconfig.baagh_ini[baagh].first, bconfig.baagh_ini[baagh].second}, 40.f, "", nullptr, theme.white};
    baagh_circ[baagh].onClick = [this, baagh](){
      this->ui_manager->engine->getValidMovesAt(baagh);
    };
    ui_manager->board_layer.baagh_pieces.push_back({baagh, std::make_pair(&baagh_circ[baagh], ui_manager->texture.baagh)});
  }



  

  // for (int baagh=1; baagh<=4; baagh++){
  // }
  // ui_manager->board_layer.textures.push_back({ui_manager->texture.baagh, &baagh_rect});
  
  // MAKING THE BOARD
  board_rect = {(static_cast<float>(ww)/2)-400.f, (static_cast<float>(wh)/2)-400.f, 800.f, 800.f};
  ui_manager->board_layer.textures.push_back({ui_manager->texture.board, &board_rect}); 

  int i = 0;
  rect.clear();
  rect.reserve(25);
  for (int row=0; row<5; row++){ // FOR EACH ROW
    for (int col=0; col<5; col++){ // FOR EACH COLUMN
      rect[i] = {bconfig.points[row][col].second.first-5, bconfig.points[row][col].second.second-5, 10.f, 10.f};
      // SDL_Log("%f, %f", bconfig.points[row][col].second.first, bconfig.points[row][col].second.second);
      // ui_manager->board_layer.rects.push_back({&rect[i], &theme.light_silver});
      i++;
    }
  }

  cover_rect = {0.f, 0.f, static_cast<float>(ww), static_cast<float>(wh)};
  // ui_manager->board_layer.textures.push_back({ui_manager->texture.baagh, NULL});


  // MAKEING THE LINES IN THE BOARD
  line_rects.clear();
  line_rects.resize(12); 
  i = 0;
  for (int turn=0; turn<2; turn++){ // FOR EACH VERTICAL LINES
    for (int ln=0; ln<5; ln++){ // FOR EACH HORIZONTAL LINES
      if (turn == 0){
        line_rects[i] = {bconfig.vrect_wid, bconfig.vrect_hg};
        line_rects[i].makeRoundRect(bconfig.lines[turn][ln].first, bconfig.lines[turn][ln].second, bconfig.rad, &theme.light_silver);
        ui_manager->board_layer.lines_rects.push_back(&line_rects[i]);
      }
      if (turn == 1){
        line_rects[i] = {bconfig.hrect_wid, bconfig.hrect_hg};
        line_rects[i].makeRoundRect(bconfig.lines[turn][ln].first, bconfig.lines[turn][ln].second, bconfig.rad, &theme.light_silver);
        ui_manager->board_layer.lines_rects.push_back(&line_rects[i]);
      }
      // SDL_Log("%f, %f", bconfig.points[row][col].second.first, bconfig.points[row][col].second.second);
      i++;
    }
  }

  // DRAWING THE TWO DIAGONALS (AT ANGLE 45 DEG AND 135 DEG)
  line_rects[i] = {bconfig.rect_diag_wid, bconfig.rect_diag_hg};
  line_rects[i].makeRoundRect(bconfig.lines[0][2].first, bconfig.lines[0][2].second, bconfig.rad, &theme.light_silver, 45.f);
  ui_manager->board_layer.lines_rects.push_back(&line_rects[i]);
  i++;
  line_rects[i] = {bconfig.rect_diag_wid, bconfig.rect_diag_hg};
  line_rects[i].makeRoundRect(bconfig.lines[0][2].first, bconfig.lines[0][2].second, bconfig.rad, &theme.light_silver, 135.f);
  ui_manager->board_layer.lines_rects.push_back(&line_rects[i]);

  // DRAWING THE CIRCULAR BUTTON IN EACH OF THE BOARD POINTS
  i = 0;
  board_pnt_btn.clear();
  board_pnt_btn.resize(25); 
  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      // SDL_Log("%f, %f are the points", bconfig.points[row][col].second.first-5, bconfig.points[row][col].second.second-5);
      board_pnt_btn[i] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 25.f, "", nullptr, theme.invisible};
      ui_manager->board_layer.circular_buttons.push_back(&board_pnt_btn[i]);
      int pos = i+1;
      board_pnt_btn[i].onClick = [pos](){
        SDL_Log("The %dth button is clicked.", pos);
      };
      i++;
    }
  }

  // STORING THE BACKGROUND TEXTURE
  bg_rect = {0.f, 0.f, static_cast<float>(ww), static_cast<float>(wh)};
  ui_manager->board_layer.background_texture.push_back({ui_manager->texture.background, NULL});

}  

void BoardScene::render(){

  // RENDERING THE BACKGROUND IMAGE
  // SDL_SetRenderLogicalPresentation(renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED); // DISABLEING THE LOGICAL PRESENTATION
  for (const auto& [bg, rect] : ui_manager->board_layer.background_texture){
    SDL_RenderTexture(renderer, bg, NULL, rect);
  }
  // SDL_SetRenderLogicalPresentation(renderer, 1600, 900, SDL_LOGICAL_PRESENTATION_LETTERBOX); // RE-ENABLEING THE LOGICAL PRESENTATION 
  // SDL_SetRenderLogicalPresentation(renderer, window_w, window_w/ui_manager->gameConf->max_aspect_ratio, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  // for (const auto& [points, col] : ui_manager->board_layer.points){
  //   SDL_SetRenderDrawColor(renderer, col->r, col->g, col->b, col->a);
  //   SDL_RenderLine(renderer, points.first->x, points.first->y, points.second->x, points.second->y);
  // }

  // for (const auto& round_rect : ui_manager->board_layer.rounded_rects){
  // SDL_RenderGeometry(renderer, NULL, 
  //   round_rect->rounded_rect.data(), 
  //   static_cast<int>(round_rect->rounded_rect.size()), 
  //   round_rect->indices.data(), 
  //   round_rect->indices.size());
  // }
  // for (const auto& round_rect : ui_manager->board_layer.rounded_rects){
  // SDL_RenderGeometry(renderer, NULL,
  //                       round_rect->rounded_rect.data(),
  //                       static_cast<int>(round_rect->rounded_rect.size()),
  //                       round_rect->indices.data(),
  //                       static_cast<int>(round_rect->indices.size()));
  // }

  for (const auto& button : ui_manager->board_layer.buttons)
  {
    // button->draw(renderer);
  }
  // RENDERING THE CIRCLE
  for (const auto& circ : ui_manager->board_layer.circles){
    // circ->render(renderer);
  }
  // for (const auto& round_rect : ui_manager->board_layer.rounded_rects){

  for (const auto& [tex, rect] : ui_manager->board_layer.textures){
    SDL_RenderTexture(renderer, tex, NULL, rect);
  }
  
  for (const auto& [rect, col] : ui_manager->board_layer.rects){
    SDL_SetRenderDrawColor(renderer, col->r, col->g, col->b, col->a);
    // SDL_RenderFillRect(renderer, rect);
  }

  for (const auto& line_rects : ui_manager->board_layer.lines_rects){
  SDL_RenderGeometry(renderer, NULL, 
    line_rects->rounded_rect.data(), 
    static_cast<int>(line_rects->rounded_rect.size()),
    line_rects->indices.data(), 
    line_rects->indices.size());
  } 

  // 
  for (const auto& brd_pnt_btn : ui_manager->board_layer.circular_buttons){
    brd_pnt_btn->draw(renderer);
  }

  // SHOWING THE BAAGH TEXTURES
  for (const auto& [id, baagh] : ui_manager->board_layer.baagh_pieces){
    baagh.first->draw(renderer, baagh.second);
  }
} 

BoardScene::BoardScene(UIManager* uim): ui_manager(uim)
{
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
  bconfig.makePoints();
}
