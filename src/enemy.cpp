#include <SDL3/SDL.h>
#include <memory>
#include "headers/enemy.h"
#include "headers/constants.h"

Enemy::Enemy(float startx, float starty, float w, float h,
             float speed, int hp, Uint8 r, Uint8 g, Uint8 b)
    : Entity(startx, starty, w, h), speed(speed), hp(hp), r(r), g(g), b(b)
{
}

void Enemy::render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
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
    : Enemy(startx, starty, 40.f, 40.f, 50.f, 1, 200, 0, 156)
{
}

void Grunt::update(float dt)
{
    y += speed * dt;
    if (offScreen())
    {
        alive = false;
    }
}

// --- Tank: big, slow, takes three hits ---
Tank::Tank(float startx, float starty)
    : Enemy(startx, starty, 70.f, 70.f, 25.f, 3, 220, 80, 40)
{
}

void Tank::update(float dt)
{
    y += speed * dt;
    if (offScreen())
    {
        alive = false;
    }
}

// --- Zigzagger: sine-wave horizontal drift ---
Zigzagger::Zigzagger(float startx, float starty)
    : Enemy(startx, starty, 30.f, 30.f, 90.f, 1, 60, 220, 120), baseX(startx)
{
}

void Zigzagger::update(float dt)
{
    t += dt;
    y += speed * dt;
    x = baseX + SDL_sinf(t * FREQUENCY) * AMPLITUDE;
    if (offScreen())
    {
        alive = false;
    }
}

std::unique_ptr<Enemy> spawnRandomEnemy()
{
    switch (SDL_rand(3))
    {
    case 0:
        return std::make_unique<Grunt>((float)SDL_rand(WIDTH - 40), -40.f);
    case 1:
        return std::make_unique<Tank>((float)SDL_rand(WIDTH - 70), -70.f);
    default:
        // keep baseX inset so the sine swing stays on screen
        return std::make_unique<Zigzagger>(
            Zigzagger::AMPLITUDE + (float)SDL_rand(WIDTH - 30 - 2 * (int)Zigzagger::AMPLITUDE), -30.f);
    }
}