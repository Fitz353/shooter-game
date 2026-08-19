#include "bullet.h"
#include <iostream>
#include <SDL3/SDL.h>

Bullet:: Bullet(float startx, float starty){
    x = startx;
    y = starty;
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
