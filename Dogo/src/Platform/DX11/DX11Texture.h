#pragma once
#if DG_PLATFORM_WINDOWS
#include "Dogo/Core.h"

#include "Platform/DX11/DX11Context.h"
#include "Dogo/Renderer/Texture.h"
namespace Dogo
{
	 
	 
	using Microsoft::WRL::ComPtr;
	class DX11Texture : public Texture
	{
	public:
		DX11Texture(const std::string& filepath, const std::string& imageType, TextureType textureType, const std::string& name);
		~DX11Texture();

		void Bind(uint32_t textureUnit, const std::string& name) const override;
		void Unbind(uint32_t textureUnit) const override;

		void UpdateTexture(const std::string& filepath, const std::string& imageType, TextureType textureType) override;
		std::string GetName() const { return m_Name; }
		std::string GetType() const { return m_Type; }

		void SetName(const std::string& name) { m_Name = name; }
		void SetType(const std::string& type) { m_Type = type; }

		inline std::string GetFilePath() const { return m_FilePath; }
	private:
		std::string m_Name;
		std::string m_Type;
		std::string m_FilePath;
		uint32_t m_RendererID{};
		DXGI_FORMAT m_ImageType{ DXGI_FORMAT_R8G8B8A8_UNORM };
		D3D11_SRV_DIMENSION m_TextureType{};
		ComPtr<ID3D11SamplerState> m_SamplerState;
		ComPtr<ID3D11Texture2D> m_Texture;
		ComPtr<ID3D11ShaderResourceView> m_TextureView;
	};
}
#endif

