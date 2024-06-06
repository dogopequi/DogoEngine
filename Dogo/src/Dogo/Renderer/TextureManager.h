#pragma once
#include "Texture.h"
namespace Dogo
{
	class TextureManager
	{
	public:
		static void Add(std::shared_ptr<Texture> texture);
		static std::vector<std::shared_ptr<Texture>> GetTextures();
		static std::shared_ptr<Texture> GetTexture(const std::string& name);
		static void Clean();
	private:
		TextureManager() { }

	private:
		static std::vector<std::shared_ptr<Texture>> s_Textures;
	};
}