#pragma once

#include <utility>

class Config
{
private:
public:
    int windowW;
    int windowH;
    int FPS_limit;
    Config(int w, int h): windowW(w), windowH(h)
    {
        // SETTING THE FPS LIMIT AS 60
        FPS_limit = 60;
    }
};
