#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11VertexBuffer.h"
#include "Graphics/WindowsWindow.h"
namespace Dogo
{
	DX11VertexBuffer::DX11VertexBuffer(uint32_t bufferSize, uint32_t componentSize, float* data)
		: m_Size(componentSize), m_Offset(NULL)
	{
		D3D11_BUFFER_DESC vDesc;
		vDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vDesc.Usage = D3D11_USAGE_DEFAULT;
		vDesc.CPUAccessFlags = 0;
		vDesc.MiscFlags = 0;
		vDesc.ByteWidth = bufferSize;
		vDesc.StructureByteStride = componentSize;
		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = data;
		DX11Context::GetContext()->GetDevice().Get()->CreateBuffer(&vDesc, &sd, m_VBO.GetAddressOf());
		DX11Context::GetContext()->GetDeviceContext().Get()->IASetVertexBuffers(0, 1, m_VBO.GetAddressOf(), &componentSize, &m_Offset);
	}
	DX11VertexBuffer::~DX11VertexBuffer()
	{
		m_VBO.Reset();
	}
	void DX11VertexBuffer::SetLayout(const BufferLayout& layout, const void* signature, SIZE_T length)
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> ied;
		for (const auto& element : layout)
		{

			D3D11_INPUT_ELEMENT_DESC desc;
			desc.SemanticName = element.Name.c_str();
			desc.SemanticIndex = 0;
			desc.Format = ShaderDataTypeToDX11(element.Type);
			desc.InputSlot = 0;
			desc.AlignedByteOffset = element.Offset;
			desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;

			ied.push_back(desc);
		}
		DX11Context::GetContext()->GetDevice().Get()->CreateInputLayout(
			ied.data(), ied.size(),
			signature,
			length,
			m_InputLayout.GetAddressOf()
		);
		m_Layout = layout;
	}
	void DX11VertexBuffer::Bind()
	{
		DX11Context::GetContext()->GetDeviceContext()->IASetInputLayout(m_InputLayout.Get());
		DX11Context::GetContext()->GetDeviceContext().Get()->IASetVertexBuffers(0, 1, m_VBO.GetAddressOf(), &m_Size, &m_Offset);
	}
	void DX11VertexBuffer::Unbind()
	{
		ID3D11InputLayout* nullIS[1] = { nullptr };
		ID3D11Buffer* nullBuffer[1] = { nullptr };
		DX11Context::GetContext()->GetDeviceContext()->IASetInputLayout(*nullIS);
		DX11Context::GetContext()->GetDeviceContext().Get()->IASetVertexBuffers(0, 1, nullBuffer, &m_Size, &m_Offset);
	}
}
#endif
