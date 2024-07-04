#pragma once
#include "Renderable2D.h"
#include "Dogo/Core.h"
namespace Dogo
{
	struct MatrixPass
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 transform;
	};
	class SimpleRenderer2D
	{
	public:
		SimpleRenderer2D();
		~SimpleRenderer2D();

		void Submit(const Renderable2D& renderable);
		void Flush();

		inline void SetViewMatrix(glm::mat4 view) 
		{
			MVP->view = view;
		}
		inline void SetModelMatrix(const glm::mat4& model) 
		{ MVP->model = model; }
		inline void SetProjectionMatrixPerspective(float FOV, float width, float height, float minDepth, float maxDepth)
		{ 
			glm::mat4 proj;
			RenderAPI api = GraphicsContext::GetAPI();
			switch (api)
			{
			case RenderAPI::API_NONE:
				DG_FATAL("Invalid render API");
				break;
			case RenderAPI::OpenGL:
				proj = glm::perspectiveFovRH_NO(glm::radians(FOV), width, height, minDepth, maxDepth);
				break;
			case RenderAPI::D3D11:
				proj = glm::perspectiveFovRH_ZO(glm::radians(FOV), width, height, minDepth, maxDepth);
				break;
			case RenderAPI::D3D12:
				DG_FATAL("Not implemented");
				break;
			case RenderAPI::VULKAN:
				DG_FATAL("Not implemented");
				break;
			default:
			{
				proj = glm::perspectiveFovRH_NO(glm::radians(FOV), width, height, minDepth, maxDepth);
				DG_FATAL("Invalid render API, defaulted to OPENGL SPEC");
			}
				break;
			}
			MVP->projection = proj;
		}
		inline void SetTransformMatrix(const glm::mat4& transform) { MVP->transform = transform; }

		inline glm::mat4 GetViewMatrix() const { return MVP->view; }
		inline glm::mat4 GetModelMatrix() const { return MVP->model; }
		inline glm::mat4 GetProjectionMatrix() const { return MVP->projection; }
		inline glm::mat4 GetTransformMatrix() const { return MVP->transform; }

		inline std::shared_ptr<Shader> GetVertexShader() const {return m_VertexShader;}
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
				break;
			case RenderAPI::D3D11:
				m_VertexShader.reset(Shader::Create(vertex, ShaderType::VERTEX));
				m_PixelShader.reset(Shader::Create(vertex, ShaderType::FRAGMENT));
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
		inline void SetVertexAndPixelShader(const std::string& vertex, const std::string& pixel)
		{
			m_VertexShader.reset(Shader::Create(vertex, pixel));
		}

	private:
		std::deque<const Renderable2D*> m_RenderQueue;
		std::unique_ptr<MatrixPass> MVP;
		std::shared_ptr<Shader> m_VertexShader;
		std::shared_ptr<Shader> m_PixelShader;


	};

}

