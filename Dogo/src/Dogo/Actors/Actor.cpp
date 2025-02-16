#include "dgpch.h"
#include "Actor.h"
#include "Dogo/Component/Component.h"
namespace Dogo
{
	Actor::Actor()
	{
		m_Entity = DogoECS::DG_EntityManager::CreateEntity();
		TC = m_Entity->AddComponent<TransformComponent>();
		SMC = m_Entity->AddComponent<StaticMeshComponent>();
		m_Shape = DG_Physics::GetShape(2.0f, 2.0f, 2.0f);
	}
	Actor::~Actor()
	{
		m_Entity->RemoveComponent<TransformComponent>(TC->GetComponentID_ui64());
		m_Entity->RemoveComponent<StaticMeshComponent>(SMC->GetComponentID_ui64());
	}
	void Actor::AddModel(Model* model)
	{
		SMC->AddModel(model);
		TC->SetTransform(new physx::PxTransform(PxVec3(model->GetPosition().x, model->GetPosition().y, model->GetPosition().z)));
		SMC->Init(*TC->GetTransform());
		SMC->AttachToParent(m_Shape);
		DG_Physics::AddActor(SMC->GetActor());
	}
	void Actor::Update()
	{
	}
}