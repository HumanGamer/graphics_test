#include <iostream>
#include <SDL.h>
#include <bgfx/bgfx.h>

#include "graphics/gfxhelpers.hpp"
#include "graphics/GraphicsSystem.hpp"

void render();
void gameLoop();
void handleEvents();
void cleanup();

bool running = true;
int main(int argc, char *argv[])
{
    GFX->init(800, 600);

    gameLoop();

    cleanup();
    return 0;
}

void cleanup()
{
    delete GFX;
}

void render()
{
    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Test");

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::frame();
}


void gameLoop()
{
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    while (running)
    {
        render();
        handleEvents();
    }
}

void handleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_WINDOWEVENT:
            {
                const SDL_WindowEvent &wev = event.window;
                switch (wev.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        GFX->resize(wev.data1, wev.data2);
                        break;
                }
                break;
            }
            case SDL_QUIT:
                running = false;
                break;
        }
    }
}
