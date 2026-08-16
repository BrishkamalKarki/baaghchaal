#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <string>
#include <utility>
#include <vector>
 
#include "scene_core.hpp"
#include "game_config/theme_config.hpp"
#include "ui/widgets/rounded_rect.hpp"
#include "ui/widgets/button.hpp"
 
class UIManager;
 
class StartupScene : public Scenes
{
private:
    int w_w, w_h;
 
public:
    UIManager* ui_manager = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Theme theme;
 
    // HOOK THESE UP FROM UIManager TO ACTUALLY START THE GAME, SHOW INFO, OR QUIT
    // THIS SCENE DOESN'T KNOW HOW TO DO ANY OF THAT ITSELF.
    // PLAY GOES STRAIGHT TO PLAYER VS BOT - NO MODE-SELECT SUBMENU ANYMORE.
    std::function<void()> onPlayBot;
    std::function<void()> onInfo;
    std::function<void()> onExit;
 
    // BACKDROP - FULL FOREST IMAGE, DRAWN TWICE IN render() TO COUNTER THE TEXTURE'S BUILT-IN LOW
    // ALPHA (SET GLOBALLY IN Texture::loadTexture) SO IT READS BRIGHT AND SATURATED LIKE THE MOCKUP
    SDL_FRect bg_rect{};
 
    // GLOWING LOGO - BIG AND CENTERED UP TOP, SAME TEXTURE THE OTHER SCENES USE SMALL IN THE CORNER
    SDL_FRect baaghchaal_txt{};
 
    // NO OUTER WOODEN BOARD ANYMORE - JUST LOGO, SUBTITLE, AND BUTTONS FLOATING ON THE FOREST,
    // SAME AS THE MOCKUP
 
    // MAIN MENU - ONLY THESE THREE SHOW AT ONCE
    RoundedRect play_btn_shape;
    RoundedRect info_btn_shape;
    RoundedRect exit_btn_shape;
    Button play_btn;
    Button info_btn;
    Button exit_btn;
 
    // SUBTITLE UNDER THE LOGO - SAME (RECT, TEXTURE) PATTERN AS ResultScene'S texts
    std::vector<std::pair<SDL_FRect, SDL_Texture*>> texts;
 
    // INFO OVERLAY - SHOWN ON TOP OF THE MENU WHEN "INFO" IS CLICKED, CLOSED WITH THE BACK BUTTON
    // (NO SCENE SWITCH NEEDED). STILL USES THE LAYERED "WOODEN BOARD" LOOK SINCE IT NEEDS A SOLID
    // PANEL FOR THE RULES TEXT TO STAY READABLE OVER THE FOREST.
    bool showing_info = false;
    RoundedRect out_info_board;
    RoundedRect mid_info_board;
    RoundedRect in_info_board;
    std::vector<RoundedRect*> info_panels;
    std::vector<std::pair<SDL_FRect, SDL_Texture*>> info_texts;
    RoundedRect back_btn_shape;
    Button back_btn;
 
    StartupScene(UIManager* uim);
    ~StartupScene();
 
    void createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                    SDL_Color color, float factor_x_text, float factor_y_text,
                    SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect);
    void addText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                 SDL_Color color, float factor_x, float factor_y);
    void addInfoText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                 SDL_Color color, float factor_x, float factor_y);
    void buildInfoOverlay();
 
    // BUILDS A PILL-SHAPED BUTTON: A RoundedRect FOR THE VISIBLE FILL PLUS A Button FOR HIT-TESTING
    // AND TEXT. THE Button'S OWN SQUARE FILL IS MADE FULLY TRANSPARENT SO ONLY THE ROUNDED SHAPE SHOWS.
    // ALL BUTTONS USE THE SAME font_regular_bold SO THEY READ AS ONE CONSISTENT FAMILY, LIKE THE MOCKUP.
    void createPillButton(RoundedRect& shape, Button& btn, SDL_FPoint center, SDL_FPoint size,
                           const std::string& text, TTF_Font* font, SDL_Color fill, SDL_Color text_color);
    void renderPillButton(RoundedRect& shape, Button& btn);
 
    void handleEvent(const SDL_Event& event);
 
    void buildUI() override;
    void render() override;
    void clearLayers();
};
