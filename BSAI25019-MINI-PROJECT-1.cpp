#include "raylib.h"
#include "BSAI25019_MINI_PROJECT_1_Game.h"

int main() 
{
    InitWindow(1920, 1080, "Flappy_Bird");
    SetTargetFPS(60);
    InitAudioDevice();

    Game g;
    while (!WindowShouldClose())
    {
        g.update();
        g.draw();
    }

    g.unload();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}