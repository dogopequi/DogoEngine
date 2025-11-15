#include "dgpch.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Utils/Logger.h"
#include "Dogo/Renderer/Core/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Dogo
{
    Texture* Texture::Create(const std::string& filepath, TextureType textureType, FilterMode filter, Wrapping wrap, bool mipmap)
    {
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLTexture(filepath, textureType, filter, wrap, mipmap);
			break;
		case RenderAPI::VULKAN:
			DG_FATAL("VULKAN not implemented");
			break;
		default:
			DG_FATAL("Invalid API to create TextureManager");
			return nullptr;
			break;
		}
		return nullptr;
    }
}
