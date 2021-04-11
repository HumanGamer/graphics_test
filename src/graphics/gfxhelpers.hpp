#pragma once

struct SDL_Window;

namespace GFXHelpers
{
    /// Set BGFX window handle from SDL_Window
    extern inline bool SDLSetWindow(SDL_Window *_window);

    /// Destroy SDL_Window
    extern inline void SDLDestroyWindow(SDL_Window *_window);
}
