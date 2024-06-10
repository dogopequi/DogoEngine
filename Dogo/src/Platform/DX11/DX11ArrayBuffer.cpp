#include "dgpch.h"
#if DG_PLATFORM_WINDOWS
#include "DX11ArrayBuffer.h"

namespace Dogo
{
	DX11ArrayBuffer::DX11ArrayBuffer()
	{
	}
	DX11ArrayBuffer::~DX11ArrayBuffer()
	{
	}
	void DX11ArrayBuffer::Bind()
	{
	}
	void DX11ArrayBuffer::Unbind()
	{
	}
	void DX11ArrayBuffer::AddBuffer(std::shared_ptr<VertexBuffer>& buffer)
	{
		auto dx11buffer = std::dynamic_pointer_cast<DX11VertexBuffer>(buffer);
		m_VertexBuffers.push_back(dx11buffer);
	}
	void DX11ArrayBuffer::Draw(uint32_t count)
	{
		for (size_t i = 0; i < m_VertexBuffers.size(); i++)
		{
			std::shared_ptr<DX11VertexBuffer> buffer = (std::shared_ptr<DX11VertexBuffer>)m_VertexBuffers[i];
			buffer->Bind();

			DX11Context::GetContext()->GetDeviceContext()->DrawIndexed(count, 0, 0);

			buffer->Unbind();
		}
	}
}
#endif