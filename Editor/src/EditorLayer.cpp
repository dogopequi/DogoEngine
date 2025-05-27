#include "dgpch.h"
#include "EditorLayer.h"
#include "Dogo/Logger.h"
#include "Dogo/Renderer/FrameBuffer.h"
#include "Dogo/Renderer/Shader.h"

EditorLayer::EditorLayer(std::shared_ptr<Dogo::Renderer2D> renderer, Dogo::DogoWindow* window, std::shared_ptr<Dogo::Framebuffer> framebuffer)
		: Layer("EditorLayer")
	{
		DG_TRACE("EditorLayer created");
		Renderer = renderer;
		Window = window;
		Framebuffer = framebuffer;
		viewport = Dogo::DogoUI::UIViewport();
		viewport.color = { 0.1f, 0.1f, 0.1f };
		viewport.pos = { 200.0f, 100.0f };
		viewport.size = { Window->GetWidth() / 2, Window->GetHeight() / 2 };
		viewport.transparent = false;
		viewport.visible = true;
		viewport.framebufferSize = glm::vec2(static_cast<float>(framebuffer->GetWidth()) , static_cast<float>(framebuffer->GetHeight()));
		Dogo::DogoUI::UseViewport = true;
	}
void EditorLayer::OnAttach()
{
	DG_TRACE("EditorLayer attached");
}
void EditorLayer::OnDetach()
{
	DG_TRACE("EditorLayer detached");
}
void EditorLayer::OnUpdate()
{
	Framebuffer->Unbind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Framebuffer->GetColorAttachmentID());
	Dogo::DogoUI::DrawViewport(viewport, Renderer, glm::mat4(1.0f));
	Dogo::DogoUI::HandleInput(viewport);
	Framebuffer->Bind();
}

