#pragma once

#include "Graphics/GraphicsContext.h"
class Window;

namespace Dogo
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(HWND* handle);
		~OpenGLContext();
		bool Init() override;
		void SwapBuffer() override;
		void Shutdown() override;
		void ClearColor(float x, float y, float z, float a) override;

	private:
		HWND* windowHandle;
		HDC m_HDC{};
		HGLRC m_HRC{};
		PIXELFORMATDESCRIPTOR m_PFD{};
		int32_t m_Format{};
	};
}
