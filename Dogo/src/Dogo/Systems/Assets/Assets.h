#pragma once
#include "Dogo/Utils/UUID.h"
namespace Dogo
{
	class Asset
	{
	public:
		Asset();

		std::filesystem::path GetPath() const { return m_Path; }
		UUID GetUUID() const { return m_ID; }

	protected:
		std::filesystem::path m_Path{};
	private:
		UUID m_ID;
	};

	class TextureAsset : public Asset
	{
	public:
		TextureAsset();
		bool LoadTextureFromDisk(std::string_view path);
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
	private:
		uint32_t m_Width{ 0 };
		uint32_t m_Height{ 0 };
	};
}