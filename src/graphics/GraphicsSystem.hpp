#pragma once

#include <cstdint>
#include <bgfx/bgfx.h>

struct SDL_Window;

class GraphicsSystem
{
public:
    GraphicsSystem();
    virtual ~GraphicsSystem();

    /// Initialize graphics system
    /// @param width Window width
    /// @param height Window height
    bool init(uint32_t width, uint32_t height, bgfx::RendererType::Enum type = bgfx::RendererType::Count);

    /// Set rendering backend
    /// @param type Renderer Type
    /// @return true if successful, false if failed
    bool setRendererType(bgfx::RendererType::Enum type);

    /// Resize window
    /// @param width Window width
    /// @param height Window height
    bool resize(uint32_t width, uint32_t height);

    /// Update renderer
    void update();

    /// Check if the app should close
    bool closeRequested() { return mWindowClosed; }

    /// Shutdown graphics system
    void shutdown();

private:
    SDL_Window* mWindow;

    bool mInitialized;
    bool mWindowClosed;
    uint32_t mWidth, mHeight;
};

extern GraphicsSystem* GFX;

