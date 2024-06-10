#include "dgpch.h"
#include "Shader.h"
#include "Platform/DX11/DX11Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Dogo
{
    Shader* Shader::Create(const std::string& shaderSource, ShaderType type)
    {
        return new OpenGLShader(shaderSource, type);
    }

    Shader* Shader::Create(const std::string& vertSource, const std::string& fragSource)
    {
        return new OpenGLShader(vertSource, fragSource);
    }
#if DG_PLATFORM_WINDOWS
    Shader* Shader::Create(const std::wstring& filepath, ShaderType type)
    {
        return DX11Shader::Create(filepath, type);
    }
#endif
}
