#pragma once
#include "glad/glad.h"
#if DG_PLATFORM_LINUX
#include <GL/glx.h>
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
		OpenGLContext(Display *dpy, XVisualInfo* vi);
		#endif
		OpenGLContext();
		~OpenGLContext();
		bool Init() override;
#if DG_PLATFORM_LINUX
		bool Init(const Window& win) override;
#endif
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
		Display* display;
		XVisualInfo* viinfo;
		GLXContext* glc;
#endif
	};
}
