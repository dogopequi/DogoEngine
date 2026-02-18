#include "dgpch.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Utils/Logger.h"
#include "Dogo/Renderer/Core/Texture.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
namespace Dogo
{
	Texture* Texture::Create(std::string_view filepath)
    {
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLTexture2D(filepath);
		case RenderAPI::VULKAN:
			DG_FATAL("VULKAN not implemented");
			return nullptr;
		default:
			DG_FATAL("Invalid API.");
			return nullptr;
		}
		return nullptr;
    }
}
