#pragma once
#include <glm/glm.hpp>
namespace Dogo
{
	enum class ShaderType
	{
		None = 0, COMPUTE, VERTEX, FRAGMENT, GEOMETRY
	};
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create(const std::string& shaderSource, ShaderType type);
		static Shader* Create(const std::string& vertSource, const std::string& fragSource);
		static Shader* Create(const std::wstring& filepath, ShaderType type);

		virtual void SetUniform1i(const std::string& name, int32_t value, uint8_t index = 0) = 0;
		virtual void SetUniform2i(const std::string& name, glm::ivec2 value, uint8_t index = 0) = 0;
		virtual void SetUniform3i(const std::string& name, glm::ivec3 value, uint8_t index = 0) = 0;
		virtual void SetUniform4i(const std::string& name, glm::ivec4 value, uint8_t index = 0) = 0;

		virtual void SetUniformBool(const std::string& name, bool value, uint8_t index = 0) = 0;

		virtual void SetUniform1f(const std::string& name, float value, uint8_t index = 0) = 0;
		virtual void SetUniform2f(const std::string& name, glm::vec2 value, uint8_t index = 0) = 0;
		virtual void SetUniform3f(const std::string& name, glm::vec3 value, uint8_t index = 0) = 0;
		virtual void SetUniform4f(const std::string& name, glm::vec4 value, uint8_t index = 0) = 0;

		virtual void SetUniformMatrix3f(const std::string& name, glm::mat3 value, uint8_t index = 0) = 0;
		virtual void SetUniformMatrix4f(const std::string& name, glm::mat4 value, uint8_t index = 0) = 0;
	};
}