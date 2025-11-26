#pragma once
#include <Dogo/Core.h>
#include "Dogo/Events/Event.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Renderer/Core/FrameBuffer.h"
namespace Dogo
{
	class DG_API Layer
	{
	public:
		friend class Application;
		Layer(const std::string& name, const std::shared_ptr<DogoWindow>& window);
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(double delta) {}
		virtual void OnResize() {}
		inline virtual const std::string& GetName() const { return m_Name; }
		virtual uint32_t GetFrameBufferID() const final { return m_FrameBuffer->GetColorAttachmentID(); }
	private:
		virtual void OnResizeNotify() final;
	protected:
		std::string m_Name;
		std::unique_ptr<Framebuffer> m_FrameBuffer;
		std::shared_ptr<DogoWindow> m_Window;
	};
}

