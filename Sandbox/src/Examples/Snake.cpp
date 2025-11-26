#include "dgpch.h"
#include "Snake.h"
#include "Dogo/Component/Components.h"
#include "Dogo/Input/Input.h"
#include "Dogo/Renderer/Core/Texture.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>
SnakeGame::SnakeGame(const std::string& name, std::shared_ptr<Dogo::DogoWindow> window) : Layer(name, window), m_Physics(), m_Audio()
{
	m_Renderer = std::shared_ptr<Dogo::Renderer2D>(Dogo::Renderer2D::Create(L"../Dogo/resources/Shaders/2Dvertex.glsl", L"../Dogo/resources/Shaders/2Dpixel.glsl"));
	m_SpriteRenderer = Dogo::SpriteRenderSystem2D();
	m_Scene = std::make_shared<Dogo::Scene>();
	m_Camera = std::make_shared<Dogo::Camera>(Dogo::Camera::Orthographic(m_Window->GetWidth(), m_Window->GetHeight(), 0.1, 100.0f));
	m_Camera->SetRenderTargetSize(m_Window->GetWidth(), m_Window->GetHeight());
	m_Renderer->SetViewMatrix(m_Camera->GetViewMatrix());
	m_Renderer->SetProjectionMatrix(m_Camera->GetProjectionMatrix());
	m_Scene->SetMainCamera(m_Camera);
	m_Scene->AddCamera(m_Camera);
	Dogo::ECS::RegisterComponent<Dogo::ECS::SpriteRendererComponent>();
	Dogo::ECS::RegisterComponent<Dogo::ECS::RigidBodyComponent>();
	Dogo::ECS::RegisterComponent<Dogo::ECS::AudioSourceComponent2D>();
	actor = std::make_shared<Dogo::Snake>(glm::vec3(0.0f, 0.0f, 0.0f));
	apple = std::make_shared<Dogo::Apple>(glm::vec3(369, 100, 0.0f));
	//Dogo::UV uv = Dogo::GetTileUV(1, 1, 16, 16, 256, 256); example for an atlas
	Dogo::ECS::SpriteRendererComponent* p1 =  apple->AddComponent<Dogo::ECS::SpriteRendererComponent>();
	p1->sprite = Dogo::Sprite("apple", "../Dogo/resources/Textures/head_down.png", (float)spriteSize, (float)spriteSize);
	Dogo::ECS::SpriteRendererComponent* p0 = actor->AddComponent<Dogo::ECS::SpriteRendererComponent>();
	p0->sprite = Dogo::Sprite("snake", "../Dogo/resources/Textures/apple.png", (float)spriteSize, (float)spriteSize);
	if(p0->sprite.GetTexture().has_value())
		m_Renderer->PreLoadTexture(p0->sprite.GetTexture().value());
	if (p1->sprite.GetTexture().has_value())
		m_Renderer->PreLoadTexture(p1->sprite.GetTexture().value());

	m_Scene->AddGameObject(actor);
	m_Scene->AddGameObject(apple);
	m_Scene->Init();
}

void SnakeGame::OnAttach()
{
}

void SnakeGame::OnDetach()
{
}
void SnakeGame::TryMove(const glm::vec3& pos)
{

}
void SnakeGame::OnUpdate(double delta)
{
	m_MoveTimer += delta;
	if (m_MoveTimer >= m_MoveInterval)
	{
		auto comp = actor->GetComponent<Dogo::ECS::TransformComponent>();
		glm::vec3 pos = comp->GetPosition();
		if (Dogo::Input::IsKeyPressed(DG_KEY_W))
			pos.y -= square;
		else if (Dogo::Input::IsKeyPressed(DG_KEY_S))
			pos.y += square;
		if (Dogo::Input::IsKeyPressed(DG_KEY_A))
			pos.x -= square;
		else if (Dogo::Input::IsKeyPressed(DG_KEY_D))
			pos.x += square;
		m_MoveTimer = 0.0;
		TryMove(pos);
	}

	m_Scene->UpdateGameObjects(delta);
	//m_Physics.Update(delta);
	m_Audio.Update();
	for (auto cam : m_Scene->GetCameras())
	{
		glm::vec3& snakepos = actor->GetComponent<Dogo::ECS::TransformComponent>()->position;
		glm::vec3& applepos = apple->GetComponent<Dogo::ECS::TransformComponent>()->position;
		ImGui::Begin("Debug window");

		ImGui::PushID("snake");
		ImGui::DragFloat3("snake", glm::value_ptr(snakepos));
		ImGui::PopID();

		ImGui::PushID("apple");
		ImGui::DragFloat3("apple", glm::value_ptr(applepos));
		ImGui::PopID();

		ImGui::End();


		if (cam.expired())
			continue;
		cam.lock()->BindTarget();
		m_Window->ClearBuffers();
		m_Renderer->Begin(cam);
		//CreateGrid();
		m_Renderer->BeginBatch();
		for (float x = 0; x <= m_Window->GetWidth(); x += 32.0f)
		{
			m_Renderer->Submit(Dogo::CreateLine2D(
				{ x, 0.0f },
				{ x, (float)m_Window->GetHeight() },
				{ 0.3f, 0.3f, 0.3f, 1.0f }
			));
		}
		for (float y = 0; y <= m_Window->GetHeight(); y += 32.0f)
		{
			m_Renderer->Submit(Dogo::CreateLine2D(
				{ 0.0f, y },
				{ (float)m_Window->GetWidth(), y },
				{ 0.3f, 0.3f, 0.3f, 1.0f }
			));
		}
		m_Renderer->Submit(Dogo::GenerateCircle(glm::vec2(980.0f, 980.0f), 32.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		m_Renderer->Submit(Dogo::CreateTriangle(480.0f, 50.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		m_Renderer->Submit(Dogo::CreateThickLine(glm::vec2(200.0f, 200.0f), glm::vec2(400.0f, 400.0f), 5.0f),glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
		m_SpriteRenderer.Update(m_Renderer);
		m_Renderer->EndBatch();
		m_Renderer->Flush();
		cam.lock()->UnbindTarget();
	}
	auto mainCam = m_Scene->GetMainCamera().lock();
	if (mainCam)
	{
		m_Renderer->SetViewMatrix(mainCam->GetViewMatrix());
		m_Renderer->SetProjectionMatrix(mainCam->GetProjectionMatrix());
		m_FrameBuffer->Bind();
		uint32_t texID = mainCam->GetRenderTargetID();
		m_Renderer->RenderFrameBuffer(texID, m_Window->GetWidth(), m_Window->GetHeight());
		m_FrameBuffer->Unbind();
	}

}

void SnakeGame::OnResize()
{
	resized = true;
}

void SnakeGame::CreateGrid()
{
    float gridPixel = (float)m_Window->GetHeight() * 0.8f;
    float startX = (m_Window->GetWidth() - gridPixel) / 2.0f;
    float startY = (m_Window->GetHeight() - gridPixel) / 2.0f;

    for (float i = 0; i < gridPixel; i += square) {
        for (float j = 0; j < gridPixel; j += square) {
            //m_Renderer->Submit(Dogo::CreateQuad(
            //    startX + i,
            //    startY + j,
            //    square, square, 0.0f, 0.0f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
        }
    }
}
