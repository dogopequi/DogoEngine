#pragma once
#include "Dogo/Renderer/AssimpModel.h"
#include "Entity.h"
#include "Dogo/Physics/DG_Physics.h"
namespace Dogo
{
	class TransformComponent;
	class StaticMeshComponent;
	class Actor
	{
	public:
		Actor();
		~Actor();

		void AddModel(Model* model);
		void Update();
		
		TransformComponent* GetTC() { return TC; }

	private:
		DogoECS::Entity* m_Entity;
		TransformComponent* TC;
		StaticMeshComponent* SMC;
		PxShape* m_Shape;
	};
}
