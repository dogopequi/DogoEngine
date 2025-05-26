#include "dgpch.h"

#include <Dogo.h>
#include "Dogo/Application.h"
#include "Sandbox.h"
#include "EditorLayer.h"

class Editor : public Dogo::Application
{
public:
    Editor()
    {
        DG_TRACE("Launching Editor");
        PushLayer(new EditorLayer());
		m_Window->~DogoWindow();
        Sandbox* game = new Sandbox();
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Editor::OnEvent));
		game->Run();
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

	void OnEvent(Dogo::Event& e)
	{
		Dogo::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Dogo::WindowCloseEvent>(DG_BIND_EVENT_FN(OnWindowClose));
		//dispatcher.Dispatch<Dogo::KeyPressedEvent>(DG_BIND_EVENT_FN(KeyPressedCallBack));
		//dispatcher.Dispatch<Dogo::KeyReleasedEvent>(DG_BIND_EVENT_FN(KeyReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseMovedEvent>(DG_BIND_EVENT_FN(MouseMovedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonPressedEvent>(DG_BIND_EVENT_FN(MouseButtonPressedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(MouseButtonReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseScrolledEvent>(DG_BIND_EVENT_FN(MouseScrolledCallBack));
	}

	void Run() override
	{

	}

	~Editor() = default;
};

Dogo::Application* Dogo::CreateApplication()
{
    return new Editor();
}
