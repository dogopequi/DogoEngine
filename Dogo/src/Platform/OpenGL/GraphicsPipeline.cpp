#include "dgpch.h"
#include "GraphicsPipeline.h"
#include "Dogo/Utils/Logger.h"
#include "Shader.h"
namespace Dogo {
	GraphicsPipeline::GraphicsPipeline(const std::filesystem::path& vpath, const std::filesystem::path& fpath)
	{
		m_ID = glCreateProgram();

		GLuint vertex = Shader::CreateShader(vpath, GL_VERTEX_SHADER);
		GLuint fragment = Shader::CreateShader(fpath, GL_FRAGMENT_SHADER);

		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		int success;
		char info[512];
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, info);
			DG_ERROR((const char*)info);
			DG_ASSERT_MSG(false, "Pipeline compilation failure");
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	GraphicsPipeline::~GraphicsPipeline()
	{
		glDeleteProgram(m_ID);
	}

	void GraphicsPipeline::Bind()
	{
		glUseProgram(m_ID);
	}

	void GraphicsPipeline::Unbind()
	{
		glUseProgram(0);
	}
	void GraphicsPipeline::AddShader(const std::filesystem::path& path, GLenum type)
	{
		GLuint shader = Shader::CreateShader(path, type);

		glAttachShader(m_ID, shader);
		glLinkProgram(m_ID);

		int success;
		char info[512];
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, info);
			DG_ERROR((const char*)info);
			DG_ASSERT_MSG(false, "Pipeline compilation failure");
		}

		glDeleteShader(shader);
	}
}