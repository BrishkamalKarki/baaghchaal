#include "game_configer_scene.hpp"
#include "ui/ui_manager.hpp"

GameConfigerScene::GameConfigerScene(UIManager* uim) : ui_manager(uim) {}

GameConfigerScene::~GameConfigerScene() {
    if (hdr_game_mode.first) SDL_DestroyTexture(hdr_game_mode.first);
    if (hdr_play_as.first) SDL_DestroyTexture(hdr_play_as.first);
    if (hdr_bot_diff.first) SDL_DestroyTexture(hdr_bot_diff.first);
    if (hdr_timer_set.first) SDL_DestroyTexture(hdr_timer_set.first);
    if (hdr_timer_dur.first) SDL_DestroyTexture(hdr_timer_dur.first);
}

SDL_Color GameConfigerScene::getActiveColor() {
    return theme.wooden_dark_brown;
}

SDL_Color GameConfigerScene::getInactiveColor() {
    return theme.wooden_brown;
}

Button GameConfigerScene::createConfigButton(SDL_FPoint pos, SDL_FPoint size, const std::string& text, std::function<void()> onClick) {
    Button btn(pos, size, text, ui_manager->font.font_regular_bold, getInactiveColor(), onClick);
    btn.text_color = theme.white;
    return btn;
}

std::pair<SDL_Texture*, SDL_FRect> GameConfigerScene::createTextHeader(const std::string& text, float centerX, float topY) {
    if (!ui_manager->font.font_bold) return {nullptr, {}};
    SDL_Surface* surf = TTF_RenderText_Blended(ui_manager->font.font_bold, text.c_str(), text.length(), theme.white);
    if (surf) {
        SDL_Texture* tex = SDL_CreateTextureFromSurface(ui_manager->renderer, surf);
        SDL_FRect rect = {0,0,0,0};
        if (tex) {
            rect.w = static_cast<float>(surf->w);
            rect.h = static_cast<float>(surf->h);
            rect.x = centerX - rect.w / 2.0f;
            rect.y = topY;
        }
        SDL_DestroySurface(surf);
        return {tex, rect};
    }
    return {nullptr, {}};
}

void GameConfigerScene::updateButtonVisuals() {
    auto& gs = *ui_manager->game_state;

    // UPDATE ROUNDED RECTANGLE COLORS BEFORE RENDERING BASED ON CURRENT STATE
    // FOR SMALLER CONDITIONAL BUTTONS, WE STILL USE STANDARD SQUARE BUTTON COLORING
    btn_pvp.shape.upper_color = {0,0,0,0};
    btn_bot.shape.upper_color = {0,0,0,0};

    btn_side_baagh.shape.upper_color = (gs.human_taken == "baagh") ? getActiveColor() : getInactiveColor();
    btn_side_goat.shape.upper_color = (gs.human_taken == "goat") ? getActiveColor() : getInactiveColor();

    btn_diff_low.shape.upper_color = (gs.bot_diff_level == "EASY") ? getActiveColor() : getInactiveColor();
    btn_diff_med.shape.upper_color = (gs.bot_diff_level == "MEDIUM") ? getActiveColor() : getInactiveColor();
    btn_diff_high.shape.upper_color = (gs.bot_diff_level == "HARD") ? getActiveColor() : getInactiveColor();

    btn_timer_on.shape.upper_color = {0,0,0,0};
    btn_timer_off.shape.upper_color = {0,0,0,0};

    btn_time_10.shape.upper_color = (gs.sec_p_move == 15) ? getActiveColor() : getInactiveColor();
    btn_time_20.shape.upper_color = (gs.sec_p_move == 30) ? getActiveColor() : getInactiveColor();
    btn_time_30.shape.upper_color = (gs.sec_p_move == 45) ? getActiveColor() : getInactiveColor();
    
    btn_play.shape.upper_color = {0,0,0,0};
}

