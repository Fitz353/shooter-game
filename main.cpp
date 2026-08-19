#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <iostream>
#define HEIGHT 600
#define WIDTH 800



// These are the 3 modes of the game
enum class state{MENU, PLAYING, GAME_OVER};

class Player{
    float x, y;
    float w = 40, h = 40;
    float speed = 300.f;
public:
    //Constructor cannot have a return type
    Player();
    void handleInput(const bool* keys, float dt);
    void render(SDL_Renderer* renderer);
};

class Game{
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  bool running = true;
  Player player;
public:
    //function for init of window, renderer and video systems
    bool init();
    void run();
    void cleanup();
};




int main(int argc, char* argv[]){
    (void) argc;
    (void) argv;

    Game game;
    if(!game.init()){
        return 1;
    }
    game.run();
    game.cleanup();

    return 0;
}

Player:: Player(){
    x = WIDTH/2.f - w/2.f;
    y = HEIGHT - h - 20.f;
}

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
    SDL_Log("x = %.1f, y = %1.f", x, y);
}

void Player::render(SDL_Renderer* renderer){
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 0, 200, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
    }
