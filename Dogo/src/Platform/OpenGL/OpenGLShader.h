#pragma once
#include "Dogo/Renderer/Core/Shader.h"
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Dogo/Core.h"

#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::wstring& shaderSource, ShaderType type);
		OpenGLShader(const std::string& shaderSource, ShaderType type);
		OpenGLShader(const std::wstring& vertfilepath, const std::wstring& fragfilepath);
		~OpenGLShader();

		bool GetIsValid() const { return isValid; }

		void Bind();
		void Unbind();
		uint32_t GetRendererID() const override { return m_RendererID; }
		void CreateShader(const std::string& shaderSource, ShaderType type);
		void SetUniform1iv(const std::string& name, int32_t* value, uint32_t count, uint8_t index = 0) override;
		void SetUniform1i(const std::string& name, int32_t value, uint8_t index = 0) override;
		void SetUniform2i(const std::string& name, glm::ivec2 value, uint8_t index = 0) override;
		void SetUniform3i(const std::string& name, glm::ivec3 value, uint8_t index = 0) override;
		void SetUniform4i(const std::string& name, glm::ivec4 value, uint8_t index = 0) override;

		void SetUniformBool(const std::string& name, bool value, uint8_t index = 0) override;

		void SetUniform1f(const std::string& name, float value, uint8_t index = 0) override;
		void SetUniform2f(const std::string& name, glm::vec2 value, uint8_t index = 0) override;
		void SetUniform3f(const std::string& name, glm::vec3 value, uint8_t index = 0) override;
		void SetUniform4f(const std::string& name, glm::vec4 value, uint8_t index = 0) override;

		void SetUniformMatrix3f(const std::string& name, glm::mat3 value, uint8_t index = 0) override;
		void SetUniformMatrix4f(const std::string& name, glm::mat4 value, uint8_t index = 0) override;

		inline std::string readFile(const std::wstring& filepath)
		{
			std::ifstream file(filepath, std::ios::binary);
			file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			std::stringstream buffer;
			buffer << file.rdbuf();
			return buffer.str();
		}

		void printShaderSource(const std::string& shaderName, const std::string& shaderCode)
		{
			std::cout << "Shader: " << shaderName << "\n";
			std::cout << "------------------------------------\n";
			std::cout << shaderCode << "\n";
			std::cout << "------------------------------------\n";
		}

		void printShaderSource(const char* shaderName, const char* shaderCode)
		{
			std::cout << "Shader: " << shaderName << "\n";
			std::cout << "------------------------------------\n";
			std::cout << shaderCode << "\n";
			std::cout << "------------------------------------\n";
		}

	private:
		uint32_t m_RendererID{};
		bool isValid{};
	};

}

