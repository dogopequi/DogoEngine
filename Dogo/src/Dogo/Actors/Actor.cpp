#include "dgpch.h"
#include "Actor.h"
#include "Dogo/Component/Component.h"
namespace Dogo
{
	Actor::Actor()
	{
		m_Entity = DogoECS::DG_EntityManager::CreateEntity();
		TC = m_Entity->AddComponent<TransformComponent>();
		m_Shape = DG_Physics::GetShape(2.0f, 2.0f, 2.0f);
	}
	Actor::~Actor()
	{
		m_Entity->RemoveComponent<TransformComponent>(TC->GetComponentID_ui64());
		if(SMC != nullptr)
			m_Entity->RemoveComponent<StaticMeshComponent>(SMC->GetComponentID_ui64());
		if(DMC != nullptr)
			m_Entity->RemoveComponent<DynamicMeshComponent>(SMC->GetComponentID_ui64());
	}
	void Actor::AddStaticModel(Model* model)
	{
		SMC = m_Entity->AddComponent<StaticMeshComponent>();
		SMC->AddModel(model);
		model->GetTC()->AttachComponentToComponent(TC);
		SMC->Init(TC->GetTransform());
		SMC->AttachToParent(m_Shape);
		DG_Physics::AddActor(SMC->GetBody());
	}
	void Actor::AddDynamicModel(Model* model)
	{
		DMC = m_Entity->AddComponent<DynamicMeshComponent>();
		DMC->AddModel(model);
		model->GetTC()->AttachComponentToComponent(TC);
		TC->AttachComponentToComponent(DMC);
		DMC->Init(TC->GetTransform());
		DMC->AttachToParent(m_Shape);
		DG_Physics::AddActor(DMC->GetBody());
	}
	void Actor::Update()
	{
	}


}