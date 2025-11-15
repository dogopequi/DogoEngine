#pragma once
#include "Dogo/Renderer/Core/FrameBuffer.h"
#ifdef DG_PLATFORM_WINDOWS
#include <glad/glad.h>
#else
#include <glad/gl.h>
#include <glad/glx.h>
#endif
namespace Dogo
{
	class OpenGLFrameBuffer : public Framebuffer
    {
    public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height);
		~OpenGLFrameBuffer();
        void Bind();
        void Unbind();
        void Resize(uint32_t width, uint32_t height);
        uint32_t GetColorAttachmentID() const;
		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }
        inline uint32_t GetX() const { return m_Height; }
        inline uint32_t GetY() const { return m_Width; }
    private:
        GLuint m_FBO = 0;
        GLuint m_TCB = 0;
        GLuint m_RBO = 0;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
    };
}