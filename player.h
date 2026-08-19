#pragma once
#include <iostream>
#include <SDL3/SDL.h>

class Player{
    float x, y;
    float w = 40, h = 40;
    float speed = 300.f;
public:
    //Constructor cannot have a return type
    Player();
    void handleInput(const bool* keys, float dt);
    void render(SDL_Renderer* renderer);
    void keepBounds();
};
