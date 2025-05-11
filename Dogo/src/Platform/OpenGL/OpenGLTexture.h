#pragma once
#include "Dogo/Core.h"
#include "Dogo/Renderer/Texture.h"
#include "glm/glm.hpp"
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
			OpenGLTexture(const std::string& filepath, const std::string& imageType, TextureType textureType, const std::string& name);
			~OpenGLTexture();

			void Bind(uint32_t textureUnit, const std::string& name) const override;
			void Unbind(uint32_t textureUnit) const override;

			void UpdateTexture(const std::string& filepath, const std::string& imageType, TextureType textureType) override;

			inline std::string GetName() const { return m_Name; }
			inline void SetName(const std::string& name) { m_Name = name; }
			inline std::string GetType() const { return m_Type; }
			inline void SetType(const std::string& type) { m_Type = type; }

			inline std::string GetFilePath() const { return m_FilePath; }

	private:
		std::string m_Name;
		std::string m_Type;
		std::string m_FilePath;
		uint32_t m_RendererID{};
		GLenum m_ImageType{};
		GLenum m_TextureType{};
	};
}

