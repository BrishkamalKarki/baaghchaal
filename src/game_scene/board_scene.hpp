#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

#include "scene_core.hpp"
#include "ui/ui_layer.hpp"
#include "game_config/system_config.hpp"
#include "game_config/theme_config.hpp"
#include "ui/widgets/rounded_rect.hpp"
#include "ui/widgets/circle.hpp"
#include "game_config/board_config/board_config.hpp"

class UIManager;

class BoardScene : public Scenes 
{   
private:
    int w_w, w_h;
    TTF_Font* font = nullptr;
public:
    UIManager* ui_manager = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Theme theme;
    BoardConfig bconfig;

    SDL_FRect baaghchaal_txt;
    SDL_FRect rect2;
    std::vector<SDL_FRect> rect;
    std::vector<CircularButton> baagh_circ; // HOLDS THE BAAGH 
    std::vector<CircularButton> goat_circ; // HOLDS THE BAAKHRA 
    SDL_FRect board_rect;
    SDL_FRect cover_rect;
    SDL_FRect bg_rect;
    SDL_FPoint p11;
    SDL_FPoint p55;
    CircularButton baagh_board_circ;

    // ROUNDED RECTS
    RoundedRect in_tiger_info_board;
    RoundedRect mid_tiger_info_board;
    RoundedRect out_tiger_info_board;
    RoundedRect out_goat_info_board;
    RoundedRect mid_goat_info_board;
    RoundedRect in_goat_info_board;
    RoundedRect in_timer_info_board;
    RoundedRect mid_timer_info_board;
    RoundedRect out_timer_info_board;
    RoundedRect out_turn_info_board;
    RoundedRect in_turn_info_board;
    RoundedRect mid_turn_info_board;
    RoundedRect mid_config_info_board;
    RoundedRect in_config_info_board;
    RoundedRect out_config_info_board;

    RoundedRect baagh_board_line;
    RoundedRect goat_board_line;
    RoundedRect timer_board_line;
    RoundedRect config_board_line;
    RoundedRect turn_board_line;

    RoundedRect rounded_rects[19];
    
    // BAAGH BOARD
    SDL_Surface* baagh_title;
    SDL_Texture* baagh_title_tex;
    SDL_FRect baagh_title_rect;

    SDL_Surface* goat_title;
    SDL_Texture* goat_title_tex;
    SDL_FRect goat_title_rect;

    SDL_Surface* conf_title;
    SDL_Texture* conf_title_tex;
    SDL_FRect conf_title_rect;

    SDL_Surface* timer_title;
    SDL_Texture* timer_title_tex;
    SDL_FRect timer_title_rect;

    SDL_Surface* turn_title;
    SDL_Texture* turn_title_tex;
    SDL_FRect turn_title_rect;

    SDL_Surface* normal_texts;
    SDL_Texture* normal_text_tex;
    SDL_FRect normal_text_rect;

    SDL_Texture* live_timer_tex = nullptr;
    SDL_FRect    live_timer_rect{};
    void updateTimerText();

    CircularButton turn_board_circ; 

    int clicked_at;
    SDL_Color temp_col;

    std::vector<RoundedRect> line_rects;
    std::vector<std::pair<CircularButton, std::string>> board_pnt_btn;

    std::vector<SDL_FRect> rects;
    RoundedRect rrect;
    RoundedRect rrect1;
    Button playButton;
    
    Circle circ;
    BoardScene(UIManager* uim);
    void setFont(TTF_Font* f) { font = f; }
    void createBoardTexts(TTF_Font* font, const char* text, float centerX, float centerY,
                    SDL_Color color, float factor_x_text, float factor_y_text, SDL_Surface*& surface,
                    SDL_Texture*& texture, SDL_FRect& rect);
    void createRoundRects(float w, float h, float x, float y, float rad, SDL_Color *col, RoundedRect& r_rects, float diag_ang = 0.0f);
    void buildUI() override;
    void render() override;
    void clearLayers();

    // DIMS THE BACKGROUND AND SHOWS RESUME / MAIN MENU / EXIT OPTIONS.
    bool showing_pause = false;
    SDL_FRect pause_btn_rect{};       
    Button pause_hit_btn;           

    // UNDO BUTTON - NEXT TO THE PAUSE BUTTON (BOTTOM LEFT)
    SDL_FRect undo_btn_rect{};       
    Button undo_hit_btn;            

    // PAUSE MENU PANEL (LAYERED WOODEN BOARD LOOK)
    RoundedRect out_pause_board;
    RoundedRect mid_pause_board;
    RoundedRect in_pause_board;
    std::vector<RoundedRect*> pause_panels;

    // PAUSE MENU TITLE TEXT
    std::vector<std::pair<SDL_FRect, SDL_Texture*>> pause_texts;

    // PAUSE MENU PILL BUTTONS
    RoundedRect resume_btn_shape;
    Button resume_btn;
    RoundedRect mainmenu_btn_shape;
    Button mainmenu_btn;
    RoundedRect exitgame_btn_shape;
    Button exitgame_btn;

    int paused_time = 0; // PAUSED TIME
    int unpaused_time = 0;
    std::string saved_time_string;

    void buildPauseOverlay();
    void renderPauseOverlay();
    void handleEvent(const SDL_Event& event);

    ~BoardScene();
}; 

