#include "headers/assets.h"
#include <SDL3_image/SDL_image.h>

static SDL_Texture *loadOne(SDL_Renderer *renderer, const char *path)
{
    SDL_Texture *t = IMG_LoadTexture(renderer, path);
    if (!t)
    {
        SDL_Log("Failed to load %s: %s", path, SDL_GetError());
        return nullptr;
    }
    SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    return t;
}

bool Assets::load(SDL_Renderer *renderer)
{
    player = loadOne(renderer, "assets/player.png");
    bullet = loadOne(renderer, "assets/bullet.png");
    grunt = loadOne(renderer, "assets/grunt.png");
    tank = loadOne(renderer, "assets/tank.png");
    zigzag = loadOne(renderer, "assets/zigzag.png");
    background = loadOne(renderer, "assets/background.png");
    font = loadOne(renderer, "assets/font.png");
    gameover = loadOne(renderer, "assets/gameover.png");
    start = loadOne(renderer, "assets/start.png");
    explosion = loadOne(renderer, "assets/explosion.png");

    return player && bullet && grunt && tank && zigzag && background &&
           font && gameover && start && explosion;
}

void Assets::destroy()
{
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(bullet);
    SDL_DestroyTexture(grunt);
    SDL_DestroyTexture(tank);
    SDL_DestroyTexture(zigzag);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(font);
    SDL_DestroyTexture(gameover);
    SDL_DestroyTexture(start);
}