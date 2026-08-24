#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "entity.h"

class Enemy : public Entity
{
protected:
    float speed;
    int hp;
    Uint8 r, g, b;

public:
    Enemy(float startx, float starty, float w, float h,
          float speed, int hp, Uint8 r, Uint8 g, Uint8 b);

    virtual void update(float dt) = 0;
    void render(SDL_Renderer *renderer) override;

    void damage(int amount);
    bool offScreen() const;
};

class Grunt : public Enemy
{
public:
    Grunt(float startx, float starty);
    void update(float dt) override;
};

class Tank : public Enemy
{
public:
    Tank(float startx, float starty);
    void update(float dt) override;
};

class Zigzagger : public Enemy
{
    float baseX;
    float t = 0.f;
    static constexpr float FREQUENCY = 3.f;

public:
    static constexpr float AMPLITUDE = 90.f;

    Zigzagger(float startx, float starty);
    void update(float dt) override;
};

std::unique_ptr<Enemy> spawnRandomEnemy();