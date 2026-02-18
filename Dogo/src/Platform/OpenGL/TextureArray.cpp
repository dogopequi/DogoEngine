#include "dgpch.h"
#include "TextureArray.h"
#include "Dogo/Utils/Logger.h"
#include "stb/stb_image.h"
namespace Dogo
{
    uint32_t TextureArray::AddTexture(const std::string& filepath)
	{
        if (m_CurrentLayer >= m_MaxLayers) {
            DG_ERROR("Error: Texture array is full!\n");
            return -1;
        }

        int texWidth, texHeight, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(filepath.c_str(), &texWidth, &texHeight, &channels, 4);

        if (!data) {
            DG_ERROR("Failed to load texture: %s\n", filepath.c_str());
            return -1;
        }

        if (texWidth != m_Width || texHeight != m_Height) {
            DG_ERROR("Texture size mismatch for %s must be %d x %d\n", filepath.c_str(), m_Width ,m_Height);
            stbi_image_free(data);
            return -1;
        }

        glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_CurrentLayer, m_Width, m_Height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);

        return m_CurrentLayer++;
	}
    void TextureArray::AddWhiteLayer()
    {
        std::vector<uint32_t> whitePixels(m_Width * m_Height, 0xffffffff);

        glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0,
            0, 0, m_CurrentLayer,
            m_Width, m_Height, 1,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            whitePixels.data()
        );

        m_CurrentLayer++;
    }
	void TextureArray::Bind() const
	{
        glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
	}
    void TextureArray::Clear() const
    {
    }
    TextureArray::TextureArray(uint32_t width, uint32_t height, uint32_t maxLayers)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);

		glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, m_Width, m_Height, m_MaxLayers, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

		m_CurrentLayer = 0;
	}
    TextureArray::~TextureArray()
    {
        glDeleteTextures(1, &m_ID);
    }
}