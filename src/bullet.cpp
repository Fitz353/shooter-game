#include "headers/bullet.h"
#include "headers/entity.h"
#include <SDL3/SDL.h>

Bullet::Bullet(float startx, float starty, SDL_Texture* t)
    : Entity(startx - BW / 2.f, starty - BH, BW, BH)
{
    setSprite(t, 16, 16, 1);
}

void Bullet::update(float dt)
{
    y -= speed * dt;
    if (y + h < 0)
    {
        alive = false;
    }
}

