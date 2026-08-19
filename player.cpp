#include "player.h"
#include "constants.h"
#include <SDL3/SDL_scancode.h>
#include <iostream>
#include <SDL3/SDL.h>

//Constructor
Player:: Player(){
    x = WIDTH/2.f - w/2.f;
    y = HEIGHT - h - 20.f;
}

void Player::handleInput(const bool* keys, float dt){
    if(keys[SDL_SCANCODE_LEFT]){
        x-=speed * dt;
    }
    if(keys[SDL_SCANCODE_RIGHT]){
        x+=speed * dt;
    }
    if(keys[SDL_SCANCODE_UP]){
        y-=speed * dt;
    }
    if(keys[SDL_SCANCODE_DOWN]){
        y+=speed * dt;
    }
}

void Player::render(SDL_Renderer* renderer){
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    }

void Player::keepBounds(){
    // By SDL  convention, x and y represent the left-upper corner of the rectangle, so the right and up edges definitions are correct
    // Also, keep in mind that the X axis works as usual, but the Y axis in reversed in computer graphics, so it grows downwards
    if(x<0){
        x = 0;
    }
    if(x+ w > WIDTH){
        x = WIDTH - w;
    }
    if(y<0){
        y = 0;
    }
    if( y + h>HEIGHT){
        y = HEIGHT - h;
    }
}

bool Player::wantstoshoot(const bool* keys, float dt){
    shoot_cooldown-=dt;
    if(keys[SDL_SCANCODE_SPACE] && shoot_cooldown <=0.f){
        shoot_cooldown = shoot_delay;
        return true;
    }
    return false;
}

// Returns the middle
float Player::getCenter() const{
    return x + w/2.f;
}

float Player::getTop() const{
    return y;
}
