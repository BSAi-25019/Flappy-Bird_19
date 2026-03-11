#pragma once
#include "raylib.h"

class Pipe {
    float spd, gapY;//gapY pipe ke darmiyaan
    int gapS;//top & Bot pipe ke darmiyaan

public:
    int x, w, h;
    Texture2D imgTop, imgBot;  
    bool scored = false;

    Pipe();// COnstructer
    void init(int startX, Texture2D top, Texture2D bot);
    void update(), draw();
    void setSpeed(float newSpeed)
    {
        spd = newSpeed;
    }
    Rectangle getTopRect(), getBottomRect();
};