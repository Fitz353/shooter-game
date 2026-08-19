#include "game.h"
#include <iostream>
#include <SDL3/SDL.h>
#include "constants.h"


bool Game::init(){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Fritz's game", WIDTH, HEIGHT, 0);
    if(!window){
        SDL_Log("Create window failed: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        SDL_Log("Renderer failed: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::run(){
    SDL_Event event;
    Uint64 lastTick = SDL_GetTicks();

    while(running){

        Uint64 now = SDL_GetTicks();
        float dt = (now - lastTick)/1000.f;
        lastTick = now;

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                running = false;
            }
        }

        const bool* keys = SDL_GetKeyboardState(NULL);
        player.handleInput(keys, dt);
        player.keepBounds();

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);

        SDL_RenderPresent(renderer);
    }
}
void Game::cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
