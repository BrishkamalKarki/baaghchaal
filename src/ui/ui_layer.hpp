#pragma once
#include <vector>
#include "SDL3/SDL.h"
#include "SDL3/SDL_rect.h"

#include "widgets/rounded_rect.hpp"
#include "widgets/button.hpp"
#include "widgets/circular_button.hpp"
#include "widgets/circle.hpp"

class BoardLayer{
public:
  std::vector <std::pair<SDL_FRect*, SDL_Color*>> rects;
  std::vector <std::pair<std::pair<SDL_FPoint*, SDL_FPoint*>, SDL_Color*>> points;
  std::vector <std::pair<SDL_Texture*, SDL_FRect*>> textures;
  std::vector <std::pair<SDL_Texture*, SDL_FRect*>> background_texture;
  std::vector <RoundedRect*> rounded_rects;
  std::vector <Button*> buttons;
  std::vector <std::pair<int, CircularButton*>> circular_buttons;
  std::vector <Circle*> circles;
  std::vector <RoundedRect*> lines_rects;
  std::vector <std::pair<int, std::pair<CircularButton*, SDL_Texture*>>> baagh_pieces;
  std::vector <std::pair<int, std::pair<CircularButton*, SDL_Texture*>>> goat_pieces;
  std::vector <std::pair<SDL_Texture*, SDL_FRect*>> texture_components;
  std::vector <RoundedRect*> info_boards;
  std::vector <std::pair<CircularButton*, SDL_Texture*>> board_tex_comp;
  std::vector <std::pair<SDL_FRect*, SDL_Texture*>> texts;
};

