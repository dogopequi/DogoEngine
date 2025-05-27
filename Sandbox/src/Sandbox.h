#pragma once
#include "Dogo/Application.h"
#include "Dogo/Renderer/Renderer2D.h"
class Sandbox : public Dogo::Application
{
public:

	bool OnWindowClose(Dogo::WindowCloseEvent& e);
	bool KeyPressedCallBack(Dogo::KeyPressedEvent& e);
	bool KeyReleasedCallBack(Dogo::KeyReleasedEvent& e);
	bool MouseMovedCallBack(Dogo::MouseMovedEvent& e);
	bool MouseButtonPressedCallBack(Dogo::MouseButtonPressedEvent& e);
	bool MouseButtonReleasedCallBack(Dogo::MouseButtonReleasedEvent& e);
	bool MouseScrolledCallBack(Dogo::MouseScrolledEvent& e);
	void Run() override;

	Sandbox();
	~Sandbox() = default;

	void OnEvent(Dogo::Event& e) override;
	std::shared_ptr<Dogo::Renderer2D> Renderer;

};