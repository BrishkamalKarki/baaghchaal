#include <iostream>
#include "game_config/board_config/board_config.hpp"
#include "ui/ui_manager.hpp"
#include <algorithm>
#include "game_config/theme_config.hpp"
#include <algorithm>

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

  // if (!ui_manager->engine->bot_busy){

    
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
              if (!ui_manager->engine->bot_busy){
                if (!ui_manager->game_state->game_paused){
                  std::string bot = this->ui_manager->game_state->bot_taken;
                  bool bot_mode = this->ui_manager->game_state->game_mode == "B V P";
                  if (bot_mode && bot == "baagh"){
                  }
                  else{
                    if (ui_manager->game_state->turn == "baagh" && ui_manager->game_state->audio_loaded){
                      this->ui_manager->state_changed = true;
                      this->ui_manager->engine->routeToEngine(pos, 'T');
                      this->clicked_at = pos;
                    }
                  }
                }
              }
            };
            if (!trapped){
              ui_manager->board_layer.baagh_pieces.push_back({pos + 1, std::make_pair(&baagh_circ[baagh], ui_manager->texture.baagh)});
            }
            else{
              ui_manager->board_layer.baagh_pieces.push_back({pos + 1, std::make_pair(&baagh_circ[baagh], ui_manager->texture.trapped_baagh)});
            }
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
              if (!ui_manager->game_state->game_paused){
                if (!ui_manager->engine->bot_busy){
                  if (this->ui_manager->game_state->bot_taken != "goat" && ui_manager->game_state->audio_loaded){
                    this->ui_manager->state_changed = true;
                    this->ui_manager->engine->routeToEngine(pos, 'G');
                    this->clicked_at = pos;
                  }
                }
              }
            };
            ui_manager->board_layer.goat_pieces.push_back({pos + 1, std::make_pair(&goat_circ[goat], ui_manager->texture.goat)});
            goat++;
          };
          pos++;
        }
      }
    
      
      // MAKING THE BOARD
      board_rect = {(static_cast<float>(w_w)/2)-400.f, (static_cast<float>(w_h)/2)-400.f, 800.f, 800.f};
      ui_manager->board_layer.textures.push_back({ui_manager->texture.board, &board_rect}); 
    
      int i = 0;
    
      cover_rect = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)}; 
    
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
      if (ui_manager->game_state->turn == "goat" && ui_manager->game_state->goats_in_hand > 0){
        // CLEAR FIRST - buildUI RE-RUNS ON EVERY state_changed AND WOULD
        // OTHERWISE ACCUMULATE DUPLICATE PLACEMENT TARGETS
        ui_manager->engine->board_eval.valid_moves.clear();
        for (int i = 0; i <= 24; i++){
          if (ui_manager->game_state->board_state[i].second != 'G' && ui_manager->game_state->board_state[i].second != 'T')
            ui_manager->engine->board_eval.valid_moves.push_back(i);
        }
      }
    
      for (int row=0; row<5; row++){
        for (int col=0; col<5; col++){
          if (std::find(ui_manager->engine->board_eval.valid_moves.begin(), ui_manager->engine->board_eval.valid_moves.end(), i) != ui_manager->engine->board_eval.valid_moves.end()){
            if (ui_manager->game_state->turn != ui_manager->game_state->bot_taken || ui_manager->game_state->game_mode == "P V P")
              board_pnt_btn[i].first = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.greenish_yellow};
            else 
              board_pnt_btn[i].first = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.invisible};
          }
          else 
            board_pnt_btn[i].first = {{bconfig.points[row][col].second.first, bconfig.points[row][col].second.second}, 15.f, "", nullptr, theme.invisible};
          
          ui_manager->board_layer.circular_buttons.push_back({i+1, &board_pnt_btn[i].first});
          board_pnt_btn[i].first.onClick = [this, i](){
            if (!ui_manager->engine->bot_busy){
              bool occupied = false;
              for (auto& [pos, type] : ui_manager->game_state->board_state){ // CHECKING IF THERE IS ANY ON THE CLICKED POSTITION
                  if (pos - 1 == i){
                    if (type != ' '){
                      occupied = true;
                      break;  
                    }
                  }
              }
              if (occupied == false && ui_manager->game_state->audio_loaded){
                this->ui_manager->state_changed = true;
                this->ui_manager->engine->routeToEngine(i);
                ui_manager->engine->board_eval.valid_moves.clear();
              }
            }
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
      createRoundRects(308.f, 158.f, 1400.f, 175.f, 22.f, &theme.black, out_tiger_info_board);
      createRoundRects(300.f, 150.f, 1400.f, 175.f, 22.f, &theme.wooden_brown, mid_tiger_info_board);
      createRoundRects(292.f, 142.f, 1400.f, 175.f, 22.f, &theme.wooden_dark_brown, in_tiger_info_board);
    
      // BOARD WHERE THE GOAT INFO IS SHOWN
      createRoundRects(308.f, 188.f, 1400.f, 390.f, 22.f, &theme.black, out_goat_info_board);
      createRoundRects(300.f, 180.f, 1400.f, 390.f, 22.f, &theme.wooden_brown, mid_goat_info_board);
      createRoundRects(292.f, 172.f, 1400.f, 390.f, 22.f, &theme.wooden_dark_brown, in_goat_info_board);
    
      // BOARD WHERE THE TIMER INFO IS SHOWN
      if (ui_manager->game_state->timer_mode){
        createRoundRects(308.f, 158.f - 25.f, 1400.f, 725.f - 150.f + 12.5f, 22.f, &theme.black, out_timer_info_board);
        createRoundRects(300.f, 150.f - 25.f, 1400.f, 725.f - 150.f + 12.5f, 22.f, &theme.wooden_brown, mid_timer_info_board);
        createRoundRects(292.f, 142.f - 25.f, 1400.f, 725.f - 150.f + 12.5f, 22.f, &theme.wooden_dark_brown, in_timer_info_board);
      }
    
      // BOARD WHERE THE CONFIGURATION INFO IS SHOWN
      createRoundRects(308.f, 308.f - 50.f, 200.f, 360.f - 75.f, 22.f, &theme.black, out_config_info_board);
      createRoundRects(300.f, 300.f - 50.f, 200.f, 360.f - 75.f, 22.f, &theme.wooden_brown, mid_config_info_board);
      createRoundRects(292.f, 292.f - 50.f, 200.f, 360.f - 75.f, 22.f, &theme.wooden_dark_brown, in_config_info_board);
    
      // BOARD WHERE THE TURN INFO IS SHOWN
      createRoundRects(308.f, 198.f - 50.f, 200.f, 705.f - 175.f, 22.f, &theme.black, out_turn_info_board); 
      createRoundRects(300.f, 190.f - 50.f, 200.f, 705.f - 175.f, 22.f, &theme.wooden_brown, mid_turn_info_board); 
      createRoundRects(292.f, 182.f - 50.f, 200.f, 705.f - 175.f, 22.f, &theme.wooden_dark_brown, in_turn_info_board); 
    
      // LINES IN THE BOARDS
      createRoundRects(200.f, 12.f, 1400.f, 150.f, 6.f, &theme.wooden_brown, baagh_board_line);
      createRoundRects(200.f, 12.f, 1400.f, 350.f, 6.f, &theme.wooden_brown, goat_board_line);
      if (ui_manager->game_state->timer_mode)
        createRoundRects(200.f, 12.f, 1400.f, 700.f - 125.f, 6.f, &theme.wooden_brown, timer_board_line);
      createRoundRects(200.f, 12.f, 200.f, 210.f, 6.f, &theme.wooden_brown, config_board_line);
      createRoundRects(200.f, 12.f, 200.f, 660.f - 150.f, 6.f, &theme.wooden_brown, turn_board_line);
    
      baagh_board_circ = CircularButton({1320.f, 100.f}, 40.f, "", nullptr, theme.white);
      // ui_manager->board_layer.board_tex_comp.push_back({&baagh_board_circ, ui_manager->texture.baagh});
    
      // CREATING THE TEXTS 
      createBoardTexts(ui_manager->font.font_bold, "BAAGH", 1400.f, 150.f, theme.white, -80, -40, baagh_title, baagh_title_tex, baagh_title_rect);
      createBoardTexts(ui_manager->font.font_bold, "GOAT", 1400.f, 350.f, theme.white, -80, -40, goat_title, goat_title_tex, goat_title_rect);
      if (ui_manager->game_state->timer_mode)
        createBoardTexts(ui_manager->font.font_bold, "TIMER", 1400.f, 700.f - 125.f, theme.white, -80, -40, timer_title, timer_title_tex, timer_title_rect);
      createBoardTexts(ui_manager->font.font_bold, "CONFIG", 200.f, 210.f, theme.white, -80, -40, conf_title, conf_title_tex, conf_title_rect);
      createBoardTexts(ui_manager->font.font_bold, "MOVE", 200.f, 660.f - 150.f, theme.white, -80, -40, turn_title, turn_title_tex, turn_title_rect);
    
      createBoardTexts(ui_manager->font.font_regular_bold, "TOTAL BAAGHS   4", 1400.f, 150.f, theme.white, -80, 20, normal_texts, normal_text_tex, normal_text_rect);
      int baagh_trapped = ui_manager->engine->board_eval.checkBaaghTrapped();
      
      std::string baagh_trapped_text = "BAAGHS TRAPPED   " + std::to_string(baagh_trapped);
      int goats_killed = ui_manager->game_state->goats_killed;
      createBoardTexts(ui_manager->font.font_regular_bold, baagh_trapped_text.c_str(), 1400.f, 150.f, theme.white, -80, 45, normal_texts, normal_text_tex, normal_text_rect);
      createBoardTexts(ui_manager->font.font_regular_bold, "TOTAL GOATS   20", 1400.f, 350.f, theme.white, -80, 20, normal_texts, normal_text_tex, normal_text_rect);
      std::string goatts_killed_text = "GOATS KILLED   " + std::to_string(goats_killed);
      int goats_in_hands = ui_manager->game_state->goats_in_hand;
      std::string goatts_ih_text = "GOATS IN HAND   " + std::to_string(goats_in_hands);
    
      createBoardTexts(ui_manager->font.font_regular_bold, goatts_ih_text.c_str(), 1400.f, 350.f, theme.white, -80, 45, normal_texts, normal_text_tex, normal_text_rect);
      createBoardTexts(ui_manager->font.font_regular_bold, goatts_killed_text.c_str(), 1400.f, 350.f, theme.white, -80, 70, normal_texts, normal_text_tex, normal_text_rect);
    
      std::string game_mode = "GAME MODE   " + ui_manager->game_state->game_mode;
      createBoardTexts(ui_manager->font.font_regular_bold, game_mode.c_str(), 200.f, 360.f, theme.white, -80, -130, normal_texts, normal_text_tex, normal_text_rect);
      std::string time_p_move = "TIME P MOVE   " + std::to_string(ui_manager->game_state->sec_p_move);
      createBoardTexts(ui_manager->font.font_regular_bold, time_p_move.c_str(), 200.f, 360.f, theme.white, -80, -105, normal_texts, normal_text_tex, normal_text_rect);
      if (ui_manager->game_state->game_mode == "B V P"){
        std::string bot_diff_level = "BOT LEVEL   " + ui_manager->game_state->bot_diff_level;
        createBoardTexts(ui_manager->font.font_regular_bold, bot_diff_level.c_str(), 200.f, 360.f, theme.white, -80, -55, normal_texts, normal_text_tex, normal_text_rect);
        std::string bot = "BOT   " + std::string(ui_manager->game_state->bot_taken == "baagh" ? "BAAAGH" : "GOAT");
        createBoardTexts(ui_manager->font.font_regular_bold, bot.c_str(), 200.f, 360.f, theme.white, -80, -30, normal_texts, normal_text_tex, normal_text_rect);
        std::string player = "HUMAN   " + std::string(ui_manager->game_state->human_taken == "baagh" ? "BAAAGH" : "GOAT");
        createBoardTexts(ui_manager->font.font_regular_bold, player.c_str(), 200.f, 360.f, theme.white, -80, -5, normal_texts, normal_text_tex, normal_text_rect);
      }
      else{
        std::string player1 = "PLAYER1   GOAT";
        createBoardTexts(ui_manager->font.font_regular_bold, player1.c_str(), 200.f, 360.f, theme.white, -80, -55, normal_texts, normal_text_tex, normal_text_rect);
        std::string player2 = "PLAYER2   BAAGH";
        createBoardTexts(ui_manager->font.font_regular_bold, player2.c_str(), 200.f, 360.f, theme.white, -80, -30, normal_texts, normal_text_tex, normal_text_rect);
      }
    
      std::string turn = "TURN   " + std::string(ui_manager->game_state->turn == "baagh" ? "BAAAGH" : "GOAT");
      std::transform(turn.begin(), turn.end(), turn.begin(), ::toupper);
      createBoardTexts(ui_manager->font.font_regular_bold, turn.c_str(), 200.f, 705.f - 175.f, theme.white, -80, -10, normal_texts, normal_text_tex, normal_text_rect);
      std::string move_no = "MOVE   " + std::to_string(ui_manager->game_state->move);
      createBoardTexts(ui_manager->font.font_regular_bold, move_no.c_str(), 200.f, 705.f - 175.f, theme.white, -80, 15, normal_texts, normal_text_tex, normal_text_rect);
    
      // PAUSE BUTTON - BOTTOM LEFT CORNER
      pause_btn_rect = {50.f, static_cast<float>(w_h) - 130.f, 120.f, 80.f};
      pause_hit_btn = Button({pause_btn_rect.x, pause_btn_rect.y}, {pause_btn_rect.w, pause_btn_rect.h}, "", nullptr, {0,0,0,0});
      pause_hit_btn.shape.upper_color.a = 0; // INVISIBLE FILL
      pause_hit_btn.onClick = [this](){
        if (!ui_manager->game_state->bot_thinking){
          showing_pause = true;
          ui_manager->game_state->game_paused = true;
          paused_time = SDL_GetTicks();
          ui_manager->time_paused = paused_time;
          MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
        }
    };
  // }

  // TIMER PART OVER IN HERE
  if (ui_manager->game_state->timer_mode && ui_manager->game_state->sec_p_move > 0){
    Uint64 now = SDL_GetTicks();

    std::string time_left_text;
    if (!ui_manager->game_state->game_paused){
      Uint64 elapsed_ms = now - ui_manager->engine->turn_start_ticks;
      int elapsed_sec = static_cast<int>(elapsed_ms / 1000);
      int remaining = ui_manager->game_state->sec_p_move - elapsed_sec;
      unpaused_time = 0; 
      paused_time = 0;
      if (remaining <= 0){
        remaining = 0;
        ui_manager->game_state->game_won = ui_manager->game_state->turn;
      } 
      // GOING TO THE RESULT SCREEN
      time_left_text = "TIME LEFT   " + std::to_string(remaining) + "S";
      if (remaining <= 0){
            std::string winner = ui_manager->game_state->turn == "baagh" ? "goat" : "baagh";
            ui_manager->game_state->game_won = winner;
            ui_manager->game_state->won_by_time_out = true;
      }
      saved_time_string = time_left_text;
      // createBoardTexts(ui_manager->font.font_regular_bold, time_left_text.c_str(), 1400.f, 700.f - 125.f, theme.white, -80, 20, normal_texts, normal_text_tex, normal_text_rect);
    }
    else{
      // createBoardTexts(ui_manager->font.font_regular_bold, saved_time_string.c_str(), 1400.f, 700.f - 125.f, theme.white, -80, 20, normal_texts, normal_text_tex, normal_text_rect);
    }
  };

  // UNDO BUTTON - NEXT TO THE PAUSE BUTTON BOTTOM LEFT
  undo_btn_rect = {190.f, static_cast<float>(w_h) - 130.f, 120.f, 80.f};
  undo_hit_btn = Button({undo_btn_rect.x, undo_btn_rect.y}, {undo_btn_rect.w, undo_btn_rect.h}, "", nullptr, {0,0,0,0});
  undo_hit_btn.shape.upper_color.a = 0; // INVISIBLE FILL
  undo_hit_btn.onClick = [this](){
    MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
    if (ui_manager->game_state->game_mode == "B V P"){
      ui_manager->engine->undoMove();
      ui_manager->engine->undoMove();
    }
    else{
      ui_manager->engine->undoMove();
    }
    ui_manager->state_changed = true;
  };

  buildPauseOverlay();
}

