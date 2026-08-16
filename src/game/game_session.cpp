#include "game_session.hpp"

GameSession::GameSession(SDL_Window* win, SDL_Renderer* rend, void* game_state, int w, int h)
    : window(win), renderer(rend), window_w(w), window_h(h), gameConf(1920, 1080, 1920.f/1080.f), game_state(game_state),
       engine(game_state, &b_config), ui_manager(&gameConf, win, rend, &engine, game_state), game_event(&ui_manager, renderer)
{
    if (SDL_GetWindowSize(window, &window_w, &window_h)){
        gameConf = Config(window_w, window_h, static_cast<float>(window_w)/window_h);
    }
    SDL_SetWindowAspectRatio(window, gameConf.max_aspect_ratio, gameConf.max_aspect_ratio);
    SDL_SetWindowMinimumSize(window, 1140, 640);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    ui_manager.initScene();
} 

SDL_AppResult GameSession::routeToEvents(SDL_Event* event)
{
    return game_event.handleEvent(event);
}

SDL_AppResult GameSession::runFrame()
{
    Uint64 start_time = SDL_GetTicks();
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    ui_manager.renderLayer();

    // THIS RENDERS THE UI ON THE BASIS OF SETUPED WINDOW SIZES
    // if (SDL_GetWindowSize(window, &window_w, &window_h))
    SDL_SetRenderLogicalPresentation(renderer, window_w, window_w/gameConf.max_aspect_ratio, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_RenderPresent(renderer);

    // DECLARAING THE TIME OUT WINNER
    std::string winner = ui_manager.engine->board_eval.checkWinner();
    if (winner == "goat" || winner == "baagh"){
        ui_manager.game_state->move = 0;
        ui_manager.game_state->turn = "goat";
        ui_manager.pair_scene.push_back(ScenceOrd::RESULT_SCREEN);
        ui_manager.initScene();
        ui_manager.game_state->won_by_time_out = true;
        ui_manager.state_changed = true;
    }

    Uint64 frame_end_time = SDL_GetTicks();
    if (frame_end_time - start_time < 1000/gameConf.FPS_limit){
        // SETTING UP THE FPS LIMIT FOR THE GAME - CURRENT FPS LIMIT = 60
        int elapsed_time = frame_end_time - start_time;
        SDL_Delay(1000/gameConf.FPS_limit - elapsed_time);
    }

    prev_w = window_w;
    prev_h = window_h;

    return SDL_APP_CONTINUE;
}