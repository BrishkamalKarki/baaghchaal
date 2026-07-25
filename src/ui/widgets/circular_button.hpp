#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <string>
#include <utility>
#include <cmath>
#include <vector>

class CircularButton {
public:
    struct Shape {
        float offset_lower = 10.0f;
        SDL_Color upper_color{200, 200, 200, 255};
        SDL_Color lower_color{100, 100, 100, 255};
    };

    Shape shape;
    std::string text_str;
    TTF_Font* font = nullptr;
    SDL_Color text_color{0, 0, 0, 255};
    
    SDL_FPoint position{0.0f, 0.0f}; // CENTER OF THE BUTTON
    float radius = 50.0f;
    
    std::function<void()> onClick;

    CircularButton(){}
    CircularButton(SDL_FPoint center, float r, std::string text, TTF_Font* font, SDL_Color color = {200, 200, 200, 255}, std::function<void()> on_click = nullptr)
        : position(center), radius(r), text_str(std::move(text)), font(font), onClick(on_click) {
            shape.upper_color = color;
        }

    void makeCircleGeometry(float cx, float cy, float r, SDL_Color col, std::vector<SDL_Vertex>& vertices, std::vector<int>& indices) const {
        vertices.clear();
        indices.clear();

        // HIGHER NUMBER OF SEGMENTS FOR SMOOTH CIRCLES, ESPECIALLY IF RADIUS IS LARGE
        int num_segments = static_cast<int>(std::fmax(36.0f, r * 0.5f)); 
        float PI = 3.141592653f;
        
        SDL_Vertex center;
        center.position.x = cx;
        center.position.y = cy;
        center.color.a = col.a / 255.0f;
        center.color.b = col.b / 255.0f;
        center.color.r = col.r / 255.0f;
        center.color.g = col.g / 255.0f;
        center.tex_coord = {0.5f, 0.5f};
        vertices.push_back(center);
        

        for (int i = 0; i < num_segments; i++) {
            float theta = 2.0f * PI * static_cast<float>(i) / static_cast<float>(num_segments);
            SDL_Vertex v;
            v.position.x = cx + r * std::cos(theta);
            v.position.y = cy + r * std::sin(theta);
            v.tex_coord.x = 0.5f + 0.5f * std::sin(theta-PI/2.f);
            v.tex_coord.y = 0.5f + 0.5f * std::cos(theta-PI/2.f);
            v.color = center.color;
            vertices.push_back(v);
        }

        for (int i = 1; i <= num_segments; i++) {
            indices.push_back(0);
            indices.push_back(i);
            indices.push_back((i % num_segments) + 1);
        }
    }

    void draw(SDL_Renderer* renderer, SDL_Texture* tex = nullptr) const {
        std::vector<SDL_Vertex> vertices;
        std::vector<int> indices;

        
        // DRAW BUTTON FACE LAYER (CIRCLE)
        makeCircleGeometry(position.x, position.y, radius, shape.upper_color, vertices, indices);
        SDL_RenderGeometry(renderer, tex, vertices.data(), vertices.size(), indices.data(), indices.size());

        // DRAW CENTERED TEXT
        if (font && !text_str.empty()) {
            SDL_Surface* text_surface = TTF_RenderText_Blended(font, text_str.c_str(), text_str.length(), text_color);
            if (text_surface) {
                SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                if (text_texture) {
                    float text_w = static_cast<float>(text_surface->w);
                    float text_h = static_cast<float>(text_surface->h);

                    SDL_FRect text_target;
                    text_target.x = position.x - text_w / 2.0f;
                    text_target.y = position.y - text_h / 2.0f;
                    text_target.w = text_w;
                    text_target.h = text_h;

                    SDL_RenderTexture(renderer, text_texture, nullptr, &text_target);
                    SDL_DestroyTexture(text_texture);
                }
                SDL_DestroySurface(text_surface);
            }
        }
    }

    void setFillColor(SDL_Color upper, SDL_Color lower) {
        shape.upper_color = upper;
        shape.lower_color = lower;
    }

    void changePosition(SDL_FPoint pos) { position = pos; }
    void changeRadius(float r) { radius = r; }

    void handleEvent(const SDL_Event& event) const
    {
        if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {   
            float mouseX = event.button.x;
            float mouseY = event.button.y;
            
            // HIT DETECTION: CHECK IF DISTANCE FROM MOUSE TO CENTER IS <= RAIDUS
            float dx = mouseX - position.x;
            float dy = mouseY - position.y;
            float distance_sq = dx * dx + dy * dy;
            
            if(distance_sq <= radius * radius)
            {
                if(onClick)
                {
                    onClick();
                }
            }
        }
    }
};
