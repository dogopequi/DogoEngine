#pragma once
#include "Dogo/Renderer/Core/TextureArray.h"
namespace Dogo
{
    class OpenGLTextureArray : public TextureArray {
    public:
        uint32_t AddTexture(const std::string& filepath) override;
        void Bind() const override;
        void Clear() const override;
        void AddWhiteLayer() override;
        OpenGLTextureArray(uint32_t width, uint32_t height, uint32_t maxLayers);
        OpenGLTextureArray() = delete;
        ~OpenGLTextureArray();
    };
}