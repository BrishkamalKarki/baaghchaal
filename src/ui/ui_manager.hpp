#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>
#include <memory>

#include "ui_layer.hpp"
#include "game_config/system_config.hpp"
#include "game_scene/scene_core.hpp"
#include "game_scene/board_scene.hpp"
#include "game_managers/texture_manager.hpp"
#include "game_managers/font_manager.hpp"
#include "engine/engine.hpp"
#include "game/game_state.hpp"

// class BoardScene;

enum class ScenceOrd
{
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
    Engine* engine = nullptr;
    GameState* game_state = nullptr;
    bool scene_state = false;
    bool state_changed = false;

    UIManager(Config* gameConf, SDL_Window* win, SDL_Renderer*, Engine* engine, void* game_state);
    ScenceOrd scnord;
    std::vector <ScenceOrd> pair_scene;
    std::unique_ptr<BoardScene> board_scene;

    // RESOURCES IN HERE
    Texture texture;
    Font font;
    BoardLayer board_layer;
    void initScene();
    void renderLayer();
};