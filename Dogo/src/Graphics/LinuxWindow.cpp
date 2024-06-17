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

		int glx_version = gladLoaderLoadGLX(display, screen);
		if (!glx_version)
		{
			DG_ERROR("Failed to load GLX");
			return false;
		}

		DG_INFO("Loaded GLX %d, %d", GLAD_VERSION_MAJOR(glx_version), GLAD_VERSION_MINOR(glx_version));

		GLint visual_attributes[] = 
		{
		 GLX_RENDER_TYPE, GLX_RGBA_BIT,
		 GLX_DOUBLEBUFFER, 1,
		 None
		};

		int num_fbc = 0;
		GLXFBConfig* fbc = glXChooseFBConfig(display, screen, visual_attributes, &num_fbc);

		GLint context_attributes[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		 GLX_CONTEXT_MINOR_VERSION_ARB, 3,
		 GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None
		};

		GLXContext context =
			glXCreateContextAttribsARB(display, fbc[0], NULL, 1, context_attributes);
		if (!context) {
			DG_ERROR("Unable to create OpenGL context.");
			return false;
		}

		glXMakeCurrent(display, window, context);

		int gl_version = gladLoaderLoadGL();
		if (!gl_version) {
			DG_ERROR("Unable to load GL.");
			return false;
		}

		DG_INFO("Loaded GL %d, %d", GLAD_VERSION_MAJOR(gl_version), GLAD_VERSION_MINOR(gl_version));

		XWindowAttributes gwa;
		XGetWindowAttributes(display, window, &gwa);
		glViewport(0, 0, gwa.width, gwa.height);

		// Select input events we are interested in
		XSelectInput(display, window, ExposureMask | KeyPressMask);

		// Map (show) the window
		XMapWindow(display, window);
		
		m_IsRunning = true;
	}
	
	void LinuxWindow::Shutdown()
	{
		glXMakeCurrent(display, 0, 0);
		glXDestroyContext(display, context);

		XDestroyWindow(display, window);
		XFreeColormap(display, colormap);
		XCloseDisplay(display);

		gladLoaderUnloadGLX();
	}
	
	void LinuxWindow::OnUpdate()
	{
		while (XPending(display)) {
			XEvent xev;
			XNextEvent(display, &xev);

			if (xev.type == KeyPress) {
				quit = true;
			}
		}

		glClearColor(0.8, 0.6, 0.7, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glXSwapBuffers(display, window);
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