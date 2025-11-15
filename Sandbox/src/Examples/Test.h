#pragma once
#include "Dogo/App/Layer.h"
#include "Dogo/Utils/Logger.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Actors/Actor.h"
class TestLayer : public Dogo::Layer
{
public:
	TestLayer(std::shared_ptr<Dogo::Renderer2D> renderer);
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnResizeNotify() override;
	void Setup();
	std::shared_ptr<Dogo::Renderer2D> m_Renderer;
	Dogo::Test2DActor* actor;

};