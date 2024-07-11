#include "dgpch.h"
#include "SimpleRenderer2D.h"

Dogo::SimpleRenderer2D::SimpleRenderer2D()
{
	MVP = std::make_unique<MatrixPass>();
	MVP->model = glm::mat4(1.0f);
	MVP->view = glm::mat4(1.0f);
	MVP->projection = glm::mat4(1.0f);
	MVP->transform = glm::mat4(1.0f);
	RenderAPI api = GraphicsContext::GetAPI();
	if(api == RenderAPI::OpenGL)
		glEnable(GL_DEPTH_TEST);
}

Dogo::SimpleRenderer2D::~SimpleRenderer2D()
{
}

void Dogo::SimpleRenderer2D::Submit(const Renderable2D& renderable)
{
	m_RenderQueue.push_back(&renderable);
}

void Dogo::SimpleRenderer2D::Flush()
{
	while (!m_RenderQueue.empty())
	{
		const Renderable2D* renderable = m_RenderQueue.front();
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
			case Dogo::RenderAPI::D3D11:
				renderable->GetVertexShader()->Bind();
				renderable->GetPixelShader()->Bind();
				break;
			case Dogo::RenderAPI::D3D12:
				DG_FATAL("Not Implemented");
				break;
			default:
				DG_FATAL("No API specified");
				break;
			}
		}
		renderable->GetVertexShader()->SetUniformMatrix4f("view", MVP->view, 1);
		renderable->GetVertexShader()->SetUniformMatrix4f("projection", MVP->projection, 2);
		renderable->GetPixelShader()->SetUniform3f("objcolor", renderable->GetColor());
		renderable->GetPixelShader()->SetUniform3f("viewPos", m_ViewPos);
		if(renderable->GetMaterial().diffuse != nullptr)
		{
			renderable->GetMaterial().diffuse->Bind(0, "material.diffuse");
			renderable->GetPixelShader()->SetUniform1i("material.diffuse", 0);
		}
		if (renderable->GetMaterial().specular != nullptr)
		{
			renderable->GetMaterial().specular->Bind(1, "material.specular");
			renderable->GetPixelShader()->SetUniform1i("material.specular", 1);
		}
		if (renderable->GetMaterial().emission != nullptr)
		{
			renderable->GetMaterial().emission->Bind(2, "material.emission");
			renderable->GetPixelShader()->SetUniform1i("material.emission", 2);
		}
		renderable->GetPixelShader()->SetUniform1f("material.shininess", renderable->GetMaterial().shininess);

		renderable->GetPixelShader()->SetUniform3f("light.position", m_Light.position);
		renderable->GetPixelShader()->SetUniform3f("light.ambient", m_Light.ambient);
		renderable->GetPixelShader()->SetUniform3f("light.diffuse", m_Light.diffuse);
		renderable->GetPixelShader()->SetUniform3f("light.specular", m_Light.specular);

		renderable->GetVAO()->Bind();
		MVP->transform = glm::mat4(1.0f);
		MVP->transform = glm::translate(MVP->transform, renderable->GetPosition());
		MVP->model = glm::mat4(1.0f);
		MVP->model *= MVP->transform;

		renderable->GetVertexShader()->SetUniformMatrix4f("model", MVP->model, 0);

		renderable->GetVAO()->Draw(renderable->GetIBO()->getComponentCount());

		m_RenderQueue.pop_front();
	}
}
