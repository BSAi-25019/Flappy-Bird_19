#include "BSAI25019_MINI_PROJECT_1_Pipe.h"


//Constructer
Pipe::Pipe() 
{}

void Pipe::init(int startX, Texture2D top, Texture2D bot) 
{
    imgTop = top;
    imgBot = bot;
    x = startX;

    w = 110;
    h = 800;
    spd = 4.0f;
    gapS = 200;
    gapY = (float)GetRandomValue(210, 700);
}

void Pipe::update() 
{
    x -= (int)spd;

    if (x + w < 0)
    {
        x += 1750;
        gapY = (float)GetRandomValue(300, 700);

        scored = false;
    }
}

void Pipe::draw() 
{
    Rectangle srcTop = { 0, 0, (float)imgTop.width, (float)imgTop.height };
    Rectangle destTop = { (float)x, gapY - (gapS / 2) - 800, 100, 800 };
    DrawTexturePro(imgTop, srcTop, destTop, { 0,0 }, 0, WHITE);

    Rectangle srcBot = { 0, 0, (float)imgBot.width, (float)imgBot.height };
    Rectangle destBot = { (float)x, gapY + (gapS / 2), 100, 800 };
    DrawTexturePro(imgBot, srcBot, destBot, { 0,0 }, 0, WHITE);

  
}

Rectangle Pipe::getTopRect() 
{
    
    return { (float)x + 27, gapY - (gapS / 2) - 817, 50, 800 };
}

Rectangle Pipe::getBottomRect() 
{
    return { (float)x + 27, gapY + (gapS / 2)+17, 50, 800 };
}