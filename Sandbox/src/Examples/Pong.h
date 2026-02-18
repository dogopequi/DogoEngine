#pragma once
#include "Dogo/App/Layer.h"
#include "Dogo/Utils/Logger.h"
#include "Platform/OpenGL/Renderer2D.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Graphics/Window.h"
class Pong : public Dogo::Layer2D
{
public:
	Pong(const std::string& name, std::shared_ptr<Dogo::Window> window);
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(double delta) override;
	void OnResize() override;
	void Setup();
	std::shared_ptr<Dogo::Renderer2D> Renderer;
	glm::vec3 pos;
	std::shared_ptr<Dogo::DogoUI::UIButton> startbutton;
	std::shared_ptr<Dogo::DogoUI::UIButton> pausebutton;
	std::shared_ptr<Dogo::DogoUI::UIPanel> panel;
	Dogo::Window* window;
	double time;
	// game
	float player{};
	float other{};
	glm::vec2 ball{};
	float radius = 10.0f;
	glm::vec2 velocity = glm::vec2(1.0f);
	bool paused = true;

	int playerScore = 0;
	int otherScore = 0;

	float width = 20.0f;
	float height = 50.0f;
	float speed = 500.0f;
	float angle{};
	float rad{};

	float top{};
	float bottom{};
	float left{};
	float right{};

};