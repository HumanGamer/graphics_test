#include "GraphicsSystem.hpp"
#include <SDL.h>
#include <bgfx/bgfx.h>

#include <iostream>

#include "sdl_bgfx_setup.h"

GraphicsSystem* GFX = new GraphicsSystem();

GraphicsSystem::GraphicsSystem() : mInitialized(false), mWindow(nullptr), mWidth(800), mHeight(600)
{

}

GraphicsSystem::~GraphicsSystem()
{
    shutdown();
}

bool GraphicsSystem::init(uint32_t width, uint32_t height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL: %s\n", SDL_GetError();
        return false;
    }

    mWidth = width;
    mHeight = height;

    mWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               mWidth, mHeight,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    bgfx::renderFrame();
    sdlSetWindow(mWindow);

    bgfx::Init init;
    init.resolution.width = mWidth;
    init.resolution.height = mHeight;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return false;

    mInitialized = true;
    return true;
}

bool GraphicsSystem::resize(uint32_t width, uint32_t height)
{
    if (width != mWidth || height != mHeight)
    {
        mWidth = width;
        mHeight = height;

        bgfx::reset(width, height, BGFX_RESET_VSYNC);
        bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

        return true;
    }

    return false;
}

void GraphicsSystem::shutdown()
{
    if (!mInitialized)
        return;

    //bgfx::shutdown(); // sometimes crashes on quit
    sdlDestroyWindow(mWindow);
    SDL_Quit();

    mInitialized = false;
}
