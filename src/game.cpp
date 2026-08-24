#include "headers/game.h"
#include <SDL3/SDL.h>
#include "headers/bullet.h"
#include "headers/constants.h"

bool Game::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("Fritz's game", WIDTH, HEIGHT, 0);
    if (!window)
    {
        SDL_Log("Create window failed: %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer)
    {
        SDL_Log("Renderer failed: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderVSync(renderer, 1);
    SDL_srand(0);
    return true;
}

void Game::run()
{
    SDL_Event event;
    Uint64 lastTick = SDL_GetTicks();

    while (running)
    {

        Uint64 now = SDL_GetTicks();
        float dt = (now - lastTick) / 1000.f;
        // Clamped dt
        if (dt > 0.05f)
        {
            dt = 0.05f;
        }
        lastTick = now;

        // Timer starts gets initialized at 0
        spawn_timer -= dt;
        if (spawn_timer <= 0.f)
        {
            spawn_timer = spawn_delay;
            // For pseudo random spawning of the enemies on the top of the map, and at the top
            float ex = (float)SDL_rand(WIDTH - 40);
            enemies.push_back(Enemy(ex, -40.f));
        }

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        const bool *keys = SDL_GetKeyboardState(NULL);
        // Player methods
        player.handleInput(keys, dt);
        player.keepBounds();

        // Put bullets in vector
        if (player.wantstoshoot(keys, dt))
        {
            // Bullets methods, this is a vector of bullets
            bullets.push_back(Bullet(player.getCenter(), player.getTop()));
        }

        // Update the location of the bullets from the vector
        for (Bullet &b : bullets)
        {
            b.update(dt);
        }

        for (Enemy &e : enemies)
        {
            e.update(dt);
        }
        for (Bullet &b : bullets)
        {
            SDL_FRect br = b.getRect();
            for (Enemy &e : enemies)
            {
                SDL_FRect er = e.getRect();
                if (SDL_HasRectIntersectionFloat(&br, &er))
                {
                    b.kill();
                    e.kill();
                    break;
                }
            }
        }
        std::erase_if(bullets, [](const Bullet &b)
                      { return !b.isAlive(); });
        std::erase_if(enemies, [](const Enemy &e)
                      { return !e.isAlive(); });

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        player.render(renderer);

        for (Bullet &b : bullets)
        {
            b.render(renderer);
        }
        for (Enemy &e : enemies)
        {
            e.render(renderer);
        }

        SDL_RenderPresent(renderer);
    }
}
void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
