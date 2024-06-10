#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11Texture.h"
#include "Dogo/Logger.h"
#include "Graphics/WindowsWindow.h"
#include "stb/stb_image.h"
namespace Dogo
{
	DX11Texture::DX11Texture(const std::string& filepath, TextureType textureType, const std::string& name) : m_Name(name)
	{

		switch (textureType)
		{
		case TextureType::oneD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE1D;
			break;
		case TextureType::twoD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE2D;
			break;
		case TextureType::threeD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE3D;
			break;
		default:
			DG_FATAL("Unknown Texture Type");
		}

		//stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			DG_INFO("read successfully");
		}

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = m_ImageType;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data;
		initData.SysMemPitch = width * channels;

		HRESULT hr;
		hr = DX11Context::GetContext()->GetDevice().Get()->CreateTexture2D(&textureDesc, &initData, m_Texture.GetAddressOf());
		if (FAILED(hr))
		{
			DG_WARN("Failed to create texture");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = m_ImageType;
		srvDesc.ViewDimension = m_TextureType;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		stbi_image_free(data);
		hr = DX11Context::GetContext()->GetDevice().Get()->CreateShaderResourceView(m_Texture.Get(), &srvDesc, m_TextureView.GetAddressOf());
		if (FAILED(hr))
		{
			DG_WARN("Failed to create shader resource view");
		}


		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = DX11Context::GetContext()->GetDevice().Get()->CreateSamplerState(&sampDesc, m_SamplerState.GetAddressOf());
		if (FAILED(hr)) 
		{
			DG_WARN("Failed to create sampler state");
		}
	}
	DX11Texture::~DX11Texture()
	{
		m_TextureView.Reset();
		m_SamplerState.Reset();
		m_Texture.Reset();
	}
	void DX11Texture::Bind(uint32_t textureUnit, const std::string& name) const
	{
		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetShaderResources(0 + textureUnit, 1, m_TextureView.GetAddressOf());
		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetSamplers(0 + textureUnit, 1, m_SamplerState.GetAddressOf());
	}
	void DX11Texture::Unbind(uint32_t textureUnit) const
	{

		ID3D11SamplerState* nullST[1] = { nullptr };
		ID3D11ShaderResourceView* nullSRV[1] = { nullptr };

		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetShaderResources(0 + textureUnit, 1, nullSRV);
		DX11Context::GetContext()->GetDeviceContext().Get()->PSSetSamplers(0 + textureUnit, 1, nullST);
	}
	void DX11Texture::UpdateTexture(const std::string& filepath, ImageType imageType, TextureType textureType)
	{

		switch (textureType)
		{
		case TextureType::oneD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE1D;
			break;
		case TextureType::twoD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE2D;
			break;
		case TextureType::threeD:
			m_TextureType = D3D11_SRV_DIMENSION_TEXTURE3D;
			break;
		default:
			DG_FATAL("Unknown Texture Type");
		}

		//stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (data)
		{
			DG_INFO("read successfully");
		}

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = m_ImageType;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = data;
		initData.SysMemPitch = width * channels;

		HRESULT hr;
		hr = DX11Context::GetContext()->GetDevice().Get()->CreateTexture2D(&textureDesc, &initData, m_Texture.GetAddressOf());
		if (FAILED(hr))
		{
			DG_WARN("Failed to create texture");
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = m_ImageType;
		srvDesc.ViewDimension = m_TextureType;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;
		stbi_image_free(data);
		hr = DX11Context::GetContext()->GetDevice().Get()->CreateShaderResourceView(m_Texture.Get(), &srvDesc, m_TextureView.GetAddressOf());
		if (FAILED(hr))
		{
			DG_WARN("Failed to create shader resource view");
		}


		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = DX11Context::GetContext()->GetDevice().Get()->CreateSamplerState(&sampDesc, m_SamplerState.GetAddressOf());
		if (FAILED(hr))
		{
			DG_WARN("Failed to create sampler state");
		}
	}
}
#endif