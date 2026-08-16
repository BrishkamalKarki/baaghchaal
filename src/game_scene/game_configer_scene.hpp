#pragma once

#include "scene_core.hpp"
#include "ui/widgets/button.hpp"
#include "ui/widgets/rounded_rect.hpp"
#include "game_config/theme_config.hpp"
#include <vector>

class UIManager;

class GameConfigerScene : public Scenes {
private:
    UIManager* ui_manager;
    Theme theme;

    // Buttons for Game Mode
    Button btn_pvp;
    Button btn_bot;
    RoundedRect rr_pvp;
    RoundedRect rr_bot;

    // Buttons for Bot Side (Player plays as)
    Button btn_side_baagh;
    Button btn_side_goat;

    // Buttons for Bot Difficulty
    Button btn_diff_low;
    Button btn_diff_med;
    Button btn_diff_high;

    // Buttons for Timer
    Button btn_timer_on;
    Button btn_timer_off;
    RoundedRect rr_timer_on;
    RoundedRect rr_timer_off;

    // Buttons for Timer Duration
    Button btn_time_10;
    Button btn_time_20;
    Button btn_time_30;

    // Play Button
    Button btn_play;
    RoundedRect rr_play;

    std::pair<SDL_Texture*, SDL_FRect> hdr_game_mode = {nullptr, {}};
    std::pair<SDL_Texture*, SDL_FRect> hdr_play_as = {nullptr, {}};
    std::pair<SDL_Texture*, SDL_FRect> hdr_bot_diff = {nullptr, {}};
    std::pair<SDL_Texture*, SDL_FRect> hdr_timer_set = {nullptr, {}};
    std::pair<SDL_Texture*, SDL_FRect> hdr_timer_dur = {nullptr, {}};

    void updateButtonVisuals();
    SDL_Color getActiveColor();
    SDL_Color getInactiveColor();
    Button createConfigButton(SDL_FPoint pos, SDL_FPoint size, const std::string& text, std::function<void()> onClick);
    std::pair<SDL_Texture*, SDL_FRect> createTextHeader(const std::string& text, float centerX, float topY);

public:
    GameConfigerScene(UIManager* uim);
    ~GameConfigerScene();

    void buildUI() override;
    void render() override;
    void handleEvents(const SDL_Event& event);
};
