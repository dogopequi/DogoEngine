#include "dgpch.h"
#include "Dogo/Logger.h"
#include "OpenGLContext.h"
#include "Graphics/Window.h"
#include "glad/glad.h"
namespace Dogo
{
#if DG_PLATFORM_WINDOWS
	OpenGLContext::OpenGLContext(HWND* handle)
	{
		windowHandle = handle;
	}
#endif
	OpenGLContext::~OpenGLContext()
	{
		#if DG_PLATFORM_WINDOWS
		delete windowHandle;
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

		if (!gladLoadGL()) {
			DG_WARN("Failed to initialize Glad!");
			return false;
		}

		DG_INFO("OpenGL Info:");
		DG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		DG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		DG_INFO("  Version: %s", glGetString(GL_VERSION));

		return true;
	}
	void OpenGLContext::SwapBuffer()
	{
		#if DG_PLATFORM_WINDOWS
		SwapBuffers(m_HDC);
		#endif
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
	}
	void OpenGLContext::ClearColor(float x, float y, float z, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(x, y, z, a);
	}
}