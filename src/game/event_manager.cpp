#include "event_manager.hpp"

SDL_AppResult GameEvent::handleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        float logicalX, logicalY;
        SDL_RenderCoordinatesFromWindow(renderer, event->button.x, event->button.y, &logicalX, &logicalY);
        event->button.x = logicalX;
        event->button.y = logicalY;
    } 

    ui_manager->handleEvents(*event);

    if (!ui_manager->pair_scene.empty() && ui_manager->pair_scene.back() == ScenceOrd::BOARD_SCENE) {
        for(auto button : ui_manager->board_layer.buttons)
        {
            button->handleEvent(*event);
        }

        for(auto [id, c_button] : ui_manager->board_layer.circular_buttons)
        {
            c_button->handleEvent(*event);
        }

        for(const auto& [id, baagh] : ui_manager->board_layer.baagh_pieces)
        {
            baagh.first->handleEvent(*event);
        }
        for(auto [id, goat] : ui_manager->board_layer.goat_pieces)
        {
            goat.first->handleEvent(*event);
        }
    }

    return SDL_APP_CONTINUE;
}

GameEvent::GameEvent(UIManager* ui_manager, SDL_Renderer* renderer) : ui_manager(ui_manager), renderer(renderer){}