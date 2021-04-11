#include <iostream>
#include <SDL.h>
#include <bx/thread.h>
#include <bgfx/bgfx.h>

#include "sdl_bgfx_setup.h"

void render();

static int32_t renderThread(bx::Thread* _thread, void* _userData);

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cout << "Error initializing SDL: %s\n", SDL_GetError();

    uint32_t width = 800, height = 600;

    SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED,
                                               SDL_WINDOWPOS_CENTERED,
                                       width, height,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    bgfx::renderFrame();
    sdlSetWindow(win);

    bgfx::Init init;
    init.resolution.width = width;
    init.resolution.height = height;
    init.resolution.reset = BGFX_RESET_VSYNC;
    if (!bgfx::init(init))
        return 1;

    bool running = true;

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
    while (running)
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
                        {
                            uint32_t oldWidth = width;
                            uint32_t oldHeight = height;

                            width = wev.data1;
                            height = wev.data2;

                            if (width != oldWidth || height != oldHeight)
                            {
                                bgfx::reset(width, height, BGFX_RESET_VSYNC);
                                bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
                            }


                            break;
                        }
                    }
                    break;
                }
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        render();
    }

    //bgfx::shutdown(); // sometimes crashes on quit
    sdlDestroyWindow(win);
    SDL_Quit();

    return 0;
}

void render()
{
    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Test");

    bgfx::setDebug(BGFX_DEBUG_TEXT);

    bgfx::frame();
}
