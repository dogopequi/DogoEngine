#pragma once
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif

class DG_Window;

namespace Dogo
{
	namespace GraphicsContext
	{
		bool Init() ;
		void SwapBuffer() ;
		void Shutdown() ;
		void Finish() ;
		void ClearColor(float x, float y, float z, float a);
		void ClearBuffers() ;
		void Viewport(int x, int y, int z, int a);
	};
}
