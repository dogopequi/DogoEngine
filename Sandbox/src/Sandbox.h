#pragma once
#include "Dogo/App/Application.h"
#include "Platform/OpenGL/Renderer2D.h"
class Sandbox : public Dogo::Application
{
public:

	void Tick() override;
	
	Sandbox();
	~Sandbox() = default;


};