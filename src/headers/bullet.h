#pragma once
#include "entity.h"
#include <SDL3/SDL.h>
#include <iostream>

class Bullet : public Entity{
    float speed = 600.f;
public:
    Bullet(float startx, float starty);
    void update(float dt);
    void render(SDL_Renderer* renderer);
    bool isAlive() const;
};
