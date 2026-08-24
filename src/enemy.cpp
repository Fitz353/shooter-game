#include <SDL3/SDL.h>
#include "headers/enemy.h"
#include "headers/constants.h"

Enemy::Enemy(float startx, float starty, float ew, float eh)
    : Entity(startx, starty, ew, eh)
{
}

void Enemy::update(float dt)
{
    y += speed * dt;
    // It needs to dissapear completely
    if (y > HEIGHT)
    {
        alive = false;
    }
}

void Enemy::render(SDL_Renderer *renderer)
{
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 200, 0, 156, 255);
    SDL_RenderFillRect(renderer, &rect);
}