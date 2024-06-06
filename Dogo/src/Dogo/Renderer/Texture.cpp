#include "dgpch.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Logger.h"
#include "Texture.h"
#include "Platform/DX11/DX11Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Dogo
{
    Texture* Texture::Create(const std::string& filepath, ImageType imageType, TextureType textureType, const std::string& name)
    {
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLTexture(filepath, imageType, textureType, name);
			break;
		case RenderAPI::D3D11:
			return new DX11Texture(filepath, textureType, name);
			break;
		default:
			DG_FATAL("Invalid API to create TextureManager");
			return nullptr;
			break;
		}
    }
}