void BoardScene::createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                SDL_Color color, float factor_x_text, float factor_y_text,
                SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect){

  surface = TTF_RenderText_Blended(font, text, 0, color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);

  rect = {centerX + factor_x_text, centerY + factor_y_text, static_cast<float>(texture->w), static_cast<float>(texture->h)};
  ui_manager->board_layer.texts.push_back({rect, texture});
}

void BoardScene::createRoundRects(float w, float h, float x, float y, float rad, SDL_Color *col, RoundedRect& r_rects, float diag_ang){
  r_rects = RoundedRect(w, h);
  r_rects.makeRoundRect(x, y, rad, col, diag_ang);
  ui_manager->board_layer.info_boards.push_back(&r_rects);
}

       
void BoardScene::render(){
  
  // RENDERING THE BACKGROUND IMAGE
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
    SDL_RenderTexture(renderer, text, NULL, &rect);
  }

  // PAUSE BUTTON ICON - ALWAYS VISIBLE IN BOTTOM LEFT
  SDL_RenderTexture(renderer, ui_manager->texture.pause_button, NULL, &pause_btn_rect);

  // UNDO BUTTON ICON - NEXT TO THE PAUSE BUTTON
  SDL_RenderTexture(renderer, ui_manager->texture.undo_move, NULL, &undo_btn_rect);

  if (ui_manager->game_state->clicked_tobe_reloaded){
    ui_manager->game_state->clicked_tobe_reloaded = false;
  }

  // PAUSE OVERLAY - DRAWN ON TOP OF EVERYTHING WHEN ACTIVE
  if (showing_pause){
    renderPauseOverlay();
  }
} 


