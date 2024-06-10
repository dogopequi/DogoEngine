#pragma once

#include "Graphics/GraphicsContext.h"
class DG_Window;

namespace Dogo
{
	class OpenGLContext : public GraphicsContext
	{
	public:
#if DG_PLATFORM_WINDOWS
		OpenGLContext(HWND* handle);
#endif
		OpenGLContext(){}
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
	};
}
