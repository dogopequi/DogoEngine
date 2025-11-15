#include "dgpch.h"
#include "Actor.h"
namespace Dogo
{
	GameObject::GameObject(const glm::vec3& pos)
	{
		DogoECS::DG_EntityManager* entityManager = GetEntityManager();
		DogoECS::DG_ComponentManager* compManager = GetComponentManager();
		m_Entity = entityManager->CreateEntity();
		m_PosComp = compManager->AddComponent<Dogo::PositionComponent>(m_Entity);
	}
	Actor2D::Actor2D(const glm::vec3& pos) : GameObject(pos)
	{
	}
	Actor::Actor(const glm::vec3& pos) : GameObject(pos)
	{
	}
}