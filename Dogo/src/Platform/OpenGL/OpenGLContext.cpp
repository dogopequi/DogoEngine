#include "dgpch.h"
#include "Dogo/Logger.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
namespace Dogo
{
	OpenGLContext::OpenGLContext()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		if (!gladLoadGL()) {
			DG_WARN("Failed to initialize Glad!");
			return;
		}
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
	void OpenGLContext::Finish()
	{
		glFinish();
	}
	void OpenGLContext::ClearColor(float x, float y, float z, float a)
	{
		glClearColor(x, y, z, a);
	}
	void OpenGLContext::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void OpenGLContext::Viewport(int x, int y, int z, int a)
	{
		glViewport(x, y, z, a);
	}
}