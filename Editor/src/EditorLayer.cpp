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
		viewport = Dogo::Viewport();
		topMenuPanel = std::make_shared<Dogo::DogoUI::UIPanel>();
		bottomPanel = std::make_shared<Dogo::DogoUI::UIPanel>();
		leftPanel = std::make_shared<Dogo::DogoUI::UIPanel>();
		rightPanel = std::make_shared<Dogo::DogoUI::UIPanel>();
		Dogo::DogoUI::UIAddEditorPanel(topMenuPanel);
		Dogo::DogoUI::UIAddEditorPanel(leftPanel);
		Dogo::DogoUI::UIAddEditorPanel(rightPanel);
		Dogo::DogoUI::UIAddEditorPanel(bottomPanel);
		SetupViewport();
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
	Window->Viewport(0, 0, Window->GetWidth(), Window->GetHeight());
	Window->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Window->ClearBuffers();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Framebuffer->GetColorAttachmentID());

	Dogo::DogoUI::UseViewport = true;
	Dogo::DogoUI::DrawViewport(viewport, Renderer, glm::mat4(1.0f));
	Dogo::DogoUI::HandleViewportInput(viewport);
	Dogo::DogoUI::UseViewport = false;
	Dogo::DogoUI::UIRenderEditorElements(Renderer);
	Dogo::DogoUI::UIHandleEditorInput();
	Framebuffer->Bind();

}

void EditorLayer::OnResizeNotify()
{
	SetupViewport();
}

void EditorLayer::SetupViewport()
{
	float windowWidth = static_cast<float>(Window->GetWidth());
	float windowHeight = static_cast<float>(Window->GetHeight());

	float topBarHeight = static_cast<float>(Window->GetHeight()) / 10;
	float bottomPanelHeight = static_cast<float>(Window->GetHeight()) / 8;
	float sidePanelWidth = windowWidth / 8.0f;

	float usableWidth = windowWidth - 2 * sidePanelWidth;
	float usableHeight = windowHeight - topBarHeight - bottomPanelHeight;

	topmenuRect = { { 0.0f, 0.0f }, windowWidth, topBarHeight };
	leftpanelRect = { { 0.0f, topBarHeight }, sidePanelWidth, windowHeight - topBarHeight };
	rightpanelRect = { { windowWidth - sidePanelWidth, topBarHeight }, sidePanelWidth, windowHeight - topBarHeight };
	bottompanelRect = { { sidePanelWidth, windowHeight - bottomPanelHeight }, usableWidth, bottomPanelHeight };

	float targetAspect = 16.0f / 9.0f;
	float viewportWidth = usableWidth;
	float viewportHeight = viewportWidth / targetAspect;

	if (viewportHeight > usableHeight) {
		viewportHeight = usableHeight;
		viewportWidth = viewportHeight * targetAspect;
	}

	float viewportX = sidePanelWidth + (usableWidth - viewportWidth) / 2.0f;
	float viewportY = topBarHeight + (usableHeight - viewportHeight) / 2.0f;

	viewportRect = { { viewportX, viewportY }, viewportWidth, viewportHeight };

	topMenuPanel->visible = true;
	topMenuPanel->color = { 1.0f, 0.2f, 0.2f };
	topMenuPanel->size = { topmenuRect.width, topmenuRect.height };
	topMenuPanel->pos = topmenuRect.pos;
	leftPanel->visible = true;
	leftPanel->color = { 0.2f, 1.0f, 0.2f };
	leftPanel->size = { leftpanelRect.width, leftpanelRect.height };
	leftPanel->pos = leftpanelRect.pos;
	rightPanel->visible = true;
	rightPanel->color = { 0.2f, 0.2f, 1.0f };
	rightPanel->size = { rightpanelRect.width, rightpanelRect.height };
	rightPanel->pos = rightpanelRect.pos;
	bottomPanel->visible = true;
	bottomPanel->color = { 1.0f, 1.0f, 1.0f };
	bottomPanel->size = { bottompanelRect.width, bottompanelRect.height };
	bottomPanel->pos = bottompanelRect.pos;
	Dogo::DogoUI::WindowSize = { static_cast<float>(Window->GetWidth()), static_cast<float>(Window->GetHeight()) };
	Framebuffer->Resize(Window->GetWidth(), Window->GetHeight());
	viewport.color = { 0.1f, 0.1f, 0.1f };
	viewport.pos = viewportRect.pos;
	viewport.size = { viewportRect.width, viewportRect.height };
	viewport.transparent = false;
	viewport.visible = true;
	viewport.framebufferSize = glm::vec2(static_cast<float>(Framebuffer->GetWidth()), static_cast<float>(Framebuffer->GetHeight()));
}

