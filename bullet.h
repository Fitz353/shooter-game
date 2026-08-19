#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Bullet{
    float x, y;
    float w = 4, h = 12;
    float speed = 600.f;
    bool alive = true;
public:
    Bullet(float startx, float starty);
    void update(float dt);
    void render(SDL_Renderer* renderer);
    bool isAlive() const;
};
