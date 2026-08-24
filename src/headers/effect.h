#pragma once
#include <SDL3/SDL.h>
#include "entity.h"

class Effect : public Entity
{
public:
    Effect(float cx, float cy, SDL_Texture *t);
    void update(float dt);
};