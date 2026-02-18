#pragma once
#include "Dogo/App/Layer.h"
#include "Dogo/Utils/Logger.h"
#include "Platform/OpenGL/Renderer2D.h"
#include "Dogo/Actors/Actor.h"
#include "Dogo/Scene/Scene.h"
#include "Graphics/Window.h"
#include "Platform/OpenGL/FrameBuffer.h"
#include "imgui.h"
#include "Dogo/Systems/AssetSystem.h"
#include "Dogo/Component/AudioSourceComponent.h"
enum class LEVEL
{
	SLUG, WORM, PYTHON 
};

class SnakeGame : public Dogo::Layer2D
{
public:
	SnakeGame(const std::string& name, std::shared_ptr<Dogo::Window> window);
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(double delta) override;
private:
	void Submit() override;
	void Setup();
	void CreateGrid();
	bool CheckBounds(const glm::vec2& nextPos);
	bool CheckDeath(const glm::vec2& pos);
	void UpdateSnake();
	glm::vec2 GetRandomPositionInBounds();
	std::shared_ptr<Dogo::Apple> apple;

	uint32_t spriteSize = 30;
	int32_t square = 32;
	static constexpr float gridPixel = 720.0f * 0.8f;
	float startX = (1280.0f - gridPixel) / 2.0f;
	float startY = (720.0f - gridPixel) / 2.0f;
	float endX = startX + gridPixel;
	float endY = startY + gridPixel;
	uint32_t cells = gridPixel / square;
	LEVEL level{ LEVEL::SLUG };
	float counter{0.0f};
	bool dead = false;
	bool running = false;
	bool won = false;
	bool hasGrownThisMove = false;
	uint32_t applesEaten = {0};
	uint32_t applesToEat = { 5 };
	glm::vec2 dir = glm::vec2(0.0f, square);

	Dogo::Texture2D* head_down;
	Dogo::Texture2D* head_up;
	Dogo::Texture2D* head_left;
	Dogo::Texture2D* head_right;
	Dogo::Texture2D* tail_down;
	Dogo::Texture2D* tail_up;
	Dogo::Texture2D* tail_left;
	Dogo::Texture2D* tail_right;
	Dogo::Texture2D* body_vertical;
	Dogo::Texture2D* body_topright;
	Dogo::Texture2D* body_topleft;
	Dogo::Texture2D* body_bottomright;
	Dogo::Texture2D* body_bottomleft;
	Dogo::Texture2D* body_horizontal;



	double m_MoveTimer = 0.0;
	double m_MoveInterval = 0.3;

	static std::mt19937 gen;

	std::uniform_int_distribution<> distCell;

	std::deque<std::pair<glm::vec2, Dogo::Texture2D*>> snake;
	size_t snakesize = { 7 };

	std::shared_ptr<Dogo::Camera> m_Camera;
	glm::vec2 start{ 0.0f, 0.0f };
	glm::vec2 end{ 0.0f, 0.0f };

	DogoECS::Entity* justforgameoveraudio;
	DogoECS::Entity* justforwinaudio;

	Dogo::ECS::AudioSourceComponent2D* gameoveraudio;
	Dogo::ECS::AudioSourceComponent2D* winaudio;
};