#include "headers/bullet.h"
#include "headers/constants.h"
#include <SDL3/SDL.h>

Bullet::Bullet(float cx, float cy, SDL_Texture *t, float vy, int frames)
    : Entity(cx - BW / 2.f, cy - BH / 2.f, BW, BH), vy(vy) {
  setSprite(t, 16, 16, frames);
}

void Bullet::update(float dt) {
  advanceAnim(dt);
  y += vy * dt;
  if (y + h < 0 || y > HEIGHT) {
    alive = false;
  }
}
