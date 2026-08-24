#pragma once
#include "entity.h"
#include <SDL3/SDL.h>

class Bullet : public Entity
{
    static constexpr float BW = 16.f;
    static constexpr float BH = 16.f;
    float vy;

public:
    Bullet(float cx, float cy, SDL_Texture *t, float vy, int frames = 1);
    void update(float dt);
};