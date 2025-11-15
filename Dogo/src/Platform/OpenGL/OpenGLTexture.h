#pragma once
#include "Dogo/Core.h"
#include "Dogo/Renderer/Core/Texture.h"
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
			OpenGLTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap);
			~OpenGLTexture();

			void Bind(uint32_t textureUnit) const override;
			void Unbind(uint32_t textureUnit) const override;

			void UpdateTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap) override;

			inline uint32_t GetRendererID() const override { return m_RendererID; }
			inline std::string GetFilePath() const override { return m_FilePath; }
			inline FilterMode GetFilterMode() const override { return m_Filter; }
			inline Wrapping GetWrapping() const override { return m_Wrap; }
			inline TextureType GetTextureType() const override { return m_TexType; }
			inline bool IsMipMap() const override { return m_IsMipMap; }
			inline uint32_t GetID() const override { return m_ID; }

		protected:
			inline void SetID(uint32_t id) override { m_ID = id; }
			void Init(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap) override;
		private:
			uint32_t m_RendererID{};
			uint32_t m_ID{};
			TextureType m_TexType;
			FilterMode m_Filter;
			Wrapping m_Wrap;
			std::string m_FilePath;
			GLenum m_GLImageType{};
			GLenum m_GLTextureType{};
			bool m_IsMipMap;
	};
}

