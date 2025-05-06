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

		void AddDynamicModel(Model* model);
		void AddStaticModel(Model* model);
		void Update();
		
		inline TransformComponent* GetTC() const { return TC; }

		inline void SetPosition(float x, float y, float z)
		{
			TC->SetX(x);
			TC->SetY(y);
			TC->SetZ(z);
		}

		inline glm::vec3 GetPosition() const
		{
			return glm::vec3(TC->GetX(), TC->GetY(), TC->GetZ());
		}

		inline Model* GetModel() const
		{
			if(SMC != nullptr)
				return SMC->GetModel();
			if (DMC != nullptr)
				return DMC->GetModel();
			return nullptr;
		}

		inline void AddForce(glm::vec3 force)
		{
			if (DMC != nullptr)
				DMC->GetBody()->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eFORCE);
		}
		inline void AddImpulse(glm::vec3 force)
		{
			if (DMC != nullptr)
				DMC->GetBody()->addForce(PxVec3(force.x, force.y, force.z), PxForceMode::eIMPULSE);
		}

	private:
		DogoECS::Entity* m_Entity;
		TransformComponent* TC;
		StaticMeshComponent* SMC = nullptr;
		DynamicMeshComponent* DMC = nullptr;
		PxShape* m_Shape;
	};
}
