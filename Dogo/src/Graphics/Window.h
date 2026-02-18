#pragma once
#include "Dogo/Core.h"
#include "Dogo/Events/Event.h"
#include "Platform/OpenGL/GraphicsContext.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Events/MouseEvent.h"
#define GLFW_INCLUDE_NONE
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
#include <GLFW/glfw3.h>
namespace Dogo
{
	using EventCallbackFn = std::function<void(Event&)>;
	class Window
	{
	public:
		Window(int width, int height, std::string_view name);
		~Window();

		bool WindowShouldClose() const;

		double GetTime() const;

		void SwapBuffers();
		inline uint32_t GetHeight() const { return m_Height; }
		inline uint32_t GetWidth() const { return m_Width; }
		inline void SetWidth(uint32_t width) { m_Width = width; }
		inline void SetHeight(uint32_t height) { m_Height = height; }
		void SwapInterval(uint32_t interval);
		void ClearColor(float x, float y, float z, float a);
		void ClearBuffers();
		void Viewport(int x, int y, int z, int a);
		void PollEvents();
		void SetEventCallback(const EventCallbackFn& callback) { EventCallback = callback; }
		inline EventCallbackFn GetEventCallback() const { return EventCallback; }

	private:
		GLFWwindow* m_Window;
		EventCallbackFn EventCallback;
		uint32_t m_Width{};
		uint32_t m_Height{};
		std::string m_Name{};
		bool m_IsRunning;
		static void ErrorCallback(int error, const char* description);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void WindowCloseCallback(GLFWwindow* window);


	};
}