#include <iostream>
#include "game_config/board_config/board_config.hpp"
#include "ui/ui_manager.hpp"
#include "game_config/theme_config.hpp"

void BoardScene::clearLayers(){
  ui_manager->board_layer.rects.clear();
  ui_manager->board_layer.points.clear();
  ui_manager->board_layer.textures.clear();
  ui_manager->board_layer.background_texture.clear();
  ui_manager->board_layer.rounded_rects.clear();
  ui_manager->board_layer.buttons.clear();
  ui_manager->board_layer.circular_buttons.clear();
  ui_manager->board_layer.circles.clear();
  ui_manager->board_layer.lines_rects.clear();
  ui_manager->board_layer.baagh_pieces.clear();
  ui_manager->board_layer.goat_pieces.clear();
  line_rects.clear();
  board_pnt_btn.clear();
  rects.clear();
  rect.clear();
  baagh_circ.clear();
  clicked_at = -1;
}

void BoardScene::buildUI(){
  this->clearLayers();

  // MAKING THE BAAGH TEXTURES - CIRCULAR BUTTONS
  baagh_circ.resize(4);
  int pos = 0;
  int baagh = 0;
  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      if (ui_manager->game_state->board_state[pos].second == 'T'){
        baagh_circ[baagh] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 40.f, "", nullptr, theme.white};
        baagh_circ[baagh].onClick = [this, pos](){
          this->ui_manager->state_changed = true;
          this->ui_manager->engine->routeToEngine(pos, 'T');
          this->clicked_at = pos;
        };
        ui_manager->board_layer.baagh_pieces.push_back({pos + 1, std::make_pair(&baagh_circ[baagh], ui_manager->texture.baagh)});
        baagh++; 
      };
      pos++;
    }
  }
  
  // MAKING THE BOARD
  board_rect = {(static_cast<float>(w_w)/2)-400.f, (static_cast<float>(w_h)/2)-400.f, 800.f, 800.f};
  // SDL_Log(" %f   %f", (static_cast<float>(ww))/2-400.f, (static_cast<float>(wh))/2-400.f);
  ui_manager->board_layer.textures.push_back({ui_manager->texture.board, &board_rect}); 

  int i = 0;

  cover_rect = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)}; 
  // ui_manager->board_layer.textures.push_back({ui_manager->texture.baagh, NULL});


  // MAKEING THE LINES IN THE BOARD
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
  board_pnt_btn.resize(25); 
  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      if (std::find(ui_manager->engine->valid_moves.begin(), ui_manager->engine->valid_moves.end(), i+1) != ui_manager->engine->valid_moves.end())
        board_pnt_btn[i] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.greenish_yellow};
      else
        board_pnt_btn[i] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.invisible};
      
      ui_manager->board_layer.circular_buttons.push_back({i+1, &board_pnt_btn[i]});
      board_pnt_btn[i].onClick = [this, i](){
        this->ui_manager->state_changed = true;
        this->ui_manager->engine->routeToEngine(i);
        ui_manager->engine->valid_moves.clear();
      };
      i++;
    }
  }

  // STORING THE BACKGROUND TEXTURE
  bg_rect = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)};
  ui_manager->board_layer.background_texture.push_back({ui_manager->texture.background, NULL});

}  

void BoardScene::render(){

  // RENDERING THE BACKGROUND IMAGE
  // SDL_SetRenderLogicalPresentation(renderer, 0, 0, SDL_LOGICAL_PRESENTATION_DISABLED); // DISABLEING THE LOGICAL PRESENTATION
  for (const auto& [bg, rect] : ui_manager->board_layer.background_texture){
    SDL_RenderTexture(renderer, bg, NULL, rect);
  }

  for (const auto& [tex, rect] : ui_manager->board_layer.textures){
    SDL_RenderTexture(renderer, tex, NULL, rect);
  }
  
  for (const auto& [rect, col] : ui_manager->board_layer.rects){
    SDL_SetRenderDrawColor(renderer, col->r, col->g, col->b, col->a);
  }

  for (const auto& line_rects : ui_manager->board_layer.lines_rects){
  SDL_RenderGeometry(renderer, NULL, 
    line_rects->rounded_rect.data(), 
    static_cast<int>(line_rects->rounded_rect.size()),
    line_rects->indices.data(), 
    line_rects->indices.size());
  } 

  // LAYERING THE BOARD BY THE CIRCULAR BUTTONS
  for (const auto& [id, brd_pnt_btn] : ui_manager->board_layer.circular_buttons){
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