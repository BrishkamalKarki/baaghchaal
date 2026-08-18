#include "result_scene.hpp"
#include "ui/ui_manager.hpp"
#include "engine/rules.hpp"
 
ResultScene::ResultScene(UIManager* uim) : ui_manager(uim)
{
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
}
 
ResultScene::~ResultScene()
{
  for (auto& [rect, tex] : texts){
    if (tex) SDL_DestroyTexture(tex);
  }
}
 
void ResultScene::clearLayers()
{
  for (auto& [rect, tex] : texts){
    if (tex) SDL_DestroyTexture(tex);
  }
  texts.clear();
  panels.clear();
}
 
void ResultScene::createRoundRects(float w, float h, float x, float y, float rad, SDL_Color* col, RoundedRect& r_rects, float diag_ang){
  r_rects = RoundedRect(w, h);
  r_rects.makeRoundRect(x, y, rad, col, diag_ang);
  panels.push_back(&r_rects);
}
 
void ResultScene::createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                SDL_Color color, float factor_x_text, float factor_y_text,
                SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect){
 
  surface = TTF_RenderText_Blended(font, text, 0, color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
 
  rect = {centerX + factor_x_text, centerY + factor_y_text, static_cast<float>(texture->w), static_cast<float>(texture->h)};
}
 
void ResultScene::addText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                           SDL_Color color, float factor_x, float factor_y){
  SDL_Surface* surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_FRect rect{};
 
  createBoardTexts(font, text.c_str(), centerX, centerY, color, factor_x, factor_y, surface, texture, rect);
  texts.push_back({rect, texture});
}
 
void ResultScene::createPillButton(RoundedRect& shape, Button& btn, SDL_FPoint center, SDL_FPoint size,
                                    const std::string& text, TTF_Font* font, SDL_Color fill, SDL_Color text_color){
  // Button STILL WANTS A TOP-LEFT POSITION FOR ITS OWN HIT-TEST RECT
  btn = Button({center.x - size.x / 2.f, center.y - size.y / 2.f}, size, text, font, fill);
  btn.text_color = text_color;
 
  // HIDE THE Button'S OWN SQUARE FILL - renderPillButton() DRAWS THE ROUNDED SHAPE IN ITS PLACE
  btn.shape.upper_color.a = 0;
 
  // FULL PILL - RADIUS IS HALF THE BUTTON'S HEIGHT, SAME ROUNDED LOOK AS THE START SCREEN'S BUTTONS
  shape = RoundedRect(size.x, size.y);
  shape.makeRoundRect(center.x, center.y, size.y / 2.f, &fill);
}
 
void ResultScene::renderPillButton(RoundedRect& shape, Button& btn){
  // ROUNDED FILL FIRST...
  SDL_RenderGeometry(renderer, NULL,
    shape.rounded_rect.data(), static_cast<int>(shape.rounded_rect.size()),
    shape.indices.data(), static_cast<int>(shape.indices.size()));
 
  // ...THEN THE BUTTON ON TOP, WHICH ONLY DRAWS ITS (INVISIBLE) FILL + ITS TEXT
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  btn.draw(renderer);
}
 
