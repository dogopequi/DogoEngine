#include "dgpch.h"
#include "Dogo/Logger.h"
#include "TextureManager.h"
namespace Dogo
{
	std::vector<std::shared_ptr<Texture>> TextureManager::s_Textures;
   
	void TextureManager::Add(std::shared_ptr<Texture> texture)
	{
		s_Textures.push_back(texture);
	}

	std::vector<std::shared_ptr<Texture>> TextureManager::GetTextures()
	{
		return s_Textures;
	}

	std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& name)
	{
		for (const std::shared_ptr<Texture>& texture : s_Textures)
		{
			if (texture->GetName() == name)
				return texture;
		}
		return nullptr;
	}

	void TextureManager::Clean()
	{
		s_Textures.clear();
	}
}
