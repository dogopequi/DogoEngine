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

		inline void SetViewMatrix(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up) 
		{ glm::mat4 view = glm::lookAtRH(pos, dir, up); MVP->view = view; }
		inline void SetModelMatrix(const glm::mat4& model) 
		{ MVP->model = model; }
		inline void SetProjectionMatrixPerspective(float FOV, float width, float height, float minDepth, float maxDepth)
		{ 
			glm::mat4 proj;
			RenderAPI api = GraphicsContext::GetAPI();
			switch (api)
			{
			case RenderAPI::None:
				DG_FATAL("Invalid render API");
				break;
			case RenderAPI::OpenGL:
				proj = glm::perspectiveFovRH_NO(glm::radians(FOV), width, height, minDepth, maxDepth);
				break;
#if DG_PLATFORM_WINDOWS
			case RenderAPI::D3D11:
				proj = glm::perspectiveFovRH_ZO(glm::radians(FOV), width, height, minDepth, maxDepth);
				break;
			case RenderAPI::D3D12:
				DG_FATAL("Not implemented");
				break;
#endif
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

		inline std::shared_ptr<Shader> GetVertexShader() const {return m_Shader;}

		inline void SetVertexAndPixelShader(const std::string& vertex, const std::string& pixel)
		{
			m_Shader.reset(Shader::Create(vertex, pixel));;
		}
#if DG_PLATFORM_WINDOWS
		inline void SetVertexAndPixelShader(const std::wstring& vertex, const std::wstring& pixel)
		{ 
			m_Shader.reset(Shader::Create(vertex, ShaderType::VERTEX)); m_PixelShader.reset(Shader::Create(pixel, ShaderType::FRAGMENT));
		}
#endif

	private:
		std::deque<const Renderable2D*> m_RenderQueue;
		std::unique_ptr<MatrixPass> MVP;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Shader> m_PixelShader; //dead space if its opengl

	};

}

