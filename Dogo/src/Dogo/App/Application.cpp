#include "dgpch.h"
#include "Dogo/Core.h"
#include "Application.h"
#include "Dogo/Utils/Logger.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"
#include "Dogo/Renderer/Core/Buffers.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
#include "Dogo/Utils/Timer.h"
#include <stb/stb_image.h>
#include "Dogo/Utils/DogoMemory.h"
#include "Dogo/Renderer/3D/AssimpModel.h"
#include "Dogo/Renderer/3D/AssimpRenderer.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Actors/Actor.h"
#include "Dogo/Renderer/3D/Line.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Dogo/Audio/AudioEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace Dogo
{
	Application::~Application()
	{
		shutdownOpenAL();
	}
	Application::Application() : m_Pool(2)
	{
		m_Window = std::make_shared<Dogo::DogoWindow>(1280, 720, "Dogo Window");
		m_Window->SetEventCallback(DG_BIND_EVENT_FN(Application::OnEvent));
		m_Renderer = std::shared_ptr<Renderer2D>(Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl"));
		m_Camera = std::make_unique<Dogo::Camera>(Dogo::Camera::Orthographic(m_Window->GetWidth(), m_Window->GetHeight(), -1.0f, 1.0f));
		m_Renderer->SetViewMatrix(m_Camera->GetViewMatrix());
		m_Renderer->SetProjectionMatrix(m_Camera->GetProjectionMatrix());
		m_Renderer->SetModelMatrix(glm::mat4(1.0f));
		m_Renderer->SetTransformMatrix(glm::mat4(1.0f));
		ECS::GetEntityManager();
		ECS::GetComponentManager();

		ECS::RegisterComponent<ECS::TransformComponent>();
		ECS::RegisterComponent<ECS::VelocityComponent>();

		DG_Physics::InitPhysics(glm::vec3(0.0f, 100.0f, 0.0f));
		Dogo::MemoryUsage::PrintUsage();

		if (!initOpenAL()) {
			DG_ERROR("Failed to init OpenAL");
		}
		m_Running = true;
	}


	void Application::PushLayer(Layer2D* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer2D* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::OnWindowClose(WindowCloseEvent& e)
	{
		OnWindowCloseEvent(e);
	}

	void Application::OnWindowResize(WindowResizeEvent& e)
	{
		m_Camera->SetOrthographic(m_Window->GetWidth(), m_Window->GetHeight(), 0.1, 100.0f);
		m_Camera->SetRenderTargetSize(m_Window->GetWidth(), m_Window->GetHeight());
		for (Dogo::Layer2D* layer : m_LayerStack)
			layer->OnResizeNotify();
		OnWindowResizeEvent(e);
		Frame();
	}
	void Application::Frame()
	{
		double now = m_Window->GetTime();
		double dt = now - m_LastDelta;
		m_LastDelta = now;

		m_Window->PollEvents();
		m_Window->ClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		m_Window->ClearBuffers();

		PhysicsSystem::Update(dt);
		AudioSystem2D::Update();
		Tick();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (Dogo::Layer2D* layer : m_LayerStack)
		{
			layer->Update(dt);
			m_Window->Viewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
			m_Renderer->SetViewMatrix(m_Camera->GetViewMatrix());
			m_Renderer->SetProjectionMatrix(m_Camera->GetProjectionMatrix());
			uint32_t texID = layer->GetFrameBufferID();
			m_Renderer->RenderFrameBuffer(texID, m_Window->GetWidth(), m_Window->GetHeight());
		}
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		Dogo::DogoUI::UIHandleGameInput();
		Input::Update();
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
		m_Window->SwapInterval(1);
		while (!m_Window->WindowShouldClose() && m_Window != nullptr)
		{
			Frame();
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
