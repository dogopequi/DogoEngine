#pragma once

namespace Dogo
{
    class TextureArray {
    public:

        virtual uint32_t AddTexture(const std::string& filepath) = 0;
        virtual void Bind() const = 0;
        virtual void Clear() const = 0;
        virtual void AddWhiteLayer() = 0;
        virtual inline uint32_t GetWidth() const { return m_Width; }
        virtual inline uint32_t GetID() const { return m_RendererID; }
        virtual inline uint32_t GetHeight() const { return m_Height; }
        virtual inline uint32_t GetLayerCount() const { return m_CurrentLayer - 1; }
        static TextureArray* Create(uint32_t width, uint32_t height, uint32_t maxLayers);
    protected:
        TextureArray(uint32_t width, uint32_t height, uint32_t maxLayers);
    protected:
        uint32_t m_Width, m_Height;
        uint32_t m_MaxLayers;
        uint32_t m_CurrentLayer;
        uint32_t m_RendererID{};
    };
}