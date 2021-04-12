cmake_minimum_required(VERSION 3.19)
project(graphics_test)

set(CMAKE_CXX_STANDARD 17)

# sdl
add_subdirectory(deps/sdl)
target_compile_definitions(SDL2-static PUBLIC HAVE_LIBC) # To avoid linker error
include_directories(deps/sdl/include)

# bgfx
add_subdirectory(deps/bgfx.cmake)
include_directories(deps/bgfx.cmake/bgfx/include)
include_directories(deps/bgfx.cmake/bgfx/tools/brtshaderc)
include_directories(deps/bgfx.cmake/bimg/include)
include_directories(deps/bgfx.cmake/bx/include)

set(MAIN_SRC
    # Sources
    src/main.cpp
    src/graphics/GraphicsSystem.cpp
    src/graphics/gfxhelpers.cpp
    src/game/Game.cpp
    src/shaders/Shader.cpp

    # Headers
    src/graphics/GraphicsSystem.hpp
    src/graphics/gfxhelpers.hpp
    src/game/Game.hpp
    src/shaders/Shader.hpp)

add_executable(graphics_test ${MAIN_SRC})
target_link_libraries(graphics_test PUBLIC SDL2-static SDL2main bgfx brtshaderc bimg bx)
