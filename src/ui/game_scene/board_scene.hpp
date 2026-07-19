#pragma once
#include <SDL3/SDL.h>

#include "scene_core.hpp"
#include "ui/ui_layer.hpp"
#include "game/config.hpp"
#include "ui_config.hpp"
#include "ui/widgets/rounded_rect.hpp"

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

    SDL_FRect rect1;
    SDL_FRect rect2;
    SDL_FRect goat_rect;
    SDL_FPoint p11;
    SDL_FPoint p55;
    RoundedRect rrect;
    RoundedRect rrect1;
    Button playButton;
    CircularButton circButton;
    BoardScene(UIManager* uim);
    void setFont(TTF_Font* f) { font = f; }
    void buildUI() override;
    void render() override;
};  

