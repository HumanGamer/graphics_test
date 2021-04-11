#include "GraphicsSystem.hpp"
#include <SDL.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include "gfxhelpers.hpp"

#include <iostream>

//-------------------------------------------
GraphicsSystem* GFX = new GraphicsSystem();

//-------------------------------------------
GraphicsSystem::GraphicsSystem() : mInitialized(false), mWindow(nullptr), mWidth(800), mHeight(600), mWindowClosed(true)
{

}

GraphicsSystem::~GraphicsSystem()
{
    shutdown();
}

//-------------------------------------------
bool GraphicsSystem::init(uint32_t width, uint32_t height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Error initializing SDL: %s\n", SDL_GetError();
        return false;
    }

    mWidth = width;
    mHeight = height;
    mWindowClosed = false;

    mWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               mWidth, mHeight,
                               SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    bgfx::renderFrame();
    GFXHelpers::SDLSetWindow(mWindow);

    bgfx::Init init;
    init.resolution.width = mWidth;
    init.resolution.height = mHeight;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
    {
        std::cout << "Error initializing BGFX: %s\n";
        shutdown();
        return false;
    }

    mInitialized = true;
    return true;
}

//-------------------------------------------
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

void GraphicsSystem::update()
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
                mWindowClosed = true;
                break;
        }
    }
}

//-------------------------------------------
void GraphicsSystem::shutdown()
{
    if (!mInitialized)
        return;

    mWindowClosed = true;

    //bgfx::shutdown(); // sometimes crashes on quit
    GFXHelpers::SDLDestroyWindow(mWindow);
    SDL_Quit();

    mInitialized = false;
}
