#include <raylib.h>
#pragma once

class Bird {

    float vel, g, angle;

public:
    int x, y,w,h;
    Texture2D img;


    Bird();// Constructor
    void update();//check gravity & updates pos
    void flap();//jump
    void draw();//rotate and draw
    bool checkCollision();//boundry collisons
    void reset();//sab wapis aopi jagah
    void unload();//deleting
};