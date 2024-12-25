#pragma once
#include "Dogo/Renderer/AssimpModel.h"
#include "Entity.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
	class TransformComponent;
	class Actor
	{
	public:
		Actor(Model* model);
		~Actor();


	private:
		DogoECS::Entity* m_Entity;
		TransformComponent* TC;
		PxShape* m_Shape;
		PxRigidStatic* m_StaticBody;
		Model* model;
	};
}
