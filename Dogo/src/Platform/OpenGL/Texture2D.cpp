#include "dgpch.h"
#include "Texture2D.h"
#include "Dogo/Utils/Logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Dogo
{
	Texture2D::Texture2D(std::string_view filepath)
	{
		Init(filepath);
	}
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void Texture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	void Texture2D::UpdateTexture(std::string_view filepath)
	{
		Init(filepath);
	}
	void Texture2D::Init(std::string_view filepath)
	{
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.data(), &width, &height, &channels, 0);
		if (data)
		{
			GLenum internalFormat = 0, dataFormat = 0;
			if (channels == 4)
			{
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3)
			{
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}
			if (internalFormat == 0 || dataFormat == 0)
			{
				DG_TRACE("format not supported for %s", filepath);
				stbi_image_free(data);
				return;
			}
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
			glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		}
		else
		{
			DG_WARN("Failed to load texture: %s", stbi_failure_reason());
		}
		stbi_image_free(data);
	}
}
