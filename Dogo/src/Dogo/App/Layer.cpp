#include "dgpch.h"
#include "Layer.h"

namespace Dogo
{
	Layer::Layer(const std::string& name, const std::shared_ptr<DogoWindow>& window)
		: m_Name(name), m_Window(window)
	{
		m_FrameBuffer = Framebuffer::Create(m_Window->GetWidth(), m_Window->GetHeight());
	}
	void Layer::OnResizeNotify()
	{
		m_FrameBuffer->Resize(m_Window->GetWidth(), m_Window->GetHeight());
		OnResize();
	}
	Layer::~Layer()
	{
	}
}
