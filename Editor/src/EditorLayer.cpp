#include "dgpch.h"
#include "EditorLayer.h"
#include "Dogo/Logger.h"
#include "Dogo/Renderer/FrameBuffer.h"
#include "Dogo/Renderer/Shader.h"

EditorLayer::EditorLayer(Dogo::Renderer2D* renderer, Dogo::DogoWindow* window, Dogo::Framebuffer* framebuffer)
		: Layer("EditorLayer")
	{
		DG_TRACE("EditorLayer created");
		Renderer = renderer;
		Window = window;
		Framebuffer = framebuffer;
		viewport = std::make_shared<Dogo::DogoUI::UIViewport>();
		viewport->color = { 0.1f, 0.1f, 0.1f };
		viewport->pos = { 0.0f, 0.0f };
		viewport->size = { Window->GetWidth(), Window->GetHeight() };
		viewport->transparent = false;
		viewport->visible = true;
		Dogo::DogoUI::AddElement(viewport);
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
	viewport->Draw(Renderer, glm::mat4(1.0f));
	Framebuffer->Bind();
}

