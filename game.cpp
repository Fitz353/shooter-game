#include "game.h"
#include <cstdint>
#include <iostream>
#include <SDL3/SDL.h>
#include "bullet.h"
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
        // Player methods
        player.handleInput(keys, dt);
        player.keepBounds();

        // Put bullets in vector
        if(player.wantstoshoot(keys, dt)){
            // Bullets methods, this is a vector of bullets
            bullets.push_back(Bullet(player.getCenter(), player.getTop()));
        }

        // Update the location of the bullets from the vector
        for(Bullet& b : bullets){
            b.update(dt);
        }
        // Delete the bullets when they go off screen from the vector
        std::erase_if(bullets, [](const Bullet& b){ return !b.isAlive(); });

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);

        for(Bullet& b: bullets){
            b.render(renderer);
        }


        SDL_RenderPresent(renderer);
    }
}
void Game::cleanup(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
