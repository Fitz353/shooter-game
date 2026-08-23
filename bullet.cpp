#include "bullet.h"
#include "entity.h"
#include <SDL3/SDL.h>

Bullet:: Bullet(float startx, float starty)
    : Entity(startx, starty, 4.f, 12.f)
{
}

void Bullet::update(float dt){
    y -= speed * dt;
    if(y+h<0){
        alive = false;
    }
}

bool Bullet::isAlive()const{
    //this is a getter
    return alive;
}

void Bullet::render(SDL_Renderer* renderer){
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 255, 240, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
