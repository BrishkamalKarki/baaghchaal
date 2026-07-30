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
  ui_manager->board_layer.texture_components.clear();
  ui_manager->board_layer.texts.clear();
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
  bool trapped = false;
  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      if (ui_manager->game_state->board_state[pos].second == 'T'){
        for (int& bgh_tpos : ui_manager->game_state->baagh_trapped_at_pos){
          if (pos == bgh_tpos){
            trapped = true;
          }
        }
        baagh_circ[baagh] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 40.f, "", nullptr, theme.white};
        baagh_circ[baagh].onClick = [this, pos](){
          this->ui_manager->state_changed = true;
          this->ui_manager->engine->routeToEngine(pos, 'T');
          this->clicked_at = pos;
        };
        if (!trapped)
          ui_manager->board_layer.baagh_pieces.push_back({pos + 1, std::make_pair(&baagh_circ[baagh], ui_manager->texture.baagh)});
        else
          ui_manager->board_layer.baagh_pieces.push_back({pos + 1, std::make_pair(&baagh_circ[baagh], ui_manager->texture.trapped_baagh)});
        trapped = false;
        baagh++; 
      };
      pos++;
    }
  }

  // MAKING THE GOAT TEXTURES - CIRCULAR BUTTONS
  goat_circ.resize(20);
  pos = 0;
  int goat = 0;
  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      if (ui_manager->game_state->board_state[pos].second == 'G'){
        goat_circ[goat] = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 40.f, "", nullptr, theme.white};
        goat_circ[goat].onClick = [this, pos](){
          this->ui_manager->state_changed = true;
          this->ui_manager->engine->routeToEngine(pos, 'G');
          this->clicked_at = pos;
        };
        ui_manager->board_layer.goat_pieces.push_back({pos + 1, std::make_pair(&goat_circ[goat], ui_manager->texture.goat)});
        goat++; 
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
  // if (ui_manager->game_state->turn == "goat" && ui_manager->game_state->goats_in_hand > 0){
  // for (int i = 0; i <= 24; i++){
  //   // SDL_Log("%d %c", i, ui_manager->game_state->board_state[i].second);
  //   if (ui_manager->game_state->board_state[i].second != 'G' || ui_manager->game_state->board_state[i].second != 'T')
  //     ui_manager->engine->valid_moves.push_back(i);
  //   }
  // }

  for (int row=0; row<5; row++){
    for (int col=0; col<5; col++){
      if (std::find(ui_manager->engine->valid_moves.begin(), ui_manager->engine->valid_moves.end(), i+1) != ui_manager->engine->valid_moves.end()){
        SDL_Log("i am choosing the themes dude");
        board_pnt_btn[i].first = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.greenish_yellow};
      }
      else
        board_pnt_btn[i].first = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.invisible};
      
      ui_manager->board_layer.circular_buttons.push_back({i+1, &board_pnt_btn[i].first});
      board_pnt_btn[i].first.onClick = [this, i](){
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

  // PUTTING THE TEXTIMAGE IN THE TOP LEFT
  baaghchaal_txt = {50.f, 50.f, 300.f, 110.f};
  ui_manager->board_layer.texture_components.push_back({ui_manager->texture.baaghchaal_txt, &baaghchaal_txt});

  // BOARD WHERE THE TIGER INFO IS SHOWN
  createRoundRects(308.f, 258.f, 1400.f, 175.f, 22.f, &theme.black, out_tiger_info_board);
  createRoundRects(300.f, 250.f, 1400.f, 175.f, 22.f, &theme.wooden_brown, mid_tiger_info_board);
  createRoundRects(292.f, 242.f, 1400.f, 175.f, 22.f, &theme.wooden_dark_brown, in_tiger_info_board);

  // BOARD WHERE THE GOAT INFO IS SHOWN
  createRoundRects(308.f, 258.f, 1400.f, 475.f, 22.f, &theme.black, out_goat_info_board);
  createRoundRects(300.f, 250.f, 1400.f, 475.f, 22.f, &theme.wooden_brown, mid_goat_info_board);
  createRoundRects(292.f, 242.f, 1400.f, 475.f, 22.f, &theme.wooden_dark_brown, in_goat_info_board);

  // BOARD WHERE THE TIMER INFO IS SHOWN
  createRoundRects(308.f, 158.f, 1400.f, 725.f, 22.f, &theme.black, out_timer_info_board);
  createRoundRects(300.f, 150.f, 1400.f, 725.f, 22.f, &theme.wooden_brown, mid_timer_info_board);
  createRoundRects(292.f, 142.f, 1400.f, 725.f, 22.f, &theme.wooden_dark_brown, in_timer_info_board);

  // BOARD WHERE THE CONFIGURATION INFO IS SHOWN
  createRoundRects(308.f, 408.f, 200.f, 360.f, 22.f, &theme.black, out_config_info_board);
  createRoundRects(300.f, 400.f, 200.f, 360.f, 22.f, &theme.wooden_brown, mid_config_info_board);
  createRoundRects(292.f, 392.f, 200.f, 360.f, 22.f, &theme.wooden_dark_brown, in_config_info_board);

  // BOARD WHERE THE TURN INFO IS SHOWN
  createRoundRects(308.f, 198.f, 200.f, 705.f, 22.f, &theme.black, out_turn_info_board);
  createRoundRects(300.f, 190.f, 200.f, 705.f, 22.f, &theme.wooden_brown, mid_turn_info_board);
  createRoundRects(292.f, 182.f, 200.f, 705.f, 22.f, &theme.wooden_dark_brown, in_turn_info_board);

  // LINES IN THE BOARDS
  createRoundRects(200.f, 12.f, 1400.f, 100.f, 6.f, &theme.wooden_brown, baagh_board_line);
  createRoundRects(200.f, 12.f, 1400.f, 400.f, 6.f, &theme.wooden_brown, goat_board_line);
  createRoundRects(200.f, 12.f, 1400.f, 700.f, 6.f, &theme.wooden_brown, timer_board_line);
  createRoundRects(200.f, 12.f, 200.f, 210.f, 6.f, &theme.wooden_brown, config_board_line);
  createRoundRects(200.f, 12.f, 200.f, 660.f, 6.f, &theme.wooden_brown, turn_board_line);


  baagh_board_circ = CircularButton({1320.f, 100.f}, 40.f, "", nullptr, theme.white);
  // ui_manager->board_layer.board_tex_comp.push_back({&baagh_board_circ, ui_manager->texture.baagh});

  createBoardTexts(ui_manager->font.font_bold, "BAAGH", 1400.f, 100.f, theme.white, -80, -40, baagh_title, baagh_title_tex, baagh_title_rect);
  createBoardTexts(ui_manager->font.font_bold, "GOAT", 1400.f, 400.f, theme.white, -80, -40, goat_title, goat_title_tex, goat_title_rect);
  createBoardTexts(ui_manager->font.font_bold, "TIMER", 1400.f, 700.f, theme.white, -80, -40, timer_title, timer_title_tex, timer_title_rect);
  createBoardTexts(ui_manager->font.font_bold, "CONFIG", 200.f, 210.f, theme.white, -80, -40, conf_title, conf_title_tex, conf_title_rect);
  createBoardTexts(ui_manager->font.font_bold, "TURN", 200.f, 660.f, theme.white, -80, -40, turn_title, turn_title_tex, turn_title_rect);
};


