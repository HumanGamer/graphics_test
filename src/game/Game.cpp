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
    delete mBasicShader;
}

//-------------------------------------------

bool Game::init(int argc, const char** argv)
{
    if (!GFX->init(800, 600))
        return false;

    mBasicShader = new Shader("shaders/basic");

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    return true;
}

bool Game::update()
{
    render();
    GFX->update();

    //if (!GFX->setRendererType(bgfx::RendererType::Vulkan))
    //    return false;

    if (GFX->closeRequested())
        return false;

    return true;
}

void Game::render()
{
    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0F, "Rendered with: %s", bgfx::getRendererName(bgfx::getRendererType()));

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    //GFX->submit(0, mBasicShader);
}
