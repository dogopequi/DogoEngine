#pragma once
#include "Dogo/Renderer/Core/Texture.h"
namespace Dogo
{
	class TextureManager
	{
	public:
		static void Add(std::shared_ptr<Texture> texture);
		static std::vector<std::shared_ptr<Texture>> GetTextures();
		static std::shared_ptr<Texture> GetTexture(uint32_t id);
		static void Clean();
		static Texture* Create(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap);
	private:
		TextureManager() { }

	private:
		static std::vector<std::shared_ptr<Texture>> s_Textures;
		static uint32_t s_TexCount;
	};
}