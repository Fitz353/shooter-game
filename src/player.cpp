#include "headers/player.h"
#include "headers/constants.h"
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL.h>

// Constructor ; parameter width, parameter height
Player::Player(float pw, float ph)
    : Entity(WIDTH / 2.f - pw / 2.f, HEIGHT - ph - 20.f, pw, ph)
{
}

void Player::handleInput(const bool *keys, float dt)
{
    frame = 1; // neutral
    if (keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_A])
    {
        x -= speed * dt;
        frame = 0;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D])
    {
        x += speed * dt;
        frame = 2;
    }
    if (keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W])
    {
        y -= speed * dt;
    }
    if (keys[SDL_SCANCODE_DOWN] || keys[SDL_SCANCODE_S])
    {
        y += speed * dt;
    }
}

void Player::keepBounds()
{
    // By SDL  convention, x and y represent the left-upper corner of the rectangle, so the right and up edges definitions are correct
    // Also, keep in mind that the X axis works as usual, but the Y axis in reversed in computer graphics, so it grows downwards
    if (x < 0)
    {
        x = 0;
    }
    if (x + w > WIDTH)
    {
        x = WIDTH - w;
    }
    if (y < 0)
    {
        y = 0;
    }
    if (y + h > HEIGHT)
    {
        y = HEIGHT - h;
    }
}

bool Player::wantstoshoot(const bool *keys, float dt)
{
    shoot_cooldown -= dt;
    if (keys[SDL_SCANCODE_SPACE] && shoot_cooldown <= 0.f)
    {
        shoot_cooldown = shoot_delay;
        return true;
    }
    return false;
}

// Returns the middle
float Player::getCenter() const
{
    return x + w / 2.f;
}

float Player::getTop() const
{
    return y;
}
