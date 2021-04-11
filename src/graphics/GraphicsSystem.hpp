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
    void update();
    bool closeRequested() { return mWindowClosed; }

    void shutdown();

private:
    SDL_Window* mWindow;

    bool mInitialized;
    bool mWindowClosed;
    uint32_t mWidth, mHeight;
};

extern GraphicsSystem* GFX;

