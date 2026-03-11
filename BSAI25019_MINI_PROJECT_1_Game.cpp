#include "BSAI25019_MINI_PROJECT_1_Game.h"
#include <fstream>
#define SW 1920
using namespace std;

Game::Game() {
    bg = LoadTexture("bg.png");
    pp = LoadTexture("pipe.png");    
    pp_f = LoadTexture("pipe-f.png"); 

    jumpSnd = LoadSound("jump.mp3");
    scoreSnd = LoadSound("score.mp3");
    deathMusic = LoadMusicStream("death.mp3");
    deathMusic.looping = false;
    gft = LoadFont("Swiss721Bold.ttf");

    ifstream rdr("highscore.txt");
    if (!rdr)
        exit(0);
    else
    rdr >> Hi_Sc;

    state = 0;
    reset();
}

void Game::reset() 
{
    Sc = 0;
    plr.reset();
    state = 0;
    bg1X = 0;
    bg2X = SW;
    //wapis start pe
    for (int i = 0; i < 5; i++)
    {
        obstacles[i].init(SW + (i * 350), pp, pp_f);
        obstacles[i].setSpeed(4.0f);
    }
}

void Game::update() 
{
    // Backg movement
    bg1X -= 1.5f;
    bg2X -= 1.5f;

    if (bg1X <= -1*SW)
    {
        bg1X = SW;
    }
    if (bg2X <= -1 * SW)
    {
        bg2X =  SW;
    }
    
    
    
    if (state == 0) 
    {
        if (IsKeyPressed(KEY_SPACE)) 
        {
            reset();
            state = 1;
        }

        Rectangle exitBtn = { 860, 600, 200, 60 }; //Pos exit box
        if (CheckCollisionPointRec(GetMousePosition(), exitBtn)) 
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                unload();
                exit(0);
            }
                
        }
    }
    else if (state == 1 || state == 2) 
    {
        if (IsKeyPressed(KEY_SPACE)) 
        {
            plr.flap();
            PlaySound(jumpSnd);
        }

        plr.update();

        if (Sc >= 10 && state == 1)
        {
        state = 2; 
          for (int i = 0; i < 5; i++)
          {
             obstacles[i].setSpeed(6.5f); //setter for speed lvl2
          }
}

//lvl3
         if (Sc >= 20) 
         {
            for (int i = 0; i < 5; i++)
            {
              obstacles[i].setSpeed(9.0f); //setter for lvl3
            }
         }

        for (int i = 0; i < 5; i++)
        {
            obstacles[i].update();

            Rectangle birdHitbox = { (float)plr.x - 45,(float)plr.y - 45,(float)plr.w - 16,(float)plr.h - 12 };

            if (CheckCollisionRecs(birdHitbox, obstacles[i].getTopRect()) || CheckCollisionRecs(birdHitbox, obstacles[i].getBottomRect())) 
            {
                if (state != 3) 
                {
                    state = 3;
                    PlayMusicStream(deathMusic);
                }
            }

            if (!obstacles[i].scored && (obstacles[i].x + obstacles[i].w < plr.x)) 
            {
                Sc++;

                if (Sc > Hi_Sc)
                    Hi_Sc = Sc;

                obstacles[i].scored = true;
                PlaySound(scoreSnd);
            }
        }

        if (plr.checkCollision()) 
        {
            if (state != 3) 
            {
                state = 3;
                PlayMusicStream(deathMusic);
            }
        }
    }

    else if (state == 3) 
    {
        if (IsMusicStreamPlaying(deathMusic)) 
        {
            UpdateMusicStream(deathMusic);
        }

        if (IsKeyPressed(KEY_R)) 
        {
            StopMusicStream(deathMusic);
            reset();
            state = 1;
        }
        Rectangle menuBtn = { 860, 600, 200, 60 };
        if (CheckCollisionPointRec(GetMousePosition(), menuBtn))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                StopMusicStream(deathMusic);
                reset();
                state = 0; 
            }
        }
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(bg, (int)bg1X, 0, WHITE);
    DrawTexture(bg, (int)bg2X, 0, WHITE);

    if (state == 0)
    {
        DrawTextEx(gft, "FLAPPY BIRD", {720, 400} ,60, 2, DARKBLUE);
        DrawTextEx(gft,"PRESS SPACE TO START", { 727, 500 }, 30,2, DARKGRAY);
        DrawTextEx(gft, "USE SPACE TO JUMP", { 750, 550 }, 30, 2, BLACK);
        Rectangle exitBtn = { 860, 600, 200, 60 };
        Color exitColor = RED; //without hover

        //Hovering
        if (CheckCollisionPointRec(GetMousePosition(), exitBtn)) 
        {
            exitColor = MAROON;
        }

        DrawRectangleRec(exitBtn, exitColor);
        DrawTextEx(gft, "EXIT", { 920, 615 }, 30,3, WHITE);
    }
    else {

        for (int i = 0; i < 5; i++) 
            obstacles[i].draw();


        plr.draw();

        

        DrawTextEx(gft, TextFormat("SCORE: %d", Sc), { 50, 50 }, 40,2, BLACK);
        DrawTextEx(gft, TextFormat("BEST: %d", Hi_Sc), { 50,140}, 30,2, PURPLE);

        //Levels
        if (Sc >= 25) 
        {
            DrawTextEx(gft, "LEVEL: INSANE", { 50, 100 }, 30,2, RED);
        }
        else if (Sc >= 10) {
            DrawTextEx(gft, "LEVEL: FAST", { 50, 100 }, 30,2, ORANGE);
        }
        else {
            DrawTextEx(gft, "LEVEL: NORMAL", { 50, 100 }, 30,2, GREEN);
        }

        if (state == 3)
        {
            DrawRectangle(0, 0, SW, 1080, ColorAlpha(BLACK, 0.4f));
            DrawTextEx(gft, "GAME OVER", { 600, 450 }, 100,5, RED);
            DrawTextEx(gft, "PRESS R TO RESTART", { 800, 550 }, 23,3, WHITE);

            Rectangle menuBtn = { 860, 600, 200, 60 };
            Color menuColor = DARKBLUE; // Default color

            if (CheckCollisionPointRec(GetMousePosition(), menuBtn))
            {
                menuColor = BLUE; // Lighten up when hovering
            }

            DrawRectangleRec(menuBtn, menuColor);
            DrawTextEx(gft, "MENU", { 905, 615 }, 30,5, WHITE);
        }
    }
    EndDrawing();
}

void Game::unload() 
{
    //check this for why
    const char* scoreToSave = TextFormat("%d", Hi_Sc);
    SaveFileText("highscore.txt", (char*)scoreToSave);


    plr.unload();
    UnloadTexture(bg);
    UnloadTexture(pp);
    UnloadTexture(pp_f);
    UnloadSound(jumpSnd);
    UnloadSound(scoreSnd);
    UnloadMusicStream(deathMusic);
    UnloadFont(gft);
}