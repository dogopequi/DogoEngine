#pragma once
#include "Dogo/Application.h"
#include "Dogo/Renderer/Renderer2D.h"
class Sandbox : public Dogo::Application
{
public:

	void Tick() override;
	
	Sandbox();
	~Sandbox() = default;


};