#include "dgpch.h"
#include "OpenGLShader.h"
#include "Dogo/Logger.h"
namespace Dogo
{
	OpenGLShader::OpenGLShader(const std::string& shaderSource, ShaderType type)
	{
		GLenum Type;
		switch (type)
		{
		case ShaderType::COMPUTE:
			Type = GL_COMPUTE_SHADER;
			break;
		case ShaderType::FRAGMENT:
			Type = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::VERTEX:
			Type = GL_VERTEX_SHADER;
			break;
		case ShaderType::GEOMETRY:
			Type = GL_GEOMETRY_SHADER;
			break;
		default:
			DG_FATAL("Unknown Shader");
		}


		m_RendererID = glCreateShader(Type);


		const GLchar* source = (const GLchar*)shaderSource.c_str();
		glShaderSource(m_RendererID, 1, &source, 0);

		glCompileShader(m_RendererID);

		GLint isCompiled = 0;
		glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(m_RendererID);

			DG_ERROR((const char*)infoLog.data());
			DG_ASSERT_MSG(false, "Vertex shader compilation failure!");
			isValid = false;
			return;
		}
		isValid = true;
	}
	OpenGLShader::OpenGLShader(const std::wstring& shaderSource, ShaderType type)
	{
		GLenum Type;
		switch (type)
		{
		case ShaderType::COMPUTE:
			Type = GL_COMPUTE_SHADER;
			break;
		case ShaderType::FRAGMENT:
			Type = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::VERTEX:
			Type = GL_VERTEX_SHADER;
			break;
		case ShaderType::GEOMETRY:
			Type = GL_GEOMETRY_SHADER;
			break;
		default:
			DG_FATAL("Unknown Shader");
		}


		m_RendererID = glCreateShader(Type);


		const GLchar* source = (const GLchar*)shaderSource.c_str();
		glShaderSource(m_RendererID, 1, &source, 0);

		glCompileShader(m_RendererID);

		GLint isCompiled = 0;
		glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(m_RendererID);

			DG_ERROR((const char*)infoLog.data());
			DG_ASSERT_MSG(false, "Vertex shader compilation failure!");
			isValid = false;
			return;
		}
		isValid = true;
	}
	OpenGLShader::OpenGLShader(const std::wstring& vertfilepath, const std::wstring& fragfilepath)
	{
		m_RendererID = glCreateProgram();

		std::string vertCode;
		std::string fragCode;

		try
		{
			vertCode = readFile(vertfilepath);
		}
		catch (std::ifstream::failure& e)
		{
			DG_ERROR("ERROR::VERTEX_SHADER::FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
		}

		try
		{
			fragCode = readFile(fragfilepath);
		}
		catch (std::ifstream::failure& e)
		{
			DG_ERROR("ERROR::FRAG_SHADER::FILE_NOT_SUCCESSFULLY_READ: %s", e.what());
		}

		CreateShader(vertCode, ShaderType::VERTEX);
		CreateShader(fragCode, ShaderType::FRAGMENT);
		glLinkProgram(m_RendererID);
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);


			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);


			glDeleteProgram(m_RendererID);

			DG_ERROR((const char*)infoLog.data());
			DG_ASSERT_MSG(false, "Shader link failure!");
			return;
		}

	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(NULL);
	}

	void OpenGLShader::CreateShader(const std::string& shaderSource, ShaderType type)
	{
		GLenum Type;
		std::string shadertype;
		switch (type)
		{
		case ShaderType::COMPUTE:
			Type = GL_COMPUTE_SHADER;
			shadertype = "Compute";
			break;
		case ShaderType::FRAGMENT:
			Type = GL_FRAGMENT_SHADER;
			shadertype = "Fragment";
			break;
		case ShaderType::VERTEX:
			Type = GL_VERTEX_SHADER;
			shadertype = "Vertex";
			break;
		case ShaderType::GEOMETRY:
			Type = GL_GEOMETRY_SHADER;
			shadertype = "Geometry";
			break;
		default:
			DG_FATAL("Unknown Shader");
		}


		GLuint shader = glCreateShader(Type);


		const GLchar* source = (const GLchar*)shaderSource.c_str();
		glShaderSource(shader, 1, &source, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);
			std::string msg = shadertype + " Shader compilation failure!";
			DG_ERROR((const char*)infoLog.data());
			DG_ASSERT_MSG(false, msg.c_str());
			isValid = false;
			return;
		}
		isValid = true;
		glAttachShader(m_RendererID, shader);
	}


	void OpenGLShader::SetUniform1i(const std::string& name, int32_t value, uint8_t index)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void OpenGLShader::SetUniform2i(const std::string& name, glm::ivec2 value, uint8_t index)
	{
		glUniform2iv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniform3i(const std::string& name, glm::ivec3 value, uint8_t index)
	{
		glUniform3iv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniform4i(const std::string& name, glm::ivec4 value, uint8_t index)
	{
		glUniform4iv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniformBool(const std::string& name, bool value, uint8_t index)
	{
		glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void OpenGLShader::SetUniform1f(const std::string& name, float value, uint8_t index)
	{
		glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
	}
	void OpenGLShader::SetUniform2f(const std::string& name, glm::vec2 value, uint8_t index)
	{
		glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniform3f(const std::string& name, glm::vec3 value, uint8_t index)
	{
		glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniform4f(const std::string& name, glm::vec4 value, uint8_t index)
	{
		glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniformMatrix3f(const std::string& name, glm::mat3 value, uint8_t index)
	{
		glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLShader::SetUniformMatrix4f(const std::string& name, glm::mat4 value, uint8_t index)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
}
