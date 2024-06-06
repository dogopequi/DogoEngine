#pragma once
#include "Dogo/Core.h"
#include "Graphics/Window.h"
#include "LayerStack.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Graphics/WindowsWindow.h"
namespace Dogo
{
	using namespace DirectX;
	class DG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();
		void OnEvent(Event& e);
#if DG_PLATFORM_WINDOWS
		void SetWindowsInstance(HINSTANCE instance);
#endif
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool KeyPressedCallBack(KeyPressedEvent& e);
		bool KeyReleasedCallBack(KeyReleasedEvent& e);
		bool MouseMovedCallBack(MouseMovedEvent& e);
		bool MouseButtonPressedCallBack(MouseButtonPressedEvent& e);
		bool MouseButtonReleasedCallBack(MouseButtonReleasedEvent& e);
		bool MouseScrolledCallBack(MouseScrolledEvent& e);
	private:
		Window* m_Window;
		LayerStack m_LayerStack;

		bool m_IsRunning;


		//temp
		bool firstMouse = true;
		float yaw = 90.0f;
		float pitch = 0.0f;
		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;
		float fov = 45.0f;

		
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -5.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
#if DG_PLATFORM_WINDOWS
		HINSTANCE instance;
#endif
	};

	Application* CreateApplication();
}

