#pragma once
#include "raylib.h"
#include "BSAI25019_MINI_PROJECT_1_Bird.h"
#include "BSAI25019_MINI_PROJECT_1_Pipe.h"

class Game 
{
    int state,Sc,Hi_Sc;
    Texture2D bg,pp,pp_f;
    Bird plr;
    Pipe obstacles[5];
    Sound jumpSnd, scoreSnd;
    Music deathMusic;
    float bg1X, bg2X;
    Font gft;

public:
    Game();//Constructor
    void update(), draw(), reset(), unload();
};