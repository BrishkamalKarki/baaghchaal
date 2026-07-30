#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <vector>

class Font{
public:
  TTF_Font* font_bold;
  TTF_Font* font_regular;

  Font(){
    font_bold = TTF_OpenFont("assets/fonts/static/GoogleSans_17pt-Bold.ttf", 26);
    font_regular = TTF_OpenFont("assets/fonts/static/GoogleSans_17pt-Regular.ttf", 17);
  }
};