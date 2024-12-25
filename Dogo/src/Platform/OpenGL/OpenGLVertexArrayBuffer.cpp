#include "dgpch.h"
#include "OpenGLVertexArrayBuffer.h"

namespace Dogo
{
	OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}
	OpenGLVertexArrayBuffer::~OpenGLVertexArrayBuffer()
	{
	}
	void OpenGLVertexArrayBuffer::Bind()
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArrayBuffer::Unbind()
	{
		glBindVertexArray(NULL);
	}
	
	void OpenGLVertexArrayBuffer::AddBuffer(std::shared_ptr<VertexBuffer>& buffer)
	{
		auto openglbuffer = std::dynamic_pointer_cast<OpenGLBuffer>(buffer);
		Bind();
		openglbuffer->Bind();
		uint32_t index = 0;
		const auto& layout = openglbuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(openglbuffer);
	}
	void OpenGLVertexArrayBuffer::Draw(uint32_t count)
	{
		for (size_t i = 0; i < m_VertexBuffers.size(); i++)
		{
			std::shared_ptr<OpenGLBuffer> buffer = (std::shared_ptr<OpenGLBuffer>)m_VertexBuffers[i];
			buffer->Bind();

			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);

			buffer->Unbind();
		}
	}
	void OpenGLVertexArrayBuffer::DrawArrays()
	{
		for (size_t i = 0; i < m_VertexBuffers.size(); i++)
		{
			std::shared_ptr<OpenGLBuffer> buffer = (std::shared_ptr<OpenGLBuffer>)m_VertexBuffers[i];
			buffer->Bind();

			glDrawArrays(GL_LINES, 0, 2);

			buffer->Unbind();
		}
	}
}
