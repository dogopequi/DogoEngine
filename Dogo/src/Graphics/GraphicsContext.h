#pragma once
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif

namespace Dogo
{
	enum class RenderAPI
	{
		API_NONE, OpenGL, VULKAN, D3D11, D3D12
	};
	class GraphicsContext
	{
	public:
		GraphicsContext(const GraphicsContext&) = delete;
		GraphicsContext& operator=(const GraphicsContext&) = delete;

		virtual bool Init() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Shutdown() = 0;
		virtual void ClearColor(float x, float y, float z, float a) = 0;


#if DG_PLATFORM_WINDOWS
		static void Create(HWND* handle, RenderAPI api);
#else
		static void Create(RenderAPI api);
		static void Create(RenderAPI api, Display *dpy, Visual* vi, int screen, const Window& window);
#endif

		static GraphicsContext* Get() { return s_Context; }
		static RenderAPI GetAPI() { return s_RenderAPI; }

	protected:
		GraphicsContext() = default;
		static GraphicsContext* s_Context;
		static RenderAPI s_RenderAPI;
	};
}