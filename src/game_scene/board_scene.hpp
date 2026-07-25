#pragma once
#include <SDL3/SDL.h>

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

    SDL_FRect rect1;
    SDL_FRect rect2;
    std::vector<SDL_FRect> rect;
    std::vector<CircularButton> baagh_circ; // HOLDS THE BAAGH TEXTURE
    Circle goat_circ; // HOLDS THE BAAKHRA TEXTURE
    SDL_FRect board_rect;
    SDL_FRect cover_rect;
    SDL_FRect bg_rect;
    SDL_FPoint p11;
    SDL_FPoint p55;
    CircularButton tada;

    std::vector<RoundedRect> line_rects;
    std::vector<CircularButton> board_pnt_btn;

    std::vector<SDL_FRect> rects;
    RoundedRect rrect;
    RoundedRect rrect1;
    Button playButton;
    Circle circ;
    BoardScene(UIManager* uim);
    void setFont(TTF_Font* f) { font = f; }
    void buildUI() override;
    void render() override;
}; 

