#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Buffers.h"
#include "Graphics/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Dogo/Renderer/Buffers.h"
#include "Platform/DX11/DX11IndexBuffer.h"
#include "Platform/DX11/DX11VertexBuffer.h"
#include "Platform/DX11/DX11Shader.h"
#include "Dogo/Logger.h"
namespace Dogo
{
	class Renderable2D
	{
	public:
		Renderable2D(glm::vec3& pos, float* vertices, size_t vertSize, uint32_t* indices, size_t indiceSize, BufferLayout& layout, std::shared_ptr<Shader> shader)
			: m_Position(pos)
		{
			m_Layout = std::make_shared<BufferLayout>(layout);
			m_VertexArray.reset(VertexArray::Create());
			m_VertexArray->Bind();
			m_VertexBuffer.reset(VertexBuffer::Create(vertSize, sizeof(float) * 8, vertices));
			m_IndexBuffer.reset(IndexBuffer::Create(indiceSize, indices, indiceSize / sizeof(uint32_t)));
			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();
			RenderAPI api = GraphicsContext::Get()->GetAPI();
			switch (api)
			{
			case RenderAPI::OpenGL:
			{
				SetLayout();
			}break;
#if DG_PLATFORM_WINDOWS
			case RenderAPI::D3D11:
			{
				SetLayout(shader);
			}
#endif
			break;
			default:
				DG_FATAL("API NOT SPECIFIED");
			}
			m_VertexArray->AddBuffer(m_VertexBuffer);
		}



		inline glm::vec3 GetPosition() const { return m_Position; }

		inline std::shared_ptr<VertexArray> GetVAO() const { return m_VertexArray; }
		inline std::shared_ptr<VertexBuffer> GetVBO() const { return m_VertexBuffer; }
		inline std::shared_ptr<IndexBuffer> GetIBO() const { return m_IndexBuffer; }
		inline void SetLayout(std::shared_ptr<Shader> shader) const
		{ 
			std::shared_ptr<DX11VertexShader> dx11shader = std::static_pointer_cast<DX11VertexShader>(shader);
			std::shared_ptr<DX11VertexBuffer> dx11vbo = std::static_pointer_cast<DX11VertexBuffer>(m_VertexBuffer);
			dx11vbo->SetLayout(*m_Layout, dx11shader->GetBufferPointer(), dx11shader->GetBufferLength());
		}
		inline void SetLayout() const { m_VertexBuffer->SetLayout(*m_Layout); }


	protected:
		glm::vec3 m_Position;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<BufferLayout> m_Layout;
	};

	
}