#include "dgpch.h"
#include "Actor.h"
#include "Dogo/Input/Input.h"
namespace Dogo
{
	GameObject::GameObject(const glm::vec3& pos)
	{
		m_Entity = ECS::CreateEntity();
		auto Pos = AddComponent<ECS::TransformComponent>(pos);
	}
	Actor2D::Actor2D(const glm::vec3& pos) : GameObject(pos)
	{
	}
	Actor::Actor(const glm::vec3& pos) : GameObject(pos)
	{
	}
	Snake::Snake(const glm::vec3& pos) : Actor2D(pos)
	{
	}
	void Snake::Tick(double delta)
	{

	}

	Apple::Apple(const glm::vec3& pos) : Actor2D(pos)
	{
	}
}