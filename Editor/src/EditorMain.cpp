#include "dgpch.h"

#include <Dogo.h>
#include "Dogo/Application.h"
#include "Sandbox.h"
#include "EditorLayer.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Dogo/Renderer/FrameBuffer.h"

class Editor : public Dogo::Application
{
public:
    Editor()
    {
        DG_TRACE("Launching Editor");
		m_Window = new Dogo::DogoWindow(1920, 1080, "Dogo Editor");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Editor::OnEvent));
		Sandbox* game = new Sandbox();
		Renderer = std::shared_ptr<Dogo::Renderer2D>(Dogo::Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl"));
		Renderer->SetViewMatrix(glm::mat4(1.0f));
		Renderer->SetProjectionMatrix(glm::orthoRH_NO(
			0.0f,
			static_cast<float>(m_Window->GetWidth()),
			static_cast<float>(m_Window->GetHeight()),
			0.0f,
			-1.0f,
			1.0f));
		Renderer->SetModelMatrix(glm::mat4(1.0f));
		Renderer->SetTransformMatrix(glm::mat4(1.0f));
		Framebuffer = std::shared_ptr<Dogo::Framebuffer>(Dogo::Framebuffer::Create(m_Window->GetWidth(), m_Window->GetHeight()));
		editorLayer = new EditorLayer(Renderer, m_Window, Framebuffer);
		PushLayer(editorLayer);
    }

	bool OnWindowClose(Dogo::WindowCloseEvent& e)
	{
		return Application::OnWindowClose(e);
	}
	bool KeyPressedCallBack(Dogo::KeyPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool KeyReleasedCallBack(Dogo::KeyReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseMovedCallBack(Dogo::MouseMovedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseButtonPressedCallBack(Dogo::MouseButtonPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseButtonReleasedCallBack(Dogo::MouseButtonReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool MouseScrolledCallBack(Dogo::MouseScrolledEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool OnWindowResize(Dogo::WindowResizeEvent& e)
	{
		Renderer->Reset();
		Framebuffer->Resize(e.GetWidth(), e.GetHeight());
		editorLayer->SetupViewport();
		resize = true;
		Framebuffer->Bind();
		return true;
	}

	void OnEvent(Dogo::Event& e)
	{
		Dogo::EventDispatcher dispatcher(e);
		dispatcher.Dispatch<Dogo::WindowCloseEvent>(DG_BIND_EVENT_FN(Editor::OnWindowClose));
		//dispatcher.Dispatch<Dogo::KeyPressedEvent>(DG_BIND_EVENT_FN(KeyPressedCallBack));
		//dispatcher.Dispatch<Dogo::KeyReleasedEvent>(DG_BIND_EVENT_FN(KeyReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseMovedEvent>(DG_BIND_EVENT_FN(MouseMovedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonPressedEvent>(DG_BIND_EVENT_FN(MouseButtonPressedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(MouseButtonReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseScrolledEvent>(DG_BIND_EVENT_FN(MouseScrolledCallBack));
		dispatcher.Dispatch<Dogo::WindowResizeEvent>(DG_BIND_EVENT_FN(Editor::OnWindowResize));
	}

	void Run() override
	{
		m_Window->SwapInterval(1);
		while (!m_Window->WindowShouldClose() && m_Window != nullptr)
		{
			m_Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			Framebuffer->Bind();
			for (Dogo::Layer* layer : m_LayerStack)
			{
				if (resize)
				{
					Framebuffer->Bind();
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
					resize = false;
					continue;
				}
				layer->OnUpdate();
			}
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}

	~Editor() = default;


private:
	std::shared_ptr<Dogo::Framebuffer> Framebuffer;
	std::shared_ptr<Dogo::Renderer2D> Renderer;
	EditorLayer* editorLayer;
	bool resize = false;
};

Dogo::Application* Dogo::CreateApplication()
{
    return new Editor();
}
