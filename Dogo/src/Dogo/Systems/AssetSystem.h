#pragma once
#include "Assets/Assets.h"
namespace Dogo
{
	namespace AssetSystem
	{
		std::optional<TextureAsset> LoadTexture(std::string_view filepath);
	}
}