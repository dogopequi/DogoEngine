#include "dgpch.h"
#include "Pong.h"
#include "../vendor/DogoECS/include/DG_Component.h"
#include "Dogo/Component/Component.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Dogo/Input/Input.h"
#include "Dogo/Renderer/Renderer2D.h"
Pong::Pong(Dogo::Renderer2D* renderer)
	: Layer("AppLayer")
{
	DG_INFO("Example App starting");
	Renderer = renderer;
}

void Pong::OnAttach()
{
	DG_INFO("AppLayer Attached");
	//Dogo::Texture* lebron = Dogo::Texture::Create("../Dogo/resources/Textures/lebron.png", "legacy", Dogo::TextureType::twoD, "lebron");
	//Dogo::Texture* rat = Dogo::Texture::Create("..Dogo/resources/Textures/rat.png", "legacy", Dogo::TextureType::twoD, "rat");
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	Renderer->LoadFont("../Dogo/resources/Fonts/arial.ttf", 20);
	startbutton = std::make_shared<Dogo::DogoUI::UIButton>();
	pausebutton = std::make_shared<Dogo::DogoUI::UIButton>();
	panel = std::make_shared<Dogo::DogoUI::UIPanel>();
	Dogo::DogoUI::AddElement(panel);
	panel->visible = true;
	panel->color = { 0.0f, 0.0f, 1.0f };
	panel->size = { window->GetWidth(), 50.0f };
	panel->pos = { 0.0f, 0.0f};

	startbutton->visible = true;
	startbutton->text = "Start";
	startbutton->size = { 100.0f, 30.0f };
	startbutton->pos = {panel->size.x / 2 - 50.0f, panel->size.y / 2 - startbutton->size.y / 2 };
	startbutton->color = { 0.0f, 1.0f, 0.0f };
	startbutton->onClick = [this]() { DG_INFO("Started game"); paused = false; };

	pausebutton->visible = true;
	pausebutton->text = "Pause";
	pausebutton->size = { 100.0f, 30.0f };
	pausebutton->pos = { panel->size.x / 2 + 50.0f, panel->size.y / 2 - pausebutton->size.y / 2 };
	pausebutton->color = { 0.0f, 1.0f, 0.0f };
	pausebutton->onClick = [this]() { DG_INFO("Paused game"); paused = true; };
	panel->AddElement(startbutton);
	panel->AddElement(pausebutton);

	player = (window->GetHeight() - panel->size.y) / 2.0f;
	other = player;

	bottom = window->GetHeight() - panel->size.y - height;
	top = height*2;
	left = height;
	right = window->GetWidth() - height - width;

	ball = { window->GetWidth() / 2.0f, window->GetHeight() / 2.0f };

	float angle = (rand() % 90) - 45;
	float rad = glm::radians(angle);
	glm::vec2 direction = glm::normalize(glm::vec2(cos(rad), sin(rad)));
	velocity = direction * speed;

	DG_INFO("bottom: %f, top: %f, left: %f, right: %f", bottom, top, left, right);

	time = window->GetTime();
}
void Pong::OnDetach()
{
	DG_INFO("AppLayer Detached");
}
void Pong::OnUpdate()
{
	double currentTime = window->GetTime();
	double deltaTime = currentTime - time;
	time = currentTime;


	Dogo::Input::Int2 mouse = Dogo::Input::GetMousePosition();
	Dogo::DogoUI::HandleInput(glm::vec2(mouse.x, mouse.y), Dogo::Input::IsMouseButtonPressed(0)); // right now input is crazy, it calls this a bunch of times. will fix soon


	std::string fpsText = "FPS: " + std::to_string((uint32_t)(1.0 / deltaTime));
	Renderer->SubmitText(fpsText.c_str(), 1.0f, panel->size.y / 2 - panel->size.y / 4, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	std::string playerScoreText = "Player 1's score: " + std::to_string(playerScore);
	Renderer->SubmitText(playerScoreText.c_str(), window->GetWidth() / 2 - 300.0f, (panel->size.y / 2 - panel->size.y / 4), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	std::string otherScoreText = " Player 2's score: " + std::to_string(otherScore);
	Renderer->SubmitText(otherScoreText.c_str(), (window->GetWidth() / 2 + 300.0f), (panel->size.y / 2 - panel->size.y / 4), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));


	Renderer->Submit(Dogo::CreateQuad(left, player, glm::vec4(1.0f), width, height, 0.0f));
	Renderer->Submit(Dogo::CreateQuad(right, other, glm::vec4(1.0f), width, height, 0.0f));

	// could have just used a quad, but i wanted to show off lines, i guess
	Renderer->Submit(Dogo::CreateLine2D(glm::vec3(left, top, 0.0f), glm::vec3(right + width, top, 0.0f)
		, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	Renderer->Submit(Dogo::CreateLine2D(glm::vec3(left, bottom + height, 0.0f), glm::vec3(right + width, bottom + height, 0.0f)
		, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	Renderer->Submit(Dogo::CreateLine2D(glm::vec3(left, bottom + height, 0.0f), glm::vec3(left, top, 0.0f)
		, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	Renderer->Submit(Dogo::CreateLine2D(glm::vec3(right + width, bottom + height, 0.0f), glm::vec3(right + width, top, 0.0f)
		, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	Renderer->Submit(Dogo::GenerateCircle(ball, radius, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f));

	if (!paused)
	{
		/// gameplay

		if (Dogo::Input::IsKeyPressed(DG_KEY_W))
		{
			float newPos = player - speed * (float)deltaTime;
			if (newPos >= top)
				player = newPos;
			else
				player = top;
		}
		if (Dogo::Input::IsKeyPressed(DG_KEY_S))
		{
			float newPos = player + speed * (float)deltaTime;
			if (newPos <= bottom)
				player = newPos;
			else
				player = bottom;
		}
		/// I need to fix the kets in INPUT. I switched keyboards.
		if (Dogo::Input::IsKeyPressed(265))
		{
			float newPos = other - speed * (float)deltaTime;
			if (newPos >= top)
				other = newPos;
			else
				other = top;
		}

		if (Dogo::Input::IsKeyPressed(264))
		{
			float newPos = other + speed * (float)deltaTime;;
			if (newPos <= bottom)
				other = newPos;
			else
				other = bottom;
		}

		/// BALL

		glm::vec2 newBallPos = ball + velocity * (float)deltaTime;
		if (newBallPos.y - radius < top)
		{
			velocity.y = fabs(velocity.y);
			newBallPos.y = top + radius;
		}
		else if (newBallPos.y + radius > bottom + height)
		{
			velocity.y = -fabs(velocity.y);
			newBallPos.y = bottom + height - radius;
		}

		if (newBallPos.x - radius < left + width &&
			newBallPos.y > player && newBallPos.y < player + height)
		{
			velocity.x = fabs(velocity.x);
			newBallPos.x = left + width + radius;
		}
		if (newBallPos.x + radius > right &&
			newBallPos.y > other && newBallPos.y < other + height)
		{
			velocity.x = -fabs(velocity.x);
			newBallPos.x = right - radius;
		}
		if (newBallPos.x < left || newBallPos.x > right)
		{
			if (newBallPos.x < left) {
				otherScore++;
			}
			else {
				playerScore++;
			}

			ball = glm::vec2(window->GetWidth() / 2.0f, window->GetHeight() / 2.0f);

			angle = (rand() % 90) - 45;
			rad = glm::radians(angle);
			glm::vec2 direction = glm::normalize(glm::vec2(cos(rad), sin(rad)));
			velocity = direction * speed;
		}
		else
		{
			ball = newBallPos;
		}
	}
	///
	Renderer->Flush();
	Dogo::DogoUI::Render(Renderer);
	Renderer->RenderText();
}