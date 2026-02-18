#include "dgpch.h"
#include "Sprite.h"
#include "Dogo/Systems/AssetSystem.h"
namespace Dogo
{
	void Sprite::ChangeTexture(std::string_view filepath)
	{
		std::optional<TextureAsset> asset = AssetSystem::LoadTexture(filepath);
		if (asset.has_value() && asset.value().IsValid())
			m_Texture = std::make_unique<Texture2D>(filepath);
		else
			m_Texture = {};
	}
	void Sprite::ChangePivotPoint(float x, float y)
	{
		m_PivotX = x;
		m_PivotY = y;
	}
	void Sprite::SetDimensions(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}
	Sprite::Sprite() : m_Name(""), m_Pivot(Pivot::BottomLeft), m_Color(glm::vec4(1.0f)), m_Width(0), m_Height(0), m_PivotX(0), m_PivotY(0), m_Texture()
	{
	}
	Sprite::Sprite(const std::string& name, float width, float height, std::string_view filepath, Pivot pivot, const glm::vec4& color, const UV& uv)
		: m_Name(name), m_Pivot(pivot), m_Color(color), m_UV(uv), m_Width(width), m_Height(height)
	{
		std::optional<TextureAsset> asset = AssetSystem::LoadTexture(filepath);
		if (asset.has_value() && asset.value().IsValid())
			m_Texture = std::make_unique<Texture2D>(filepath);
		else
			m_Texture = {};
		switch (pivot)
		{
			case Pivot::Center:
			{
				m_PivotX = m_Width / 2;
				m_PivotY = m_Height / 2;
				break;
			}
			case Pivot::BottomLeft:
			{
				m_PivotX = 0;
				m_PivotY = 0;
				break;
			}
			case Pivot::BottomRight:
			{
				m_PivotX = m_Width;
				m_PivotY = 0;
				break;
			}
			case Pivot::TopRight:
			{
				m_PivotX = m_Width;
				m_PivotY = m_Height;
				break;
			}
			case Pivot::TopLeft:
			{
				m_PivotX = 0;
				m_PivotY = m_Height;
				break;
			}
			default:
			{
				m_PivotX = 0;
				m_PivotY = 0;
				break;
			}
		}
	}
}
