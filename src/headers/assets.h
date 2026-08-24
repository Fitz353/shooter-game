#pragma once
#include <SDL3/SDL.h>

struct Assets
{
    SDL_Texture *player = nullptr;
    SDL_Texture *bullet = nullptr;
    SDL_Texture *grunt = nullptr;
    SDL_Texture *tank = nullptr;
    SDL_Texture *zigzag = nullptr;
    SDL_Texture *background = nullptr;
    SDL_Texture *font = nullptr;
    SDL_Texture *gameover = nullptr;
    SDL_Texture *start = nullptr;
    SDL_Texture *explosion = nullptr;
    SDL_Texture *life = nullptr;
    SDL_Texture *enemybullet = nullptr;

    bool load(SDL_Renderer *renderer);
    void destroy();
};