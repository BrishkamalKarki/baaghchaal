#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <functional>
#include <string>
#include <utility>

class Button {
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
    
    float padding = 5.0f;
    SDL_FPoint position{0.0f, 0.0f};
    SDL_FPoint size{0.0f, 0.0f};
    
    std::function<void()> onClick;

    Button(){}
    Button(SDL_FPoint pos, SDL_FPoint size, std::string text, TTF_Font* font, SDL_Color color = {200, 200, 200, 255}, std::function<void()> on_click = nullptr)
        : position(pos), text_str(std::move(text)), font(font), onClick(on_click), size(size) {
            shape.upper_color = color;
        }

    void draw(SDL_Renderer* renderer) {
        // DRAW BUTTON FACE LAYER
        SDL_FRect upper_rect{position.x, position.y, size.x, size.y};
        SDL_SetRenderDrawColor(renderer, shape.upper_color.r, shape.upper_color.g, shape.upper_color.b, shape.upper_color.a);
        SDL_RenderFillRect(renderer, &upper_rect);

        // DRAW CENTERED TEXT
        if (font && !text_str.empty()) {
            SDL_Surface* text_surface = TTF_RenderText_Blended(font, text_str.c_str(), text_str.length(), text_color);
            if (text_surface) {
                SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                if (text_texture) {
                    float text_w = static_cast<float>(text_surface->w);
                    float text_h = static_cast<float>(text_surface->h);

                    SDL_FRect text_target;
                    text_target.x = position.x + (size.x - text_w) / 2.0f;
                    text_target.y = position.y + (size.y - text_h) / 2.0f;
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
    void changeSize(SDL_FPoint new_size) { size = new_size; }

    void fitText() {
        if (!font || text_str.empty()) return;

        int text_w = 0;
        int text_h = 0;
        TTF_GetStringSize(font, text_str.c_str(), text_str.length(), &text_w, &text_h);

        float requiredX = static_cast<float>(text_w) + 2.0f * padding;
        float requiredY = static_cast<float>(text_h) + 2.0f * padding;

        if (requiredX > size.x) size.x = requiredX;
        if (requiredY > size.y) size.y = requiredY;
    }

    SDL_FRect getGlobalBounds() const {
        return {position.x, position.y, size.x, size.y + shape.offset_lower};
    }

    void handleEvent(const SDL_Event& event)
    {
        if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            float mouseX = event.button.x;
            float mouseY = event.button.y;
            SDL_FRect bounds = getGlobalBounds();

            // SDL_Log("Button bounds: %.1f %.1f %.1f %.1f",
            //         bounds.x,
            //         bounds.y,
            //         bounds.w,
            //         bounds.h);

            if(onClick)
            {
                SDL_Log("Button has callback.");
            }

            if(mouseX >= bounds.x &&
               mouseX <= bounds.x + bounds.w &&
               mouseY >= bounds.y &&
               mouseY <= bounds.y + bounds.h)
            {
                if(onClick)
                {
                    onClick();
                }
            }
        }
    }
};