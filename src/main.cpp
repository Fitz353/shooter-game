#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "headers/game.h"

int main(int argc, char *argv[])
{
    // For no warning when compiling
    (void)argc;
    (void)argv;

    Game game;
    if (!game.init())
    {
        return 1;
    }
    game.run();
    game.cleanup();

    return 0;
}
