#include "GBuffer.h"

#include <vector>
#include <GL/glew.h>

#include "FBOAttachment.h"
#include "Settings.h"

using namespace Renderer;

using Engine::Settings;

// GBuffer Layout
// Buffer   | Type   | R          | G          | B          | A
// Normal   | RGBA8U | normal.x   | normal.y   | ao         | roughness
// Albedo   | RGBA8U | albedo.r   | albedo.g   | albedo.b   | metallic
// Emmisive | RGB8U  | emmisive.r | emmisive.g | emmisive.b | NONE
// Depth    | D24S8  | depth      | stencil    | NONE       | NONE

GBuffer::GBuffer()
    : buffer(std::make_shared<FrameBuffer>())
{
    // Get settings
    const auto& settings = Settings::GetInstance();

    // Normal attachment
    Renderer::FBOAttachment normal =
    {
        GL_NEAREST,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE,
        GL_RGBA8,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_COLOR_ATTACHMENT0
    };

    // Albedo attachment
    Renderer::FBOAttachment albedo =
    {
        GL_NEAREST,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE,
        GL_RGBA8,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        GL_COLOR_ATTACHMENT1
    };

    // Emission attachment
    Renderer::FBOAttachment emmisive =
    {
        GL_NEAREST,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE,
        GL_RGB8,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        GL_COLOR_ATTACHMENT2
    };

    // Depth attachment
    Renderer::FBOAttachment depth =
    {
        GL_NEAREST,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE,
        GL_DEPTH24_STENCIL8,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        GL_DEPTH_STENCIL_ATTACHMENT
    };

    // Selected draw buffers
    std::vector<GLenum> drawBuffers =
    {
        normal.slot,
        albedo.slot,
        emmisive.slot
    };

    // Set buffer width and height
    buffer->width  = settings.window.dimensions.x;
    buffer->height = settings.window.dimensions.y;

    // Create frame buffer
    buffer->CreateFrameBuffer();
    buffer->Bind();
    buffer->AddTexture(buffer->colorTextures[0], normal);
    buffer->AddTexture(buffer->colorTextures[1], albedo);
    buffer->AddTexture(buffer->colorTextures[2], emmisive);
    buffer->AddTexture(buffer->depthTexture,     depth);
    buffer->SetDrawBuffers(drawBuffers);
    buffer->CheckStatus();
    buffer->EnableDepth();
    buffer->Unbind();
}

void GBuffer::BindGBuffer() const
{
    // Bind
    buffer->Bind();
}

void GBuffer::BindDefaultFBO() const
{
    // Unbind
    buffer->Unbind();
}
