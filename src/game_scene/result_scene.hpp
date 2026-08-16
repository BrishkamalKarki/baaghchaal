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
 
class ResultScene : public Scenes
{
private:
    int w_w, w_h;
 
public:
    UIManager* ui_manager = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Theme theme;

    bool out_by_time = false;
 
    // HOOK THESE UP FROM UIManager / GameSession TO ACTUALLY RESTART THE GAME
    // OR SWITCH BACK TO THE START SCREEN - THIS SCENE DOESN'T KNOW HOW TO DO EITHER ITSELF
    std::function<void()> onPlayAgain;
    std::function<void()> onMainMenu;
 
    // BACKDROP
    SDL_FRect bg_rect{};
    SDL_FRect baaghchaal_txt{};
 
    // NO BOXED PANEL BEHIND THE RESULT SCREEN ANYMORE - TITLE, SCORE LINES, AND BUTTONS ALL
    // FLOAT DIRECTLY ON THE DIMMED FOREST BACKDROP, SAME "NO TABLE" LOOK AS THE START SCREEN.
 
    // DIVIDER LINES - ONE UNDER THE TITLE/SUBTITLE, ONE UNDER THE SCORE LINES ABOVE THE BUTTONS
    RoundedRect title_divider;
    RoundedRect stats_divider;
 
    std::vector<RoundedRect*> panels; // DIVIDER LINES ONLY, DRAWN IN PUSH ORDER
 
    // PILL BUTTONS - SAME STYLE AS THE START SCREEN'S PLAY / INFO / EXIT BUTTONS
    RoundedRect play_again_btn_shape;
    RoundedRect main_menu_btn_shape;
    Button play_again_btn;
    Button main_menu_btn;
 
    // TITLE / SUBTITLE / STAT LINES - SAME (RECT, TEXTURE) PATTERN AS BoardScene'S normal_texts
    std::vector<std::pair<SDL_FRect, SDL_Texture*>> texts;
 
    ResultScene(UIManager* uim);
    ~ResultScene();
 
    void createRoundRects(float w, float h, float x, float y, float rad, SDL_Color* col, RoundedRect& r_rects, float diag_ang = 0.0f);
    void createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                    SDL_Color color, float factor_x_text, float factor_y_text,
                    SDL_Surface*& surface, SDL_Texture*& texture, SDL_FRect& rect);
    void addText(TTF_Font* font, const std::string& text, float centerX, float centerY,
                 SDL_Color color, float factor_x, float factor_y);
 
    // SAME PILL-BUTTON HELPERS AS StartupScene - A RoundedRect FOR THE VISIBLE FILL PLUS
    // A Button FOR HIT-TESTING/TEXT, WITH THE Button'S OWN SQUARE FILL HIDDEN
    void createPillButton(RoundedRect& shape, Button& btn, SDL_FPoint center, SDL_FPoint size,
                           const std::string& text, TTF_Font* font, SDL_Color fill, SDL_Color text_color);
    void renderPillButton(RoundedRect& shape, Button& btn);
 
    void handleEvent(const SDL_Event& event); // NOT YET WIRED INTO GameEvent - SEE NOTES
 
    void buildUI() override;
    void render() override;
    void clearLayers();
};
