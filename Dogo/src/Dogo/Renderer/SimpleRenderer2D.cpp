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

	RenderAPI api = GraphicsContext::Get()->GetAPI();
	switch (api)
	{
	case RenderAPI::OpenGL:
	{
		m_Shader->Bind();
		m_Shader->SetUniformMatrix4f("view", MVP->view, 1);
		m_Shader->SetUniformMatrix4f("projection", MVP->projection, 2);

	}break;
	#if DG_PLATFORM_WINDOWS
	case RenderAPI::D3D11:
	{
		m_Shader->Bind();
		m_PixelShader->Bind();
		m_Shader->SetUniformMatrix4f("view", MVP->view, 1);
		m_Shader->SetUniformMatrix4f("projection", MVP->projection, 2);
		DX11Context::GetContext()->GetDeviceContext().Get()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DX11Context::GetContext()->GetDeviceContext().Get()->RSSetViewports(1, &DX11Context::GetContext()->GetViewport());
	}
	#endif
	break;
	default:
		DG_FATAL("API NOT SPECIFIED");
	}

	while (!m_RenderQueue.empty())
	{
		const Renderable2D* renderable = m_RenderQueue.front();

		renderable->GetVAO()->Bind();
		MVP->transform = glm::mat4(1.0f);
		MVP->transform = glm::translate(MVP->transform, renderable->GetPosition());
		MVP->model = glm::mat4(1.0f);
		MVP->model *= MVP->transform;

		m_Shader->SetUniformMatrix4f("model", MVP->model, 0);

		renderable->GetVAO()->Draw(renderable->GetIBO()->getComponentCount());

		m_RenderQueue.pop_front();
	}
}
