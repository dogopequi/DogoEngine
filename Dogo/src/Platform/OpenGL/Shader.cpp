#include "dgpch.h"
#include "Shader.h"
#include "Dogo/Utils/Logger.h"
namespace Dogo
{
	GLuint Shader::CreateShader(const std::filesystem::path& path, const GLenum type) {
		if (path.empty()) {
			std::runtime_error("Path does not exist: " + path.string());
		}
		if (!std::filesystem::is_regular_file(path)) {
			std::runtime_error("File does not exist: " + path.string());
		}

		std::string code;
		std::ifstream file;

		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			file.open(path);
			std::stringstream stream;
			stream << file.rdbuf();
			file.close();

			code = stream.str();
		}
		catch (std::ifstream::failure e) {
			throw std::runtime_error("Failure reading shader: " + path.string());
			std::println("Failure reading shader({})", path.string());
			throw std::runtime_error("Shader creation failed");
		}

		int success;
		char info[512];
		const char* s_code = code.c_str();
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &s_code, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, info);
			DG_ERROR((const char*)info);
			DG_ASSERT_MSG(false, "Shader compilation failure");
		}

		return shader;
	}
	void Shader::SetUniform1iv(GLuint id, const std::string& name, int32_t* value, uint32_t count, uint8_t index)
	{
		glUniform1iv(glGetUniformLocation(id, name.c_str()), count, value);
	}


	void Shader::SetUniform1i(GLuint id, const std::string& name, int32_t value, uint8_t index)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	void Shader::SetUniform2i(GLuint id, const std::string& name, glm::ivec2 value, uint8_t index)
	{
		glUniform2iv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniform3i(GLuint id, const std::string& name, glm::ivec3 value, uint8_t index)
	{
		glUniform3iv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniform4i(GLuint id, const std::string& name, glm::ivec4 value, uint8_t index)
	{
		glUniform4iv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniformBool(GLuint id, const std::string& name, bool value, uint8_t index)
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	void Shader::SetUniform1f(GLuint id, const std::string& name, float value, uint8_t index)
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
	void Shader::SetUniform2f(GLuint id, const std::string& name, glm::vec2 value, uint8_t index)
	{
		glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniform3f(GLuint id, const std::string& name, glm::vec3 value, uint8_t index)
	{
		glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniform4f(GLuint id, const std::string& name, glm::vec4 value, uint8_t index)
	{
		glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
	}
	void Shader::SetUniformMatrix3f(GLuint id, const std::string& name, glm::mat3 value, uint8_t index)
	{
		glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void Shader::SetUniformMatrix4f(GLuint id, const std::string& name, glm::mat4 value, uint8_t index)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}
