#include "dgpch.h"
#include "AssimpRenderer.h"


namespace Dogo
{
	AssimpRenderer::AssimpRenderer()
	{

		MVP = std::make_unique<MatrixPass2>();
		MVP->model = glm::mat4(1.0f);
		MVP->view = glm::mat4(1.0f);
		MVP->projection = glm::mat4(1.0f);
		MVP->transform = glm::mat4(1.0f);
		RenderAPI api = GraphicsContext::GetAPI();
		if (api == RenderAPI::OpenGL)
			glEnable(GL_DEPTH_TEST);
	}

	void AssimpRenderer::Submit(const Actor& renderable)
	{
		m_RenderQueue.push_back(std::make_pair(std::ref(*renderable.GetModel()), std::ref(*renderable.GetTC())));
	}
	void AssimpRenderer::Submit(const Line& renderable)
	{
		m_RenderQueueLines.push_back(&renderable);
	}
	void AssimpRenderer::Flush()
	{
		while (!m_RenderQueue.empty())
		{
			const auto renderable = m_RenderQueue.front();
			RenderAPI api = GraphicsContext::GetAPI();
			{
				switch (api)
				{
				case Dogo::RenderAPI::API_NONE:
					DG_FATAL("No API specified");
					break;
				case Dogo::RenderAPI::OpenGL:
					renderable.first.GetVertexShader()->Bind();
					break;
				case Dogo::RenderAPI::VULKAN:
					DG_FATAL("Not Implemented");
					break;
				default:
					DG_FATAL("No API specified");
					break;
				}
			}

			MVP->transform = glm::mat4(1.0f);
			glm::vec3 pos = glm::vec3(renderable.second.GetX(), renderable.second.GetY(), renderable.second.GetZ());
			MVP->transform = glm::translate(MVP->transform, pos);
			MVP->model = glm::mat4(1.0f);
			//if (renderable->GetPosition() == glm::vec3(0.0f, 0.0f, 0.01f))
			//{
			//	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.025f, 0.025f, 0.025f));
			//	MVP->model = scaleMatrix * MVP->model;
			//}
			MVP->model *= MVP->transform;
			renderable.first.GetVertexShader()->SetUniformMatrix4f("view", MVP->view, 1);
			renderable.first.GetVertexShader()->SetUniformMatrix4f("projection", MVP->projection, 2);
			renderable.first.GetVertexShader()->SetUniformMatrix4f("model", MVP->model, 0);

			renderable.first.Draw();

			m_RenderQueue.pop_front();
		}
	while (!m_RenderQueueLines.empty())
	{
		const Line* renderable = m_RenderQueueLines.front();
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				renderable->GetVertexShader()->Bind();
				break;
			case Dogo::RenderAPI::VULKAN:
				DG_FATAL("Not Implemented");
				break;
			default:
				DG_FATAL("No API specified");
				break;
			}
		}

		MVP->transform = glm::mat4(1.0f);
		//MVP->transform = glm::translate(MVP->transform, renderable->GetPosition());
		MVP->model = glm::mat4(1.0f);
		MVP->model *= MVP->transform;
		renderable->GetVertexShader()->SetUniformMatrix4f("view", MVP->view, 1);
		renderable->GetVertexShader()->SetUniformMatrix4f("projection", MVP->projection, 2);
		renderable->GetVertexShader()->SetUniformMatrix4f("model", MVP->model, 0);
				
		renderable->Draw();

		m_RenderQueueLines.pop_front();
	}
}
}