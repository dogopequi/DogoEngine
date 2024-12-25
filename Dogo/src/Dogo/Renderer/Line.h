#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include "VertexHash.h"
#include "Shader.h"
#include "Buffers.h"
#include "Graphics/GraphicsContext.h"
#include "Texture.h"
#include "Platform/DX11/DX11VertexBuffer.h"
#include "Platform/DX11/DX11Shader.h"
namespace Dogo
{
	class Line
	{
	public:
		Line(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color, const std::wstring& vertex, const std::wstring& pixel) {
			m_StartPoint = start;  m_EndPoint
				= end; m_Color = color;
            SetVertexAndPixelShader(vertex, pixel);

			m_Vertices = {
			 start.x, start.y, start.z,
			 end.x, end.y, end.z,

			};

            m_VertexArray.reset(VertexArray::Create());
            m_VertexArray->Bind();
            std::vector<float> vertexData;
            for (const auto& vertex : m_Vertices) {
                vertexData.push_back(start.x);
                vertexData.push_back(start.y);
                vertexData.push_back(start.z);
				vertexData.push_back(end.x);
				vertexData.push_back(end.y);
				vertexData.push_back(end.z);
            }
            m_VertexBuffer.reset(VertexBuffer::Create(m_Vertices.size() * sizeof(Vertex), sizeof(Vertex), vertexData.data()));
            m_VertexBuffer->Bind();
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
		~Line() {}

        inline std::shared_ptr<Shader> GetVertexShader() const { return m_VertexShader; }
        inline std::shared_ptr<Shader> GetPixelShader() const { return m_PixelShader; }

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

        void Draw() const;
#if DG_PLATFORM_WINDOWS
        inline void SetLayout(std::shared_ptr<Shader> shader) const
        {
            std::shared_ptr<DX11VertexShader> dx11shader = std::static_pointer_cast<DX11VertexShader>(shader);
            std::shared_ptr<DX11VertexBuffer> dx11vbo = std::static_pointer_cast<DX11VertexBuffer>(m_VertexBuffer);
            dx11vbo->SetLayout(m_Layout, dx11shader->GetBufferPointer(), dx11shader->GetBufferLength());
        }
#endif
        inline void SetLayout() const { m_VertexBuffer->SetLayout(m_Layout); }

		std::vector<float> m_Vertices;
		glm::vec3 m_StartPoint;
		glm::vec3 m_EndPoint;
		glm::vec3 m_Color;
        std::shared_ptr<VertexArray> m_VertexArray;
        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<Shader> m_VertexShader;
        std::shared_ptr<Shader> m_PixelShader;

        BufferLayout m_Layout =
		{
			{ShaderDataType::Float3, "aPos"}
		};
	};
}