void ResultScene::buildUI(){
  this->clearLayers();
 
  GameState* gs = ui_manager->game_state;
 
  // DETERMINE THE WINNER - PREFER game_won IF THE ENGINE HAS SET IT, OTHERWISE
  // FALL BACK TO THE SAME CONDITIONS AS BoardEvaluator::checkWinner()
  std::string winner = gs->game_won;
  if (winner.empty()){
    if (gs->baagh_trapped >= Rules::TIGERS_TRAPPED) winner = "goat";
    else if (gs->goats_killed >= Rules::KILLED_GOATS) winner = "baagh";
  }
 
  bool baagh_won = (winner == "baagh");
 
  std::string winner_text = baagh_won ? "THE BAAGH WINS!" : "THE GOATS WIN!";
  std::string winner_sub;
  if (ui_manager->game_state->won_by_time_out){
    winner_sub = "  WON BY TIMEOUT ";
  }
  else{
    winner_sub  = baagh_won
        ? "ALL " + std::to_string(static_cast<int>(Rules::KILLED_GOATS)) + " GOATS WERE HUNTED DOWN"
        : "ALL " + std::to_string(static_cast<int>(Rules::TIGERS_TRAPPED)) + " BAAGHS WERE SURROUNDED";
  }
  SDL_Log("%s" ,winner_sub.c_str());



  // ACCENT COLOR MATCHES THE WINNING SIDE - AMBER/ORANGE FOR THE TIGER, GREENISH-YELLOW FOR THE
  // GOATS - SO THE HEADLINE AND DIVIDERS READ AS ONE DELIBERATE, WINNER-THEMED CARD
  SDL_Color accent = baagh_won ? theme.orange : theme.greenish_yellow;
 
  float center_x = static_cast<float>(w_w) / 2.f;
  float center_y = static_cast<float>(w_h) / 2.f;
 
  // DIMMED BACKDROP OVER WHATEVER THE BOARD LOOKED LIKE LAST
  bg_rect = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)};
 
  // LOGO, TOP LEFT - SAME SPOT AS THE BOARD SCENE
  baaghchaal_txt = {50.f, 50.f, 300.f, 110.f};
 
  // NO BOXED PANEL - TITLE, SCORE LINES, AND BUTTONS FLOAT DIRECTLY ON THE DIMMED FOREST
  // BACKDROP, SAME "NO TABLE" LOOK THE START SCREEN USES FOR ITS BUTTONS.
 
  // TITLE - BIG HEADLINE FONT, COLORED TO MATCH THE WINNING SIDE, PRECISELY CENTERED
  // (STRING WIDTH VARIES BETWEEN "THE BAAGH WINS!" / "THE GOATS WIN!" SO WE MEASURE THE
  // RENDERED TEXTURE AND CENTER OFF ITS ACTUAL WIDTH RATHER THAN A HARDCODED OFFSET)
  {
    SDL_Surface* surface = TTF_RenderText_Blended(ui_manager->font.font_bold, winner_text.c_str(), 0, accent);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    float w = static_cast<float>(texture->w);
    float h = static_cast<float>(texture->h);
    SDL_FRect rect{center_x - w / 2.f, center_y - 250.f, w, h};
    texts.push_back({rect, texture});
  }
 
  // SUBTITLE - REQUIRED RESULT SENTENCE, ALSO CENTERED OFF ITS MEASURED WIDTH
  {
    SDL_Surface* surface = TTF_RenderText_Blended(ui_manager->font.font_regular, winner_sub.c_str(), 0, theme.light_silver);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    float w = static_cast<float>(texture->w);
    float h = static_cast<float>(texture->h);
    SDL_FRect rect{center_x - w / 2.f, center_y - 175.f, w, h};
    texts.push_back({rect, texture});
  }
 
  // DIVIDER UNDER THE TITLE/SUBTITLE - ACCENT COLORED
  createRoundRects(460.f, 4.f, center_x, center_y - 130.f, 2.f, &accent, title_divider);
 
  // SCORE LINES - PLAIN, GENEROUSLY SPACED TEXT DIRECTLY ON THE CARD, NO BOXED PANEL
  std::string goats_killed_text = "GOATS KILLED    " + std::to_string(gs->goats_killed) + " / " + std::to_string(static_cast<int>(Rules::KILLED_GOATS));
  std::string baagh_trapped_text = "BAAGHS TRAPPED    " + std::to_string(gs->baagh_trapped) + " / " + std::to_string(static_cast<int>(Rules::TIGERS_TRAPPED));
  std::string mode_text = "GAME MODE    " + gs->game_mode;
 
  addText(ui_manager->font.font_regular_bold, goats_killed_text, center_x, center_y - 95.f, theme.white, 0.f, 0.f);
  addText(ui_manager->font.font_regular_bold, baagh_trapped_text, center_x, center_y - 55.f, theme.white, 0.f, 0.f);
  addText(ui_manager->font.font_regular_bold, mode_text, center_x, center_y - 15.f, theme.light_silver, 0.f, 0.f);
 
  // RE-CENTER EACH SCORE LINE OFF ITS OWN MEASURED WIDTH (THEY'RE ALL DIFFERENT LENGTHS)
  for (auto it = texts.end() - 3; it != texts.end(); ++it){
    it->first.x = center_x - it->first.w / 2.f;
  }
 
  // DIVIDER ABOVE THE BUTTONS
  createRoundRects(460.f, 4.f, center_x, center_y + 45.f, 2.f, &accent, stats_divider);
 
  // BUTTONS - SAME PILL STYLE AS THE START SCREEN. PLAY AGAIN USES THE ACCENT COLOR SO IT
  // READS AS THE PRIMARY ACTION; MAIN MENU STAYS THE NEUTRAL WOODEN-BROWN SECONDARY ACTION.
  createPillButton(play_again_btn_shape, play_again_btn, {center_x - 130.f, center_y + 130.f}, {220.f, 64.f},
                    "PLAY AGAIN", ui_manager->font.font_regular_bold, accent, theme.black);
  play_again_btn.onClick = [this](){ 
    MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
    if (onPlayAgain) onPlayAgain(); 
  };
 
  createPillButton(main_menu_btn_shape, main_menu_btn, {center_x + 130.f, center_y + 130.f}, {220.f, 64.f},
                    "MAIN MENU", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  main_menu_btn.onClick = [this](){ 
    MIX_PlayAudio(ui_manager->sound.mixer, ui_manager->sound.button_clicked);
    if (onMainMenu) onMainMenu(); 
  };
}
 
void ResultScene::render(){
  // SAME BACKGROUND TEXTURE AS EVERY OTHER SCENE, THEN DIM IT SO THE CARD STANDS OUT
  SDL_RenderTexture(renderer, ui_manager->texture.background, NULL, &bg_rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 170);
  SDL_RenderFillRect(renderer, &bg_rect);
 
  // LOGO
  SDL_RenderTexture(renderer, ui_manager->texture.baaghchaal_txt, NULL, &baaghchaal_txt);
 
  // LAYERED CARD + DIVIDER LINES
  for (const auto& panel : panels){
    SDL_RenderGeometry(renderer, NULL,
      panel->rounded_rect.data(),
      static_cast<int>(panel->rounded_rect.size()),
      panel->indices.data(),
      panel->indices.size());
  }
 
  // TITLE / SUBTITLE / SCORE LINES
  for (const auto& [rect, tex] : texts){
    SDL_RenderTexture(renderer, tex, NULL, &rect);
  }
 
  // BUTTONS
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  renderPillButton(play_again_btn_shape, play_again_btn);
  renderPillButton(main_menu_btn_shape, main_menu_btn);
}
 
void ResultScene::handleEvent(const SDL_Event& event){
  // BOTH BUTTONS ARE ALWAYS ON SCREEN - NO OVERLAY/SUBMENU TOGGLE ON THIS SCENE
  if (play_again_btn.handleEvent(event)) return;
  if (main_menu_btn.handleEvent(event)) return;
}
