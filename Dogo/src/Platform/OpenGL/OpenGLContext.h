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
		OpenGLContext();
		~OpenGLContext();
		bool Init() override;
		void SwapBuffer() override;
		void Shutdown() override;
		void ClearColor(float x, float y, float z, float a) override;

	private:

	};
}
