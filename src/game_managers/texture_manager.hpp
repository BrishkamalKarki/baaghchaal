#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <vector>

class Font;

class Texture{
public:
  SDL_Texture* baagh = nullptr;
  SDL_Texture* trapped_baagh = nullptr;
  SDL_Texture* goat = nullptr;
  SDL_Texture* board = nullptr;
  SDL_Texture* cover = nullptr;
  SDL_Texture* background = nullptr;
  SDL_Texture* baaghchaal_txt = nullptr;
  const char* tex_location = nullptr;
  SDL_Renderer* renderer = nullptr;

  Texture(SDL_Renderer* renderer):renderer(renderer){}
  void loadTexture(){
    // BAAGH(TIGER) TEXTURE LOADING
    baagh = IMG_LoadTexture(renderer, "assets/sprites/the_tiger.jpg"); 
    SDL_SetTextureBlendMode(baagh, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(baagh, SDL_SCALEMODE_PIXELART); 

    // TRAPPED BAAGH(TIGER) TEXTURE LOADING
    trapped_baagh = IMG_LoadTexture(renderer, "assets/sprites/the_tiger.jpg"); 
    SDL_SetTextureBlendMode(baagh, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(baagh, SDL_SCALEMODE_PIXELART);
    SDL_SetTextureAlphaMod(trapped_baagh, 99);

    // GOAT TEXTURE LOADING
    goat = IMG_LoadTexture(renderer, "assets/sprites/the_goat.jpg"); 
    SDL_SetTextureBlendMode(goat, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(goat, SDL_SCALEMODE_PIXELART); 
    
    // BOARD TEXTURE LOADING
    board = IMG_LoadTexture(renderer, "assets/sprites/wooden_board.jpg");
    SDL_SetTextureScaleMode(board, SDL_SCALEMODE_PIXELART);
    SDL_SetTextureBlendMode(board, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(board, 255);

    // COVER TEXTURE LOADING
    cover = IMG_LoadTexture(renderer, "assets/sprites/cover_bright.png");
    int x = cover->w;
    int y = cover->h;
    SDL_Log("%d, %d", x, y);
    SDL_SetTextureScaleMode(cover, SDL_SCALEMODE_NEAREST);

    // BACKGROUND TEXTURE LOADING
    background = IMG_LoadTexture(renderer, "assets/sprites/background.png");
    SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background, 123);

    // BAAGHCHAAL TEXT
    baaghchaal_txt = IMG_LoadTexture(renderer, "assets/sprites/baaghchaal_txt.png");
    SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(baaghchaal_txt, 153);

  }
  ~Texture(){}
};