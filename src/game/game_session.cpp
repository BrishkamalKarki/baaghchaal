#include "game_session.hpp"

GameSession::GameSession(SDL_Window* win, SDL_Renderer* rend, TTF_Font* font, int w, int h)
    : window(win), renderer(rend), window_w(w), window_h(h), gameConf(1920, 1080, 1920.f/1080.f), ui_manager(&gameConf, win, rend)
{
    ui_manager.setFont(font);
    ui_manager.initScene();
}

SDL_AppResult GameSession::handleEvent(SDL_Event* event)
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

    for(auto button : ui_manager.board_layer.buttons)
    {
    button->handleEvent(*event);
    }

    for(auto c_button : ui_manager.board_layer.circular_buttons)
    {
        c_button->handleEvent(*event);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult GameSession::runFrame()
{
    Uint64 start_time = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    ui_manager.renderLayer();
    SDL_RenderPresent(renderer);

    Uint64 frame_end_time = SDL_GetTicks();
    if (frame_end_time - start_time < 1000/gameConf.FPS_limit){
        // SETTING UP THE FPS LIMIT FOR THE GAME - CURRENT FPS LIMIT = 60
        int elapsed_time = frame_end_time - start_time;
        SDL_Delay(1000/gameConf.FPS_limit - elapsed_time);
    }
    return SDL_APP_CONTINUE;
}