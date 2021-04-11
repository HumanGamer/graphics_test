#pragma once

#include "gfxhelpers.hpp"

#include <SDL_syswm.h>
#include <bgfx/platform.h>

namespace GFXHelpers
{
    static void *SDLNativeWindowHandle(SDL_Window *_window)
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(_window, &wmi))
        {
            return NULL;
        }

#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
        wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
        if(!win_impl)
        {
            int width, height;
            SDL_GetWindowSize(_window, &width, &height);
            struct wl_surface* surface = wmi.info.wl.surface;
            if(!surface)
                return nullptr;
            win_impl = wl_egl_window_create(surface, width, height);
            SDL_SetWindowData(_window, "wl_egl_window", win_impl);
        }
        return (void*)(uintptr_t)win_impl;
#		else
        return (void*)wmi.info.x11.window;
#		endif
#	elif BX_PLATFORM_OSX
        return wmi.info.cocoa.window;
#	elif BX_PLATFORM_WINDOWS
        return wmi.info.win.window;
#	endif // BX_PLATFORM_
    }

    bool SDLSetWindow(SDL_Window *_window)
    {
        SDL_SysWMinfo wmi;
        SDL_VERSION(&wmi.version);
        if (!SDL_GetWindowWMInfo(_window, &wmi))
        {
            return false;
        }

        bgfx::PlatformData pd;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
        pd.ndt          = wmi.info.wl.display;
#		else
        pd.ndt          = wmi.info.x11.display;
#		endif
#	elif BX_PLATFORM_OSX
        pd.ndt          = NULL;
#	elif BX_PLATFORM_WINDOWS
        pd.ndt = NULL;
#	endif // BX_PLATFORM_
        pd.nwh = SDLNativeWindowHandle(_window);

        pd.context = NULL;
        pd.backBuffer = NULL;
        pd.backBufferDS = NULL;
        bgfx::setPlatformData(pd);

        return true;
    }

    void SDLDestroyWindow(SDL_Window *_window)
    {
        if (!_window)
            return;
#	if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
#		if ENTRY_CONFIG_USE_WAYLAND
        wl_egl_window *win_impl = (wl_egl_window*)SDL_GetWindowData(_window, "wl_egl_window");
        if(win_impl)
        {
            SDL_SetWindowData(_window, "wl_egl_window", nullptr);
            wl_egl_window_destroy(win_impl);
        }
#		endif
#	endif
        SDL_DestroyWindow(_window);
    }
}
