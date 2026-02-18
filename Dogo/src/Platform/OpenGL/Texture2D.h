#pragma once
#include "Dogo/Core.h"
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

	class Texture2D
	{
		public:
			Texture2D(std::string_view filepath);
			~Texture2D();

			void Bind(uint32_t slot) const;

			void UpdateTexture(std::string_view filepath) ;

			inline uint32_t GetRendererID() const { return m_RendererID; }

		protected:
			void Init(std::string_view filepath);
		private:
			uint32_t m_RendererID{};
	};
}

