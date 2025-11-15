#pragma once
#include "Dogo/Renderer/Core/Buffers.h"
namespace Dogo
{
	class OpenGLBuffer : public VertexBuffer
	{
	public:
		OpenGLBuffer(uint32_t size, float* data);
		~OpenGLBuffer();

		void Bind() override;
		void Unbind() override;
		inline uint32_t getSize() const{ return m_Size; }


		inline const BufferLayout& GetLayout() const override { return m_Layout; }
		inline void SetLayout(const BufferLayout& layout)  override { m_Layout = layout; }

	private:
		BufferLayout m_Layout{};
		GLuint m_RendererID{};
		uint32_t m_Size{};
	};
}

