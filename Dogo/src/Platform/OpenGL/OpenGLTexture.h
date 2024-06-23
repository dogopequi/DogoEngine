#pragma once
#include "Dogo/Core.h"
#include "Dogo/Renderer/Texture.h"
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo
{
	class OpenGLTexture: public Texture
	{
		public:
			OpenGLTexture(const std::string& filepath, ImageType imageType, TextureType textureType, const std::string& name);
			~OpenGLTexture();

			void Bind(uint32_t textureUnit, const std::string& name) const override;
			void Unbind(uint32_t textureUnit) const override;

			void UpdateTexture(const std::string& filepath, ImageType imageType, TextureType textureType) override;

			std::string GetName() const { return m_Name; }

	private:
		std::string m_Name;
		uint32_t m_RendererID{};
		GLenum m_ImageType{};
		GLenum m_TextureType{};
	};
}

