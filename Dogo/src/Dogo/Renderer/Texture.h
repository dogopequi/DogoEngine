#pragma once

namespace Dogo
{
	enum class ImageType
	{
		None = 0, JPEG, JPG, PNG, PPM
	};
	enum class TextureType
	{
		None = 0, oneD, twoD, threeD
	};
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind(uint32_t textureUnit, const std::string& name) const = 0;
		virtual void Unbind(uint32_t textureUnit) const = 0;

		virtual void UpdateTexture(const std::string& filepath, ImageType imageType, TextureType textureType) = 0;

		virtual std::string GetName() const = 0;

		static Texture* Create(const std::string& filepath, ImageType imageType, TextureType textureType, const std::string& name);
	};
}