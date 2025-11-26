#pragma once
#include "Dogo/App/Layer.h"
#include "Dogo/Utils/Logger.h"
#include "Dogo/Renderer/2D/Renderer2D.h"
#include "Dogo/Actors/Actor.h"
#include "Dogo/Systems/System.h"
#include "Dogo/Scene/Scene.h"
#include "Graphics/DogoWindow.h"
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Renderer/Core/FrameBuffer.h"
#include "imgui.h"
#include "Dogo/Systems/AssetSystem.h"
enum class LEVEL
{
	SLUG, WORM, PYTHON 
};

class SnakeGame : public Dogo::Layer
{
public:
	SnakeGame(const std::string& name, std::shared_ptr<Dogo::DogoWindow> window);
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(double delta) override;
	void OnResize() override;
	void Setup();
	void CreateGrid();
	void TryMove(const glm::vec3& pos);
	std::shared_ptr<Dogo::Renderer2D> m_Renderer;
	std::shared_ptr<Dogo::Snake> actor;
	std::shared_ptr<Dogo::Apple> apple;
	uint32_t spriteSize = 200;
	uint32_t square = 30;
	Dogo::SpriteRenderSystem2D m_SpriteRenderer;
	Dogo::PhysicsSystem m_Physics;
	Dogo::AudioSystem2D m_Audio;
	std::shared_ptr<Dogo::Scene> m_Scene;
	std::shared_ptr<Dogo::Camera> m_Camera;
	glm::vec2 start{ 0.0f, 0.0f };
	glm::vec2 end{ 0.0f, 0.0f };
	double m_MoveTimer = 0.0;
	double m_MoveInterval = 0.1;

	bool resized = true;
};