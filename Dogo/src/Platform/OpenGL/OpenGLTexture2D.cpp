#include "dgpch.h"
#include "OpenGLTexture2D.h"
#include "Dogo/Utils/Logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Dogo
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
		: m_FilePath(filepath)
	{
		Init(filepath);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
	void OpenGLTexture2D::UpdateTexture(const std::string& filepath)
	{
		Init(filepath);
	}
	void OpenGLTexture2D::Init(const std::string& filepath)
	{
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
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
