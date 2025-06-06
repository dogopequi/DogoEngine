#include "dgpch.h"
#include "Pong.h"
#include "../vendor/DogoECS/include/DG_Component.h"
#include "Dogo/Component/Component.h"
#include "Dogo/Renderer/UI/UI.h"
#include "Dogo/Input/Input.h"
#include "Dogo/Renderer/Renderer2D.h"
Pong::Pong(std::shared_ptr<Dogo::Renderer2D> renderer)
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
	Dogo::DogoUI::UIAddGamePanel(panel);
	panel->AddElement(startbutton);
	panel->AddElement(pausebutton);
	Setup();

	float angle = float((rand() % 90) - 45);
	float rad = glm::radians(angle);
	glm::vec2 direction = glm::normalize(glm::vec2(cos(rad), sin(rad)));
	velocity = direction * speed;

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

	Dogo::DogoUI::MousePosition = Dogo::Input::GetMousePosition();


	std::string fpsText = "FPS: " + std::to_string((uint32_t)(1.0 / deltaTime));
	Renderer->SubmitText(fpsText.c_str(), 1.0f, panel->size.y / 2 - panel->size.y / 4, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	std::string playerScoreText = "Player 1's score: " + std::to_string(playerScore);
	Renderer->SubmitText(playerScoreText.c_str(), window->GetWidth() / 6, (panel->size.y / 2 - panel->size.y / 4), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	std::string otherScoreText = " Player 2's score: " + std::to_string(otherScore);
	Renderer->SubmitText(otherScoreText.c_str(), (window->GetWidth() - window->GetWidth() / 6 - (panel->size.y / 2 - panel->size.y / 4)), (panel->size.y / 2 - panel->size.y / 4), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));


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

			angle = float((rand() % 90) - 45);
			rad = glm::radians(angle);
			glm::vec2 direction = glm::normalize(glm::vec2(cos(rad), sin(rad)));
			velocity = direction * speed;
		}
		else
		{
			ball = newBallPos;
		}
	}
	Renderer->Flush();
	Dogo::DogoUI::UIRenderGameElements(Renderer);
	Renderer->RenderText();
}

void Pong::OnResizeNotify()
{
	Setup();
}

void Pong::Setup()
{
	float windowWidth = window->GetWidth();
	float windowHeight = window->GetHeight();

	panel->visible = true;
	panel->color = { 0.0f, 0.0f, 1.0f };
	panel->size = { windowWidth, windowHeight / 8 };
	panel->pos = { 0.0f, 0.0f };

	float buttonWidth = windowWidth / 8;
	float buttonHeight = windowHeight / 20;
	float buttonY = panel->size.y / 2.0f - buttonHeight / 2.0f;
	float buttonSpacing = windowWidth / 12;

	startbutton->visible = true;
	startbutton->text = "Start";
	startbutton->size = { buttonWidth, buttonHeight };
	startbutton->pos = { windowWidth / 2.0f - buttonWidth - buttonSpacing / 2.0f, buttonY };
	startbutton->color = { 0.0f, 1.0f, 0.0f };
	startbutton->onClick = [this]() { DG_INFO("Started game"); paused = false; };
	startbutton->button = 0;

	pausebutton->visible = true;
	pausebutton->text = "Pause";
	pausebutton->size = { buttonWidth, buttonHeight };
	pausebutton->pos = { windowWidth / 2.0f + buttonSpacing / 2.0f, buttonY };
	pausebutton->color = { 0.0f, 1.0f, 0.0f };
	pausebutton->onClick = [this]() { DG_INFO("Paused game"); paused = true; };
	pausebutton->button = 0;

	float playAreaTop = panel->size.y;
	float playAreaHeight = windowHeight - panel->size.y;
	float paddleHeight = windowHeight / 8;
	float paddleWidth = windowWidth / 10;


	player = playAreaHeight / 2.0f + playAreaTop;
	other = player;


	bottom = windowHeight - paddleHeight;
	top = playAreaTop + paddleHeight;
	left = paddleWidth;
	right = windowWidth - paddleWidth;

	ball = { windowWidth / 2.0f, windowHeight / 2.0f };

}
