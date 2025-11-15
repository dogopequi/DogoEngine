#pragma once
#include "Dogo/Physics/DG_Physics.h"
#include "Dogo/Component/Components.h"
namespace Dogo
{
	class GameObject
	{
	public:
		GameObject() = delete;
		GameObject(const glm::vec3& pos);

		virtual DogoECS::Entity* GetEntity() const { return m_Entity; }

		virtual void Tick(float delta) {};

	protected:
		DogoECS::Entity* m_Entity;
		PositionComponent* m_PosComp;

	};

	class Actor2D : public GameObject
	{
	public:
		Actor2D() = delete;
		Actor2D(const glm::vec3& pos);

	private:
	};

	class Actor : public GameObject
	{
	public:
		Actor() = delete;
		Actor(const glm::vec3& pos);

	private:

	};

	class Test2DActor : public Actor2D
	{
	public:
		Test2DActor() = delete;
		Test2DActor(const glm::vec3& pos) : Actor2D(pos) {}


	private:
		SpriteRendererComponent* spriteRenderer;
	};
}
