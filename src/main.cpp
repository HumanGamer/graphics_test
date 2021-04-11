#include <iostream>
#include <SDL.h>
#include <bgfx/bgfx.h>

#include "graphics/GraphicsSystem.hpp"

void gameLoop();
void render();
void cleanup();

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

void gameLoop()
{
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

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
