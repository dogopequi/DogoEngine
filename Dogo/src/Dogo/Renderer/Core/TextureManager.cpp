#include "dgpch.h"
#include "Dogo/Utils/Logger.h"
#include "TextureManager.h"
namespace Dogo
{
	std::vector<std::shared_ptr<Texture>> TextureManager::s_Textures;
	uint32_t TextureManager::s_TexCount = 0;
   
	void TextureManager::Add(std::shared_ptr<Texture> texture)
	{
		s_Textures.push_back(texture);
	}

	std::vector<std::shared_ptr<Texture>> TextureManager::GetTextures()
	{
		return s_Textures;
	}

	Texture* TextureManager::Create(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap)
	{
		Texture* tex = Texture::Create(filepath, textureType, filter, wrap, mipmap);
		tex->SetID(++TextureManager::s_TexCount);
		return tex;
	}

	std::shared_ptr<Texture> TextureManager::GetTexture(uint32_t id)
	{
		for (const std::shared_ptr<Texture>& texture : s_Textures)
		{
			if (texture->GetID() == id)
				return texture;
		}
		return nullptr;
	}

	void TextureManager::Clean()
	{
		s_Textures.clear();
	}
}
