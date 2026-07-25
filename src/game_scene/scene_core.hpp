#pragma once
#include <SDL3/SDL.h>

#include "game_config/system_config.hpp"

class Scenes{
public:
    virtual void buildUI() = 0;
    virtual void render() = 0;
    virtual ~Scenes() = default;

private:
};