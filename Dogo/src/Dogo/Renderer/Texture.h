#pragma once

namespace Dogo
{
	enum class ImageType
	{
		TYPE_NONE, JPEG, JPG, PNG, PPM
	};
	enum class TextureType
	{
		TYPE_NONE, oneD, twoD, threeD
	};
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void Bind(uint32_t textureUnit, const std::string& name = "") const = 0;
		virtual void Unbind(uint32_t textureUnit) const = 0;

		virtual void UpdateTexture(const std::string& filepath, const std::string& imageType, TextureType textureType) = 0;

		virtual std::string GetName() const = 0;
		virtual std::string GetType() const = 0;
		virtual void SetName(const std::string& name) = 0;
		virtual void SetType(const std::string& type) = 0;
		virtual std::string GetFilePath() const = 0;

		static Texture* Create(const std::string& filepath, const std::string& imageType, TextureType textureType, const std::string& name);
	};
}