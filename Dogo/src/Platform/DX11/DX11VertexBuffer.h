#pragma once
#include "Dogo/Renderer/Buffers.h"
#include "Platform/DX11/DX11Context.h"
#include "Dogo/Renderer/Buffers.h"
namespace Dogo
{
	using namespace DirectX;
	using namespace PackedVector;
	using Microsoft::WRL::ComPtr;
	class DX11VertexBuffer : public VertexBuffer
	{
	public:
		DX11VertexBuffer(uint32_t bufferSize, uint32_t componentSize, float* data);
		~DX11VertexBuffer();

		void SetLayout(const BufferLayout& layout, const void* signature, SIZE_T length);
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout;}
		inline const BufferLayout& GetLayout() const override { return m_Layout; }
		void Bind() override;
		void Unbind() override;

	private:
		ComPtr<ID3D11Buffer> m_VBO;
		ComPtr<ID3D11InputLayout> m_InputLayout;
		uint32_t m_Size;
		uint32_t m_Offset;
		BufferLayout m_Layout{};
	};
}

