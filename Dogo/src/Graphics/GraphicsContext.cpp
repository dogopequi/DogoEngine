#include "dgpch.h"
#include "GraphicsContext.h"
#include "Dogo/Logger.h"
#include "Platform/DX11/DX11Context.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dogo
{
	GraphicsContext* GraphicsContext::s_Context = nullptr;
	RenderAPI GraphicsContext::s_RenderAPI = RenderAPI::None;
	void GraphicsContext::Create(HWND* handle, RenderAPI api)
	{
		switch (api)
		{
		case RenderAPI::None:
			DG_FATAL("Invalid render API");
			break;
		case RenderAPI::OpenGL:
			s_Context = new OpenGLContext(handle);
			break;
#if DG_PLATFORM_WINDOWS
		case RenderAPI::D3D11:
			s_Context = new DX11Context(handle);
			break;
		case RenderAPI::D3D12:
			DG_FATAL("Not implemented");
			break;
#endif
		case RenderAPI::VULKAN:
			DG_FATAL("Not implemented");
			break;
		default:
			DG_FATAL("Invalid render API");
			break;
		}
		s_RenderAPI = api;
	}
}
