#include "dgpch.h"
#include "OpenGLTexture.h"
#include "Dogo/Utils/Logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Dogo
{
	OpenGLTexture::OpenGLTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap)
		: m_FilePath(filepath), m_TexType(textureType), m_GLTextureType(Texture::TexD_ToOpenGL(textureType)), m_Filter(filter), m_Wrap(wrap), m_IsMipMap(mipmap)
	{
		Init(filepath, textureType, filter, wrap, mipmap);
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture::Bind(uint32_t textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(m_GLTextureType, m_RendererID);
	}
	void OpenGLTexture::Unbind(uint32_t textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(m_GLTextureType, NULL);
	}
	void OpenGLTexture::UpdateTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap)
	{
		m_GLTextureType = Texture::TexD_ToOpenGL(textureType);
		m_TexType = textureType;
		m_Filter = filter;
		m_Wrap = wrap;
		m_IsMipMap = mipmap;
		Init(filepath, textureType, filter, wrap, mipmap);
	}
	void OpenGLTexture::Init(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap)
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		switch (channels)
		{
		case 4:
			m_GLImageType = GL_RGBA;
			break;
		case 3:
			m_GLImageType = GL_RGB;
			break;
		default:
			DG_FATAL("Unknown Image Type");
		}
		GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
		glCreateTextures(m_GLTextureType, 1, &m_RendererID);
		glBindTexture(m_GLTextureType, m_RendererID);
		glTexParameteri(m_GLTextureType, GL_TEXTURE_WRAP_S, Texture::WrapToOpenGL(wrap));
		glTexParameteri(m_GLTextureType, GL_TEXTURE_WRAP_T, Texture::WrapToOpenGL(wrap));
		glTexParameteri(m_GLTextureType, GL_TEXTURE_MIN_FILTER, Texture::FilterToOpenGL(filter));
		glTexParameteri(m_GLTextureType, GL_TEXTURE_MAG_FILTER, Texture::FilterToOpenGL(filter));
		if (data)
		{
			glTexImage2D(m_GLTextureType, 0, internalFormat, width, height, 0, m_GLImageType, GL_UNSIGNED_BYTE, data);
			if (mipmap)
				glGenerateMipmap(m_GLTextureType);
		}
		else
		{
			DG_WARN("Failed to load texture: %s", stbi_failure_reason());
		}
		stbi_image_free(data);
	}
}
