#pragma once
#include <SDL3/SDL.h>



class Entity{
protected:
    float x, y;
    float w, h;
    bool alive = true;
public:
    Entity(float startx, float starty, float w, float h);
};
