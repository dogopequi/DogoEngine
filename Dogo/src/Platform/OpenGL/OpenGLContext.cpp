#include "dgpch.h"
#include "Dogo/Logger.h"
#include "OpenGLContext.h"
#include "Graphics/Window.h"
#include "glad/glad.h"
namespace Dogo
{
	OpenGLContext::OpenGLContext(HWND* handle)
	{
		windowHandle = handle;
	}
	OpenGLContext::~OpenGLContext()
	{
		delete windowHandle;
	}
	bool OpenGLContext::Init()
	{
		m_HDC = GetDC(*windowHandle);

		m_PFD = { sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
		m_Format = ChoosePixelFormat(m_HDC, &m_PFD);
		SetPixelFormat(m_HDC, m_Format, &m_PFD);

		m_HRC = wglCreateContext(m_HDC);
		wglMakeCurrent(m_HDC, m_HRC);

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
		SwapBuffers(m_HDC);
	}
	void OpenGLContext::Shutdown()
	{
		if (m_HRC) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(m_HRC);
			m_HRC = NULL;
		}
		if (m_HDC) {
			ReleaseDC(*windowHandle, m_HDC);
			m_HDC = NULL;
		}
	}
	void OpenGLContext::ClearColor(float x, float y, float z, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(x, y, z, a);
	}
}