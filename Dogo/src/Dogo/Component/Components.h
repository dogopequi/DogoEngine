#pragma once
#include <DogoECS.h>
#include "Dogo/Renderer/2D/Sprite.h"
namespace Dogo
{
	inline static constexpr size_t NUM_ENTITIES = 5000;
	inline static constexpr size_t NUM_COMPONENTS = 10000;
	inline static DogoECS::DG_EntityManager entityManager(NUM_ENTITIES);
	inline static DogoECS::DG_ComponentManager componentManager(NUM_COMPONENTS, NUM_ENTITIES);

	inline DogoECS::DG_EntityManager* GetEntityManager() { return &entityManager; }
	inline DogoECS::DG_ComponentManager* GetComponentManager() { return &componentManager; }


	struct PositionComponent : public DogoECS::DG_Component
	{
		PositionComponent() {
			x = 0; y = 0; z = 0;
		}
		PositionComponent(float tx, float ty, float tz) : x(tx), y(ty), z(tz) {}
		float x, y, z;
	};
	struct VelocityComponent : public DogoECS::DG_Component {
		float vx = 0, vy = 0, vz = 0;
	};

	struct SpriteRendererComponent : public DogoECS::DG_Component
	{
		SpriteRendererComponent();
		Sprite sprite{};

		void Draw(std::weak_ptr<Dogo::Renderer2D> renderer, float actorX, float actorY);
		//layer
		//layer id
	};
}