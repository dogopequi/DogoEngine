#include "dgpch.h"
#include "Dogo/Logger.h"
#include "OpenGLContext.h"
#include "Graphics/Window.h"
namespace Dogo
{
#if DG_PLATFORM_WINDOWS
	OpenGLContext::OpenGLContext(HWND* handle)
	{
		windowHandle = handle;
	}
#else
	OpenGLContext::OpenGLContext(Display *dpy, Visual* vi, int screen, const Window& window)
	{
		display = dpy;
		visual = vi;
		this->screen = screen;
		this->window = window;
	}
	#endif
	OpenGLContext::OpenGLContext()
	{
			
	}
	OpenGLContext::~OpenGLContext()
	{
		Shutdown();
		#if DG_PLATFORM_WINDOWS
		delete windowHandle;
		#endif
	}

	void OpenGLContext::SwapBuffer()
	{
		#if DG_PLATFORM_WINDOWS
		SwapBuffers(m_HDC);
		#endif
		#if DG_PLATFORM_LINUX
		glXSwapBuffers(display, window);
		#endif
	}
	bool OpenGLContext::Init()
	{
#if DG_PLATFORM_WINDOWS
		m_HDC = GetDC(*windowHandle);

		m_PFD = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
		m_Format = ChoosePixelFormat(m_HDC, &m_PFD);
		SetPixelFormat(m_HDC, m_Format, &m_PFD);

		m_HRC = wglCreateContext(m_HDC);
		wglMakeCurrent(m_HDC, m_HRC);
#endif
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
		GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
		 GLX_CONTEXT_MINOR_VERSION_ARB, 6,
		 GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
		None
		};

		context =
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


		DG_INFO("OpenGL Info:");
		DG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		DG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		DG_INFO("  Version: %s", glGetString(GL_VERSION));

		return true;
	}
	void OpenGLContext::Shutdown()
	{
#if DG_PLATFORM_WINDOWS
		if (m_HRC) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_HRC);
			m_HRC = NULL;
		}
		if (m_HDC) {
			ReleaseDC(*windowHandle, m_HDC);
			m_HDC = NULL;
		}
#endif
#if DG_PLATFORM_LINUX
		glXMakeCurrent(display, 0, 0);
		glXDestroyContext(display, context);
		gladLoaderUnloadGLX();
#endif

	}
	void OpenGLContext::ClearColor(float x, float y, float z, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(x, y, z, a);
	}
}