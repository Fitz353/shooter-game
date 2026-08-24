#include "headers/effect.h"

static constexpr float SIZE = 48.f;
static constexpr int FRAMES = 6;

Effect::Effect(float cx, float cy, SDL_Texture *t)
    : Entity(cx - SIZE / 2.f, cy - SIZE / 2.f, SIZE, SIZE)
{
    setSprite(t, 16, 16, FRAMES);
    anim_fps = 16.f;
}

void Effect::update(float dt)
{
    int before = frame;
    advanceAnim(dt);
    if (frame < before)
    {
        alive = false;
    }
}