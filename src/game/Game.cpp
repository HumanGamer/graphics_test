#include "Game.hpp"
#include <SDL.h>
#include <bgfx/bgfx.h>
#include "../graphics/GraphicsSystem.hpp"

//-------------------------------------------

Game::Game()
{

}

Game::~Game()
{
    delete GFX;
}

//-------------------------------------------

bool Game::init(int argc, const char** argv)
{
    if (!GFX->init(800, 600))
        return false;

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    return true;
}

bool Game::update()
{
    render();
    GFX->update();

    if (GFX->closeRequested())
        return false;

    return true;
}

void Game::render()
{
    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Test");

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::frame();
}
