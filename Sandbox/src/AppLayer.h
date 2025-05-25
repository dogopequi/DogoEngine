#pragma once
#include "Dogo/Layer.h"
#include "Dogo/Logger.h"
#include "Dogo/Renderer/Renderer2D.h"
class AppLayer : public Dogo::Layer
{
public:
	AppLayer();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;

	Dogo::Renderer2D* Renderer;
};