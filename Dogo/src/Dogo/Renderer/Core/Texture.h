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
	enum class TextureType
	{
		T_1D, T_2D, T_3D
	};
	enum class FilterMode
	{
		NEAREST, BILINEAR, TRILINEAR
	};
	enum class Wrapping
	{
		REPEAT, MIRRORED_REPEAT, CLAMP_TO_EDGE, CLAMP_TO_BORDER
	};
	class Texture
	{
	public:
		friend class TextureManager;
		virtual ~Texture() = default;
		virtual void Bind(uint32_t textureUnit) const = 0;
		virtual void Unbind(uint32_t textureUnit) const = 0;

		virtual void UpdateTexture(const std::string& filepath,  TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap) = 0;
		virtual uint32_t GetRendererID() const = 0;
		virtual uint32_t GetID() const = 0;
		virtual void SetID(uint32_t id) = 0;
		virtual std::string GetFilePath() const = 0;
		virtual FilterMode GetFilterMode() const = 0;
		virtual Wrapping GetWrapping() const = 0;
		virtual TextureType GetTextureType() const = 0;
		virtual bool IsMipMap() const = 0;


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
		static GLenum TexD_ToOpenGL(TextureType d)
		{
			switch (d)
			{
			case TextureType::T_1D:
				return GL_TEXTURE_1D;
			case TextureType::T_2D:
				return GL_TEXTURE_2D;
			case TextureType::T_3D:
				return GL_TEXTURE_3D;
			default:
				return GL_TEXTURE_2D;
			}
		}

	protected:
		static Texture* Create(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap,  bool mipmap);
		virtual void Init(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap) = 0;
	};
}