void GameConfigerScene::buildUI() {
    if (hdr_game_mode.first) SDL_DestroyTexture(hdr_game_mode.first);
    if (hdr_play_as.first) SDL_DestroyTexture(hdr_play_as.first);
    if (hdr_bot_diff.first) SDL_DestroyTexture(hdr_bot_diff.first);
    if (hdr_timer_set.first) SDL_DestroyTexture(hdr_timer_set.first);
    if (hdr_timer_dur.first) SDL_DestroyTexture(hdr_timer_dur.first);

    float centerX = static_cast<float>(ui_manager->gameConf->windowW) / 2.0f;
    float startY = 220.0f;
    
    float largeBtnW = 200.0f;
    float largeBtnH = 60.0f;
    float smallBtnW = 120.0f;
    float smallBtnH = 45.0f;

    // INITIALIZE GEOMETRIES FOR ROUNDED RECTANGLE BUTTONS
    rr_pvp = RoundedRect(largeBtnW, largeBtnH);
    rr_bot = RoundedRect(largeBtnW, largeBtnH);
    rr_timer_on = RoundedRect(largeBtnW, largeBtnH);
    rr_timer_off = RoundedRect(largeBtnW, largeBtnH);
    rr_play = RoundedRect(250.0f, 70.0f);

    // APPLY DEFAULT GAME CONFIGURATION SETTINGS IF THEY ARE NOT YET INITIALIZED
    if(ui_manager->game_state->game_mode.empty()) {
        ui_manager->game_state->game_mode = "B V P";
        ui_manager->game_state->human_taken = "goat";
        ui_manager->game_state->bot_taken = "baagh";
        ui_manager->game_state->bot_diff_level = "HARD";
        ui_manager->game_state->timer_mode = true;
        ui_manager->game_state->sec_p_move = 45;
    }

    // 1. GAME MODE SELECTION SECTION
    hdr_game_mode = createTextHeader("CHOOSE GAME MODE", centerX, startY - 45.0f);
    btn_pvp = createConfigButton({centerX - largeBtnW - 40.0f, startY}, {largeBtnW, largeBtnH}, "PVP MODE", [this]() {
        ui_manager->game_state->game_mode = "P V P";
        ui_manager->state_changed = true;
    });
    btn_bot = createConfigButton({centerX + 40.0f, startY}, {largeBtnW, largeBtnH}, "VS BOT", [this]() {
        ui_manager->game_state->game_mode = "B V P";
        ui_manager->state_changed = true;
        ui_manager->game_state->player1 = "goat";
        ui_manager->game_state->player2 = "baagh";
    });

    startY += 120.0f;

    // 2. PLAY AS SIDE AND BOT DIFFICULTY SELECTION (ACTIVE IN VS BOT MODE ONLY)
    hdr_play_as = createTextHeader("PLAY AS", centerX - 250.0f, startY - 35.0f);
    btn_side_baagh = createConfigButton({centerX - 250.0f - smallBtnW - 15.0f, startY}, {smallBtnW, smallBtnH}, "BAAGH", [this]() {
        ui_manager->game_state->human_taken = "baagh";
        ui_manager->game_state->bot_taken = "goat";
        ui_manager->state_changed = true;
    });
    btn_side_goat = createConfigButton({centerX - 250.0f + 15.0f, startY}, {smallBtnW, smallBtnH}, "GOAT", [this]() {
        ui_manager->game_state->human_taken = "goat";
        ui_manager->game_state->bot_taken = "baagh";
        ui_manager->state_changed = true;
    });

    hdr_bot_diff = createTextHeader("BOT DIFFICULTY", centerX + 250.0f, startY - 35.0f);
    btn_diff_low = createConfigButton({centerX + 250.0f - smallBtnW*1.5f - 20.0f, startY}, {smallBtnW, smallBtnH}, "EASY", [this]() {
        ui_manager->game_state->bot_diff_level = "EASY";
        ui_manager->state_changed = true;
    });
    btn_diff_med = createConfigButton({centerX + 250.0f - smallBtnW/2.0f, startY}, {smallBtnW, smallBtnH}, "MEDIUM", [this]() {
        ui_manager->game_state->bot_diff_level = "MEDIUM";
        ui_manager->state_changed = true;
    });
    btn_diff_high = createConfigButton({centerX + 250.0f + smallBtnW/2.0f + 20.0f, startY}, {smallBtnW, smallBtnH}, "HARD", [this]() {
        ui_manager->game_state->bot_diff_level = "HARD";
        ui_manager->state_changed = true;
    });

    startY += 110.0f;

    // 3. TIMER TOGGLE SECTION
    hdr_timer_set = createTextHeader("TIMER SETTINGS", centerX, startY - 45.0f);
    btn_timer_on = createConfigButton({centerX - largeBtnW - 40.0f, startY}, {largeBtnW, largeBtnH}, "TIMER ON", [this]() {
        ui_manager->game_state->timer_mode = true;
        ui_manager->state_changed = true;
    });
    btn_timer_off = createConfigButton({centerX + 40.0f, startY}, {largeBtnW, largeBtnH}, "TIMER OFF", [this]() {
        ui_manager->game_state->timer_mode = false;
        ui_manager->state_changed = true;
    });

    startY += 120.0f;

    // 4. TIMER DURATION SELECTION SECTION
    hdr_timer_dur = createTextHeader("TIMER DURATION", centerX, startY - 35.0f);
    btn_time_10 = createConfigButton({centerX - smallBtnW*1.5f - 20.0f, startY}, {smallBtnW, smallBtnH}, "15S", [this]() {
        ui_manager->game_state->sec_p_move = 15;
        ui_manager->state_changed = true;
    });
    btn_time_20 = createConfigButton({centerX - smallBtnW/2.0f, startY}, {smallBtnW, smallBtnH}, "30S", [this]() {
        ui_manager->game_state->sec_p_move = 30;
        ui_manager->state_changed = true;
    });
    btn_time_30 = createConfigButton({centerX + smallBtnW/2.0f + 20.0f, startY}, {smallBtnW, smallBtnH}, "45S", [this]() {
        ui_manager->game_state->sec_p_move = 45;
        ui_manager->state_changed = true;
    });

    startY += 120.0f;

    // 5. PLAY BUTTON TO LAUNCH THE GAME BOARD SCENE
    btn_play = createConfigButton({centerX - 125.0f, startY}, {250.f, 70.f}, "PLAY", [this]() {
        ui_manager->pair_scene.push_back(ScenceOrd::BOARD_SCENE);
        ui_manager->initScene(); 
        ui_manager->state_changed = true;
    });
    btn_play.text_color = theme.black;

    updateButtonVisuals();
}

