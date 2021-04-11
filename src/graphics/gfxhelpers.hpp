#pragma once

struct SDL_Window;

namespace GFXHelpers
{
    extern inline bool SDLSetWindow(SDL_Window *_window);
    extern inline void SDLDestroyWindow(SDL_Window *_window);
}
