#pragma once
#include "entity.h"
#include <SDL3/SDL.h>

class Bullet : public Entity
{
    static constexpr float BW = 16.f;
    static constexpr float BH = 16.f;
    float speed = 600.f;

public:
    Bullet(float startx, float starty, SDL_Texture* t);
    void update(float dt);
};
