#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11IndexBuffer.h"
#include "DX11Context.h"
#include "Graphics/WindowsWindow.h"

namespace Dogo
{
	DX11IndexBuffer::DX11IndexBuffer(uint32_t size, uint32_t* data, uint32_t count)
		: m_Size(size), m_ComponentCount(count)
	{
		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = size;
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;
		ibd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA iinitData;
		iinitData.pSysMem = data;

		DX11Context::GetContext()->GetDevice().Get()->CreateBuffer(&ibd, &iinitData, m_IBO.GetAddressOf());
	}
	DX11IndexBuffer::~DX11IndexBuffer()
	{
		m_IBO.Reset();
	}
	void DX11IndexBuffer::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext()->IASetIndexBuffer(m_IBO.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	void DX11IndexBuffer::Unbind()
	{
		ID3D11Buffer* nullBuffer[1] = { nullptr };
		DX11Context::GetContext()->GetDeviceContext()->IASetIndexBuffer(*nullBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
}
#endif