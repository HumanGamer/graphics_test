#include <iostream>
#include <SDL.h>
#include <bgfx/bgfx.h>

#include "graphics/GraphicsSystem.hpp"

void init();
void gameLoop();
void render();
void cleanup();

int main(int argc, char *argv[])
{
    init();

    gameLoop();

    cleanup();
    return 0;
}

void cleanup()
{
    delete GFX;
}

void init()
{
    GFX->init(800, 600);

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
}

void gameLoop()
{
    while (true)
    {
        render();
        GFX->update();

        if (GFX->closeRequested())
            break;
    }
}

void render()
{
    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Test");

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::frame();
}
