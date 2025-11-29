#include "dgpch.h"
#include "DogoWindow.h"
#include "Dogo/Utils/Logger.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
namespace Dogo
{
	DogoWindow::DogoWindow(int width, int height, std::string_view name)
	{
		m_Width = width;
		m_Height = height;
		m_Name = name;

		if (!glfwInit())
		{
			DG_ERROR("Failed to initialize GLFW");
			return;
		}
		GraphicsContext::Create(RenderAPI::OpenGL);
		window = glfwCreateWindow(width, height, name.data(), nullptr, nullptr);
		if (!window)
		{
			DG_ERROR("Failed to create GLFW window");
			glfwTerminate();
			return;
		}		
		glfwMakeContextCurrent(window);
		m_Context = GraphicsContext::Get();
		m_Context->Init();
		glfwSetErrorCallback(ErrorCallback);
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, CursorPositionCallback);
		glfwSetScrollCallback(window, ScrollCallback);
		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		glfwSetWindowCloseCallback(window, WindowCloseCallback);

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
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		m_IsRunning = true;
	}

	DogoWindow::~DogoWindow()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	bool DogoWindow::WindowShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	double DogoWindow::GetTime() const
	{
		return glfwGetTime();
	}

	void DogoWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
	void DogoWindow::Viewport(int x, int y, int z, int a)
	{
		m_Context->Viewport(x, y, z, a);
	}
	void DogoWindow::SwapInterval(uint32_t interval)
	{
		glfwSwapInterval(interval);
	}

	void DogoWindow::ClearColor(float x, float y, float z, float a)
	{
		m_Context->ClearColor(x, y, z, a);
	}

	void DogoWindow::ClearBuffers()
	{
		m_Context->ClearBuffers();
	}

	void DogoWindow::PollEvents()
	{
		glfwPollEvents();
	}

	void DogoWindow::ErrorCallback(int error, const char* description)
	{
		DG_ERROR("GLFW Error [%d]: {%s}", error, description);
	}

	void DogoWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));
		if (action == GLFW_PRESS) {
			Input::ProcessKey(key, true);
			KeyPressedEvent e(key, false);
			dogoWindow->GetEventCallback()(e);
		}
		else if (action == GLFW_RELEASE) {
			Input::ProcessKey(key, false);
			KeyReleasedEvent e(key);
			dogoWindow->GetEventCallback()(e);
		}
		//else if (action == GLFW_REPEAT) {
		//	Input::ProcessKey(key, true);
		//	KeyPressedEvent e(key, true);
		//	dogoWindow->GetEventCallback()(e);
		//}
	}

	void DogoWindow::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS) {
			Input::ProcessButton(button, true);
			MouseButtonPressedEvent e(button, false);
			dogoWindow->GetEventCallback()(e);
		}
		else if (action == GLFW_RELEASE) {
			Input::ProcessButton(button, false);
			MouseButtonReleasedEvent e(button);
			dogoWindow->GetEventCallback()(e);
		}
		else if (action == GLFW_REPEAT) {
			Input::ProcessButton(button, true);
			MouseButtonPressedEvent e(button, true);
			dogoWindow->GetEventCallback()(e);
		}
	}

	void DogoWindow::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		Input::ProcessMousePos({ (int32_t)xpos, (int32_t)ypos });
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));
		MouseMovedEvent e((uint32_t)xpos, (uint32_t)ypos);
		dogoWindow->GetEventCallback()(e);
	}

	void DogoWindow::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Input::ProcessMouseScroll({ (int32_t)xoffset, (int32_t)yoffset });
		Input::ProcessMouseScrollDelta((int32_t)yoffset);
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));
		MouseScrolledEvent e(xoffset, yoffset);
		dogoWindow->GetEventCallback()(e);
	}

	void DogoWindow::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));
		dogoWindow->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		dogoWindow->ClearBuffers();
		dogoWindow->SetHeight(height);
		dogoWindow->SetWidth(width);
		dogoWindow->Viewport(0, 0, width, height);
		WindowResizeEvent e(width, height);
		dogoWindow->GetEventCallback()(e);
	}

	void DogoWindow::WindowCloseCallback(GLFWwindow* window)
	{
		DogoWindow* dogoWindow = static_cast<DogoWindow*>(glfwGetWindowUserPointer(window));
		WindowCloseEvent e;
		dogoWindow->GetEventCallback()(e);
	}
}
