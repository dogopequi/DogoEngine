#pragma once
#if DG_PLATFORM_WINDOWS
#include "Platform/DX11/DX11Context.h"
#include "Dogo/Renderer/Buffers.h"
namespace Dogo
{
	using namespace DirectX;
	using namespace PackedVector;
	using Microsoft::WRL::ComPtr;
	class DX11IndexBuffer : public IndexBuffer
	{
	public:
		DX11IndexBuffer(uint32_t size, uint32_t* data, uint32_t count);
		~DX11IndexBuffer();

		void Bind() override;
		void Unbind() override;
		inline uint32_t getSize() const override { return m_Size; }
		inline uint32_t getComponentCount() const override { return m_ComponentCount; }

	private:
		uint32_t m_ComponentCount{};
		uint32_t m_Size{};
		ComPtr<ID3D11Buffer> m_IBO;
	};
}

#endif