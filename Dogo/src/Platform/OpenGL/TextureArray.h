#pragma once

namespace Dogo
{
    class TextureArray {
    public:
        uint32_t AddTexture(const std::string& filepath);
        void Bind() const;
        void Clear() const;
        void AddWhiteLayer();
        TextureArray(uint32_t width, uint32_t height, uint32_t maxLayers);
        TextureArray() = delete;
        ~TextureArray();

    private:
        uint32_t m_Width, m_Height;
        uint32_t m_MaxLayers;
        uint32_t m_CurrentLayer;
        GLuint m_ID{};
    };
}