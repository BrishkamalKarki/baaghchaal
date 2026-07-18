#include "Circle.hpp"

#include <cmath>



// CREATES A CIRCLE WITH DEFAULT VALUES.
Circle::Circle()
{

    x = 0;
    y = 0;

    radius = 10;

    color =
    {
        255,
        255,
        255,
        255
    };

    enabled = true;

    update();

}



// CREATES A CIRCLE WITH THE GIVEN POSITION, RADIUS, AND COLOR.
Circle::Circle(
    float x,
    float y,
    float radius,
    SDL_Color color
)
{

    this->x = x;
    this->y = y;

    this->radius = radius;

    this->color = color;

    enabled = true;

    update();

}



// ENABLE OR DISABLE THE CIRCLE.

void Circle::setEnabled(bool state)
{
    enabled = state;
}



void Circle::toggleEnabled()
{
    enabled = !enabled;
}



bool Circle::isEnabled() const
{
    return enabled;
}



// MODIFY THE CIRCLE PROPERTIES.

void Circle::setPosition(float x,float y)
{

    // DO NOT MODIFY THE CIRCLE IF IT IS DISABLED.
    if(!enabled)
        return;

    this->x = x;
    this->y = y;

    update();

}



void Circle::setRadius(float radius)
{

    // DO NOT MODIFY THE CIRCLE IF IT IS DISABLED.
    if(!enabled)
        return;

    this->radius = radius;

    // KEEP THE RADIUS GREATER THAN ZERO.
    if(this->radius < 1)
        this->radius = 1;

    update();

}



void Circle::setColor(SDL_Color color)
{

    // DO NOT MODIFY THE CIRCLE IF IT IS DISABLED.
    if(!enabled)
        return;

    this->color = color;

    update();

}



// RETURN THE CIRCLE PROPERTIES.

float Circle::getX() const
{
    return x;
}

float Circle::getY() const
{
    return y;
}

float Circle::getRadius() const
{
    return radius;
}

SDL_Color Circle::getColor() const
{
    return color;
}



// GENERATES THE GEOMETRY OF THE CIRCLE.

void Circle::update()
{

    vertices.clear();
    indices.clear();

    const float PI = 3.14159265358979323846f;

    // CALCULATE THE NUMBER OF POINTS USED TO DRAW THE CIRCLE.
    int points = static_cast<int>(radius * 2);

    // USE AT LEAST 30 POINTS TO KEEP THE CIRCLE SMOOTH.
    if(points < 30)
        points = 30;

    // CONVERT THE COLOR VALUES TO THE RANGE REQUIRED BY SDL.
    SDL_FColor fcolor;

    fcolor.r = color.r / 255.0f;
    fcolor.g = color.g / 255.0f;
    fcolor.b = color.b / 255.0f;
    fcolor.a = color.a / 255.0f;

    // CREATE THE CENTER VERTEX OF THE CIRCLE.
    SDL_Vertex center;

    center.position.x = x;
    center.position.y = y;

    center.color = fcolor;

    vertices.push_back(center);

    // CREATE THE OUTER VERTICES OF THE CIRCLE.
    for(int i = 0; i < points; i++)
    {

        float angle =
            (2.0f * PI * i) / points;

        SDL_Vertex vertex;

        vertex.position.x =
            x + radius * cos(angle);

        vertex.position.y =
            y + radius * sin(angle);

        vertex.color = fcolor;

        vertices.push_back(vertex);

    }

    // CREATE TRIANGLES TO FORM THE FILLED CIRCLE.
    for(int i = 1; i <= points; i++)
    {

        indices.push_back(0);

        indices.push_back(i);

        if(i == points)

            indices.push_back(1);

        else

            indices.push_back(i + 1);

    }

}



// DRAWS THE CIRCLE ON THE SCREEN.

void Circle::render(SDL_Renderer* renderer)
{

    SDL_RenderGeometry(

        renderer,

        nullptr,

        vertices.data(),

        static_cast<int>(vertices.size()),

        indices.data(),

        static_cast<int>(indices.size())

    );

}