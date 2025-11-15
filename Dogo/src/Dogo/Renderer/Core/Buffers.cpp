#include "dgpch.h"
#include "Dogo/Renderer/Core/Buffers.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Graphics/GraphicsContext.h"

namespace Dogo
{
	VertexArray* VertexArray::Create()
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLVertexArrayBuffer();
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid API to create VertexArrayBuffer");
			return nullptr;
			break;
		}
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* data, uint32_t count)
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLIndexBuffer(size, data, count);
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid API to create IndexBuffer");
			return nullptr;
			break;
		}
		return nullptr;
	}
	VertexBuffer* VertexBuffer::Create(uint32_t bufferSize, uint32_t componentSize, float* data)
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLBuffer(bufferSize, data);
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid API to create IndexBuffer");
			return nullptr;
			break;
		}
		return nullptr;
	}
}
