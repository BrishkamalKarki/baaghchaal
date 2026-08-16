#include "startup_scene.hpp"
#include "ui/ui_manager.hpp"
 
StartupScene::StartupScene(UIManager* uim) : ui_manager(uim)
{
  w_w = ui_manager->gameConf->windowW;
  w_h = ui_manager->gameConf->windowH;
  window = ui_manager->window;
  renderer = ui_manager->renderer;
}
 
StartupScene::~StartupScene()
{
  for (auto& [rect, tex] : texts){
    if (tex) SDL_DestroyTexture(tex);
  }
  for (auto& [rect, tex] : info_texts){
    if (tex) SDL_DestroyTexture(tex);
  }
}
 
void StartupScene::clearLayers()
{
  for (auto& [rect, tex] : texts){
    if (tex) SDL_DestroyTexture(tex);
  }
  texts.clear();
 
  for (auto& [rect, tex] : info_texts){
    if (tex) SDL_DestroyTexture(tex);
  }
  info_texts.clear();
  info_panels.clear();
}
 
void StartupScene::createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                SDL_Color color, float factor_x_text, float factor_y_text,
                SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect){
 
  surface = TTF_RenderText_Blended(font, text, 0, color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
 
  rect = {centerX + factor_x_text, centerY + factor_y_text, static_cast<float>(texture->w), static_cast<float>(texture->h)};
}
 
void StartupScene::addText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                           SDL_Color color, float factor_x, float factor_y){
  SDL_Surface* surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_FRect rect{};
 
  createBoardTexts(font, text.c_str(), centerX, centerY, color, factor_x, factor_y, surface, texture, rect);
  texts.push_back({rect, texture});
}
 
void StartupScene::addInfoText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                           SDL_Color color, float factor_x, float factor_y){
  SDL_Surface* surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_FRect rect{};
 
  createBoardTexts(font, text.c_str(), centerX, centerY, color, factor_x, factor_y, surface, texture, rect);
  info_texts.push_back({rect, texture});
}
 
void StartupScene::createPillButton(RoundedRect& shape, Button& btn, SDL_FPoint center, SDL_FPoint size,
                                     const std::string& text, TTF_Font* font, SDL_Color fill, SDL_Color text_color){
  // Button STILL WANTS A TOP-LEFT POSITION FOR ITS OWN HIT-TEST RECT
  btn = Button({center.x - size.x / 2.f, center.y - size.y / 2.f}, size, text, font, fill);
  btn.text_color = text_color;
 
  // HIDE THE Button'S OWN SQUARE FILL - renderPillButton() DRAWS THE ROUNDED SHAPE IN ITS PLACE
  btn.shape.upper_color.a = 0;
 
  // FULL PILL - RADIUS IS HALF THE BUTTON'S HEIGHT, SAME ROUNDED LOOK AS THE MOCKUP'S BUTTONS
  shape = RoundedRect(size.x, size.y);
  shape.makeRoundRect(center.x, center.y, 15.f, &fill);
}
 
void StartupScene::renderPillButton(RoundedRect& shape, Button& btn){
  // ROUNDED FILL FIRST...
  SDL_RenderGeometry(renderer, NULL,
    shape.rounded_rect.data(), static_cast<int>(shape.rounded_rect.size()),
    shape.indices.data(), static_cast<int>(shape.indices.size()));
 
  // ...THEN THE BUTTON ON TOP, WHICH ONLY DRAWS ITS (INVISIBLE) FILL + ITS TEXT
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  btn.draw(renderer);
}
 
