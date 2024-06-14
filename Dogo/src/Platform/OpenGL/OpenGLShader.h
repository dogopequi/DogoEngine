#pragma once
#include "Dogo/Renderer/Shader.h"
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Dogo/Core.h"
namespace Dogo
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::wstring& shaderSource, ShaderType type);
		OpenGLShader(const std::string& shaderSource, ShaderType type);
		OpenGLShader(const std::string& vertSource, const std::string& fragSource);
		OpenGLShader(const std::wstring& vertSource, const std::wstring& fragSource);
		~OpenGLShader();

		bool GetIsValid() const { return isValid; }
		uint32_t GetID() const { return m_RendererID; }

		void Bind();
		void Unbind();

		void CreateShader(const std::string& shaderSource, ShaderType type);
		void CreateShader(const std::wstring& shaderSource, ShaderType type);

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

	private:
		uint32_t m_RendererID{};
		bool isValid{};
	};

}

