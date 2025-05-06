#pragma once
#include "Renderable2D.h"
#include "Dogo/Core.h"
namespace Dogo
{
	struct Light {
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
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


		//temp
		inline void SetLight(const glm::vec3& position, const glm::vec3& ambient, const glm::vec3& diffuse, glm::vec3& specular)
		{ 
			m_Light.position = position;
			m_Light.ambient = ambient;
			m_Light.diffuse = diffuse;
			m_Light.specular = specular;
		}
		inline void SetViewPos(glm::vec3 pos) { m_ViewPos = pos; }

	private:
		std::deque<const Renderable2D*> m_RenderQueue;
		std::unique_ptr<MatrixPass> MVP;


		//temp
		Light m_Light;
		glm::vec3 m_ViewPos;


	};

}

