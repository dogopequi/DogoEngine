#pragma once
namespace Dogo
{
    class Framebuffer
    {
    public:
        static Framebuffer* Create(uint32_t width, uint32_t height);
        virtual ~Framebuffer() = default;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void Resize(uint32_t width, uint32_t height) = 0;
        virtual uint32_t GetColorAttachmentID() const = 0;
    };
}