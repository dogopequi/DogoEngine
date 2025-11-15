#pragma once
#include "Dogo/Renderer/Core/TextureManager.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
namespace Dogo
{
	enum class Pivot {
		Center, TopRight, TopLeft, BottomLeft, BottomRight, Custom
	};
	struct Sprite
	{
	public:

		Sprite();

		Sprite(Sprite&&) = default;
		Sprite& operator=(Sprite&&) = default;

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		Sprite(const std::string& name, const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, float width, float height, Pivot pivot, const glm::vec4& color = glm::vec4(1.0f), bool mipmaps = true);
		Sprite(const std::string& name, const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, float width, float height, const glm::vec4& color = glm::vec4(1.0f), bool mipmaps = true);
		~Sprite() = default;

		bool ChangeTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmaps);
		bool GenerateMipMaps();
		bool ChangeFiltering(FilterMode filter);
		bool ChangeWrapping(Wrapping wrap);
		bool ChangeTextureType(TextureType type);
		void ChangePivotPoint(float x, float y);
		void SetDimensions(float width, float height);

		inline Texture* GetTexture() const { return m_Tex.get(); }
		inline std::string_view GetName() const{ return m_Name; }
		inline void SetName(const std::string& name) { m_Name = name; }
		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }
		inline float GetPivotX() const { return m_PivotX; }
		inline float GetPivotY() const { return m_PivotY; }
		inline bool IsMipMap() const { return m_GenerateMipMaps; }
		inline FilterMode GetFilterMode() const {
			if (m_Tex == nullptr)
				throw 1;
			return m_Tex->GetFilterMode();
		}
		inline Wrapping GetWrapping() const {
			if (m_Tex == nullptr)
				throw 1;
			return m_Tex->GetWrapping();
		}
		inline TextureType GetTextureType() const {
			if (m_Tex == nullptr)
				throw 1;
			return m_Tex->GetTextureType();
		}



	private:
		void Init(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmaps);

		std::string m_Name;
		glm::vec4 m_Color;
		std::unique_ptr<Texture> m_Tex;
		Pivot m_Pivot;
		float m_Width, m_Height;
		float m_PivotX, m_PivotY;
		bool m_GenerateMipMaps;
	};
}

