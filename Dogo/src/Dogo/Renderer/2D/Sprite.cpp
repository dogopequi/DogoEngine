#include "dgpch.h"
#include "Sprite.h"
namespace Dogo
{
	void Sprite::ChangeTexture(std::string_view filepath)
	{
		m_Texture = AssetSystem::LoadTexture(filepath);
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
	Sprite::Sprite(const std::string& name, std::string_view filepath, float width, float height, Pivot pivot, const glm::vec4& color, const UV& uv)
		: m_Name(name), m_Pivot(pivot), m_Color(color), m_UV(uv), m_Width(width), m_Height(height)
	{
		m_Texture = AssetSystem::LoadTexture(filepath);
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
