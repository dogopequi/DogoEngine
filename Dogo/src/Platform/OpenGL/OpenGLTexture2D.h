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

	class OpenGLTexture2D: public Texture
	{
		public:
			OpenGLTexture2D(const std::string& filepath);
			~OpenGLTexture2D();

			void Bind(uint32_t slot) const override;

			void UpdateTexture(const std::string& filepath) override;

			inline uint32_t GetRendererID() const override { return m_RendererID; }
			inline std::string GetFilePath() const override { return m_FilePath; }

		protected:
			void Init(const std::string& filepath) override;
		private:
			uint32_t m_RendererID{};
			std::string m_FilePath;
	};
}

