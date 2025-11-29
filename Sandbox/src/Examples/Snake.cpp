#include "dgpch.h"
#include "Snake.h"
#include "Dogo/Actors/Actor.h"
#include "Dogo/Component/Components.h"
#include "Dogo/Component/SpriteRendererComponent.h"
#include "Dogo/Component/RigidBodyComponent.h"
#include "Dogo/Renderer/2D/Sprite.h"
#include "Dogo/Input/Input.h"
#include "Dogo/Renderer/Core/Texture.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>
std::mt19937 SnakeGame::gen(std::random_device{}());

SnakeGame::SnakeGame(const std::string& name, std::shared_ptr<Dogo::DogoWindow> window) : Layer2D(name, window)
{
	startX = std::round(startX / square) * square;
	startY = std::round(startY / square) * square;
	endX = std::round((startX + gridPixel) / square) * square;
	endY = std::round((startY + gridPixel) / square) * square;
	m_Camera = std::make_shared<Dogo::Camera>(Dogo::Camera::Orthographic(m_Window->GetWidth(), m_Window->GetHeight(), 0.1, 100.0f));
	m_Camera->SetRenderTargetSize(m_Window->GetWidth(), m_Window->GetHeight());
	m_Renderer->SetViewMatrix(m_Camera->GetViewMatrix());
	m_Renderer->SetProjectionMatrix(m_Camera->GetProjectionMatrix());
	m_Scene->SetMainCamera(m_Camera);
	m_Scene->AddCamera(m_Camera);
	Dogo::ECS::RegisterComponent<Dogo::ECS::SpriteRendererComponent>();
	Dogo::ECS::RegisterComponent<Dogo::ECS::RigidBodyComponent>();
	Dogo::ECS::RegisterComponent<Dogo::ECS::AudioSourceComponent2D>();
	apple = std::make_shared<Dogo::Apple>(glm::vec3(0.0f, 0.0f, 0.0f));
	Dogo::ECS::AudioSourceComponent2D* apppleaudio = apple->AddComponent<Dogo::ECS::AudioSourceComponent2D>("../Dogo/resources/Audio/eat.wav", 10);
	apppleaudio->Load();
	Dogo::ECS::SpriteRendererComponent* p1 = apple->AddComponent<Dogo::ECS::SpriteRendererComponent>();
	p1->sprite = Dogo::Sprite("apple", "../Dogo/resources/Textures/apple.png", (float)spriteSize, (float)spriteSize);
	if (p1->sprite.GetTexture().has_value())
		m_Renderer->PreLoadTexture(p1->sprite.GetTexture().value());

	distCell = std::uniform_int_distribution<>(0, cells - 1);

	if (level == LEVEL::SLUG)
	{
		m_MoveInterval = 0.3;
		applesToEat = 5;
	}
	else if (level == LEVEL::WORM)
	{
		m_MoveInterval = 0.2;
		applesToEat = 10;
	}
	else if (level == LEVEL::PYTHON)
	{
		m_MoveInterval = 0.1;
		applesToEat = 15;
	}

	head_down = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/head_down.png");
	head_up = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/head_up.png");
	head_left = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/head_left.png");
	head_right = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/head_right.png");
	tail_down = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/tail_down.png");
	tail_up = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/tail_up.png");
	tail_left = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/tail_left.png");
	tail_right = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/tail_right.png");
	body_vertical = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_vertical.png");
	body_topright = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_topright.png");
	body_topleft = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_topleft.png");
	body_bottomright = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_bottomright.png");
	body_bottomleft = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_bottomleft.png");
	body_horizontal = Dogo::AssetSystem::LoadTexture("../Dogo/resources/Textures/body_horizontal.png");


	glm::vec2 posapple = GetRandomPositionInBounds();
	glm::vec2 possnake = {startX + ((endX - startX) / 2), startY + ((endY - startY) / 2)};
	apple->GetComponent<Dogo::ECS::TransformComponent>()->SetPosition({ posapple.x, posapple.y, 0.0f });

	snake.emplace_back(possnake, &head_up.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - square), &body_vertical.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - (square * 2)), &body_vertical.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - (square * 3)), &body_vertical.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - (square * 4)), &body_vertical.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - (square * 5)), &body_vertical.value());
	snake.emplace_back(glm::vec2(possnake.x, possnake.y - (square * 6)), &tail_down.value());
	m_Scene->AddGameObject(apple);
	m_Scene->Init();

	justforgameoveraudio = Dogo::ECS::CreateEntity();
	justforwinaudio = Dogo::ECS::CreateEntity();

	gameoveraudio = Dogo::ECS::AddComponent<Dogo::ECS::AudioSourceComponent2D>(justforgameoveraudio, "../Dogo/resources/Audio/gameover.wav", 10.0f);
	winaudio = Dogo::ECS::AddComponent<Dogo::ECS::AudioSourceComponent2D>(justforgameoveraudio, "../Dogo/resources/Audio/sound.wav", 10.0f);
	gameoveraudio->Load();
	winaudio->Load();
}

