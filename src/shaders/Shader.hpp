#pragma once

#include <bgfx/bgfx.h>

class Shader
{
    friend class GraphicsSystem;

public:
    enum ShaderType
    {
        SHADERTYPE_VERTEX,
        SHADERTYPE_PIXEL,
        SHADERTYPE_COMPUTE,
    };

    Shader(const char* shaderName);
    ~Shader();

    void recompile();

private:
    bgfx::RendererType::Enum mRendererType;

    const char* mShaderName;

    static bgfx::ShaderHandle createShaderHandle(const char* file, ShaderType type);

    bgfx::ProgramHandle mProgram;
};
