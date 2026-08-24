#pragma once
#include "entity.h"
#include <SDL3/SDL.h>

class Player : public Entity
{

    // float x, y;
    // float w = 40, h = 40;
    float speed = 300.f;
    float shoot_cooldown = 0.f;
    float shoot_delay = 0.25f;

public:
    // Constructor cannot have a return type
    Player(float pw = 48.f, float ph = 48.f);
    float getCenter() const;
    float getTop() const;
    void handleInput(const bool *keys, float dt);
    void keepBounds();
    bool wantstoshoot(const bool *keys, float dt);
};
