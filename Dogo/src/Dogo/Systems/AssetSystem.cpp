#include "dgpch.h"
#include "AssetSystem.h"
#include "stb/stb_image.h"
namespace Dogo
{
	namespace AssetSystem
	{
		std::optional<TextureAsset> LoadTexture(std::string_view filepath)
		{
			TextureAsset asset;
			bool success = asset.LoadTextureFromDisk(filepath);
			if (success)
				return asset;
			else
				return {};
		}
	}
}