#include "dgpch.h"
#include "OpenGLTexture.h"
#include "Dogo/Logger.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Dogo
{
	OpenGLTexture::OpenGLTexture(const std::string& filepath, const std::string& imageType, TextureType textureType, const std::string& name) : m_Name(name), m_Type(imageType), m_FilePath(filepath)
	{
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		switch (channels)
		{
		case 4:
			m_ImageType = GL_RGBA;
			break;
		case 3:
			m_ImageType = GL_RGB;
			break;
		default:
			DG_FATAL("Unknown Image Type");
		}
		// switch (imageType)
		// {
		// case ImageType::JPG:
		// 	m_ImageType = GL_RGB;
		// 	break;
		// case ImageType::JPEG:
		// 	m_ImageType = GL_RGB;
		// 	break;
		// case ImageType::PNG:
		// 	m_ImageType = GL_RGBA;
		// 	break;
		// case ImageType::PPM:
		// 	m_ImageType = GL_RGB;
		// 	break;
		// default:
		// 	DG_FATAL("Unknown Image Type");
		// }
		switch (textureType)
		{
		case TextureType::oneD:
			m_TextureType = GL_TEXTURE_1D;
			break;
		case TextureType::twoD:
			m_TextureType = GL_TEXTURE_2D;
			break;
		case TextureType::threeD:
			m_TextureType = GL_TEXTURE_3D;
			break;
		default:
			DG_FATAL("Unknown Texture Type");
		}
		glCreateTextures(m_TextureType, 1, &m_RendererID);
		glBindTexture(m_TextureType, m_RendererID);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (data)
		{
			glTexImage2D(m_TextureType, 0, GL_RGB, width, height, 0, m_ImageType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(m_TextureType);
		}
		else
		{
			DG_WARN("Failed to load texture: %s", stbi_failure_reason());
		}
		stbi_image_free(data);
	}
	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture::Bind(uint32_t textureUnit, const std::string& name = "") const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(m_TextureType, m_RendererID);
	}
	void OpenGLTexture::Unbind(uint32_t textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(m_TextureType, NULL);
	}
	void OpenGLTexture::UpdateTexture(const std::string& filepath, const std::string& imageType, TextureType textureType)
	{
		/*switch (imageType)
		{
		case ImageType::JPG:
			m_ImageType = GL_RGB;
			break;
		case ImageType::JPEG:
			m_ImageType = GL_RGB;
			break;
		case ImageType::PNG:
			m_ImageType = GL_RGBA;
			break;
		case ImageType::PPM:
			m_ImageType = GL_RGB;
			break;
		default:
			DG_FATAL("Unknown Image Type");
		}*/
		switch (textureType)
		{
		case TextureType::oneD:
			m_TextureType = GL_TEXTURE_1D;
			break;
		case TextureType::twoD:
			m_TextureType = GL_TEXTURE_2D;
			break;
		case TextureType::threeD:
			m_TextureType = GL_TEXTURE_3D;
			break;
		default:
			DG_FATAL("Unknown Texture Type");
		}
		glCreateTextures(m_TextureType, 1, &m_RendererID);
		glBindTexture(m_TextureType, m_RendererID);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(m_TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(m_TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(m_TextureType, 0, GL_RGB, width, height, 0, m_ImageType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(m_TextureType);
		}
		else
		{
			DG_WARN("Failed to load texture: %s", stbi_failure_reason());
		}
		stbi_image_free(data);
		stbi_set_flip_vertically_on_load(true);
	}
}
