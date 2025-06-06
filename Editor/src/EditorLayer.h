#pragma once
#include "Dogo/Layer.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Renderer/Renderer2D.h"
#include "Dogo/Renderer/FrameBuffer.h"
class EditorLayer : public Dogo::Layer
{
public:
	EditorLayer(std::shared_ptr<Dogo::Renderer2D> renderer, Dogo::DogoWindow* window, std::shared_ptr<Dogo::Framebuffer> framebuffer);
	~EditorLayer() = default;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnResizeNotify() override;
private:
	void SetupViewport();
	Dogo::Viewport viewport;
	Dogo::DogoWindow* Window;
	std::shared_ptr<Dogo::Framebuffer> Framebuffer;
	std::shared_ptr<Dogo::Renderer2D> Renderer;

	Dogo::Rect viewportRect{};
	Dogo::Rect topmenuRect{};
	Dogo::Rect leftpanelRect{};
	Dogo::Rect rightpanelRect{};
	Dogo::Rect bottompanelRect{};

	std::shared_ptr<Dogo::DogoUI::UIPanel> topMenuPanel;
	std::shared_ptr<Dogo::DogoUI::UIPanel> leftPanel;
	std::shared_ptr<Dogo::DogoUI::UIPanel> rightPanel;
	std::shared_ptr<Dogo::DogoUI::UIPanel> bottomPanel;

};