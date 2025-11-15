#include "dgpch.h"
#include "Test.h"
#include "Dogo/Component/Components.h"
TestLayer::TestLayer(std::shared_ptr<Dogo::Renderer2D> renderer)
{
	m_Renderer = renderer;
	DogoECS::DG_ComponentManager* manager = Dogo::GetComponentManager();
	manager->RegisterComponent<Dogo::SpriteRendererComponent>();
	actor = new Dogo::Test2DActor(glm::vec3(0.0f));
	Dogo::SpriteRendererComponent* sp = manager->AddComponent<Dogo::SpriteRendererComponent>(actor->GetEntity());
	sp->sprite = Dogo::Sprite("test", "../Dogo/resources/Textures/lebron.png", Dogo::TextureType::T_2D, Dogo::FilterMode::BILINEAR, Dogo::Wrapping::REPEAT, 1280.0f, 720.0f);
}

void TestLayer::OnAttach()
{
}

void TestLayer::OnDetach()
{
}

void TestLayer::OnUpdate()
{
	DogoECS::DG_ComponentManager* manager = Dogo::GetComponentManager();
	for (auto it = manager->AllActiveBegin<Dogo::SpriteRendererComponent>();
		it != manager->AllActiveEnd<Dogo::SpriteRendererComponent>(); ++it)
	{
		Dogo::PositionComponent* pos = manager->GetComponent<Dogo::PositionComponent>(it->GetEntityID());
		it->Draw(m_Renderer, pos->x, pos->y);
	}
	m_Renderer->Flush();
}

void TestLayer::OnResizeNotify()
{
}