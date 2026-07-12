#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <memory>

#include "ui_layer.hpp"
#include "game/config.hpp"
#include "game_scene/scene_core.hpp"
#include "game_scene/board_scene.hpp"
#include "resource_manager.hpp"

// class BoardScene;

enum class ScenceOrd{
    INITIAL_SCENE,
    CONFIGURE_SCENE,
    BOARD_SCENE,
    RESULT_SCREEN
};

class UIManager
{
public:
    Config* gameConf = nullptr;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool scene_state = false;
    UIManager(Config* gameConf, SDL_Window* win, SDL_Renderer*);
    ScenceOrd scnord;
    std::vector <ScenceOrd> pair_scene;
    std::unique_ptr<BoardScene> board_scene;
    Texture texture;
    BoardLayer board_layer;
    void initScene();
    void renderLayer();
};