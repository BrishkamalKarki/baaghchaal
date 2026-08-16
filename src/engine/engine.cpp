#include "engine.hpp"
#include <cmath>
#include <algorithm>
#include <random>
#include <SDL3/SDL.h>

Engine::Engine(void* game_st, BoardConfig* b_conf)
    : b_conf(b_conf), bot(this), board_eval(this)
{
    game_state = static_cast<GameState*>(game_st);
    b_conf->makePoints();
    turn_start_ticks = SDL_GetTicks();
}


// ─── SYNCHRONOUS BOT MOVE ──────────────────────────────────────────

void Engine::performBotMove()
{
    bot.findBestMove();

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();

    SDL_Log(" ");
    SDL_Log("============================================================");
    SDL_Log("                 BOT MOVE DIAGNOSTICS");
    SDL_Log("============================================================");

    SDL_Log(
        "BOT PIECE = %s | from = %d | to = %d",
        game_state->bot_taken.c_str(),
        bot.from,
        bot.to
    );


    // ============================================================
    // BOARD BEFORE BOT MOVE
    // ============================================================

    SDL_Log("BOARD BEFORE BOT MOVE:");

    for (int row = 0; row < 5; row++)
    {
        SDL_Log(
            "  %c %c %c %c %c",
            game_state->board_state[row * 5 + 0].second,
            game_state->board_state[row * 5 + 1].second,
            game_state->board_state[row * 5 + 2].second,
            game_state->board_state[row * 5 + 3].second,
            game_state->board_state[row * 5 + 4].second
        );
    }


    // ============================================================
    // GOAT PLACEMENT
    // ============================================================

    if (bot.from == -1)
    {
        if (bot.to >= 0 && bot.to < 25)
        {
            int destination = bot.to;

            int threatening_tigers = 0;
            std::vector<int> threatening_tiger_positions;

            // ----------------------------------------------------
            // Check whether the goat being placed can immediately
            // be captured by any tiger.
            // ----------------------------------------------------

            for (int tiger_pos = 0;
                 tiger_pos < 25;
                 tiger_pos++)
            {
                if (game_state->board_state[tiger_pos].second != 'T')
                {
                    continue;
                }

                board_eval.valid_moves.clear();
                board_eval.edible_valid_moves.clear();

                game_state->turn = "baagh";

                board_eval.getValidMovesAt(tiger_pos);

                for (const auto& [goat_pos, landing_pos]
                     : board_eval.edible_valid_moves)
                {
                    (void)landing_pos;

                    if (goat_pos == destination)
                    {
                        threatening_tigers++;

                        threatening_tiger_positions.push_back(
                            tiger_pos
                        );

                        break;
                    }
                }
            }

            board_eval.valid_moves.clear();
            board_eval.edible_valid_moves.clear();


            // ----------------------------------------------------
            // Print goat danger
            // ----------------------------------------------------

            if (threatening_tigers == 0)
            {
                SDL_Log(
                    "BOT GOAT MOVE: PLACE goat at %d | "
                    "DANGER = 0 | SAFE",
                    destination
                );
            }
            else
            {
                SDL_Log(
                    "BOT GOAT MOVE: PLACE goat at %d | "
                    "DANGER = %d | IMMEDIATELY CAPTURABLE",
                    destination,
                    threatening_tigers
                );

                for (int tiger_pos :
                     threatening_tiger_positions)
                {
                    SDL_Log(
                        "    TIGER at %d can capture this goat",
                        tiger_pos
                    );
                }
            }


            // ----------------------------------------------------
            // Actual goat placement
            // ----------------------------------------------------

            SDL_Log(
                "BOT PLACES GOAT AT POSITION %d",
                destination
            );

            game_state->board_state[destination].second = 'G';
            game_state->goats_in_hand--;
        }
        else
        {
            SDL_Log(
                "ERROR: bot.to is invalid (%d) for goat placement",
                bot.to
            );
        }
    }


    // ============================================================
    // TIGER MOVE
    // ============================================================

    else
    {
        bool was_capture = false;
        int captured_goat = -1;


        // --------------------------------------------------------
        // Analyze tiger move BEFORE modifying the real board.
        // --------------------------------------------------------

        if (game_state->bot_taken == "baagh")
        {
            game_state->turn = "baagh";

            board_eval.valid_moves.clear();
            board_eval.edible_valid_moves.clear();

            board_eval.getValidMovesAt(bot.from);


            // ----------------------------------------------------
            // Print all available captures from this tiger.
            // ----------------------------------------------------

            if (!board_eval.edible_valid_moves.empty())
            {
                SDL_Log(
                    "TIGER %d HAS %zu AVAILABLE CAPTURE(S):",
                    bot.from,
                    board_eval.edible_valid_moves.size()
                );

                for (const auto& [goat_pos, landing_pos]
                     : board_eval.edible_valid_moves)
                {
                    SDL_Log(
                        "    goat=%d -> landing=%d",
                        goat_pos,
                        landing_pos
                    );
                }
            }
            else
            {
                SDL_Log(
                    "TIGER %d HAS NO AVAILABLE CAPTURES",
                    bot.from
                );
            }


            // ----------------------------------------------------
            // Determine whether selected move is a capture.
            // ----------------------------------------------------

            for (const auto& [goat_pos, landing_pos]
                 : board_eval.edible_valid_moves)
            {
                if (landing_pos == bot.to)
                {
                    was_capture = true;
                    captured_goat = goat_pos;
                    break;
                }
            }


            SDL_Log(
                "BOT TIGER MOVE ANALYSIS: "
                "from=%d -> to=%d | capture=%s",
                bot.from,
                bot.to,
                was_capture ? "YES" : "NO"
            );

            if (was_capture)
            {
                SDL_Log(
                    "    TIGER WILL EAT GOAT AT %d",
                    captured_goat
                );
            }
            else if (!board_eval.edible_valid_moves.empty())
            {
                SDL_Log(
                    "    WARNING: TIGER HAS A CAPTURE AVAILABLE "
                    "BUT SELECTED A NON-CAPTURE MOVE"
                );
            }
        }


        board_eval.valid_moves.clear();
        board_eval.edible_valid_moves.clear();


        // ========================================================
        // ACTUAL TIGER CAPTURE
        // ========================================================

        if (game_state->bot_taken == "baagh")
        {
            game_state->turn = "baagh";

            board_eval.getValidMovesAt(bot.from);

            for (const auto& [goat_pos, landing_pos]
                 : board_eval.edible_valid_moves)
            {
                if (landing_pos == bot.to)
                {
                    SDL_Log(
                        "BOT CAPTURES GOAT AT %d",
                        goat_pos
                    );

                    game_state->board_state[goat_pos].second = ' ';
                    game_state->goats_killed++;

                    break;
                }
            }
        }


        // ========================================================
        // ACTUAL MOVE
        // ========================================================

        SDL_Log(
            "BOT MOVE: %s from %d -> %d",
            game_state->bot_taken.c_str(),
            bot.from,
            bot.to
        );

        game_state->board_state[bot.from].second = ' ';
        game_state->board_state[bot.to].second = bot.bot_piece;


        // ========================================================
        // ANALYZE TIGER'S NEW POSITION
        // ========================================================

        if (game_state->bot_taken == "baagh")
        {
            board_eval.valid_moves.clear();
            board_eval.edible_valid_moves.clear();

            game_state->turn = "baagh";

            board_eval.getValidMovesAt(bot.to);

            int mobility =
                static_cast<int>(
                    board_eval.valid_moves.size()
                );

            int captures =
                static_cast<int>(
                    board_eval.edible_valid_moves.size()
                );


            if (mobility == 0)
            {
                SDL_Log(
                    "TIGER DESTINATION %d | "
                    "MOBILITY = 0 | DANGER = TRAPPED",
                    bot.to
                );
            }
            else
            {
                SDL_Log(
                    "TIGER DESTINATION %d | "
                    "MOBILITY = %d | FUTURE CAPTURES = %d",
                    bot.to,
                    mobility,
                    captures
                );
            }


            if (captures > 0)
            {
                for (const auto& [goat_pos, landing_pos]
                     : board_eval.edible_valid_moves)
                {
                    SDL_Log(
                        "    FROM TIGER POSITION %d: "
                        "CAN EAT GOAT %d -> LANDING %d",
                        bot.to,
                        goat_pos,
                        landing_pos
                    );
                }
            }
        }
    }


    // ============================================================
    // UPDATE GAME STATE
    // ============================================================

    game_state->move++;

    saveBoardState();

    board_eval.valid_moves.clear();
    board_eval.edible_valid_moves.clear();

    board_eval.checkBaaghTrapped(true);


    // ============================================================
    // BOARD AFTER BOT MOVE
    // ============================================================

    SDL_Log("BOARD AFTER BOT MOVE:");

    for (int row = 0; row < 5; row++)
    {
        SDL_Log(
            "  %c %c %c %c %c",
            game_state->board_state[row * 5 + 0].second,
            game_state->board_state[row * 5 + 1].second,
            game_state->board_state[row * 5 + 2].second,
            game_state->board_state[row * 5 + 3].second,
            game_state->board_state[row * 5 + 4].second
        );
    }


    SDL_Log(
        "GOATS KILLED = %d | "
        "GOATS IN HAND = %d | "
        "BAAGHS TRAPPED = %d",
        game_state->goats_killed,
        game_state->goats_in_hand,
        game_state->baagh_trapped
    );


    // ============================================================
    // NEXT TURN
    // ============================================================

    game_state->turn = game_state->human_taken;

    turn_start_ticks = SDL_GetTicks();

    last_processed_pos = -1;

    SDL_Log(
        "BOT MOVE APPLIED. TURN NOW: %s",
        game_state->turn.c_str()
    );

    SDL_Log("============================================================");
    SDL_Log(" ");
}