void GameConfigerScene::handleEvents(const SDL_Event& event) {
    btn_pvp.handleEvent(event);
    btn_bot.handleEvent(event);

    if (ui_manager->game_state->game_mode == "B V P") {
        btn_side_baagh.handleEvent(event);
        btn_side_goat.handleEvent(event);
        btn_diff_low.handleEvent(event);
        btn_diff_med.handleEvent(event);
        btn_diff_high.handleEvent(event);
    }

    btn_timer_on.handleEvent(event);
    btn_timer_off.handleEvent(event);

    if (ui_manager->game_state->timer_mode) {
        btn_time_10.handleEvent(event);
        btn_time_20.handleEvent(event);
        btn_time_30.handleEvent(event);
    }

    btn_play.handleEvent(event);
}

void GameConfigerScene::render() {
    if (ui_manager->state_changed) {
        updateButtonVisuals();
        ui_manager->state_changed = false;
    }

    auto& gs = *ui_manager->game_state;

    // RENDER THE FULL FOREST BACKGROUND IMAGE
    SDL_FRect bg_rect = {0.f, 0.f, static_cast<float>(ui_manager->gameConf->windowW), static_cast<float>(ui_manager->gameConf->windowH)};
    SDL_RenderTexture(ui_manager->renderer, ui_manager->texture.background, nullptr, &bg_rect);

    // RENDER THE BAAGHCHAAL LOGO IN THE CENTER TOP
    if (ui_manager->texture.baaghchaal_txt) {
        SDL_FRect logo_rect = {bg_rect.w / 2.0f - 150.0f, 30.0f, 300.0f, 110.0f};
        SDL_RenderTexture(ui_manager->renderer, ui_manager->texture.baaghchaal_txt, nullptr, &logo_rect);
    }

    // RENDER SECTION HEADERS AND LABELS
    if (hdr_game_mode.first) SDL_RenderTexture(ui_manager->renderer, hdr_game_mode.first, nullptr, &hdr_game_mode.second);
    if (hdr_timer_set.first) SDL_RenderTexture(ui_manager->renderer, hdr_timer_set.first, nullptr, &hdr_timer_set.second);
    
    if (gs.game_mode == "B V P") {
        if (hdr_play_as.first) SDL_RenderTexture(ui_manager->renderer, hdr_play_as.first, nullptr, &hdr_play_as.second);
        if (hdr_bot_diff.first) SDL_RenderTexture(ui_manager->renderer, hdr_bot_diff.first, nullptr, &hdr_bot_diff.second);
    }

    if (gs.timer_mode) {
        if (hdr_timer_dur.first) SDL_RenderTexture(ui_manager->renderer, hdr_timer_dur.first, nullptr, &hdr_timer_dur.second);
    }

    // CALCULATE ACTIVE/INACTIVE FILL COLORS FOR LARGE BUTTONS BASED ON GAME STATE
    SDL_Color c_pvp = (gs.game_mode == "P V P") ? getActiveColor() : getInactiveColor();
    SDL_Color c_bot = (gs.game_mode == "B V P") ? getActiveColor() : getInactiveColor();
    SDL_Color c_ton = (gs.timer_mode) ? getActiveColor() : getInactiveColor();
    SDL_Color c_toff = (!gs.timer_mode) ? getActiveColor() : getInactiveColor();
    SDL_Color c_play = theme.greenish_yellow;

    float rad = 15.0f;

    // MAKE AND DRAW GEOMETRIES FOR LARGE ROUNDED RECTANGLE BUTTONS AND DRAW TEXT ON TOP
    rr_pvp.makeRoundRect(btn_pvp.position.x + btn_pvp.size.x/2.0f, btn_pvp.position.y + btn_pvp.size.y/2.0f, rad, &c_pvp);
    SDL_RenderGeometry(ui_manager->renderer, nullptr, rr_pvp.rounded_rect.data(), rr_pvp.rounded_rect.size(), rr_pvp.indices.data(), rr_pvp.indices.size());
    btn_pvp.draw(ui_manager->renderer);

    rr_bot.makeRoundRect(btn_bot.position.x + btn_bot.size.x/2.0f, btn_bot.position.y + btn_bot.size.y/2.0f, rad, &c_bot);
    SDL_RenderGeometry(ui_manager->renderer, nullptr, rr_bot.rounded_rect.data(), rr_bot.rounded_rect.size(), rr_bot.indices.data(), rr_bot.indices.size());
    btn_bot.draw(ui_manager->renderer);

    rr_timer_on.makeRoundRect(btn_timer_on.position.x + btn_timer_on.size.x/2.0f, btn_timer_on.position.y + btn_timer_on.size.y/2.0f, rad, &c_ton);
    SDL_RenderGeometry(ui_manager->renderer, nullptr, rr_timer_on.rounded_rect.data(), rr_timer_on.rounded_rect.size(), rr_timer_on.indices.data(), rr_timer_on.indices.size());
    btn_timer_on.draw(ui_manager->renderer);

    rr_timer_off.makeRoundRect(btn_timer_off.position.x + btn_timer_off.size.x/2.0f, btn_timer_off.position.y + btn_timer_off.size.y/2.0f, rad, &c_toff);
    SDL_RenderGeometry(ui_manager->renderer, nullptr, rr_timer_off.rounded_rect.data(), rr_timer_off.rounded_rect.size(), rr_timer_off.indices.data(), rr_timer_off.indices.size());
    btn_timer_off.draw(ui_manager->renderer);

    rr_play.makeRoundRect(btn_play.position.x + btn_play.size.x/2.0f, btn_play.position.y + btn_play.size.y/2.0f, 20.0f, &c_play);
    SDL_RenderGeometry(ui_manager->renderer, nullptr, rr_play.rounded_rect.data(), rr_play.rounded_rect.size(), rr_play.indices.data(), rr_play.indices.size());
    btn_play.draw(ui_manager->renderer);

    // DRAW CONDITIONAL SMALL BUTTONS (SIDE CHOSEN, DIFFICULTY, AND DURATION SETTINGS)
    if (gs.game_mode == "B V P") {
        btn_side_baagh.draw(ui_manager->renderer);
        btn_side_goat.draw(ui_manager->renderer);
        btn_diff_low.draw(ui_manager->renderer);
        btn_diff_med.draw(ui_manager->renderer);
        btn_diff_high.draw(ui_manager->renderer);
    }

    if (gs.timer_mode) {
        btn_time_10.draw(ui_manager->renderer);
        btn_time_20.draw(ui_manager->renderer);
        btn_time_30.draw(ui_manager->renderer);
    }
}
