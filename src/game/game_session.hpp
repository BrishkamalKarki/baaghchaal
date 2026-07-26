#pragma once
#include <SDL3/SDL.h>

#include "game_config/system_config.hpp"
#include "ui/ui_manager.hpp"
#include "event_manager.hpp"
#include "engine/engine.hpp"

class GameSession {
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event* event = nullptr;                                                                                                             
    void* game_state = nullptr;

    int window_w, prev_w;
    int window_h, prev_h;

    Config gameConf;
    UIManager ui_manager;
    GameEvent game_event;
    BoardConfig b_config;
    Engine engine;

    GameSession(SDL_Window* win, SDL_Renderer* rend, void* game_state, int w, int h);
    SDL_AppResult runFrame();
    SDL_AppResult routeToEvents(SDL_Event* event);
    void render();
};