// ENTRY POINT TO THE ENGINE
void Engine::routeToEngine(int pos, char type){
    if (pos < 0 || pos > 24){
        return;
    }

    if (pos == last_processed_pos){
        return;
    }
    last_processed_pos = pos;

    SDL_Log("routeToEngine: pos=%d, turn=%s, bot_taken=%s, game_mode=%s",
            pos, game_state->turn.c_str(), game_state->bot_taken.c_str(),
            game_state->game_mode.c_str());

    bool is_bot_mode = (game_state->game_mode == "B V P");

    if (is_bot_mode){
        if (game_state->turn == game_state->bot_taken){
            // Bot's turn — the auto-trigger in renderLayer() handles this.
            // Ignore clicks during bot's turn.
            return;
        } else {
            // Human's turn
            SDL_Log("routeToEngine: Human's turn, calling selectPos(%d)", pos);
            selectPos(pos);

            // After human move, if it's now bot's turn, reset the timer
            // but do NOT call the bot directly — renderLayer() will pick it up.
            if (game_state->turn == game_state->bot_taken){
                turn_start_ticks = SDL_GetTicks();
                SDL_Log("routeToEngine: Turn passed to bot.");
            }
        }
    } else {
        // Two-player mode
        selectPos(pos);
    }
}

void Engine::selectPos(int pos){
    if (pos < 0 || pos > 24) return;

    board_eval.checkBaaghTrapped(true);

    for (int id = 0; id < 25; id++){
        char tp = game_state->board_state[id].second;
        if (game_state->turn == "baagh" && game_state->bot_taken != "baagh"){
            if (id == pos && tp == 'T'){
                from_to.first = pos;
                board_eval.valid_moves.clear();
                board_eval.valid_moves.reserve(24);
                board_eval.getValidMovesAt(pos);
                SDL_Log("TIGER IS SELECTED AT %d", pos);
                return;
            }
        }
        else if (game_state->turn == "goat" && game_state->bot_taken != "goat"){
            if (id == pos){
                turn_start_ticks = SDL_GetTicks();
                if (tp == ' ' && game_state->goats_in_hand > 0){ // PLACING THE NEW GOAT
                    game_state->move++;
                    game_state->board_state[pos].second = 'G';
                    game_state->goats_in_hand--;
                    game_state->turn = "baagh";
                    saveBoardState();
                    SDL_Log("GOAT IS PALCED AT %d", pos);
                    return;
                }
                else if (tp == 'G' && game_state->goats_in_hand == 0){
                    // SELECTING THE BAAKHRA PRESENT IN THE BOARD TO MOVE
                    from_to.first = pos;
                    board_eval.valid_moves.clear();
                    board_eval.valid_moves.reserve(24);
                    board_eval.getValidMovesAt(pos);
                    SDL_Log("GOAT IS SELECTED %d", pos);
                    return;
                }
            }
        }
    }

    // SECOND CLICK TO MOVE THE BAAGH OR BAAKHRA
    if (std::find(board_eval.valid_moves.begin(), board_eval.valid_moves.end(), pos) != board_eval.valid_moves.end()){
        from_to.second = pos; // SAVING THE POSITION TO GO TO

        if (game_state->turn == "baagh"){
            for (auto& [goat, vacant] : board_eval.edible_valid_moves){
                if (pos == vacant){
                    SDL_Log("CAPTURED THE GOAT BY BAAGH AT %d", goat);
                    game_state->board_state[goat].second = ' ';
                    game_state->goats_killed++;
                }
            }
            changePosBaagh();
            game_state->turn = "goat";
            board_eval.edible_valid_moves.clear();
        }
        else if (game_state->turn == "goat"){
            changePosGoat();
            game_state->turn = "baagh";
        }
        saveBoardState();
        turn_start_ticks = SDL_GetTicks();
        SDL_Log("BAAKHRA / BAAGH MOVED TO %d", pos);
        return;
    }

    SDL_Log("NOT A VALID MOVE at pos %d", pos);
}

