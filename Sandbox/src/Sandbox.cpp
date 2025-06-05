#include "dgpch.h"
#include "Sandbox.h"
#include "Dogo/Core.h"
#include "Dogo/LayerStack.h"
#include "Dogo/Layer.h"
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

	bool Sandbox::OnWindowClose(Dogo::WindowCloseEvent& e)
	{
		return Application::OnWindowClose(e);
	}
	bool Sandbox::KeyPressedCallBack(Dogo::KeyPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::KeyReleasedCallBack(Dogo::KeyReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::MouseMovedCallBack(Dogo::MouseMovedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::MouseButtonPressedCallBack(Dogo::MouseButtonPressedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::MouseButtonReleasedCallBack(Dogo::MouseButtonReleasedEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::MouseScrolledCallBack(Dogo::MouseScrolledEvent& e)
	{
		DG_TRACE(e.ToString().c_str());
		return true;
	}
	bool Sandbox::OnWindowResize(Dogo::WindowResizeEvent& e)
	{
		Renderer->Reset();
		Renderer->SetProjectionMatrix(glm::orthoRH_NO(
			0.0f,
			static_cast<float>(m_Window->GetWidth()),
			static_cast<float>(m_Window->GetHeight()),
			0.0f,
			-1.0f,
			1.0f));
		m_Window->Viewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		for (Dogo::Layer* layer : m_LayerStack)
			layer->OnResizeNotify();
		resize = true;
		return true;
	}

	void Sandbox::Run()
	{
		m_Window->SwapInterval(0);
		while (!m_Window->WindowShouldClose() && m_Window != nullptr)
		{
			m_Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			m_Window->ClearBuffers();
			for (Dogo::Layer* layer : m_LayerStack)
			{
				if (resize)
				{
					m_Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
					m_Window->ClearBuffers();
					resize = false;
					continue;
				}
				layer->OnUpdate();
			}
			Dogo::DogoUI::UIHandleGameInput();
			m_Window->SwapBuffers();
			m_Window->PollEvents();
		}
	}


	Sandbox::Sandbox() : Application()
	{
#ifdef DG_SANDBOX_MODE_APP
		m_Window = new Dogo::DogoWindow(1280, 720, "Dogo Window");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Sandbox::OnEvent));
#endif
		DG_TRACE("Hello Window");
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
		Pong* pong = new Pong(Renderer);
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
#ifdef DG_SANDBOX_MODE_APP
		Run();
#endif
	}

	void Sandbox::OnEvent(Dogo::Event& e)
	{
		Dogo::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<Dogo::WindowCloseEvent>(DG_BIND_EVENT_FN(Sandbox::OnWindowClose));
		//dispatcher.Dispatch<Dogo::KeyPressedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyPressedCallBack));
		//dispatcher.Dispatch<Dogo::KeyReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::KeyReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseMovedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseMovedCallBack));
		dispatcher.Dispatch<Dogo::MouseButtonPressedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonPressedCallBack));
		//dispatcher.Dispatch<Dogo::MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(Sandbox::MouseButtonReleasedCallBack));
		//dispatcher.Dispatch<Dogo::MouseScrolledEvent>(DG_BIND_EVENT_FN(Sandbox::MouseScrolledCallBack));
		dispatcher.Dispatch<Dogo::WindowResizeEvent>(DG_BIND_EVENT_FN(Sandbox::OnWindowResize));
	}
