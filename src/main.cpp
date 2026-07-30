// USING THE CALL-BACK METHOD
#define SDL_MAIN_USE_CALLBACKS 
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "game/game_session.hpp"
#include "game/game_state.hpp"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
GameSession* game = nullptr;
GameState* game_state = nullptr;

// INITIALIZING THE GAME
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("VIDEO SYSTEM COULD NOT BE INITIALIZED: %s", SDL_GetError());
    return SDL_APP_FAILURE; 
  }

  window = SDL_CreateWindow("BaaghChaal", 1600, 900, SDL_WINDOW_RESIZABLE);
  if (!window) {
    SDL_Log("WINDOW CANNOT BE CREATED: %s", SDL_GetError());
    return SDL_APP_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
      SDL_Log("RENDERER CANNOT BE CREATED: %s", SDL_GetError());
      SDL_DestroyWindow(window);
      return SDL_APP_FAILURE;
  }

  // INITIALIZE TTF
  if (!TTF_Init()) {
    SDL_Log("TTF CANNOT BE INITIALIZED: %s", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return SDL_APP_FAILURE;
  }

  SDL_Log("STARTING THE GAME");
  game_state = new GameState();
  *appstate = static_cast<void*>(game_state);
  game = new GameSession(window, renderer, *appstate, 1600, 700);

  return SDL_APP_CONTINUE;
}

// HANDLING THE EVENTS
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
  return game->routeToEvents(event);
}

// GAME LOOP
SDL_AppResult SDL_AppIterate(void *appstate)
{
  return game->runFrame();
}

// QUITING THE GAME
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  delete game;
  delete game_state;
}