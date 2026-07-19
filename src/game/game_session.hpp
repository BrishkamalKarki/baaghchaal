#pragma once
#include <SDL3/SDL.h>

#include "config.hpp"
#include "ui/ui_manager.hpp"
#include <SDL3_ttf/SDL_ttf.h>

class GameSession {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    int window_w;
    int window_h;

    Config gameConf;
    UIManager ui_manager;

    GameSession(SDL_Window* win, SDL_Renderer* rend, TTF_Font* font, int w, int h);
    SDL_AppResult runFrame();
    SDL_AppResult handleEvent(SDL_Event* event);
    void render();
};
