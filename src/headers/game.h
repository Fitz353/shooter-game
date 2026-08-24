#pragma once

#include <SDL3/SDL.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <vector>

enum class state
{
  MENU,
  PLAYING,
  GAME_OVER
};

class Game
{
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  bool running = true;
  // We need player inside so the run method can interact with the player's data
  Player player;
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;
  float spawn_timer = 0.f;
  float spawn_delay = 1.0f;

public:
  // function for init of window, renderer and video systems
  bool init();
  void run();
  void cleanup();
};
