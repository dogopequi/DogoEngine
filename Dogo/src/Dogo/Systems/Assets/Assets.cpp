#include "dgpch.h"
#include "Assets.h"
#include "stb/stb_image.h"
namespace Dogo
{
	Asset::Asset() : m_ID(UUID())
	{

	}
	TextureAsset::TextureAsset() : Asset()
	{
	}
	bool TextureAsset::LoadTextureFromDisk(std::string_view path)
	{
		std::filesystem::path fs{ path };
		if (std::filesystem::exists(fs) && std::filesystem::is_regular_file(fs))
		{
			m_Path = path;
			int width, height, channels;
			unsigned char* data = stbi_load(fs.string().c_str(), &width, &height, &channels, 0);

			if (data)
			{
				m_Width = width;
				m_Height = height;
				stbi_image_free(data);
				return true;
			}
			else
			{
				stbi_image_free(data);
				return false;
			}
		}
		return false;
	}
}