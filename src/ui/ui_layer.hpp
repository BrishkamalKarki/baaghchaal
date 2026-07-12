#pragma once
#include <vector>
#include "SDL3/SDL.h"
#include "SDL3/SDL_rect.h"

#include "widgets/rounded_rect.hpp"

class BoardLayer{
public:
  std::vector <std::pair<SDL_FRect*, SDL_Color*>> rects;
  std::vector <std::pair<std::pair<SDL_FPoint*, SDL_FPoint*>, SDL_Color*>> points;
  std::vector <std::pair<SDL_Texture*, SDL_FRect*>> textures;
  std::vector <RoundedRect*> rounded_rects;
};