void createPausePillButton(SDL_Renderer* , RoundedRect& shape, Button& btn, SDL_FPoint center, SDL_FPoint size, const std::string& text, TTF_Font* font,
  SDL_Color fill, SDL_Color text_color){
  btn = Button({center.x - size.x / 2.f, center.y - size.y / 2.f}, size, text, font, fill);
  btn.text_color = text_color;
  btn.shape.upper_color.a = 0;
  shape = RoundedRect(size.x, size.y);
  shape.makeRoundRect(center.x, center.y, 15.f, &fill);
}

static void renderPausePillButton(SDL_Renderer* renderer, RoundedRect& shape, Button& btn){
  SDL_RenderGeometry(renderer, NULL,
    shape.rounded_rect.data(), static_cast<int>(shape.rounded_rect.size()),
    shape.indices.data(), static_cast<int>(shape.indices.size()));
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  btn.draw(renderer);
}

void BoardScene::buildPauseOverlay(){
  // CLEAN UP ANY PREVIOUS PAUSE TEXTURES
  for (auto& [rect, tex] : pause_texts){
    if (tex) SDL_DestroyTexture(tex);
  }
  pause_texts.clear();
  pause_panels.clear();

  float cx = static_cast<float>(w_w) / 2.f;
  float cy = static_cast<float>(w_h) / 2.f;
  
  // LAYERED WOODEN PANEL - SAME 3-DEPTH STYLE AS THE INFO OVERLAY
  float pw = 500.f, ph = 400.f;
  out_pause_board = RoundedRect(pw, ph);
  out_pause_board.makeRoundRect(cx, cy, 28.f, &theme.black);
  pause_panels.push_back(&out_pause_board);
  
  mid_pause_board = RoundedRect(pw - 8.f, ph - 8.f);
  mid_pause_board.makeRoundRect(cx, cy, 28.f, &theme.wooden_brown);
  pause_panels.push_back(&mid_pause_board);

  in_pause_board = RoundedRect(pw - 16.f, ph - 16.f);
  in_pause_board.makeRoundRect(cx, cy, 28.f, &theme.wooden_dark_brown);
  pause_panels.push_back(&in_pause_board);
  
  // TITLE TEXT 
  {
    SDL_Surface* surf = TTF_RenderText_Blended(ui_manager->font.font_bold, "PAUSED", 0, theme.white);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    float tw = static_cast<float>(surf->w);
    float th = static_cast<float>(surf->h);
    SDL_DestroySurface(surf);
    SDL_FRect r = {cx - tw / 2.f, cy - 160.f, tw, th};
    pause_texts.push_back({r, tex});
  }
  
  // PILL BUTTONS - RESUME / MAIN MENU / EXIT GAME
  createPausePillButton(renderer, resume_btn_shape, resume_btn, {cx, cy - 50.f}, {280.f, 60.f}, "RESUME", ui_manager->font.font_regular_bold, 
    theme.greenish_yellow, theme.black); resume_btn.onClick = [this](){ 
      showing_pause = false; 
      ui_manager->game_state->game_paused = false; 
      MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
      unpaused_time = SDL_GetTicks();
      ui_manager->time_resumed = unpaused_time;
      ui_manager->engine->turn_start_ticks += unpaused_time- paused_time;
    };
    
  createPausePillButton(renderer, mainmenu_btn_shape, mainmenu_btn, {cx, cy + 30.f}, {280.f, 60.f}, "MAIN MENU", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  mainmenu_btn.onClick = [this, uim = ui_manager](){ 
    showing_pause = false; 
    ui_manager->game_state->game_paused = false;
    MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
    uim->deferred_actions.push_back([uim]() {
      uim->engine->resetEngineState(); // JOINS ANY RUNNING BOT SEARCH
      *uim->game_state = GameState();
      uim->game_state->resetGameState();
      uim->engine->resetHistory(); // SEED THE FRESH BOARD AS UNDO BASE
      uim->result_scene.reset();
      uim->config_scene.reset();
      uim->startup_scene.reset();
      uim->pair_scene.clear();
      uim->pair_scene.push_back(ScenceOrd::INITIAL_SCENE);
      uim->board_scene.reset();
      uim->initScene();
      uim->state_changed = true;
    });
  };
  
  createPausePillButton(renderer, exitgame_btn_shape, exitgame_btn, {cx, cy + 110.f}, {280.f, 60.f}, "EXIT GAME", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  exitgame_btn.onClick = [this](){
    MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
    SDL_Event quit_event;
    quit_event.type = SDL_EVENT_QUIT;
    SDL_PushEvent(&quit_event);
  };
}

void BoardScene::renderPauseOverlay(){
  // DIM EVERYTHING BEHIND THE OVERLAY
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 170);
  SDL_FRect full = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)};
  SDL_RenderFillRect(renderer, &full);

  // PANEL
  for (const auto* panel : pause_panels){
    SDL_RenderGeometry(renderer, NULL,
      panel->rounded_rect.data(),
      static_cast<int>(panel->rounded_rect.size()),
      panel->indices.data(),
      panel->indices.size());
  }

  // TITLE
  for (const auto& [rect, tex] : pause_texts){
    SDL_RenderTexture(renderer, tex, NULL, &rect);
  }
  
  // BUTTONS
  renderPausePillButton(renderer, resume_btn_shape, resume_btn);
  renderPausePillButton(renderer, mainmenu_btn_shape, mainmenu_btn);
  renderPausePillButton(renderer, exitgame_btn_shape, exitgame_btn);
}

void BoardScene::handleEvent(const SDL_Event& event){
  if (showing_pause){
    // WHILE PAUSED, ONLY THE OVERLAY BUTTONS SHOULD RESPOND
    if (resume_btn.handleEvent(event)) return;
    if (mainmenu_btn.handleEvent(event)) return; // DO NOT access 'this' after this point
    if (exitgame_btn.handleEvent(event)) return;
    return;
  }
  // PAUSE BUTTON HIT-TEST
  pause_hit_btn.handleEvent(event);
  // UNDO BUTTON HIT-TEST
  undo_hit_btn.handleEvent(event);
}

BoardScene::BoardScene(UIManager* uim): ui_manager(uim){
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
  bconfig.makePoints();
  ui_manager->engine->turn_start_ticks = SDL_GetTicks();
}

BoardScene::~BoardScene(){
  clearLayers();
}