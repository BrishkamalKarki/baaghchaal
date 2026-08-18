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
  SDL_Texture* cover_dim = nullptr;
  SDL_Texture* pause_button = nullptr;
  SDL_Texture* undo_move = nullptr;
  SDL_Texture* background = nullptr;
  SDL_Texture* baaghchaal_txt = nullptr;
  const char* tex_location = nullptr;
  SDL_Renderer* renderer = nullptr;

  Texture(SDL_Renderer* renderer):renderer(renderer){}

  SDL_Texture* loadOrNull(const char* path){
    SDL_Texture* tex = IMG_LoadTexture(renderer, path);
    if (!tex){
      SDL_Log("TEXTURE LOAD FAILED: %s (%s)", path, SDL_GetError());
    }
    return tex;
  }

  void loadTexture(){
    // BAAGH(TIGER) TEXTURE LOADING
    baagh = loadOrNull("assets/sprites/the_tiger.jpg");
    SDL_SetTextureBlendMode(baagh, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(baagh, SDL_SCALEMODE_PIXELART);

    // TRAPPED BAAGH(TIGER) TEXTURE LOADING
    trapped_baagh = loadOrNull("assets/sprites/the_tiger.jpg");
    SDL_SetTextureBlendMode(trapped_baagh, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(trapped_baagh, SDL_SCALEMODE_PIXELART);
    SDL_SetTextureAlphaMod(trapped_baagh, 99);

    // GOAT TEXTURE LOADING
    goat = loadOrNull("assets/sprites/the_goat.jpg");
    SDL_SetTextureBlendMode(goat, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(goat, SDL_SCALEMODE_PIXELART);

    // BOARD TEXTURE LOADING
    board = loadOrNull("assets/sprites/wooden_board.jpg");
    SDL_SetTextureScaleMode(board, SDL_SCALEMODE_PIXELART);
    SDL_SetTextureBlendMode(board, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(board, 255);

    // COVER TEXTURE LOADING
    cover = loadOrNull("assets/sprites/cover_dim.png");
    SDL_SetTextureScaleMode(cover, SDL_SCALEMODE_NEAREST);

    // COVER DIM TEXTURE LOADING (STARTUP SCREEN BACKGROUND)
    cover_dim = loadOrNull("assets/sprites/cover_dim.png");
    SDL_SetTextureScaleMode(cover_dim, SDL_SCALEMODE_NEAREST);

    // PAUSE BUTTON TEXTURE LOADING
    pause_button = loadOrNull("assets/sprites/pause_button.png");
    SDL_SetTextureScaleMode(pause_button, SDL_SCALEMODE_NEAREST);

    // UNDO BUTTON TEXTURE LOADING
    undo_move = loadOrNull("assets/sprites/undo_move.png");
    SDL_SetTextureScaleMode(undo_move, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(undo_move, SDL_BLENDMODE_BLEND);

    // BACKGROUND TEXTURE LOADING
    background = loadOrNull("assets/sprites/background.png");
    SDL_SetTextureScaleMode(background, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(background, 123);

    // BAAGHCHAAL TEXT
    baaghchaal_txt = loadOrNull("assets/sprites/baaghchaal_txt.png");
    SDL_SetTextureScaleMode(baaghchaal_txt, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(baaghchaal_txt, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(baaghchaal_txt, 153);

  }
  ~Texture(){}
};