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

		virtual void Run() = 0;
		virtual void OnEvent(Event& e);

	protected:
		virtual bool OnWindowClose(WindowCloseEvent& e);
		virtual bool KeyPressedCallBack(KeyPressedEvent& e);
		virtual bool KeyReleasedCallBack(KeyReleasedEvent& e);
		virtual bool MouseMovedCallBack(MouseMovedEvent& e);
		virtual bool MouseButtonPressedCallBack(MouseButtonPressedEvent& e);
		virtual bool MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e);
		virtual bool MouseScrolledCallBack(MouseScrolledEvent& e);
	protected:
		inline static DogoWindow* m_Window;
		inline static LayerStack m_LayerStack;

		bool m_IsRunning;


		////temp
		//bool firstMouse = true;
		//float lastX = 800.0f / 2.0;
		//float lastY = 600.0 / 2.0;

		////temp
		//void processInput(float time);
		
		//std::shared_ptr<Camera> m_Camera;
	};
	Application* CreateApplication();
}



