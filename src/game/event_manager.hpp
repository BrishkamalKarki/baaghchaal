#pragma once
#include <SDL3/SDL.h>

#include "ui/ui_manager.hpp"

class GameEvent{
public:
  SDL_Renderer* renderer = nullptr;
  SDL_Event* event = nullptr;
  UIManager* ui_manager = nullptr;

  GameEvent(UIManager* ui_manager, SDL_Renderer* renderer);
  SDL_AppResult handleEvent(SDL_Event* event);
};