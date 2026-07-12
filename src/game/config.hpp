#pragma once

#include <utility>

class Config
{
private:
public:
    int windowW;
    int windowH;
    int FPS_limit;
    float max_aspect_ratio;
    float min_aspect_ratio;
    Config(){}
    Config(int w, int h, float ar): windowW(w), windowH(h), max_aspect_ratio(ar)
    {
        // SETTING THE FPS LIMIT AS 60
        FPS_limit = 60;
    }
};
