#include "dgpch.h"
#include "GraphicsContext.h"
#include "Dogo/Utils/Logger.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Dogo
{
	GraphicsContext* GraphicsContext::s_Context = nullptr;
	RenderAPI GraphicsContext::s_RenderAPI = RenderAPI::API_NONE;

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
}
