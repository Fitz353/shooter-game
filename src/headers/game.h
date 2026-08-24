#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <vector>
#include "assets.h"
#include "effect.h"

enum class GameState
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
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<Effect> effects;
  std::vector<Bullet> enemyBullets;
  float spawn_timer = 0.f;
  float spawn_delay = 1.0f;
  GameState current = GameState::MENU;
  int score = 0;
  void reset();
  void hitPlayer();
  void renderBackground();
  void drawNumber(int value, float x, float y, float scale);
  void drawCentered(SDL_Texture *t, float srcw, float srch, float y, float scale);
  Assets assets;
  float bg_scroll = 0.f;
  static constexpr float BG_SCALE = 3.f;
  int lives = 3;
  float invuln = 0.f;

public:
  // function for init of window, renderer and video systems
  bool init();
  void run();
  void cleanup();
};
