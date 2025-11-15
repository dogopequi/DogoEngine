#pragma once
#include "OpenGLIndexBuffer.h"
#include "OpenGLBuffer.h"
#include "Dogo/Renderer/Core/Buffers.h"
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
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
		void DrawArrays();

	private:
		GLuint m_RendererID{0};
		std::vector<std::shared_ptr<OpenGLBuffer>> m_VertexBuffers;
	};
}

