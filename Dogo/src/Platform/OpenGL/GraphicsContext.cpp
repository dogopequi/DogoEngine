#include "dgpch.h"
#include "Dogo/Utils/Logger.h"
#include "GraphicsContext.h"
#include <GLFW/glfw3.h>
namespace Dogo
{

	void GraphicsContext::SwapBuffer()
	{
	}
	bool GraphicsContext::Init()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			DG_WARN("Failed to initialize Glad!");
			return false;
		}
		DG_INFO("OpenGL Info:");
		DG_INFO("  Vendor: %s", glGetString(GL_VENDOR));
		DG_INFO("  Renderer: %s", glGetString(GL_RENDERER));
		DG_INFO("  Version: %s", glGetString(GL_VERSION));

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const void* userParam)
			{
				// Filter noisy messages, or print all
				DG_FATAL("GL DEBUG: id=0x%x, severity=%d, message=%s\n", id, severity, message);
			}, nullptr);
		return true;
	}
	void GraphicsContext::Shutdown()
	{
	}
	void GraphicsContext::Finish()
	{
		glFinish();
	}
	void GraphicsContext::ClearColor(float x, float y, float z, float a)
	{
		glClearColor(x, y, z, a);
	}
	void GraphicsContext::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void GraphicsContext::Viewport(int x, int y, int z, int a)
	{
		glViewport(x, y, z, a);
	}
}