#pragma once
#include <SDL3/SDL.h>

class Entity
{
protected:
    float x, y;
    float w, h;
    bool alive = true;
    SDL_Texture *tex = nullptr; // borrowed, never destroyed here
    int frame_w = 0, frame_h = 0;
    int frame_count = 1;
    int frame = 0;
    float anim_timer = 0.f;
    float anim_fps = 8.f;

public:
    Entity(float startx, float starty, float w, float h);
    virtual ~Entity() = default;

    virtual void render(SDL_Renderer *renderer);
    void setSprite(SDL_Texture *t, int fw, int fh, int count, int startFrame = 0);
    void advanceAnim(float dt);

    SDL_FRect getRect() const { return {x, y, w, h}; }
    SDL_FRect getHitbox() const
    {
        float ix = w * 0.25f;
        float iy = h * 0.25f;
        return {x + ix, y + iy, w - 2 * ix, h - 2 * iy};
    }
    void kill() { alive = false; }
    bool isAlive() const { return alive; }
};
