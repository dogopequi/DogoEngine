#pragma once
#if DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#endif
#if DG_PLATFORM_LINUX
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo {
	class GraphicsPipeline
	{
	public:
		GraphicsPipeline(const std::filesystem::path& vpath, const std::filesystem::path& fpath);
		GraphicsPipeline() = delete;
		~GraphicsPipeline();

		void Bind();
		void Unbind();

		void AddShader(const std::filesystem::path& path, GLenum type);

		inline GLuint GetID() const { return m_ID; }


	private:
		GLuint m_ID;
	};
}

