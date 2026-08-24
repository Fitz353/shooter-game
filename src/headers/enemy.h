#pragma once
#include <SDL3/SDL.h>
#include "entity.h"

class Enemy : public Entity
{
    float speed = 50.f;

public:
    Enemy(float startx, float starty, float ew = 40.f, float eh = 40.f);
    void update(float dt);
    void render(SDL_Renderer *renderer);
};