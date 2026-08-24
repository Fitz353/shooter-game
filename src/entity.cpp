#include <SDL3/SDL.h>
#include "headers/entity.h"

// Constructor of entity
Entity::Entity(float startx, float starty, float w, float h)
    : x(startx), y(starty), w(w), h(h)
{
}

void Entity::setSprite(SDL_Texture *t, int fw, int fh, int count, int startFrame)
{
    tex = t;
    frame_w = fw;
    frame_h = fh;
    frame_count = count;
    frame = startFrame;
}

void Entity::advanceAnim(float dt)
{
    if (frame_count <= 1)
    {
        return;
    }
    anim_timer += dt;
    float seconds_per_frame = 1.f / anim_fps;
    while (anim_timer >= seconds_per_frame)
    {
        anim_timer -= seconds_per_frame;
        frame = (frame + 1) % frame_count;
    }
}

void Entity::render(SDL_Renderer *renderer)
{
    SDL_FRect dst = {x, y, w, h};
    if (!tex)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &dst);
        return;
    }
    SDL_FRect src = {(float)(frame * frame_w), 0.f,
                     (float)frame_w, (float)frame_h};
    SDL_RenderTexture(renderer, tex, &src, &dst);
}