void SnakeGame::OnAttach()
{
}

void SnakeGame::OnDetach()
{
}
void SnakeGame::UpdateSnake()
{
		if (snake.empty()) return;
		if (snake.size() == 1)
		{
			glm::vec2 headDir = dir;
			if (headDir.x > 0) snake[0].second = &head_right.value();
			else if (headDir.x < 0) snake[0].second = &head_left.value();
			else if (headDir.y > 0) snake[0].second = &head_up.value();
			else if (headDir.y < 0) snake[0].second = &head_down.value();
			return;
		}

		{
			const glm::vec2 head = snake[0].first;
			const glm::vec2 second = snake[1].first;
			glm::vec2 headDir = head - second;

			if (headDir.x > 0) snake[0].second = &head_right.value();
			else if (headDir.x < 0) snake[0].second = &head_left.value();
			else if (headDir.y > 0) snake[0].second = &head_up.value();
			else if (headDir.y < 0) snake[0].second = &head_down.value();
		}

		
		{
			size_t last = snake.size() - 1;
			const glm::vec2 tail = snake[last].first;
			const glm::vec2 beforeTail = snake[last - 1].first;
			glm::vec2 tailDir = beforeTail - tail;

			if (tailDir.x > 0) snake[last].second = &tail_left.value();
			else if (tailDir.x < 0) snake[last].second = &tail_right.value();
			else if (tailDir.y > 0) snake[last].second = &tail_down.value();
			else if (tailDir.y < 0) snake[last].second = &tail_up.value();
		}

		for (size_t i = 1; i + 1 < snake.size(); ++i)
		{
			const glm::vec2 curr = snake[i].first;
			const glm::vec2 prev = snake[i - 1].first;
			const glm::vec2 next = snake[i + 1].first;

			glm::vec2 dirPrev = prev - curr;
			glm::vec2 dirNext = next - curr;

			if (dirPrev.x == 0 && dirNext.x == 0)
			{
				snake[i].second = &body_vertical.value();
				continue;
			}
			if (dirPrev.y == 0 && dirNext.y == 0)
			{
				snake[i].second = &body_horizontal.value();
				continue;
			}
			if ((dirPrev.x < 0 && dirNext.y < 0) || (dirNext.x < 0 && dirPrev.y < 0))
				snake[i].second = &body_bottomleft.value();
			else if ((dirPrev.x < 0 && dirNext.y > 0) || (dirNext.x < 0 && dirPrev.y > 0))
				snake[i].second = &body_topleft.value();
			else if ((dirPrev.x > 0 && dirNext.y > 0) || (dirNext.x > 0 && dirPrev.y > 0))
				snake[i].second = &body_topright.value();
			else if ((dirPrev.x > 0 && dirNext.y < 0) || (dirNext.x > 0 && dirPrev.y < 0))
				snake[i].second = &body_bottomright.value();
			else
				snake[i].second = &body_horizontal.value();
		}

}
void SnakeGame::OnUpdate(double delta)
{
	if (won)
	{
		m_Renderer->SubmitText("You won", m_Window->GetWidth() / 2 - m_Window->GetWidth() / 3, m_Window->GetHeight() - m_Window->GetHeight() / 10, 1.0f);
		return;
	}
	if (dead)
	{
		m_Renderer->SubmitText("Game over", m_Window->GetWidth() / 2 - m_Window->GetWidth() / 8, m_Window->GetHeight() - m_Window->GetHeight() / 10, 1.0f);
		return;
	}
	if (Dogo::Input::IsKeyPressed(DG_KEY_SPACE))
		running = !running;
	if (!running)
	{
		m_Renderer->SubmitText("Paused", m_Window->GetWidth() / 2 - m_Window->GetWidth() / 10, m_Window->GetHeight() - m_Window->GetHeight() / 10, 1.0f);
		return;
	}

	std::stringstream ss;
	ss << "Apples eaten: " << applesEaten << " --- Apples to eat: " << applesToEat;
	m_Renderer->SubmitText(ss.str(), m_Window->GetWidth() / 2 - m_Window->GetWidth() / 3, m_Window->GetHeight() - m_Window->GetHeight() / 10, 1.0f);
	glm::vec2 pos = snake.at(0).first;
	bool pressed = false;
	if (Dogo::Input::IsKeyPressed(DG_KEY_W)) { dir = glm::vec2(0.0f, square); pressed = true; }
	else if (Dogo::Input::IsKeyPressed(DG_KEY_S)) { dir = glm::vec2(0.0f, -square);; pressed = true; }
	else if (Dogo::Input::IsKeyPressed(DG_KEY_A)) { dir = glm::vec2(-square, 0.0f); pressed = true; }
	else if (Dogo::Input::IsKeyPressed(DG_KEY_D)) { dir = glm::vec2(square, 0.0f); pressed = true; }
	pos += dir;
	if (!pressed)
	{
		m_MoveTimer += delta;
		if (m_MoveTimer < m_MoveInterval)
			return;
	}
	m_MoveTimer = 0.0f;
	hasGrownThisMove = false;
	if (CheckBounds(pos) && (snake.back().first.x != pos.x || snake.back().first.y != pos.y))
	{
		if (CheckDeath(pos))
			return;
		snake.emplace_front(pos, &head_down.value());

		auto acomp = apple->GetComponent<Dogo::ECS::TransformComponent>();
		glm::vec2 applepos = acomp->GetPosition();
		if (applepos.x == pos.x && applepos.y == pos.y)
		{
			applesEaten++;
			apple->GetComponent<Dogo::ECS::AudioSourceComponent2D>()->Play();
			glm::vec2 newpos = GetRandomPositionInBounds();
			acomp->SetPosition({ newpos.x, newpos.y, 0.0f });
		}

		if (level == LEVEL::SLUG)
		{
			if (applesEaten >= 5)
			{
				m_MoveInterval = 0.2;
				applesToEat = 10;
				level = LEVEL::WORM;
				snakesize = 15;
			}
			if (snake.size() > snakesize)
			{
				snake.pop_back();
			}
		}
		else if (level == LEVEL::WORM)
		{
			if (applesEaten >= 10)
			{
				m_MoveInterval = 0.1;
				applesToEat = 15;
				level = LEVEL::PYTHON;
				snakesize = 30;
			}
			if (snake.size() > snakesize)
			{
				snake.pop_back();
			}
		}
		else if (level == LEVEL::PYTHON)
		{
			if (applesEaten >= 15)
			{
				won = true;
				winaudio->Play();
			}
			if (snake.size() > snakesize)
			{
				snake.pop_back(); 
			}
		}
		if (!hasGrownThisMove)
		{
			if (snake.size() - 1 < snakesize && snake.size() > 1)
			{
				glm::vec2 tail = snake.back().first;
				glm::vec2 second = snake[snake.size() - 2].first;

				glm::vec2 dir = tail - second;
				glm::vec2 growPos = tail + dir;
				if (CheckBounds(growPos))
				{
					if (dir.x > 0) snake.emplace_back(growPos, &tail_right.value());
					else if (dir.x < 0) snake.emplace_back(growPos, &tail_left.value());
					else if (dir.y > 0) snake.emplace_back(growPos, &tail_up.value());
					else if (dir.y < 0) snake.emplace_back(growPos, &tail_down.value());
				}
			}
		}
		UpdateSnake();
	}
}

