#include "dgpch.h"
#include "Actor.h"
#include "Dogo/Component/Component.h"
namespace Dogo
{
	Actor::Actor(Model* model)
	{
		m_Entity = DogoECS::DG_EntityManager::CreateEntity();
		TC = m_Entity->AddComponent<TransformComponent>();
		TC->SetX(0.0f);
		TC->SetY(0.0f);
		TC->SetZ(0.0f);
		m_Shape = DG_Physics::GetShape(2.0f, 2.0f, 2.0f);
		PxTransform localTm(PxVec3(2.0f, 2.0f, 2.0f));
		m_StaticBody = DG_Physics::GetRigidStatic(TC->GetTransform(), localTm);
		m_StaticBody->attachShape(*m_Shape);
		DG_Physics::AddActor(m_StaticBody);
		this->model = model;
	}
	Actor::~Actor()
	{
		m_Entity->RemoveComponent<TransformComponent>(TC->GetComponentID_ui64());
		delete model;
	}
}