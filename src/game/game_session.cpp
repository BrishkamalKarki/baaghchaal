#include "game_session.hpp"

GameSession::GameSession(SDL_Window* win, SDL_Renderer* rend, int w, int h)
    : window(win), renderer(rend), window_w(w), window_h(h), gameConf(1920, 1080, 1920.f/1080.f), ui_manager(&gameConf, win, rend)
{
    ui_manager.initScene();
}

SDL_AppResult GameSession::handleEvent(SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
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