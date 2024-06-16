#include "dgpch.h"
#include "LinuxWindow.h"
#if DG_PLATFORM_LINUX
#include "Dogo/Core.h"
#include "Dogo/Logger.h"
#include <glad/glad.h>
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
		display = XOpenDisplay(nullptr);
		if(display == nullptr)
		{
			DG_FATAL("Cannot open display");
			return false;
		}
		screen = DefaultScreen(display);
		root = RootWindow(display, screen);
		GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
		vi = glXChooseVisual(display, 0, att);
		if (vi == NULL) {
			printf("No appropriate visual found\n");
		}
		Colormap cmap = XCreateColormap(display, root, vi->visual, AllocNone);
		XSetWindowAttributes swa;
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask;
		 window = XCreateWindow(display, 
		 root, 0, 0, 
		 attrib.Width, attrib.Height, 
		 0, vi->depth, 
		 InputOutput, 
		 vi->visual, 
		 CWColormap | CWEventMask, 
		 &swa);
		 
//		window = XCreateSimpleWindow(
//		display, root,
//		10, 10,
//		attrib.Width, attrib.Height,
//		1, BlackPixel(display, screen),
//		WhitePixel(display, screen)
//		);
		window = XCreateWindow(display, root, 0, 0, attrib.Width, attrib.Height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
		if (!window) {
			DG_ERROR("Failed to create window\n");
			return false;
		}
				const char *glxExtensions = glXQueryExtensionsString(display, screen);
		if (!glXQueryExtension(display, NULL, NULL)) {
			DG_ERROR("GLX extension not found");
			return false;
		}
// Check for specific GLX extensions required by GLAD
		if (!strstr(glxExtensions, "GLX_ARB_create_context")) {
			DG_ERROR("GLX_ARB_create_context extension not supported");
			return false;
		}
		    // Select input events we are interested in
		XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map (show) the window
		XMapWindow(display, window);
		
		m_IsRunning = true;
	}
	
	void LinuxWindow::Shutdown()
	{
		
	}
	
	void LinuxWindow::OnUpdate()
	{
	while (XPending(display)) 
    {
        XNextEvent(display, &event);
        if (event.type == Expose) 
        {
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
			glClearColor(0.0, 0.5, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            glXSwapBuffers(display, window);
        } 
        else if (event.type == KeyPress) 
        {
            // Handle the key press event appropriately
            // You can add specific key handling logic here
            return;
        }
    }
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