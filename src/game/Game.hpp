#pragma once

#include "../shaders/Shader.hpp"

class Game
{
public:
    Game();
    virtual ~Game();

    /// Initialize game
    bool init(int argc, const char** argv);

    /// Update game
    bool update();

private:

    /// Render Game
    void render();

    Shader* mBasicShader;
};
