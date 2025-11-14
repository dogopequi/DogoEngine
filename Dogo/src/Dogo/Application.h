#pragma once
#include "Dogo/Core.h"
#include "LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Renderer/Camera.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/ThreadPool.h"
#include "Dogo/Component/Components.h"
namespace Dogo
{
	#if DG_PLATFORM_WINDOWS
	 
	#endif
	class DG_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

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
		DogoWindow* m_Window;
		LayerStack m_LayerStack;
		std::shared_ptr<Renderer2D> m_Renderer;
		std::atomic<bool> m_Running{ true };
	private:
		void DrawFrame();
	private:
		ThreadPool m_Pool;
	};
	Application* CreateApplication();
}



