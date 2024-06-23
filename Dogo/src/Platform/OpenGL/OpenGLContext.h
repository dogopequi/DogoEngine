#pragma once
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif

#include "Graphics/GraphicsContext.h"
class DG_Window;

namespace Dogo
{
	class OpenGLContext : public GraphicsContext
	{
	public:
#if DG_PLATFORM_WINDOWS
		OpenGLContext(HWND* handle);
#else
		OpenGLContext(Display *dpy, Visual* vi, int screen, const Window& window);
		#endif
		OpenGLContext();
		~OpenGLContext();
		bool Init() override;
		void SwapBuffer() override;
		void Shutdown() override;
		void ClearColor(float x, float y, float z, float a) override;

	private:
#if DG_PLATFORM_WINDOWS
		HWND* windowHandle;
		HDC m_HDC{};
		HGLRC m_HRC{};
		PIXELFORMATDESCRIPTOR m_PFD{};
		int32_t m_Format{};
#endif
#if DG_PLATFORM_LINUX
		Display* display = nullptr;
		int screen;
		Window window;
		Visual* visual = nullptr;
		GLXContext context;
#endif
	};
}
