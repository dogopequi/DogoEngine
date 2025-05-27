#pragma once
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include "VertexHash.h"
#include "Shader.h"
#include "Buffers.h"
#include "Graphics/GraphicsContext.h"
#include "Texture.h"

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
            m_VertexBuffer.reset(VertexBuffer::Create(uint32_t(m_Vertices.size() * sizeof(assimpVertex)), uint32_t(sizeof(assimpVertex)), vertexData.data()));
            m_VertexBuffer->Bind();
            RenderAPI api = GraphicsContext::Get()->GetAPI();
            switch (api)
            {
            case RenderAPI::OpenGL:
            {
                SetLayout();
            }break;
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