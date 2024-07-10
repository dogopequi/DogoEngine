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
	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};
	class Renderable2D
	{
	public:
		Renderable2D(const glm::vec3& pos, float* vertices, size_t vertSize, uint32_t* indices, size_t indiceSize, BufferLayout& layout, const std::wstring& vertex, const std::wstring& pixel)
			: m_Position(pos)
		{
			SetVertexAndPixelShader(vertex, pixel);
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
				SetLayout(m_VertexShader);
			}
#endif
			break;
			default:
				DG_FATAL("API NOT SPECIFIED");
			}
			m_VertexArray->AddBuffer(m_VertexBuffer);
		}

		inline void SetVertexAndPixelShader(const std::wstring& vertex, const std::wstring& pixel)
		{
			RenderAPI api = GraphicsContext::GetAPI();
			switch (api)
			{
			case RenderAPI::API_NONE:
				DG_FATAL("Invalid render API");
				break;
			case RenderAPI::OpenGL:
				m_VertexShader.reset(Shader::Create(vertex, pixel));
				m_PixelShader = m_VertexShader;
				break;
			case RenderAPI::D3D11:
				m_VertexShader.reset(Shader::Create(vertex, ShaderType::VERTEX));
				m_PixelShader.reset(Shader::Create(pixel, ShaderType::FRAGMENT));
				break;
			case RenderAPI::D3D12:
				DG_FATAL("Not implemented");
				break;
			case RenderAPI::VULKAN:
				DG_FATAL("Not implemented");
				break;
			default:
			{
				DG_FATAL("Invalid render API, defaulted to OPENGL SPEC");
			}
			break;
			}
		}

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetColor() const { return m_Color; }
		inline void SetColor(const glm::vec3& color) { m_Color = color; }

		inline std::shared_ptr<VertexArray> GetVAO() const { return m_VertexArray; }
		inline std::shared_ptr<VertexBuffer> GetVBO() const { return m_VertexBuffer; }
		inline std::shared_ptr<IndexBuffer> GetIBO() const { return m_IndexBuffer; }
		#if DG_PLATFORM_WINDOWS
		inline void SetLayout(std::shared_ptr<Shader> shader) const
		{ 
			std::shared_ptr<DX11VertexShader> dx11shader = std::static_pointer_cast<DX11VertexShader>(shader);
			std::shared_ptr<DX11VertexBuffer> dx11vbo = std::static_pointer_cast<DX11VertexBuffer>(m_VertexBuffer);
			dx11vbo->SetLayout(*m_Layout, dx11shader->GetBufferPointer(), dx11shader->GetBufferLength());
		}
		#endif
		inline void SetLayout() const { m_VertexBuffer->SetLayout(*m_Layout); }


		inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
		inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }


		inline void SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
		{
			m_Material.ambient = ambient;
			m_Material.diffuse = diffuse;
			m_Material.specular = specular;
			m_Material.shininess = shininess;
		}

		inline Material GetMaterial() const { return m_Material; }


	protected:
		glm::vec3 m_Position;
		glm::vec3 m_Color;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<BufferLayout> m_Layout;
		std::shared_ptr<Shader> m_VertexShader;
		std::shared_ptr<Shader> m_PixelShader;
		Material m_Material;
	};

	
}