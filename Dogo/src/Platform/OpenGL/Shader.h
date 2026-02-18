#pragma once
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
	class Shader
	{
	public:
		static GLuint CreateShader(const std::filesystem::path& path, const GLenum type);
		static void SetUniform1iv(GLuint id, const std::string& name, int32_t* value, uint32_t count, uint8_t index = 0) ;
		static void SetUniform1i(GLuint id, const std::string& name, int32_t value, uint8_t index = 0) ;
		static void SetUniform2i(GLuint id, const std::string& name, glm::ivec2 value, uint8_t index = 0) ;
		static void SetUniform3i(GLuint id, const std::string& name, glm::ivec3 value, uint8_t index = 0) ;
		static void SetUniform4i(GLuint id, const std::string& name, glm::ivec4 value, uint8_t index = 0) ;

		static void SetUniformBool(GLuint id, const std::string& name, bool value, uint8_t index = 0) ;

		static void SetUniform1f(GLuint id, const std::string& name, float value, uint8_t index = 0) ;
		static void SetUniform2f(GLuint id, const std::string& name, glm::vec2 value, uint8_t index = 0) ;
		static void SetUniform3f(GLuint id, const std::string& name, glm::vec3 value, uint8_t index = 0) ;
		static void SetUniform4f(GLuint id, const std::string& name, glm::vec4 value, uint8_t index = 0) ;

		static void SetUniformMatrix3f(GLuint id, const std::string& name, glm::mat3 value, uint8_t index = 0) ;
		static void SetUniformMatrix4f(GLuint id, const std::string& name, glm::mat4 value, uint8_t index = 0) ;

	private:
		Shader() = default;
		~Shader() {};
	};

}

