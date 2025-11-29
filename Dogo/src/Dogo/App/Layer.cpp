#include "dgpch.h"
#include "Layer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace Dogo
{
	Layer2D::Layer2D(const std::string& name, const std::shared_ptr<DogoWindow>& window)
		: m_Name(name), m_Window(window)
	{
		m_FrameBuffer = std::unique_ptr<Framebuffer>(Framebuffer::Create(m_Window->GetWidth(), m_Window->GetHeight()));
		m_Scene = std::make_shared<Scene>();
		m_Renderer = std::shared_ptr<Dogo::Renderer2D>(Dogo::Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl"));
	}
	void Layer2D::OnResizeNotify()
	{
		for (auto cam : m_Scene->GetCameras())
		{
			if (cam.expired())
				continue;
			auto camera = cam.lock();
			camera->SetRenderTargetSize(m_Window->GetWidth(), m_Window->GetHeight());
			camera->SetOrthographic(m_Window->GetWidth(), m_Window->GetHeight(), 0.1, 100.0f);
		}
		m_FrameBuffer->Resize(m_Window->GetWidth(), m_Window->GetHeight());
		OnResize();
	}
	void Layer2D::Update(double delta)
	{
		m_Scene->UpdateGameObjects(delta);
		OnUpdate(delta);
		for (auto cam : m_Scene->GetCameras())
		{
			if (cam.expired())
				continue;
			auto camera = cam.lock();
			m_Renderer->SetViewMatrix(camera->GetViewMatrix());
			m_Renderer->SetProjectionMatrix(camera->GetProjectionMatrix());
			camera->BindTarget();
			m_Window->ClearBuffers();
			m_Renderer->Begin(camera);
			m_Renderer->BeginBatch();
			for (float x = 0; x <= m_Window->GetWidth(); x += 32.0f)
			{
				m_Renderer->Submit(Dogo::CreateLine2D(
					{ x, 0.0f },
					{ x, (float)m_Window->GetHeight() },
					{ 0.3f, 0.3f, 0.3f, 1.0f }
				));
			}
			for (float y = 0; y <= m_Window->GetHeight(); y += 32.0f)
			{
				m_Renderer->Submit(Dogo::CreateLine2D(
					{ 0.0f, y },
					{ (float)m_Window->GetWidth(), y },
					{ 0.3f, 0.3f, 0.3f, 1.0f }
				));
			}
			Submit();
			SpriteRenderSystem2D::Update(m_Renderer);
			m_Renderer->EndBatch();
			m_Renderer->Flush();
			camera->UnbindTarget();
		}
		auto mainCam = m_Scene->GetMainCamera().lock();
		if (mainCam)
		{
			m_Renderer->SetViewMatrix(mainCam->GetViewMatrix());
			m_Renderer->SetProjectionMatrix(mainCam->GetProjectionMatrix());
			m_FrameBuffer->Bind();
			uint32_t texID = mainCam->GetRenderTargetID();
			m_Renderer->RenderFrameBuffer(texID, m_Window->GetWidth(), m_Window->GetHeight());
			m_Renderer->RenderText();
			m_FrameBuffer->Unbind();
		}
	}
	Layer2D::~Layer2D()
	{
	}
}
