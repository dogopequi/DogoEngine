#include "dgpch.h"
#include "Sprite.h"
namespace Dogo
{
	bool Sprite::ChangeTexture(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmaps)
	{
		if (m_Tex == nullptr)
			return false;
		m_Tex->UpdateTexture(filepath, textureType, filter, wrap, mipmaps);
	}
	bool Sprite::GenerateMipMaps()
	{
		if (m_Tex == nullptr)
			return false;
		m_Tex->UpdateTexture(m_Tex->GetFilePath(), m_Tex->GetTextureType(), m_Tex->GetFilterMode(), m_Tex->GetWrapping(), true);
	}
	bool Sprite::ChangeFiltering(FilterMode filter)
	{
		if (m_Tex == nullptr)
			return false;
		m_Tex->UpdateTexture(m_Tex->GetFilePath(), m_Tex->GetTextureType(), filter, m_Tex->GetWrapping(), m_Tex->IsMipMap());
	}
	bool Sprite::ChangeWrapping(Wrapping wrap)
	{
		if (m_Tex == nullptr)
			return false;
		m_Tex->UpdateTexture(m_Tex->GetFilePath(), m_Tex->GetTextureType(), m_Tex->GetFilterMode(), wrap, m_Tex->IsMipMap());
	}
	bool Sprite::ChangeTextureType(TextureType type)
	{
		if (m_Tex == nullptr)
			return false;
		m_Tex->UpdateTexture(m_Tex->GetFilePath(), type, m_Tex->GetFilterMode(), m_Tex->GetWrapping(), m_Tex->IsMipMap());
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
	void Sprite::Init(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmaps)
	{
		m_Tex.reset(TextureManager::Create(filepath, textureType, filter, wrap, mipmaps));
	}
	Sprite::Sprite() : m_Name(""), m_Pivot(Pivot::BottomLeft), m_GenerateMipMaps(false), m_Color(glm::vec4(1.0f)), m_Width(0), m_Height(0), m_PivotX(0), m_PivotY(0)
	{
	}
	Sprite::Sprite(const std::string& name, const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, float width, float height, Pivot pivot, const glm::vec4& color, bool mipmaps)
		: m_Name(name), m_Pivot(pivot), m_GenerateMipMaps(true), m_Color(color)
	{
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
		Init(filepath, textureType, filter, wrap, mipmaps);
	}
	Sprite::Sprite(const std::string& name, const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, float width, float height, const glm::vec4& color, bool mipmaps)
		: m_Name(name), m_Width(width), m_Height(height), m_Pivot(Pivot::BottomLeft), m_GenerateMipMaps(true), m_Color(color)
	{
		m_PivotX = 0;
		m_PivotY = 0;
		Init(filepath, textureType, filter, wrap, mipmaps);
	}
}
