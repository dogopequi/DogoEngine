#include "dgpch.h"
#include "Dogo/Logger.h"
#include "OpenGLContext.h"
namespace Dogo
{
	OpenGLContext::OpenGLContext()
	{
			
	}
	OpenGLContext::~OpenGLContext()
	{
		Shutdown();
	}

	void OpenGLContext::SwapBuffer()
	{
	}
	bool OpenGLContext::Init()
	{
		DG_INFO("OpenGL Info:");
		DG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		DG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		DG_INFO("  Version: %s", glGetString(GL_VERSION));

		return true;
	}
	void OpenGLContext::Shutdown()
	{
	}
	void OpenGLContext::ClearColor(float x, float y, float z, float a)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(x, y, z, a);
	}
}