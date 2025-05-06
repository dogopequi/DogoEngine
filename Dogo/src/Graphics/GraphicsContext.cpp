#include "dgpch.h"
#include "GraphicsContext.h"
#include "Dogo/Logger.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dogo
{
	GraphicsContext* GraphicsContext::s_Context = nullptr;
	RenderAPI GraphicsContext::s_RenderAPI = RenderAPI::API_NONE;

#if DG_PLATFORM_WINDOWS
	void GraphicsContext::Create(HWND* handle, RenderAPI api)
	{
		switch (api)
		{
		case RenderAPI::API_NONE:
			DG_FATAL("Invalid render API");
			break;
		case RenderAPI::OpenGL:
			s_Context = new OpenGLContext(handle);
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid render API");
			break;
		}
		s_RenderAPI = api;
	}
#else
	void GraphicsContext::Create(RenderAPI api)
	{
		switch (api)
		{
		case RenderAPI::API_NONE:
			DG_FATAL("Invalid render API");
			break;
		case RenderAPI::OpenGL:
			s_Context = new OpenGLContext();
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid render API");
			break;
		}
		s_RenderAPI = api;
	}
	
	void GraphicsContext::Create(RenderAPI api, Display *dpy, Visual* vi, int screen, const Window& window)
	{
		switch (api)
		{
		case RenderAPI::API_NONE:
			DG_FATAL("Invalid render API");
			break;
		case RenderAPI::OpenGL:
			s_Context = new OpenGLContext(dpy, vi, screen, window);
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid render API");
			break;
		}
		s_RenderAPI = api;
	}
#endif
}
