#include "dgpch.h"
#include "TextureArray.h"
#include "Graphics/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLTextureArray.h"
#include "Dogo/Utils/Logger.h"
namespace Dogo
{
	TextureArray* TextureArray::Create(uint32_t width, uint32_t height, uint32_t maxLayers)
	{
		RenderAPI api = GraphicsContext::Get()->GetAPI();
		switch (api)
		{
		case RenderAPI::OpenGL:
			return new OpenGLTextureArray(width, height, maxLayers);
		case RenderAPI::VULKAN:
			DG_FATAL("VULKAN not implemented");
			return nullptr;
		default:
			DG_FATAL("Invalid API.");
			return nullptr;
		}
		return nullptr;
	}
	TextureArray::TextureArray(uint32_t width, uint32_t height, uint32_t maxLayers) : m_Width(width), m_Height(height), m_MaxLayers(maxLayers)
	{
	}
}