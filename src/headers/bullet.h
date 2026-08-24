#pragma once
#include "entity.h"
#include <SDL3/SDL.h>

class Bullet : public Entity
{
    static constexpr float BW = 4.f;
    static constexpr float BH = 12.f;
    float speed = 600.f;

public:
    Bullet(float startx, float starty);
    void update(float dt);
    void render(SDL_Renderer *renderer) override;
};
