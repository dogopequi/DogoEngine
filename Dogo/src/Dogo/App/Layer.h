#pragma once
#include <Dogo/Core.h>
#include "Dogo/Events/Event.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Renderer/Core/FrameBuffer.h"
#include "Dogo/Scene/Scene.h"
#include "Dogo/Systems/System.h"
namespace Dogo
{
	class DG_API Layer2D
	{
	public:
		friend class Application;
		Layer2D(const std::string& name, const std::shared_ptr<DogoWindow>& window);
		virtual ~Layer2D();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(double delta) {}
		virtual void OnResize() {}
		inline virtual const std::string& GetName() const { return m_Name; }
		virtual uint32_t GetFrameBufferID() const { return m_FrameBuffer->GetColorAttachmentID(); }

	protected:
		void virtual Submit() {}
	private:
		virtual void Update(double delta) final;
		virtual void OnResizeNotify() final;
	protected:
		std::string m_Name;
		std::unique_ptr<Framebuffer> m_FrameBuffer;
		std::shared_ptr<DogoWindow> m_Window;
		std::shared_ptr<Scene> m_Scene;
		std::shared_ptr<Renderer2D> m_Renderer;
	};
}

