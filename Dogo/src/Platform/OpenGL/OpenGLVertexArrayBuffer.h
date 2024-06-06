#pragma once
#include <glad/glad.h>
#include "OpenGLIndexBuffer.h"
#include "OpenGLBuffer.h"
#include "Dogo/Renderer/Buffers.h"
namespace Dogo
{
	class OpenGLVertexArrayBuffer : public VertexArray
	{
	public:
		OpenGLVertexArrayBuffer();
		~OpenGLVertexArrayBuffer();

		void Bind();
		void Unbind();

		void AddBuffer(std::shared_ptr<VertexBuffer>& buffer);
		void Draw(uint32_t count);

	private:
		GLuint m_RendererID{};
		std::vector<std::shared_ptr<OpenGLBuffer>> m_VertexBuffers;
	};
}

