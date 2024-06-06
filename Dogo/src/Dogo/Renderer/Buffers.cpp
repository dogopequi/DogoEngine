#include "dgpch.h"
#include "Buffers.h"
#include "Platform/DX11/DX11ArrayBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Platform/DX11/DX11IndexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/DX11/DX11VertexBuffer.h"
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
		case RenderAPI::D3D11:
			return new DX11ArrayBuffer();
			break;
		default:
			DG_FATAL("Invalid API to create VertexArrayBuffer");
			return nullptr;
			break;
		}
	}
	IndexBuffer* IndexBuffer::Create(uint32_t size, uint32_t* data, uint32_t count)
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLIndexBuffer(size, data, count);
			break;
		case RenderAPI::D3D11:
			return new DX11IndexBuffer(size, data, count);
			break;
		default:
			DG_FATAL("Invalid API to create IndexBuffer");
			return nullptr;
			break;
		}
	}
	VertexBuffer* VertexBuffer::Create(uint32_t bufferSize, uint32_t componentSize, float* data)
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLBuffer(bufferSize, data);
			break;
		case RenderAPI::D3D11:
			return new DX11VertexBuffer(bufferSize, componentSize, data);
			break;
		default:
			DG_FATAL("Invalid API to create IndexBuffer");
			return nullptr;
			break;
		}
	}
}
