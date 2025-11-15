#include "dgpch.h"
#include "FrameBuffer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Utils/Logger.h"

namespace Dogo
{
    Framebuffer* Framebuffer::Create(uint32_t width, uint32_t height)
    {
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				return new OpenGLFrameBuffer(width, height);
				break;
			case Dogo::RenderAPI::VULKAN:
				DG_FATAL("Not Implemented");
				break;
			default:
				DG_FATAL("No API specified");
				break;
			}
		}
		return nullptr;
    }
}
