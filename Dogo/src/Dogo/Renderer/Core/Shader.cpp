#include "dgpch.h"
#include "Dogo/Renderer/Core/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Graphics/GraphicsContext.h"
#include "Dogo/Utils/Logger.h"
namespace Dogo
{
    Shader* Shader::Create(const std::wstring& filepath, ShaderType type)
    {
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				return new OpenGLShader(filepath, type);
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
	
	Shader* Shader::Create(const std::wstring& filepath, const std::wstring& filepath2)
	{
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				return new OpenGLShader(filepath, filepath2);
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
	Shader* Shader::Create(const std::string& filepath, ShaderType type)
	{
		RenderAPI api = GraphicsContext::GetAPI();
		{
			switch (api)
			{
			case Dogo::RenderAPI::API_NONE:
				DG_FATAL("No API specified");
				break;
			case Dogo::RenderAPI::OpenGL:
				return new OpenGLShader(filepath, type);
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
