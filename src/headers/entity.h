#pragma once
#include <SDL3/SDL.h>

class Entity
{
protected:
    float x, y;
    float w, h;
    bool alive = true;

public:
    Entity(float startx, float starty, float w, float h);
    SDL_FRect getRect() const { return {x, y, w, h}; }
    void kill() { alive = false; }
    bool isAlive() const { return alive; }
};
