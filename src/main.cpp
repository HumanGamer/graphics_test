#include <SDL.h> // need to include SDL.h for SDL main
#include "game/Game.hpp"

int main(int argc, char *argv[])
{
    Game game;
    if (!game.init(argc, (const char**)argv))
        return 1;

    while (game.update());

    return 0;
}
