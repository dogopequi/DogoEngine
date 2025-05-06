#pragma once
#include "AssimpModel.h"
#include "Dogo/Core.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Line.h"
#include "Dogo/Actors/Actor.h"
namespace Dogo
{
	struct MatrixPass2
	{
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		glm::mat4 transform;
	};
	class AssimpRenderer
	{
	public:
		AssimpRenderer();
		~AssimpRenderer() {}

		void Submit(const Actor& renderable);
		void Submit(const Line& renderable);
		void Flush();


		inline void SetViewMatrix(glm::mat4 view)
		{
			MVP->view = view;
		}
		inline void SetModelMatrix(const glm::mat4& model)
		{
			MVP->model = model;
		}
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

		inline void SetViewPos(glm::vec3 pos) { m_ViewPos = pos; }

	private:
		std::deque<std::pair<const Model&, const TransformComponent&>> m_RenderQueue;
		std::deque<const Line*> m_RenderQueueLines;
		std::unique_ptr<MatrixPass2> MVP;

		glm::vec3 m_ViewPos;
	};
}