void BoardScene::createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                SDL_Color color, float factor_x_text, float factor_y_text,
                SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect){

  surface = TTF_RenderText_Blended(font, text, 0, color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);

  rect = {centerX + factor_x_text, centerY + factor_y_text, static_cast<float>(texture->w), static_cast<float>(texture->h)};
  ui_manager->board_layer.texts.push_back({&rect, texture});
}

void BoardScene::createRoundRects(float w, float h, float x, float y, float rad, SDL_Color *col, RoundedRect& r_rects, float diag_ang){
  r_rects = RoundedRect(w, h);
  r_rects.makeRoundRect(x, y, rad, col, diag_ang);
  ui_manager->board_layer.info_boards.push_back(&r_rects);
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

  
  // SHOWING THE GOAT TEXTURES
  for (const auto& [id, goat] : ui_manager->board_layer.goat_pieces){
    goat.first->draw(renderer, goat.second);
  }

    // SHOWING THE TEXTURES COMPONENTS
  for (const auto& [tex, rect] : ui_manager->board_layer.texture_components){
    SDL_RenderTexture(renderer, tex, NULL, rect);
  }

  // SHOWING THE INFO BOARDS
  for (const auto& rect : ui_manager->board_layer.info_boards){
    SDL_RenderGeometry(renderer, NULL, 
    rect->rounded_rect.data(), 
    static_cast<int>(rect->rounded_rect.size()),
    rect->indices.data(), 
    rect->indices.size());
  }

  // SHOWING THE TEXTURES IN THE INFOS BOARDS
  for (const auto& [circ, tex] : ui_manager->board_layer.board_tex_comp){
    circ->draw(renderer, tex);
  }
  
  for (const auto& [rect, text] : ui_manager->board_layer.texts){
    SDL_RenderTexture(renderer, text, NULL, rect);
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