#pragma once
#include "Dogo/App/Application.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
class Sandbox : public Dogo::Application
{
public:

	void Tick() override;
	
	Sandbox();
	~Sandbox() = default;


};