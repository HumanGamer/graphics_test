#include "Shader.hpp"
#include <brtshaderc.h>
#include <string>
#include <iostream>

Shader::Shader(const char *shaderName) : mShaderName(shaderName)
{
    recompile();
}

Shader::~Shader()
{
    bgfx::destroy(mProgram);
}

void Shader::recompile()
{
    mRendererType = bgfx::getRendererType();
    bgfx::ShaderHandle vsh = createShaderHandle((std::string(mShaderName) + "V.sc").c_str(), SHADERTYPE_VERTEX);
    bgfx::ShaderHandle fsh = createShaderHandle((std::string(mShaderName) + "P.sc").c_str(), SHADERTYPE_PIXEL);
    mProgram = bgfx::createProgram(vsh, fsh);
}

bgfx::ShaderHandle Shader::createShaderHandle(const char* file, ShaderType type)
{
    shaderc::ShaderType sType;
    switch (type)
    {
        case SHADERTYPE_VERTEX:
            sType = shaderc::ST_VERTEX;
            break;
        case SHADERTYPE_PIXEL:
            sType = shaderc::ST_FRAGMENT;
            break;
        case SHADERTYPE_COMPUTE:
            sType = shaderc::ST_COMPUTE;
            break;
    }
    const bgfx::Memory* mem = shaderc::compileShader(sType, file);
    if (mem == nullptr)
    {
        std::cerr << "Failed to compile shader '" << file << "'" << std::endl;
        exit(1);
    }
    return bgfx::createShader(mem);
}
