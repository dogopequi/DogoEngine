#include "dgpch.h"
#include "LinuxWindow.h"
#if DG_PLATFORM_LINUX
#include "Dogo/Core.h"
#include "Dogo/Logger.h"

namespace Dogo
{
	DG_Window* DG_Window::Create(const WindowAttrib& attrib)
	{
		return new LinuxWindow(attrib);
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
		
		m_IsRunning = true;
		return true;
	}
	
	void LinuxWindow::Shutdown()
	{
		XDestroyWindow(display, window);
		XFreeColormap(display, colormap);
		XCloseDisplay(display);
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
                    DG_INFO("Key pressed: %i",  XLookupKeysym(&xev.xkey, 0));
                    if (XLookupKeysym(&xev.xkey, 0) == XK_Escape) {
                        quit = true;
                    }
				}
                break;

                case KeyRelease:
                    {
						DG_INFO("Key released: %i",  XLookupKeysym(&xev.xkey, 0));
					}
                    break;

                case ButtonPress:
				{
                    DG_INFO("Button pressed: ", xev.xbutton.button);
                    if (xev.xbutton.button == Button1) { // Left mouse button
                        DG_INFO("Left mouse button pressed at %i, %i", xev.xbutton.x, xev.xbutton.y);
                    } else if (xev.xbutton.button == Button4) { // Mouse wheel up
                        DG_INFO("Mouse wheel up");
                    } else if (xev.xbutton.button == Button5) { // Mouse wheel down
                        DG_INFO("Mouse wheel down");
                    }
				}
                    break;

                case ButtonRelease:
                { 
					DG_INFO("Button released: %i", xev.xbutton.button);
				}
                    break;

                case MotionNotify:
				{
                    DG_INFO("Mouse moved to: %i, %i", xev.xmotion.x, xev.xmotion.y);
				}
                    break;

                case ConfigureNotify:
				{
                    DG_INFO("Window resized to %i, %i", xev.xconfigure.width, xev.xconfigure.height);
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
		
	}
	
	float LinuxWindow::GetClock() const
	{
		
	}
	
	void LinuxWindow::SetVsync(bool b)
	{
		
	}

	//TODO
}
#endif