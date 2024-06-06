#include "dgpch.h"
#include "OpenGLBuffer.h"

namespace Dogo
{
	OpenGLBuffer::OpenGLBuffer(uint32_t size, float* data)
		: m_Size(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}
	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}
}
