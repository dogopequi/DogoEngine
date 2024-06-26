#include "dgpch.h"
#include "LinuxWindow.h"
#if DG_PLATFORM_LINUX
#include "Dogo/Core.h"
#include "Dogo/Logger.h"
#include "Dogo/Events/ApplicationEvent.h"
#include "Dogo/Events/KeyEvent.h"
#include "Dogo/Input/WindowsInput.h"
#include "Dogo/Events/MouseEvent.h"

namespace Dogo
{
	DG_Window* DG_Window::Create(const WindowAttrib& attrib)
	{
		return new LinuxWindow(attrib);
	}

	std::map<const char* , LinuxWindow*> LinuxWindow::s_Handles;

	LinuxWindow* LinuxWindow::GetWindowClass(const char*  handle)
	{
		if (handle == nullptr)
			return s_Handles.begin()->second;

		return s_Handles[handle];
	}
	void LinuxWindow::RegisterWindowClass(const char*  handle, LinuxWindow* window)
	{
		s_Handles[handle] = window;
	}
	
	LinuxWindow::LinuxWindow(const WindowAttrib& attrib)
	{
		Init(attrib);
	}
	
	LinuxWindow::~LinuxWindow()
	{
		Shutdown();
	}
	
	bool LinuxWindow::Init(const WindowAttrib& attrib)
	{
		display = XOpenDisplay(NULL);
		if (display == NULL)
		{
			DG_ERROR("Cannot connect to X Server");
			return false;
		}

		screen = DefaultScreen(display);
		root = RootWindow(display, screen);
		visual = DefaultVisual(display, screen);

		colormap = XCreateColormap(display, root, visual, AllocNone);
		XSetWindowAttributes attributes;
		attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask;
		attributes.colormap = colormap;

		window = XCreateWindow(display, root, 0, 0, attrib.Width, attrib.Height, 0, DefaultDepth(display, screen), InputOutput, visual, CWColormap | CWEventMask, &attributes);
		XMapWindow(display, window);
		XStoreName(display, window, attrib.Name.c_str());

		if (!window)
		{
			DG_ERROR("Failed to create window");
			return false;
		}
		
		InitContext();

		// Select input events we are interested in
		XSelectInput(display, window, ExposureMask | KeyPressMask | KeyReleaseMask |
                                ButtonPressMask | ButtonReleaseMask | PointerMotionMask | 
                                StructureNotifyMask);

		RegisterWindowClass(attrib.Name.c_str(), this);
		
		m_IsRunning = true;
		return true;
	}
	
	void LinuxWindow::Shutdown()
	{
		XDestroyWindow(display, window);
		XFreeColormap(display, colormap);
		XCloseDisplay(display);
	}

	void LinuxWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		EventCallback = callback;
		// if (EventCallback) {
		// 	std::cout << " Event callback set!!!!!!";
        // } else {
        // std::cout << "No event callback set!!!!!!";}
	}
	
	void LinuxWindow::OnUpdate()
	{
		bool quit = false;
		while (XPending(display)) 
		{
			XEvent xev;
			XNextEvent(display, &xev);

 			switch (xev.type) {
                case Expose:
				{   // Handle window expose event (redraw)
                    DG_INFO("Window exposed");
				}
                break;
                case KeyPress:
				{
                    //DG_INFO("Key pressed: %i",  XLookupKeysym(&xev.xkey, 0));
                    KeySym keysym = XLookupKeysym(&xev.xkey, 0);
					int32_t key = (int32_t)keysym;
					Input::ProcessKey(key, true);
					bool repeat;
					if (Input::GetKeyState() == KeyState::REPEAT) { repeat = true; }
					else { repeat = false; }
					KeyPressedEvent e(key, repeat);
					if (GetEventCallback()) {
               		 GetEventCallback()(e);;
           		 	} else {
               		 DG_INFO("No event callback set!");}
            	}break;
					//GetEventCallback()(e);
                break;
                case KeyRelease:
                {
					// DG_INFO("Key released: %i",  XLookupKeysym(&xev.xkey, 0));
					KeySym keysym = XLookupKeysym(&xev.xkey, 0);
					int32_t key = (int32_t)keysym;
					Input::ProcessKey(key, true);
					KeyReleasedEvent e(key);
					GetEventCallback()(e);
				}
                break;

                case ButtonPress:
				{
                    // DG_INFO("Button pressed: ", xev.xbutton.button);
                    // if (xev.xbutton.button == Button1) { // Left mouse button
                    //     DG_INFO("Left mouse button pressed at %i, %i", xev.xbutton.x, xev.xbutton.y);
                    // } else if (xev.xbutton.button == Button4) { // Mouse wheel up
                    //     DG_INFO("Mouse wheel up");
                    // } else if (xev.xbutton.button == Button5) { // Mouse wheel down
                    //     DG_INFO("Mouse wheel down");
                    // }
					switch(xev.xbutton.button)
					{
						case 4:
						{
							int xPos = xev.xbutton.x;
                    		int yPos = xev.xbutton.y;
							// DG_INFO("Mouse wheel scrolled up at position (%d, %d)", xPos, yPos);
							int32_t delta = 120; // x11 doesnt have delta? preposturous
							delta = delta / 25;
							Input::ProcessMouseScrollDelta(delta);
							Input::ProcessMouseScroll(std::make_pair(xPos, yPos));
							MouseScrolledEvent e(xPos, yPos);
							GetEventCallback()(e);
						}break;
						case 5:
						{
							int xPos = xev.xbutton.x;
                   			int yPos = xev.xbutton.y;
							// DG_INFO("Mouse wheel scrolled down at position (%d, %d)", xPos, yPos);
							int32_t delta = 120; // x11 doesnt have delta? preposturous
							delta = delta / 25;
							Input::ProcessMouseScrollDelta(delta);
							Input::ProcessMouseScroll(std::make_pair(xPos, yPos));
							MouseScrolledEvent e(xPos, yPos);
							GetEventCallback()(e);
						}break;
						default:
						{
							int32_t key = (int32_t)xev.xbutton.button;
							Input::ProcessButton(key, true);
							bool repeat;
							if (Input::GetButtonState() == ButtonState::REPEAT) { repeat = true; }
							else { repeat = false; }
							MouseButtonPressedEvent e(key, repeat);
							GetEventCallback()(e);
						}break;
					}
				}
                break;

                case ButtonRelease:
                { 
					// DG_INFO("Button released: %i", xev.xbutton.button);
					int32_t key = (int32_t)xev.xbutton.button;
					Input::ProcessButton(key, true);
					MouseButtonReleasedEvent e(key);
					GetEventCallback()(e);
				}
                    break;

                case MotionNotify:
				{
                    // DG_INFO("Mouse moved to: %i, %i", xev.xmotion.x, xev.xmotion.y);
					int32_t x_position = xev.xmotion.x;
					int32_t y_position = xev.xmotion.y;
					Input::ProcessMousePos(std::make_pair(x_position, y_position));
					MouseMovedEvent e(x_position, y_position);
					GetEventCallback()(e);
				}
                    break;

                case ConfigureNotify:
				{
                    // DG_INFO("Window resized to %i, %i", xev.xconfigure.width, xev.xconfigure.height);
				}
                break;

                default:
                    break;
            }
		}
		if (m_IsRunning)
			m_Context->SwapBuffer();
	}
	
	void LinuxWindow::WindowSleep(float ms) const
	{
		return;
	}
	
	float LinuxWindow::GetClock() const
	{
		return 1.0f;
	}
	
	void LinuxWindow::SetVsync(bool b)
	{
		return;
	}

	//TODO
}
#endif