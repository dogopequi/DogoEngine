#include "dgpch.h"
#include "Window.h"
#include "Dogo/Utils/Logger.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace Dogo
{
	Window::Window(int width, int height, std::string_view name)
	{
		m_Width = width;
		m_Height = height;
		m_Name = name;

		if (!glfwInit())
		{
			DG_ERROR("Failed to initialize GLFW");
			return;
		}
		m_Window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
		if (!m_Window)
		{
			DG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}		
		glfwMakeContextCurrent(m_Window);
		GraphicsContext::Init();
		glfwSetErrorCallback(ErrorCallback);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetKeyCallback(m_Window, KeyCallback);
		glfwSetMouseButtonCallback(m_Window, MouseButtonCallback);
		glfwSetCursorPosCallback(m_Window, CursorPositionCallback);
		glfwSetScrollCallback(m_Window, ScrollCallback);
		glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();
		float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
		// Setup scaling
		ImGuiStyle& style = ImGui::GetStyle();
		style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
		style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		m_IsRunning = true;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	bool Window::WindowShouldClose() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	double Window::GetTime() const
	{
		return glfwGetTime();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
	void Window::Viewport(int x, int y, int z, int a)
	{
		GraphicsContext::Viewport(x, y, z, a);
	}
	void Window::SwapInterval(uint32_t interval)
	{
		glfwSwapInterval(interval);
	}

	void Window::ClearColor(float x, float y, float z, float a)
	{
		GraphicsContext::ClearColor(x, y, z, a);
	}

	void Window::ClearBuffers()
	{
		GraphicsContext::ClearBuffers();
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::ErrorCallback(int error, const char* description)
	{
		DG_ERROR("GLFW Error [%d]: {%s}", error, description);
	}

	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (action == GLFW_PRESS) {
			Input::ProcessKey(key, true);
			KeyPressedEvent e(key, false);
			w->GetEventCallback()(e);
		}
		else if (action == GLFW_RELEASE) {
			Input::ProcessKey(key, false);
			KeyReleasedEvent e(key);
			w->GetEventCallback()(e);
		}
		//else if (action == GLFW_REPEAT) {
		//	Input::ProcessKey(key, true);
		//	KeyPressedEvent e(key, true);
		//	Window->GetEventCallback()(e);
		//}
	}

	void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS) {
			Input::ProcessButton(button, true);
			MouseButtonPressedEvent e(button, false);
			w->GetEventCallback()(e);
		}
		else if (action == GLFW_RELEASE) {
			Input::ProcessButton(button, false);
			MouseButtonReleasedEvent e(button);
			w->GetEventCallback()(e);
		}
		else if (action == GLFW_REPEAT) {
			Input::ProcessButton(button, true);
			MouseButtonPressedEvent e(button, true);
			w->GetEventCallback()(e);
		}
	}

	void Window::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::ProcessMousePos({ (int32_t)xpos, (int32_t)ypos });
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		MouseMovedEvent e((uint32_t)xpos, (uint32_t)ypos);
		w->GetEventCallback()(e);
	}

	void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Input::ProcessMouseScroll({ (int32_t)xoffset, (int32_t)yoffset });
		Input::ProcessMouseScrollDelta((int32_t)yoffset);
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		MouseScrolledEvent e(xoffset, yoffset);
		w->GetEventCallback()(e);
	}

	void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		w->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		w->ClearBuffers();
		w->SetHeight(height);
		w->SetWidth(width);
		w->Viewport(0, 0, width, height);
		WindowResizeEvent e(width, height);
		w->GetEventCallback()(e);
	}

	void Window::WindowCloseCallback(GLFWwindow* window)
	{
		Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent e;
		w->GetEventCallback()(e);
	}
}
