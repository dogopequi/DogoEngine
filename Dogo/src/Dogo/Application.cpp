#include "dgpch.h"
#include "Dogo/Core.h"
#include "Application.h"
#include "Logger.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Dogo/Timer.h"
#include <stb/stb_image.h>
#include "Dogo/Renderer/Renderable2D.h"
#include "Dogo/Renderer/SimpleRenderer2D.h"
#include "Dogo/DogoMemory.h"
#include "Renderer/AssimpModel.h"
#include "Renderer/AssimpRenderer.h"
#include "Physics/DG_Physics.h"
#include "Actors/Actor.h"
#include "Dogo/Renderer/Line.h"
#include "Dogo/Renderer/UI/UI.h"

namespace Dogo
{
	constexpr size_t NUM_ENTITIES = 5000;
	constexpr size_t NUM_COMPONENTS = 10000;
	Application::Application() : m_Pool(2)
	{
		m_Window = new Dogo::DogoWindow(1280, 720, "Dogo Window");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Application::OnEvent));
		DG_TRACE("Hello Window");
		m_Renderer = std::shared_ptr<Dogo::Renderer2D>(Dogo::Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl"));
		m_Renderer->SetViewMatrix(glm::mat4(1.0f));
		m_Renderer->SetProjectionMatrix(glm::orthoRH_NO(
			0.0f,
			static_cast<float>(m_Window->GetWidth()),
			static_cast<float>(m_Window->GetHeight()),
			0.0f,
			-1.0f,
			1.0f));
		m_Renderer->SetModelMatrix(glm::mat4(1.0f));
		m_Renderer->SetTransformMatrix(glm::mat4(1.0f));
		entityManager = GetEntityManager();
		componentManager = GetComponentManager();

		componentManager->RegisterComponent<PositionComponent>();
		componentManager->RegisterComponent<VelocityComponent>();
		Dogo::MemoryUsage::PrintUsage();
		m_Running = true;
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		OnWindowCloseEvent(e);
	}

	void Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Renderer->Reset();
		m_Renderer->SetProjectionMatrix(glm::orthoRH_NO(
			0.0f,
			static_cast<float>(m_Window->GetWidth()),
			static_cast<float>(m_Window->GetHeight()),
			0.0f,
			-1.0f,
			1.0f));
		for (Dogo::Layer* layer : m_LayerStack)
			layer->OnResizeNotify();
		OnWindowResizeEvent(e);
		DrawFrame();
	}
	void Application::DrawFrame()
	{
		m_Window->PollEvents();
		m_Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		m_Window->ClearBuffers();
		Tick();
		for (Dogo::Layer* layer : m_LayerStack)
		{
			layer->OnUpdate();
		}
		m_Renderer->Flush();
		Dogo::DogoUI::UIHandleGameInput();
		m_Window->SwapBuffers();
	}
	void Application::KeyPressedCallBack(KeyPressedEvent& e)
	{
		OnKeyPressedEvent(e);
	}
	void Application::KeyReleasedCallBack(KeyReleasedEvent& e)
	{
		OnKeyReleasedEvent(e);
	}
	void Application::MouseMovedCallBack(MouseMovedEvent& e)
	{
		OnMouseMovedEvent(e);
	}
	void Application::MouseButtonPressedCallBack(MouseButtonPressedEvent& e)
	{
		OnMouseButtonPressedEvent(e);
	}
	void Application::MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e)
	{
		OnMouseButtonReleasedEvent(e);
	}
	void Application::MouseScrolledCallBack(MouseScrolledEvent& e)
	{
		OnMouseScrolledEvent(e);
	}

	void Application::Run()
	{
		m_Window->SwapInterval(0);
		while (!m_Window->WindowShouldClose() && m_Window != nullptr)
		{
			DrawFrame();
		

		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			switch (err) {
			case GL_INVALID_ENUM:
				std::cout << "OpenGL Error: GL_INVALID_ENUM" << std::endl;
				break;
			case GL_INVALID_VALUE:
				std::cout << "OpenGL Error: GL_INVALID_VALUE" << std::endl;
				break;
			case GL_INVALID_OPERATION:
				std::cout << "OpenGL Error: GL_INVALID_OPERATION" << std::endl;
				break;
			case GL_STACK_OVERFLOW:
				std::cout << "OpenGL Error: GL_STACK_OVERFLOW" << std::endl;
				break;
			case GL_STACK_UNDERFLOW:
				std::cout << "OpenGL Error: GL_STACK_UNDERFLOW" << std::endl;
				break;
			case GL_OUT_OF_MEMORY:
				std::cout << "OpenGL Error: GL_OUT_OF_MEMORY" << std::endl;
				break;
			default:
				std::cout << "Unknown OpenGL Error" << std::endl;
				break;
			}
		}
		}
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(DG_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(DG_BIND_EVENT_FN(Application::KeyPressedCallBack));
		dispatcher.Dispatch<KeyReleasedEvent>(DG_BIND_EVENT_FN(Application::KeyReleasedCallBack));
		dispatcher.Dispatch<MouseMovedEvent>(DG_BIND_EVENT_FN(Application::MouseMovedCallBack));
		dispatcher.Dispatch<MouseButtonPressedEvent>(DG_BIND_EVENT_FN(Application::MouseButtonPressedCallBack));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(DG_BIND_EVENT_FN(Application::MouseButtonReleasedCallBack));
		dispatcher.Dispatch<MouseScrolledEvent>(DG_BIND_EVENT_FN(Application::MouseScrolledCallBack));
		dispatcher.Dispatch<WindowResizeEvent>(DG_BIND_EVENT_FN(Application::OnWindowResize));
	}
}
