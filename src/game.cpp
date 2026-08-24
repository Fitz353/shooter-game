#include "headers/game.h"
#include "headers/bullet.h"
#include "headers/constants.h"
#include <SDL3/SDL.h>

bool Game::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init failed: %s", SDL_GetError());
    return false;
  }
  window = SDL_CreateWindow("Fritz's game", WIDTH, HEIGHT, 0);
  if (!window) {
    SDL_Log("Create window failed: %s", SDL_GetError());
    return false;
  }
  renderer = SDL_CreateRenderer(window, NULL);
  if (!renderer) {
    SDL_Log("Renderer failed: %s", SDL_GetError());
    return false;
  }
  SDL_SetRenderVSync(renderer, 1);
  SDL_srand(0);
  if (!assets.load(renderer)) {
    return false;
  }
  player.setSprite(assets.player, 16, 16, 3, 1);
  return true;
}

void Game::run() {
  SDL_Event event;
  Uint64 lastTick = SDL_GetTicks();

  while (running) {

    Uint64 now = SDL_GetTicks();
    float dt = (now - lastTick) / 1000.f;
    // Clamped dt
    if (dt > 0.05f) {
      dt = 0.05f;
    }
    lastTick = now;

    bg_scroll += 40.f * dt;
    if (bg_scroll >= 64.f * BG_SCALE) {
      bg_scroll -= 64.f * BG_SCALE;
    }

    for (Effect &f : effects) {
      f.update(dt);
    }
    std::erase_if(effects, [](const Effect &f) { return !f.isAlive(); });

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      if (event.type == SDL_EVENT_KEY_DOWN &&
          event.key.scancode == SDL_SCANCODE_RETURN &&
          current != GameState::PLAYING) {
        reset();
      }
    }

    if (current == GameState::PLAYING) {
      // Timer starts gets initialized at 0
      spawn_timer -= dt;
      if (spawn_timer <= 0.f) {
        spawn_timer = spawn_delay;
        enemies.push_back(spawnRandomEnemy(assets));

        if (spawn_delay > 0.25f) {
          spawn_delay -= 0.015f;
        }
      }

      const bool *keys = SDL_GetKeyboardState(NULL);
      // Player methods
      player.handleInput(keys, dt);
      player.keepBounds();

      // Put bullets in vector
      if (player.wantstoshoot(keys, dt)) {
        // Bullets methods, this is a vector of bullets
        bullets.push_back(
            Bullet(player.getCenter(), player.getTop(), assets.bullet, -600.f));
      }

      // Update the location of the bullets from the vector
      for (Bullet &b : bullets) {
        b.update(dt);
      }

      for (auto &e : enemies) {
        e->update(dt);
        if (e->isAlive() && e->getRect().y > 0.f && e->wantsToShoot(dt)) {
          SDL_FRect r = e->getRect();
          enemyBullets.push_back(
              Bullet(r.x + r.w / 2.f, r.y + r.h, assets.enemybullet, 250.f, 4));
        }
      }

      for (Bullet &b : enemyBullets) {
        b.update(dt);
      }

      for (Bullet &b : bullets) {
        SDL_FRect br = b.getHitbox();
        for (auto &e : enemies) {
          if (!e->isAlive())
            continue;
          SDL_FRect er = e->getHitbox();
          if (SDL_HasRectIntersectionFloat(&br, &er)) {
            b.kill();
            e->damage(1);
            if (!e->isAlive()) {
              score++;
              SDL_FRect r = e->getRect();
              effects.push_back(
                  Effect(r.x + r.w / 2.f, r.y + r.h / 2.f, assets.explosion));
            }
            break;
          }
        }
      }
      if (invuln > 0.f) {
        invuln -= dt;
      }

      SDL_FRect pr = player.getHitbox();
      for (auto &e : enemies) {
        if (!e->isAlive() || invuln > 0.f)
          continue;

        SDL_FRect er = e->getHitbox();
        if (SDL_HasRectIntersectionFloat(&pr, &er)) {
          SDL_FRect r = e->getRect();
          effects.push_back(
              Effect(r.x + r.w / 2.f, r.y + r.h / 2.f, assets.explosion));
          e->kill();
          hitPlayer();
          break;
        }
      }

      if (invuln <= 0.f) {
        SDL_FRect pr2 = player.getHitbox();
        for (Bullet &b : enemyBullets) {
          if (!b.isAlive())
            continue;
          SDL_FRect br2 = b.getHitbox();
          if (SDL_HasRectIntersectionFloat(&pr2, &br2)) {
            b.kill();
            hitPlayer();
            break;
          }
        }
      }

      std::erase_if(bullets, [](const Bullet &b) { return !b.isAlive(); });
      std::erase_if(enemies, [](const std::unique_ptr<Enemy> &e) {
        return !e->isAlive();
      });
      std::erase_if(enemyBullets, [](const Bullet &b) { return !b.isAlive(); });
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
    SDL_RenderClear(renderer);

    renderBackground();

    if (current == GameState::MENU) {
      drawCentered(assets.start, 48.f, 8.f, HEIGHT / 2.f - 16.f, 4.f);
    }

    if (invuln <= 0.f || SDL_fmodf(invuln, 0.2f) > 0.1f) {
      player.render(renderer);
    }

    for (Bullet &b : bullets) {
      b.render(renderer);
    }
    for (auto &e : enemies) {
      e->render(renderer);
    }

    for (Bullet &b : enemyBullets) {
      b.render(renderer);
    }

    for (Effect &f : effects) {
      f.render(renderer);
    }
    drawNumber(score, 16.f, 16.f, 3.f);

    for (int i = 0; i < lives; i++) {
      SDL_FRect src = {0.f, 0.f, 16.f, 16.f};
      SDL_FRect dst = {WIDTH - 40.f - i * 40.f, 16.f, 32.f, 32.f};
      SDL_RenderTexture(renderer, assets.life, &src, &dst);
    }

    if (current == GameState::GAME_OVER) {
      SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
      SDL_SetRenderDrawColor(renderer, 120, 0, 0, 110);
      SDL_FRect full = {0, 0, WIDTH, HEIGHT};
      SDL_RenderFillRect(renderer, &full);

      drawCentered(assets.gameover, 72.f, 8.f, HEIGHT / 2.f - 60.f, 4.f);
      drawNumber(score, WIDTH / 2.f - 36.f, HEIGHT / 2.f + 10.f, 6.f);
    }

    SDL_RenderPresent(renderer);
  }
}
void Game::cleanup() {
  assets.destroy();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::reset() {
  bullets.clear();
  effects.clear();
  enemies.clear();
  enemyBullets.clear();
  score = 0;
  spawn_timer = 0.f;
  player = Player();
  player.setSprite(assets.player, 16, 16, 3, 1);
  lives = 3;
  invuln = 0.f;
  spawn_delay = 1.0f;
  current = GameState::PLAYING;
}

void Game::renderBackground() {
  const float tile = 64.f * BG_SCALE;
  SDL_FRect src = {0.f, 0.f, 64.f, 64.f}; // frame 0 of the 2-frame sheet

  int cols = (int)(WIDTH / tile) + 1;
  int rows = (int)(HEIGHT / tile) + 2;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      SDL_FRect dst = {col * tile, row * tile - tile + bg_scroll, tile, tile};
      SDL_RenderTexture(renderer, assets.background, &src, &dst);
    }
  }
}

