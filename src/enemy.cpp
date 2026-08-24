#include <SDL3/SDL.h>
#include <memory>
#include "headers/enemy.h"
#include "headers/constants.h"

Enemy::Enemy(float startx, float starty, float w, float h,
             float speed, int hp)
    : Entity(startx, starty, w, h), speed(speed), hp(hp)
{
}

void Enemy::damage(int amount)
{
    hp -= amount;
    if (hp <= 0)
    {
        alive = false;
    }
}

bool Enemy::offScreen() const
{
    return y > HEIGHT;
}

// --- Grunt: straight down, dies in one hit ---
Grunt::Grunt(float startx, float starty)
    : Enemy(startx, starty, 48.f, 48.f, 50.f, 1)
{
}

void Grunt::update(float dt)
{
    advanceAnim(dt);
    y += speed * dt;
    if (offScreen())
    {
        alive = false;
    }
}

// --- Tank: big, slow, takes three hits ---
Tank::Tank(float startx, float starty)
    : Enemy(startx, starty, 64.f, 64.f, 25.f, 3)
{
}

void Tank::update(float dt)
{
    advanceAnim(dt);
    y += speed * dt;
    if (offScreen())
    {
        alive = false;
    }
}

// --- Zigzagger: sine-wave horizontal drift ---
Zigzagger::Zigzagger(float startx, float starty)
    : Enemy(startx, starty, 32.f, 32.f, 90.f, 1), baseX(startx)
{
}

void Zigzagger::update(float dt)
{
    advanceAnim(dt);
    t += dt;
    y += speed * dt;
    x = baseX + SDL_sinf(t * FREQUENCY) * AMPLITUDE;
    if (offScreen())
    {
        alive = false;
    }
}

std::unique_ptr<Enemy> spawnRandomEnemy(const Assets &a)
{
    std::unique_ptr<Enemy> e;
    switch (SDL_rand(3))
    {
    case 0:
        e = std::make_unique<Grunt>((float)SDL_rand(WIDTH - 48), -48.f);
        e->setSprite(a.grunt, 16, 16, 6);
        break;
    case 1:
        e = std::make_unique<Tank>((float)SDL_rand(WIDTH - 64), -64.f);
        e->setSprite(a.tank, 16, 16, 4);
        break;
    default:
        e = std::make_unique<Zigzagger>(
            Zigzagger::AMPLITUDE +
                (float)SDL_rand(WIDTH - 32 - 2 * (int)Zigzagger::AMPLITUDE),
            -32.f);
        e->setSprite(a.zigzag, 16, 16, 5);
        break;
    }
    return e;
}