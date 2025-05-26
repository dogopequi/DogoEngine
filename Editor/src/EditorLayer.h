#pragma once
#include "Dogo/Layer.h"
class EditorLayer : public Dogo::Layer
{
public:
	EditorLayer();
	~EditorLayer() = default;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
};