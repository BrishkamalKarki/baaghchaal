#pragma once
#include <SDL3/SDL.h>

#include "scene_core.hpp"
#include "ui/ui_layer.hpp"
#include "game/config.hpp"

class UIManager;

class BoardScene : public Scenes
{   
private:
    int w_w, w_h;
public:
    UIManager* ui_manager = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_FRect rect1;
    SDL_FRect rect2;
    BoardScene(UIManager* uim);
    void buildUI() override;
    void render() override;
};  

