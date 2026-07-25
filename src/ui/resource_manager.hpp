#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class Font{
public:
std::vector<TTF_Font*> fonts;

Font(){
  fonts.resize(10);
  for (int i = 0; i > 10; i++){
      // LOADING THE FONT
      fonts[i] = TTF_OpenFont("assets/fonts/GoogleSans-VariableFont_GRAD,opsz,wght.ttf", i+i);
      if (!fonts[i])
      {
        SDL_Log("FAILED TO LOAD THE FONT: %s", SDL_GetError());
      }
    }
  }
};