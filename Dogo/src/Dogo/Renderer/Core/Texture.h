#pragma once
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo
{
	enum class FilterMode
	{
		NEAREST, BILINEAR, TRILINEAR
	};
	enum class Wrapping
	{
		REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
	};
	enum class TextureType
	{
		SPECULAR, DIFFUSE, NORMAL, HEIGHT
	};
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind(uint32_t slot) const = 0;

		virtual void UpdateTexture(std::string_view filepath) = 0;
		virtual uint32_t GetRendererID() const = 0;


		static GLenum WrapToOpenGL(Wrapping wrap)
		{
			switch (wrap)
			{
			case Wrapping::REPEAT:
				return GL_REPEAT;
			case Wrapping::MIRRORED_REPEAT:
				return GL_MIRRORED_REPEAT;
			case Wrapping::CLAMP_TO_EDGE:
				return GL_CLAMP_TO_EDGE;
			case Wrapping::CLAMP_TO_BORDER:
				return GL_CLAMP_TO_BORDER;
			default:
				return GL_REPEAT;
			}
		}
		static GLenum FilterToOpenGL(FilterMode filter)
		{
			switch (filter)
			{
			case FilterMode::BILINEAR:
				return GL_LINEAR;
			case FilterMode::NEAREST:
				return GL_NEAREST;
			case FilterMode::TRILINEAR:
				return GL_LINEAR_MIPMAP_LINEAR;
			default:
				return GL_LINEAR;
			}
		}

		static Texture* Create(std::string_view filepath);
	};
}