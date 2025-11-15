#pragma once
#include "Dogo/Renderer/Core/Buffers.h"

namespace Dogo
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t size, uint32_t* data, uint32_t count);
		~OpenGLIndexBuffer();

		void Bind() override;
		void Unbind() override;
		inline uint32_t getSize() const override { return m_Size; }
		inline uint32_t getComponentCount() const override { return m_ComponentCount; }

	private:
		GLuint m_RendererID{};
		uint32_t m_ComponentCount{};
		uint32_t m_Size{};
	};
}
