#include "dgpch.h"
#include "Dogo/Core.h"
#include "Dogo/Logger.h"
#include "WindowsWindow.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Input/WindowsInput.h"
#include "Dogo/Events/MouseEvent.h"

#if DG_PLATFORM_WINDOWS
	namespace Dogo
	{
	std::map<HWND, WindowsWindow*> WindowsWindow::s_Handles;
	Window* Window::Create(const WindowAttrib& attrib)
	{
		return new WindowsWindow(attrib);
	}

	WindowsWindow* WindowsWindow::GetWindowClass(HWND handle)
	{
		if (handle == nullptr)
			return s_Handles.begin()->second;

		return s_Handles[handle];
	}
	void WindowsWindow::RegisterWindowClass(HWND handle, WindowsWindow* window)
	{
		s_Handles[handle] = window;
	}

	LRESULT CALLBACK Win32ProcessMessage(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
	{
		LRESULT result = NULL;
		WindowsWindow* window = WindowsWindow::GetWindowClass(hwnd);
		if (window == nullptr)
			return DefWindowProcA(hwnd, msg, wparam, lparam);
		switch (msg) 
		{
		case WM_ERASEBKGND:
			// Notify the OS that erasing will be handled by the application to prevent flicker.
			return 1;
		case WM_CLOSE:
		{
			WindowResizeEvent e1(10, 10);
			WindowCloseEvent e;
			window->GetEventCallback()(e);
			PostQuitMessage(0);
			DestroyWindow(hwnd); // or PostQuitMessage(0);
			window->StopRunning();
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			window->StopRunning();
			return 0;
		case WM_SIZE: 
		{
			// Get the updated size.
			// RECT r;
			// GetClientRect(hwnd, &r);
			// u32 width = r.right - r.left;
			// u32 height = r.bottom - r.top;

			// TODO: Fire an event for window resize.
		} break;
		case WM_KEYDOWN:
		{
			int32_t key = (int32_t)wparam;
			Input::ProcessKey(key, true);
			bool repeat;
			if (Input::GetKeyState() == KeyState::REPEAT) { repeat = true; }
			else { repeat = false; }
			KeyPressedEvent e(int32_t(wparam), repeat);
			window->GetEventCallback()(e);

		}break;
		case WM_SYSKEYDOWN:
		{
			int32_t key = (int32_t)wparam;
			Input::ProcessKey(key, true);
			bool repeat;
			if (Input::GetKeyState() == KeyState::REPEAT) { repeat = true; }
			else { repeat = false; }
			KeyPressedEvent e(int32_t(wparam), repeat);
			window->GetEventCallback()(e);

		}break;
		case WM_KEYUP:
		{
			int32_t key = (int32_t)wparam;
			Input::ProcessKey(key, false);
			KeyReleasedEvent e((wparam));
			window->GetEventCallback()(e);
		}break;
		case WM_SYSKEYUP: 
		{
			int32_t key = (int32_t)wparam;
			Input::ProcessKey(key, false);
			KeyReleasedEvent e((wparam));
			window->GetEventCallback()(e);
		} break;
		case WM_MOUSEMOVE: 
		{
			int32_t x_position = GET_X_LPARAM(lparam);
			int32_t y_position = GET_Y_LPARAM(lparam);
			Input::ProcessMousePos(std::make_pair(x_position, y_position));
			MouseMovedEvent e(x_position, y_position);
			window->GetEventCallback()(e);
		} break;
		case WM_MOUSEWHEEL: 
		{
			int32_t delta = GET_WHEEL_DELTA_WPARAM(wparam);
			delta = delta / 25;
			Input::ProcessMouseScrollDelta(delta);
			int32_t xPos = GET_X_LPARAM(lparam);
			int32_t yPos = GET_Y_LPARAM(lparam);
			Input::ProcessMouseScroll(std::make_pair(xPos, yPos));

			MouseScrolledEvent e(xPos, yPos);
			window->GetEventCallback()(e);
			//if (delta > 0) {
			//	// Scroll up
			//	SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0);
			//}
			//else if (delta < 0) {
			//	// Scroll down
			//	SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0);
			//}
		} break;
		case WM_LBUTTONDOWN:
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_1, true);
			bool repeat;
			if (Input::GetButtonState() == ButtonState::REPEAT) { repeat = true; }
			else { repeat = false; }
			MouseButtonPressedEvent e(int32_t(wparam), repeat);
			window->GetEventCallback()(e);
		}break;
		case WM_MBUTTONDOWN:
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_2, true);
			bool repeat;
			if (Input::GetButtonState() == ButtonState::REPEAT) { repeat = true; }
			else { repeat = false; }
			MouseButtonPressedEvent e(int32_t(wparam), repeat);
			window->GetEventCallback()(e);
		}break;
		case WM_RBUTTONDOWN:
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_3, true);
			bool repeat;
			if (Input::GetButtonState() == ButtonState::REPEAT) { repeat = true; }
			else { repeat = false; }
			MouseButtonPressedEvent e(int32_t(wparam), repeat);
			window->GetEventCallback()(e);
		}break;
		case WM_LBUTTONUP:
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_1, false);
			MouseButtonReleasedEvent e((DG_MOUSE_BUTTON_1));
			window->GetEventCallback()(e);
		}break;
		case WM_MBUTTONUP:
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_2, false);
			MouseButtonReleasedEvent e((DG_MOUSE_BUTTON_2));
			window->GetEventCallback()(e);
		}break;
		case WM_RBUTTONUP: 
		{
			Input::ProcessButton(DG_MOUSE_BUTTON_3, false);
			MouseButtonReleasedEvent e((DG_MOUSE_BUTTON_3));
			window->GetEventCallback()(e);
		} break;
		}
		return DefWindowProcA(hwnd, msg, wparam, lparam);
	}

	static float frequency;
	static LARGE_INTEGER startTime;

	WindowsWindow::WindowsWindow(const WindowAttrib& attrib)
	{
		DG_INFO("Created Window");
		m_Data = attrib;
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
			WindowsMessages();

			if (m_IsRunning)
				m_Context->SwapBuffer();
	}

	void WindowsWindow::WindowSleep(float ms) const
	{
		Sleep(ms);
	}

	float WindowsWindow::GetClock() const
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return (float)currentTime.QuadPart * frequency;
	}

	void WindowsWindow::SetVsync(bool b)
	{
		m_VSync = b;
	}

	bool WindowsWindow::WindowsMessages()
	{
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		return true;
	}

	bool WindowsWindow::InitContext()
	{
#if OPENGL
		GraphicsContext::Create(&m_Hwnd, RenderAPI::OpenGL);
#endif
#if DX11
		GraphicsContext::Create(&m_Hwnd, RenderAPI::D3D11);
#endif
		m_Context = GraphicsContext::Get();
		if (!m_Context->Init())
			return false;

		return true;
	}

	bool WindowsWindow::Init()
	{
		m_IsRunning = true;
		m_Name = m_Data.Name;
		m_Width = m_Data.Width;
		m_Height = m_Data.Height;

		m_Instance = GetModuleHandleA(0);

		HICON icon = LoadIcon(m_Instance, IDI_APPLICATION);
		WNDCLASSA wc = { 0 };
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = Win32ProcessMessage;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_Instance;
		wc.hIcon = icon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszClassName = "Dogo Window";

		if (!RegisterClassA(&wc))
		{
			MessageBoxA(NULL, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
			DG_FATAL("Failed to register window");
			return false;
		}

		uint32_t clientX = x;
		uint32_t clientY = y;
		uint32_t clientWidth = m_Width;
		uint32_t clientHeight = m_Height;

		uint32_t windowX = clientX;
		uint32_t windowY = clientY;
		uint32_t windowWidth = clientWidth;
		uint32_t windowHeight = clientHeight;

		uint32_t windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		uint32_t windowExStyle = WS_EX_APPWINDOW;

		windowStyle |= WS_MAXIMIZEBOX;
		windowStyle |= WS_MINIMIZEBOX;
		windowStyle |= WS_THICKFRAME;

		RECT borderRect = { 0, 0, 0, 0 };
		AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);

		windowX += borderRect.left;
		windowY += borderRect.right;
		windowWidth += borderRect.right - borderRect.left;
		windowHeight += borderRect.bottom - borderRect.top;

		HWND handle = CreateWindowExA(windowExStyle, "Dogo Window", "Dogo Window", windowStyle, windowX, windowY, windowWidth, windowHeight, 0, 0, m_Instance, this);

		if (handle == 0)
		{
			DWORD error = GetLastError();
			DG_FATAL("Failed to create window handle. Error code: %i", error);
			MessageBoxA(NULL, "Failed to create handle", "Error", MB_ICONEXCLAMATION | MB_OK);
			DG_FATAL("Failed to create handle for window");
			return false;
		}
		else
		{
			m_Hwnd = handle;
			RegisterWindowClass(m_Hwnd, this);
		}

		bool shouldActivate = false;
		int32_t showWindowComandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
		//TODO: handle maximization and minimization
		ShowWindow(m_Hwnd, showWindowComandFlags);

		LARGE_INTEGER f;
		QueryPerformanceFrequency(&f);
		frequency = 1.0 / (float)f.QuadPart;
		QueryPerformanceCounter(&startTime);

		return true;
	}

	void WindowsWindow::ClearColor(float x, float y, float z, float a)
	{
		m_Context->ClearColor(x, y, z, a);
	}

	void WindowsWindow::LockCursor()
	{
		RECT rect;
		GetClientRect(m_Hwnd, &rect); // Get the dimensions of the window

		// Convert client-area coordinates to screen coordinates
		POINT upperLeft = { rect.left, rect.top };
		POINT bottomRight = { rect.right, rect.bottom };
		ClientToScreen(m_Hwnd, &upperLeft);
		ClientToScreen(m_Hwnd, &bottomRight);

		// Create a rectangle that represents the window area
		RECT windowRect = { upperLeft.x, upperLeft.y, bottomRight.x, bottomRight.y };

		// Lock the cursor to the window
		ClipCursor(&windowRect);

		// Hide the cursor
		//ShowCursor(FALSE);
	}

	void WindowsWindow::UnlockCursor()
	{
		ClipCursor(NULL);

		// Show the cursor
		ShowCursor(TRUE);
	}

	void WindowsWindow::Shutdown()
	{
		m_IsRunning = false;
		m_Context->Shutdown();
		if (m_Hwnd)
		{
			DestroyWindow(m_Hwnd);
			m_Hwnd = 0;
		}
	}
	}
#endif