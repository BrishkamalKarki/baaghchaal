#pragma once
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <vector>

class Sounds{
public:
  MIX_Audio* game_start;
  MIX_Audio* game_end;
  MIX_Audio* tiger_trapped;
  MIX_Audio* goat_killed;
  MIX_Audio* moved;
  MIX_Audio* button_clicked;

  MIX_Mixer* mixer;
  MIX_Mixer* ind_mixer; // FOR THE TIMER
  MIX_Track* track;

  Sounds(){
    MIX_Init();
    track = MIX_CreateTrack(mixer);
    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    ind_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

    game_start = MIX_LoadAudio(mixer, "assets/sounds/game_start.wav", true);
    game_end = MIX_LoadAudio(mixer, "assets/sounds/game_end.wav", true);
    tiger_trapped = MIX_LoadAudio(mixer, "assets/sounds/tiger_trapped.wav", true);
    goat_killed = MIX_LoadAudio(mixer, "assets/sounds/goat_killed.wav", true);
    moved = MIX_LoadAudio(mixer, "assets/sounds/baaghchaal_move_slide.wav", true);
    button_clicked = MIX_LoadAudio(mixer, "assets/sounds/button_clicked.wav", true);
  }
};