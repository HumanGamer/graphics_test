#pragma once

#include <cstdint>
#include <bgfx/bgfx.h>
#include "../shaders/Shader.hpp"

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

    void submit(bgfx::ViewId viewId, Shader* shader, uint32_t _depth = 0, uint8_t _flags  = BGFX_DISCARD_ALL);

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

    uint32_t getWindowWidth() { return mWidth; }
    uint32_t getWindowHeight() { return mHeight; }

private:
    SDL_Window* mWindow;

    bgfx::RendererType::Enum mRendererType;
    bool mInitialized;
    bool mWindowClosed;
    uint32_t mWidth, mHeight;
};

extern GraphicsSystem* GFX;