void StartupScene::buildUI(){
  this->clearLayers();
  showing_info = false;
 
  float center_x = static_cast<float>(w_w) / 2.f;
 
  // FULL BACKDROP
  bg_rect = {0.f, 0.f, static_cast<float>(w_w), static_cast<float>(w_h)};
 
  // GLOWING LOGO - BIG, CENTERED, TOP OF SCREEN
  baaghchaal_txt = {center_x - 260.f, 50.f, 520.f, 165.f};
 
  // MAIN MENU - PLAY / INFO / EXIT, STACKED. SAME SIZE {280,80} FOR ALL THREE SO THE PADDING AROUND
  // EACH LABEL AND THE PILL'S ROUNDED EDGE READ IDENTICAL ACROSS ALL THREE BUTTONS.
  // PLAY - STARTS THE GAME DIRECTLY IN PLAYER VS BOT MODE. NO MODE-SELECT SUBMENU ANYMORE;
  // WHOEVER WIRES onPlayBot UP HANDLES THE ACTUAL SCENE SWITCH ON THEIR SIDE.
  createPillButton(play_btn_shape, play_btn, {center_x, 400.f}, {280.f, 80.f},
                    "PLAY", ui_manager->font.font_regular_bold, theme.greenish_yellow, theme.black);
  play_btn.onClick = [this](){ if (onPlayBot) onPlayBot(); };
 
  createPillButton(info_btn_shape, info_btn, {center_x, 510.f}, {280.f, 80.f},
                    "INFO", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  info_btn.onClick = [this](){ showing_info = true; if (onInfo) onInfo(); };
 
  createPillButton(exit_btn_shape, exit_btn, {center_x, 620.f}, {280.f, 80.f},
                    "EXIT", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  exit_btn.onClick = [this](){ if (onExit) onExit(); };
 
  buildInfoOverlay();
}
 
void StartupScene::buildInfoOverlay(){
  float center_x = static_cast<float>(w_w) / 2.f;
  float center_y = static_cast<float>(w_h) / 2.f;
 
  // INFO PANEL - LAYERED BLACK / WOODEN_BROWN / WOODEN_DARK_BROWN, SAME 3-DEPTH LOOK AS BEFORE.
  // KEPT AS A SOLID PANEL (RATHER THAN A PILL BUTTON) SINCE IT NEEDS TO HOLD A BLOCK OF RULES TEXT.
  out_info_board = RoundedRect(720.f, 560.f);
  out_info_board.makeRoundRect(center_x, center_y, 28.f, &theme.black);
  info_panels.push_back(&out_info_board);
 
  mid_info_board = RoundedRect(712.f, 552.f);
  mid_info_board.makeRoundRect(center_x, center_y, 28.f, &theme.wooden_brown);
  info_panels.push_back(&mid_info_board);
 
  in_info_board = RoundedRect(704.f, 544.f);
  in_info_board.makeRoundRect(center_x, center_y, 28.f, &theme.wooden_dark_brown);
  info_panels.push_back(&in_info_board);
 
  // TITLE
  addInfoText(ui_manager->font.font_bold, "HOW TO PLAY", center_x, center_y - 240.f, theme.white, -110.f, -20.f);
 
  // RULES, ONE LINE PER FACT
  float line_y = center_y - 170.f;
  float line_step = 34.f;
  addInfoText(ui_manager->font.font_regular_bold, "20 GOATS FACE OFF AGAINST 4 TIGERS", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "GOATS WIN BY TRAPPING ALL 4 TIGERS", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "TIGERS WIN BY CAPTURING 5 GOATS", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "TAP AN OPEN POINT TO PLACE A GOAT", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "ONCE ALL GOATS ARE PLACED, TAP A GOAT", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "THEN TAP A HIGHLIGHTED POINT TO MOVE IT", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "TIGERS CAPTURE BY JUMPING OVER A GOAT", center_x, line_y, theme.light_silver, -300.f, 0.f);
  line_y += line_step;
  addInfoText(ui_manager->font.font_regular_bold, "INTO AN EMPTY POINT DIRECTLY BEHIND IT", center_x, line_y, theme.light_silver, -300.f, 0.f);
 
  // BACK BUTTON - SAME PILL STYLE AND FONT AS THE MAIN MENU BUTTONS
  createPillButton(back_btn_shape, back_btn, {center_x, center_y + 220.f}, {220.f, 60.f},
                    "BACK", ui_manager->font.font_regular_bold, theme.wooden_brown, theme.white);
  back_btn.onClick = [this](){ showing_info = false; };
}
 
void StartupScene::render(){
  // BACKDROP - DRAWN TWICE TO COUNTER THE TEXTURE'S BUILT-IN LOW ALPHA (SET GLOBALLY IN
  // Texture::loadTexture) SO IT READS BRIGHT AND SATURATED LIKE THE MOCKUP INSTEAD OF WASHED OUT
  SDL_RenderTexture(renderer, ui_manager->texture.background, NULL, &bg_rect);
  SDL_RenderTexture(renderer, ui_manager->texture.background, NULL, &bg_rect);
 
  // GLOWING LOGO
  SDL_RenderTexture(renderer, ui_manager->texture.baaghchaal_txt, NULL, &baaghchaal_txt);
 
  // SUBTITLE
  for (const auto& [rect, tex] : texts){
    SDL_RenderTexture(renderer, tex, NULL, &rect);
  }
 
  // BUTTONS - PLAY / INFO / EXIT, ALWAYS THE SAME THREE
  renderPillButton(play_btn_shape, play_btn);
  renderPillButton(info_btn_shape, info_btn);
  renderPillButton(exit_btn_shape, exit_btn);
 
  if (showing_info){
    // DIM EVERYTHING BEHIND THE INFO OVERLAY
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 170);
    SDL_RenderFillRect(renderer, &bg_rect);
 
    // INFO PANEL
    for (const auto& panel : info_panels){
      SDL_RenderGeometry(renderer, NULL,
        panel->rounded_rect.data(),
        static_cast<int>(panel->rounded_rect.size()),
        panel->indices.data(),
        panel->indices.size());
    }
 
    // RULES TEXT
    for (const auto& [rect, tex] : info_texts){
      SDL_RenderTexture(renderer, tex, NULL, &rect);
    }
 
    // BACK BUTTON
    renderPillButton(back_btn_shape, back_btn);
  }
}
 
void StartupScene::handleEvent(const SDL_Event& event){
  if (showing_info){
    // WHILE THE OVERLAY IS OPEN, ONLY THE BACK BUTTON SHOULD BE CLICKABLE
    back_btn.handleEvent(event);
    return;
  }
 
  // NORMAL MENU - PLAY / INFO / EXIT ARE ALL CLICKABLE
  play_btn.handleEvent(event);
  info_btn.handleEvent(event);
  exit_btn.handleEvent(event);
}
