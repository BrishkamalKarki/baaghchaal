#pragma once

#include <SDL3/SDL.h>
#include <vector>

class Circle
{

private:

    float x;
    float y;
    float radius;

    SDL_Color color;

    // CONTROLS WHETHER THE CIRCLE IS DRAWN.
    bool enabled;

    // STORES THE GEOMETRY REQUIRED TO DRAW THE CIRCLE.
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;

public:

    // CREATES A CIRCLE WITH DEFAULT VALUES.
    Circle();

   
    Circle(
        float x,
        float y,
        float radius,
        SDL_Color color
    );

    // ENABLES OR DISABLES THE CIRCLE.
    void setEnabled(bool state);

    // CHANGES THE CURRENT ENABLED STATE OF THE CIRCLE.
    void toggleEnabled();

    // RETURNS WHETHER THE CIRCLE IS ENABLED.
    bool isEnabled() const;

    // CHANGES THE POSITION OF THE CIRCLE.
    void setPosition(
        float x,
        float y
    );

    // CHANGES THE RADIUS OF THE CIRCLE.
    void setRadius(
        float radius
    );

    // CHANGES THE COLOR OF THE CIRCLE.
    void setColor(
        SDL_Color color
    );

    // RETURNS THE X COORDINATE OF THE CIRCLE.
    float getX() const;

  
    float getY() const;

  
    float getRadius() const;

    // RETURNS THE COLOR OF THE CIRCLE.
    SDL_Color getColor() const;

    // UPDATES THE GEOMETRY OF THE CIRCLE.
    void update();

    // DRAWS THE CIRCLE ON THE SCREEN.
    void render(
        SDL_Renderer* renderer
    );

};