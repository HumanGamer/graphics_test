#pragma once

#include <cstdint>

struct SDL_Window;

class GraphicsSystem
{
public:
    GraphicsSystem();
    ~GraphicsSystem();

    bool init(uint32_t width, uint32_t height);
    bool resize(uint32_t width, uint32_t height);

    void shutdown();

private:
    SDL_Window* mWindow;

    bool mInitialized;
    uint32_t mWidth, mHeight;
};

extern GraphicsSystem* GFX;

