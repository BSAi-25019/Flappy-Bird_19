#include "BSAI25019_MINI_PROJECT_1_Bird.h"
#define SW 1920
#define SH 1080



// Constructor
Bird::Bird()
{
    img = LoadTexture("bird.png");
    //dims
    w = 80;
    h = 70;
    g = 0.5f;//graviyt
    reset();
}

void Bird::reset()
{
    x = 300;
    y = SH/2;
    w = 80;
    h = 70;
    vel = 0;
    angle = 0;
}

void Bird::update() 
{
    vel += g;//add on jump
    y += (int)vel;//then update

    // vel<0, bird(up). 
    // vel>=0, bird(down).
    if (vel < 0) 
    {
        angle = -20;
    }
    else {
        angle += 2.5f;

        if (angle > 90) 
            angle = 90;//downfall
    }
}

void Bird::flap() 
{
    vel = -8.5f;
}

void Bird::draw() 
{
    Rectangle src = { 0, 0, (float)img.width, (float)img.height }, dest = { (float)x, (float)y, (float)w, (float)h };

    //for obird tilting
    Vector2 origin = { (float)w / 2, (float)h / 2 };

    DrawTexturePro(img, src, dest, origin, angle, WHITE);
}

bool Bird::checkCollision() 
{
    //top
    if (y - 45 <= 0) 
        return true;

    //tottom 
    if ((y - 45) + (h - 12) >= 1080)
        return true;

    return false;
}

void Bird::unload() 
{
    UnloadTexture(img);
}