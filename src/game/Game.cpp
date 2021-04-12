#include "Game.hpp"
#include <SDL.h>
#include <bgfx/bgfx.h>
#include <bx/math.h>
#include "../graphics/GraphicsSystem.hpp"

//-------------------------------------------

Game::Game()
{

}

Game::~Game()
{
    delete GFX;
    delete mBasicShader;
}

//-------------------------------------------

struct PosColorVertex
{
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_abgr;

    static void init()
    {
        ms_layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

static PosColorVertex s_cubeVertices[] = {
    {-1.0f, 1.0f,  1.0f,  0xff000000},
    {1.0f,  1.0f,  1.0f,  0xff0000ff},
    {-1.0f, -1.0f, 1.0f,  0xff00ff00},
    {1.0f,  -1.0f, 1.0f,  0xff00ffff},
    {-1.0f, 1.0f,  -1.0f, 0xffff0000},
    {1.0f,  1.0f,  -1.0f, 0xffff00ff},
    {-1.0f, -1.0f, -1.0f, 0xffffff00},
    {1.0f,  -1.0f, -1.0f, 0xffffffff},
};

static const uint16_t s_cubeTriList[] = {
    0, 1, 2, // 0
    1, 3, 2,
    4, 6, 5, // 2
    5, 6, 7,
    0, 2, 4, // 4
    4, 2, 6,
    1, 5, 3, // 6
    5, 7, 3,
    0, 4, 1, // 8
    4, 5, 1,
    2, 3, 6, // 10
    6, 3, 7,
};

bgfx::VertexBufferHandle vbh;
bgfx::IndexBufferHandle ibh;
bool Game::init(int argc, const char **argv)
{
    if (!GFX->init(800, 600))
        return false;

    mBasicShader = new Shader("shaders/basic");

    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000FF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

    PosColorVertex::init();

    vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), PosColorVertex::ms_layout);
    ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList)));

    return true;
}

bool Game::update()
{
    render();
    GFX->update();

    //if (!GFX->setRendererType(bgfx::RendererType::Vulkan))
    //    return false;

    if (GFX->closeRequested())
        return false;

    return true;
}

void Game::render()
{
    const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
    const bx::Vec3 eye = {0.0f, 2.0f, -7.0f};

    // Set view and projection matrices
    {
        float view[16];
        bx::mtxLookAt(view, eye, at);

        float proj[16];
        bx::mtxProj(proj, 60.0f, float(GFX->getWindowWidth()) / float(GFX->getWindowHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
    }

    bgfx::touch(0);

    // Draw Cube
    {
        float mtx[16];
        bx::mtxIdentity(mtx);

        // Set model matrix
        bgfx::setTransform(mtx);

        bgfx::setVertexBuffer(0, vbh);
        bgfx::setIndexBuffer(ibh);

        bgfx::setState(BGFX_STATE_DEFAULT); // BGFX_STATE_PT_TRILIST is what it uses if you don't put anything.

        GFX->submit(0, mBasicShader);
    }

    bgfx::touch(0);
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0F, "Rendered with: %s", bgfx::getRendererName(bgfx::getRendererType()));

    bgfx::setDebug(BGFX_DEBUG_TEXT);
}
