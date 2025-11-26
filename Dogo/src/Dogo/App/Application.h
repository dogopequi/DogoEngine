#pragma once
#include "Dogo/Core.h"
#include "Dogo/App/LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Dogo/Events/Event.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Utils/ThreadPool.h"
#include "Dogo/Component/Components.h"
#include "Dogo/Renderer/Core/Camera.h"
#include "imgui.h"
namespace Dogo
{
	#if DG_PLATFORM_WINDOWS
	 
	#endif
	class DG_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void PushLayer(Layer* layer);
		virtual void PushOverlay(Layer* layer);

		virtual void Run() final;
	protected:
		virtual void Tick() = 0;
		virtual void OnWindowCloseEvent(WindowCloseEvent& e) {}
		virtual void OnKeyPressedEvent(KeyPressedEvent& e) {}
		virtual void OnKeyReleasedEvent(KeyReleasedEvent& e) {}
		virtual void OnMouseMovedEvent(MouseMovedEvent& e) {}
		virtual void OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {}
		virtual void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {}
		virtual void OnMouseScrolledEvent(MouseScrolledEvent& e) {}
		virtual void OnWindowResizeEvent(WindowResizeEvent& e) {}


	private:
		virtual void OnEvent(Event& e);
		void OnWindowClose(WindowCloseEvent& e);
		void KeyPressedCallBack(KeyPressedEvent& e);
		void KeyReleasedCallBack(KeyReleasedEvent& e);
		void MouseMovedCallBack(MouseMovedEvent& e);
		void MouseButtonPressedCallBack(MouseButtonPressedEvent& e);
		void MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e);
		void MouseScrolledCallBack(MouseScrolledEvent& e);
		void OnWindowResize(Dogo::WindowResizeEvent& e);
	protected:
		DogoECS::DG_EntityManager* entityManager;
		DogoECS::DG_ComponentManager* componentManager;
		std::shared_ptr<DogoWindow> m_Window;
		LayerStack m_LayerStack;
		std::shared_ptr<Renderer2D> m_Renderer;
		std::atomic<bool> m_Running{ true };
	private:
		void Frame();
	private:
		std::unique_ptr<Camera> m_Camera;
		ThreadPool m_Pool;
		double m_LastDelta = 0;

	};
	Application* CreateApplication();
}



