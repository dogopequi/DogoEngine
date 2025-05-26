#include "dgpch.h"
#include <Dogo.h>
#include "Dogo/Core.h"
#include "Dogo/LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Dogo/Events/Event.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#include "Dogo/Renderer/Camera.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Dogo/Timer.h"
#include "Dogo/DogoMemory.h"
#include "Dogo/Physics/DG_Physics.h"
#include "DogoECS.h"
#include "Dogo/Component/Component.h"
#include "Dogo/Renderer/Line.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/DogoWindow.h"
#include "Examples/Pong.h"
class Sandbox : public Dogo::Application
{
public:

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


	Sandbox() : Application()
	{
		DG_TRACE("Hello Window");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Sandbox::OnEvent));
		Pong* pong = new Pong();
		pong->window = m_Window;
		pong->OnAttach();
		PushLayer(pong);

		Dogo::MemoryUsage::PrintUsage();
		DogoECS::Init();
		Dogo::DG_Physics::InitPhysics(glm::vec3(0.0f, -9.81f, 0.0f));
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::BaseComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::DynamicMeshComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::TransformComponent>();
		DogoECS::DG_ComponentManager::RegisterComponent<Dogo::StaticMeshComponent>();
	}
	~Sandbox()
	{

	}

	void OnEvent(Dogo::Event& e) override
	{
		Dogo::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Dogo::WindowCloseEvent>(DG_BIND_EVENT_FN(Sandbox::OnWindowClose));
		//dispatcher.Dispatch<Dogo::KeyPressedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyPressedCallBack));
		//dispatcher.Dispatch<Dogo::KeyReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseMovedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseMovedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonPressedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonPressedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseScrolledEvent>(DG_BIND_EVENT_FN(Sandbox::MouseScrolledCallBack));
	}


};

Dogo::Application* Dogo::CreateApplication()
{
	return new Sandbox();
}