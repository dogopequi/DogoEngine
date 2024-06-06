#pragma once
#include "DX11VertexBuffer.h"
#include "DX11IndexBuffer.h"
namespace Dogo
{
	class DX11ArrayBuffer : public VertexArray
	{
	public:
		DX11ArrayBuffer();
		~DX11ArrayBuffer();

		void Bind();
		void Unbind();

		void AddBuffer(std::shared_ptr<VertexBuffer>& buffer);
		void Draw(uint32_t count);

	private:
		std::vector<std::shared_ptr<DX11VertexBuffer>> m_VertexBuffers;
	};
}

