#pragma once
#include <SDL3/SDL.h>

class Texture{
public:
  SDL_Texture* goat = nullptr;
  SDL_Surface* surface = NULL;
  const char* tex_location = NULL;
  SDL_Renderer* renderer = nullptr;

  Texture(SDL_Renderer* renderer):renderer(renderer){}
  void loadTexture(){
    surface = SDL_LoadPNG("assets/sprites/pieces/pixel-baagh.png");
    goat = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_SetTextureScaleMode(goat, SDL_SCALEMODE_PIXELART);
  }
  ~Texture(){}
};

