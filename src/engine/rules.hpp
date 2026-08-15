#pragma once

enum Rules
{
    KILLED_GOATS = 5,
    TIGERS_TRAPPED = 4
};

enum Scores
{
    BOT_WON   = 10000000,
    HUMAN_WON = -10000000,

    GOATS_KILLED = 100,
    
    TIGER_MOBILITY        = 8,
    TIGER_CAPTURE         = 70,
    TIGER_CENTER          = 4,
    TIGER_ESCAPE          = 8,
    TIGER_TRAPPED         = 350,
    TIGER_EDGE            = 2,

    GOAT_MOBILITY         = 3,
    GOAT_CLUSTER          = 2,
    GOAT_RESTRICT         = 18,
    GOAT_VULNERABLE       = 80,

    CENTER_CONTROL        = 6,
    GOAT_ADVANCED         = 2,
    GOAT_BLOCKING         = 12,


    IMMEDIATE_CAPTURE     = 180,
    DOUBLE_CAPTURE        = 100,
    TIGER_ESCAPE_BONUS    = 15,

    GOAT_SAFE_PLACEMENT   = 15,
    GOAT_DANGER_PLACEMENT = 60
};