// MAKING TEH MOVES
void Engine::changePosBaagh(){
    game_state->move++;
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'T';
}

void Engine::changePosGoat(){
    game_state->move++;
    game_state->board_state[this->from_to.first].second = ' ';
    game_state->board_state[this->from_to.second].second = 'G';
}

// SAVING THE CURRENT BOARD IN THE BIT BOARD
void Engine::saveBoardState(){
    if (saved == 9){
        for (int i = 0; i < 9; i++){
            bit_board_goats[i] = bit_board_goats[i + 1];
            bit_board_tigers[i] = bit_board_tigers[i + 1];
        }
        bit_board_goats[9] = 0;
        bit_board_tigers[9] = 0;
    } else {
        saved++;
    }

    bit_board_goats[saved] = 0;
    bit_board_tigers[saved] = 0;

    for (int id = 0; id < 25; id++){
        char type = game_state->board_state[id].second;
        if (type == 'G'){
            bit_board_goats[saved] |= (1u << id);
        } else if (type == 'T'){
            bit_board_tigers[saved] |= (1u << id);
        }
    }
}

// 10 UNDOS AT MAX
void Engine::undoMove(){
    if (saved < 0){
        SDL_Log("NO MOVES TO UNDO");
        return;
    }

    bit_board_goats[saved] = 0;
    bit_board_tigers[saved] = 0;
    saved--;

    if (saved >= 0){
        for (int pos = 0; pos < 25; pos++){
            game_state->board_state[pos].second = ' ';
        }
        for (int pos = 0; pos < 25; pos++){
            uint32_t bit = (1u << pos);
            if (bit & bit_board_tigers[saved]){
                game_state->board_state[pos].second = 'T';
            } else if (bit & bit_board_goats[saved]){
                game_state->board_state[pos].second = 'G';
            }
        }
    }
}