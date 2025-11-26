#pragma once
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Renderer/Core/Texture.h"
namespace Dogo
{
	enum class Pivot {
		Center, TopRight, TopLeft, BottomLeft, BottomRight, Custom
	};
	struct Sprite
	{
	public:

		Sprite();
		Sprite(Sprite&&) noexcept = default;
		Sprite& operator=(Sprite&&) noexcept = default;

		Sprite(const Sprite&) = default;
		Sprite& operator=(const Sprite&) = default;

		Sprite(const std::string& name, std::string_view filepath, float width, float height, Pivot pivot = Pivot::BottomLeft, const glm::vec4& color = glm::vec4(1.0f), const UV& uv = UV());
		~Sprite() = default;

		void ChangeTexture(std::string_view filepath);
		void ChangePivotPoint(float x, float y);
		void SetDimensions(float width, float height);

		inline std::optional<TextureAsset> GetTexture() const { return m_Texture; }
		inline std::string_view GetName() const{ return m_Name; }
		inline void SetName(const std::string& name) { m_Name = name; }
		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }
		inline float GetPivotX() const { return m_PivotX; }
		inline float GetPivotY() const { return m_PivotY; }
		inline UV GetUV() const { return m_UV; }
		inline void SetUV(const UV& uv){ m_UV = uv; }

	private:

		std::string m_Name;
		glm::vec4 m_Color;
		std::optional<TextureAsset> m_Texture;
		Pivot m_Pivot;
		float m_Width, m_Height;
		float m_PivotX, m_PivotY;
		bool m_GenerateMipMaps;
		UV m_UV;
	};
}

