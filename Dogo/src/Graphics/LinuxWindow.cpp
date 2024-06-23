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

		Colormap colormap = XCreateColormap(display, root, visual, AllocNone);
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
		XSelectInput(display, window, ExposureMask | KeyPressMask);
//		
		m_IsRunning = true;
		return true;
	}
	
	void LinuxWindow::Shutdown()
	{
//		glXMakeCurrent(display, 0, 0);
////		glXDestroyContext(display, context);
//
//		XDestroyWindow(display, *window);
////		XFreeColormap(display, colormap);
//		XCloseDisplay(display);
//
//		gladLoaderUnloadGLX();
	}
	
	void LinuxWindow::OnUpdate()
	{
//		bool quit = false;
//		while (XPending(display)) {
//			XEvent xev;
//			XNextEvent(display, &xev);
//
//			if (xev.type == KeyPress) {
//				quit = true;
//			}
//		}
//
//		glClearColor(0.8, 0.6, 0.7, 1.0);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		glXSwapBuffers(display, *window);
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