void SnakeGame::OnResize()
{
}

void SnakeGame::Submit()
{
	m_Renderer->SetViewMatrix(m_Camera->GetViewMatrix());
	m_Renderer->SetProjectionMatrix(m_Camera->GetProjectionMatrix());
	m_Renderer->Begin(m_Camera);
	CreateGrid();

	float g = 0.4f;
	for (auto& p : snake)
	{
		g += 0.025f;
		glm::clamp(g, 0.0f, 1.0f);
		m_Renderer->Submit(Dogo::CreateQuad(p.first.x, p.first.y, square, square, 0, 0), *(p.second));
	}
}

void SnakeGame::CreateGrid()
{
	for (float i = 0; i < gridPixel; i += square) {
		for (float j = 0; j < gridPixel; j += square) {
			m_Renderer->Submit(Dogo::CreateQuad(
				startX + i,
				startY + j,
				square, square, 0.0f, 0.0f), glm::vec4(0.0f, 0.3f, 0.0f, 0.9f));
		}
	}
}

bool SnakeGame::CheckBounds(const glm::vec2& nextPos)
{
	return nextPos.x >= startX &&
		nextPos.x < endX &&
		nextPos.y >= startY &&
		nextPos.y < endY;
}

bool SnakeGame::CheckDeath(const glm::vec2& pos)
{
	for (size_t i = 1; i < snake.size(); i++)
	{
		if (pos.x == snake.at(i).first.x && pos.y == snake.at(i).first.y)
		{
			dead = true;
			gameoveraudio->Play();
			return true;
		}
	}
	return false;
}


glm::vec2 SnakeGame::GetRandomPositionInBounds()
{
	glm::vec2 r = glm::vec2(0.0f, 0.0f);
	bool found = false;
	for (size_t tries = 0; !found && tries < 100; tries++)
	{
		int cx = distCell(gen);
		int cy = distCell(gen);

		float x = startX + cx * square;
		float y = startY + cy * square;
		if (!CheckBounds({ x, y }))
			continue;
		r = glm::vec2(x, y);
		break;
	}
	return r;
}