void Game::drawNumber(int value, float x, float y, float scale) {
  char buf[16];
  SDL_snprintf(buf, sizeof(buf), "%d", value);

  float gw = 8.f * scale;
  for (int i = 0; buf[i] != '\0'; i++) {
    int d = buf[i] - '0';
    int gi = (d == 0) ? 9 : d - 1;
    SDL_FRect src = {(float)((gi % 5) * 8), (float)((gi / 5) * 8), 8.f, 8.f};
    SDL_FRect dst = {x + i * gw, y, gw, gw};
    SDL_RenderTexture(renderer, assets.font, &src, &dst);
  }
}

void Game::drawCentered(SDL_Texture *t, float srcw, float srch, float y,
                        float scale) {
  SDL_FRect src = {0.f, 0.f, srcw, srch};
  SDL_FRect dst = {(WIDTH - srcw * scale) / 2.f, y, srcw * scale, srch * scale};
  SDL_RenderTexture(renderer, t, &src, &dst);
}

void Game::hitPlayer() {
  SDL_FRect pr = player.getRect();
  effects.push_back(
      Effect(pr.x + pr.w / 2.f, pr.y + pr.h / 2.f, assets.explosion));
  lives--;
  invuln = 2.f;
  if (lives <= 0) {
    current = GameState::GAME_OVER;
  }
}
